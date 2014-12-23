#include "confcreationwidget.h"
#include "ui_confcreationwidget.h"

ConfCreationWidget::ConfCreationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfCreationWidget)
{
    ui->setupUi(this);
}

ConfCreationWidget::~ConfCreationWidget()
{
    delete ui;
}

void ConfCreationWidget::on_pushButton_browse_clicked()
{

}

void ConfCreationWidget::on_radioButton_linux_toggled(bool checked)
{

}

void ConfCreationWidget::on_radioButton_mac_toggled(bool checked)
{

}

void ConfCreationWidget::on_radioButton_windows_toggled(bool checked)
{

}

void ConfCreationWidget::on_checkBox_server_toggled(bool checked)
{

}

void ConfCreationWidget::on_checkBox_generate_toggled(bool checked)
{

}

void ConfCreationWidget::on_radioButton_addNodes_toggled(bool checked)
{

}

void ConfCreationWidget::on_radioButton_connectOnly_toggled(bool checked)
{

}

void ConfCreationWidget::on_checkBox_testnet_toggled(bool checked)
{

}

void ConfCreationWidget::on_checkBox_startMini_toggled(bool checked)
{

}

void ConfCreationWidget::on_checkBox_startTrayed_toggled(bool checked)
{

}

void ConfCreationWidget::on_checkBox_receiveByIP_toggled(bool checked)
{

}

void ConfCreationWidget::on_comboBox_selectCoin_currentIndexChanged(int index)
{

}

void ConfCreationWidget::on_pushButton_cancel_clicked()
{

}

void ConfCreationWidget::on_pushButton_Save_clicked()
{

}
