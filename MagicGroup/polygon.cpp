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
//        QLine line=new QLine(x0,y0,x1,y1);
//        this->lines.push_back(line);
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
        x1=points[0]->x();
        y1=points[0]->y();
        x0=points[points.size()-1]->x();
        y0=points[points.size()-1]->y();
//        QLine line=new QLine(x0,y0,x1,y1);
//        this->lines.push_back(line);
        this->DDA(painter,x0,y0,x1,y1);
    }
}

void Polygon::get_y_max_min(){
    this->pymax=this->points[0]->y();
    this->pymin=this->points[0]->y();
    for(int i=0;i<this->points.size();i++){
        if(this->pymax<this->points[i]->y()){
            this->pymax=this->points[i]->y();
        }
        if(this->pymin>this->points[i]->y()){
            this->pymin=this->points[i]->y();
        }
    }
}

void Polygon::fillgraph(QPainter *painter){
    this->is_fill=true;
    painter->setPen(*this->pen);
    this->get_y_max_min();
    int i;
    AET *pAET=new AET;
    pAET->next=NULL;

    NET *pNET[1024];
    for(i=0; i<=this->pymax; i++)
    {
        pNET[i]=new NET;
        pNET[i]->next=NULL;
    }

    for(i=0; i<=this->pymax; i++)
    {
        for(int j=0; j<this->points.size(); j++)
            if(this->points[j]->y()==i)
            {
                //一个点跟前面的一个点形成一条线段，跟后面的点也形成线段
                if(this->points[(j-1+points.size())%points.size()]->y()>points[j]->y())
                {
                    NET *p=new NET;
                    p->x=points[j]->x();
                    p->ymax=points[(j-1+points.size())%points.size()]->y();
                    p->dx=1.0*(points[(j-1+points.size())%points.size()]->x()-points[j]->x())/(points[(j-1+points.size())%points.size()]->y()-points[j]->y());
                    p->next=pNET[i]->next;
                    pNET[i]->next=p;
                }
                if(points[(j+1+points.size())%points.size()]->y()>points[j]->y())
                {
                    NET *p=new NET;
                    p->x=points[j]->x();
                    p->ymax=points[(j+1+points.size())%points.size()]->y();
                    p->dx=1.0*(points[(j+1+points.size())%points.size()]->x()-points[j]->x())/(points[(j+1+points.size())%points.size()]->y()-points[j]->y());
                    p->next=pNET[i]->next;
                    pNET[i]->next=p;
                }
            }
    }

    /******建立并更新活性边表AET*****************************************************/
    for(i=0; i<=this->pymax; i++)
    {
        //计算新的交点x,更新AET
        NET *p=pAET->next;
        while(p)
        {
            p->x=p->x + p->dx;
            p=p->next;
        }
        //更新后新AET先排序*************************************************************/
//        //断表排序,不再开辟空间
        AET *tq=pAET;
        p=pAET->next;
        tq->next=NULL;
        while(p)
        {
            while(tq->next && p->x >= tq->next->x)
                tq=tq->next;
            NET *s=p->next;
            p->next=tq->next;
            tq->next=p;
            p=s;
            tq=pAET;
        }
        //(改进算法)先从AET表中删除ymax==i的结点****************************************/
        AET *q=pAET;
        p=q->next;
        while(p)
        {
            if(p->ymax==i)
            {
                q->next=p->next;
                delete p;
                p=q->next;
            }
            else
            {
                q=q->next;
                p=q->next;
            }
        }
        //将NET中的新点加入AET,并用插入法按X值递增排序**********************************/
        p=pNET[i]->next;
        q=pAET;
        while(p)
        {
            while(q->next && p->x >= q->next->x)
                q=q->next;
            NET *s=p->next;
            p->next=q->next;
            q->next=p;
            p=s;
            q=pAET;
        }
        /******配对填充颜色***************************************************************/

        p=pAET->next;
        while(p && p->next)
        {
            for(float j=p->x; j<=p->next->x; j++)
                painter->drawPoint(static_cast<int>(j),i);
            p=p->next->next;//考虑端点情况
        }
    }
}

void Polygon::traslation_polygon(GLint x, GLint y)
{
    for(int i=0;i<this->points.size();i++){
        this->points[i]->rx()+=x;
        this->points[i]->ry()+=y;
    }
}

void Polygon::rotate_polygon(double x, double y, double angel)
{
    double radian=(3.14159/180)*angel;
    double old_x,old_y;
    for(int i=0;i<points.size();i++){
        old_x=points[i]->rx();
        old_y=points[i]->ry();
        points[i]->rx()=x+qCos(radian)*(old_x-x)-qSin(radian)*(old_y-y);
        points[i]->ry()=y+qSin(radian)*(old_x-x)+qCos(radian)*(old_y-y);
    }
}

void Polygon::zoom_polyogn(double x, double y, double factor_x, double factor_y)
{
    for(int i=0;i<points.size();i++){
        points[i]->rx()=factor_x*points[i]->rx()+(1-factor_x)*x;
        points[i]->ry()=factor_y*points[i]->ry()+(1-factor_y)*y;
    }
}
