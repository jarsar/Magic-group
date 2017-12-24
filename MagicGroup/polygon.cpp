#include "polygon.h"

Polygon::Polygon()
{

}

void Polygon::setpolygon(QPoint point){
    QPoint *p=new QPoint(point.x(),point.y());
    this->points.push_back(p);
}

void Polygon::drawpolygon(QPainter *painter){

}
