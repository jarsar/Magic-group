#ifndef POLYGON_H
#define POLYGON_H

#include<mygraph.h>
#include<QLine>
typedef struct XET
{
    float x;
    float dx,ymax;
    XET* next;
} AET,NET;
class Polygon:public MyGraph
{
private:
    QVector<QPoint *>points;
    int pymax;
    int pymin;
//    QVector<QLine *>lines;
private:
    void drawpolygon(QPainter *painter);
    void DDA(QPainter *painter,GLint x0,GLint y0,GLint x1,GLint y1);
    void get_y_max_min();
public:
    Polygon();
    void setpolygon(QPoint point);
    void draw(QPainter *painter);
    void redraw(QPainter *painter);
    void fillgraph(QPainter *painter);
    void traslation_polygon(GLint x,GLint y);
    void rotate_polygon(double x,double y,double angel);
    void zoom_polyogn(double x,double y,double factor_x,double factor_y);
};

#endif // POLYGON_H
