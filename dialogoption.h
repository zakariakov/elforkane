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
#ifndef DIALOGOPTION_H
#define DIALOGOPTION_H

#include <QDialog>
#include <QWidget>
#include <QLineEdit>
#include <QAbstractButton>
#include <QKeyEvent>
class  LineEdit : public QLineEdit
{
    Q_OBJECT
public:
     LineEdit(QWidget* parent=0)
         : QLineEdit(parent)
{
     }

protected:
void keyReleaseEvent(QKeyEvent *)
{

         txtControl=QString::null;
}
void keyPressEvent(QKeyEvent *event)
{
    if (    event->key()==Qt::Key_AltGr||event->key()==Qt::Key_Print||
            event->key()==Qt::Key_CapsLock||event->key()==Qt::Key_NumLock||
              event->key()==Qt::Key_Return||event->key()==Qt::Key_Enter)

        return;

     if (event->key()==Qt::Key_Control){
        txtControl="Ctrl+";
        return;
    }
    if (event->key()==Qt::Key_Shift){
        txtControl="Shift+";
        return;
    }
    if (event->key()==Qt::Key_Alt){
        txtControl="Alt+";
        return;
    }
    if (event->key()==Qt::Key_Meta){
        txtControl="Meta+";
        return;
    }
      QKeySequence key=event->key();
       QString txt=key.toString();
    this->setText(txtControl+txt);
    txtControl=QString::null;
  //this->setText(txtControl);
}

private:
QString txtControl;
    };

namespace Ui {
    class DialogOption;
}

class DialogOption : public QDialog
{
    Q_OBJECT
protected:

public:
    explicit DialogOption(QWidget *parent = 0);
    ~DialogOption();


    bool restoreDefaults;


    QStringList listShortcuts;

public slots:

    //************
    void setShortcutsList(QStringList list);

    void setAutoPlayNext(bool playNext);
    bool getAutoPlayNext();

    void setautoRepeatSura(bool repeatSura);
    bool getautoRepeatSura();

    void setAutoRepeatPage(bool repeatPage);
    bool getAutoRepeatPage();

    void setAutoRepeatOne(bool repeatOne);
    bool getAutoRepeatOne();

    void setAutoRepeatFromTo(bool repeatFromTo);
    bool getAutoRepeatFromTo();

    void setRepeatNumber(bool isRepeat);
    bool  getRepeatNumber();

    void setNumberRepeats(int number);
    int  getNumberRepeats();


    int getRepeatAyaFirst();
    int getRepeatAyaLast();

    void setSpinMax(int number);

    void setInfoDely(int number);
    int getInfoDely();

    void setCurTab(int number);

    void setAnimEnabled(bool anim);
    bool getAnimEnabled();

    void setFitInView(bool fit);
    bool getFitInView();

    void setMinimizToTry(bool minimiz);
    bool getMinimizToTry();

    void setTextInIcons(bool textIcons);
    bool getTextInIcons();

    void setShowMediaControl(bool show);
    bool getShowMediaControl();

    void setLng(QString language);
    QString getLng();

    void setCadrFolder(QString folder);
    QString getCadrFolder();

    void setAppPath(QString path);

    void setSelectColor(QColor color);
    QColor getSelectColor();

    void setShowMenu(bool show);
    bool getShowMenu();

    void setShowSelection(bool show);
    bool getShowSelection();

    void setReciteBasmala(bool recite);
    bool getReciteBasmala();

    void setFullSceenAnimated(bool Animated);
    bool getFullSceenAnimated();

    void setListFullSceen(QList<QString > listSceenName, int index);

    void setCurentLocale(int locale);
    int getCurentLocale();

  //  int getFullIndex();

    void setshowStandardTool(bool show);
    bool getshowStandardTool();

//    void setSaveMediaLoaded(bool save);
//    bool getSaveMediaLoaded();
    void setfullbackgroundDir(QString folder);
    QString getfullbackgroundDir();


private slots:
    void on_spinBoxFrom_valueChanged(int arg1);

    void on_buttonBox_accepted();

    void on_comboBoxLanguage_activated(int );

    void on_pushButtonColor_clicked();

    void on_toolButtonFullOption_clicked();

    void on_comboBoxNumber_activated(int );

    void on_checkBoxStandardTool_clicked();

    void on_treeWidget_itemSelectionChanged();

    void on_buttonBoxKey_clicked(QAbstractButton *button);

    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::DialogOption *ui;

    LineEdit *lineEdit;
    QString appPath;
    QColor selectColor;
};

#endif // DIALOGOPTION_H
