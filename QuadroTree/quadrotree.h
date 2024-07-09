#ifndef QUADROTREE_H
#define QUADROTREE_H

#include <QRect>
#include <QPoint>
#include <QPainter>
#include <memory>
#include <vector>

class QuadroTreeNode{
public:
    QuadroTreeNode(const QRectF& rect);

public:
    void addItem(QPointF newPoint);
    void getPoints(std::vector<QPointF>& vec) const;
    void draw(QPainter& painter) const;

private:

private:
    int m_maxPoints;
    QRectF m_area;
    QPointF m_mid;
    std::unique_ptr<QuadroTreeNode> m_nw, m_ne, m_sw, m_se;
    std::vector<QPointF> m_points;

};
#endif // QUADROTREE_H
