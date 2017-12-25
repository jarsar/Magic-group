#ifndef ELLIPSE_H
#define ELLIPSE_H
#include<mygraph.h>

class Ellipse:public MyGraph
{
private:
    QPoint point;
    GLint a;
    GLint b;
private:
    void draw_fourpoints(QPainter *p,int x,int y);
    void drawellipse(QPainter *painter);
public:
    Ellipse();
    void setellipse(QPoint point,GLint a,GLint b);
    void draw(QPainter *painter);
};
#endif // ELLIPSE_H
