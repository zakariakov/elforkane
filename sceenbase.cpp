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
#include "sceenbase.h"
#include <math.h>
#include<QLocale>
 #include <QFile>
 #include <QTextStream>
 #include <QDebug>
 #include <QGraphicsProxyWidget>
#include <QWidget>
 #include <QBoxLayout>
 #include <QGraphicsGridLayout>
 #include <QGraphicsDropShadowEffect>
 #include <QPropertyAnimation>
 #include <QParallelAnimationGroup>
 #include <QApplication>
 #include <QFileInfo>
Sceenbase::Sceenbase( QWidget *parent) : QGraphicsScene(parent)
{

///----------------------قيم مبدئية
    m_pHieght=672;
    m_pWith=456;
        m_px=457;
        m_curentRiwaya="default";
        m_themeFolder="default";
        m_showSelection=true;
        m_animEnabled=false;
        m_bLeft=false;
        m_bRight=false;
        m_isHifdh=false;
        safhaLeft=2;
        safhaRight=1;
        m_difer=10;

creatPagesAndPopup();
//! [0]

        //! [1]




}

void Sceenbase::setAppPath(QString path)
{
    appPath=path;

}

  void  Sceenbase::setColorSelection(QColor color)
  {
         m_selectColor=color;
  }

  void  Sceenbase::setThemeFolder(QString themeFolder)
  {
        m_themeFolder=themeFolder;
  }
  void  Sceenbase::setRewayat(QString rewayat)
  {
            m_curentRiwaya=rewayat;

            openData();
             newPages();
  }
  void  Sceenbase::setAnimationEnabled(bool enabled)
  {
            m_animEnabled=enabled;
  }
  void Sceenbase::updatePages()
  {
      newPages();
  }

void Sceenbase::setwinLocal(QLocale arg)
{
    Lc=arg;
}
  void Sceenbase::setParentSize(int with,int hieght,int x)
  {
      m_parentWidth=with;
      m_parentHeight=hieght;
      m_parentLeft=x;
      int ptop=0;
      if(m_parentHeight>m_pHieght)
          ptop=(m_parentHeight-m_pHieght)/2;
  panelMedia->setPos(QPointF(panelMedia->pos().x(), -(ptop+10)));
  }
   void Sceenbase::setParentLeft(int x)
   {
       m_parentLeft=x;
   }

 void Sceenbase::setCurentPages(int safha,int y, bool istafsir)
 {
//     safhaLeft=left;
//     safhaRight=right;
//     safhaCurent=curent;
//     itemSelection->setVisible(false);
//     panelPopup->setVisible(false);
    safhaCurent=safha;
    //------------------------------------------------------------------------
    //معرفة اذا كان العدد زوجي او فردي
        int d=(safha);
        int i=fmod(d,2);
        if (safha >safhaLeft){//اذا كانت الصفحة المطلوبة اكبر من الصفحة الحالية اليسرى
            if (i==1){
                safhaRight=safha;
                safhaLeft=(safha+1);

            }else{
                safhaRight=(safha-1);
                safhaLeft=safha;

            }

           // sceenbase->setCurentPages(safhaLeft,safhaRight,m_curentSafha);
            animePageRight();

        }else if(safha<safhaRight){    //اذا كانت الصفحة المطلوبة اقل من الصفحة الحالية اليمنى
            safhaRight=(safha-1);
            safhaLeft=safha;
            if (i==1){
                safhaRight=safha;
                safhaLeft=(safha+1);
            }else{
                safhaRight=(safha-1);
                safhaLeft=safha;
            }


       //     sceenbase->setCurentPages(safhaLeft,safhaRight,m_curentSafha);
           animePageLeft();

        }


     //   setPage(m_curentSafha);

        if (i==1){//اذا كانت الصفحة تحمل رقما فرديا يتم رسم نافذة التفاسير على اليمين
            m_px=457;
               updatPopup(y,m_pWith,m_pWith,0,istafsir);
        }else{
            m_px=0;
                 updatPopup(y,120,0,457,istafsir);
        }
      //-------------------------------------------------------tosceenbase--------------------------------

 }
  void Sceenbase::setPage(int p)
  {
        safhaCurent=p;
  }

  void Sceenbase::setPopupVisible(bool visible)
  {
     m_showPopup=visible;
     panelPopup->setVisible(visible);

  }
   void Sceenbase::setMediaControleVisible(bool visible)
   {
       panelMedia->setVisible(visible);
   }
     void Sceenbase::setStandardTools(bool st)
     {
        m_standardTool=st;
        creatMediaControles();
     }
       void Sceenbase::setShowSelection(bool show)
       {
           m_showSelection=show;
       }

void Sceenbase::openData()
{
    QString dataArbaa=appPath+"/images/"+m_curentRiwaya+"/arbaarc";
    QString dataSafahat=appPath+"/images/"+m_curentRiwaya+"/safahatrc";

    qDebug()<<appPath+"/images/"+m_curentRiwaya+"/datarc";
    qDebug()<<appPath+"/images/"+m_curentRiwaya+"/safahatrc";
    if(!QFile::exists(dataArbaa)){

  dataSafahat=":/data/safahatrc";
   dataArbaa=":/data/arbaarc";
    }
    QFile fileArbaa(dataArbaa);
    //-----------------------dataSafahat-----------------------------
    QFile fileSafahat(dataSafahat);
    if(!fileSafahat.open( QFile::ReadOnly)){
        qDebug() <<"no open safahat " +appPath+"/safahatrc";
    }
    myListSafhat.clear();
    QTextStream textStream2(&fileSafahat);
    QString lineSafahat;
    lineSafahat = textStream2.readLine();//premier line

    while (!lineSafahat.isNull()) {

        myListSafhat.append(lineSafahat);

        lineSafahat = textStream2.readLine();
    }
    fileSafahat.close();

    //-----------------------dataArbaa-----------------------------
    if(!fileArbaa.open( QFile::ReadOnly)){
        qDebug() <<"no open arbaa "+appPath+"/arbaarc" ;
    }
    myListArbaa.clear();
    QTextStream textStreamarba(&fileArbaa);

    QString lineArbaa;
    lineArbaa = textStreamarba.readLine();

    while (!lineArbaa.isNull()) {

        myListArbaa.append(lineArbaa);

        lineArbaa = textStreamarba.readLine();
    }


    fileArbaa.close();
}

