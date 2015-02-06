// ~CryptAxe

#ifndef CONFCREATIONWIDGET_H
#define CONFCREATIONWIDGET_H

#include <QWidget>
#include <QStringList>

namespace Ui {
class ConfCreationWidget;
}

class ConfCreationWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ConfCreationWidget(QWidget *parent = 0);
    ~ConfCreationWidget();
    // Detect the data directory (default location based on OS)
    QString detectDataDir();
    // Use compiler macros to detect OS
    QString detectOperatingSystem();
    // Returns the text to be added to the conf file
    QString formConfText();
    /*
     * Writes the text returned by formConfText() to the
     * selected file after:
     *
     * -User confirms location
     * -Double check if over writing file
     *
     * @return true if file written
     *
     */
    bool writeConfFile();
    // List of strings read line by line from existing conf
    QStringList get_ConfFileStrings();

    // Get Functions
    QString get_confDirectory();
    bool get_serverEnabled();
    int get_RPCPort();
    QString get_RPCUser();
    QString get_RPCPassword();
    bool get_generateEnabled();
    bool get_addNodesEnabled();
    bool get_connectOnlyEnabled();
    bool get_testnetEnabled();
    bool get_startMinEnabled();
    bool get_startTrayedEnabled();
    bool get_receiveByIPEnabled();
    int get_maxConnections();
    int get_rpcTimeout();
    QString get_coinName();
    void loadExistingFromConf();

private slots:
    void on_pushButton_browse_clicked();

    void on_radioButton_linux_toggled(bool checked);

    void on_radioButton_mac_toggled(bool checked);

    void on_radioButton_windows_toggled(bool checked);

    void on_checkBox_server_toggled(bool checked);

    void on_checkBox_generate_toggled(bool checked);

    void on_radioButton_addNodes_toggled(bool checked);

    void on_radioButton_connectOnly_toggled(bool checked);

    void on_checkBox_testnet_toggled(bool checked);

    void on_checkBox_startMini_toggled(bool checked);

    void on_checkBox_startTrayed_toggled(bool checked);

    void on_checkBox_receiveByIP_toggled(bool checked);

    void on_comboBox_selectCoin_currentIndexChanged(int index);

    void on_pushButton_cancel_clicked();

    void on_pushButton_Save_clicked();

    void on_pushButton_addNode_clicked();

    void on_pushButton_clearNodeList_clicked();

    // Clear out the ui and all text
    void resetUI();

signals:
    void confWidgetClosing();

private:
    Ui::ConfCreationWidget *ui;
    int selectCoinIndex;
    QString confDirectory;
    QString rpcConnectForward;
    bool serverEnabled;
    QString allowedIP;
    QString proxy;
    int RPCPort;
    QString RPCUser;
    QString RPCPassword;
    bool generateEnabled;
    bool addNodesEnabled;
    bool connectOnlyEnabled;
    bool testnetEnabled;
    bool startMinEnabled;
    bool startTrayedEnabled;
    bool receiveByIPEnabled;
    int maxConnections;
    int rpcTimeout;
    QString coinName;

    // String representing operating system detected
    QString osString;
};

#endif // CONFCREATIONWIDGET_H
