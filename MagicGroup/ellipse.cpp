#include "ellipse.h"

Ellipse::Ellipse(){
    this->kind=kellipse;
    this->is_rotate=false;
}

void Ellipse::setellipse(QPoint point, GLint a, GLint b){
    this->point=point;
    this->a=a;
    this->b=b;
}

void Ellipse::drawellipse(QPainter *painter){
    painter->setPen(*this->pen);
    points.clear();
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
    QPoint *p1,*p2,*p3,*p4;
    x1=this->point.x()+x;
    y1=this->point.y()+y;
    p1=new QPoint(x1,y1);

    x2=this->point.x()+x;
    y2=this->point.y()-y;
    p2=new QPoint(x2,y2);

    x3=this->point.x()-x;
    y3=this->point.y()+y;
    p3=new QPoint(x3,y3);

    x4=this->point.x()-x;
    y4=this->point.y()-y;
    p4=new QPoint(x4,y4);

    p->drawPoint(x1,y1);
    p->drawPoint(x2,y2);
    p->drawPoint(x3,y3);
    p->drawPoint(x4,y4);

    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);

}

void Ellipse::draw(QPainter *painter){
    this->drawellipse(painter);
}

void Ellipse::redraw(QPainter *painter)
{
    painter->setPen(*this->pen);
    for(int i=0;i<points.size();i++){
        painter->drawPoint(points[i]->rx(),points[i]->ry());
    }
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

void Ellipse::translation_ellipse(GLint x, GLint y)
{
    this->point.rx()+=x;
    this->point.ry()+=y;
}

void Ellipse::rotate_ellipse(double x, double y, double angel)
{
    double radian=(3.14159/180)*angel;
    this->is_rotate=true;
    double old_x,old_y;
    for(int i=0;i<points.size();i++){
        old_x=points[i]->rx();
        old_y=points[i]->ry();
        points[i]->rx()=x+qCos(radian)*(old_x-x)-qSin(radian)*(old_y-y);
        points[i]->ry()=y+qSin(radian)*(old_x-x)+qCos(radian)*(old_y-y);
    }
}

void Ellipse::zoom_ellipse(double x, double y, double factor_x, double factor_y)
{
    double multiple,old_x,old_y;
    old_x=point.rx();
    old_y=point.ry();
    point.rx()=factor_x*point.rx()+(1-factor_x)*x;
    point.ry()=factor_y*point.ry()+(1-factor_y)*y;
    multiple=qSqrt((x-point.rx())*(x-point.rx())+(y-point.ry())*(y-point.ry()))/qSqrt((x-old_x)*(x-old_x)+(y-old_y)*(y-old_y));
    a=a*multiple;
    b=b*multiple;
}

void Ellipse::draw_twopoints(int x1, int x2, int y1, QPainter *painter){
    int y2=2*this->point.y()-y1;
    for(int j=x1;j<=x2;j++){
        painter->drawPoint(j,y1);
        painter->drawPoint(j,y2);
    }
}
