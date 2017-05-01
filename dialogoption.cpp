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
#include "dialogoption.h"
#include "ui_dialogoption.h"

#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>
#include <QPainter>
#include <QColorDialog>
#include <QDebug>
#include <QFileDialog>
#include <QDesktopServices>
#include <QTreeWidgetItem>
#include <QTextCodec>
DialogOption::DialogOption(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogOption)
{
    ui->setupUi(this);
    lineEdit=new LineEdit ;
    ui->horizontalLayout_10->addWidget(lineEdit);
    QLocale Arabic(QLocale::Arabic);
    Arabic.setNumberOptions(QLocale::OmitGroupSeparator);
    QString txt="1234567890";
     QString s2 = Arabic.toString(txt.toInt());
    ui->comboBoxNumber->addItem(trUtf8("system"));
    ui->comboBoxNumber->addItem(trUtf8("Arabic")+" ("+txt+")");
    ui->comboBoxNumber->addItem(trUtf8("Arabic India")+" ("+s2+")");
    ui->treeWidget->setColumnHidden(2,true);

    restoreDefaults=false;

    //================================================================




}

DialogOption::~DialogOption()
{
    delete ui;
}


void DialogOption::on_spinBoxFrom_valueChanged(int arg1)
{
     ui->spinBoxTo->setMinimum(arg1);
}

void DialogOption::on_buttonBox_accepted()
{

    listShortcuts.clear();
    int count=ui->treeWidget->topLevelItemCount();
  for(int i=0;i<count;i++){
        QTreeWidgetItem *item=ui->treeWidget->topLevelItem(i);
       listShortcuts.append(item->text(1));

  }

}
    void DialogOption::setShortcutsList(QStringList list)
    {
        int count=ui->treeWidget->topLevelItemCount();
      for(int i=0;i<count;i++){
            QTreeWidgetItem *item=ui->treeWidget->topLevelItem(i);
         item->setText(1,list.at(i));
         //   qDebug()<<item->text(1);
      }
    }

void DialogOption::on_comboBoxLanguage_activated(int )
{
    QMessageBox::information(this,"",trUtf8("The language for this application has been changed.The change will take effect the next time the application is started."));
}


void DialogOption::on_pushButtonColor_clicked()
{

    QColor couleur = QColorDialog::getColor(selectColor, this,trUtf8("Select Color"));
       if( couleur.isValid()){
          selectColor=couleur;
          setSelectColor(couleur);
       }
}
//*****************
void DialogOption::setAppPath(QString path)
{
appPath=path;
    QDir dirImage(path+"/themes");
    QString subdir;
    ui->comboBoxTheme->addItem(trUtf8("default"));
    foreach ( subdir, dirImage.entryList(QDir::AllDirs | QDir::NoDotAndDotDot |
                                         QDir::Hidden )){
        QIcon icon(path+"/themes/"+subdir+"/top.png");
        ui->comboBoxTheme->addItem(icon,subdir);

    }

    QFile file;
    file.setFileName(path+"/language/launguagerc");
    ui->comboBoxLanguage->addItem(trUtf8("system"),"sys");
    if(file.open( QFile::ReadOnly)){
        QTextStream textStream(&file);
        textStream.setCodec(QTextCodec::codecForName("UTF-8"));

        QString line;
        line = textStream.readLine();//premier line
        while (!line.isNull()) {

            QString txt=line.section(",",0,0);
             QString txtdata=line.section(",",1,1);
            ui->comboBoxLanguage->addItem(txt,txtdata);
            line = textStream.readLine();
        }
    }else{
        qDebug()<<"no open : "+path+"/language/launguagerc";
    }
    file.close();
}

void DialogOption::setAutoPlayNext(bool playNext)
{
     ui->radioButtonRepeatAll->setChecked( playNext);
}
   bool DialogOption::getAutoPlayNext()
   {
       return   ui->radioButtonRepeatAll->isChecked();
   }

void DialogOption::setautoRepeatSura(bool repeatSura)
{
     ui->radioButtonRepeatSura->setChecked( repeatSura);
}

 bool DialogOption::getautoRepeatSura()
 {
     return  ui->radioButtonRepeatSura->isChecked();
 }

void DialogOption::setAutoRepeatPage(bool repeatPage)
{
    ui->radioButtonRepeatPage->setChecked( repeatPage);
}
bool DialogOption::getAutoRepeatPage()
{
    return  ui->radioButtonRepeatPage->isChecked();
}

