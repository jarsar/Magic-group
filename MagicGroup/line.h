#ifndef LINE_H
#define LINE_H

#include<mygraph.h>
class Line:public MyGraph{
private:
    GLint x0,y0,x1,y1;
private:
    void LineDDA(QPainter *painter);
public:
    Line();
    void setline(GLint x0,GLint y0,GLint x1,GLint y1);
    void draw(QPainter *painter);
    void translation_line(GLint x,GLint y);
    void rotate_line(double x,double y,double angel);
    void zoom_line(double x,double y,double factor_x,double factor_y);
};
#endif // LINE_H
