#include<line.h>

Line::Line(){
    this->kind=kline;
}

void Line::LineDDA(QPainter *painter){
    painter->setPen(*this->pen);
    GLfloat m,dx,dy,x,y,flag;
        dx=x1-x0;
        dy=y1-y0;
        if(dx!=0){
            m=dy/dx;
            if(m<=1&&m>=-1){
                flag=dx/fabsf(dx);
                y=y0;
                for(x=x0;(flag*x)<=(flag*x1);x+=flag){
                    GLint temp=y+0.5;
                    painter->drawPoint(x,temp);
                    y+=(flag*m);
                }
            }
            if(m>1||m<-1){
                flag=dy/fabsf(dy);
                x=x0;
                for(y=y0;(flag*y)<=(flag*y1);y+=flag){
                    GLint temp=x+0.5;
                    painter->drawPoint(temp,y);
                    x+=(flag*(1/m));
                }
            }
        }
        else{
            GLint x=x0;
            flag=dy/fabsf(dy);
            for(GLint y=y0;(flag*y)<=(flag*y1);y+=flag){
                painter->drawPoint(x,y);
            }
        }
}

void Line::setline(GLint x0, GLint y0, GLint x1, GLint y1){
    this->x0=x0;
    this->y0=y0;
    this->x1=x1;
    this->y1=y1;
}

void Line::draw(QPainter *painter){
    this->LineDDA(painter);
}

void Line::translation_line(GLint x,GLint y)
{
    this->x0+=x;
    this->y0+=y;
    this->x1+=x;
    this->y1+=y;
}

void Line::rotate_line(double x, double y, double angel)
{
    double radian=(3.14159/180)*angel;
    double old_x,old_y;
    old_x=x0;
    old_y=y0;
    x0=x+qCos(radian)*(old_x-x)-qSin(radian)*(old_y-y);
    y0=y+qSin(radian)*(old_x-x)+qCos(radian)*(old_y-y);
    old_x=x1;
    old_y=y1;
    x1=x+qCos(radian)*(old_x-x)-qSin(radian)*(old_y-y);
    y1=y+qSin(radian)*(old_x-x)+qCos(radian)*(old_y-y);
}

void Line::zoom_line(double x, double y, double factor_x, double factor_y)
{
    this->x0=factor_x*this->x0+(1-factor_x)*x;
    this->y0=factor_y*this->y0+(1-factor_y)*y;
    this->x1=factor_x*this->x1+(1-factor_x)*x;
    this->y1=factor_y*this->y1+(1-factor_y)*y;
}

