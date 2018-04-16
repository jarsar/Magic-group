#ifndef GRAPH_H
#define GRAPH_H
#include<QPainter>
#include<QPen>
#include<qopengl.h>
#include<qmath.h>
#include<QVector>
#include<QColor>
#include<QPointF>
enum Kind{
    kline,kround,kellipse,kcurve,kpolygon,k3D
};
class MyGraph{
protected:
    Kind kind;
    QPen *pen;
    bool is_fill;
    bool is_rotate;
public:
     MyGraph();
     void set_color(QColor color);
     virtual void setline(GLint x0,GLint y0,GLint x1,GLint y1){};
     virtual void setround(QPoint p,GLint r){};
     virtual void setellipse(QPoint point,GLint a,GLint b){};
     virtual void setpolygon(QPoint point){};
     virtual void draw(QPainter*painter){};
     virtual void redraw(QPainter *painter){};
     virtual void fillgraph(QPainter *painter){};
     bool get_fill();
     Kind get_Kind();
     bool get_is_rotate();
};

#endif // GRAPH_H

