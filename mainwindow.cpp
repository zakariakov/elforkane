/****************************************************************************
//   elforkane Copyright (C) 2012 yahia nouah <yahiaui@gmail.com>
//
//      This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
//      This is free software, and you are welcome to redistribute it
//      under certain conditions; type `show c' for details.
//
//  The hypothetical commands `show w' and `show c' should show the appropriate
//  parts of the General Public License.  Of course, your program's commands
//  might be different; for a GUI interface, you would use an "about box".
//
//    You should also get your employer (if you work as a programmer) or school,
//  if any, to sign a "copyright disclaimer" for the program, if necessary.
//  For more information on this, and how to apply and follow the GNU GPL, see
//  <http://www.gnu.org/licenses/>.
//
//    The GNU General Public License does not permit incorporating your program
//  into proprietary programs.  If your program is a subroutine library, you
//  may consider it more useful to permit linking proprietary applications with
//  the library.  If this is what you want to do, use the GNU Lesser General
//  Public License instead of this License.  But first, please read
//  <http://www.gnu.org/philosophy/why-not-lgpl.html>.
// ----------------------------------------------------------
** If you have questions regarding the use of this file, please contact
** yahia nouah (yahiaui@gmail.com)
** $elforkane_END_LICENSE$
**
****************************************************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QDebug>
#include "dialogaddreciter.h"
#include "dialogoption.h"
#include "dialogabout.h"
#include "dialogscript.h"
#include <QTimer>
#include <QSettings>
#include <QTextCodec>
#include <QDirIterator>
#include <math.h>       /* fmod */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),mSceenFull(0)
{

    database=new Database;
    sceenbase=new Sceenbase(this);
    //    NetWork=new netWork();

    //    QApplication::setLayoutDirection(Qt::RightToLeft);
    //تحديد مكان بيانات البرنامج حسب نوع النظام
    QDir appDir(qApp->applicationDirPath());
#if defined(Q_OS_WIN)
    appDir.cdUp();
    m_appPath=  appDir.absolutePath()+"/share/elforkane";
#elif defined(Q_OS_MAC)
    if (appDir.dirName() == "MacOS") {
        appDir.cdUp();
        appDir.cdUp();
        appDir.cdUp();
        m_appPath=  appDir.absolutePath()+"/elforkane";
    }
#else
    appDir.cdUp();
    m_appPath=  appDir.absolutePath()+"/share/elforkane";
#endif

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))

    mPlayer=new PlayerMultimedia(m_appPath,this);
#else
    mPlayer=new Player(m_appPath,this);
#endif
    //    mPlayer=new Player(m_appPath,this);
    //تحميل الاعدادات الافتراضية للمتغيرات


    m_repeatNumber=2;
    m_isRepeatNumber=false;
    m_layouDir=trUtf8("ltr","layou direction for this language ex:rtl for arabic");
    m_restoreDefaults=false;
    //  m_difer=0;

    m_px=457;
    m_numPlayed=1;
    // m_pHieght=672;
    //  m_pWith=456;
    //  m_soundPath="audio/Husary_Mujawwad_64kbps";
    m_autoRepeatPage=false;
    m_autoRepeatOne=false;
    m_autoRepeatSura=false;
    m_autoRepeatFromTo=false;
    m_autoPlayNext=true;
    isPlay=false;
    emit popupVisible(false);
    //التحميلات والاعدادات
    loadSetting();   //تحميل ااعدادات المستخدم
    if(m_layouDir=="ltr"){
        QApplication::setLayoutDirection(Qt::LeftToRight);
    }else{
        QApplication::setLayoutDirection(Qt::RightToLeft);
    }
    ui->setupUi(this);
    setupToolbarIcons();//انشاء الادوات والايقونات

    //  sceenbase->setCurentPages(2,1,1);
    sceenbase->setAppPath(m_appPath);
    sceenbase->setColorSelection(m_selectColor);
    sceenbase->setThemeFolder(m_themeFolder);
    sceenbase->setwinLocal(this->locale());
    sceenbase->setRewayat(m_curentRiwaya);
    sceenbase->setShowSelection(m_showSelection);


    createTrayIcon();//انشاء ايقونة صينية النظام

    //تحميل البيانات

    database->chargeCsvs(m_curentRiwaya);
    database->treeChargeJozaa(ui->treeWidgetIndex);
    database->treeChargeSoura(ui->treeWidgetIndex,false,comboSura,m_layouDir,m_sura-1);

    chargeDataTools();    // تحميل  التراجم التفاسير بيانات المقرئين

    //تحديد مسار الصوت الاخير
    QString txt=comboBoxReciter-> itemData(m_receter).toString();
    m_soundPath=txt.section("|",0,0);
    m_soundUrl=txt.section("|",1,1);

    //الانتقال الى الموضع المحدد
    setCurentPos(m_id);


    //-------تحميل الاضافات لملأ الشاشة
//    loadPlugin();


    int hieght=676;

    if(m_showMenu==true)
        hieght=hieght+ui->menuBar->height();

    if(m_standardTool==true)
        hieght=hieght+ui->toolBar->height();

    // qDebug()<<"hieght ------------------"<<hieght;
    this->resize(466*2,hieght);
    sceenbase->setAnimationEnabled(m_animEnabled);

    timerScreen = new QTimer(this);
    connect(timerScreen, SIGNAL(timeout()), this, SLOT(runtimerScreen()));
    connect(sceenbase, SIGNAL(setPos(int)), this, SLOT(setCurentPos(int)));
    sceenbase->updatePages();
    connect(mPlayer,SIGNAL(finished()),this,SLOT(mediaFinished()));

    //    QWinJumpList jumplist;
    //    jumplist.recent()->setVisible(true);
    //   createTaskbar();
    //   createThumbnailToolBar();
}

