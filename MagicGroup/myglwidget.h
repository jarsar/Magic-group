#ifndef GLWIDGET_H
#define GLWIDGET_H

#include<QOpenGLWidget>
#include<QOpenGLFunctions>
#include<QPainter>
#include<QPen>
#include<line.h>
#include<QMouseEvent>
#include<qvector.h>
#include<iostream>
#include<mygraph.h>
#include<round.h>
class Line;
class Round;
class MyGLWidget : public QOpenGLWidget,
        protected QOpenGLFunctions
{
     Q_OBJECT
private:
    GLint x0,y0,x1,y1;
    bool check_flag;
    int *buttonjudge;
    QPainter painter;
    Line *line;
    QVector<Line *>lines;
    Round *round;
    QVector<Round *>rounds;
public:
    MyGLWidget(QWidget * parent = 0);
    ~MyGLWidget();
    void get_buttonjudge(int *buttonjudge);
protected:
    void initializeGL();
    void paintGL();
    void resizeGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    void draw();
    void redraw();
    void create_graph();
    void get_graphinformation();
    void save_graph();
};

#endif // GLWIDGET_H
