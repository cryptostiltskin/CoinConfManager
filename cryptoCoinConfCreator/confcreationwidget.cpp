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
    if (checked) {
        selectedOS = 0;
    }
}

void ConfCreationWidget::on_radioButton_mac_toggled(bool checked)
{
    if (checked) {
        selectedOS = 1;
    }
}

void ConfCreationWidget::on_radioButton_windows_toggled(bool checked)
{
    if (checked) {
        selectedOS = 2;
    }
}

void ConfCreationWidget::on_checkBox_server_toggled(bool checked)
{
    serverEnabled = checked;
}

void ConfCreationWidget::on_checkBox_generate_toggled(bool checked)
{
    generateEnabled = checked;
}

void ConfCreationWidget::on_radioButton_addNodes_toggled(bool checked)
{
    addNodesEnabled = checked;
}

void ConfCreationWidget::on_radioButton_connectOnly_toggled(bool checked)
{
    connectOnlyEnabled = checked;
}

void ConfCreationWidget::on_checkBox_testnet_toggled(bool checked)
{
    testnetEnabled = checked;
}

void ConfCreationWidget::on_checkBox_startMini_toggled(bool checked)
{
    startMinEnabled = checked;
}

void ConfCreationWidget::on_checkBox_startTrayed_toggled(bool checked)
{
    startTrayedEnabled = checked;
}

void ConfCreationWidget::on_checkBox_receiveByIP_toggled(bool checked)
{
    receiveByIPEnabled = checked;
}

void ConfCreationWidget::on_comboBox_selectCoin_currentIndexChanged(int index)
{
    selectCoinIndex = index;
}

void ConfCreationWidget::on_pushButton_cancel_clicked()
{

}

void ConfCreationWidget::on_pushButton_Save_clicked()
{

}
