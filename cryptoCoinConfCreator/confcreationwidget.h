// ~CryptAxe

#ifndef CONFCREATIONWIDGET_H
#define CONFCREATIONWIDGET_H

#include <QWidget>

namespace Ui {
class ConfCreationWidget;
}

class ConfCreationWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ConfCreationWidget(QWidget *parent = 0);
    ~ConfCreationWidget();
    
private slots:
    void on_pushButton_browse_clicked();

    void on_radioButton_linux_toggled(bool checked);

private:
    Ui::ConfCreationWidget *ui;
};

#endif // CONFCREATIONWIDGET_H
