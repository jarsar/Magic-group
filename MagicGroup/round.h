#ifndef ROUND_H
#define ROUND_H

#include<mygraph.h>
class Round:public MyGraph
{
private:
    QPoint center;
    GLint r;
private:
    void draw_eightpoint(QPainter *p,QPoint point);
    void drawround(QPainter *painter);
public:
    Round();
    void setround(QPoint p,GLint r);
    void draw(QPainter *painter);
};

#endif // ROUND_H
