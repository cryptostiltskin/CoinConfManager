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
