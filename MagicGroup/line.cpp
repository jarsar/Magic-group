#include<line.h>

Line::Line(){

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

void Line::set_points(){
    this->setline();
}

void Line::draw(){
    this->LineDDA();
}