void Sceenbase::creatPagesAndPopup()
{
    //انشاء اللوحة الام مع الصفحتين اليسرى واليمنى
    panelParent = new QGraphicsWidget;
    pageLeft=new QGraphicsPixmapItem(panelParent);
    pageRight=new QGraphicsPixmapItem(panelParent);
    pageLeft->setPos(0,0);
    pageRight->setPos(m_pWith+1,0);
    QPainter p;
    //انشاء اطار سفلي
    QPixmap pixbotum((m_pWith*2)+2,m_pHieght+2);
    pixbotum.fill(Qt::transparent);
    p.begin(&pixbotum);
    //        QLineF line(m_pWith, m_pHieght, m_pWith,0.0);
    //       p.drawLine(line);
    p.setPen(QColor(127,120,25,250));
    QRectF rect(0.0, 1.0, (m_pWith*2), m_pHieght-1);
    p.drawRect(rect);
    p.end();
    //انشاء زرين على اليمين واليسار لسحب الصفحات
    QPixmap pixT(1,1);
    pixT.fill(Qt::transparent);
    btnLeft=new PixmapS(pixT);
    btnLeft->setGeometry(QRectF(0,0,30,m_pHieght));
    connect(btnLeft, SIGNAL(enter()), this, SLOT(goNextEenter()));
    connect(btnLeft, SIGNAL(leave()), this, SLOT(goNextLeave()));
    connect(btnLeft, SIGNAL(pressed()), this, SLOT(goNextPrissed()));
    connect(btnLeft, SIGNAL(release()), this, SLOT(goNextRelease()));
    connect(btnLeft, SIGNAL(mouseMove()), this, SLOT(goNextMoved()));
    btnRight=new PixmapS(pixT);
    btnRight->setGeometry(QRectF((m_pWith*2)-30,0,30,m_pHieght));
    connect(btnRight, SIGNAL(enter()), this, SLOT(goPrevEenter()));
    connect(btnRight, SIGNAL(leave()), this, SLOT(goPrevLeave()));
    connect(btnRight, SIGNAL(pressed()), this, SLOT(goPrevPrissed()));
    connect(btnRight, SIGNAL(release()), this, SLOT(goPrevRelease()));
    connect(btnRight, SIGNAL(mouseMove()), this, SLOT(goPrevMoved()));
    //انشاء اطار لاستعماله عند تحريك الصفحات بواسطة الرسم التلقائي  من نوع لابل label
    //  QGraphicsProxyWidget *maskProxy = new QGraphicsProxyWidget;
    m_labMask=new QLabel();
    m_labMask->setLayoutDirection(Qt::RightToLeft);
    m_labMask->setGeometry(0,0,150,m_pHieght);
    //maskProxy->setWidget(m_labMask);

    //انشاء اطار التحديد بابعاد اافتراضية
    itemSelection = new PixmapS( updatePixSelect(60,382,382,1,0)); //type  0=button 1=selection 2=mask
    itemSelection->setGeometry(QRectF(m_px+37,40,382,60));
    //انشاء اطار للظل المتحرك اثناء تحريك الصفحات اليمنى واليسرى
    QPixmap pixsRefletLeft(80,m_pHieght);
    pixsRefletLeft.fill(Qt::transparent);
    p.begin(&pixsRefletLeft);
    p.drawPixmap(0,0,80,m_pHieght,QPixmap(":/img/reflet.png"));
    p.end();
    itemRefletLeft= new PixmapS(pixsRefletLeft);
    itemRefletLeft->setGeometry(QRectF(0,0,80,m_pHieght));

    QPixmap pixsRefletRight(80,m_pHieght);
    pixsRefletRight.fill(Qt::transparent);
    p.begin(&pixsRefletRight);
    p.drawPixmap(0,0,80,m_pHieght,QPixmap(":/img/refletRight.png"));
    p.end();
    itemRefletRigt= new PixmapS(pixsRefletRight);
    itemRefletRigt->setGeometry(QRectF(m_pWith-80,1,60,m_pHieght));
    //انشاء اطار للرسم عليه اثناء حركة السحب بواسطة الماوس
    picMoved=new QGraphicsPixmapItem(panelParent);

    //انشاء نافذة التفاسير والتراجم
    //قاعدة النافذة
    panelPopup=new  QGraphicsWidget;

    ItemPopup= new   QGraphicsPixmapItem (panelPopup);
    ItemPopupBlure= new   QGraphicsPixmapItem (panelPopup);
    //اداة النص الذي يعرض عليه التفسير والترجمة
    textEdit=new QTextEdit();
    //    QAction *actionZoomIn=new QAction(QIcon(":/img/zoom-in.png"),trUtf8("&zoomIn"),this);
    //    QAction *actionZoomOut=new QAction(QIcon(":/img/zoom-out.png"),trUtf8("&zoomOut"),this);
    //            connect(actionZoomIn, SIGNAL(triggered()), textEdit, SLOT(zoomIn()));
    //    connect(actionZoomOut, SIGNAL(triggered()), textEdit, SLOT(zoomOut()));
    textEdit->setFrameShape(QFrame::NoFrame);
    QGraphicsProxyWidget *txtProxy = new QGraphicsProxyWidget();
    QGraphicsProxyWidget *toolProxy = new QGraphicsProxyWidget();
    txtProxy->setWidget(textEdit);
    //لوحة الادوات التي تحتوي زر التكبير والتصغير وعنوان التفسير وقائمة االتبديل بين التفاسير والتراجم
    toolbarPopup=new QToolBar();
    toolbarPopup->setIconSize(QSize(16,16));
    QHBoxLayout  *horizontalLayout = new QHBoxLayout();
    QFrame *frame=new QFrame;
    horizontalLayout->setContentsMargins(1,1,1,1);
    horizontalLayout->addWidget(toolbarPopup);
    frame->setLayout(horizontalLayout);
    //    QAction *actHidPop=new QAction(QIcon(":/img/list-remove.png"),trUtf8("&Hide"),frame);
    //    connect(actHidPop, SIGNAL(triggered()), this, SLOT(hidePopup()));
    //اضافة الادوات الى اللوحة
    //    toolbarPopup->addAction(actHidPop);
    //    toolbarPopup->addSeparator();
    //    toolbarPopup->addAction(actionZoomIn);
    //    toolbarPopup->addAction(actionZoomOut);
    toolbarPopup->addSeparator();
    //    labelTransTefsir=new QLabel;
    //    labelTransTefsir->setMaximumWidth(150);

    //استخدام سمة للوحة الادوات
    // qApp->palette().color(QPalette::Window)

    QString str="QFrame ,QToolBar {"
                "background-color: rgba(255, 255, 255, 0);border: 0px;}";
    frame->setStyleSheet(str);
    frame->setFrameShape(QFrame::NoFrame);
    frame->setLineWidth(0);
    toolbarPopup->setFloatable(false);
    toolbarPopup->setMovable(false);
    toolProxy->setWidget(frame);
    //--------------
    //اظافة الادوات والاطارات السابقة الى قاعدة النافذة
    panelPopup->setGeometry(0,0,m_pWith,(m_pHieght/2)+120);
    QGraphicsGridLayout *gridLayout = new QGraphicsGridLayout();
    gridLayout->addItem(toolProxy,0,1,Qt::AlignCenter);
    gridLayout->addItem(txtProxy,1,1,Qt::AlignCenter);
    gridLayout->setContentsMargins(70,70,70,70);
    panelPopup->setLayout(gridLayout);

    m_labMask->setVisible(false);
    itemRefletLeft->setVisible(false);
    itemRefletRigt->setVisible(false);
    //  panelPopup->setVisible(m_showPopup);
    // emit popupVisible(m_showPopup);


    //اعداد المشهد واضافة كل الصفحات والادوات السابقة
    //m_scene=new QGraphicsScene();
    QLineF line(m_pWith, m_pHieght, m_pWith,0.0);
    this->addLine(line);
    this->addItem(panelParent);

    this->addPixmap(pixbotum);
    this->addItem(itemSelection);
    //  this->addItem(maskProxy);
    this->addWidget(m_labMask);
    this->addItem(itemRefletLeft);
    this->addItem(itemRefletRigt);
    this->addItem(btnLeft);
    this->addItem(btnRight);
    this->addItem(panelPopup);

    //  ui->graphicsView->setScene(m_scene);
    panelParent->setPos(0,1);



    itemRefletLeft->setZValue(99);
    itemRefletRigt->setZValue(98);
    //maskProxy->setZValue(97);
    picMoved->setZValue(96);
    panelPopup->setZValue(95);

}

