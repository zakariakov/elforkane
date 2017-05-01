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
#ifndef DATABASE_H
#define DATABASE_H
//#include <QtGui>
#include <QObject>
#include <QSqlDatabase>
#include <QComboBox>
#include <QTreeWidget>
#include <QList>

class Database : public QObject
{
    Q_OBJECT
public:
    Database();
    QSqlDatabase db;
    QList<int>*myListSura;
    QList<QString>*myList;
    //QList<QString>*myListJozaa;
    QList<QString>*myListSafhat;
    QList<int>*myListJozaa;
    QList<int>*myListHizb;
    QList<QString>*myListArbaa;
    QList<QAction *>myListAction;
    QString appPath;

    int curentId;
    int curentSura;
    int curentSafha;
    int curentAya;
    int curentJozaa;
    int curentHizb;
    int curentRobaa;
    QString curentSound;
    QString m_soundPath;
signals:


public slots:

    void searchInCuran(QString searchString );
    void treeChargeJozaa(QTreeWidget *view);
    void treeChargeSoura(QTreeWidget *view,   bool suraCharged,QComboBox *combo,QString lng,int id);
    void  chargeCsvs(QString riwaya);
    void openDb(QString dataFileName);
    void dataSearchString(QTreeWidget *view,QString arg1,QString arg2,QString orAnd ,int option);
    QString getStringPage(int begen,int end);
    //void chargeTree(QTreeWidget *view);
    void searchInTreeview(QTreeWidget *view, QString searchString, int colum, bool hamza);
    QString getTranslation(int pos);
private:
    QString tableName;
    QString databaseName;
private slots:
    QString creatIndex(QString mytxt);
    bool searchTreeForString( const QString &searchString, QTreeWidgetItem* parent,
                              bool itemtop,int  topindex,QTreeWidget *view,int colum, bool hamza) ;
    bool showAllItems( QTreeWidgetItem* parent,QTreeWidget *view ) ;
};

#endif // DATABASE_H
