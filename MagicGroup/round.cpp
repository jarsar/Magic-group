#include "round.h"

Round::Round()
{

}

Round::~Round(){

}

void Round::setround(QPoint p, GLint r){
    this->center.setX(p.x());
    this->center.setY(p.y());
    this->r=r;
}

void Round::drawround(QPainter *painter){
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
