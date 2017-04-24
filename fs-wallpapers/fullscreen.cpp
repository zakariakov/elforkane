#include "fullscreen.h"

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsWidget>
#include <QDesktopWidget>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QDebug>
#include <QSettings>

SceenFull::SceenFull()
{
    this->setObjectName(trUtf8("wallpapers-fullscreen"));
    QDir appDir(qApp->applicationDirPath());

#if defined(Q_OS_WIN)

    //  if (appDir.dirName().toLower() == "debug" || appDir.dirName().toLower() == "release")
    appDir.cdUp();
    appPath=  appDir.absolutePath()+"/share/elforkane";
#elif defined(Q_OS_MAC)
    if (appDir.dirName() == "MacOS") {
        appDir.cdUp();
        appDir.cdUp();
        appDir.cdUp();
        appPath=  appDir.absolutePath()+"/elforkane";
    }
#else
    appDir.cdUp();
    appPath=  appDir.absolutePath()+"/share/elforkane";
    // qDebug()<<appPath;
#endif
    loadSetting();


    sceen=new QGraphicsScene;
    createSceen();
    //   setBackground();
}

SceenFull::~SceenFull()
{
    stopAnimation();

}


void SceenFull::setGraphicSceen(QGraphicsView *view)
{
    view->setScene(sceen);
    setBackgroundDir();
}

void SceenFull::createSceen()
{
    panelBgr=new QGraphicsWidget ;
    pixBgr=new QGraphicsPixmapItem(panelBgr) ;
    pixBgrBack=new QGraphicsPixmapItem ;
    zekhrafaRondedBot=new QGraphicsWidget ;
    zekhrafaRondedTop=new QGraphicsWidget ;

    panelAya=new  QGraphicsWidget;
    itemAya= new   QGraphicsPixmapItem (panelAya);
    itemBlurAya=new  QGraphicsWidget (panelAya);
    pageAya= new QGraphicsPixmapItem (panelAya);


    sceen->addItem(pixBgrBack);
    sceen->addItem(panelBgr);

    sceen->addItem(zekhrafaRondedBot);
    sceen->addItem(zekhrafaRondedTop);
    sceen->addItem(panelAya);
    createTopPanel();
    creatBotPanel();
    createBlurAya();


    animZekhrafaRing();

    listBgr.append(appPath+"/fullscreen/bgrFull.png");
    curListIndexOf=0;
}
void SceenFull::createBlurAya()
{

    QGraphicsPixmapItem * blurAya=new QGraphicsPixmapItem(itemBlurAya);
    QGraphicsPixmapItem * blurTop=new QGraphicsPixmapItem(itemBlurTop);
    QPixmap pix(50,50);

    pix.fill(Qt::transparent);
    QPainter p;

    QRadialGradient radialGrad(QPointF(25, 25), 25);
    radialGrad.setColorAt(0, Qt::white);

    radialGrad.setColorAt(0.8, Qt::transparent);
    radialGrad.setColorAt(1, Qt::transparent);
    QBrush brush(radialGrad);
    p.begin(&pix);
    p.setBrush(brush);
    p.fillRect(0, 0, 50, 50,brush);
    p.end();

    blurAya->setPixmap(pix);
    blurTop->setPixmap(pix);
    itemBlurAya->setPos(50,2);
    itemBlurTop->setPos(50,45);
}
void SceenFull::createTopPanel()
{
    int w=QApplication::desktop()->geometry().width();

    QGraphicsWidget  * panelTop=new QGraphicsWidget ;
    QGraphicsPixmapItem   *itemPanelTop= new   QGraphicsPixmapItem (panelTop);
    itemBlurTop=new QGraphicsWidget (panelTop);
    QPixmap pix(w,90);
    pix.fill(Qt::transparent);
    QPainter p;
    p.begin(&pix);

    p.fillRect(0,0,w,60,QColor(255, 255, 255, 100));
    //      p.setPen(QColor(128, 128, 128,200));
    //      p.drawLine(0,59,pix.width(),59);
    //      p.setPen(QColor(255, 255, 255,150));
    //      p.drawLine(0,58,pix.width(),58);
    //رسم زخارف في الاعلى
    QPixmap pixBot(":/image/bot.png");
    int n=(w/64)+1;
    for(int i=0;i<n;i++){
        int x=(64*i);
        p.drawPixmap(x,50,pixBot);
    }
    p.end();

    itemPanelTop->setPixmap(pix);

    QGraphicsDropShadowEffect *efet=new QGraphicsDropShadowEffect;
    efet->setOffset(0,5);
    efet->setColor((QColor(64, 64,64,255)))  ;
    efet->setBlurRadius(10);
    panelTop->setGraphicsEffect(efet);

    labelInfo=new QLabel();
    labelInfo->setGeometry(0,10,w,40);
    labelInfo->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    QString labStyle="QLabel {  font: bold 18px;color: white;background-color: rgba(255, 255, 255, 0);border: 0px;}";
    labelInfo->setStyleSheet(labStyle);

    sceen->addItem(panelTop);
    sceen->addWidget(labelInfo);
}
void SceenFull::creatBotPanel()
{
    int w=QApplication::desktop()->geometry().width();
    int h=QApplication::desktop()->geometry().height();
    QGraphicsWidget  * panelBot=new QGraphicsWidget ;
    QGraphicsPixmapItem   *itemPanelBot= new   QGraphicsPixmapItem (panelBot);
    QPixmap pix(w,90);
    pix.fill(Qt::transparent);
    QPainter p;
    p.begin(&pix);

    p.fillRect(0,30,w,60,QColor(255, 255, 255, 100));
    //      p.setPen(QColor(128, 128, 128,150));
    //      p.drawLine(0,0,pix.width(),0);

    //      p.setPen(QColor(255, 255, 255,150));
    //      p.drawLine(0,1,pix.width(),1);

    QPixmap pixtop(":/image/top.png");
    int n=(w/64)+1;
    for(int i=0;i<n;i++){
        int x=(64*i);
        p.drawPixmap(x,0,pixtop);
    }

    p.end();
    p.end();
    itemPanelBot->setPixmap(pix);
    QGraphicsDropShadowEffect *efet=new QGraphicsDropShadowEffect;
    efet->setOffset(0,-5);
    efet->setColor((QColor(63, 63, 63,200)))  ;
    efet->setBlurRadius(10);
    panelBot->setGraphicsEffect(efet);

    panelBot->setPos(0,h-90);
    labelTrans=new QLabel;
    labelTrans->setGeometry(0,h-50,w,45);
    labelTrans->setAlignment(Qt::AlignHCenter);
    labelTrans->setWordWrap(true);
    QString labStyle="QLabel { font: bold 14px;color:rgb(255, 255, 255);background-color: rgba(255, 255, 255, 0);border: 0px;}";
    labelTrans->setStyleSheet(labStyle);

    sceen->addItem(panelBot);
    sceen->addWidget(labelTrans);
}
void SceenFull::animBlur()
{

    QPropertyAnimation *anim3 = new QPropertyAnimation(itemBlurAya, "pos");
    anim3->setEasingCurve(QEasingCurve::CosineCurve);
    anim3->setDuration(5000);
    anim3->setStartValue(QPoint(400,3));
    anim3->setEndValue(QPoint(50,3));
    //anim3->start();

    QPropertyAnimation *anim4= new QPropertyAnimation(itemBlurAya, "opacity");
    anim4->setEasingCurve(QEasingCurve::CosineCurve);
    anim4->setDuration(5000);
    anim4->setStartValue(0);

    anim4->setEndValue(0.9);
    //anim4->start();

    QParallelAnimationGroup *groupBlur=new  QParallelAnimationGroup;
    groupBlur->addAnimation(anim3);
    groupBlur->addAnimation(anim4);
    groupBlur->start();
}

