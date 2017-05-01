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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QMainWindow>
//#include "network.h"
#include "database.h"
#include "sceenbase.h"
#include "fs-wallpapers/fullscreen.h"
#include <QtGlobal>
#include <QSystemTrayIcon>
#include <QSpinBox>
#include <QProgressBar>
#include <QToolButton>

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include "playermultimedia.h"
#else
#include "player.h"
#endif


QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QSlider)
QT_FORWARD_DECLARE_CLASS(QAbstractButton)
QT_FORWARD_DECLARE_CLASS(QWinTaskbarButton)
QT_FORWARD_DECLARE_CLASS(QWinTaskbarProgress)
QT_FORWARD_DECLARE_CLASS(QWinThumbnailToolBar)
QT_FORWARD_DECLARE_CLASS(QWinThumbnailToolButton)

///--------------------------Pixmap-------------------------------

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Database *database;
    Sceenbase *sceenbase;
//    netWork *NetWork;

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
PlayerMultimedia *mPlayer;
#else
Player *mPlayer;
#endif

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //slot for terminal
    void setPage(int page);
    void setSora(int sora);
    void setJozaa(int jozaa);
    void setHizb(int hizb);
    void setAya(int sora,int aya);
      bool m_plaOne;
    void   toggleFullScreen();
    bool m_minimizToTry;//تصغير بجانب الساغة
    void mediaPlay();//القراءة

protected:

    void resizeEvent ( QResizeEvent *);

    void moveEvent ( QMoveEvent *  );
    bool eventFilter(QObject *obj, QEvent *ev);
    void changeEvent(QEvent *e);
    virtual void closeEvent(QCloseEvent *e );

signals:
    void popupVisible(bool );

private slots:

    bool mediaPlayInLocale(QString dirPath);
    bool mediaPlayAyat(QString dirPath);
    void mediaPlayInNetwork();
 //   QPixmap disignePage(QString safha);
    //! [ انشاء ادوات البرنامج]
    void setupToolbarIcons();//انشاء الادوات
 //     void creatMediaControles();  //انشاء لوحة ادوات الوسائط المتحركة
  void actMediaExec();
  void comboMediaExec();
    void chargeDataTools();//تحميل البيانات على الادوات
    void menuTefsirAndTranslation();

    //systry
    void  createTrayIcon();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void showMessage();
    void setshowInfo(bool show);

    //! [setting]
    void loadSetting();
    void saveSetting();
    void stupActionsShortcuts();

    //! [التنقل الى اماكن محددة]
    void setCurentPos(int pos);    //الانتقال الى الموضع المحدد
    //slot for spin
    void goAya();
    void goJozaa();
    void goHizb();
    void goPage();
    void goSura(int index);//الذهاب الى السورة المحددة


   // void goAyaSelected();//الذهاب الى الاية المحددة عند النقر على الاية

    //! [animation]
    //لحركة التلقائية عند تغيير الصفحات
//    void animPageRight();//تحريك الي لليمين
//    void animPageLeft();//تحريك الي لليسار

    void moveSelection(int top,int hight,int x1,int x2); //تحريك التحديد الى الموضع الجديد
  void fullScreenPixmap(int top,int high,int x1,int x2);//استخراج نص الاية الحالية لوضعية ملء الشاشة

    //! [phonon]
     void mediaFinished();//انتهاء القراءة

    //! [phononEffect]

    //! [generale]
    void getOption(int tab,QString title);
    void locateThemePath();    //التحقق من مسارات الصور للسمة ان كانت موجودة
    void hidePopup();
   // void newPages();//رسم صفحات جديدة
    void convertTextToHtm(QString text);
    void chargeLastAndFirstAya();//معرفة اول واخر اية سواء في الصفحة او السورة
    void setSpinAyaMaximum(int index);
    void translationChanged();
    void tefsirChanged();
    void txtQuran();

    //! [actions]
    void on_actionNextPage_triggered();

    void on_actionPrevPage_triggered();

    void on_actionNextSura_triggered();

    void on_actionPrevSura_triggered();

    void on_actionNextAya_triggered();

    void on_actionPrevAya_triggered();

    void on_actionOptions_triggered();

    void on_actionFullScreen_triggered();



    void on_actionAddReceter_triggered();

    void on_actionRemoveReceter_triggered();//حذف المقرئ المحدد

    void on_actionAbout_triggered();

    void on_actionQuranText_triggered();

    void on_actionEditeReceter_triggered();

    void on_actionRceterEdite_triggered();

    void editReciter();//تحرير المقرئ

    void on_actionRepeatOption_triggered();

    //other tools

    void comboBoxResiter_activated(int index);

    void comboBoxSoraJozaa_currentIndexChanged(int index);

    void treeWidgetIndex_itemActivated(QTreeWidgetItem *item, int );

    void lineEditSearchTree_textChanged(const QString &arg1);

    void popup_toggled(bool checked);

    void on_graphicsView_customContextMenuRequested(const QPoint );

    void on_actionNavigation_toggled(bool arg1);

    void on_toolButtonGoSearch_clicked();

    void on_treeWidgetSearch_itemActivated(QTreeWidgetItem *item, int );

    void on_lineEditSearch_returnPressed();

    void on_lineEditSearchAnd_returnPressed();

    void on_actionEnableAnimFull_toggled(bool arg1);

