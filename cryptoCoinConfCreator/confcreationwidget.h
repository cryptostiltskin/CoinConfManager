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
    
private:
    Ui::ConfCreationWidget *ui;
};

#endif // CONFCREATIONWIDGET_H
