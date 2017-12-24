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
#include<ellipse.h>
#include<QSpinBox>
#include<QLabel>
#include<qstackedwidget.h>
class MyGraph;
class Line;
class Round;
class Ellipse;
class MyGLWidget : public QOpenGLWidget,
        protected QOpenGLFunctions
{
     Q_OBJECT
private:
    GLint x0,y0,x1,y1;
    bool check_flag;
    int *buttonjudge;
    int graphflag;
    QPainter painter;
    MyGraph *graph;
    QColor color;
    //点颜色
    QSpinBox *red,*green,*blue;
    QLabel *labelshowcolor;
    //绘制窗口属性
    QStackedWidget *mystack;
    //直线
    Line *line;
    QVector<Line *>lines;
    //圆
    Round *round;
    QVector<Round *>rounds;
    //椭圆
    Ellipse *ellipse;
    QVector<Ellipse*>ellipses;

public:
    MyGLWidget(QWidget * parent = 0);
    ~MyGLWidget();
    void get_buttonjudge(int *buttonjudge);
    int *get_graphflag();
    Round *get_roundlist();
    Ellipse *get_ellispelist();
    void get_information(QSpinBox *red,QSpinBox *green,QSpinBox *blue,QLabel *labelshowcolor,QStackedWidget *mystack);

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
private slots:
    void setcolor();
};

#endif // GLWIDGET_H
