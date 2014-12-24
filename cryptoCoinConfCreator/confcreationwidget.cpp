#include "confcreationwidget.h"
#include "ui_confcreationwidget.h"

#include <QDebug>
#include <QFileDialog>

ConfCreationWidget::ConfCreationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfCreationWidget)
{
    ui->setupUi(this);
    qDebug() << "Os Detected" << detectOperatingSystem() << "\n";
    osString = detectOperatingSystem();

    ui->lineEdit_detectedLocation->setText(detectDataDir());
}

ConfCreationWidget::~ConfCreationWidget()
{
    delete ui;
}

void ConfCreationWidget::on_pushButton_browse_clicked()
{
    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::AnyFile);
    fileDialog.setWindowTitle("Find your .conf file");
    fileDialog.setNameFilter("Conf file (.conf) TIP: Enable \"show hidden files\" in your OS* (*.conf)");

    QStringList fileNames;

    if (fileDialog.exec()) {
        fileNames = fileDialog.selectedFiles();
    }

    if (!fileNames.isEmpty()) {
        ui->lineEdit_detectedLocation->setText(fileNames.at(0));
    }
}

void ConfCreationWidget::on_radioButton_linux_toggled(bool checked)
{
    if (checked) {
        osString = "unix";
    }
    ui->lineEdit_detectedLocation->setText(detectDataDir());
}

void ConfCreationWidget::on_radioButton_mac_toggled(bool checked)
{
    if (checked) {
        osString = "mac";
    }
    ui->lineEdit_detectedLocation->setText(detectDataDir());
}

void ConfCreationWidget::on_radioButton_windows_toggled(bool checked)
{
    if (checked) {
        osString = "windows";
    }
    ui->lineEdit_detectedLocation->setText(detectDataDir());
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
    switch (index) {
    case 0:
        coinName = "ATOMIC";
        break;
    case 1:
        coinName = "bitcoin";
        break;
    case 2:
        coinName = "dogecoin";
        break;
    case 3:
        coinName = "litecoin";
        break;
    case 4:
        coinName = "nxt";
    default:
        break;
    }
    ui->lineEdit_detectedLocation->setText(detectDataDir());
}

void ConfCreationWidget::on_pushButton_cancel_clicked()
{

}

void ConfCreationWidget::on_pushButton_Save_clicked()
{

}

QString ConfCreationWidget::detectDataDir()
{
    if (coinName.isEmpty()) {
        coinName = "ATOMIC";
    }

    if (!osString.isEmpty()) {
        if (osString == "unix") {
            QString returnString = "~/." + coinName;
            qDebug() << returnString;
            return "~/." + coinName;
        } else if (osString == "mac") {
            return "~/Library/Application Support/" + coinName + "/";
        } else if (osString == "windows") {
            return "%APPDATA%\\" + coinName + "\\";
        } else {
            return "";
        }
    } else {
        return "";
    }
}

QString ConfCreationWidget::detectOperatingSystem()
{
#ifdef _WIN32
    ui->radioButton_windows->setChecked(true);
    return "windows";

#elif _WIN64
    ui->radioButton_windows->setChecked(true);
    return "windows";

#elif __unix || __unix__
    ui->radioButton_linux->setChecked(true);
    return "unix";

#elif __linux__
    ui->radioButton_linux->setChecked(true);
    return "unix";

#elif __APPLE__ || __MACH__
    ui->radioButton_mac->setChecked(true);
    return "mac";

#else
    return "";

#endif
}