void MainWindow::closeEvent(QCloseEvent *e)
{
   if(trayIcon->isVisible()){
       this->hide();
       e->ignore();
       return;

   }

    qDebug()<<"closing";
    mPlayer->stop();
    close();
    qDebug()<<"closing";
    mPlayer->stop();
    QFile fileReciter(QDir::homePath()+"/.elforkane/reciterInfo");
    if (!fileReciter.open(QFile::WriteOnly)){
        // return ;
    }
    QTextStream out(&fileReciter);
    out.setCodec(QTextCodec::codecForName("UTF-8"));
    for (int i=0;i<comboBoxReciter->count();i++){
        QString txtName=comboBoxReciter->itemText(i);
        QVariant txtData=comboBoxReciter->itemData(i);

        out << txtName+","+txtData.toString()+"\n";
        //   qDebug()<<txtData.toString();
    }
    fileReciter.close();
    if(m_restoreDefaults==false){
        saveSetting();
    }

    if(mSceenFull)
      delete  mSceenFull;


    delete database;
    //delete sceenbase;

    //
    qDebug()<<"closing quit";
    delete ui;
    // delete mPlayer;
    //  qApp->quit();

    e->accept();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setupToolbarIcons()
{
    ui->lineEditSearchTree->installEventFilter(this);
    ui->lineEditSearchTree->setText(trUtf8("Search"));
    ui->lineEditSearchTree->setStyleSheet("QLineEdit {font: italic;color: rgb(115, 115, 115);}");
    ui->dockWidget->setVisible(false);
    ui-> treeWidgetIndex->setColumnHidden(1,true);
    ui->treeWidgetSearch->setColumnHidden(3,true);
    ui->treeWidgetSearch->setColumnWidth(0,50);
    ui->treeWidgetSearch->setColumnWidth(1,30);
    ui->treeWidgetSearch->setColumnWidth(2,300);

    ui->actionEnableAnimFull->setChecked(m_fullAnimEnable);
    ui->actionAbout->setIcon(QIcon::fromTheme("stock_about",QIcon(style()->standardPixmap(QStyle::SP_DialogHelpButton))));
    //------------اضافة ادوات الى المشهد حتى تعمل الاختصارات عند عدم ظهور القوائم

   // ui->graphicsView->setBackgroundBrush(QPixmap(":/img/tawhid.png"));
    ui->graphicsView->setBackgroundBrush(QBrush(QColor("#7D9D64"),  Qt::Dense1Pattern));
    ui->graphicsView->addAction(ui->actionFullScreen);
    ui->graphicsView->addAction(ui->actionNextAya);
    ui->graphicsView->addAction(ui->actionPrevAya);
    ui->graphicsView->addAction(ui->actionPlayPause);
    ui->graphicsView->addAction(ui->actionNextSura);
    ui->graphicsView->addAction(ui->actionPrevSura);
    ui->graphicsView->addAction(ui->actionNextPage);
    ui->graphicsView->addAction(ui->actionPrevPage);
    ui->graphicsView->addAction(ui->actionEnableAnimFull);


    //---------toolbox style---------------------------------
    int mred= this->palette().color(QPalette::Dark).red();
    int mgreen= this->palette().color(QPalette::Dark).green();
    int mblue= this->palette().color(QPalette::Dark).blue();
    QString stylbox=QString("QToolBox::tab {"
                            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(%1, %2, %3, 100), stop:1 rgba(255, 255, 255, 80));"
                            "border-radius: 5px;}"
                            "QToolBox::tab:hover { "
                            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(255, 255, 255, 80), stop:1 rgba(%1, %2, %3, 200));"
                            "font: italic;  }"
                            "QToolBox::tab:selected { "
                            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(%1, %2, %3, 250), stop:1 rgba(255, 255, 255, 0));"
                            "}").arg(QString::number(mred)).arg(QString::number(mgreen)).arg(QString::number(mblue)) ;

    ui->toolBox->setStyleSheet(stylbox);
    ui->toolBox->setCurrentIndex(1);

    if(m_textIcon==true){
        ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    }else{
        ui->toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    }
    connect(ui->comboBoxSoraJozaa, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBoxSoraJozaa_currentIndexChanged(int)));
    connect(ui->treeWidgetIndex, SIGNAL(itemActivated(QTreeWidgetItem*,int)), this, SLOT(treeWidgetIndex_itemActivated(QTreeWidgetItem*,int)));
    connect(ui->lineEditSearchTree, SIGNAL(textChanged(QString)), this, SLOT(lineEditSearchTree_textChanged(QString)));
    connect(ui->dockWidget, SIGNAL(visibilityChanged(bool)), ui->actionNavigation, SLOT(setChecked(bool)));

    // ui->menuView->addAction(ui->toolBarAodioEffect->toggleViewAction());

    //  ui->toolBar->toggleViewAction()->setShortcut(QKeySequence(tr("Ctrl+M")));
    //   ui->toolBarAodioEffect->toggleViewAction()->setShortcut(QKeySequence(tr("Ctrl+E")));
    ///   ui->toolBarAodioEffect->toggleViewAction()->setIcon(QIcon(":/img/media-effect.png"));


    //ui->toolBarAodioEffect->setVisible(false);
    //-------------End--Phonon----------------------------------------------------


    //---------------setup actions

    spinSafha=new QSpinBox;
    spinSafha->setPrefix(trUtf8("P : "));
    spinSafha->setToolTip(trUtf8("Page"));
    connect(spinSafha, SIGNAL(editingFinished()), this, SLOT(goPage()));

    comboSura=new QComboBox;
    connect(comboSura, SIGNAL(activated(int)), this, SLOT(goSura(int )));
    connect(comboSura, SIGNAL(currentIndexChanged(int)), this, SLOT(setSpinAyaMaximum(int)));

    spinAya=new  QSpinBox;
    spinAya->setPrefix(trUtf8("A : "));
    spinAya->setToolTip(trUtf8("Aya"));
    connect(spinAya, SIGNAL(editingFinished()), this, SLOT(goAya()));

    spinJozaa=new  QSpinBox;
    spinJozaa->setPrefix(trUtf8("J : "));
    spinJozaa->setToolTip(trUtf8("Jozaa"));
    connect(spinJozaa, SIGNAL(editingFinished()), this, SLOT(goJozaa()));

    spinHizb=new  QSpinBox;
    spinHizb->setPrefix(trUtf8("H : "));
    spinHizb->setToolTip(trUtf8("Hizb"));
    connect(spinHizb, SIGNAL(editingFinished()), this, SLOT(goHizb()));


    spinAya->setMinimum(1);
    spinJozaa->setMinimum(1);
    spinJozaa->setMaximum(30);
    spinSafha->setMinimum(1);
    spinSafha->setMaximum(604);
    spinHizb->setMinimum(1);
    spinHizb->setMaximum(60);




    actTansTefsir=new QAction(QIcon(":/img/tefsir.png"),trUtf8("Translation and Tefsir"),this);
    actTansTefsir->setCheckable(true);
    actTansTefsir->setMenu(ui->menuTransTefsir);
    connect(actTansTefsir, SIGNAL(toggled(bool)), this, SLOT(popup_toggled(bool)));
    connect(this, SIGNAL(popupVisible(bool)), actTansTefsir, SLOT(setChecked(bool)));



    progress=new QProgressBar;

    progress->hide();

    //NetWork->setProgress(progress);
    //connect(NetWork, SIGNAL(progresseIsVisible(bool)), slider, SLOT(setHidden(bool)));
    //connect(NetWork, SIGNAL(progresseIsVisible(bool)), progress, SLOT(setVisible(bool)));
    //--------------------------------
    comboBoxReciter = new QComboBox;
    comboBoxReciter->setMaximumWidth(150);

    QMenu *menu=new QMenu;
    menu->addAction(ui->actionAddReceter);
    menu->addAction(ui->actionEditeReceter);
    menu->addAction(ui->actionRemoveReceter);
    ui->actionRceterEdite->setMenu(menu);

    connect(comboBoxReciter, SIGNAL(activated(int)), this, SLOT(comboBoxResiter_activated(int)));
    //--------------------------------
    QWidget *widget=new QWidget;
    QHBoxLayout *horizontalLayoutTool = new QHBoxLayout(widget);
    QSpacerItem *horizontalSpacer=new QSpacerItem(5, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayoutTool->addItem(horizontalSpacer);



    btnMenu=new QToolButton ;
    btnMenu->setIcon(QIcon(":/img/system-run.png"));
    btnMenu->setToolTip(trUtf8("menu"));
    //btnMenu->setFlat(true);
    btnMenu->setPopupMode(QToolButton::InstantPopup);

    QMenu *menuBar=new QMenu;
    menuBar->addMenu(ui->menuFile);
    menuBar->addMenu(ui->menu_edit);
    menuBar->addMenu(ui->menuView);
    menuBar->addMenu(ui->menuHelp);
    btnMenu->setMenu(menuBar);
    ui->menuBar->setVisible(m_showMenu);




    //------------------------------------



    //ui->dockWidget->toggleViewAction()->setIcon(QIcon(":/img/document-properties.png"));
    actMediaSafha=new QAction(this);
    actMediaSafha->setToolTip(trUtf8("Page"));
    actMediaSafha->setObjectName("actMediaSafha");
    connect(actMediaSafha, SIGNAL(triggered()), this, SLOT(actMediaExec()));

    actMediaSura=new QAction(this);
    actMediaSura->setToolTip(trUtf8("Sura"));
    actMediaSura->setObjectName("actMediaSura");
    connect(actMediaSura, SIGNAL(triggered()), this, SLOT(comboMediaExec()));

    actMediaAya=new QAction(this);
    actMediaAya->setToolTip(trUtf8("Aya"));
    actMediaAya->setObjectName("actMediaAya");
    connect(actMediaAya, SIGNAL(triggered()), this, SLOT(actMediaExec()));

    actMediaJozaa=new QAction(this);
    actMediaJozaa->setToolTip(trUtf8("Jozaa"));
    actMediaJozaa->setObjectName("actMediaJozaa");
    connect(actMediaJozaa, SIGNAL(triggered()), this, SLOT(actMediaExec()));

    actMediaHizb=new QAction(this);
    actMediaHizb->setToolTip(trUtf8("Hizb"));
    actMediaHizb->setObjectName("actMediaHizb");
    connect(actMediaHizb, SIGNAL(triggered()), this, SLOT(actMediaExec()));

    actMediaReciter=new QAction(this);
    actMediaReciter->setToolTip(trUtf8("Reciter"));
    actMediaReciter->setObjectName("actMediaReciter");
    connect(actMediaReciter, SIGNAL(triggered()), this, SLOT(comboMediaExec()));

    QAction *actionZoomIn=new QAction(QIcon(":/img/zoom-in.png"),trUtf8("&zoomIn"),this);
    QAction *actionZoomOut=new QAction(QIcon(":/img/zoom-out.png"),trUtf8("&zoomOut"),this);
    connect(actionZoomIn, SIGNAL(triggered()), sceenbase->textEdit, SLOT(zoomIn()));
    connect(actionZoomOut, SIGNAL(triggered()), sceenbase-> textEdit, SLOT(zoomOut()));
    QAction *actHidPop=new QAction(QIcon(":/img/list-remove.png"),trUtf8("&Hide"),this);
    connect(actHidPop, SIGNAL(triggered()), this, SLOT(hidePopup()));
    //اداة النص الذي يعرض عليه التفسير والترجمة
    //   textEdit=new QTextEdit();
    labelTransTefsir=new QLabel;
    labelTransTefsir->setMaximumWidth(150);

    QString labStyle="QLabel { font: bold;color: black;}";
    labelTransTefsir->setStyleSheet(labStyle);
    QToolButton *tbtnMenu=new QToolButton(this);
    tbtnMenu->setArrowType(Qt::DownArrow);
    connect(tbtnMenu, SIGNAL(pressed()), this, SLOT(menuTefsirAndTranslation()));

    btnMenu->setVisible(!m_showMenu);
    //اضافة الادوات الى اللوحة
    sceenbase->toolbarPopup->addAction(actHidPop);
    sceenbase->toolbarPopup->addSeparator();
    sceenbase->toolbarPopup->addAction(actionZoomIn);
    sceenbase->toolbarPopup->addAction(actionZoomOut);
    sceenbase->toolbarPopup->addWidget(labelTransTefsir);
    sceenbase->toolbarPopup->addWidget(tbtnMenu);
    sceenbase->setStandardTools(m_standardTool);


    if(m_standardTool==false){

        sceenbase->toolbarMedia->addAction(ui->actionOptions);
        sceenbase->toolbarMedia->addAction(ui->actionNavigation);
        sceenbase->toolbarMedia->addAction(ui->actionRepeatOption);
        sceenbase->toolbarMedia->addAction(ui->actionFullScreen);
        sceenbase->toolbarMedia->addAction(actTansTefsir);
        sceenbase->toolbarMedia->addSeparator();
        sceenbase->toolbarMedia->addAction(actMediaSafha);
        sceenbase->toolbarMedia->addAction(actMediaSura);
        sceenbase->toolbarMedia->addAction(actMediaAya);
        sceenbase->toolbarMedia->addAction(actMediaJozaa);
        sceenbase->toolbarMedia->addAction(actMediaHizb);
        sceenbase->toolbarMedia->addSeparator();
        sceenbase->toolbarMedia->addAction(actMediaReciter);
        sceenbase->toolbarMedia->addAction(ui->actionRceterEdite);

        sceenbase->toolbarMedia->addSeparator();

        sceenbase->toolbarMedia->addWidget(mPlayer);
        //     sceenbase->toolbarMedia->addAction(ui->toolBarAodioEffect->toggleViewAction());
        sceenbase->toolbarMedia->addSeparator();
        sceenbase->toolbarMedia->addAction(ui->actionMemoriz);
        if(m_showMenu==false){
            btnMenu->setParent(this);
            btnMenu->setVisible(false);
        }
    }else{
        //-----------------toolbar add actions-------------------
        ui->toolBar->addAction(ui->actionOptions);
        ui->toolBar->addAction(ui->actionNavigation);
        ui->toolBar->addAction(ui->actionRepeatOption);
        ui->toolBar->addAction(ui->actionFullScreen);
        ui->toolBar->addAction(actTansTefsir);
        ui->toolBar->addSeparator();
        //------------------toolbar add spins-------------------
        ui->toolBar->addWidget(spinSafha);
        ui->toolBar->addWidget(comboSura);
        ui->toolBar->addWidget(spinAya);
        ui->toolBar->addWidget(spinJozaa);
        ui->toolBar->addWidget(spinHizb);
        ui->toolBar->addSeparator();
        //-------------------------reciter--------------------------
        ui->toolBar->addWidget(comboBoxReciter);
        ui->toolBar->addAction(ui->actionRceterEdite);

        if(m_showMediaControl==true){
            sceenbase->setMediaControleVisible(false);
            ui->toolBar->addSeparator();
            ui->toolBar->addWidget(mPlayer);

            //     ui->toolBar->addAction(ui->toolBarAodioEffect->toggleViewAction());
            ui->toolBar->addSeparator();
        }else{

            sceenbase->toolbarMedia->addWidget(mPlayer);
            //   sceenbase->toolbarMedia->addAction(ui->toolBarAodioEffect->toggleViewAction());
        }

        ui->toolBar->addWidget(widget);
        if(m_showMenu==false)
            ui->toolBar->addWidget(btnMenu);
        ui->toolBar->addAction(ui->actionMemoriz);
    }


    ui->graphicsView->setScene(sceenbase);
    popup_toggled(m_showPopup);
    ui->toolBar->setVisible(m_standardTool);

    stupActionsShortcuts();

}

