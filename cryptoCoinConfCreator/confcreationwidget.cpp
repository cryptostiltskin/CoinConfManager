#include "confcreationwidget.h"
#include "ui_confcreationwidget.h"

#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>

ConfCreationWidget::ConfCreationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfCreationWidget)
{
    ui->setupUi(this);

    serverEnabled = false;
    generateEnabled = false;
    addNodesEnabled = true;
    connectOnlyEnabled = false;
    testnetEnabled = false;
    startMinEnabled = false;
    startTrayedEnabled = false;
    receiveByIPEnabled = false;

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
    QApplication::quit();
}

void ConfCreationWidget::on_pushButton_Save_clicked()
{
    writeConfFile();
}

QString ConfCreationWidget::detectDataDir()
{
    if (coinName.isEmpty()) {
        coinName = "ATOMIC";
    }

    if (!osString.isEmpty()) {
        if (osString == "unix") {
            QString returnString = QDir::homePath() + "/." + coinName + "/" + coinName + ".conf";
            return returnString;
        } else if (osString == "mac") {
            return QDir::homePath() + "/Library/Application Support/" + coinName + "/" + coinName + ".conf";
        } else if (osString == "windows") {
            return "%APPDATA%\\" + coinName + "\\" + coinName + ".conf";;
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

QString ConfCreationWidget::formConfText() {
    QString confText;

    // Basic Settings

    if (serverEnabled) {
        confText.append("server=1\n");
    }

    if (!ui->lineEdit_rpcPort->text().isEmpty()) {
        confText.append("rpcport=");
        confText.append(ui->lineEdit_rpcPort->text());
        qDebug() << ui->lineEdit_rpcPort->text() << "\n";
        confText.append("\n");
    }

    if (!ui->lineEdit_rpcUser->text().isEmpty()) {
        confText.append("rpcuser=");
        confText.append(ui->lineEdit_rpcUser->text());
        confText.append("\n");
    }

    if (!ui->lineEdit_rpcPassword->text().isEmpty()) {
        confText.append("rpcpassword=");
        confText.append(ui->lineEdit_rpcPassword->text());
        confText.append("\n");
    }

    if (generateEnabled) {
        confText.append("gen=1");
        confText.append("\n");
    }

    // Node settings

    // eg connect= or addnode= depending on the selected mode
    QString nodePreText;
    if (addNodesEnabled) {
        nodePreText = "addnode=";
    } else if (connectOnlyEnabled) {
        nodePreText = "connect=";
    }

    for (int i = 0; i < ui->listWidget_nodes->count(); i++) {
        confText.append(nodePreText);
        confText.append(ui->listWidget_nodes->itemAt(i, 0)->text());
        confText.append("\n");
    }

    // Advanced/other settings

    if (testnetEnabled) {
        confText.append("testnet=1");
        confText.append("\n");
    }

    if (startMinEnabled) {
        confText.append("min=1");
        confText.append("\n");
    }

    if (startTrayedEnabled) {
        confText.append("minimizetotray=1");
        confText.append("\n");
    }

    if (receiveByIPEnabled) {
        confText.append("allowreceivebyip=1");
        confText.append("\n");
    }

    if (ui->spinBox_maxConnections->value() != 0) {
        confText.append("maxconnections=");
        confText.append(ui->spinBox_maxConnections->value());
        confText.append("\n");
    }

    if (ui->spinBox_RPCTimeout->value() != 0) {
        confText.append("rpctimeout=");
        confText.append(ui->spinBox_RPCTimeout->value());
        confText.append("\n");
    }

    if (!ui->lineEdit_RPCAllowIP->text().isEmpty()) {
        confText.append("rpcallowip=");
        confText.append(ui->lineEdit_RPCAllowIP->text());
        confText.append("\n");
    }

    if (!ui->lineEdit_RPCConnect->text().isEmpty()) {
        confText.append("rpcconnect=");
        confText.append(ui->lineEdit_RPCConnect->text());
        confText.append("\n");
    }

    if (!ui->lineEdit_socks4->text().isEmpty()) {
        confText.append("proxy=");
        confText.append(ui->lineEdit_socks4->text());
        confText.append("\n");
    }

    return confText;
}

bool ConfCreationWidget::writeConfFile() {
    // Exit the function if there is nothing to write
    if (formConfText().isEmpty()) {
        return false;
    }

    // Check that we can open the file and write to it
    QFile confFile(ui->lineEdit_detectedLocation->text());

    if (confFile.exists()) {
        qDebug() << "File already exists\n" << confFile.fileName() << "\n";
        QMessageBox overwriteMessage;
        overwriteMessage.setText("Configuration file already exists!");
        overwriteMessage.setInformativeText("Do you want to overwrite your configuration file?");
        overwriteMessage.setStandardButtons(QMessageBox::Cancel | QMessageBox::Save);
        overwriteMessage.setDefaultButton(QMessageBox::Cancel);
        int overwriteReturn = overwriteMessage.exec();

        switch (overwriteReturn) {
        case QMessageBox::Cancel:
            return false;
            break;
        case QMessageBox::Save:
            break;
        default:
            return false;
            break;
        }
    } else {
        qDebug() << "File does not exist\n" << confFile.fileName() << "\n";
    }

    if (!confFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "sorry dave\n";
        return false;
    } else {
        QTextStream out(&confFile);
        out << formConfText();
        if (confFile.error()) {
            qDebug() << "ERRPR\n";
            return false;
        } else {
            qDebug() << "noerr\n";
            return true;
        }
    }
    confFile.close();
    return false;
}

void ConfCreationWidget::on_pushButton_addNode_clicked()
{
    if (ui->lineedit_enterIP->text().isEmpty()) {
        QMessageBox blankLine;
        blankLine.setText("You have to put an IP address in there");
        blankLine.setInformativeText("Please enter an IP address and port number.");
        blankLine.setStandardButtons(QMessageBox::Ok);
        blankLine.setDefaultButton(QMessageBox::Ok);
        blankLine.exec();
        return;
    } else {
        ui->listWidget_nodes->addItem(ui->lineedit_enterIP->text());
        ui->lineedit_enterIP->clear();
    }
}

void ConfCreationWidget::on_pushButton_clearNodeList_clicked()
{
    QMessageBox clearMessage;
    clearMessage.setText("Clear the node list!");
    clearMessage.setInformativeText("Are you sure?");
    clearMessage.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
    clearMessage.setDefaultButton(QMessageBox::Cancel);
    int clearReturn = clearMessage.exec();

    switch (clearReturn) {
    case QMessageBox::Cancel:
        break;
    case QMessageBox::Ok:
        ui->listWidget_nodes->clear();
        break;
    default:
        break;
    }
}
