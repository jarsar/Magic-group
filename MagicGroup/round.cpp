#include "round.h"

Round::Round(){
    this->kind=kround;
}

void Round::setround(QPoint p, GLint r){
    this->center.setX(p.x());
    this->center.setY(p.y());
    this->r=r;
}

void Round::drawround(QPainter *painter){
    painter->setPen(*this->pen);
    QPoint point;
    double d;
    point.setX(0);
    point.setY(this->r);
    d=1.25-r;
    this->draw_eightpoint(painter,point);
    while(point.x()<point.y()){
        if(d<0){
            d=d+2*point.x()+3;
        }
        else{
            d=d+2*(point.x()-point.y())+5;
            point.setY(point.y()-1);
        }
        point.setX(point.x()+1);
        this->draw_eightpoint(painter,point);
    }

}

void Round::draw_eightpoint(QPainter *p,QPoint point){
    QPoint *points=new QPoint[8];
    int angel=0;
    for(int i=0;i<8;i++){
        switch (i) {
        case 0:{
            points[i].setX(this->center.x()+point.x());
            points[i].setY(this->center.y()+point.y());
        }
            break;
        case 1:{
            points[i].setX(this->center.x()+point.x());
            points[i].setY(this->center.y()-point.y());
        }
            break;
        case 2:{
            points[i].setX(this->center.x()-point.x());
            points[i].setY(this->center.y()-point.y());
        }
            break;
        case 3:{
            points[i].setX(this->center.x()-point.x());
            points[i].setY(this->center.y()+point.y());
        }
            break;
        case 4:{
            points[i].setX(this->center.x()+point.y());
            points[i].setY(this->center.y()+point.x());
        }
            break;
        case 5:{
            points[i].setX(this->center.x()+point.y());
            points[i].setY(this->center.y()-point.x());
        }
            break;
        case 6:{
            points[i].setX(this->center.x()-point.y());
            points[i].setY(this->center.y()-point.x());
        }
            break;
        case 7:{
            points[i].setX(this->center.x()-point.y());
            points[i].setY(this->center.y()+point.x());
        }
            break;
        default:
            break;
        }
        p->drawPoint(points[i]);
        }
}

void Round::draw(QPainter *painter){
    this->drawround(painter);
}

void Round::fillgraph(QPainter *painter){
    this->is_fill=true;
    painter->setPen(*this->pen);
    for(int i=this->r;i>=0;i--){
        int x1,y1,x2,y2;
        x1=this->center.x()-qSqrt(r*r-i*i);
        x2=this->center.x()+qSqrt(r*r-i*i);
        y1=this->center.y()-i;
        this->link_twopoints(x1,x2,y1,painter);
    }
}

void Round::translation_round(GLint x, GLint y)
{
    this->center.rx()+=x;
    this->center.ry()+=y;
}

void Round::rotate_round(double x, double y, double angel)
{
    double radian=(3.14159/180)*angel;
    double old_x,old_y;
    old_x=center.rx();
    old_y=center.ry();
    center.rx()=x+qCos(radian)*(old_x-x)-qSin(radian)*(old_y-y);
    center.ry()=y+qSin(radian)*(old_x-x)+qCos(radian)*(old_y-y);
}

void Round::zoom_round(double x, double y, double factor_x, double factor_y)
{
    double multiple,old_x,old_y;
    old_x=center.rx();
    old_y=center.ry();
    center.rx()=factor_x*center.rx()+(1-factor_x)*x;
    center.ry()=factor_y*center.ry()+(1-factor_y)*y;
    multiple=qSqrt((x-center.rx())*(x-center.rx())+(y-center.ry())*(y-center.ry()))/qSqrt((old_x-x)*(old_x-x)+(old_y-y)*(old_y-y));
    r=multiple*r;
}

void Round::link_twopoints(int x1,int x2,int y1,QPainter *painter){
    int y2=2*this->center.y()-y1;
    for(int j=x1;j<=x2;j++){
    painter->drawPoint(j,y1);
    painter->drawPoint(j,y2);
    }
}
