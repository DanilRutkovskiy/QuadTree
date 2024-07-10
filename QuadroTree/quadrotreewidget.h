#ifndef QUADROTREEWIDGET_H
#define QUADROTREEWIDGET_H

#include <memory>
#include <QWidget>
#include "quadrotree.h"

namespace Ui {
class QuadroTreeWidget;
}

class QuadroTreeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QuadroTreeWidget(QWidget *parent = nullptr);
    ~QuadroTreeWidget();

private:
    void initConnects();
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    Ui::QuadroTreeWidget *ui;
    std::unique_ptr<QuadroTreeNode> m_head;
};

#endif // QUADROTREEWIDGET_H
