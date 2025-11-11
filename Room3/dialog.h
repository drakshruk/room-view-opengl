#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    double roofAtten[3];
    double lampAtten[3];
    double carAtten[3];

    bool carcas;
    bool split;
    bool iDrive;

signals:
    void valuesChanged();

private slots:
    void on_roofConstEdit_editingFinished();
    void on_roofLinearEdit_editingFinished();
    void on_roofQuadEdit_editingFinished();

    void on_lampConstEdit_editingFinished();
    void on_lampLinearEdit_editingFinished();
    void on_lampQuadEdit_editingFinished();

    void on_carConstEdit_editingFinished();
    void on_carLinearEdit_editingFinished();
    void on_carQuadEdit_editingFinished();

    void on_carcasBox_clicked();
    void on_splitBox_clicked();
    void on_carBox_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