void Sceenbase::creatMediaControles()
{
    panelMedia=new  QGraphicsWidget;
    panelMedia->setZValue(100);
    QPixmap pixmy(54,24);
    pixmy.fill(Qt::transparent);
    btnMedia=new PixmapS(pixmy,panelMedia);

    int panelwidth=0;
int panelXpos=0;

 if(m_standardTool==false){
     panelwidth=m_pWith*2;//300 ; //m_pWith*2;
     panelXpos=0;//m_pWith-150;//0;
 }else{
      panelwidth=300 ; //m_pWith*2;
     panelXpos=m_pWith-150;//0;
 }

   QGraphicsPixmapItem *ItemMedia= new   QGraphicsPixmapItem (panelMedia);
   QPixmap pixmap(panelwidth,80);
   pixmap.fill(Qt::transparent);
   //qreal rad =20;
   QPainter p;
   p.begin(&pixmap);
   p.setRenderHint(QPainter::Antialiasing,true);
   p.setPen(QColor(255, 255, 255,255));
   QRectF rect(0.0,0.0,panelwidth,50.0);
   p.setBrush(QColor(255, 255, 255, 120));
   QRectF rectangle((panelwidth/2)-30, 5.5, 60.0, 60.0);
   int startAngle = 16 * 210;
   int spanAngle = 16 * 120;
   p.drawRoundedRect(rect,9.0,9.0);
   p.drawChord(rectangle, startAngle, spanAngle);

   p.end();

   ItemMedia->setPixmap(pixmap);

   panelMedia->setGeometry(panelXpos,(m_pHieght-m_pHieght)-10,panelwidth,70);
   QGraphicsDropShadowEffect *efet=new QGraphicsDropShadowEffect;
   efet->setOffset(5,5);
   efet->setColor((QColor(63, 63, 63,200)))  ;
   efet->setBlurRadius(15);

   panelMedia->setGraphicsEffect(efet);
   QGraphicsProxyWidget *txtProxy = new QGraphicsProxyWidget();
  toolbarMedia=new QToolBar();
   QVBoxLayout  *horizontalLayout = new QVBoxLayout();
   QFrame *frame=new QFrame;
   horizontalLayout->setContentsMargins(1,1,1,1);
   horizontalLayout->setSpacing(0);
           horizontalLayout->addWidget(toolbarMedia);

   frame->setLayout(horizontalLayout);
   int mred=  qApp->palette().color(QPalette::Window).red();
       int mgreen=qApp->palette().color(QPalette::Window).green();
       int mblue= qApp->palette().color(QPalette::Window).blue();
   //--------
       QString str=QString("QFrame ,QToolBar  {"
                   " background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(%1, %2, %3, 160), stop:0.652632 rgba(%1, %2, %3, 50), stop:1 rgba(255, 255, 255, 0));border: 0px solid white; border-radius: 5px;}"
                           ).arg(mred).arg(mgreen).arg(mblue);

       frame->setStyleSheet(str);
   frame->setFrameShape(QFrame::NoFrame);
   frame->setLineWidth(0);
   toolbarMedia->setFloatable(false);
   toolbarMedia->setMovable(false);
   txtProxy->setWidget(frame);
   QGraphicsGridLayout *gridLayout = new QGraphicsGridLayout();
   gridLayout->addItem(txtProxy,1,1,Qt::AlignCenter);
   gridLayout->setContentsMargins(1,10,1,25);

   connect(btnMedia, SIGNAL(release()), this, SLOT(moveMediaControle()));
   btnMedia->setGeometry(QRectF((panelwidth/2)-30,50,60,24));
   btnMedia->setCursor(Qt::PointingHandCursor);
   panelMedia->setLayout(gridLayout);
   panelMedia->setPos(panelXpos,-10);

   this->addItem(panelMedia);
   panelMedia->resize(panelMedia->size());
}

void Sceenbase:: moveMediaControle()
{
    int ptop=0;
    if(m_parentHeight>m_pHieght)
        ptop=(m_parentHeight-m_pHieght)/2;

    int y=panelMedia->pos().y();
    int x=panelMedia->pos().x();

    if (m_animEnabled==false){//اذا كانت المؤثرات الحركية غير مفعلة
        if (y<= -(ptop+50)){
            panelMedia->setPos(QPointF(x, -(ptop+10)));

        }else{
            panelMedia->setPos(QPointF(x, -(ptop+50)));
        }
        return;
    }

    QPropertyAnimation * anim = new QPropertyAnimation(panelMedia, "pos");
    if (y<= -(ptop+50)){//التحريك للاعلى

        anim->setEndValue(QPointF(x, -(ptop+10)));
        anim->setEasingCurve(QEasingCurve::OutBounce);

    }else{//التحريك للاسفل

        anim->setEndValue(QPointF(x, -(ptop+50)));
        anim->setEasingCurve(QEasingCurve::InCubic);

    }

    anim->setDuration(750);
    anim->start();
}

