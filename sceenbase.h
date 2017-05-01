#ifndef SCEENBASE_H
#define SCEENBASE_H
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsWidget>
//#include<QtGui>
#include <QGraphicsWidget>
#include <QPainter>
#include <QLocale>
#include <QTextEdit>
#include <QLabel>
#include <QLabel>
#include <QToolBar>
class ButtonG : public QGraphicsWidget
{
    Q_OBJECT

public:
    ButtonG(const QPixmap &pix, QGraphicsItem *parent = 0)
        : QGraphicsWidget(parent), orig(pix), p(pix)
    {

  setCacheMode(DeviceCoordinateCache);
        setAcceptHoverEvents(true);
    }

    QPainterPath shape() const
    {

 //  path.addEllipse(boundingRect());
        //path.addRect(0,0, 100, 100);
  //    path.addRect(20,20,250,250);
        return path;
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
    {
        painter->drawPixmap(QPointF(), p);
    }

    virtual void setGeometry(const QRectF &rect)
    {
        QGraphicsWidget::setGeometry(rect);
   p = orig.scaled(rect.size().toSize());
//        if (rect.size().width() > orig.size().width())
//            p = orig.scaled(rect.size().toSize());
//        else
//            p = orig;
    }
    virtual void setPixmap(QPixmap pix)
    {
             orig=pix;
    }
     void setPath(QPainterPath pt)
    {
             path=pt;
    }
signals:
    void pressed();
    void release();
    void enter();
    void leave();
 void mouseMove();

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *)
    {
        emit pressed();
        update();
    }
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *)
    {
        emit release();
        update();
    }
    void hoverEnterEvent(  QGraphicsSceneHoverEvent *)
    {

        emit enter();
        update();

    }
    void hoverLeaveEvent ( QGraphicsSceneHoverEvent  *)
    {
        emit leave();
        update();
    }
        void mouseMoveEvent(QGraphicsSceneMouseEvent *)
        {
            emit mouseMove();
            update();
        }

private:
    QPixmap orig;
    QPixmap p;
 QPainterPath path;
};

class PixmapS : public QGraphicsWidget
{
    Q_OBJECT

public:
    PixmapS(const QPixmap &pix, QGraphicsItem *parent = 0)
        : QGraphicsWidget(parent), orig(pix), p(pix)
    {

  setCacheMode(DeviceCoordinateCache);
        setAcceptHoverEvents(true);
    }


    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
    {
        painter->drawPixmap(QPointF(), p);
    }

    virtual void setGeometry(const QRectF &rect)
    {
        QGraphicsWidget::setGeometry(rect);
   p = orig.scaled(rect.size().toSize());
//        if (rect.size().width() > orig.size().width())
//            p = orig.scaled(rect.size().toSize());
//        else
//            p = orig;
    }
    virtual void setPixmap(QPixmap pix)
    {
             orig=pix;
    }

signals:
    void pressed();
    void release();
    void enter();
    void leave();
 void mouseMove();

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *)
    {
        emit pressed();
        update();
    }
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *)
    {
        emit release();
        update();
    }
    void hoverEnterEvent(  QGraphicsSceneHoverEvent *)
    {

        emit enter();
        update();

    }
    void hoverLeaveEvent ( QGraphicsSceneHoverEvent  *)
    {
        emit leave();
        update();
    }
        void mouseMoveEvent(QGraphicsSceneMouseEvent *)
        {
            emit mouseMove();
            update();
        }

private:
    QPixmap orig;
    QPixmap p;

};

class Sceenbase : public QGraphicsScene
{
    Q_OBJECT
public:
    Sceenbase( QWidget *parent=0) ;
//    Sceenbase();
    QToolBar *toolbarPopup;
    QToolBar *toolbarMedia;
    QTextEdit *textEdit;
    QStringList    myListSafhat;

signals:

    void setPos(int );

public slots:
    void setAppPath(QString path);

    void setwinLocal(QLocale arg);
    void setMoveSelection(int top,int hight,int x1,int x2, int px);

