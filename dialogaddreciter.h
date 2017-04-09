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
#ifndef DIALOGADDRECITER_H
#define DIALOGADDRECITER_H

#include <QDialog>
#include <QAbstractButton>
#include <QListWidget>
#include<QProcess>

namespace Ui {
    class DialogAddReciter;
}

class DialogAddReciter : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddReciter(QWidget *parent = 0);
    ~DialogAddReciter();

public slots:
void setReceterName(QString name);
void setDirName(QString name);
void setUrlName(QString name);
void setRiwayaName(QString arg);
void setListItems( QStringList list);
void setDownload(bool arg);
QString getReciterName();
QString getDataName();

private slots:
void on_toolButtonFileName_clicked();

    void on_buttonBox_clicked(QAbstractButton *button);

    void on_toolButtonDownLoad_toggled(bool checked);

    void on_pushButtonStart_clicked();

    void on_pushButtonStop_clicked();

    void on_toolButtonSeectAll_clicked(bool checked);

    void startDownload();

    void downloadSora(QString sura,int max);

    void readStandardOutput();
     void readStandardError();
private:
    Ui::DialogAddReciter *ui;
    QString dirName;
    QString urlName;
    QString riwayaName;
    QString reciterName;
    QString dataName;
    QStringList listDownload;
    QProcess *mProcess;
};

#endif // DIALOGADDRECITER_H
