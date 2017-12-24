#ifndef GRAPH_H
#define GRAPH_H
#include<QPainter>
#include<QPen>
#include<qopengl.h>
#include<qmath.h>
#include<QVector>
#include<QColor>
enum Kind{
    line,round,ellipse,curve,polygon,_3D
};
class MyGraph{
protected:
    Kind kind;
    QPen *pen;
public:
     MyGraph();
     void set_color(QColor color);
     virtual void set_points(){};
     virtual void draw(){};
};

#endif // GRAPH_H

