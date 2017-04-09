#****************************************************************************
#   elforkane Copyright (C) 2012 yahia nouah <yahiaui@gmail.com>
#
#      This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
#      This is free software, and you are welcome to redistribute it
#      under certain conditions; type `show c' for details.
#
#  The hypothetical commands `show w' and `show c' should show the appropriate
#  parts of the General Public License.  Of course, your program's commands
#  might be different; for a GUI interface, you would use an "about box".
#
#    You should also get your employer (if you work as a programmer) or school,
#  if any, to sign a "copyright disclaimer" for the program, if necessary.
#  For more information on this, and how to apply and follow the GNU GPL, see
#  <http://www.gnu.org/licenses/>.
#
#    The GNU General Public License does not permit incorporating your program
#  into proprietary programs.  If your program is a subroutine library, you
#  may consider it more useful to permit linking proprietary applications with
#  the library.  If this is what you want to do, use the GNU Lesser General
#  Public License instead of this License.  But first, please read
#  <http://www.gnu.org/philosophy/why-not-lgpl.html>.
# ----------------------------------------------------------
# If you have questions regarding the use of this file, please contact
# yahia nouah (yahiaui@gmail.com)
# $elforkane_END_LICENSE$
#
#**************************************************************************
#-------------------------------------------------
#
# Project created by QtCreator 2011-12-23T17:36:01
#
#-------------------------------------------------

#QT       += core gui   sql multimedia multimediawidgets widgets printsupport winextras

#greaterThan(QT_MAJOR_VERSION, 4): QT +=

OBJECTS_DIR = usr
MOC_DIR = usr
UI_DIR = usr
INCLUDEPATH += usr
TARGET =elforkane



CONFIG += qt \
          release
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
INCLUDEPATH +=build




win32 {

    debug:DESTDIR = usr/bin
    release:DESTDIR = usr/bin
    RC_FILE = myapp.rc
}else{
    DESTDIR = usr/bin
}

   equals(QT_MAJOR_VERSION, 4) {
     QT += core gui   sql  phonon
    SOURCES +=  player.cpp\
     main.cpp\
    mainwindow.cpp \
    database.cpp \
    dialogaddreciter.cpp \
    dialogoption.cpp \
    dialogabout.cpp\
    sceenbase.cpp \
    dialogscript.cpp

    HEADERS  +=   player.h\
    mainwindow.h \
    database.h \
    dialogaddreciter.h \
    dialogoption.h \
    dialogabout.h\
    sceenbase.h \
    dialogscript.h
     message("qt vertion is :4 " $$QT_MAJOR_VERSION)
  }

   equals(QT_MAJOR_VERSION, 5) {
     QT       += core gui   sql multimedia multimediawidgets widgets printsupport
win32 {
#    QT       += winextras
}
     SOURCES +=  playermultimedia.cpp\
     main.cpp\
    mainwindow.cpp \
    database.cpp \
    dialogaddreciter.cpp \
    dialogoption.cpp \
    dialogabout.cpp\
    sceenbase.cpp \
    dialogscript.cpp

   HEADERS  +=   playermultimedia.h\
     mainwindow.h \
    database.h \
    dialogaddreciter.h \
    dialogoption.h \
    dialogabout.h\
    sceenbase.h \
    dialogscript.h

  message("qt vertion is :5 " $$QT_MAJOR_VERSION)
   }



FORMS    += mainwindow.ui \
    dialogaddreciter.ui \
    dialogoption.ui \
    dialogabout.ui \
    dialogscript.ui

RESOURCES += \
    img.qrc


TRANSLATIONS    =usr/share/elforkane/language/elforkane_ar.ts\
usr/share/elforkane/language/elforkane_fr.ts\
usr/share/elforkane/language/elforkane_en.ts
CODECFORTR = UTF-8




# install

MKDIR = mkdir -p /usr/share/elforkane

 data.files =usr/share/elforkane*
 data.path=/usr/share/

 desktopfile.files = elforkane.desktop
 desktopfile.path = /usr/share/applications

 icon.files = usr/share/icons/hicolor/22x22/apps/elforkane.png
 icon.path = /usr/share/icons/hicolor/22x22/apps
 icon1.files = usr/share/icons/hicolor/24x24/apps/elforkane.png
 icon1.path = /usr/share/icons/hicolor/24x24/apps
 icon2.files = usr/share/icons/hicolor/32x32/apps/elforkane.png
 icon2.path = /usr/share/icons/hicolor/32x32/apps
 icon3.files = usr/share/icons/hicolor/48x48/apps/elforkane.png
 icon3.path = /usr/share/icons/hicolor/48x48/apps
 icon4.files = usr/share/icons/hicolor/64x64/apps/elforkane.png
 icon4.path = /usr/share/icons/hicolor/64x64/apps
 icon5.files = usr/share/icons/hicolor/scalable/apps/elforkane.svg
 icon5.path = /usr/share/icons/hicolor/scalable/apps

 target.path = /usr/bin

 INSTALLS +=    data \
                target \
                desktopfile\
                icon\
                icon1\
                icon2\
                icon3\
                icon4\
                icon5

HEADERS += \
    fs-wallpapers/fullscreen.h \


