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
#include "dialogaddreciter.h"
#include "ui_dialogaddreciter.h"
#include<QFile>
#include<QFileDialog>
#include<QStackedWidget>
#include<QToolButton>
#include<QDebug>
#include<QTextEdit>
#include<QComboBox>

DialogAddReciter::DialogAddReciter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddReciter)
{
    ui->setupUi(this);
    mProcess=new QProcess;
    connect(mProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(readStandardOutput()));
    connect(mProcess,SIGNAL(readyReadStandardError()),this,SLOT(readStandardError()));

    ui->comboBoxRiwayat->addItem(trUtf8("Default hafs"),("default"));
    ui->comboBoxRiwayat->addItem(trUtf8("Riwayat hafs"),("hafs"));
    ui->comboBoxRiwayat->addItem(trUtf8("Riwayat warsh"),("warsh"));
    ui->comboBoxRiwayat->addItem(trUtf8("Riwayat hafs by colors"),("hafs-colors"));
    ui->comboBoxRiwayat->addItem(trUtf8("Riwayat warsh by colors"),("warsh-colors"));
}

DialogAddReciter::~DialogAddReciter()
{
    delete ui;
}

void DialogAddReciter::on_toolButtonFileName_clicked()
{
    QString dirName = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                        QString(),
                                                        QFileDialog::ShowDirsOnly
                                                        |QFileDialog::DontResolveSymlinks);
    if(!dirName.isEmpty())
        ui->lineEditFileName->setText(dirName);
}

void DialogAddReciter::on_buttonBox_clicked(QAbstractButton *button)
{
    mProcess->close();
    if(ui->buttonBox->standardButton(button)==QDialogButtonBox::Ok){
        if(ui->lineEditReciterName->text().isEmpty())
            return;
        if(ui->lineEditFileName->text().isEmpty())
            return;
    }
    reciterName=ui->lineEditReciterName->text();
    dirName=ui->lineEditFileName->text();
    int index=ui->comboBoxRiwayat->currentIndex();
    riwayaName=ui->comboBoxRiwayat->itemData(index).toString();
    urlName=ui->lineEditUrl->text();
    dataName=dirName+"|"+urlName+"|"+riwayaName;
    this->accept();
}
//--------set----------------------
void DialogAddReciter::setReceterName(QString name)
{
    ui->lineEditReciterName->setText(name);
}

void DialogAddReciter::setDirName(QString name)
{
    ui->lineEditFileName->setText(name);
}

void DialogAddReciter::setUrlName(QString name)
{
    ui->lineEditUrl->setText(name);

}

void DialogAddReciter::setRiwayaName(QString arg)
{
    int ind=0;
    if(arg=="default"){
        ind=0;
    }else if(arg=="hafs"){
        ind=1;
    }else if(arg=="warsh"){
        ind=2;
    }else if(arg=="hafs-colors"){
        ind=3;
    }else if(arg=="warsh-colors"){
        ind=4;
    }

    ui->comboBoxRiwayat->setCurrentIndex(ind);

}
//----get-----
QString DialogAddReciter::getReciterName()
{
    return reciterName;
}
QString DialogAddReciter::getDataName()
{
    return dataName;
}


//TODO FIX this
void DialogAddReciter::on_toolButtonDownLoad_toggled(bool checked)
{
    mProcess->close();
    ui->stackedWidget->setCurrentIndex(checked);
}



void DialogAddReciter::on_pushButtonStop_clicked()
{
    mProcess->close();
    ui->stackedWidget->setCurrentIndex(1);
}

void DialogAddReciter::on_toolButtonSeectAll_clicked(bool checked)
{
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        QListWidgetItem *item=ui->listWidget->item(i);
        if(checked)
            item->setCheckState(Qt::Checked);
        else
            item->setCheckState(Qt::Unchecked);
    }
}

void DialogAddReciter::setDownload(bool arg)
{
    ui->toolButtonDownLoad->setVisible(arg);
}

