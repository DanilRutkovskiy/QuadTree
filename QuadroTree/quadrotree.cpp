#include "quadrotree.h"

QuadroTreeNode::QuadroTreeNode(const QRectF& area): m_area{area},
    m_nw{nullptr}, m_ne{nullptr}, m_sw{nullptr}, m_se{nullptr},
    m_maxPoints{5}
{
    m_mid.setX((m_area.left() + m_area.right()) / 2);
    m_mid.setY((m_area.top() + m_area.bottom()) / 2);
}

void QuadroTreeNode::addPoint(QPointF newPoint)
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
                if(point.x() < m_mid.x()){ m_nw->addPoint(point);}
                else{m_ne->addPoint(point);}
            }
            else{
                if(point.x() < m_mid.x()){m_sw->addPoint(point);}
                else{m_se->addPoint(point);}
            }
        }

        m_points.clear();
    }

    if(m_nw == nullptr){
        m_points.push_back(newPoint);
    }
    else{
        if(newPoint.y() < m_mid.y()){
            if(newPoint.x() < m_mid.x()){ m_nw->addPoint(newPoint);}
            else{m_ne->addPoint(newPoint);}
        }
        else{
            if(newPoint.x() < m_mid.x()){m_sw->addPoint(newPoint);}
            else{m_se->addPoint(newPoint);}
        }
    }
}

void QuadroTreeNode::deletePoint(const QPointF& point, QuadroTreeNode* parent)
{
    if(m_ne != nullptr){
        if(point.x() < m_mid.x()){
            if(point.y() < m_mid.y()) { m_nw->deletePoint(point, this); }
            else {m_sw->deletePoint(point, this);};
        }
        else{
            if(point.y() < m_mid.y()) { m_ne->deletePoint(point, this); }
            else {m_se->deletePoint(point, this);};
        }
    }
    else{
        for(auto it = m_points.begin(); it != m_points.end(); it++){
            if((it->x() >= point.x() - 2) && (it->x() <= point.x() + 2)
                && (it->y() >= point.y() - 2) && (it->y() <= point.y() +2))
            {
                m_points.erase(it);
                if(parent != nullptr){
                    parent->reconstruct();
                }
                break;
            }
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
    if(m_ne == nullptr){
        painter.drawRect(m_area);
    }

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

void QuadroTreeNode::reconstruct()
{
    if(m_ne != nullptr){
        int totalPoints = 0;
        totalPoints += m_nw->m_points.size();
        totalPoints += m_ne->m_points.size();
        totalPoints += m_sw->m_points.size();
        totalPoints += m_se->m_points.size();

        if(totalPoints <= m_maxPoints){
            m_points.reserve(totalPoints);
            m_points.insert(m_points.end(), m_nw->m_points.begin(), m_nw->m_points.end());
            m_points.insert(m_points.end(), m_ne->m_points.begin(), m_ne->m_points.end());
            m_points.insert(m_points.end(), m_sw->m_points.begin(), m_sw->m_points.end());
            m_points.insert(m_points.end(), m_se->m_points.begin(), m_se->m_points.end());

            m_nw.reset(nullptr);
            m_ne.reset(nullptr);
            m_se.reset(nullptr);
            m_sw.reset(nullptr);
        }
    }
}

