#ifndef CURVE_H
#define CURVE_H
#include<mygraph.h>

class Curve:public MyGraph
{
private:
    QVector<QPointF> ctrlPoints;
    QVector<QPointF> curvePoints;
private:
    void set_curvepoints();
    double N(int i, double u);
public:
    Curve();
    void setcurve(GLint x,GLint y);
    void draw(QPainter *painter);
};

#endif // CURVE_H
