#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "confcreationwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    confWidget = new ConfCreationWidget(this);
    ui->verticalLayout_2->addWidget(confWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