//----تحدسث نافذة التفاسير
void Sceenbase::updatPopup(qreal poY,qreal poX1,qreal poX2,int px,bool istefsir)
{
    panelPopup->setPos(px,0);
    qreal poY2=poY;
    if (poY2<80)
        poY2=80;
    if (poY2>m_pHieght-80)//اذا كان الموضع ع اكبر من طول الصفحة
        poY2=m_pHieght-80;

    if(istefsir==true){
        //اذا كانت تحتوي على تفسير سيكون الحجم على حجم الصفحة
        panelPopup->setGeometry(panelPopup->pos().x(),panelPopup->pos().y(),m_pWith,(m_pHieght));

    }else{
        panelPopup->setGeometry(panelPopup->pos().x(),panelPopup->pos().y(),m_pWith,(m_pHieght/2)+120);
        if (poY2>(m_pHieght/2)){
            int y=(m_pHieght/2)-120;
            panelPopup->setPos(panelPopup->pos().x(),y);
            poY2=poY2-y;
            poY=poY-y;
        }
    }

    QPainter p;
    textEdit->setStyleSheet("QTextEdit{background-color: rgba(255, 255, 255, 20);"
                            " background-attachment: fixed;"
                           " /*font-family:Traditional Arabic;*/}");

    QPixmap pixmap(panelPopup->geometry().width(),panelPopup->geometry().height());

    QPixmap pixmapBlure(panelPopup->geometry().width()-124,panelPopup->geometry().height()-124);
    pixmapBlure.fill(Qt::transparent);
    pixmap.fill(Qt::transparent);
     QString image;
    if(px==0){
       image=appPath+"/images/"+m_curentRiwaya+"/"+QString::number(safhaLeft)+".png";
    }else{
          image=appPath+"/images/"+m_curentRiwaya+"/"+QString::number(safhaRight)+".png";
    }

      p.begin(&pixmapBlure);
          p.setRenderHint(QPainter::Antialiasing,true);
        p.drawPixmap(0,0,panelPopup->geometry().width()-124,panelPopup->geometry().height()-124,QPixmap(image)
                     ,60,panelPopup->pos().y()+60,panelPopup->geometry().width()-124,panelPopup->geometry().height()-124);
        p.end();
ItemPopupBlure->setPixmap(pixmapBlure);
ItemPopupBlure->setPos(62.0,62.0);
    p.begin(&pixmap);
    p.setRenderHint(QPainter::Antialiasing,true);
    p.setPen(QColor(128, 128, 128,80));
    //ابعاد المربع
    QRectF rect(60.0,60.0,panelPopup->geometry().width()-120,panelPopup->geometry().height()-120);
    p.setBrush(QColor(255, 255, 255,220));
    //النقاط الثلاثة للمثلث
    QPointF points[3]={
        QPointF(poX1-60,poY2-10.0),
        QPointF(poX2,poY),
        QPointF(poX1-60,poY2+10.0),
    };
    //رسم المربع
    p.drawRoundedRect(rect,5.0,5.0);
    //رسم مثلث الذي يشير الى الاية
    p.drawPolygon(points,3);
    p.end();
    ItemPopup->setPixmap(pixmap);
    //اضافة مؤثر الظل الى النافذة
    QGraphicsDropShadowEffect *efet=new QGraphicsDropShadowEffect;
    efet->setOffset(3,3);
    efet->setColor((QColor(63, 63, 63,180)))  ;
    efet->setBlurRadius(10);
//blure
    QGraphicsBlurEffect *efetBlure=new QGraphicsBlurEffect;
   // efetBlure->setBlurHints();
    efetBlure->setBlurRadius(6);


    panelPopup->setGraphicsEffect(efet);
ItemPopupBlure->setGraphicsEffect(efetBlure);
}

//رسم الصفحات الجديدة
void Sceenbase::newPages()
{

    m_labMask->setVisible(false);
    itemRefletLeft->setVisible(false);
    itemRefletRigt->setVisible(false);
    itemSelection->setVisible(true);
    panelPopup->setVisible(m_showPopup);//----------------------------------------------------------------(m_showPopup);



    if (safhaRight==1){
        btnRight->setEnabled(false);
    }else{
        btnRight->setEnabled(true);
    }
    if (safhaLeft==604){
        btnLeft->setEnabled(false);
    }else{
        btnLeft->setEnabled(true);
    }



    for (int i = 0; i <buttons.count(); ++i) {
        this->removeItem(buttons.at(i));

        delete buttons.at(i);
    }
    buttons.clear();

    //--------------------------********************************------------
    if(m_isHifdh==true){

      hifdhType();
    }else{

         readType();
    }

    QString pixRight=appPath+"/images/"+m_curentRiwaya+"/"+QString::number(safhaRight)+".png";
    QString pixLeft=appPath+"/images/"+m_curentRiwaya+"/"+QString::number(safhaLeft)+".png";

    if (safhaCurent<3){
        pageRight->setPixmap(pixRight);
        pageLeft->setPixmap(pixLeft);
    } else{
        pageRight->setPixmap(disignePage(pixRight));
        pageLeft->setPixmap(disignePage(pixLeft));
    }


}

void Sceenbase::goAyaSelected()
{
    ButtonG *currentItem= qobject_cast<ButtonG *>(sender());
    int pos=currentItem->data(0).toInt();
emit setPos(pos);
}

void Sceenbase::itemAyaEntered()
{
      ButtonG *currentItem= qobject_cast<ButtonG *>(sender());
      currentItem->setOpacity(0.3);
}

void Sceenbase::itemAyaLived()
{
      ButtonG *currentItem= qobject_cast<ButtonG *>(sender());
       currentItem->setOpacity(0.01);
}

