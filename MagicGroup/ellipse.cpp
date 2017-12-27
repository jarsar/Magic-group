#include "ellipse.h"

Ellipse::Ellipse(){
    this->kind=kellipse;
}

void Ellipse::setellipse(QPoint point, GLint a, GLint b){
    this->point=point;
    this->a=a;
    this->b=b;
}

void Ellipse::drawellipse(QPainter *painter){
    painter->setPen(*this->pen);
    double sqa=a*a;
    double sqb=b*b;
    double d=sqb+sqa*(-b+0.25);
    int x=0;
    int y=b;
    draw_fourpoints(painter,x,y);
    while(sqb*(x+1)<sqa*(y-0.5)){
        if(d<0){
            d+=sqb*(2*x+3);
        }else{
            d+=(sqb*(2*x+3)+sqa*(-2*y+2));
            y--;
        }
        x++;
        draw_fourpoints(painter,x,y);
    }
    d=(b*(x+0.5))*2+(a*(y-1))*2-(a*b)*2;
    while(y>0){
        if(d<0){
            d+=sqb*(2*x+2)+sqa*(-2*y+3);
            x++;
        }else{
            d+=sqa*(-2*y+3);
        }
        y--;
        draw_fourpoints(painter,x,y);
    }
}

void Ellipse::draw_fourpoints(QPainter *p,int x,int y){
    int x1,x2,x3,x4,y1,y2,y3,y4;
    x1=this->point.x()+x;
    y1=this->point.y()+y;

    x2=this->point.x()+x;
    y2=this->point.y()-y;

    x3=this->point.x()-x;
    y3=this->point.y()+y;

    x4=this->point.x()-x;
    y4=this->point.y()-y;

    p->drawPoint(x1,y1);
    p->drawPoint(x2,y2);
    p->drawPoint(x3,y3);
    p->drawPoint(x4,y4);
}

void Ellipse::draw(QPainter *painter){
    this->drawellipse(painter);
}

void Ellipse::fillgraph(QPainter *painter){
    painter->setPen(*this->pen);
    this->is_fill=true;
    int x1,x2,y1,k;
    for(double i=b;i>=0;i--){
        k=(1.0-(i*i)/(b*b))*(a*a);
        x1=-qSqrt(k);
        x2=-x1;
        x1+=this->point.x();
        x2+=this->point.x();
        y1=i+this->point.y();
        this->draw_twopoints(x1,x2,y1,painter);
    }
}

void Ellipse::draw_twopoints(int x1, int x2, int y1, QPainter *painter){
    int y2=2*this->point.y()-y1;
    for(int j=x1;j<=x2;j++){
        painter->drawPoint(j,y1);
        painter->drawPoint(j,y2);
    }
}
