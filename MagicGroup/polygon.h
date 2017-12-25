#ifndef POLYGON_H
#define POLYGON_H

#include<mygraph.h>
class Polygon:public MyGraph
{
private:
    QVector<QPoint *>points;
private:
    void drawpolygon(QPainter *painter);
    void DDA(QPainter *painter,GLint x0,GLint y0,GLint x1,GLint y1);
public:
    Polygon();
    void setpolygon(QPoint point);
    void draw(QPainter *painter);
    void redraw(QPainter *painter);
};

#endif // POLYGON_H