   // void setCurentPages(int left,int right,int curent);
  void setCurentPages(int   safha,int y, bool istafsir);
    void setPage(int p);
    void updatPopup(qreal poY,qreal poX1,qreal poX2,int px,bool istefsir);
    void setParentSize(int with,int hieght,int x);
    void setParentLeft(int x);
     void setHifdh(bool hifdh);
     void setPopupVisible(bool visible);
 void setMediaControleVisible(bool visible);
     void setColorSelection(QColor color);
     void setThemeFolder(QString themeFolder);
     void setRewayat(QString rewayat);
     void setAnimationEnabled(bool enabled);
     void setStandardTools(bool st);
     void setShowSelection(bool show);
     void updatePages();
private:
    //sceen object
    QPixmap m_pixRigtMoved;
    QPixmap m_pixLeftMoved;

    QGraphicsPixmapItem *picMoved;
    PixmapS * itemRefletLeft;
    PixmapS * itemRefletRigt;
    PixmapS * btnLeft;    //زر على الصفحة اليسرى لسحب الصفحة
    PixmapS * btnRight;   //زر على الصفحة اليمنى لسحب الصفحة
    PixmapS * btnMedia;// زر عرض واخفاء لوحة ادوات الوسائط
    QGraphicsPixmapItem *pageLeft;//مربع الصفحة اليسرى
    QGraphicsPixmapItem *pageRight;//مربع الصفحة اليمنى
    PixmapS *itemSelection;  //مربع التحديد
    QGraphicsWidget  *panelParent ;
    QGraphicsWidget  *panelPopup ;
    QGraphicsWidget  *panelMedia;
    QGraphicsWidget  *panelNavig;
    QGraphicsPixmapItem *ItemPopup;
  QGraphicsPixmapItem   * ItemPopupBlure;
    QLabel *m_labMask;
    QList<PixmapS *> items;
    QList<ButtonG *> buttons;
 //   QLabel *labelTransTefsir;
    //--variable--
    int  m_pHieght;
    int m_pWith;
    int m_px; // موضع الصور س
//    bool isTefsirPopup;//--------------------------------------------------------------------------------move to public
    QString m_curentRiwaya;
    QString m_themeFolder;

    QColor m_selectColor;
    bool m_animEnabled;

     bool m_showSelection;
    bool m_showPopup;
    //----privat
    QString appPath;
    QLocale Lc;
    QStringList    myListArbaa;

    int m_difer;
    bool m_standardTool;
    int safhaLeft;
    int safhaRight;
    int safhaCurent;
    bool m_bLeft;  //اذا كان التحريك لليسار مفعل
    bool m_bRight;  //اذا كان التحريك لليمين مفعل

    int m_parentHeight;
    int m_parentWidth;
    int m_parentLeft;
bool m_isHifdh;
private slots:
void animePageLeft();
void animePageRight();
    void openData();
    void creatPagesAndPopup();
    void creatMediaControles();
    void  moveMediaControle();
        void newPages();
   QPixmap disignePage(QString safha);
    QPixmap updatePixSelect(int h,int x1 ,int x2,int type,int item);

    void goAyaSelected();
    void itemAyaEntered();
    void itemAyaLived();

    //go left to right عند سحب الصفحة الى اليمين
    void goNextEenter();//عند ادخال مؤشر الفأرة على الحافة اليسرى
    void goNextLeave();//عند خروج مؤشر الفأرة من الحافة اليسرى
    void goNextPrissed( );//عند نقر  مؤشر الفأرة على الحافة اليسرى
    void goNextMoved();//عند تحريك  مؤشر الفأرة من الحافة اليسرى
    void goNextRelease( );//عند ارسال  مؤشر الفأرة من الحافة اليسرى
    void moveLeftToRight();// تحريك الصفحة بواسطة مؤشر الفأرة نحوى اليمين
    // go right to left عند سحب الصفحة الى اليسار
    void goPrevEenter();//عند ادخال مؤشر الفأرة على الحافة اليمنى
    void goPrevLeave();//عند خروج مؤشر الفأرة من الحافة اليمنى
    void goPrevPrissed( );//عند نقر  مؤشر الفأرة على الحافة اليمنى
    void goPrevMoved();//عند تحريك  مؤشر الفأرة من الحافة اليمنى
    void goPrevRelease(  );//عند ارسال  مؤشر الفأرة من الحافة اليمنى
    void moveRightToLeft();//تحريك الصفحة بواسطة مؤشر الفأرةنحوى اليسار
//-----------------------------hifdh----------------------------------------
    void hifdhType();
    void readType();
    void itemHifdhCliked();
     void itemHifdhEntered();
   void itemHifdhLived();
};

#endif // SCEENBASE_H