SOURCES += \
    fs-wallpapers/fullscreen.cpp \


DISTFILES += \
    usr/share/elforkane/fullscreen/bgrFull.png \
    usr/share/elforkane/language/elforkane_ar.qm \
    usr/share/elforkane/language/elforkane_en.qm \
    usr/share/elforkane/language/elforkane_fr.qm \
    usr/share/elforkane/tafasir/ar_muyassar.db \
    usr/share/elforkane/tafasir/baghawy.db \
    usr/share/elforkane/tafasir/katheer.db \
    usr/share/elforkane/tafasir/qortoby.db \
    usr/share/elforkane/tafasir/sa3dy.db \
    usr/share/elforkane/tafasir/tabary.db \
    usr/share/elforkane/tafasir/tafheem.db \
    usr/share/elforkane/translat/ar_muyassar.db \
    usr/share/elforkane/translat/en_sahih.db \
    usr/share/elforkane/translat/fr_hamidullah.db \
    usr/share/elforkane/quran.db \
    usr/share/elforkane/ajzaa.xml \
    usr/share/elforkane/quran.xml \
    usr/share/elforkane/audhubillah.ogg \
    usr/share/elforkane/bismillah.ogg \
    usr/share/elforkane/images/default/1.png \
    usr/share/elforkane/images/default/10.png \
    usr/share/elforkane/images/default/100.png \
    usr/share/elforkane/images/default/101.png \
    usr/share/elforkane/images/default/102.png \
    usr/share/elforkane/images/default/103.png \
    usr/share/elforkane/images/default/104.png \
    usr/share/elforkane/images/default/105.png \
    usr/share/elforkane/images/default/106.png \
    usr/share/elforkane/images/default/107.png \
    usr/share/elforkane/images/default/108.png \
    usr/share/elforkane/images/default/109.png \
    usr/share/elforkane/images/default/11.png \
    usr/share/elforkane/images/default/110.png \
    usr/share/elforkane/images/default/111.png \
    usr/share/elforkane/images/default/112.png \
    usr/share/elforkane/images/default/113.png \
    usr/share/elforkane/images/default/114.png \
    usr/share/elforkane/images/default/115.png \
    usr/share/elforkane/images/default/116.png \
    usr/share/elforkane/images/default/117.png \
    usr/share/elforkane/images/default/118.png \
    usr/share/elforkane/images/default/119.png \
    usr/share/elforkane/images/default/12.png \
    usr/share/elforkane/images/default/120.png \
    usr/share/elforkane/images/default/121.png \
    usr/share/elforkane/images/default/122.png \
    usr/share/elforkane/images/default/123.png \
    usr/share/elforkane/images/default/124.png \
    usr/share/elforkane/images/default/125.png \
    usr/share/elforkane/images/default/126.png \
    usr/share/elforkane/images/default/127.png \
    usr/share/elforkane/images/default/128.png \
    usr/share/elforkane/images/default/129.png \
    usr/share/elforkane/images/default/13.png \
    usr/share/elforkane/images/default/130.png \
    usr/share/elforkane/images/default/131.png \
    usr/share/elforkane/images/default/132.png \
    usr/share/elforkane/images/default/133.png \
    usr/share/elforkane/images/default/134.png \
    usr/share/elforkane/images/default/135.png \
    usr/share/elforkane/images/default/136.png \
    usr/share/elforkane/images/default/137.png \
    usr/share/elforkane/images/default/138.png \
    usr/share/elforkane/images/default/139.png \
    usr/share/elforkane/images/default/14.png \
    usr/share/elforkane/images/default/140.png \
    usr/share/elforkane/images/default/141.png \
    usr/share/elforkane/images/default/142.png \
    usr/share/elforkane/images/default/143.png \
    usr/share/elforkane/images/default/144.png \
    usr/share/elforkane/images/default/145.png \
    usr/share/elforkane/images/default/146.png \
    usr/share/elforkane/images/default/147.png \
    usr/share/elforkane/images/default/148.png \
    usr/share/elforkane/images/default/149.png \
    usr/share/elforkane/images/default/15.png \
    usr/share/elforkane/images/default/150.png \
    usr/share/elforkane/images/default/151.png \
    usr/share/elforkane/images/default/152.png \
    usr/share/elforkane/images/default/153.png \
    usr/share/elforkane/images/default/154.png \
    usr/share/elforkane/images/default/155.png \
    usr/share/elforkane/images/default/156.png \
    usr/share/elforkane/images/default/157.png \
    usr/share/elforkane/images/default/158.png \
    usr/share/elforkane/images/default/159.png \
    usr/share/elforkane/images/default/16.png \
    usr/share/elforkane/images/default/160.png \
    usr/share/elforkane/images/default/161.png \
    usr/share/elforkane/images/default/162.png \
    usr/share/elforkane/images/default/163.png \
    usr/share/elforkane/images/default/164.png \
    usr/share/elforkane/images/default/165.png \
    usr/share/elforkane/images/default/166.png \
    usr/share/elforkane/images/default/167.png \
    usr/share/elforkane/images/default/168.png \
    usr/share/elforkane/images/default/169.png \
    usr/share/elforkane/images/default/17.png \
    usr/share/elforkane/images/default/170.png \
    usr/share/elforkane/images/default/171.png \
    usr/share/elforkane/images/default/172.png \
    usr/share/elforkane/images/default/173.png \
    usr/share/elforkane/images/default/174.png \
    usr/share/elforkane/images/default/175.png \
    usr/share/elforkane/images/default/176.png \
    usr/share/elforkane/images/default/177.png \
    usr/share/elforkane/images/default/178.png \
    usr/share/elforkane/images/default/179.png \
    usr/share/elforkane/images/default/18.png \
    usr/share/elforkane/images/default/180.png \
    usr/share/elforkane/images/default/181.png \
    usr/share/elforkane/images/default/182.png \
    usr/share/elforkane/images/default/183.png \
    usr/share/elforkane/images/default/184.png \
    usr/share/elforkane/images/default/185.png \
    usr/share/elforkane/images/default/186.png \
    usr/share/elforkane/images/default/187.png \
    usr/share/elforkane/images/default/188.png \
    usr/share/elforkane/images/default/189.png \
    usr/share/elforkane/images/default/19.png \
    usr/share/elforkane/images/default/190.png \
    usr/share/elforkane/images/default/191.png \
    usr/share/elforkane/images/default/192.png \
    usr/share/elforkane/images/default/193.png \
    usr/share/elforkane/images/default/194.png \
    usr/share/elforkane/images/default/195.png \
    usr/share/elforkane/images/default/196.png \
    usr/share/elforkane/images/default/197.png \
    usr/share/elforkane/images/default/198.png \
    usr/share/elforkane/images/default/199.png \
    usr/share/elforkane/images/default/2.png \
    usr/share/elforkane/images/default/20.png \
    usr/share/elforkane/images/default/200.png \
    usr/share/elforkane/images/default/201.png \
    usr/share/elforkane/images/default/202.png \
    usr/share/elforkane/images/default/203.png \
    usr/share/elforkane/images/default/204.png \
    usr/share/elforkane/images/default/205.png \
    usr/share/elforkane/images/default/206.png \
    usr/share/elforkane/images/default/207.png \
    usr/share/elforkane/images/default/208.png \
    usr/share/elforkane/images/default/209.png \
    usr/share/elforkane/images/default/21.png \
    usr/share/elforkane/images/default/210.png \
    usr/share/elforkane/images/default/211.png \
    usr/share/elforkane/images/default/212.png \
    usr/share/elforkane/images/default/213.png \
    usr/share/elforkane/images/default/214.png \
    usr/share/elforkane/images/default/215.png \
    usr/share/elforkane/images/default/216.png \
    usr/share/elforkane/images/default/217.png \
    usr/share/elforkane/images/default/218.png \
    usr/share/elforkane/images/default/219.png \
    usr/share/elforkane/images/default/22.png \
    usr/share/elforkane/images/default/220.png \
    usr/share/elforkane/images/default/221.png \
    usr/share/elforkane/images/default/222.png \
    usr/share/elforkane/images/default/223.png \
    usr/share/elforkane/images/default/224.png \
    usr/share/elforkane/images/default/225.png \
    usr/share/elforkane/images/default/226.png \
    usr/share/elforkane/images/default/227.png \
    usr/share/elforkane/images/default/228.png \
    usr/share/elforkane/images/default/229.png \
    usr/share/elforkane/images/default/23.png \
    usr/share/elforkane/images/default/230.png \
    usr/share/elforkane/images/default/231.png \
    usr/share/elforkane/images/default/232.png \
    usr/share/elforkane/images/default/233.png \
    usr/share/elforkane/images/default/234.png \
    usr/share/elforkane/images/default/235.png \
    usr/share/elforkane/images/default/236.png \
    usr/share/elforkane/images/default/237.png \
    usr/share/elforkane/images/default/238.png \
    usr/share/elforkane/images/default/239.png \
    usr/share/elforkane/images/default/24.png \
    usr/share/elforkane/images/default/240.png \
    usr/share/elforkane/images/default/241.png \
    usr/share/elforkane/images/default/242.png \
    usr/share/elforkane/images/default/243.png \
    usr/share/elforkane/images/default/244.png \
    usr/share/elforkane/images/default/245.png \
    usr/share/elforkane/images/default/246.png \
    usr/share/elforkane/images/default/247.png \
    usr/share/elforkane/images/default/248.png \
    usr/share/elforkane/images/default/249.png \
    usr/share/elforkane/images/default/25.png \
    usr/share/elforkane/images/default/250.png \
    usr/share/elforkane/images/default/251.png \
    usr/share/elforkane/images/default/252.png \
    usr/share/elforkane/images/default/253.png \
    usr/share/elforkane/images/default/254.png \
    usr/share/elforkane/images/default/255.png \
    usr/share/elforkane/images/default/256.png \
    usr/share/elforkane/images/default/257.png \
    usr/share/elforkane/images/default/258.png \
    usr/share/elforkane/images/default/259.png \
    usr/share/elforkane/images/default/26.png \
    usr/share/elforkane/images/default/260.png \
    usr/share/elforkane/images/default/261.png \
    usr/share/elforkane/images/default/262.png \
    usr/share/elforkane/images/default/263.png \
    usr/share/elforkane/images/default/264.png \
    usr/share/elforkane/images/default/265.png \
    usr/share/elforkane/images/default/266.png \
    usr/share/elforkane/images/default/267.png \
    usr/share/elforkane/images/default/268.png \
    usr/share/elforkane/images/default/269.png \
    usr/share/elforkane/images/default/27.png \
    usr/share/elforkane/images/default/270.png \
    usr/share/elforkane/images/default/271.png \
    usr/share/elforkane/images/default/272.png \
    usr/share/elforkane/images/default/273.png \
    usr/share/elforkane/images/default/274.png \
    usr/share/elforkane/images/default/275.png \
    usr/share/elforkane/images/default/276.png \
    usr/share/elforkane/images/default/277.png \
    usr/share/elforkane/images/default/278.png \
    usr/share/elforkane/images/default/279.png \
    usr/share/elforkane/images/default/28.png \
    usr/share/elforkane/images/default/280.png \
    usr/share/elforkane/images/default/281.png \
    usr/share/elforkane/images/default/282.png \
    usr/share/elforkane/images/default/283.png \
    usr/share/elforkane/images/default/284.png \
    usr/share/elforkane/images/default/285.png \
    usr/share/elforkane/images/default/286.png \
    usr/share/elforkane/images/default/287.png \
    usr/share/elforkane/images/default/288.png \
    usr/share/elforkane/images/default/289.png \
    usr/share/elforkane/images/default/29.png \
    usr/share/elforkane/images/default/290.png \
    usr/share/elforkane/images/default/291.png \
    usr/share/elforkane/images/default/292.png \
    usr/share/elforkane/images/default/293.png \
    usr/share/elforkane/images/default/294.png \
    usr/share/elforkane/images/default/295.png \
    usr/share/elforkane/images/default/296.png \
    usr/share/elforkane/images/default/297.png \
    usr/share/elforkane/images/default/298.png \
    usr/share/elforkane/images/default/299.png \
    usr/share/elforkane/images/default/3.png \
    usr/share/elforkane/images/default/30.png \
    usr/share/elforkane/images/default/300.png \
    usr/share/elforkane/images/default/301.png \
    usr/share/elforkane/images/default/302.png \
    usr/share/elforkane/images/default/303.png \
    usr/share/elforkane/images/default/304.png \
    usr/share/elforkane/images/default/305.png \
    usr/share/elforkane/images/default/306.png \
    usr/share/elforkane/images/default/307.png \
    usr/share/elforkane/images/default/308.png \
    usr/share/elforkane/images/default/309.png \
    usr/share/elforkane/images/default/31.png \
    usr/share/elforkane/images/default/310.png \
    usr/share/elforkane/images/default/311.png \
    usr/share/elforkane/images/default/312.png \
    usr/share/elforkane/images/default/313.png \
    usr/share/elforkane/images/default/314.png \
    usr/share/elforkane/images/default/315.png \
    usr/share/elforkane/images/default/316.png \
    usr/share/elforkane/images/default/317.png \
    usr/share/elforkane/images/default/318.png \
    usr/share/elforkane/images/default/319.png \
    usr/share/elforkane/images/default/32.png \
    usr/share/elforkane/images/default/320.png \
    usr/share/elforkane/images/default/321.png \
    usr/share/elforkane/images/default/322.png \
    usr/share/elforkane/images/default/323.png \
    usr/share/elforkane/images/default/324.png \
    usr/share/elforkane/images/default/325.png \
    usr/share/elforkane/images/default/326.png \
    usr/share/elforkane/images/default/327.png \
    usr/share/elforkane/images/default/328.png \
    usr/share/elforkane/images/default/329.png \
    usr/share/elforkane/images/default/33.png \
    usr/share/elforkane/images/default/330.png \
    usr/share/elforkane/images/default/331.png \
    usr/share/elforkane/images/default/332.png \
    usr/share/elforkane/images/default/333.png \
    usr/share/elforkane/images/default/334.png \
    usr/share/elforkane/images/default/335.png \
    usr/share/elforkane/images/default/336.png \
    usr/share/elforkane/images/default/337.png \
    usr/share/elforkane/images/default/338.png \
    usr/share/elforkane/images/default/339.png \
    usr/share/elforkane/images/default/34.png \
    usr/share/elforkane/images/default/340.png \
    usr/share/elforkane/images/default/341.png \
    usr/share/elforkane/images/default/342.png \
    usr/share/elforkane/images/default/343.png \
    usr/share/elforkane/images/default/344.png \
    usr/share/elforkane/images/default/345.png \
    usr/share/elforkane/images/default/346.png \
    usr/share/elforkane/images/default/347.png \
    usr/share/elforkane/images/default/348.png \
    usr/share/elforkane/images/default/349.png \
    usr/share/elforkane/images/default/35.png \
    usr/share/elforkane/images/default/350.png \
    usr/share/elforkane/images/default/351.png \
    usr/share/elforkane/images/default/352.png \
    usr/share/elforkane/images/default/353.png \
    usr/share/elforkane/images/default/354.png \
    usr/share/elforkane/images/default/355.png \
    usr/share/elforkane/images/default/356.png \
    usr/share/elforkane/images/default/357.png \
    usr/share/elforkane/images/default/358.png \
    usr/share/elforkane/images/default/359.png \
    usr/share/elforkane/images/default/36.png \
    usr/share/elforkane/images/default/360.png \
    usr/share/elforkane/images/default/361.png \
    usr/share/elforkane/images/default/362.png \
    usr/share/elforkane/images/default/363.png \
    usr/share/elforkane/images/default/364.png \
    usr/share/elforkane/images/default/365.png \
    usr/share/elforkane/images/default/366.png \
    usr/share/elforkane/images/default/367.png \
    usr/share/elforkane/images/default/368.png \
    usr/share/elforkane/images/default/369.png \
    usr/share/elforkane/images/default/37.png \
    usr/share/elforkane/images/default/370.png \
    usr/share/elforkane/images/default/371.png \
    usr/share/elforkane/images/default/372.png \
    usr/share/elforkane/images/default/373.png \
    usr/share/elforkane/images/default/374.png \
    usr/share/elforkane/images/default/375.png \
    usr/share/elforkane/images/default/376.png \
    usr/share/elforkane/images/default/377.png \
    usr/share/elforkane/images/default/378.png \
    usr/share/elforkane/images/default/379.png \
    usr/share/elforkane/images/default/38.png \
    usr/share/elforkane/images/default/380.png \
    usr/share/elforkane/images/default/381.png \
    usr/share/elforkane/images/default/382.png \
    usr/share/elforkane/images/default/383.png \
    usr/share/elforkane/images/default/384.png \
    usr/share/elforkane/images/default/385.png \
    usr/share/elforkane/images/default/386.png \
    usr/share/elforkane/images/default/387.png \
    usr/share/elforkane/images/default/388.png \
    usr/share/elforkane/images/default/389.png \
    usr/share/elforkane/images/default/39.png \
    usr/share/elforkane/images/default/390.png \
    usr/share/elforkane/images/default/391.png \
    usr/share/elforkane/images/default/392.png \
    usr/share/elforkane/images/default/393.png \
    usr/share/elforkane/images/default/394.png \
    usr/share/elforkane/images/default/395.png \
    usr/share/elforkane/images/default/396.png \
    usr/share/elforkane/images/default/397.png \
    usr/share/elforkane/images/default/398.png \
    usr/share/elforkane/images/default/399.png \
    usr/share/elforkane/images/default/4.png \
    usr/share/elforkane/images/default/40.png \
    usr/share/elforkane/images/default/400.png \
    usr/share/elforkane/images/default/401.png \
    usr/share/elforkane/images/default/402.png \
    usr/share/elforkane/images/default/403.png \
    usr/share/elforkane/images/default/404.png \
    usr/share/elforkane/images/default/405.png \
    usr/share/elforkane/images/default/406.png \
    usr/share/elforkane/images/default/407.png \
    usr/share/elforkane/images/default/408.png \
    usr/share/elforkane/images/default/409.png \
    usr/share/elforkane/images/default/41.png \
    usr/share/elforkane/images/default/410.png \
    usr/share/elforkane/images/default/411.png \
    usr/share/elforkane/images/default/412.png \
    usr/share/elforkane/images/default/413.png \
    usr/share/elforkane/images/default/414.png \
    usr/share/elforkane/images/default/415.png \
    usr/share/elforkane/images/default/416.png \
    usr/share/elforkane/images/default/417.png \
    usr/share/elforkane/images/default/418.png \
    usr/share/elforkane/images/default/419.png \
    usr/share/elforkane/images/default/42.png \
    usr/share/elforkane/images/default/420.png \
    usr/share/elforkane/images/default/421.png \
    usr/share/elforkane/images/default/422.png \
    usr/share/elforkane/images/default/423.png \
    usr/share/elforkane/images/default/424.png \
    usr/share/elforkane/images/default/425.png \
    usr/share/elforkane/images/default/426.png \
    usr/share/elforkane/images/default/427.png \
    usr/share/elforkane/images/default/428.png \
    usr/share/elforkane/images/default/429.png \
    usr/share/elforkane/images/default/43.png \
    usr/share/elforkane/images/default/430.png \
    usr/share/elforkane/images/default/431.png \
    usr/share/elforkane/images/default/432.png \
    usr/share/elforkane/images/default/433.png \
    usr/share/elforkane/images/default/434.png \
    usr/share/elforkane/images/default/435.png \
    usr/share/elforkane/images/default/436.png \
    usr/share/elforkane/images/default/437.png \
    usr/share/elforkane/images/default/438.png \
    usr/share/elforkane/images/default/439.png \
    usr/share/elforkane/images/default/44.png \
    usr/share/elforkane/images/default/440.png \
    usr/share/elforkane/images/default/441.png \
    usr/share/elforkane/images/default/442.png \
    usr/share/elforkane/images/default/443.png \
    usr/share/elforkane/images/default/444.png \
    usr/share/elforkane/images/default/445.png \
    usr/share/elforkane/images/default/446.png \
    usr/share/elforkane/images/default/447.png \
    usr/share/elforkane/images/default/448.png \
    usr/share/elforkane/images/default/449.png \
    usr/share/elforkane/images/default/45.png \
    usr/share/elforkane/images/default/450.png \
    usr/share/elforkane/images/default/451.png \
    usr/share/elforkane/images/default/452.png \
    usr/share/elforkane/images/default/453.png \
    usr/share/elforkane/images/default/454.png \
    usr/share/elforkane/images/default/455.png \
    usr/share/elforkane/images/default/456.png \
    usr/share/elforkane/images/default/457.png \
    usr/share/elforkane/images/default/458.png \
    usr/share/elforkane/images/default/459.png \
    usr/share/elforkane/images/default/46.png \
    usr/share/elforkane/images/default/460.png \
    usr/share/elforkane/images/default/461.png \
    usr/share/elforkane/images/default/462.png \
    usr/share/elforkane/images/default/463.png \
    usr/share/elforkane/images/default/464.png \
    usr/share/elforkane/images/default/465.png \
    usr/share/elforkane/images/default/466.png \
    usr/share/elforkane/images/default/467.png \
    usr/share/elforkane/images/default/468.png \
    usr/share/elforkane/images/default/469.png \
    usr/share/elforkane/images/default/47.png \
    usr/share/elforkane/images/default/470.png \
    usr/share/elforkane/images/default/471.png \
    usr/share/elforkane/images/default/472.png \
    usr/share/elforkane/images/default/473.png \
    usr/share/elforkane/images/default/474.png \
    usr/share/elforkane/images/default/475.png \
    usr/share/elforkane/images/default/476.png \
    usr/share/elforkane/images/default/477.png \
    usr/share/elforkane/images/default/478.png \
    usr/share/elforkane/images/default/479.png \
    usr/share/elforkane/images/default/48.png \
    usr/share/elforkane/images/default/480.png \
    usr/share/elforkane/images/default/481.png \
    usr/share/elforkane/images/default/482.png \
    usr/share/elforkane/images/default/483.png \
    usr/share/elforkane/images/default/484.png \
    usr/share/elforkane/images/default/485.png \
    usr/share/elforkane/images/default/486.png \
    usr/share/elforkane/images/default/487.png \
    usr/share/elforkane/images/default/488.png \
    usr/share/elforkane/images/default/489.png \
    usr/share/elforkane/images/default/49.png \
    usr/share/elforkane/images/default/490.png \
    usr/share/elforkane/images/default/491.png \
    usr/share/elforkane/images/default/492.png \
    usr/share/elforkane/images/default/493.png \
    usr/share/elforkane/images/default/494.png \
    usr/share/elforkane/images/default/495.png \
    usr/share/elforkane/images/default/496.png \
    usr/share/elforkane/images/default/497.png \
    usr/share/elforkane/images/default/498.png \
    usr/share/elforkane/images/default/499.png \
    usr/share/elforkane/images/default/5.png \
    usr/share/elforkane/images/default/50.png \
    usr/share/elforkane/images/default/500.png \
    usr/share/elforkane/images/default/501.png \
    usr/share/elforkane/images/default/502.png \
    usr/share/elforkane/images/default/503.png \
    usr/share/elforkane/images/default/504.png \
    usr/share/elforkane/images/default/505.png \
    usr/share/elforkane/images/default/506.png \
    usr/share/elforkane/images/default/507.png \
    usr/share/elforkane/images/default/508.png \
    usr/share/elforkane/images/default/509.png \
    usr/share/elforkane/images/default/51.png \
    usr/share/elforkane/images/default/510.png \
    usr/share/elforkane/images/default/511.png \
    usr/share/elforkane/images/default/512.png \
    usr/share/elforkane/images/default/513.png \
    usr/share/elforkane/images/default/514.png \
    usr/share/elforkane/images/default/515.png \
    usr/share/elforkane/images/default/516.png \
    usr/share/elforkane/images/default/517.png \
    usr/share/elforkane/images/default/518.png \
    usr/share/elforkane/images/default/519.png \
    usr/share/elforkane/images/default/52.png \
    usr/share/elforkane/images/default/520.png \
    usr/share/elforkane/images/default/521.png \
    usr/share/elforkane/images/default/522.png \
    usr/share/elforkane/images/default/523.png \
    usr/share/elforkane/images/default/524.png \
    usr/share/elforkane/images/default/525.png \
    usr/share/elforkane/images/default/526.png \
    usr/share/elforkane/images/default/527.png \
    usr/share/elforkane/images/default/528.png \
    usr/share/elforkane/images/default/529.png \
    usr/share/elforkane/images/default/53.png \
    usr/share/elforkane/images/default/530.png \
    usr/share/elforkane/images/default/531.png \
    usr/share/elforkane/images/default/532.png \
    usr/share/elforkane/images/default/533.png \
    usr/share/elforkane/images/default/534.png \
    usr/share/elforkane/images/default/535.png \
    usr/share/elforkane/images/default/536.png \
    usr/share/elforkane/images/default/537.png \
    usr/share/elforkane/images/default/538.png \
    usr/share/elforkane/images/default/539.png \
    usr/share/elforkane/images/default/54.png \
    usr/share/elforkane/images/default/540.png \
    usr/share/elforkane/images/default/541.png \
    usr/share/elforkane/images/default/542.png \
    usr/share/elforkane/images/default/543.png \
    usr/share/elforkane/images/default/544.png \
    usr/share/elforkane/images/default/545.png \
    usr/share/elforkane/images/default/546.png \
    usr/share/elforkane/images/default/547.png \
    usr/share/elforkane/images/default/548.png \
    usr/share/elforkane/images/default/549.png \
    usr/share/elforkane/images/default/55.png \
    usr/share/elforkane/images/default/550.png \
    usr/share/elforkane/images/default/551.png \
    usr/share/elforkane/images/default/552.png \
    usr/share/elforkane/images/default/553.png \
    usr/share/elforkane/images/default/554.png \
    usr/share/elforkane/images/default/555.png \
    usr/share/elforkane/images/default/556.png \
    usr/share/elforkane/images/default/557.png \
    usr/share/elforkane/images/default/558.png \
    usr/share/elforkane/images/default/559.png \
    usr/share/elforkane/images/default/56.png \
    usr/share/elforkane/images/default/560.png \
    usr/share/elforkane/images/default/561.png \
    usr/share/elforkane/images/default/562.png \
    usr/share/elforkane/images/default/563.png \
    usr/share/elforkane/images/default/564.png \
    usr/share/elforkane/images/default/565.png \
    usr/share/elforkane/images/default/566.png \
    usr/share/elforkane/images/default/567.png \
    usr/share/elforkane/images/default/568.png \
    usr/share/elforkane/images/default/569.png \
    usr/share/elforkane/images/default/57.png \
    usr/share/elforkane/images/default/570.png \
    usr/share/elforkane/images/default/571.png \
    usr/share/elforkane/images/default/572.png \
    usr/share/elforkane/images/default/573.png \
    usr/share/elforkane/images/default/574.png \
    usr/share/elforkane/images/default/575.png \
    usr/share/elforkane/images/default/576.png \
    usr/share/elforkane/images/default/577.png \
    usr/share/elforkane/images/default/578.png \
    usr/share/elforkane/images/default/579.png \
    usr/share/elforkane/images/default/58.png \
    usr/share/elforkane/images/default/580.png \
    usr/share/elforkane/images/default/581.png \
    usr/share/elforkane/images/default/582.png \
    usr/share/elforkane/images/default/583.png \
    usr/share/elforkane/images/default/584.png \
    usr/share/elforkane/images/default/585.png \
    usr/share/elforkane/images/default/586.png \
    usr/share/elforkane/images/default/587.png \
    usr/share/elforkane/images/default/588.png \
    usr/share/elforkane/images/default/589.png \
    usr/share/elforkane/images/default/59.png \
    usr/share/elforkane/images/default/590.png \
    usr/share/elforkane/images/default/591.png \
    usr/share/elforkane/images/default/592.png \
    usr/share/elforkane/images/default/593.png \
    usr/share/elforkane/images/default/594.png \
    usr/share/elforkane/images/default/595.png \
    usr/share/elforkane/images/default/596.png \
    usr/share/elforkane/images/default/597.png \
    usr/share/elforkane/images/default/598.png \
    usr/share/elforkane/images/default/599.png \
    usr/share/elforkane/images/default/6.png \
    usr/share/elforkane/images/default/60.png \
    usr/share/elforkane/images/default/600.png \
    usr/share/elforkane/images/default/601.png \
    usr/share/elforkane/images/default/602.png \
    usr/share/elforkane/images/default/603.png \
    usr/share/elforkane/images/default/604.png \
    usr/share/elforkane/images/default/61.png \
    usr/share/elforkane/images/default/62.png \
    usr/share/elforkane/images/default/63.png \
    usr/share/elforkane/images/default/64.png \
    usr/share/elforkane/images/default/65.png \
    usr/share/elforkane/images/default/66.png \
    usr/share/elforkane/images/default/67.png \
    usr/share/elforkane/images/default/68.png \
    usr/share/elforkane/images/default/69.png \
    usr/share/elforkane/images/default/7.png \
    usr/share/elforkane/images/default/70.png \
    usr/share/elforkane/images/default/71.png \
    usr/share/elforkane/images/default/72.png \
    usr/share/elforkane/images/default/73.png \
    usr/share/elforkane/images/default/74.png \
    usr/share/elforkane/images/default/75.png \
    usr/share/elforkane/images/default/76.png \
    usr/share/elforkane/images/default/77.png \
    usr/share/elforkane/images/default/78.png \
    usr/share/elforkane/images/default/79.png \
    usr/share/elforkane/images/default/8.png \
    usr/share/elforkane/images/default/80.png \
    usr/share/elforkane/images/default/81.png \
    usr/share/elforkane/images/default/82.png \
    usr/share/elforkane/images/default/83.png \
    usr/share/elforkane/images/default/84.png \
    usr/share/elforkane/images/default/85.png \
    usr/share/elforkane/images/default/86.png \
    usr/share/elforkane/images/default/87.png \
    usr/share/elforkane/images/default/88.png \
    usr/share/elforkane/images/default/89.png \
    usr/share/elforkane/images/default/9.png \
    usr/share/elforkane/images/default/90.png \
    usr/share/elforkane/images/default/91.png \
    usr/share/elforkane/images/default/92.png \
    usr/share/elforkane/images/default/93.png \
    usr/share/elforkane/images/default/94.png \
    usr/share/elforkane/images/default/95.png \
    usr/share/elforkane/images/default/96.png \
    usr/share/elforkane/images/default/97.png \
    usr/share/elforkane/images/default/98.png \
    usr/share/elforkane/images/default/99.png \
    usr/share/elforkane/themes/arabesque/bot.png \
    usr/share/elforkane/themes/arabesque/bot_left.png \
    usr/share/elforkane/themes/arabesque/bot_right.png \
    usr/share/elforkane/themes/arabesque/left.png \
    usr/share/elforkane/themes/arabesque/right.png \
    usr/share/elforkane/themes/arabesque/top.png \
    usr/share/elforkane/themes/arabesque/top_left.png \
    usr/share/elforkane/themes/arabesque/top_right.png \
    usr/share/elforkane/themes/arabesque2/bot.png \
    usr/share/elforkane/themes/arabesque2/bot_left.png \
    usr/share/elforkane/themes/arabesque2/bot_right.png \
    usr/share/elforkane/themes/arabesque2/left.png \
    usr/share/elforkane/themes/arabesque2/right.png \
    usr/share/elforkane/themes/arabesque2/top.png \
    usr/share/elforkane/themes/arabesque2/top_left.png \
    usr/share/elforkane/themes/arabesque2/top_right.png \
    usr/share/elforkane/themes/mashaf/bot.png \
    usr/share/elforkane/themes/mashaf/bot_left.png \
    usr/share/elforkane/themes/mashaf/bot_right.png \
    usr/share/elforkane/themes/mashaf/left.png \
    usr/share/elforkane/themes/mashaf/right.png \
    usr/share/elforkane/themes/mashaf/top.png \
    usr/share/elforkane/themes/mashaf/top_left.png \
    usr/share/elforkane/themes/mashaf/top_right.png \
    usr/share/elforkane/themes/mashaf2/bot.png \
    usr/share/elforkane/themes/mashaf2/bot_left.png \
    usr/share/elforkane/themes/mashaf2/bot_right.png \
    usr/share/elforkane/themes/mashaf2/left.png \
    usr/share/elforkane/themes/mashaf2/right.png \
    usr/share/elforkane/themes/mashaf2/top.png \
    usr/share/elforkane/themes/mashaf2/top_left.png \
    usr/share/elforkane/themes/mashaf2/top_right.png \
    usr/share/elforkane/themes/mashaf3/bot.png \
    usr/share/elforkane/themes/mashaf3/bot_left.png \
    usr/share/elforkane/themes/mashaf3/bot_right.png \
    usr/share/elforkane/themes/mashaf3/left.png \
    usr/share/elforkane/themes/mashaf3/r1.png \
    usr/share/elforkane/themes/mashaf3/r2.png \
    usr/share/elforkane/themes/mashaf3/r3.png \
    usr/share/elforkane/themes/mashaf3/r4.png \
    usr/share/elforkane/themes/mashaf3/right.png \
    usr/share/elforkane/themes/mashaf3/top.png \
    usr/share/elforkane/themes/mashaf3/top_left.png \
    usr/share/elforkane/themes/mashaf3/top_right.png \
    usr/share/elforkane/themes/zakhrafa/bot.png \
    usr/share/elforkane/themes/zakhrafa/bot_left.png \
    usr/share/elforkane/themes/zakhrafa/bot_right.png \
    usr/share/elforkane/themes/zakhrafa/left.png \
    usr/share/elforkane/themes/zakhrafa/right.png \
    usr/share/elforkane/themes/zakhrafa/top.png \
    usr/share/elforkane/themes/zakhrafa/top_left.png \
    usr/share/elforkane/themes/zakhrafa/top_right.png \
    usr/share/elforkane/themes/zakhrafa2/bot.png \
    usr/share/elforkane/themes/zakhrafa2/bot_left.png \
    usr/share/elforkane/themes/zakhrafa2/bot_right.png \
    usr/share/elforkane/themes/zakhrafa2/left.png \
    usr/share/elforkane/themes/zakhrafa2/right.png \
    usr/share/elforkane/themes/zakhrafa2/top.png \
    usr/share/elforkane/themes/zakhrafa2/top_left.png \
    usr/share/elforkane/themes/zakhrafa2/top_right.png \
    usr/share/elforkane/default.png \
    usr/share/elforkane/language/launguagerc \
    usr/share/elforkane/tafasir/tafasirInfo \
    usr/share/elforkane/translat/so_abduh.db \
    usr/share/elforkane/translat/translatInfo \
    usr/share/elforkane/reciterInfo \
    usr/share/elforkane/language/elforkane_ar.ts \
    usr/share/elforkane/language/elforkane_en.ts \
    usr/share/elforkane/language/elforkane_fr.ts \
    README.md