void MainWindow::chargeDataTools()
{
    QFile file;
    //تحميل  التراجم --------------------------------------------
    file.setFileName(m_appPath+"/translat/translatInfo");
    if(file.open( QFile::ReadOnly)){
        QTextStream textStream(&file);
        textStream.setCodec(QTextCodec::codecForName("UTF-8"));
        QString line;
        line = textStream.readLine();//premier line

        QActionGroup *actTransGroup=new QActionGroup(this);
        while   (!line.isNull()) {
            QString txtdata=line.section(",",0,0);
            QString txt=line.section(",",1,1);
            //comboTrans->addItem(txt,txtdata);
            QAction *act=new QAction(txt,this);
            act->setData(txtdata);
            act->setCheckable(true);
            connect(act, SIGNAL(triggered()), this, SLOT(translationChanged()));
            myListActionTrans.append(act);
            actTransGroup->addAction(act);

            line = textStream.readLine();
        }
        if (myListActionTrans.count()>=m_curTranslation){
            myListActionTrans.at(m_curTranslation)->setChecked(true);
            QVariant data=  myListActionTrans.at(m_curTranslation)->data();
            QString txt=  myListActionTrans.at(m_curTranslation)->text();
            database->openDb(m_appPath+"/translat/"+data.toString());
            convertTextToHtm(database->getTranslation(m_id));
            labelTransTefsir->setText(txt);
            isTefsirPopup=false;
        }

        ui->menuTranslation->addActions(myListActionTrans);
    }

    file.close();
    //-تحميل التفاسير
    file.setFileName(m_appPath+"/tafasir/tafasirInfo");
    if(file.open( QFile::ReadOnly)){
        QTextStream textStream(&file);
        textStream.setCodec(QTextCodec::codecForName("UTF-8"));
        QString line;
        QList<QAction *>myListActionTefsir;
        QActionGroup *actTefsirGroup=new QActionGroup(this);
        line = textStream.readLine();//premier line
        while (!line.isNull()) {
            QString txtdata=line.section(",",0,0);
            QString txt=line.section(",",1,1);
            QAction *act=new QAction(txt,this);
            act->setData(txtdata);
            act->setCheckable(true);
            connect(act, SIGNAL(triggered()), this, SLOT(tefsirChanged()));

            myListActionTefsir.append(act);
            actTefsirGroup->addAction(act);

            line = textStream.readLine();
        }

        ui->menuTefsir->addActions(myListActionTefsir);
    }
    file.close();
    //تحميل بيانات المقرئين------------------------------------------------------------
    file.setFileName(QDir::homePath()+"/.elforkane/reciterInfo");
    if(!file.exists())
        file.setFileName(m_appPath+"/.elforkane/reciterInfo");

    if(file.open( QFile::ReadOnly)){

        QTextStream textStream(&file);
        textStream.setCodec(QTextCodec::codecForName("UTF-8"));
        QString line;
        line = textStream.readLine();//premier line

        while (!line.isNull()) {
            //QMessageBox::information(0,"",line);
            QString txt=line.section(",",0,0);
            QString txtdata=line.section(",",1,1);
            comboBoxReciter->addItem(txt.trimmed(),txtdata.trimmed());

            line = textStream.readLine();
        }
    }
    comboBoxReciter->setCurrentIndex(m_receter);
    file.close();

}

void MainWindow::actMediaExec()
{
    QAction *currenAction= qobject_cast<QAction *>(sender());
    bool ok;
    int min=0;
    int val=0;
    int max=0;
    int ret;
    QString title= trUtf8("getInteger");
    QString name=currenAction->objectName();

    if(name=="actMediaSafha") {
        min=spinSafha->minimum();
        val=spinSafha->value();
        max=spinSafha->maximum();
        title= trUtf8("get page");
        ret=0;
    }
    if(name=="actMediaAya") {
        min=spinAya->minimum();
        val=spinAya->value();
        max=spinAya->maximum();
        title= trUtf8("get Aya");
        ret=1;
    }
    if(name=="actMediaJozaa") {
        min=spinJozaa->minimum();
        val=spinJozaa->value();
        max=spinJozaa->maximum();
        title= trUtf8("get Jozaa");
        ret=2;
    }
    if(name=="actMediaHizb") {
        min=spinHizb->minimum();
        val=spinHizb->value();
        max=spinHizb->maximum();
        title= trUtf8("get Hizb");
        ret=3;
    }

    int i = QInputDialog::getInt(this,title,
                                 trUtf8("enter Value:"), val, min, max, 1, &ok);
    if (ok){
        if(ret==0)
            setPage(i);
        if(ret==1)
            setAya(comboSura->currentIndex()+1,i);
        if(ret==2)
            setJozaa(i);
        if(ret==3)
            setHizb(i);
    }
}

void MainWindow::comboMediaExec()
{
    QAction *currenAction= qobject_cast<QAction *>(sender());
    int val=-1;
    QString title;
    QString label;
    QStringList items;
    int ret;
    bool ok;

    QString name=currenAction->objectName();
    if(name=="actMediaSura") {
        val=comboSura->currentIndex();
        int count=comboSura->count();
        for(int i=0;i<count;i++){
            items <<comboSura->itemText(i);
        }

        title= trUtf8("get sura");
        label=trUtf8("shoose sura");
        ret=0;
    }

    if(name=="actMediaReciter") {
        val=comboBoxReciter->currentIndex();
        int count=comboBoxReciter->count();
        for(int i=0;i<count;i++){
            items <<comboBoxReciter->itemText(i);
        }
        title= trUtf8("get Reciter");
        label=trUtf8("shoose Reciter");
        ret=1;
    }
    QString item = QInputDialog::getItem(this,title,
                                         label, items, val, false, &ok);

    if (ok && !item.isEmpty())
        if(ret==0){
            int ind=   comboSura->findText(item);
            comboSura->setCurrentIndex(ind);
            goSura(ind);
        }
    if(ret==1){
        int ind=   comboBoxReciter->findText(item);
        comboBoxReciter->setCurrentIndex(ind);
        actMediaReciter->setText(item);
        comboBoxResiter_activated(ind);

    }


}


//begen---------------Events---------------------------------------


void MainWindow::resizeEvent ( QResizeEvent * )
{
    //   int ytop=0;e.

    if  (m_fitInView==true)
        ui->graphicsView->fitInView(QRect(0,0,456*2,672),Qt::KeepAspectRatio);


    sceenbase->setParentSize(ui->graphicsView->width(),ui->graphicsView->height(),this->pos().x());
}