void SceenFull::animAya()
{
    QPropertyAnimation *anim = new QPropertyAnimation(panelAya, "opacity");
    anim->setDuration(700);
    anim->setStartValue(0.5);
    anim->setEndValue(1.0);
    anim->start();
}
void SceenFull::setInfo(QString sura,QString  jozaa,QString hizb,QString rbaa,QString aya,QString reciter,QString trans)
{


    QString mytxt=sura+ jozaa+ hizb+ rbaa+  aya+   reciter;

    labelInfo->setText( mytxt);


    labelTrans->setText(trans);
}

void  SceenFull::setPixmapAya(QPixmap pix)
{

    // pageAya->setPos(w-pw,h-ph);
    //-------------------------------------------------------------

    //  panelAya->setOpacity(0.8);
    bool pixmapExist=true;
    if (!QFile::exists(":/image/top_left.png"))
        pixmapExist=false;

    QPixmap pixmap(pix.width()+100,pix.height()+100);
    QPixmap pixTopleft(":/image/top_left.png");
    QPixmap pixTopRight(":/image/top_right.png");
    QPixmap pixTop(":/image/top.png");
    QPixmap pixBot(":/image/bot.png");
    QPixmap pixLeft(":/image/left.png");
    QPixmap pixRight(":/image/right.png");
    QPixmap pixBotleft(":/image/bot_left.png");
    QPixmap pixBotRight(":/image/bot_right.png");
    QPixmap pixDrawLeft(36,pix.height());
    QPixmap pixDrawRight(36,pix.height());
    pixDrawLeft.fill(Qt::transparent);
    pixDrawRight.fill(Qt::transparent);
    QPainter p;
    int pDH=(pix.height()/64)+1;//جلب عدد الصور بالنسبة الى الطول +1 للاحتيط
    if(pDH<=1)pDH=2;
    p.begin(&pixDrawLeft);//رسم صورة على الجهة اليسرى تقسما لطول المحتوى
    for(int i=0;i<pDH;i++){
        int h=(64*i);
        p.drawPixmap(0,h,pixLeft);

    }
    p.end();

    p.begin(&pixDrawRight);//رسم صورة على الجهة اليسرى تقسما لطول المحتوى
    for(int i=0;i<pDH;i++){
        int h=(64*i);
        p.drawPixmap(0,h,pixRight);

    }
    p.end();
    pixmap.fill(Qt::transparent);

    p.begin(&pixmap);
    p.setRenderHint(QPainter::Antialiasing,true);
    if(pixmapExist==false){
        // اذا لم تكن الصور موجودة رسم اطار شفاف حول الاية
        p.setPen(QColor(128, 128, 128,255));
        QRectF rect(0.0,0.0,pix.width()+100,pix.height()+100);
        p.drawRoundedRect(rect,9.0,9.0);//رسم مربع بالرمادي
        QRectF rect2(1.0,1.0,pix.width()+97,pix.height()+97);
        p.setPen(QColor(255, 255, 255,255));
        p.setBrush(QColor(255, 255, 255, 80));//رسم لون شفاف على المساحة
        p.drawRoundedRect(rect2,7.0,7.0);//رسم مربع بالابيض نقطة بعد الرمادي
    }
    //رسم رخارف حول الاية
    p.drawPixmap(14,14,pixTopleft);//رسم صورة على الجهة العليا اليسرى
    p.drawPixmap(pix.width()+51,14,pixTopRight);//رسم صورة على الجهة العليا اليمنى
    p.drawPixmap(14,pix.height()+50,pixBotleft);//رسم صورة على الجهة السفلى اليسرى
    p.drawPixmap(pix.width()+51,pix.height()+50,pixBotRight);//رسم صورة على الجهة العليا اليمنى

    for(int i=0;i<6;i++){//رسم صورة على الجهة العليا و السفلى 6مرات
        int x=(64*i)+50;
        p.drawPixmap(x,14,pixTop);
        p.drawPixmap(x,pix.height()+50,pixBot);
    }
    p.drawPixmap(14,50,pixDrawLeft);//رسم صورة على الجهة اليسرى
    p.drawPixmap(pix.width()+51,50,pixDrawRight);//رسم صورة على الجهة اليسرى

    p.end();

    itemAya->setPixmap(pixmap);
    int w=QApplication::desktop()->geometry().width()/2;
    int h=(QApplication::desktop()->geometry().height())/2;
    int pw=(pix.width()+100)/2;
    int ph=(pix.height()+100)/2;
    panelAya->setGeometry(w-pw,h-ph,pix.width()+100,pix.height()+100);
    QGraphicsDropShadowEffect *efet=new QGraphicsDropShadowEffect;
    efet->setOffset(8,8);
    efet->setColor((QColor(63, 63, 63,150)))  ;
    efet->setBlurRadius(25);
    panelAya->setGraphicsEffect(efet);

    pageAya->setPixmap(pix);
    pageAya->setPos(50,50);
    setBackground();
    //  animAya();
    animBlur();

}
void SceenFull::setBackgroundDir()
{
    /*
    int w=QApplication::desktop()->geometry().width();
    int h=QApplication::desktop()->geometry().height();
      QPixmap pix(w,h);


              QLinearGradient linearGrad(QPointF(w, 0), QPointF(w, h));
                  linearGrad.setColorAt(0,QColor(167, 186, 156, 255));
                  linearGrad.setColorAt(1, QColor(47, 62, 39, 255));
              QPainter p;
     p.begin(&pix);
         p.fillRect(pix.rect(),linearGrad);
     p.drawPixmap(0,0,w,h,QPixmap(fileName));
     p.end();
  pixBgr->setPixmap(pix);
  */
    //listBgr.add filename
    //pixBgrBack->setPixmap(pix);
    listBgr.clear();

    QDir dirS(m_fullbackgroundDir);
    QString subfile;

    foreach ( subfile, dirS.entryList(QDir::Files|QDir::NoDotAndDotDot)){
        QFileInfo fi(m_fullbackgroundDir+"/"+subfile);
        QString ext = fi.suffix();
        if(ext=="png"||ext=="jpg"||ext=="PNG"||ext=="JPG"){
            listBgr.append(m_fullbackgroundDir+"/"+subfile);
            //  qDebug()<<m_fullbackgroundDir+"/"+subfile;
        }
    }
    qDebug()<<"listcount"+QString::number(listBgr.count());
    if(listBgr.count()==0)
        listBgr.append(appPath+"/fullscreen/bgrFull.png");
    curListIndexOf=0;
    setBackground();
}
void  SceenFull::setBackground()
{
    int w=QApplication::desktop()->geometry().width();
    int h=QApplication::desktop()->geometry().height();

    panelBgr->setOpacity(0);
    QString curBgr;
    if(listBgr.count()>0)
        curBgr=   listBgr.at(curListIndexOf);

    QPixmap pix(w,h);
    pix.fill(Qt::transparent);
    QPainter p;
    p.begin(&pix);
    p.drawPixmap(0,0,w,h,QPixmap(curBgr));
    p.end();

    pixBgr->setPixmap(pix);
    animBgr();

}

