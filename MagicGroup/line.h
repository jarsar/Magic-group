#ifndef LINE_H
#define LINE_H

#include<mygraph.h>
class Line
{
private:
    GLint x0,y0,x1,y1;
public:
    Line();
    ~Line(){}
    void setline(GLint x0,GLint y0,GLint x1,GLint y1);
    void LineDDA(QPainter *painter);
};
#endif // LINE_H