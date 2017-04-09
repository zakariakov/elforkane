#ifndef DIALOGFULLSCEEN_H
#define DIALOGFULLSCEEN_H

#include <QDialog>

namespace Ui {
    class Dialogfullsceen;
}

class Dialogfullsceen : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogfullsceen(QWidget *parent = 0);
    ~Dialogfullsceen();
       QString bgrDir;
public slots:
    void setBackground(QString bgr);
private slots:


    void on_toolButtonOpen_clicked();

    void on_buttonBox_accepted();

private:
    Ui::Dialogfullsceen *ui;

};

#endif // DIALOGFULLSCEEN_H