void  SceenFull::setBackgroundBack()
{
    QString curBgr;
    if(listBgr.count()>0)
        curBgr=   listBgr.at(curListIndexOf);

    // qDebug()<<curBgr;
    //qDebug()<<"listcounted"+QString::number(listBgr.count());
    int w=QApplication::desktop()->geometry().width();
    int h=QApplication::desktop()->geometry().height();
    QPixmap pix(w,h);
    pix.fill(Qt::transparent);
    QPainter p;
    p.begin(&pix);
    p.drawPixmap(0,0,w,h,QPixmap(curBgr));
    p.end();
    pixBgrBack->setPixmap(pix);
    int i=listBgr.count()-1;
    curListIndexOf++;
    if(curListIndexOf>i)
        curListIndexOf=0;
}

void SceenFull::animBgr()
{
    QPropertyAnimation *anim = new QPropertyAnimation(panelBgr, "opacity");
    anim->setDuration(1000);
    anim->setStartValue(0.0);
    anim->setEndValue(1.0);
    connect(anim, SIGNAL(finished()), this, SLOT(setBackgroundBack()));
    anim->start();
}

void  SceenFull::animZekhrafaRing()
{



    int h=(QApplication::desktop()->geometry().height());
    int w=(QApplication::desktop()->geometry().width());
    //الزخرفة الدائرية على الجهة السفلى
    QPixmap pix(":/image/ringBot.png");
    QGraphicsPixmapItem *zekhrafa=new QGraphicsPixmapItem(zekhrafaRondedBot);
    zekhrafa->setPixmap(pix);

    int ph=pix.height()/2;
    zekhrafaRondedBot->setPos(-ph,h-ph);
    zekhrafaRondedBot->setOpacity(0.70);
    zekhrafaRondedBot->setTransformOriginPoint(ph,ph);
    QPropertyAnimation  *anim1 = new QPropertyAnimation(zekhrafaRondedBot, "rotation");
    anim1->setDuration(20000);
    anim1->setStartValue(0);
    anim1->setEndValue(360);

    //الزخرفة الدائرية على الجهة اعليا
    QPixmap pix2(":/image/ringTop.png");
    QGraphicsPixmapItem *zekhrafa2=new QGraphicsPixmapItem(zekhrafaRondedTop);
    zekhrafa2->setPixmap(pix2);

    int ph2=pix2.height()/2;
    int pw=pix2.width()/2;
    zekhrafaRondedTop->setPos(w-pw,-ph2);
    zekhrafaRondedTop->setOpacity(0.70);
    zekhrafaRondedTop->setTransformOriginPoint(QPointF(ph2,pw));
    QPropertyAnimation *anim2 = new QPropertyAnimation(zekhrafaRondedTop, "rotation");
    anim2->setDuration(20000);
    anim2->setStartValue(360);
    anim2->setEndValue(0);
    //    anim2->setLoopCount(-1);
    QPropertyAnimation *anim3 = new QPropertyAnimation(itemBlurTop, "pos");
    anim3->setEasingCurve(QEasingCurve::CosineCurve);
    anim3->setDuration(20000);
    anim3->setStartValue(QPoint(w-50,45));
    anim3->setEndValue(QPoint(50,45));
    //anim3->start();

    QPropertyAnimation *anim4= new QPropertyAnimation(itemBlurTop, "opacity");
    anim4->setEasingCurve(QEasingCurve::SineCurve);
    anim4->setDuration(20000);
    anim4->setStartValue(0);

    anim4->setEndValue(0.9);

    group=new  QParallelAnimationGroup;
    group->addAnimation(anim1);
    group->addAnimation(anim2);
    group->addAnimation(anim3);
    group->addAnimation(anim4);
    group->setLoopCount(-1);
}

void SceenFull::stopAnimation()
{
    group->stop();
}
void SceenFull::setAnimationEnabled(bool enable)
{

    if(enable==true){
        group->start();
    }else{
        group->stop();
    }

}


void SceenFull::loadSetting()
{
    QSettings settings(QDir::homePath()+"/.elforkane/setting.ini",QSettings::IniFormat);

    settings.beginGroup("Main");
    m_fullbackgroundDir=settings.value("fullbackgroundDir",appPath+"/fullscreen/bgrFull.png").toString();
    settings.endGroup();
}


