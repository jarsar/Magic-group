#include<mygraph.h>

MyGraph::MyGraph(){
    this->pen=new QPen;
    pen->setColor(Qt::black);
    this->is_fill=false;
}

void MyGraph::set_color(QColor color){
    pen->setColor(color);
}

Kind MyGraph::get_Kind(){
    return this->kind;
}

bool MyGraph::get_is_rotate()
{
    return this->is_rotate;
}

bool MyGraph::get_fill(){
    return this->is_fill;
}
