#include "quadrotreewidget.h"
#include "ui_quadrotreewidget.h"

#include <QMouseEvent>

QuadroTreeWidget::QuadroTreeWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QuadroTreeWidget)
    , m_head{nullptr}
{
    ui->setupUi(this);


    initConnects();
}

QuadroTreeWidget::~QuadroTreeWidget()
{
    delete ui;
}

void QuadroTreeWidget::initConnects()
{

}

void QuadroTreeWidget::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);

    if(event->button() == Qt::LeftButton){
        m_head->addPoint(event->position());
    }
    else if(event->button() == Qt::RightButton){
        m_head->deletePoint(event->position());
    }

    this->update();
}

void QuadroTreeWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    std::vector<QPointF> points;
    m_head->getPoints(points);

    QPainter painter(this);
    m_head->draw(painter);
}

void QuadroTreeWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    if(m_head == nullptr){
        QRect rect = this->rect();
        rect.adjust(0,0,-1,-1);
        m_head = std::make_unique<QuadroTreeNode>(rect);
    }
}

void QuadroTreeWidget::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
}
