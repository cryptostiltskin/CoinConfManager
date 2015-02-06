#include "confcreationwidget.h"
#include "ui_confcreationwidget.h"

#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QByteArray>
#include <iostream>

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
    allowedIP = "";

    qDebug() << "Os Detected" << detectOperatingSystem() << "\n";
    osString = detectOperatingSystem();

    if (osString.isEmpty()) {
        QMessageBox emptyMessage;
        emptyMessage.setText("Operating System could not be detected!");
        emptyMessage.setInformativeText("You will need to manual select your system type");
        emptyMessage.setStandardButtons(QMessageBox::Ok);
        emptyMessage.setDefaultButton(QMessageBox::Ok);
        emptyMessage.exec();
    }

    ui->lineEdit_detectedLocation->setText(detectDataDir());
    ui->comboBox_selectCoin->setCurrentIndex(0);
    on_comboBox_selectCoin_currentIndexChanged(0);
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
    default:
        break;
    }
    resetUI();
    ui->lineEdit_detectedLocation->setText(detectDataDir());
    loadExistingFromConf();
}

void ConfCreationWidget::on_pushButton_cancel_clicked()
{
    this->close();
    emit confWidgetClosing();
}

void ConfCreationWidget::on_pushButton_Save_clicked()
{
    bool written = writeConfFile();
    qDebug() << "Conf file written? " << written << "\n";
}

QString ConfCreationWidget::detectDataDir()
{
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
        confText.append(ui->listWidget_nodes->item(i)->text());
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
        int spinMax = ui->spinBox_maxConnections->value();
        confText.append(QString::number(spinMax));
        confText.append("\n");
    }

    if (ui->spinBox_RPCTimeout->value() != 0) {
        confText.append("rpctimeout=");
        int spinTimeout = ui->spinBox_RPCTimeout->value();
        confText.append(QString::number(spinTimeout));
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
        QMessageBox emptyMessage;
        emptyMessage.setText("You have nothing to save!");
        emptyMessage.setInformativeText("You haven't entered any settings to save");
        emptyMessage.setStandardButtons(QMessageBox::Ok);
        emptyMessage.setDefaultButton(QMessageBox::Ok);
        emptyMessage.exec();
        return false;
    }

    // Check that we can open the file and write to it
    QFile confFile(detectDataDir());

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
            qDebug() << "erorr\n";
            QMessageBox errorMessage;
            errorMessage.setText("Configuration file failed to write!");
            errorMessage.setInformativeText("Double check your directory and permissions before trying again");
            errorMessage.setStandardButtons(QMessageBox::Ok);
            errorMessage.setDefaultButton(QMessageBox::Ok);
            errorMessage.exec();
            return false;
        } else {
            qDebug() << "no error\n";
            QMessageBox writeMessage;
            writeMessage.setText("Configuration file writen!, " \
                                 "Your settings have been written to the conf file.\n");
            writeMessage.setInformativeText("Important: You must restart your client before " \
                                            "settings will be applied.");
            writeMessage.setStandardButtons(QMessageBox::Ok);
            writeMessage.setDefaultButton(QMessageBox::Ok);
            writeMessage.exec();
        }
    }
    confFile.close();
    return true;
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
QStringList ConfCreationWidget::get_ConfFileStrings()
{
    QFile confFile(detectDataDir());
    QStringList confDataList;

    // Quit if there is nothing to do.
    if (!confFile.exists()) {
        return confDataList;
    }

    // Check that we can open the file
    if (!confFile.open(QIODevice::ReadOnly)) {
        return confDataList;
    }

    QTextStream inStream(&confFile);
    while (!inStream.atEnd()) {
        // Read line as long as it is < 100 chars (in case long password)
        QString newString = inStream.readLine(100);
        confDataList << newString;
    }
    return confDataList;
}

QString ConfCreationWidget::get_confDirectory()
{
    return confDirectory;
}

bool ConfCreationWidget::get_serverEnabled()
{
    return serverEnabled;
}

int ConfCreationWidget::get_RPCPort()
{
    return RPCPort;
}

QString ConfCreationWidget::get_RPCUser()
{
    return RPCUser;
}

QString ConfCreationWidget::get_RPCPassword()
{
    return RPCPassword;
}

bool ConfCreationWidget::get_generateEnabled()
{
    return generateEnabled;
}

bool ConfCreationWidget::get_addNodesEnabled()
{
    return addNodesEnabled;
}

bool ConfCreationWidget::get_connectOnlyEnabled()
{
    return connectOnlyEnabled;
}

bool ConfCreationWidget::get_testnetEnabled()
{
    return testnetEnabled;
}

bool ConfCreationWidget::get_startMinEnabled()
{
    return startMinEnabled;
}

