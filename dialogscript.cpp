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
#include "dialogscript.h"
#include "ui_dialogscript.h"
#include <QDebug>
#include <QAbstractButton>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include<QStandardPaths>
DialogScript::DialogScript(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogScript)
{
    ui->setupUi(this);
}

DialogScript::~DialogScript()
{
    delete ui;
}

 void DialogScript::setcomboItems(QStringList list)
 {
     for(int i=0;i<list.count();i++){
         QString line=list.at(i);
         QString txt=line.section(",",0,0);
          QString data=line.section(",",1);
         ui->comboBoxSura->addItem(txt,data);
     }
 }

void DialogScript::setUrlName(QString url)
     {
      ui->lineEdit->setText(url);
     }

void DialogScript::setPathCostum(QString arg)
{
    pathCostum=arg;
}

void DialogScript::on_comboBoxSura_currentIndexChanged(int index)
{
    QString txt=ui->comboBoxSura->itemData(index).toString();
    int max=txt.section(",",1,1).toInt();
   ui->spinBoxTo->setMaximum(max);
   ui->spinBoxFrom->setMaximum(max);
      ui->spinBoxFrom->setValue(1);
      ui->spinBoxTo->setValue(max);
}

void DialogScript::on_spinBoxFrom_valueChanged(int arg1)
{
       ui->spinBoxTo->setMinimum(arg1);
}

void DialogScript::on_buttonBox_clicked(QAbstractButton *button)
{
    if(ui->buttonBox->standardButton(button)==QDialogButtonBox::Apply){
      createScript();
    }else if(ui->buttonBox->standardButton(button)==QDialogButtonBox::Ok){
        createScript();
        this->accept();
    }

}

void DialogScript::createScript()
{
   int surat=ui->comboBoxSura->currentIndex()+1;
    QString url=ui->lineEdit->text();
    QString reciter = url.section('/', -1);
     QString sura="000"+QString::number(surat);
QString destPath=QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
QDir dir(destPath);
if(!dir.exists())
    destPath=QDir::homePath();

QString distFile=destPath+"/"+reciter+"_"+QString::number(surat);


QFile fileReciter(distFile);
    if (!fileReciter.open(QFile::WriteOnly)){
          return ;
      }
    QTextStream out(&fileReciter);
    out<<"#!/bin/sh \n";
    if(ui->checkBoxNoExists->isChecked()){

        for(int i=1;i<ui->spinBoxTo->maximum()+1;i++)
        {
           QString aya="000"+QString::number(i);
           QString  soundName=sura.right(3)+aya.right(3) ;
           if(getFileExists("/"+soundName+".mp3")==false)
           out<< "wget -c  "+url+"/"+soundName+".mp3 \n";
        }
    }else{
        for(int i=ui->spinBoxFrom->value();i<ui->spinBoxTo->value()+1;i++)
        {

           QString aya="000"+QString::number(i);
           QString  soundName=sura.right(3)+aya.right(3) ;

           out<< "wget -c  "+url+"/"+soundName+".mp3 \n";
        }
    }
    QMessageBox::information(this,"","package genirated in \n "+
                           distFile);

}

bool DialogScript::getFileExists(QString path)
{

    QDir appDir(qApp->applicationDirPath());

    appDir.cdUp();
   QString appPath=  appDir.absolutePath()+"/share/elforkane";
    if(QFile::exists(pathCostum+path)){
     //البحث عن الاية حسب ما ادخله المستخدم
     qDebug()<<pathCostum+path;
        return true;
   }else if(QFile::exists(appPath+"/"+pathCostum+path)==true){
       //usr/shar/elforkane/audio/recetername----البحث عن الاية في دليل البرنامج
   qDebug()<<"exist in apppath"<<appPath+"/"+pathCostum+path;
        return true;
   }else if(QFile::exists(QDir::homePath()+"/.elforkane/"+pathCostum+path)==true){
       //home/user/.elforkane/audio/recetername----البحث عن الاية في دليل المستخدم
 qDebug()<<"exist in home : "<<QDir::homePath()+"/.elforkane/"+pathCostum+path;
        return true;
   }
    return false;
}
