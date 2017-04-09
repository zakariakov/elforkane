#ifndef SCEENTEST_H
#define SCEENTEST_H
#include <QObject>
#include <QGraphicsScene>
#include <QParallelAnimationGroup>
#include <QLabel>
#include <QDir>
 class SceenFull : public QGraphicsScene
 {
     Q_OBJECT

 public:
     SceenFull();
     ~SceenFull();

 public slots:

     void setPixmapAya(QPixmap pix);//تحديد الاية
     void setInfo(QString sura,QString  jozaa,QString hizb,QString rbaa,QString aya,QString reciter,QString trans);
     void setAnimationEnabled(bool enable);

     void setGraphicSceen(QGraphicsView *view);
   void loadSetting();
 private slots:
     void setBackgroundDir();//تحديد صورة الخلفية

     void createSceen();
     void createBlurAya();//انشاء محتوى الاية
     void createTopPanel();
     void creatBotPanel();
     void setBackground();
     void setBackgroundBack();
     void stopAnimation();//ايقاف الحركات
    void animZekhrafaRing();//انشاء الزخرفة المتحركة
     void animBgr();
     void animAya();
     void animBlur();



 private:
     QGraphicsScene * sceen ;
     QGraphicsPixmapItem *pageAya;//محتوى الاية
     QGraphicsPixmapItem *pixBgr;//محتوى صورة الخلفية
     QGraphicsPixmapItem *pixBgrBack;
     QGraphicsWidget *panelBgr;
     QGraphicsWidget *zekhrafaRondedBot;//محتوى صورة الزخرفة السفلى
     QGraphicsWidget *zekhrafaRondedTop;//محتوى صورة الزخرفة العليا
     QGraphicsWidget *panelAya ;//محتوى اطار الاية
     QGraphicsPixmapItem *itemAya;//الاطار الذي سيرسم عليه الاطار الابيض
     QGraphicsWidget  *itemBlurAya ;
     QGraphicsWidget  *itemBlurTop ;

     QParallelAnimationGroup *group;

     QLabel *labelInfo;
     QLabel *labelTrans;
     QString  appPath;
     QString m_fullbackgroundDir;
     QList<QString> listBgr;
     int curListIndexOf;
 };

#endif // SCEENTEST_H
