#include "quadrotree.h"

QuadroTreeNode::QuadroTreeNode(const QRectF& area): m_area{area},
    m_nw{nullptr}, m_ne{nullptr}, m_sw{nullptr}, m_se{nullptr},
    m_maxPoints{5}
{
    m_mid.setX((m_area.left() + m_area.right()) / 2);
    m_mid.setY((m_area.top() + m_area.bottom()) / 2);
}

void QuadroTreeNode::addItem(QPointF newPoint)
{
    if(m_points.size() == m_maxPoints){
        double width = m_area.width() / 2;
        double height = m_area.height() / 2;
        QRectF tempRect{m_area.topLeft().x(), m_area.topLeft().y(), width, height};
        m_nw = std::make_unique<QuadroTreeNode>(tempRect);
        tempRect.setRect(tempRect.right(), tempRect.top(), width, height);
        m_ne = std::make_unique<QuadroTreeNode>(tempRect);
        tempRect.setRect(m_area.left(), tempRect.bottom(), width, height);
        m_sw = std::make_unique<QuadroTreeNode>(tempRect);
        tempRect.setRect(tempRect.right(), tempRect.top(), width, height);
        m_se = std::make_unique<QuadroTreeNode>(tempRect);

        for(auto& point : m_points){
            if(point.y() < m_mid.y()){
                if(point.x() < m_mid.x()){ m_nw->addItem(point);}
                else{m_ne->addItem(point);}
            }
            else{
                if(point.x() < m_mid.x()){m_sw->addItem(point);}
                else{m_se->addItem(point);}
            }
        }

        m_points.clear();
    }

    if(m_nw == nullptr){
        m_points.push_back(newPoint);
    }
    else{
        if(newPoint.y() < m_mid.y()){
            if(newPoint.x() < m_mid.x()){ m_nw->addItem(newPoint);}
            else{m_ne->addItem(newPoint);}
        }
        else{
            if(newPoint.x() < m_mid.x()){m_sw->addItem(newPoint);}
            else{m_se->addItem(newPoint);}
        }
    }
}

void QuadroTreeNode::getPoints(std::vector<QPointF> &vec) const
{
    if(!m_points.empty()){
        for(auto& point : m_points){
            vec.push_back(point);
        }
    }
    else if(m_nw != nullptr){
        m_nw->getPoints(vec);
        m_ne->getPoints(vec);
        m_sw->getPoints(vec);
        m_se->getPoints(vec);
    }
}

void QuadroTreeNode::draw(QPainter &painter) const
{
    painter.drawRect(m_area);

    for(const auto& point : m_points){
        painter.drawEllipse(point, 2, 2);
    }

    if(m_ne != nullptr){
        m_ne->draw(painter);
        m_nw->draw(painter);
        m_se->draw(painter);
        m_sw->draw(painter);
    }
}
