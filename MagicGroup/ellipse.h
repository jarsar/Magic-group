#ifndef ELLIPSE_H
#define ELLIPSE_H
#include<mygraph.h>
class Ellipse:public MyGraph
{
private:
    QPoint point;
    GLint a;
    GLint b;
    QVector<QPoint *>points;
private:
    void draw_fourpoints(QPainter *p,int x,int y);
    void drawellipse(QPainter *painter);
    void draw_twopoints(int x1,int x2,int y1,QPainter *painter);
public:
    Ellipse();
    void setellipse(QPoint point,GLint a,GLint b);
    void draw(QPainter *painter);
    void redraw(QPainter *painter);
    void fillgraph(QPainter *painter);
    void translation_ellipse(GLint x,GLint y);
    void rotate_ellipse(double x,double y,double angel);
    void zoom_ellipse(double x,double y,double factor_x,double factor_y);
};
#endif // ELLIPSE_H