bool ConfCreationWidget::get_startTrayedEnabled()
{
    return startTrayedEnabled;
}

bool ConfCreationWidget::get_receiveByIPEnabled()
{
    return receiveByIPEnabled;
}

int ConfCreationWidget::get_maxConnections()
{
    return maxConnections;
}

int ConfCreationWidget::get_rpcTimeout()
{
    return rpcTimeout;
}

QString ConfCreationWidget::get_coinName()
{
    return coinName;
}

void ConfCreationWidget::loadExistingFromConf()
{
    QStringList existingData = get_ConfFileStrings();

    for (int i = 0; i < existingData.count(); i++) {
        QString line = existingData.at(i);

        if (line.section("=", 0, 0) == "rpcuser") {
            RPCUser = line.section("=", 1, 1);
            ui->lineEdit_rpcUser->setText(RPCUser);

        } else if (line.section("=", 0, 0) == "rpcpassword") {
            RPCPassword = line.section("=", 1, 1);
            ui->lineEdit_rpcPassword->setText(RPCPassword);

        } else if (line.section("=", 0, 0) == "server") {
            serverEnabled = line.section("=", 1, 1).toInt();
            ui->checkBox_server->setChecked(serverEnabled);

        } else if (line.section("=", 0, 0) == "rpcport") {
            RPCPort = line.section("=", 1, 1).toInt();
            ui->lineEdit_rpcPort->setText(QString::number(RPCPort));

        } else if (line.section("=", 0, 0) == "gen") {
            generateEnabled = line.section("=", 1, 1).toInt();
            ui->checkBox_generate->setChecked(generateEnabled);

        } else if (line.section("=", 0, 0) == "addnode") {
            ui->radioButton_addNodes->setChecked(true);
            QString node = line.section("=", 1, 1);
            ui->listWidget_nodes->addItem(node);

        } else if (line.section("=", 0, 0) == "connect") {
            ui->radioButton_connectOnly->setChecked(true);
            QString node = line.section("=", 1, 1);
            ui->listWidget_nodes->addItem(node);

        } else if (line.section("=", 0, 0) == "testnet") {
            testnetEnabled = line.section("=", 1, 1).toInt();
            ui->checkBox_testnet->setChecked(testnetEnabled);

        } else if (line.section("=", 0, 0) == "min") {
            startMinEnabled = line.section("=", 1, 1).toInt();
            ui->checkBox_startMini->setChecked(startMinEnabled);

        } else if (line.section("=", 0, 0) == "minimizetotray") {
            startTrayedEnabled = line.section("=", 1, 1).toInt();
            ui->checkBox_startTrayed->setChecked(startTrayedEnabled);

        } else if (line.section("=", 0, 0) == "allowreceivebyip") {
            receiveByIPEnabled = line.section("=", 1, 1).toInt();
            ui->checkBox_receiveByIP->setChecked(receiveByIPEnabled);

        } else if (line.section("=", 0, 0) == "maxconnections") {
            maxConnections = line.section("=", 1, 1).toInt();
            ui->spinBox_maxConnections->setValue(maxConnections);

        } else if (line.section("=", 0, 0) == "rpctimeout") {
            rpcTimeout = line.section("=", 1, 1).toInt();
            ui->spinBox_RPCTimeout->setValue(rpcTimeout);

        } else if (line.section("=", 0, 0) == "rpcallowip") {
            allowedIP = line.section("=", 1, 1);
            ui->lineEdit_RPCAllowIP->setText(allowedIP);

        } else if (line.section("=", 0, 0) == "rpcconnect") {
            rpcConnectForward = line.section("=", 1, 1);
            ui->lineEdit_RPCConnect->setText(rpcConnectForward);

        } else if (line.section("=", 0, 0) == "proxy") {
            proxy = line.section("=", 1, 1);
            ui->lineEdit_socks4->setText(proxy);
        }
    }
}

void ConfCreationWidget::resetUI()
{
    ui->lineEdit_detectedLocation->clear();
    ui->checkBox_server->setChecked(false);
    ui->lineEdit_rpcPort->clear();
    ui->lineEdit_rpcUser->clear();
    ui->lineEdit_rpcPassword->clear();
    ui->checkBox_generate->setChecked(false);
    ui->listWidget_nodes->clear();
    ui->checkBox_testnet->setChecked(false);
    ui->checkBox_startMini->setChecked(false);
    ui->checkBox_startTrayed->setChecked(false);
    ui->checkBox_receiveByIP->setChecked(false);
    ui->spinBox_maxConnections->setValue(0);
    ui->spinBox_RPCTimeout->setValue(0);
    ui->lineEdit_RPCAllowIP->clear();
    ui->lineEdit_RPCConnect->clear();
    ui->lineEdit_socks4->clear();
}