//رسم الصفحات
QPixmap Sceenbase::disignePage(QString safha)
{

    bool defaultThem=false;

    QFileInfo fi(safha);
    QString num=fi.baseName();


        if (m_themeFolder=="default"&&m_curentRiwaya!="default")
            return safha;
        if(m_themeFolder=="default"&&m_curentRiwaya=="default")
           defaultThem=true;


    QPixmap pixMy(safha);
    QPainter p;


    QString arbaaStr=myListArbaa.at(num.toInt());
    QString robaa=arbaaStr.section(",",2,2).trimmed();
    QString robaaY=arbaaStr.section(",",1,1).trimmed();
    QString robahizb=arbaaStr.section(",",0,0).trimmed();
    QPixmap pixtop(37,37);
    //-----------بداية الرسم
    p.begin(&pixMy);
  //  pixtop.fill(Qt::white);
  //    p.setCompositionMode(QPainter::CompositionMode_Source);
    p.setRenderHint(QPainter::Antialiasing,true);
 QString imgThemePath=appPath+"/themes/"+m_themeFolder;
    if(defaultThem==false){

        //-------رسم زخارف الجهة العليا والسفلى
        pixtop.load( imgThemePath+"/top.png") ;
        int count=(m_pWith/pixtop.width())+1;
        for (int i=0;i<count;i++){

            p.drawPixmap(i*pixtop.width(),0,pixtop.width(),38,pixtop);
        }

        QPixmap pixbot( imgThemePath+"/bot.png") ;
        for (int i=0;i<count;i++){
            p.drawPixmap(i*pixbot.width(),m_pHieght-38,pixbot.width(),38,pixbot);
        }

        //-------رسم زخارف الجهة اليسرى واليمنى
         QPixmap pixleft( imgThemePath+"/left.png") ;
        int count2=(m_pHieght/pixleft.height())+1;

        for (int i=0;i<count2;i++){
            p.drawPixmap(0,i*pixleft.height(),38,pixleft.height(),pixleft);
        }
        QPixmap pixright( imgThemePath+"/right.png") ;
        for (int i=0;i<count2;i++){
            p.drawPixmap(m_pWith-38,i*pixright.height(),38,pixright.height(),pixright);
        }
        //---------رسم زخارف الزوايا

       QPixmap pixtop_left( imgThemePath+"/top_left.png") ;
        p.drawPixmap(0,0,38,38,pixtop_left);
       QPixmap top_right( imgThemePath+"/top_right.png") ;
        p.drawPixmap(m_pWith-38,0,38,38,top_right);
        QPixmap bot_left( imgThemePath+"/bot_left.png") ;
        p.drawPixmap(0,m_pHieght-38,38,38,bot_left);
       QPixmap pixbot_right( imgThemePath+"/bot_right.png") ;
        p.drawPixmap(m_pWith-38,m_pHieght-38,38,38,pixbot_right);

        //--------------------------------------------------------------------------------------
    }else{
        QPixmap pixDefault(appPath+"/default.png");
        p.drawPixmap(pixMy.rect(),pixDefault);
    }
    //------رسم ارقام الصفحات
     QLocale lc(Lc.name());
    QRectF rectangle(m_pWith/2-24, m_pHieght-30, 40, 28);
    p.setBrush(QColor(255, 255, 255,200));
    p.drawEllipse(rectangle);
    p.drawText(rectangle, Qt::AlignCenter,lc.toString(num.toInt()));
    //-------  رسم الارباع و بعض الاستثناءات
    if (robaa.toInt()>0){
        QPixmap pixRbaa(":/img/r"+robaa+".png");
        if(QFile::exists(imgThemePath+"/r"+robaa+".png"))
            pixRbaa.load(imgThemePath+"/r"+robaa+".png");
        int pLeft=0;
        int i=fmod(num.toInt(),2);
        if(i==1)
            pLeft=m_pWith-pixRbaa.width();
        p.drawPixmap(pLeft,robaaY.toInt()-pixRbaa.height()/2,pixRbaa);
        if(robaa!="5"){
            QRect rect(pLeft+3,robaaY.toInt(),30,25);
            p.drawText(rect, Qt::AlignCenter,lc.toString(robahizb.toInt()));
        }
        if (num=="454"||num=="589"){
            QPixmap pixRbaaBack(":/img/r5.png");
            if(QFile::exists(imgThemePath+"/r5.png"))
                pixRbaaBack.load(imgThemePath+"/r5.png");
            if (num=="454")
                p.drawPixmap(pLeft,457-pixRbaa.height()/2,pixRbaaBack);
            if (num=="589")
                p.drawPixmap(pLeft,573-pixRbaa.height()/2,pixRbaaBack);
        }
    }
    p.end();
    return pixMy;
}

