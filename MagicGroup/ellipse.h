#ifndef ELLIPSE_H
#define ELLIPSE_H
#include<mygraph.h>

class Ellipse
{
private:
    QPoint point;
    GLint a;
    GLint b;
private:
    void draw_fourpoints(QPainter *p,int x,int y);
public:
    Ellipse();
    ~Ellipse(){};
    void setellipse(QPoint point,GLint a,GLint b);
    void drawellipse(QPainter *painter);
};
#endif // ELLIPSE_H
