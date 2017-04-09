#include "dialogfullsceen.h"
#include "ui_dialogfullsceen.h"
#include <QDesktopServices>
#include <QFileDialog>
Dialogfullsceen::Dialogfullsceen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogfullsceen)
{
    ui->setupUi(this);
}

Dialogfullsceen::~Dialogfullsceen()
{
    delete ui;
}


void Dialogfullsceen::on_toolButtonOpen_clicked()
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


void Dialogfullsceen::on_buttonBox_accepted()
{
    bgrDir= ui->lineEditFileBgr->text();
}
 void Dialogfullsceen::setBackground(QString bgr)
 {
     ui->lineEditFileBgr->setText(bgr);
 }
