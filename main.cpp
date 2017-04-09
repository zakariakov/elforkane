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
#include <QApplication>
#include "mainwindow.h"
#include "database.h"

static void associateFileTypes()
{
    #if defined(Q_OS_WIN)
    QString displayName = QGuiApplication::applicationDisplayName();
    QString filePath = QCoreApplication::applicationFilePath();
    QString fileName = QFileInfo(filePath).fileName();

    QSettings settings("HKEY_CURRENT_USER\\Software\\Classes\\Applications\\" + fileName, QSettings::NativeFormat);
    settings.setValue("FriendlyAppName", displayName);



    settings.beginGroup("shell");
    settings.beginGroup("open");
    settings.setValue("FriendlyAppName", displayName);
    settings.beginGroup("Command");
    settings.setValue(".", QChar('"') + QDir::toNativeSeparators(filePath) + QString("\" \"%1\""));
    #endif
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Elforkane");
    a.setOrganizationName("Abouzakaria");
    a.setWindowIcon(QIcon::fromTheme("elforkane",QIcon(":/img/elforkane.png")))  ;
    a.setApplicationVersion("1.2.5");
    a.setOrganizationDomain("elokab-project.org");
    a.setApplicationDisplayName("Elforkane");

    //associateFileTypes();

      QDir appDir(a.applicationDirPath());
    QString appPath;
#if defined(Q_OS_WIN)
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
#endif


    //-----------------------
    QDir dir;
    //   QString h=dir.homePath();

    if (!dir.exists(QDir::homePath()+"/.elforkane")) //
    {
        dir.mkdir( QDir::homePath()+"/.elforkane");
    }
    QFile file;
    if (!file.exists(QDir::homePath()+"/.elforkane/reciterInfo")){
        file.copy(appPath+"/reciterInfo",QDir::homePath()+"/.elforkane/reciterInfo");
    }
    QSettings settings(QDir::homePath()+"/.elforkane/setting.ini",QSettings::IniFormat);
    settings.beginGroup("Main");
    QString lng=settings.value("lng","sys").toString();
    int m_locale= settings.value("locale",0).toInt();
    settings.endGroup();

    switch (m_locale) {
    case 0:
        QLocale::setDefault(QLocale(QLocale::system()));
        break;
    case 1:
        QLocale::setDefault(QLocale(QLocale::Latin));
        break;
    case 2:
        QLocale::setDefault(QLocale(QLocale::Arabic));
        break;
    default:
        break;
    }
    QString translatorFileName = QLatin1String("qt_");
    translatorFileName += QLocale::system().name();
    QTranslator *translatorsys = new QTranslator(&a);
    if (translatorsys->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        a.installTranslator(translatorsys);
    QString locale = QLocale::system().name();

    QTranslator translator;
    if(lng=="sys"){
        translator.load(QString(appPath+"/language/elforkane_"+locale.section("_",0,0)) );
    }else {
        translator.load(QString(appPath+"/language/elforkane_"+lng) );
    }
    a.installTranslator(&translator);
    //-------------------------------

    const QStringList args = QCoreApplication::arguments();

    if (args.count() ==2){
        QString   goPos1 = args.at(1);

        if (goPos1.toLower()==("-help")){
            QString txt=QString(QObject::trUtf8("elforkane The electronic Holly Quran browser Version : %1 \n"
                                                "Usage: elforkane [options]\n"
                                               "Options:\n"
                                               "-help                   Show help about options.\n"
                                               "-full                   Run in full screen .\n"
                                               "-j      <int>           Run in the specified jozaa .\n"
                                               "-h      <int>           Run in the specified hizb.\n"
                                               "-s      <int> <int>     Run in the specified sura and aya.\n"
                                               "-s      <int>           Run in the specified sura .\n"
                                               "-f      <string>        Find .\n"
                                               "-play   <int>           Play in the specified sura\n"
                                               "-play   <int> <int>     Play in the specified sura and aya\n")).arg(a.applicationVersion());
            qDebug()<<txt;
            return 0;
        }else  if (goPos1.toLower()==("-full")){
            MainWindow w;
            w.toggleFullScreen();
            //   w.showFullScreen();

            w. m_plaOne=false;
            w.mediaPlay();
            return a.exec();
        }

    }
     if (args.count() >= 3){


        QString   goPos1 = args.at(1);
        QString   goPos2 = args.at(2);
        if (args.count() == 3){

            if (goPos1.toLower()==("-j")){
               MainWindow w;
                w.setJozaa(goPos2.toInt());
            }else if (goPos1.toLower()==("-h")){
                MainWindow w;
                w.setHizb(goPos2.toInt());
            }else if (goPos1.toLower()==("-s")){
              MainWindow w;
                w.setSora(goPos2.toInt());
            }else  if (goPos1.toLower()==("-f")){
                Database data;
                data.searchInCuran(goPos2);
                return 0;
            }else if (goPos1.toLower()==("-play")){
             MainWindow w;
                w.setSora(goPos2.toInt());
                w. m_plaOne=false;
                w.mediaPlay();
              w.hide();
                return a.exec();
            }
        }

        if (args.count() == 4){
            MainWindow w;
            QString   goPos3 = args.at(3);
            if (goPos1.toLower()==("-s")){
                w.setAya(goPos2.toInt(),goPos3.toInt());
            }
            if (goPos1.toLower()==("-play")){
                w.setAya(goPos2.toInt(),goPos3.toInt());
                w.m_plaOne=false;
                w.mediaPlay();
             w.hide();
                return a.exec();
            }
        }

    }

    MainWindow w;
    w.show();

    return a.exec();
}