void DialogOption::setAutoRepeatOne(bool repeatOne)
{
    ui->radioButtonRepeatOne->setChecked( repeatOne);
}

bool  DialogOption::getAutoRepeatOne()
{
    return  ui->radioButtonRepeatOne->isChecked();
}

void DialogOption::setAutoRepeatFromTo(bool repeatFromTo)
{
      ui->radioButtonFromTo->setChecked( repeatFromTo);
}
   bool  DialogOption::getAutoRepeatFromTo()
   {
       return ui->radioButtonFromTo->isChecked();
   }

void DialogOption::setRepeatNumber(bool isRepeat)
{
       ui->checkBoxNumRepeat->setChecked(isRepeat);
}
    bool  DialogOption::getRepeatNumber()
    {
        return  ui->checkBoxNumRepeat->isChecked();
    }

void DialogOption::setNumberRepeats(int number)
{
     ui->spinBoxNumRepeat->setValue( number);
}
int DialogOption::getNumberRepeats()
{
    return  ui->spinBoxNumRepeat->value();
}

  int DialogOption::getRepeatAyaFirst()
  {
    return ui->spinBoxFrom->value();
  }

  int DialogOption::getRepeatAyaLast()
  {
      return ui->spinBoxTo->value();
  }

void DialogOption::setSpinMax(int number)
{
    ui->spinBoxFrom->setMaximum(number);
    ui->spinBoxTo->setMaximum(number);
    ui->spinBoxFrom->setMinimum(1);
    ui->spinBoxTo->setMinimum(1);
}

void DialogOption::setInfoDely(int number)
{
     ui->spinBoxsystry->setValue(number);
}
  int DialogOption::getInfoDely()
  {
    return  ui->spinBoxsystry->value();
  }

void DialogOption::setCurTab(int number)
{
    ui->stackedWidget->setCurrentIndex(number);
}

void DialogOption::setAnimEnabled(bool anim)
{
       ui->checkBoxAnimEfect->setChecked( anim);
}
 bool  DialogOption::getAnimEnabled()
 {
     return ui->checkBoxAnimEfect->isChecked();
 }

void DialogOption::setFitInView(bool fit)
{
    ui->checkBoxFitInView->setChecked( fit);
}
bool DialogOption::getFitInView()
{
   return ui->checkBoxFitInView->isChecked();
}

void DialogOption:: setMinimizToTry(bool minimiz)
{
     ui->checkBoxSystry->setChecked( minimiz);
}
bool DialogOption::getMinimizToTry()
{
    return   ui->checkBoxSystry->isChecked();
}

void DialogOption::setTextInIcons(bool textIcons)
{
     ui->checkBoxtool->setChecked( textIcons);
}
bool DialogOption::getTextInIcons()
    {
        return ui->checkBoxtool->isChecked();
    }

void DialogOption::setShowMediaControl(bool show)
{
     ui->checkBoxMediaControl->setChecked(show);
}
  bool DialogOption::getShowMediaControl()
  {
      return  ui->checkBoxMediaControl->isChecked();
  }

void DialogOption::setLng(QString language)
{
    int idxl=ui->comboBoxLanguage->findData(language);
    ui->comboBoxLanguage->setCurrentIndex(idxl);
}
  QString DialogOption::getLng()
  {
      int index=ui->comboBoxLanguage->currentIndex();
      QVariant lngg=ui->comboBoxLanguage->itemData(index);
      return lngg.toString();
  }

void DialogOption::setCadrFolder(QString folder)
{
    int idx= ui->comboBoxTheme->findText(folder);
    ui->comboBoxTheme->setCurrentIndex(idx);
}
 QString DialogOption::getCadrFolder()
 {
     return ui->comboBoxTheme->currentText();
 }

void DialogOption::setShowMenu(bool show)
{
  ui->checkBoxShowMenu->setChecked(show);
}
bool DialogOption::getShowMenu()
{
    return ui->checkBoxShowMenu->isChecked();
}

void DialogOption::setShowSelection(bool show)
{
  ui->checkBoxShowSelection->setChecked(show);
}
bool DialogOption::getShowSelection()
{
    return ui->checkBoxShowSelection->isChecked();
}

void DialogOption::setReciteBasmala(bool recite)
{
   ui->checkBoxReciteBasmala->setChecked(recite);
}
bool DialogOption::getReciteBasmala()
{
    return ui->checkBoxReciteBasmala->isChecked();
}