void MainWindow::moveEvent ( QMoveEvent *  )
{

    sceenbase->setParentLeft(this->pos().x());
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {

    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        if(m_layouDir=="ltr"){
            QApplication::setLayoutDirection(Qt::LeftToRight);
        }else{
            QApplication::setLayoutDirection(Qt::RightToLeft);
        }

        break;
    case QEvent::WindowStateChange:
        if(this->isFullScreen()){
            ui->actionFullScreen->setShortcut(QKeySequence("Esc"));
        }else{
            ui->actionFullScreen->setShortcut(QKeySequence(listShortcut.at(14)));
        }

        break;

    default:
        break;
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{

    if (obj ==  ui->lineEditSearchTree) {
        if (event->type() == QEvent::FocusIn && ui->lineEditSearchTree->text()==trUtf8("Search")) {
            ui->lineEditSearchTree->setText("");
            ui->lineEditSearchTree->setStyleSheet("");
            return true;
        }else if (event->type() == QEvent::FocusOut && ui->lineEditSearchTree->text().isEmpty()){

            ui->lineEditSearchTree->setText(trUtf8("Search"));
            ui->lineEditSearchTree->setStyleSheet("QLineEdit {font: italic;color: rgb(115, 115, 115);}");
            return true;
        }

    }
    return QMainWindow::eventFilter(obj, event);
}
//end---------------Events---------------------------------------

//begen---------------save and load settings--------------------
void MainWindow::loadSetting()
{
    QSettings settings(QDir::homePath()+"/.elforkane/setting.ini",QSettings::IniFormat);

    settings.beginGroup("Main");
    m_id=settings.value("id",1).toInt();
    m_fitInView=  settings.value("fitInView", false).toBool();
    m_animEnabled=  settings.value("animEnabled", true).toBool();
    m_themeFolder=  settings.value("cadrFolder", "default").toString();
    m_showPopup=  settings.value("showPopup", false).toBool();
    m_receter=  settings.value("receter", 0).toInt();
    m_showInfo=  settings.value("showInfo",true).toBool();
    m_minimizToTry=  settings.value("minimizToTry",false).toBool();
    m_lng= settings.value("lng","sys").toString();
    m_textIcon=  settings.value("textIcon",false).toBool();
    m_infoDely=settings.value("infoDely",5).toInt();
    m_selectColor=settings.value("selectColor",QColor("#00aaff")).value<QColor>();

    m_showMediaControl=settings.value("showMediaControl",false).toBool();
    m_curTranslation=settings.value("curTranslation",0).toInt();
    m_showMenu= settings.value("showMenu",true).toBool();
    m_showSelection= settings.value("showSelection",true).toBool();
    m_reciteBasmala= settings.value("reciteBasmala",false).toBool();
    m_fullAnimEnable= settings.value("fullAnimEnable",true).toBool();
    //       m_fullScreenBgr=  settings.value("bgrFullScreen", m_appPath+"/fullscreen/bgrFull.png").toString();
    m_fullAnimated= settings.value("fullAnimated",false).toBool();
//    m_fullIndex= settings.value("fullIndex",0).toInt();
    m_curentRiwaya= settings.value("curentRiwaya","default").toString();
    m_locale= settings.value("locale",0).toInt();
    m_standardTool=settings.value("standardTool",false).toBool();
    m_saveMediaLoaded=settings.value("saveMediaLoaded",false).toBool();

    m_fullbackgroundDir=settings.value("fullbackgroundDir",m_appPath+"/fullscreen/bgrFull.png").toString();
    settings.endGroup();
    //  التحقق من المجلدات الصور في حالة تم حذفها او تغيرت الاعدادات او تشغيل البرنامج لاول مرة
    QDir dir;
    if(!dir.exists(m_appPath+"/images/"+m_curentRiwaya)||m_curentRiwaya.isEmpty()){
        m_curentRiwaya="default";

    }
    locateThemePath();//تحديد سمة الصفحات
    settings.beginGroup("Shortcut");

    listShortcut.append(settings.value("actionOptions","Ctrl+L").toString());
    listShortcut.append(settings.value("actionNavigation","Ctrl+F").toString());
    listShortcut.append(settings.value("actionRepeatOption","Ctrl+R").toString());
    listShortcut.append(settings.value("toolBarAodioEffect","Ctrl+E").toString());
    listShortcut.append(settings.value("actTansTefsir","Ctrl+T").toString());
    listShortcut.append(settings.value("actionNextPage","Alt+PgDown").toString());
    listShortcut.append(settings.value("actionPrevPage","Alt+PgUp").toString());
    listShortcut.append(settings.value("actionNextSura","Alt+Down").toString());
    listShortcut.append(settings.value("actionPrevSura","Alt+Up").toString());
    listShortcut.append(settings.value("actionNextAya","Alt+Left").toString());
    listShortcut.append(settings.value("actionPrevAya","Alt+Right").toString());
    listShortcut.append(settings.value("actionMemoriz","Alt+M").toString());
    listShortcut.append(settings.value("actionPlayPause","Space").toString());
    listShortcut.append(settings.value("actionStopMedia","S").toString());
    listShortcut.append(settings.value("actionFullScreen","F11").toString());

    settings.endGroup();


}

void MainWindow::saveSetting()
{
    QSettings settings(QDir::homePath()+"/.elforkane/setting.ini",QSettings::IniFormat);

    settings.beginGroup("Main");
    settings.setValue("id", m_id);
    settings.setValue("fitInView", m_fitInView);
    settings.setValue("animEnabled", m_animEnabled);
    settings.setValue("cadrFolder", m_themeFolder);
    settings.setValue("showPopup", m_showPopup);
    settings.setValue("receter", m_receter);
    settings.setValue("showInfo", m_showInfo);
    settings.setValue("minimizToTry", m_minimizToTry);
    settings.setValue("lng", m_lng);
    settings.setValue("textIcon", m_textIcon);
    settings.setValue("infoDely", m_infoDely);
    settings.setValue("selectColor", m_selectColor);
    settings.setValue("showMediaControl", m_showMediaControl);
    settings.setValue("curTranslation", m_curTranslation);
    settings.setValue("showMenu", m_showMenu);
    settings.setValue("showSelection", m_showSelection);
    settings.setValue("reciteBasmala", m_reciteBasmala);
    settings.setValue("fullAnimEnable", m_fullAnimEnable);
    //   settings.setValue("bgrFullScreen", m_fullScreenBgr);
    settings.setValue("fullAnimated", m_fullAnimated);
    //settings.setValue("fullIndex", m_fullIndex);
    settings.setValue("curentRiwaya", m_curentRiwaya);
    settings.setValue("locale", m_locale);
    settings.setValue("standardTool", m_standardTool);
    settings.setValue("saveMediaLoaded", m_saveMediaLoaded);
     settings.setValue("fullbackgroundDir", m_fullbackgroundDir);

    settings.endGroup();

    settings.beginGroup("Shortcut");

    settings.setValue("actionOptions", listShortcut.at(0));
    settings.setValue("actionNavigation", listShortcut.at(1));
    settings.setValue("actionRepeatOption", listShortcut.at(2));
    settings.setValue("toolBarAodioEffect", listShortcut.at(3));
    settings.setValue("actTansTefsir", listShortcut.at(4));
    settings.setValue("actionNextPage", listShortcut.at(5));
    settings.setValue("actionPrevPage", listShortcut.at(6));
    settings.setValue("actionNextSura", listShortcut.at(7));
    settings.setValue("actionPrevSura", listShortcut.at(8));
    settings.setValue("actionNextAya", listShortcut.at(9));
    settings.setValue("actionPrevAya", listShortcut.at(10));
    settings.setValue("actionMemoriz", listShortcut.at(11));
    settings.setValue("actionPlayPause", listShortcut.at(12));
    settings.setValue("actionStopMedia", listShortcut.at(13));
    settings.setValue("actionFullScreen", listShortcut.at(14));


    settings.endGroup();
}
void MainWindow::stupActionsShortcuts()
{
    ui->actionOptions->setShortcut(QKeySequence(listShortcut.at(0)));
    ui->actionNavigation->setShortcut(QKeySequence(listShortcut.at(1)));
    ui->actionRepeatOption->setShortcut(QKeySequence(listShortcut.at(2)));
    //   ui->toolBarAodioEffect->toggleViewAction()->setShortcut(QKeySequence(listShortcut.at(3)));
    actTansTefsir->setShortcut(QKeySequence(listShortcut.at(4)));
    ui->actionNextPage->setShortcut(QKeySequence(listShortcut.at(5)));
    ui->actionPrevPage->setShortcut(QKeySequence(listShortcut.at(6)));
    ui->actionNextSura->setShortcut(QKeySequence(listShortcut.at(7)));
    ui->actionPrevSura->setShortcut(QKeySequence(listShortcut.at(8)));
    ui->actionNextAya->setShortcut(QKeySequence(listShortcut.at(9)));
    ui->actionPrevAya->setShortcut(QKeySequence(listShortcut.at(10)));
    ui->actionMemoriz->setShortcut(QKeySequence(listShortcut.at(11)));
    mPlayer->setPlayPauseShortcut(QKeySequence(listShortcut.at(12)));
    ui->actionStopMedia->setShortcut(QKeySequence(listShortcut.at(13)));
    ui->actionFullScreen->setShortcut(QKeySequence(listShortcut.at(14)));

}
//end-------------save and load settings--------------------------

//begen----------systry--------------------------------------------------
void MainWindow::createTrayIcon()
{
    actionMinimiz=new QAction(trUtf8("&Minimize"),this);
    actionRestore=new QAction(trUtf8("&Restore"),this);
    connect(actionRestore, SIGNAL(triggered()), this, SLOT(showNormal()));
    connect(actionMinimiz, SIGNAL(triggered()), this, SLOT(hide()));
    actionSowInfo=new QAction(trUtf8("&Show info"),this);
    actionSowInfo->setCheckable(true);
    actionSowInfo->setChecked(m_showInfo);
    connect(actionSowInfo, SIGNAL(toggled(bool)), this, SLOT(setshowInfo(bool)));
    QMenu *trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(ui->actionPlayPause);
    trayIconMenu->addAction(ui->actionStopMedia);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(actionSowInfo);
    trayIconMenu->addAction(actionMinimiz);
    trayIconMenu->addAction(actionRestore);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(ui->actionQuit);

    trayIcon = new QSystemTrayIcon(this);
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    trayIcon->setIcon(QIcon(":/img/elforkane.png"));
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setVisible(m_minimizToTry);
}

void MainWindow::setshowInfo(bool show)
{
    m_showInfo=show;
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        if(this->isHidden()){
            this->showNormal();
        }else{
            this->hide();
        }


        break;
    case QSystemTrayIcon::DoubleClick:

        break;
    case QSystemTrayIcon::MiddleClick:
        showMessage();
        break;
    default:
        ;
    }
}

void MainWindow::showMessage()
{

    if(!this->isHidden())
        return;
    if(m_showInfo==false)
        return;

    QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);
    QString txtTrans="";
    if(m_showPopup==true)
        txtTrans=sceenbase->textEdit->toPlainText();
    trayIcon->showMessage(trUtf8("Sura :")+comboSura->currentText(), trUtf8(" Aya :")
                          +QString::number(m_aya)+trUtf8(" Hizb :")+QString::number(m_hizb)+"\n"+txtTrans, icon,
                          m_infoDely * 1000);
}
//end----------systry--------------------------------------------------



//التحقق من مسارات الصور للسمة ان كانت موجودة
void MainWindow::locateThemePath()
{

    QString imgPath=m_appPath+"/themes/"+m_themeFolder;

    QFile file;
    if (!file.exists(imgPath+"/top.png") || !file.exists(imgPath+"/top_right.png")||!file.exists(imgPath+"/left.png")||
            !file.exists(imgPath+"/right.png")||!file.exists(imgPath+"/bot.png")||!file.exists(imgPath+"/bot_right.png")||
            !file.exists(imgPath+"/top_left.png")||!file.exists(imgPath+"/bot_left.png"))  {

        m_themeFolder="default";
        imgPath=":/images/image";
    }

}


//الانتقال الى الموضع المحدد
//! [1]
void MainWindow::setCurentPos(int pos)
{
    if (pos>6236||pos<1)//اذا كان الموضع اقل من 1 او اكبر من عدد الايات
        return;
    m_id=pos;
    int    ayaY=40;
    //جلب بيانات الموضع الحالي والذي يسبقه
    QString txtPrev=    database->myList->at(pos-1);
    QString txt=    database->myList->at(pos);

    //تقسيم النص لجلب البيانات
    m_id=txt.section(",",0,0).trimmed().toInt();
    int surat=txt.section(",",1,1).trimmed().toInt();
    m_aya=txt.section(",",2,2).trimmed().toInt();
    QString safha=txt.section(",",3,3).trimmed();
    QString xCurent=txt.section(",",4,4).trimmed();
    ayaY=txt.section(",",5,5).trimmed().toInt();
    m_jozaa=txt.section(",",6,6).trimmed().toInt();
    m_hizb=txt.section(",",7,7).trimmed().toInt();
    m_robaa=txt.section(",",8,8).trimmed().toInt();

    QString aya="000"+QString::number(m_aya);
    QString sura="000"+QString::number(surat);;
    m_soundName=sura.right(3)+aya.right(3) ;
    //   معرفة احداثيات س و ع السابقة
    QString xPrev=txtPrev.section(",",4,4).trimmed();
    QString sFirst=txtPrev.section(",",3,3).trimmed();
    QString yFirst=txtPrev.section(",",5,5).trimmed();

    //اذا تغيرت الصفحة وكان اعداد تكرار الصفحة مفعل سيجلب اول اية واخرها في الصفحة
    if (m_curentSafha!=safha.toInt()){
        m_curentSafha=safha.toInt();

        if(m_autoRepeatPage==true)
            chargeLastAndFirstAya();
    }

    //اذا تغيرت السورة وكان خيار تكرار السورة سجلب بيان اول واخر اية في السورة
    if(m_sura!=surat){
        m_sura=surat;
        if(m_autoRepeatSura==true)
            chargeLastAndFirstAya();
    }

    int d=(safha.toInt());
    int i=fmod(d,2);
    if (i==1){//اذا كانت الصفحة تحمل رقما فرديا يتم رسم نافذة التفاسير على اليمين
        m_px=457;
    }else{
        m_px=0;
    }

    sceenbase->setCurentPages( safha.toInt(),ayaY,isTefsirPopup);
    //اذا كانت الصفحة المطلوبة لا تساوي الحالية ستكون ع =60لانها صفحة جديدة
    if(sFirst!=safha){
        yFirst="60";
        xPrev="430";
    }
    int high=ayaY-yFirst.toInt();
    int top=ayaY-high;


    if(m_showPopup==true)//اذا كان عرض التفاسير والتراجم مفعل
        convertTextToHtm(database->getTranslation(m_id));
    //نقل التحديد الى الموضع الجديد
    //  qDebug()<<"her pos to mediaplay";

    moveSelection(top-20,high+40,xCurent.toInt()-8,xPrev.toInt()-8);

    //تحديد الموضع الحالي في الفهرسة
    QVariant dd=m_id;
    QTreeWidgetItem *item=new QTreeWidgetItem;
    QList<QTreeWidgetItem *> found =ui->treeWidgetIndex->findItems( dd.toString(),Qt::MatchExactly | Qt::MatchRecursive,1);
    foreach (item, found){
        ui-> treeWidgetIndex->setCurrentItem(item);
    }
    //-----------تحديث بيانات الادوات
    comboSura->setCurrentIndex(m_sura-1);
    spinAya->setValue(m_aya);
    spinJozaa->setValue(m_jozaa);
    spinHizb->setValue(m_hizb);
    spinSafha->setValue(m_curentSafha);

    //if(showtoolbaredia==true)
    QLocale lc(this->locale().name());
    //p.drawText(rectangle, Qt::AlignCenter,lc.toString(num.toInt()));
    actMediaSafha->setText(trUtf8("P : ")+lc.toString(m_curentSafha));
    actMediaSura->setText(comboSura->currentText());
    actMediaAya->setText(trUtf8("A : ","aya")+lc.toString(m_aya));
    actMediaJozaa->setText(trUtf8("J : ","jozaa")+lc.toString(m_jozaa));
    actMediaHizb->setText(trUtf8("H : ","hizb")+lc.toString(m_hizb));
    actMediaReciter->setText(comboBoxReciter->currentText());

    qDebug()<<QString("-------------- Pos %1-------------").arg(QString::number(m_id));

    qDebug()<<trUtf8("Sound Path")+" : " +(m_soundPath)+"/"+m_soundName;
    qDebug()<<trUtf8("Sound Url")+" : "+(m_soundUrl)+"/"+m_soundName+".mp3";
    qDebug()<<trUtf8("Curent Media")+" : "+mPlayer->curentMedia();

    qDebug()<<trUtf8("Sura")+" : "+QString::number(m_sura)
           <<  trUtf8("Jozaa")+" : " +QString::number(m_jozaa)
            << trUtf8("Hizb")+" : "+QString::number(m_hizb)
            <<trUtf8("Robaa")+" : "+QString::number(m_robaa)
           <<trUtf8("Page")+" : "+QString::number(m_curentSafha)
          <<trUtf8("Aya")+" : "+QString::number(m_aya);
    qDebug()<<item->text(0);
    showMessage();//عرض التنبيه قرب الساعة اذا كان محدد


}
//! [2]
void MainWindow::moveSelection(int top,int hight,int x1,int x2)
{

    if(this->isFullScreen()){
        if(mSceenFull)
            fullScreenPixmap(top,hight,x1,x2);
    }

    //اعادة رسم التحديد
    sceenbase->setMoveSelection( top, hight, x1, x2,m_px);
    if(m_autoRepeatOne==false){     //اذا كان وضع القراءة وتم تحريك التحديد

        // if(mPlayer->isPlaying())
        mediaPlay();

    }
}

