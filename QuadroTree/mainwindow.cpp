#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_drawWgt = new QuadroTreeWidget(this);
    ui->drawLayout->addWidget(m_drawWgt);
    m_drawWgt->show();
}

MainWindow::~MainWindow()
{
    delete ui;

    if(m_drawWgt != nullptr){
        delete m_drawWgt;
    }
}