QPixmap Sceenbase::updatePixSelect(int h,int x1 ,int x2,int type,int item)
{
    //type  0=button 1=selection 2=mask
    QPainter p;
    QPainterPath path;
QColor myColor=m_selectColor;
 myColor.setAlpha(50);
if(type==2){
myColor=Qt::white;
 myColor.setAlpha(250);
}
    if(m_showSelection==false&&type==1){//اذا كان التحديد غير مفعل سيتم رسم دائرة حول رقم الاية
        QPixmap pix(24,26);
        pix.fill(Qt::transparent);
        p.begin(&pix);
        p.setRenderHint(QPainter::Antialiasing,true);

        p.setPen(myColor);
        //    QRectF rect(0.0,0.0,300,50.0);
        p.setBrush(myColor);
        //   myColor.setAlpha(100);
        p.drawEllipse(QRect(0, 0,24,26));
        p.end();
        return pix;
    }


    QPixmap pixselect(380,h);
    pixselect.fill(Qt::transparent);
    p.begin(&pixselect);

    int top=0;

    //اذا كان ترقيم الاية في اخر السطر تأخذ القيمة 0 حتى لايتم رسمها

    if(x2<60){
        x2=0;

    }
    p.setPen(myColor);
    //اذا كلنت الاية تتكون من سطر واحد اي طول اتحديد اقل من 50

    if (h<=50){
       // if(type>0)
        p.fillRect(x1-40,top,x2-x1,40,myColor);
        p.end();
         //type  0=button 1=selection 2=mask
    if(type!=1){
        path.addRect(x1-40,0,x2-x1,40);
        buttons.at(item)->setPath(path);
    }
        return pixselect;
    }
    //اذا كانت الاية تتكون من سطرين

    if(h<=85){

  //if(type>0){
        p.fillRect(0,top,x2-40,40,myColor);
        p.fillRect(x1-40,top+40,382-x1+40,40,myColor);
 // }
        p.end();
        if(type!=1){
            path.addRect(0,top,x2-40,40);
             path.addRect(x1-40,top+40,382-x1+40,40);
            buttons.at(item)->setPath(path);
        }

        return pixselect;
    }
    //اكثر من سطرين
   //   if(type>0){
    p.fillRect(0,top,-40+x2,40,myColor);
     p.fillRect(0,40,382,h-80,myColor);
    p.fillRect(x1-40,h-40,382-x1+40,40,myColor);
//}
    p.end();
    if(type!=1){
        path.addRect(0,top,-40+x2,40);
         path.addRect(0,40,382,h-80);
        path.addRect(x1-40,h-40,382-x1+40,40);
         buttons.at(item)->setPath(path);
    }
    return pixselect;
}
void Sceenbase::setMoveSelection(int top,int hight,int x1,int x2, int px)
{
//    if(this->parent()->isFullScreen()){
//         if(myListSceen.count()>0)
//        fullScreenPixmap(top,hight,x1,x2);
//    }
//    if(m_autoRepeatOne==false){     //اذا كان وضع القراءة وتم تحريك التحديد
//        if(isPlay==true){
//            mediaPlay();
//        }
//    }
    //اعادة رسم التحديد


    itemSelection->setPixmap( updatePixSelect(hight,x1,x2,1,0));
 //type  0=button 1=selection 2=mask
    if(m_showSelection==false){      //اذا كان التحديد غير مفعل
        if (m_animEnabled==false){      //اذا لم تكن المؤثرات الحركية مفعلة
            itemSelection->setGeometry(QRect(px+x1-4, top+hight-32,24,26));
        }else{
            QPropertyAnimation * anim = new QPropertyAnimation(itemSelection, "geometry");
            anim->setEasingCurve(QEasingCurve::OutQuad);
            anim->setEndValue(QRect(px+x1-4, top+hight-32,24,26));
            anim->setDuration(550);
            anim->start();
        }
        return;
    }

    if (m_animEnabled==false){      //اذا لم تكن المؤثرات الحركية مفعلة
        itemSelection->setGeometry(QRect(px+37, top,382,hight));
        return;
    }
    // المؤثر الحركي لانتقال التحديد
    QPropertyAnimation * anim = new QPropertyAnimation(itemSelection, "geometry");
    anim->setEasingCurve(QEasingCurve::OutQuad);
    anim->setEndValue(QRect(px+37, top,382,hight));
    anim->setDuration(550);
    anim->start();

}
//--تحريك الصفحة لليمسن
void Sceenbase::animePageRight()
{

    if (m_animEnabled==false){
     newPages( );
        return;
    }

    // m_labMask->setLayoutDirection(Qt::RightToLeft);
    m_labMask->setAlignment(Qt::AlignLeft);
    m_labMask->setVisible(true);

    itemRefletLeft->setVisible(true);
    m_labMask->setGeometry(m_difer,0,m_difer,m_pHieght);
    itemRefletLeft->setGeometry(QRect(m_difer-35,0,80,m_pHieght));

    QString pixRight=appPath+"/images/"+m_curentRiwaya+"/"+QString::number(safhaRight)+".png";
    QString pixLeft=appPath+"/images/"+m_curentRiwaya+"/"+QString::number(safhaLeft)+".png";


 m_labMask->setPixmap( disignePage( pixRight));
    pageLeft->setPixmap(disignePage(pixLeft));


    QPropertyAnimation * anim3 = new QPropertyAnimation(m_labMask, "geometry");
    anim3->setEndValue(QRect(m_pWith,0,m_pWith,m_pHieght));
    anim3->setDuration(550);
   anim3->setEasingCurve(QEasingCurve::OutQuint);

    QPropertyAnimation * anim4 = new QPropertyAnimation(itemRefletLeft, "pos");
    // anim4->setEndValue(QRect(m_pWith,0,60,m_pHieght));
    anim4->setEndValue(QPoint(m_pWith-35,0));
    anim4->setEasingCurve(QEasingCurve::OutQuint);
    anim4->setDuration(550);
    connect( anim3, SIGNAL(finished()), this, SLOT(newPages()));
    QParallelAnimationGroup *group = new QParallelAnimationGroup;

    group->addAnimation(anim3);
    group->addAnimation(anim4);

    group->start();

    m_difer=10;
}
//تحريك الصفحة تلقائيا الى اليسار
void Sceenbase::animePageLeft()
{
    if (m_animEnabled==false){
          newPages();
        return;
    }
    int with=m_pWith*2;

    //   m_labMask->setLayoutDirection(Qt::LeftToRight);
    m_labMask->setAlignment(Qt::AlignRight);
    m_labMask->setVisible(true);
    itemRefletRigt->setVisible(true);

    m_labMask->setGeometry(with-m_difer,0,m_difer/2,m_pHieght);
    itemRefletRigt->setGeometry(QRect(with-(m_difer/2)-55,0,80,m_pHieght));


    QString pixLeft=appPath+"/images/"+m_curentRiwaya+"/"+QString::number(safhaLeft)+".png";
    QString pixRight=appPath+"/images/"+m_curentRiwaya+"/"+QString::number(safhaRight)+".png";


    m_labMask->setPixmap(  disignePage(pixLeft));
    pageRight->setPixmap(disignePage(pixRight));

    QPropertyAnimation * anim3 = new QPropertyAnimation(m_labMask, "geometry");
    anim3->setEndValue(QRect(0,0,m_pWith,m_pHieght));
    anim3->setDuration(550);
    anim3->setEasingCurve(QEasingCurve::OutQuint);

    QPropertyAnimation * anim4 = new QPropertyAnimation(itemRefletRigt, "pos");

    anim4->setEndValue(QPoint(m_pWith-55,0));
  anim4->setEasingCurve(QEasingCurve::OutQuint);
    anim4->setDuration(550);
    connect( anim3, SIGNAL(finished()), this, SLOT(newPages()));
    QParallelAnimationGroup *group = new QParallelAnimationGroup;

    group->addAnimation(anim3);
    group->addAnimation(anim4);

    group->start();
    m_difer=10;
}
//-------------------------------------------move page manuel------------------------------------------------------
//------------------------move left to right----------------------

void Sceenbase::goNextEenter( )
{
    m_difer=15;
    //   اعطاء صورة مطوية عند ادخال المؤشر للحافة اليسرى ووضعها على الاحداثية س=0 ع=0
    picMoved->setPixmap(QPixmap(":/img/ply.png"));
    picMoved->setPos(0,0);
}

void Sceenbase::goNextLeave()
{
     //   اعطاء صورة شفافة عند اخراج المؤشر المؤشر من للحافة اليسرى
    QPixmap pix(0,0);
    pix.fill(Qt::transparent);
    picMoved->setPixmap(pix);

}

