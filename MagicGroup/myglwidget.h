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
#include<polygon.h>
#include<QSpinBox>
#include<QLabel>
#include<qstackedwidget.h>
class MyGraph;
class Line;
class Round;
class Ellipse;
//class Polygon;
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
    //所有图
    MyGraph *graph;
    QVector<MyGraph *> graphs;
    //点颜色
    QSpinBox *red,*green,*blue;
    QLabel *labelshowcolor;
    //绘制窗口属性
    QStackedWidget *mystack;
    //直线
    Line *line;
    QSpinBox *lx0,*ly0,*lx1,*ly1;
    //圆
    Round *round;
    QSpinBox *rR,*rx,*ry;
    //椭圆
    Ellipse *ellipse;
    QSpinBox *ex,*ey,*ea,*eb;
    //多边形
    Polygon *polygon;
    QSpinBox *px,*py;
public:
    MyGLWidget(QWidget * parent = 0);
    ~MyGLWidget();
    void get_buttonjudge(int *buttonjudge);
    int *get_graphflag();
    Round *get_roundlist();
    Ellipse *get_ellispelist();
    void get_information(QSpinBox *red,QSpinBox *green,QSpinBox *blue,QLabel *labelshowcolor,QStackedWidget *mystack);
    //设置直线属性
    void set_line(QSpinBox *lx0,QSpinBox *ly0,QSpinBox *lx1,QSpinBox *ly1);
    //设置圆属性
    void set_round(QSpinBox *rR,QSpinBox *rx,QSpinBox *ry);
    //设置椭圆属性
    void set_ellipse(QSpinBox *ex,QSpinBox *ey,QSpinBox *ea,QSpinBox *eb);
    //设置多边形属性
    void set_polygon(QSpinBox *px,QSpinBox *py);
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
private slots:
    void setcolor();
    void draw_line();
    void draw_round();
    void draw_ellipse();
    void create_polygon();
    void draw_polygon();
    void draw_polygon_finally();
    void fill_color();
};

#endif // GLWIDGET_H