void DialogOption::setSelectColor(QColor color)
{
    selectColor=color;
     QIcon icon1;
     QPixmap pixColor(30,16);
      QPainter p;
      p.begin(&pixColor);
      color.setAlpha(255);
      p.fillRect(0, 0, 30, 16, color);
      p.end();
     icon1.addPixmap(pixColor);
     ui->pushButtonColor->setIcon(icon1);
}
   QColor DialogOption::getSelectColor()
   {
       return   selectColor;
   }

void DialogOption::setFullSceenAnimated(bool animated)
{
    ui->checkBoxFullType->setChecked(animated);
}
 bool DialogOption::getFullSceenAnimated()
 {
     return ui->checkBoxFullType->isChecked();
 }

void DialogOption::setListFullSceen(QList<QString > listSceenName,int index)
{
//    int i=listSceenName.count();
//    if(i<1){
//        ui->checkBoxFullType->setChecked(false);
//        ui->groupBox->setEnabled(false);
//    }
//    for(int r=0;r<i;r++){
//        QString name=listSceenName.at(r);
//        ui->comboBoxFull->addItem(name);

//    }
//    ui->comboBoxFull->setCurrentIndex(index);
}

void DialogOption::setCurentLocale(int locale)
{
//localeIndex=locale;
ui->comboBoxNumber->setCurrentIndex(locale);
}
 int DialogOption::getCurentLocale()
 {
     return ui->comboBoxNumber->currentIndex();
 }

//     int DialogOption::getFullIndex()
//     {
//         return ui->comboBoxFull->currentIndex();
//     }

void  DialogOption::setshowStandardTool(bool show)
{
    ui->checkBoxStandardTool->setChecked(show);
}
 bool DialogOption::getshowStandardTool()
 {
     return ui->checkBoxStandardTool->isChecked();
 }

 void DialogOption::setfullbackgroundDir(QString folder)
 {
     ui->lineEditFileBgr->setText(folder);
 }

 QString DialogOption::getfullbackgroundDir()
 {
     return ui->lineEditFileBgr->text();
 }

// void DialogOption::setSaveMediaLoaded(bool save)
// {
//     //ui->checkBoxSaveMedia->setChecked(save);
// }

// bool DialogOption::getSaveMediaLoaded()
// {
//     return ui->checkBoxSaveMedia->isChecked();
// }

void DialogOption::on_toolButtonFullOption_clicked()
{
    QString curDirectori= ui->lineEditFileBgr->text();
    if(curDirectori.isEmpty()){
#if QT_VERSION >= 0x050000
    curDirectori=QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
#else
    curDirectori=QDesktopServices::storageLocation(QDesktopServices::PicturesLocation);
#endif
    }

    QString fileName =QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                      curDirectori,
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
    if(!fileName.isEmpty())
    ui->lineEditFileBgr->setText(fileName);



}

void DialogOption::on_comboBoxNumber_activated(int )
{
       QMessageBox::information(this,"",trUtf8("The change will take effect the next time the application is started."));
}



void DialogOption::on_checkBoxStandardTool_clicked()
{
     QMessageBox::information(this,"",trUtf8("The change will take effect the next time the application is started."));
}

void DialogOption::on_treeWidget_itemSelectionChanged()
{
    QTreeWidgetItem *item=  ui->treeWidget->currentItem();
    QString txt=item->text(1);

    lineEdit->setText(txt);

}

void DialogOption::on_buttonBoxKey_clicked(QAbstractButton *button)
{
      if(ui->buttonBoxKey->standardButton(button)==QDialogButtonBox::Apply){
          if(lineEdit->text().isNull())
              return;
          QTreeWidgetItem *item=  ui->treeWidget->currentItem();
            if(item){


                item->setText(1,lineEdit->text());
            }
      }
      if(ui->buttonBoxKey->standardButton(button)==QDialogButtonBox::Reset){
          QTreeWidgetItem *item=  ui->treeWidget->currentItem();
            if(item){
                QString txt=item->text(2);
                item->setText(1,txt);


                lineEdit->setText(txt);
            }
      }
}

void DialogOption::on_buttonBox_clicked(QAbstractButton *button)
{

    if(ui->buttonBox->standardButton(button)==QDialogButtonBox::RestoreDefaults){
        restoreDefaults=true;
        QString settingini=QDir::homePath()+"/.elforkane/setting.ini";
        QFile::remove(settingini);
        QMessageBox::information(this,"",trUtf8("The change will take effect the next time the application is started."));
    }

}
