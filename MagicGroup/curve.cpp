#include "curve.h"

Curve::Curve()
{
    this->kind=kcurve;
}

void Curve::setcurve(GLint x, GLint y)
{
    QPointF p(x,y);
    ctrlPoints.push_back(p);
}

void Curve::draw(QPainter *painter)
{
    this->set_curvepoints();
    QPen ctrlPen1(QColor(0,0,255));
    ctrlPen1.setWidth(7);
    painter->setPen(ctrlPen1);
    for(int i=0; i< ctrlPoints.size(); i++)
    {
        painter->drawPoint(ctrlPoints[i]);
    }

    // draw Control Lines;
    QPen ctrlPen2(QColor(255,0,0));
    ctrlPen2.setWidth(1);
    ctrlPen2.setStyle(Qt::DashDotDotLine);
    painter->setPen(ctrlPen2);
    for(int i=0; i<ctrlPoints.size()-1;i++)
    {
        painter->drawLine(ctrlPoints[i],ctrlPoints[i+1]);
    }

    // draw Spline Curve
    painter->setPen(*this->pen);

    for(int i=0; i<curvePoints.size()-1; i++)
    {
        painter->drawLine(curvePoints[i],curvePoints[i+1]);
    }
}

void Curve::set_curvepoints()
{
    curvePoints.clear();
    for(double u=3.0; u<ctrlPoints.size(); u+=0.01)
    {
        QPointF tmp(0,0);
        for(int i=0; i<ctrlPoints.size();i++)
        {
            QPointF t = ctrlPoints[i];

            t*=N(i,u);

            tmp+=t;
        }
        curvePoints.push_back(tmp);
    }
}

double Curve::N(int i, double u)
{
    double t = u-i;

    if(0<=t && t<1)
        return 0.5*t*t;
    if(1<=t && t<2)
        return 3*t-t*t-1.5;
    if(2<=t && t<3)
        return 0.5*pow(3-t,2);
    return 0;
}
