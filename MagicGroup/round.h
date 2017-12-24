#ifndef ROUND_H
#define ROUND_H

#include<mygraph.h>
class Round
{
private:
    QPoint center;
    GLint r;
private:
    void draw_eightpoint(QPainter *p,QPoint point);
public:
    Round();
    ~Round();
    void setround(QPoint p,GLint r);
    void drawround(QPainter *painter);
};

#endif // ROUND_H