void Sceenbase::goNextPrissed( )
{

     if (m_animEnabled==false){
         if (safhaCurent==604)
             return;

         QString mtxt=myListSafhat.at(safhaCurent+1);
          int id=mtxt.section(",",0,0).trimmed().toInt();
         emit  setPos(id );
         return;
     }
     //اعلام البرنامج ببداية السحب
    m_bLeft=true;
    //desableHifdhPage();
    itemSelection->setVisible(false);
    panelPopup->setVisible(false);

//جلب الصورة اليمنى واليسرى
    QString pixRight=appPath+"/images/"+m_curentRiwaya+"/"+QString::number(safhaLeft+1)+".png";
    QString pixLeft=appPath+"/images/"+m_curentRiwaya+"/"+QString::number(safhaLeft+2)+".png";

    m_pixRigtMoved=(disignePage(pixRight));
    m_pixLeftMoved=(   disignePage(pixLeft));

}

void Sceenbase::goNextRelease( )
{
//اعلام البرنامج بنهاية السحب عند افلات المؤشر
    m_bLeft=false;
    if(m_isHifdh==false){
  panelPopup->setVisible(m_showPopup);
  itemSelection->setVisible(true);
    }
    if(m_difer<150)
        return;

    QString mtxt=myListSafhat.at(safhaLeft+1);
    int id=mtxt.section(",",0,0).trimmed().toInt();
   emit setPos(id);

}

void Sceenbase::goNextMoved( )
{
    //عند السحب
    if (m_bLeft==true){
        int tpos=m_parentLeft;
//        if(this->isMaximized()||this->isFullScreen())
//            tpos=0;
        int w=(m_parentWidth/2)-m_pWith;
        if (w<0)
            w=0;
        //معرفة موضع المؤشر
        int    wx = QCursor::pos().x()-tpos-w;
        if (wx>900)
            return;
        m_difer=wx/2;
        moveLeftToRight();
    }
}

void Sceenbase::moveLeftToRight()
{
// الرسم بعد تلقي الاشارة بتغير موضع الماوس
    QPixmap   pix1(m_difer*2,m_pHieght);
    QPainter p;
    p.begin(&pix1);
   //اقتطاع الصورة ورسمها على حاوي الرسم
    p.drawPixmap(0,0,m_difer,m_pHieght,m_pixLeftMoved,0,0,m_difer,m_pHieght);
    p.drawPixmap(m_difer,0,m_difer,m_pHieght,m_pixRigtMoved,m_pWith-m_difer,0,m_difer,m_pHieght);
    p.setPen(QColor(128,128,128,180));
    p.drawPixmap(m_difer-25,0,80,m_pHieght,QPixmap(":/img/reflet.png"));
    p.drawLine((m_difer*2)-1,0,(m_difer*2)-1,m_pHieght);
    p.end();
    picMoved->setPixmap(pix1);
}

//-----------------go right to left---------------------------
void Sceenbase::goPrevEenter()
{
    if(safhaRight==1)
        return;

    picMoved->setPixmap(QPixmap(":/img/plyR.png"));
    picMoved->setPos((m_pWith*2)-29,0);

}

void Sceenbase::goPrevLeave()
{

    QPixmap pix(0,0);
    pix.fill(Qt::transparent);
    picMoved->setPixmap(pix);

}

void Sceenbase::goPrevPrissed( )
{
    if (m_animEnabled==false){
         //on_actionPrevPage_triggered();
        return;
    }
      if(safhaRight>1){
           m_bRight=true;
    //desableHifdhPage();
           itemSelection->setVisible(false);
           panelPopup->setVisible(false);

           QString pixRight=appPath+"/images/"+m_curentRiwaya+"/"+QString::number(safhaRight-2)+".png";
           QString pixLeft=appPath+"/images/"+m_curentRiwaya+"/"+QString::number(safhaRight-1)+".png";


           m_pixRigtMoved=( disignePage(pixRight));
           m_pixLeftMoved=( disignePage(pixLeft));
     }


}

void Sceenbase::goPrevRelease( )
{

    m_bRight=false;

    if(m_isHifdh==false){
  panelPopup->setVisible(m_showPopup);//-------------------------------------***----------------
  itemSelection->setVisible(true);
    }
    //  emit popupVisible(m_showPopup);
    if(m_difer<300)
        return;

    QString mtxt=myListSafhat.at(safhaRight-1);
   int id=mtxt.section(",",0,0).trimmed().toInt();
    emit setPos(id);
}

void Sceenbase::goPrevMoved()
{

    if (m_bRight==true){
        picMoved->setPos(0,0);
        int tpos=m_parentLeft;
//        if(this->isMaximized()||this->isFullScreen())
//            tpos=0;
        int w=(m_parentWidth/2)-(m_pWith-10);
        if (w<0)
            w=0;
        int    wx = QCursor::pos().x()-tpos-w;
        if (wx<40)
            return;
        m_difer=912-wx;
        moveRightToLeft();
    }
}

void Sceenbase::moveRightToLeft()
{

   int with=m_pWith*2;

    QPixmap   pix1(with,m_pHieght);
    pix1.fill(Qt::transparent);
    QPainter p;
    p.begin(&pix1);
    p.drawPixmap(with-(m_difer),0,m_difer/2,m_pHieght,m_pixLeftMoved,0,0,m_difer/2,m_pHieght);
    p.drawPixmap(with-(m_difer/2),0,m_difer/2,m_pHieght,m_pixRigtMoved,m_pWith-(m_difer/2),0,m_difer/2,m_pHieght);
    p.setPen(QColor(128,128,128,200));
    p.drawPixmap((with-(m_difer/2))-52,0,80,m_pHieght,QPixmap(":/img/refletRight.png"));
    p.drawLine(with-(m_difer),0,with-(m_difer),m_pHieght);
    p.end();
    picMoved->setPixmap(pix1);
}

