#include "polygon.h"

Polygon::Polygon(){
    this->kind=kpolygon;
}

void Polygon::setpolygon(QPoint point){
    QPoint *p=new QPoint(point.x(),point.y());
    this->points.push_back(p);
}

void Polygon::drawpolygon(QPainter *painter){
     GLint x0,y0,x1,y1;
    for(int i=0;i<this->points.size()-1;i++){
        x0=this->points[i]->x();
        y0=this->points[i]->y();
        x1=this->points[i+1]->x();
        y1=this->points[i+1]->y();
        this->DDA(painter,x0,y0,x1,y1);
    }
}

void Polygon::draw(QPainter *painter){
    painter->setPen(*this->pen);
    this->drawpolygon(painter);
}

void Polygon::DDA(QPainter *painter,GLint x0,GLint y0,GLint x1,GLint y1){
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

void Polygon::redraw(QPainter *painter){
    painter->setPen(*this->pen);
    GLint x0,y0,x1,y1;
    if(points.size()>1){
        x0=points[0]->x();
        y0=points[0]->y();
        x1=points[points.size()-1]->x();
        y1=points[points.size()-1]->y();
        this->DDA(painter,x0,y0,x1,y1);
    }
}
