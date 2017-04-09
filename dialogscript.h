#ifndef DIALOGSCRIPT_H
#define DIALOGSCRIPT_H

#include <QDialog>
#include <QAbstractButton>
namespace Ui {
    class DialogScript;
}

class DialogScript : public QDialog
{
    Q_OBJECT

public:
    explicit DialogScript(QWidget *parent = 0);
    ~DialogScript();
    void setcomboItems(QStringList list);
    void setUrlName(QString url);
    void setPathCostum(QString arg);
private slots:
    void on_comboBoxSura_currentIndexChanged(int index);

    void on_spinBoxFrom_valueChanged(int arg1);

    void on_buttonBox_clicked(QAbstractButton *button);
    void createScript();
    bool getFileExists(QString path);
private:
    Ui::DialogScript *ui;
    QString pathCostum;
};

#endif // DIALOGSCRIPT_H