//! [2]
void MainWindow::fullScreenPixmap(int top,int high,int x1,int x2)
{

    QPixmap pix(m_appPath+"/images/"+m_curentRiwaya+"/"+QString::number(m_curentSafha)+".png");//الصفحة التي يتم الرسم منها
    QPainter p;//الطابعة
    QString textTrans="";
    if(m_showPopup==true)//اذا كانت نافذة التفاسير ظاهرة سيجلب  النص
        textTrans=sceenbase->textEdit->toPlainText();
    //qDebug()<<"m_showPopup: "<<m_showPopup;
    if(m_curentSafha==1||m_curentSafha==2){     //اذا كانت الصفحة الاولى او الثانية سيعيد الصفحة بكاملها

        QPixmap pixdest(382,468);
        pixdest.fill(Qt::white);
        QRect rect(69,144,320,468);
        QRect rectDest(31,0,320,468);
        p.begin(&pixdest);
        p.drawPixmap(rectDest,pix,rect);//رسم مربع الاية
        p.end();
        if(mSceenFull){
        mSceenFull->setPixmapAya(pixdest);//اعادة الرسم الى مشهد ملء الشاشة
        QLocale lc(this->locale().name());

        mSceenFull->setInfo(trUtf8("Sura : ")+comboSura->currentText(),
                                    trUtf8("   Jozaa : ")+lc.toString(m_jozaa),
                                    trUtf8("   Hizb : ")+lc.toString(m_hizb),
                                    trUtf8("   Robaa : ")+lc.toString(m_robaa),
                                    trUtf8("   Aya : ")+lc.toString(m_aya),
                                    trUtf8("     El Chiekh : ")+comboBoxReciter->currentText(),
                                    textTrans);
        }
        return;//ليس بحاجة الى الباقي
    }

    QRect rectselect(37, top,382,high);//المربع المحدد للاية

    QPixmap pixAyaSource(382,high);//الاطار الذي يتم ارسم الاية عليه
    pixAyaSource.fill(Qt::transparent);//جعل اطار الاية شفافا
    p.begin(&pixAyaSource);//بداية الرسم
    p.drawPixmap(pixAyaSource.rect(),pix,rectselect);//رسم مربع الاية
    p.end();//نهاية رسم مربع الاية
    //  if(x2<60)x2=1;

    int top1=0,top2=40, hight=high, bot=80;

    if(x2<60)
        top1=-40,top2=0,hight=high-40,bot=40;


    QPixmap pixFull(382,hight);//الصورة التي تعاد الى مشهد ملأ الشاشة
    pixFull.fill(Qt::white);//جعل اطار الاية شفاف

    p.begin(&pixFull);
    if (high<=45){                          //اذا كانت الاية تتكون من سطر واحد
        int w=(382-(x2-x1))/2;
        QRect rectSource(x1-40,0,x2-x1,40);
        QRect rectDeste(w,0,x2-x1,40);

        p.drawPixmap(rectDeste,pixAyaSource,rectSource);//رسم السطر الاول
    }else if(high<=85){               //اذا كانت الاية تتكون من سطر ين

        //1سطر

        int w=(382-(x2-40))/2;
        QRect rectSource(0,0,x2-40,40);
        QRect rectDeste(w,top1,x2-40,40);
        p.drawPixmap(rectDeste,pixAyaSource,rectSource);//رسم السطر الاول
        //2سطر
        int w2=(382/2)-((382-x1+40)/2);
        QRect rectSource2(x1-40,40,382-x1+40,40);
        QRect rectDeste2(w2,top2,382-x1+40,40);
        p.drawPixmap(rectDeste2,pixAyaSource,rectSource2);
    }else{                                     //اذا كانت الاية تتكون من 3 اسطر

        //1سطر
        int w=(382-(x2-40))/2;

        QRect rectSource(0,0,x2-40,40);
        QRect rectDeste(w,top1,x2-40,40);
        p.drawPixmap(rectDeste,pixAyaSource,rectSource);//رسم السطر الاول
        //2سطر
        QRect rectSource2(0,40,382,high-80);
        QRect rectDeste2(4,top2,382,hight-bot);
        p.drawPixmap(rectDeste2,pixAyaSource,rectSource2);
        //3سطر
        int w2=(382/2)-((382-x1+40)/2);
        QRect rectSource3(x1-40,high-40,382-x1+40,40);
        QRect rectDeste3(w2,hight-40,382-x1+40,40);
        p.drawPixmap(rectDeste3,pixAyaSource,rectSource3);
    }
    //رسم مربع على الصورة
    p.setPen(QColor(164,164,164));
    QRectF rectangle(0.0, 0.0, 381.0, hight-1);
    p.drawRect(rectangle);
    p.end();
     if (mSceenFull){
    mSceenFull->setPixmapAya(pixFull);//اعادة الرسم الى مشهد ملء الشاشة
    QLocale lc(this->locale().name());
    mSceenFull->setInfo(trUtf8("Sura : ")+comboSura->currentText(),
                                trUtf8("   Jozaa : ")+lc.toString(m_jozaa),
                                trUtf8("   Hizb : ")+lc.toString(m_hizb),
                                trUtf8("   Robaa : ")+lc.toString(m_robaa),
                                trUtf8("   Aya : ")+lc.toString(m_aya),
                                trUtf8("     El Chiekh : ")+comboBoxReciter->currentText(),
                                textTrans);//اغادة البيانات الى المشهد

     }
}
//begin-------------------------go page and pos--------------------
void MainWindow::goSura(int index)
{


    // i/nt idx=comboSura->currentIndex();
    QVariant txt=comboSura->itemData(index);

    QString pos=txt.toString().section(",",0,0);

    setCurentPos(pos.toInt());
}

void MainWindow::goAya()
{
    int idx=comboSura->currentIndex();
    QVariant txt=comboSura->itemData(idx);
    QString pos=txt.toString().section(",",0,0);
    setCurentPos(pos.toInt()+spinAya->value()-1);
}

void MainWindow::goJozaa()
{
    if(spinJozaa->value()==m_jozaa)
        return;

    if( database->myListJozaa->count()>0){
        int idx=  database->myListJozaa->at(spinJozaa->value()-1);
        setCurentPos(idx);
    }
}

void MainWindow::goHizb()
{
    if(spinHizb->value()==m_hizb)
        return;

    if( database->myListJozaa->count()>0){
        int idx=  database->myListHizb->at(spinHizb->value()-1);
        setCurentPos(idx);
    }
}

void MainWindow::goPage()
{
    if(spinSafha->value()==m_curentSafha)
        return;

    QString mtxt=sceenbase->myListSafhat.at(spinSafha->value());
    int id=mtxt.section(",",0,0).trimmed().toInt();
    setCurentPos(id);
}

void MainWindow::setPage(int page)
{
    if(page==m_curentSafha)
        return;

    QString mtxt=sceenbase->myListSafhat.at(page);
    int id=mtxt.section(",",0,0).trimmed().toInt();
    setCurentPos(id);
}

void MainWindow::setSora(int sora)
{
    if(sora>114||sora <1){
        return ;
    }
    int i=database->myListSura->at(sora-1);
    setCurentPos(i);

}

void MainWindow::setJozaa(int jozaa)
{
    if (jozaa>30||jozaa<1){
        return ;
    }
    int i=database->myListJozaa->at(jozaa-1);
    setCurentPos(i);

}

void MainWindow::setHizb(int hizb)
{
    if (hizb>60||hizb<1){
        return ;
    }
    int i=database->myListHizb->at(hizb-1);
    setCurentPos(i);

}

void MainWindow::setAya(int sora,int aya)
{
    if(sora>114||sora <1){
        return ;
    }
    int i=database->myListSura->at(sora-1);
    QVariant txt=comboSura->itemData(sora-1);
    QString max=txt.toString().section(",",1,1);
    if(aya>max.toInt()||aya <1){
        setCurentPos(i);
        return ;
    }
    setCurentPos(i+aya-1);

}

//end-------------------------go page and pos--------------------

void MainWindow::setSpinAyaMaximum(int index)
{

    QVariant txt=comboSura->itemData(index);

    QString i =txt.toString().section(",",1,1);
    spinAya->setMaximum(i.toInt());
    spinAya->setMinimum(1);

}


void MainWindow::chargeLastAndFirstAya()
{
    if(m_autoRepeatPage==true){
        QString  txt=   sceenbase->myListSafhat.at(m_curentSafha);
        int i=  txt.count("|");
        m_repeatAyaFirst=txt.section(",",0,0).trimmed().toInt();
        QString lastTxt=txt.section("|",i,i).trimmed();
        m_repeatAyaLast=lastTxt.section(",",0,0).trimmed().toInt();

    }else if (m_autoRepeatSura==true){
        int sura=m_sura-1;
        m_repeatAyaFirst=database-> myListSura->at(sura);
        m_repeatAyaLast=database-> myListSura->at(sura+1)-1;
        if (m_repeatAyaLast==-1)
            m_repeatAyaLast=6236;
    }

}


