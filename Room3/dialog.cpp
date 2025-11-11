#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    roofAtten[0] = 0; roofAtten[1] = 0.005; roofAtten[2] = 0.0001;
    lampAtten[0] = 0; lampAtten[1] = 0.005; lampAtten[2] = 0.0005;
    carAtten[0] = 0; carAtten[1] = 0.005; carAtten[2] = 0.0005;

    carcas = false;
    split = false;
    iDrive = false;
    ui->carConstEdit->setText(QString::number(carAtten[0]));
    ui->carLinearEdit->setText(QString::number(carAtten[1]));
    ui->carQuadEdit->setText(QString::number(carAtten[2]));

    ui->roofConstEdit->setText(QString::number(roofAtten[0]));
    ui->roofLinearEdit->setText(QString::number(roofAtten[1]));
    ui->roofQuadEdit->setText(QString::number(roofAtten[2]));

    ui->lampConstEdit->setText(QString::number(lampAtten[0]));
    ui->lampLinearEdit->setText(QString::number(lampAtten[1]));
    ui->lampQuadEdit->setText(QString::number(lampAtten[2]));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_roofConstEdit_editingFinished()
{
    roofAtten[0] = ui->roofConstEdit->text().toDouble();
    emit valuesChanged();
}

void Dialog::on_roofLinearEdit_editingFinished()
{
    roofAtten[1] = ui->roofLinearEdit->text().toDouble();
    emit valuesChanged();
}

void Dialog::on_roofQuadEdit_editingFinished()
{
    roofAtten[2] = ui->roofQuadEdit->text().toDouble();
    emit valuesChanged();
}

void Dialog::on_lampConstEdit_editingFinished()
{
    lampAtten[0] = ui->lampConstEdit->text().toDouble();
    emit valuesChanged();
}

void Dialog::on_lampLinearEdit_editingFinished()
{
    lampAtten[1] = ui->lampLinearEdit->text().toDouble();
    emit valuesChanged();
}

void Dialog::on_lampQuadEdit_editingFinished()
{
    lampAtten[2] = ui->lampQuadEdit->text().toDouble();
    emit valuesChanged();
}

void Dialog::on_carConstEdit_editingFinished()
{
    carAtten[0] = ui->carConstEdit->text().toDouble();
    emit valuesChanged();
}

void Dialog::on_carLinearEdit_editingFinished()
{
    carAtten[1] = ui->carLinearEdit->text().toDouble();
    emit valuesChanged();
}

void Dialog::on_carQuadEdit_editingFinished()
{
    carAtten[2] = ui->carQuadEdit->text().toDouble();
    emit valuesChanged();
}

void Dialog::on_carcasBox_clicked()
{
    carcas = !carcas;
    emit valuesChanged();
}

void Dialog::on_splitBox_clicked()
{
    split = !split;
    emit valuesChanged();
}

void Dialog::on_carBox_clicked()
{
    iDrive = !iDrive;
    emit valuesChanged();
}
