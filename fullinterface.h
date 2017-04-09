#ifndef SCEENINTERFACE_H
#define SCEENINTERFACE_H
#include <QObject>
#include <QtGui>
#include <QGraphicsView>
//! [0]
class SceenFullInterface
{
public:

    virtual ~SceenFullInterface() {}

    virtual  void setGraphicSceen(QGraphicsView *view)= 0;
    virtual  void  setPixmapAya(QPixmap pix)= 0;
    virtual  void  setInfo(QString sura,QString  jozaa,QString hizb,QString rbaa,QString aya,QString reciter,QString trans)= 0;
    virtual   void setAnimationEnabled(bool enable)=0;
  virtual   void execOptions()=0;

};
//! [0]



QT_BEGIN_NAMESPACE

Q_DECLARE_INTERFACE(SceenFullInterface,
                    "com.elforkane.Plugin.SceenFullInterface/1.0");


QT_END_NAMESPACE
#endif // SCEENINTERFACE_H