void on_actionMemoriz_triggered(bool checked);
//void desableHifdhPage();

void runtimerScreen();
//void on_actionScriptDownload_triggered();


void createTaskbar();
void createThumbnailToolBar();
void updateThumbnailToolBar();



void on_actionPlayPause_triggered();

void on_actionQuit_triggered();

void on_actionStopMedia_triggered();

private:
    Ui::MainWindow *ui;

   // QTextEdit *textEdit;
     QStringList listShortcut;
    QLabel *labelTransTefsir;
    //متغيرات البرنامج
    bool m_animEnabled;
     bool m_fitInView;
    bool m_showPopup;
    bool m_autoRepeatSura;
    bool m_autoRepeatPage;
    bool m_autoRepeatOne;
    bool m_autoRepeatFromTo;
    bool m_autoPlayNext;

    bool isPlay;//هل القراة تشتغل
    bool m_showInfo;//عرض المعلومات بجانب الساعة
     bool m_textIcon;
    bool m_isRepeatNumber;
    bool m_showMediaControl;
    bool isTefsirPopup;
    bool m_showMenu;
    bool m_showSelection;
    bool m_reciteBasmala;
    bool m_standardTool;
    int m_id; //الموضع الحالي
    int m_sura; //رقم السورة الحالية
    int m_aya; //رقم الاية الحالية
    int m_jozaa; //رقم الجزء الحالي
    int m_hizb; //رقم الحزب الحالي
    int m_robaa; //رقم الربع الحالي
 //   int m_pHieght; //طول الصفحة
  //  int m_pWith;  //عرض الصفحة
bool m_restoreDefaults;
    int m_curentSafha;  //الصفحة الحالية المحددة
//    int m_difer; //الفرق بين الصفحة اليسرة واليمنى عند تحريك الصفحة بواسطة المؤشر
    int m_px; // موضع الصور س
    int m_numPlayed; //   مرات القراءة حتى الان
    int m_repeatNumber; // عدد التكرار
    int m_receter; //المقرئ
    int m_repeatAyaFirst; //اول الاية في الصفحة او السورة
    int m_repeatAyaLast;//اخر الاية في الصفحة او السورة
    int m_infoDely;//مدة بقاء المعلومة في ايقونة النظام
    int m_curTranslation;// الترجمة الحالية
    int m_locale;
bool m_saveMediaLoaded;
    QString m_curentRiwaya;

    //---------------------------------
    bool m_fullAnimEnable;//تفعيل الحركة في وضع ملء الشاشة
 QString m_fullbackgroundDir;
 bool m_fullAnimated;
 //int m_fullIndex;
// void loadPlugin();
//    QList<SceenFullInterface *>myListSceen;
//    QList<QString > listSceenName;
//-----------------------------------
QList<QAction *>myListActionTrans;
    QString m_lng;//اللغة الحالية
    QString m_appPath;//مسار بينات البرنامج
 //   QString m_y;
    QString m_soundName;
    QString m_themeFolder;//مجلد السمة
    QString m_soundPath; //مسار الصوت الحالي
    QString m_soundUrl;//موقع الصوت الحالي
    QString m_layouDir;//اتجاه البرنامج
    QColor m_selectColor;//لون التحديد
    //Phonon

    QProgressBar *progress;

    //------systry-----
    QSystemTrayIcon *trayIcon;
    QAction *actionMinimiz;
    QAction *actionRestore;
    QAction *actionSowInfo;

    //---------tool in toolbar
    QComboBox *comboSura;                               //القائمة المنسدلة للسور
    QSpinBox *spinAya;                                            //اداة ادخال رقم الاية
    QSpinBox *spinJozaa;                                            //اداة ادخال رقم الجزء
    QSpinBox *spinHizb;                                            //اداة ادخال رقم الحزب
    QSpinBox *spinSafha;                                            //اداة ادخال رقم الصفحة
    QAction *actTansTefsir;                                    //زر عرض قائمة التفاسير والتراجم
      QComboBox *comboBoxReciter;                //القائمة المنسدلة للمقرئين

 QToolButton *btnMenu;

 QAction *actMediaSafha;
QAction *actMediaSura;
QAction *actMediaAya;
QAction *actMediaJozaa;
QAction *actMediaHizb;
QAction *actMediaReciter;

int oldCurPos;
QTimer *timerScreen;

SceenFull *mSceenFull;

/*
QWinTaskbarButton* taskbarButton;
QWinTaskbarProgress* taskbarProgress;
QWinThumbnailToolBar* thumbnailToolBar;
QWinThumbnailToolButton *playToolButton;
QWinThumbnailToolButton *forwardToolButton;
QWinThumbnailToolButton *backwardToolButton;
*/

};

#endif // MAINWINDOW_H
