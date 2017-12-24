#ifndef POLYGON_H
#define POLYGON_H

#include<mygraph.h>
class Polygon
{
private:
    QVector<QPoint *>points;
public:
    Polygon();
    void setpolygon(QPoint point);
    void drawpolygon(QPainter *painter);
};

#endif // POLYGON_H