///------------------------------Actions---------------------------------------------
void MainWindow::on_actionNextPage_triggered()
{
    if (m_curentSafha==604)
        return;
    QString mtxt=sceenbase->myListSafhat.at(m_curentSafha+1);
    int id=mtxt.section(",",0,0).trimmed().toInt();
    setCurentPos(id);
}

void MainWindow::on_actionPrevPage_triggered()
{
    if (m_curentSafha==1)
        return;
    QString mtxt=sceenbase->myListSafhat.at(m_curentSafha-1);
    int id=mtxt.section(",",0,0).trimmed().toInt();
    setCurentPos(id);
}

void MainWindow::on_actionNextSura_triggered()
{
    if(m_sura==114)
        return;
    int i=database->myListSura->at(m_sura);
    setCurentPos(i);
}

void MainWindow::on_actionPrevSura_triggered()
{
    if(m_sura==1)
        return;
    int i=database->myListSura->at(m_sura-2);
    setCurentPos(i);
}

void MainWindow::on_actionNextAya_triggered()
{
    if (m_id==6236)
        return;
    setCurentPos(m_id+1);
}

void MainWindow::on_actionPrevAya_triggered()
{
    if (m_id==1)
        return;
    setCurentPos(m_id-1);
}

void MainWindow::on_actionOptions_triggered()
{
    getOption(0,trUtf8("General Options"));
}

void MainWindow::on_actionRepeatOption_triggered()
{
    getOption(1,trUtf8("Repeat Options"));
}

void MainWindow::on_actionNavigation_toggled(bool arg1)
{
    ui->dockWidget->setVisible(arg1);
}


void MainWindow::comboBoxSoraJozaa_currentIndexChanged(int index)
{
    if (index==0){
        database-> treeChargeSoura(ui->treeWidgetIndex,true,comboSura,m_layouDir,m_sura-1);
    }else{

        database-> treeChargeJozaa(ui->treeWidgetIndex);
    }
}

void MainWindow::treeWidgetIndex_itemActivated(QTreeWidgetItem *item, int )
{
    int id =item->text(1).toInt();

    setCurentPos(id);
}


//bigen-----------التفاسير و التراجم------------
void MainWindow::popup_toggled(bool checked)
{
    m_showPopup=checked;
    emit popupVisible(checked);
    sceenbase->setPopupVisible(checked);
    convertTextToHtm(database->getTranslation(m_id));
}

void MainWindow::menuTefsirAndTranslation()
{
    QMenu menu(this);
    menu.addMenu(ui->menuTranslation);
    menu.addMenu(ui->menuTefsir);

    menu.addAction(ui->actionQuranText);
    menu.exec(QCursor::pos());
}

void MainWindow::translationChanged()
{

    QAction *action = qobject_cast<QAction *>(sender());
    if (action){
        QVariant data=action->data();
        QString txt=action->text();
        database->openDb(m_appPath+"/translat/"+data.toString());
        convertTextToHtm(database->getTranslation(m_id));
        labelTransTefsir->setText(txt);
        m_showPopup=true;
        emit popupVisible(true);
        isTefsirPopup=false;
        //    panelPopup->setVisible(true);

        m_curTranslation=myListActionTrans.indexOf(action);

    }
}

void MainWindow:: tefsirChanged()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (action){
        QVariant data=action->data();
        QString txt=action->text();
        database->openDb(m_appPath+"/tafasir/"+data.toString());
        convertTextToHtm(database->getTranslation(m_id));
        labelTransTefsir->setText(txt);
        m_showPopup=true;
        emit popupVisible(true);
        isTefsirPopup=true;
        //    panelPopup->setVisible(true);

    }
}

void MainWindow::txtQuran()
{
    database->openDb(m_appPath+"/quran.db");
    convertTextToHtm(database->getTranslation(m_id));
    labelTransTefsir->setText(trUtf8("Quran txt"));
    m_showPopup=true;
    emit popupVisible(true);
    isTefsirPopup=false;
    //   panelPopup->setVisible(true);

}

void MainWindow::on_actionQuranText_triggered()
{
    txtQuran();
}

void MainWindow::hidePopup()
{
    actTansTefsir->setChecked(false);
    emit popupVisible(false);
}

void MainWindow::convertTextToHtm(QString text)
{
    text=text.replace("\\r\\n","");
    QString aya=QString::number(m_aya)+ " - ";
    QString textTrans=QString("< font color='red' >%1</font>< font color='blue' >%2</font> ").arg(aya).arg(text);
    // textEdit->setHtml(textTrans);
    sceenbase->textEdit->setHtml(textTrans);
    QLocale lc(this->locale().name());
    if(mSceenFull){
        QString translatTxt="";
        if(m_showPopup==true)//اذا كانت نافذة التفاسير ظاهرة سيجلب  النص
            translatTxt= sceenbase->textEdit->toPlainText();
        if(m_fullAnimated==true&&this->isFullScreen()){

                  mSceenFull->setInfo(trUtf8("Sura : ")+comboSura->currentText(),
                                        trUtf8("   Jozaa : ")+lc.toString(m_jozaa),
                                        trUtf8("   Hizb : ")+lc.toString(m_hizb),
                                        trUtf8("   Robaa : ")+lc.toString(m_robaa),
                                        trUtf8("   Aya : ")+lc.toString(m_aya),
                                        trUtf8("     El Chiekh : ")+comboBoxReciter->currentText(),
                                        translatTxt);
        }

    }
}

//end-----------التفاسير و التراجم------------

//begin------------------reciter-----------------------------------------
void MainWindow::comboBoxResiter_activated(int index)
{
    m_receter=index;
    QString txt=comboBoxReciter-> itemData(index).toString();
    m_soundPath=txt.section("|",0,0);
    m_soundUrl=txt.section("|",1,1);
    m_curentRiwaya=txt.section("|",2,2);
    QDir dir;
    if(!dir.exists(m_appPath+"/images/"+m_curentRiwaya)||m_curentRiwaya.isEmpty()){
        m_curentRiwaya="default";

    }
    if(!dir.exists(m_appPath+"/images/"+m_curentRiwaya)||m_curentRiwaya.isEmpty())
        m_curentRiwaya="default";
    database-> chargeCsvs(m_curentRiwaya);
    sceenbase->setRewayat(m_curentRiwaya);
    sceenbase->updatePages();
}

void MainWindow::on_actionAddReceter_triggered()
{
    DialogAddReciter *dlg=new DialogAddReciter(this);

    dlg->setDownload(false);

    dlg->setWindowTitle(trUtf8("Add Receter"));
    if (dlg->exec() == QDialog::Accepted){
        comboBoxReciter->addItem(dlg->getReciterName(),dlg->getDataName());

    }

}

void MainWindow::editReciter()
{
    int index=comboBoxReciter->currentIndex();
    DialogAddReciter *dlg=new DialogAddReciter(this);
    dlg->setWindowTitle(trUtf8("Edit Receter"));
    dlg->setReceterName(comboBoxReciter->currentText());
    dlg->setDirName(m_soundPath);
    dlg->setUrlName(m_soundUrl);
    //  int index=comboBoxReciter->currentIndex();
    QString data=comboBoxReciter->itemData(index).toString();
    dlg->setRiwayaName(data.section("|",2,2));

    QStringList listItem;
    for(int i=0;i<comboSura->count();i++)
    {
        QString txt=comboSura->itemText(i);
        QString data=comboSura->itemData(i).toString();
        listItem<<txt+","+data;
    }
    dlg->setListItems(listItem);

    if (dlg->exec() == QDialog::Accepted){
        comboBoxReciter->setItemText(index,dlg->getReciterName());
        comboBoxReciter->setItemData(index,dlg->getDataName());
        QString dataStr=dlg->getDataName();
        m_soundPath=dataStr.section("|",0,0);
        m_soundUrl=dataStr.section("|",1,1);
        m_curentRiwaya=dataStr.section("|",2,2);
        QDir dir;
        if(!dir.exists(m_appPath+"/images/"+m_curentRiwaya)||m_curentRiwaya.isEmpty())
            m_curentRiwaya="default";
        database-> chargeCsvs(m_curentRiwaya);
        sceenbase->setRewayat(m_curentRiwaya);
        sceenbase->updatePages();

    }
}

void MainWindow::on_actionEditeReceter_triggered()
{
    editReciter();
}

void MainWindow::on_actionRemoveReceter_triggered()
{
    QMessageBox msgBox;
    //msgBox.setText("The document has been modified.");
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setText(QString(trUtf8("Do you want to delete %1 ?")).arg(comboBoxReciter->currentText()));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No );
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Yes:
        comboBoxReciter->removeItem(comboBoxReciter->currentIndex());
        break;
    case QMessageBox::No:

        break;

    default:

        break;
    }

}

//end------------------reciter-----------------------------------------
void MainWindow::on_graphicsView_customContextMenuRequested(const QPoint )
{
    QMenu menu(this);
    menu.addAction(ui->actionFullScreen);
    menu.addAction(ui->actionEnableAnimFull);
    menu.addSeparator();
    menu.addMenu(ui->menu_edit);
    menu.addMenu(ui->menuTranslation);
    menu.addSeparator();
    menu.addAction(ui->actionQuit);
    menu.exec(QCursor::pos());
}