void DialogAddReciter::setListItems( QStringList list)
{
    for(int i=0;i<list.count();i++){

        QString line=list.at(i);
        QString txt=line.section(",",0,0);
        QString data=line.section(",",1);
        QListWidgetItem *item=new QListWidgetItem(ui->listWidget);
        item->setText(txt);
        item->setData(Qt::UserRole,data);
        item->setCheckState(Qt::Unchecked);

    }

}

bool DialogAddReciter::creatListDownload()
{
    QString url=ui->lineEditUrl->text();
    QString reciter = url.section('/', -1);
    listDownload.clear();
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        QListWidgetItem *item=ui->listWidget->item(i);
        if(item->checkState()==Qt::Checked){
            int surat=i+1;


            QString sura="000"+QString::number(surat);
            QString txt=item->data(Qt::UserRole).toString();
            int max=txt.section(",",1,1).toInt();


            //            ui->textEditOut->insertPlainText(item->text()+ "=============================\n");

            downloadSora( sura, max);
            listDownload<<"echo \"done :"+item->text()+"\" \n";

        }

    }

    return true;

}

void DialogAddReciter::downloadSora(QString sura,int max)
{

    QString prog =ui->comboBox->currentText();

    QString url=ui->lineEditUrl->text();
    for (int i = 0; i < max; ++i) {
        QString aya="000"+QString::number(i+1);
        QString  soundName=sura.right(3)+aya.right(3) ;

        listDownload<<"echo \"downloading :=========================="+soundName+".mp3\" \n";
        listDownload <<prog +" "+url+"/"+soundName+".mp3 \n";
        //        ui->textEditOut->insertPlainText( "wget -c  "+url+"/"+soundName+".mp3 \n");

    }


}
void DialogAddReciter::readStandardOutput()
{
    ui->textEditOut->insertPlainText(mProcess->readAllStandardOutput());
    QTextCursor cursor( ui->textEditOut->document());
    cursor.movePosition(QTextCursor::End);
    ui->textEditOut->setTextCursor(cursor);
}
void DialogAddReciter::readStandardError()
{
    ui->textEditOut->insertPlainText(mProcess->readAllStandardError());
    QTextCursor cursor( ui->textEditOut->document());
    cursor.movePosition(QTextCursor::End);
    ui->textEditOut->setTextCursor(cursor);
}

void DialogAddReciter::on_pushButtonSaveScript_clicked()
{
    QString dirPath=ui->lineEditFileName->text();

    if(dirPath.startsWith("audio/"))
        dirPath=QDir::homePath()+"/.elforkane/"+ui->lineEditFileName->text();

    QDir dir;
    if(!QFile::exists(dirPath))
        dir.mkpath(dirPath) ;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    dirPath+"/download-sh",
                                                    "*");

    qDebug()<<fileName;
    if(fileName.isEmpty())
        return;

    if(creatListDownload()){

        qApp->processEvents();

        QFile fileReciter(fileName);
        if (!fileReciter.open(QFile::WriteOnly)){
            return ;
        }
        QTextStream out(&fileReciter);
        out<<"#!/bin/sh \n";
        foreach (QString txt, listDownload) {
            out<<txt;
        }

    }
}

void DialogAddReciter::on_pushButtonStart_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    if(creatListDownload()){

        qApp->processEvents();

        QFile fileReciter(QDir::homePath()+"/.elforkane/out");
        if (!fileReciter.open(QFile::WriteOnly)){
            return ;
        }
        QTextStream out(&fileReciter);
        out<<"#!/bin/sh \n";
        foreach (QString txt, listDownload) {
            out<<txt;
        }


        qApp->processEvents();
        QDir dir;
        QString dirPath=ui->lineEditFileName->text();

        if(dirPath.startsWith("audio/"))
            dirPath=QDir::homePath()+"/.elforkane/"+ui->lineEditFileName->text();

        if(!QFile::exists(dirPath))
            dir.mkpath(dirPath) ;


        mProcess->setWorkingDirectory(dirPath);
        dir.setCurrent(dirPath);
        mProcess->start("/bin/sh  "+ fileReciter.fileName());

    }

}