void Sceenbase::setHifdh(bool hifdh)
{
    m_isHifdh=hifdh;
    newPages();
}
void Sceenbase::readType()
{
    //رسم ازرار على الايات
    QString lineLeft=myListSafhat.at(safhaLeft);
    QString lineRight=myListSafhat.at(safhaRight);

    int countRight=lineRight.count("|");
    int countLeft=lineLeft.count("|");

    //    QPixmap mypix(28,28);
    //    mypix.fill(Qt::transparent);
    //     updatePixSelect(hight,x1,x2);

    //   int height=0;

    //   int height=0;
    //--------------ازرار الصفحة اليمنى
    int xold=430;
    int yold=60;
    int itemIndex=-1;
    for (int r=0;r <countRight+1 ;r++){
        itemIndex=r;
        QString txt=lineRight.section("|",r,r).trimmed();
        QString id =txt.section(",",0,0).trimmed();
        int mx =txt.section(",",1,1).trimmed().toInt();
        int my =txt.section(",",2,2).trimmed().toInt();
        int height=my-yold;
        ButtonG *item = new ButtonG(QPixmap());
        buttons << item;
        QPixmap pix(updatePixSelect(height+40,mx-12,xold-8,0,itemIndex));
        //type  0=button 1=selection 2=mask
        item->setPixmap(pix);
      this->addItem(item);
        item->setGeometry(QRectF((m_pWith+40),yold-14,pix.width(),pix.height()-4));
        item->setCursor(Qt::PointingHandCursor);
        item->setData(0,id);
        item->setOpacity(0.01);
        xold=mx-4;
        yold=my;
        connect(item, SIGNAL(release()), this, SLOT(goAyaSelected()));
        connect(item, SIGNAL(enter()), this, SLOT(itemAyaEntered()));
        connect(item, SIGNAL(leave()), this, SLOT(itemAyaLived()));
    }
    //-------------ازرار الصفحة اليسرى
    xold=430;
    yold=60;
    for (int r=0;r <countLeft+1 ;r++){
        itemIndex++;
        QString txt=lineLeft.section("|",r,r).trimmed();
        QString id =txt.section(",",0,0).trimmed();
        int mx =txt.section(",",1,1).trimmed().toInt();
        int my =txt.section(",",2,2).trimmed().toInt();
        int height=my-yold;
        ButtonG *item = new ButtonG(QPixmap());
        buttons << item;
        QPixmap pix(updatePixSelect(height+40,mx-14,xold-14,0,itemIndex));
        item->setPixmap(pix);

      this->addItem(item);

        item->setGeometry(QRectF(40,yold-14,pix.width(),pix.height()-4));
        item->setCursor(Qt::PointingHandCursor);
        item->setData(0,id);
        item->setOpacity(0.01);
        xold=mx-4;
        yold=my;
        connect(item, SIGNAL(release()), this, SLOT(goAyaSelected()));
        connect(item, SIGNAL(enter()), this, SLOT(itemAyaEntered()));
        connect(item, SIGNAL(leave()), this, SLOT(itemAyaLived()));
    }

}

void Sceenbase::hifdhType()
{


    itemSelection->setVisible(false);
    panelPopup->setVisible(false);
   // emit popupVisible(false);


    //رسم ازرار على الايات
    QString lineLeft=myListSafhat.at(safhaLeft);
    QString lineRight=myListSafhat.at(safhaRight);

    int countRight=lineRight.count("|");
    int countLeft=lineLeft.count("|");

    QPixmap mypix(28,28);
    mypix.fill(Qt::transparent);
//     updatePixSelect(hight,x1,x2);

 //   int height=0;

    //   int height=0;
       //--------------ازرار الصفحة اليمنى
    int xold=430;
    int yold=60;
    int itemIndex=-1;
    for (int r=0;r <countRight+1 ;r++){
        itemIndex=r;
           QString txt=lineRight.section("|",r,r).trimmed();

           int mx =txt.section(",",1,1).trimmed().toInt();
           int my =txt.section(",",2,2).trimmed().toInt();
          int height=my-yold;
          ButtonG *item = new ButtonG(QPixmap(),panelParent);
         buttons << item;
            QPixmap pix(updatePixSelect(height+40,mx+12,xold-8,2,itemIndex));
 //type  0=button 1=selection 2=mask
            item->setPixmap(pix);
      //    this->addItem(item);

          item->setGeometry(QRectF((m_pWith+42),yold-20,pix.width(),pix.height()));
           item->setCursor(Qt::PointingHandCursor);
 //   item->setZValue(95-itemIndex);

           xold=mx-4;
           yold=my;
           connect(item, SIGNAL(release()), this, SLOT(itemHifdhCliked()));
     connect(item, SIGNAL(enter()), this, SLOT(itemHifdhEntered()));
       connect(item, SIGNAL(leave()), this, SLOT(itemHifdhLived()));
       }
    //-------------ازرار الصفحة اليسرى
     xold=430;
     yold=60;
    for (int r=0;r <countLeft+1 ;r++){
        itemIndex++;
        QString txt=lineLeft.section("|",r,r).trimmed();

        int mx =txt.section(",",1,1).trimmed().toInt();
        int my =txt.section(",",2,2).trimmed().toInt();
       int height=my-yold;
       ButtonG *item = new ButtonG(QPixmap(),panelParent);
      buttons << item;
         QPixmap pix(updatePixSelect(height+40,mx+12,xold-6,2,itemIndex));
          //type  0=button 1=selection 2=mask
item->setPixmap(pix);
   // item->setZValue(95-itemIndex);
   //     this->addItem(item);

       item->setGeometry(QRectF((40),yold-20,pix.width(),pix.height()));
        item->setCursor(Qt::PointingHandCursor);


        xold=mx-4;
        yold=my;
  connect(item, SIGNAL(pressed()), this, SLOT(itemHifdhCliked()));
  connect(item, SIGNAL(enter()), this, SLOT(itemHifdhEntered()));
  connect(item, SIGNAL(leave()), this, SLOT(itemHifdhLived()));
    }
}
void Sceenbase::itemHifdhCliked()
{
    ButtonG *currentItem= qobject_cast<ButtonG *>(sender());
        currentItem->setOpacity(0.0 );

}

void Sceenbase::itemHifdhEntered()
{

     ButtonG *currentItem= qobject_cast<ButtonG *>(sender());
     if(currentItem->opacity()==0.0)
         return;


     QPropertyAnimation * anim = new QPropertyAnimation(currentItem, "opacity");

       //  anim->setStartValue(QPointF(x, -(ptop+50)));
        anim->setEndValue(0.3);
       anim->setEasingCurve(QEasingCurve::InQuint);
       anim->setDuration(1000);
       anim->start();
}

void Sceenbase::itemHifdhLived()
{

     ButtonG *currentItem= qobject_cast<ButtonG *>(sender());
     if(currentItem->opacity()==0.0)
         return;

     QPropertyAnimation * anim = new QPropertyAnimation(currentItem, "opacity");

         anim->setEndValue(1.0);
         anim->setDuration(750);
         anim->start();
}