void MainWindow::getOption(int tab,QString title)
{




    DialogOption *dlg=new DialogOption(this);

    dlg->setAppPath(m_appPath);
    //repeat settings
    dlg->setAutoPlayNext(m_autoPlayNext);
    dlg->setAutoRepeatOne(m_autoRepeatOne);
    dlg->setAutoRepeatPage(m_autoRepeatPage);
    dlg->setautoRepeatSura(m_autoRepeatSura);
    dlg->setAutoRepeatFromTo(m_autoRepeatFromTo);
    dlg->setNumberRepeats(m_repeatNumber);
    dlg->setRepeatNumber(m_isRepeatNumber);

    dlg->setShowMediaControl(m_showMediaControl);
    dlg->setAnimEnabled(m_animEnabled);
    dlg->setFitInView(m_fitInView);
    dlg->setMinimizToTry(m_minimizToTry);
    dlg->setTextInIcons(m_textIcon);
    dlg->setCadrFolder(m_themeFolder);
    dlg->setLng(m_lng);
    dlg->setInfoDely(m_infoDely);
    dlg->setSpinMax(spinAya->maximum());
    dlg->setSelectColor(m_selectColor);
    dlg->setShowMenu(m_showMenu);
    dlg->setShowSelection(m_showSelection);
    dlg->setshowStandardTool(m_standardTool);
    dlg ->setReciteBasmala(m_reciteBasmala);
    dlg->setFullSceenAnimated(m_fullAnimated);
    dlg->setfullbackgroundDir(m_fullbackgroundDir);
    dlg->setCurTab(tab);
    dlg->setWindowTitle(title);
    //dlg->setListFullSceen(listSceenName,m_fullIndex);
    //dlg->listSceen=myListSceen;
    dlg->setShortcutsList(listShortcut);
//    dlg->setSaveMediaLoaded(m_saveMediaLoaded);
    //dlg->chargeSettings();
    //dlg->setRiwayat(listRiwayatText,listRiwayatData,m_curentRiwaya);
    dlg->setCurentLocale(m_locale);
    if (dlg->exec() == QDialog::Accepted){
        m_themeFolder=dlg->getCadrFolder();
        m_animEnabled=dlg->getAnimEnabled();
        m_fitInView=dlg->getFitInView();
        m_minimizToTry=dlg->getMinimizToTry();
        m_textIcon=dlg->getTextInIcons();
        m_infoDely=dlg->getInfoDely();
        m_lng=dlg->getLng();
        m_selectColor=dlg->getSelectColor();
        m_showMediaControl=dlg->getShowMediaControl();
        m_autoRepeatFromTo=dlg->getAutoRepeatFromTo();
        m_autoRepeatOne=dlg->getAutoRepeatOne();
        m_autoRepeatPage=dlg->getAutoRepeatPage();
        m_autoRepeatSura=dlg->getautoRepeatSura();
        m_autoPlayNext=dlg->getAutoPlayNext();
        m_repeatNumber=dlg->getNumberRepeats();
        m_isRepeatNumber=dlg->getRepeatNumber();
        m_showMenu=dlg->getShowMenu();
        m_standardTool=dlg->getshowStandardTool();
        m_showSelection=dlg->getShowSelection();
        m_saveMediaLoaded=false;
        sceenbase->setShowSelection(dlg->getShowSelection());
        m_reciteBasmala=dlg->getReciteBasmala();
        m_fullbackgroundDir=dlg->getfullbackgroundDir();
        ui->menuBar->setVisible(m_showMenu);
        btnMenu->setVisible(!m_showMenu);
        m_restoreDefaults=dlg->restoreDefaults;
        if(m_showMenu==false){
            // ui->toolBar->addWidget(btnMenu);
            ui->toolBar->addWidget(btnMenu);
        }else{
            btnMenu->setParent(this);

        }

        listShortcut=dlg->listShortcuts;
        stupActionsShortcuts();
        m_fullAnimated=dlg->getFullSceenAnimated();
        //m_fullIndex=dlg->getFullIndex();
        //  m_curentRiwaya=dlg->riwayat;
        m_locale=dlg->getCurentLocale();
        // database-> chargeCsvs(m_curentRiwaya);


        //if(m_fullIndex<0)m_fullIndex=0;
//        if(myListSceen.count()>0)
//            sceenFullInterface=myListSceen.at(m_fullIndex);

        locateThemePath();
        sceenbase->setColorSelection(m_selectColor);
        sceenbase->setThemeFolder(m_themeFolder);

        // sceenbase->setRewayat(m_curentRiwaya);
        sceenbase->setAnimationEnabled(m_animEnabled);
        //
        setCurentPos(m_id);
        sceenbase->updatePages();
        this->resize(this->size().width()+1,this->size().height()+1);

        trayIcon->setVisible(m_minimizToTry);
        if(m_textIcon==true){
            ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        }else{
            ui->toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
        }

        if (dlg->getAutoRepeatFromTo()==true){
            int sura=database-> myListSura->at(m_sura-1);
            m_repeatAyaFirst=sura+dlg->getRepeatAyaFirst()-1;
            m_repeatAyaLast=sura+dlg->getRepeatAyaLast()-1;
            m_numPlayed=1;
        }
        chargeLastAndFirstAya();
    }



 saveSetting();

 if(mSceenFull)
     mSceenFull->loadSetting();

}

//
void MainWindow::on_actionAbout_triggered()
{
    DialogAbout *dlg=new DialogAbout(this);
    dlg->exec() ;
}


void MainWindow::on_actionRceterEdite_triggered()
{
    editReciter();
}

//begen------------------------search--------------------------------------------
void MainWindow::on_toolButtonGoSearch_clicked()
{
    if(ui->lineEditSearch->text().isEmpty())
        return;


    int option;
    if(ui->radioButtonSearch->isChecked())
        option=0;
    if(ui->radioButtonSearchFirst->isChecked())
        option=1;
    if(ui->radioButtonSearchLast->isChecked())
        option=2;
    if(ui->radioButtonAdvensed->isChecked())
        option=3;
    if (option==3&&ui->lineEditSearchAnd->text().isEmpty())
        return;
    QString orAnd;
    if(ui->checkBoxAnd->isChecked()==true){
        orAnd="and";
    }else if(ui->checkBoxOr->isChecked()==true){
        orAnd="or";
    }
    database->dataSearchString(ui->treeWidgetSearch,
                               ui->lineEditSearch->text(),
                               ui->lineEditSearchAnd->text(),
                               orAnd,
                               option);
}

void MainWindow::on_lineEditSearch_returnPressed()
{
    on_toolButtonGoSearch_clicked();
}

void MainWindow::on_lineEditSearchAnd_returnPressed()
{
    on_toolButtonGoSearch_clicked();
}

void MainWindow::on_treeWidgetSearch_itemActivated(QTreeWidgetItem *item, int )
{
    int id =item->text(3).toInt();
    setCurentPos(id);
}


void MainWindow::lineEditSearchTree_textChanged(const QString &arg1)
{
    if(arg1==trUtf8("Search"))
        return;
    database->searchInTreeview(ui->treeWidgetIndex,arg1,0,ui->checkBoxHamza->isChecked());
}

//end------------------------search--------------------------------------------

//begin----------------------------fullscreen------------------------------------------
//void MainWindow::loadPlugin()
//{
//    QDir pluginsDir(qApp->applicationDirPath());
//#if defined(Q_OS_WIN)

//    pluginsDir.cdUp();
//#elif defined(Q_OS_MAC)
//    if (pluginsDir.dirName() == "MacOS") {
//        pluginsDir.cdUp();
//        pluginsDir.cdUp();
//        pluginsDir.cdUp();
//    }
//#else
//    pluginsDir.cdUp();

//#endif
//    if(QFile::exists(m_appPath+"/plugins")){
//        pluginsDir.cd(m_appPath+"/plugins");
//    }else  if(QFile::exists(pluginsDir.path()+"/lib/elforkane/plugins")){
//        pluginsDir.cd("lib/elforkane/plugins");
//    }else if(QFile::exists(pluginsDir.path()+"/lib64/elforkane/plugins")){
//        pluginsDir.cd("lib64/elforkane/plugins");
//    }
//    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
//        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
//        QObject *plugin = pluginLoader.instance();

//        if (plugin) {
//            sceenFullInterface    = qobject_cast<SceenFullInterface *>(plugin);
//            if (sceenFullInterface){
//                myListSceen.append(qobject_cast<SceenFullInterface *>(plugin));
//                listSceenName.append(plugin->objectName());

//            }
//        }
//    }
//    int count=myListSceen.count();
//    if(count<1||m_fullIndex<0||m_fullIndex>count-1){
//        m_fullAnimated=false;
//        m_fullIndex=0;
//    }else{
//        sceenFullInterface=myListSceen.at(m_fullIndex);
//    }
//}

void MainWindow::toggleFullScreen()
{
//    if(m_fullIndex<0||m_fullIndex>myListSceen.count()-1)
//        m_fullAnimated=false;

    if(this->isFullScreen()){
        timerScreen->stop();
        ui->toolBar->setVisible(m_standardTool);
        ui->menuBar->setVisible(m_showMenu);

        this->showNormal();
        ui->graphicsView->setContextMenuPolicy(Qt::NoContextMenu);
        ui->graphicsView->setScene(sceenbase);
        ui->graphicsView->setSceneRect(QRectF(0.0,0.0,912.0,672.0));
        ui->graphicsView->updateSceneRect(QRectF(0.0,0.0,912.0,672.0));
        //        if(myListSceen.count()>0)
        //        sceenFullInterface->setAnimationEnabled(false);


    }else{
        oldCurPos=this->cursor().pos().x();


        timerScreen->start(30000);
        int w=QApplication::desktop()->geometry().width();
        int h=QApplication::desktop()->geometry().height();
 ui->menuBar->setVisible(false);
        if(m_fullAnimated==false){

            ui->graphicsView->setSceneRect(QRectF(0.0,0.0,912.0,672.0));
            ui->graphicsView->updateSceneRect(QRectF(0.0,0.0,912.0,672.0));
            ui->graphicsView->setScene(sceenbase);
            this->showFullScreen();

        }else  {
            ui->toolBar->setVisible(false);

            this->showFullScreen();
            ui->graphicsView->setSceneRect(QRectF(0.0,0.0,w,h));
            ui->graphicsView->updateSceneRect(QRectF(0.0,0.0,w,h));
            //     ui->graphicsView->setScene(scenfull);
            ui->graphicsView->setContextMenuPolicy(Qt::CustomContextMenu);
            //     scenfull->setBackgroundDir(m_fullScreenBgr);
            setCurentPos(m_id);
//            if(myListSceen.count()>0){
               if (!mSceenFull)
                  mSceenFull=new SceenFull;
//                sceenFullInterface->setGraphicSceen(ui->graphicsView);

//                sceenFullInterface->setAnimationEnabled(m_fullAnimEnable);

                mSceenFull->setGraphicSceen(ui->graphicsView);
                mSceenFull->setAnimationEnabled(m_fullAnimEnable);
//            }
        }

    }

}

void MainWindow::on_actionFullScreen_triggered()
{
    toggleFullScreen();
}

void MainWindow::on_actionEnableAnimFull_toggled(bool arg1)
{
    m_fullAnimEnable=arg1;
    if(this->isFullScreen())
        if(mSceenFull)
        mSceenFull->setAnimationEnabled(arg1);


}
//end----------------------------fullscreen------------------------------------------

//begen-------------------------phonon-----------------------------------------------

