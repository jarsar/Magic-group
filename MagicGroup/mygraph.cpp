#include<mygraph.h>

MyGraph::MyGraph(){
    this->pen=new QPen;
    pen->setColor(Qt::black);
}

void MyGraph::set_color(QColor color){
    pen->setColor(color);
}