//for ayat dir
bool MainWindow::mediaPlayAyat(QString dirPath)
{

//      qDebug()<<"Ayat file path===================== :"+dirPath;
//      qDebug()<<"m_soundPath===================== :"+m_soundPath.section("/",1,1);
//        qDebug()<<"m_soundName===================== :"+m_soundName;

    QString soundN=m_soundPath+"/"+m_soundName+".mp3";

    if(m_soundPath.contains("/"))
        QString soundN=m_soundPath.section("/",1,1)+"/"+m_soundName+".mp3";

        QDirIterator it(dirPath,QDir::Dirs|QDir::NoDotAndDotDot, QDirIterator::Subdirectories);

        while (it.hasNext()) {

             // qDebug()<< it.filePath();

            if(QFile::exists(it.filePath()+"/"+soundN)){
                qDebug()<<"exists" << it.filePath()+"/"+soundN;
                bool mbesmala=false;
                //سيضيف البسملة و الاية
                if (m_aya==1&&m_sura!=9&&m_sura!=1&&m_reciteBasmala==true){
                    mbesmala=true;
                }

                mPlayer->play(QUrl::fromLocalFile(it.filePath()+"/"+soundN),mbesmala);
                return true;
            }

           it.next();


        }

/*
    QDir dir(dirPath);
    QStringList filters(m_soundPath.section("/",1,1)+"*");//فلترة الاية حسب الاسم ولا تهم اللاحقة

    QStringList list=dir.entryList(filters,QDir::AllEntries|QDir::NoDotAndDotDot,QDir::Name);

    if (list.count()==0){
        qDebug()<<"2-media no exist :"+dirPath+"/.../"+m_soundPath+"/"+m_soundName+".mp3";;
        return false;
    }
    for(int i=0;i<list.count();i++){
        QString ss=dirPath+list.at(i)+"/"+m_soundPath+"/"+m_soundName+".mp3";
        // qDebug()<<"Ayat file name :"+ss;
        if(QFile::exists(ss)){
            bool besmala=false;
            //سيضيف البسملة و الاية
            if (m_aya==1&&m_sura!=9&&m_sura!=1&&m_reciteBasmala==true){
                besmala=true;
            }

            mPlayer->play(QUrl::fromLocalFile(ss));
            return true;
        }
    }

    */
    qDebug()<<"2-media no exist :"+dirPath+"/.../"+m_soundPath+"/"+m_soundName+".mp3";;
    return false;
}

bool MainWindow::mediaPlayInLocale(QString dirPath)
{
    //    qDebug()<<"=============mediaPlayInLocale()==================";
    QDir dir(dirPath);
    QStringList filters(m_soundName+"*");//فلترة الاية حسب الاسم ولا تهم اللاحقة
    QStringList list=dir.entryList(filters,QDir::AllEntries|QDir::NoDotAndDotDot,QDir::Name);

    QString curentAya ;
    if (list.count()>0){
        curentAya = list.at(0);
    }else{
        curentAya=m_soundName+".mp3";
    }
    QString fileName=dirPath+"/"+curentAya;

    if(QFile::exists(fileName)){
        bool besmala=false;
        //سيضيف البسملة و الاية
        if (m_aya==1&&m_sura!=9&&m_sura!=1&&m_reciteBasmala==true){
            besmala=true;
        }

        mPlayer->play(QUrl::fromLocalFile(fileName),besmala);
        return true;
    }else{
        qDebug()<<"1-media no exist :"+fileName;
        return false;
    }
}


void MainWindow::mediaPlayInNetwork()
{

    //---------------------القراءة المباشرة في الانترنت
   // if(m_saveMediaLoaded==false){
        QUrl url(m_soundUrl+"/"+m_soundName+".mp3");
        if(url.isValid()){
            bool besmala=false;
            if (m_aya==1&&m_sura!=9&&m_sura!=1&&m_reciteBasmala==true){
                besmala=true;
            }

            mPlayer->play(url,besmala);
            return ;
        }
mPlayer->clearList();
 //   }
 return ;

 //TODO FOX this
    //--------------------التحميل ثم القراءة
    QString destFile;
    if(QFile::exists(m_soundPath)){
        destFile=m_soundPath+"/";
    }else{
        destFile=QDir::homePath()+"/.elforkane/"+m_soundPath+"/";
        if(!QFile::exists(destFile)){
            QDir dir(QDir::homePath()+"/.elforkane/");
            dir.mkpath(destFile);
        }
    }

    QString fileurl(destFile+m_soundName+".mp3");

    //  slider->hide();
    //    if(NetWork->downloadFile(m_soundUrl+"/"+m_soundName+".mp3",destFile)==true){

    //        if(QFile::exists(fileurl)){

    //           mPlayer->play(fileurl);
    //        }else{
    //            mPlayer->stop();
    //        }

    //    }else{
    //        qDebug()<<"3-Download failed: Host  not found. : "<< m_soundUrl+"/"+m_soundName+".mp3";
    //      //  qDebug()<<"this destfile network"<<fileurl;

    //         mPlayer->stop();

    //    }

}


void MainWindow::mediaPlay()
{



    // QStringList filters(m_soundName+"*");//فلترة الاية حسب الاسم ولا تهم اللاحقة

    if(mediaPlayInLocale(m_soundPath)==true){
        //البحث عن الاية حسب ما ادخله المستخدم
        qDebug()<<"mediaPlay return true"<<m_soundPath;
        return;
    }else if(mediaPlayInLocale(m_appPath+"/"+m_soundPath)==true){
        //usr/shar/elforkane/audio/recetername----البحث عن الاية في دليل البرنامج
        qDebug()<<"mediaPlay return true"<<m_appPath+"/"+m_soundPath;
        return;
    }else if(mediaPlayAyat("/usr/share/ayat/packages/data/")==true){
        //"/usr/shar/ayat/packages/data/"+m_receter+"1-3"+"/audio/"+m_soundPath----البحث عن الاية حسب حزم برنامج ايات
qDebug()<<"mediaPlayAyat===============================================";
        return;

    }else if(mediaPlayInLocale(QDir::homePath()+"/.elforkane/"+m_soundPath)==true){
        //home/user/.elforkane/audio/recetername----البحث عن الاية في دليل المستخدم
        qDebug()<<"mediaPlay return true"<<QDir::homePath()+"/.elforkane/"+m_soundPath;
        return;
    }else{

        //البحث عن الاية في الانترنت
        mediaPlayInNetwork();
        return;
    }


}

void MainWindow::mediaFinished()
{

    if(m_autoPlayNext==false){

        //تكرار الاية
        if (m_autoRepeatOne==true){
            if (m_isRepeatNumber==true){
                if(m_numPlayed>=m_repeatNumber){
                    m_numPlayed=1;

                    setCurentPos(m_id+1);
                    mediaPlay();
                    return;
                }
            }

            mPlayer->repeate();
            m_numPlayed++;
            return;
        }

        // تكرار الصفحة او تكرار السورة
        if (m_autoRepeatPage==true||m_autoRepeatSura==true||m_autoRepeatFromTo){
            if(m_id>=m_repeatAyaLast){
                if (m_isRepeatNumber==true){
                    if(m_numPlayed>=m_repeatNumber){
                        m_numPlayed=1;
                        setCurentPos(m_id+1);
                    }else{
                        setCurentPos(m_repeatAyaFirst);
                        m_numPlayed++;
                    }
                }else{
                    setCurentPos(m_repeatAyaFirst);
                }
            }else{
                setCurentPos(m_id+1);
            }
            return;
        }
    }
    //قراءة متتالية

    setCurentPos(m_id+1);


}



//end------------- phonon----------

void MainWindow::on_actionMemoriz_triggered(bool checked)
{

    sceenbase->setHifdh(checked);

}


void MainWindow::runtimerScreen()
{
    int cpos=this->cursor().pos().x();
    int ypos=this->cursor().pos().y();
    if(cpos>=QApplication::desktop()->screen()->geometry().width()-10)
        oldCurPos=QApplication::desktop()->screen()->geometry().width()-11;
    if(cpos==oldCurPos){
        this->cursor().setPos(cpos+10,ypos);
        this->cursor().setPos(cpos-10,ypos);
        //  oldCurPos=cpos+5;
    }else if(cpos==oldCurPos+10){
        this->cursor().setPos(cpos-10,ypos);
        //  oldCurPos=cpos-5;
    }else {
        oldCurPos=this->cursor().pos().x();
    }
}

void MainWindow::on_actionScriptDownload_triggered()
{
    DialogScript *dlg=new DialogScript(this);
    QStringList listItem;
    for(int i=0;i<comboSura->count();i++)
    {
        QString txt=comboSura->itemText(i);
        QString data=comboSura->itemData(i).toString();
        listItem<<txt+","+data;
    }
    dlg->setcomboItems(listItem);
    dlg->setUrlName(m_soundUrl);
    dlg->setPathCostum(m_soundPath);
    if (dlg->exec() == QDialog::Accepted){


    }
}

void MainWindow::createTaskbar()
{
    //    taskbarButton = new QWinTaskbarButton(this);
    //    taskbarButton->setWindow(windowHandle());

    //    taskbarProgress = taskbarButton->progress();
    //    connect(positionSlider, SIGNAL(valueChanged(int)), taskbarProgress, SLOT(setValue(int)));
    //    connect(positionSlider, SIGNAL(rangeChanged(int, int)), taskbarProgress, SLOT(setRange(int, int)));

    //    connect(mediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(updateTaskbar()));
}

void MainWindow::createThumbnailToolBar()
{
    //    thumbnailToolBar = new QWinThumbnailToolBar(this);
    //    thumbnailToolBar->setWindow(windowHandle());

    //    playToolButton = new QWinThumbnailToolButton(thumbnailToolBar);
    //    playToolButton->setEnabled(true);
    //    playToolButton->setToolTip(tr("Play"));
    //    playToolButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    //  //connect(playToolButton, SIGNAL(clicked()), this, SLOT(playPause()));

    //    forwardToolButton = new QWinThumbnailToolButton(thumbnailToolBar);
    //    forwardToolButton->setEnabled(true);
    //    forwardToolButton->setToolTip(tr("Fast forward"));
    //    forwardToolButton->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    //   // connect(forwardToolButton, SIGNAL(clicked()), this, SLOT(seekForward()));

    //    backwardToolButton = new QWinThumbnailToolButton(thumbnailToolBar);
    //    backwardToolButton->setEnabled(true);
    //    backwardToolButton->setToolTip(tr("Rewind"));
    //    backwardToolButton->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    //    //connect(backwardToolButton, SIGNAL(clicked()), this, SLOT(seekBackward()));

    //    thumbnailToolBar->addButton(backwardToolButton);
    //    thumbnailToolBar->addButton(playToolButton);
    //    thumbnailToolBar->addButton(forwardToolButton);

    ////    connect(mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(updateThumbnailToolBar()));
    ////    connect(mediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(updateThumbnailToolBar()));
    //    connect(mediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(updateThumbnailToolBar()));
}

void MainWindow::updateThumbnailToolBar()
{

    //    playToolButton->setEnabled(mediaPlayer->duration() > 0);
    //    backwardToolButton->setEnabled(mediaPlayer->position() > 0);
    //    forwardToolButton->setEnabled(mediaPlayer->position() < mediaPlayer->duration());

    //    if (mediaPlayer->state() == QMediaPlayer::PlayingState) {
    //        playToolButton->setToolTip(tr("Pause"));
    //        playToolButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    //    } else {
    //        playToolButton->setToolTip(tr("Play"));
    //        playToolButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    //    }

}



void MainWindow::on_actionPlayPause_triggered()
{
    mPlayer->playPause();
}

void MainWindow::on_actionQuit_triggered()
{
    if(trayIcon->isVisible())
        trayIcon->hide();

    this->close();
}
