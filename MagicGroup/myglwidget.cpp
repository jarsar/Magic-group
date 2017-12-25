#include "myglwidget.h"

MyGLWidget::MyGLWidget(QWidget * parent)
{
    check_flag=false;
}

MyGLWidget::~MyGLWidget()
{

}
void MyGLWidget::get_information(QSpinBox *red, QSpinBox *green, QSpinBox *blue, QLabel *labelshowcolor, QStackedWidget *mystack){
    this->red=red;
    this->green=green;
    this->blue=blue;
    this->labelshowcolor=labelshowcolor;
    this->mystack=mystack;
}

void MyGLWidget::set_line(QSpinBox *lx0, QSpinBox *ly0, QSpinBox *lx1, QSpinBox *ly1){
    this->lx0=lx0;
    this->ly0=ly0;
    this->lx1=lx1;
    this->ly1=ly1;
}

void MyGLWidget::set_round(QSpinBox *rR, QSpinBox *rx, QSpinBox *ry){
    this->rR=rR;
    this->rx=rx;
    this->ry=ry;
}

void MyGLWidget::set_ellipse(QSpinBox *ex, QSpinBox *ey, QSpinBox *ea, QSpinBox *eb){
    this->ex=ex;
    this->ey=ey;
    this->ea=ea;
    this->eb=eb;
}

void MyGLWidget::set_polygon(QSpinBox *px, QSpinBox *py){
    this->px=px;
    this->py=py;
}

void MyGLWidget::setcolor(){
    QColor color(this->red->value(),this->green->value(),this->blue->value());
    QString str = "background-color: rgb(" + red->text() + ", " + green->text() + ", " +blue->text() + ");";
    this->labelshowcolor->setStyleSheet(str);
    graphs[graphs.size()-1]->set_color(color);
    painter.begin(this);
    graphs[graphs.size()-1]->draw(&this->painter);
    if(graphs[graphs.size()-1]->get_Kind()==kpolygon){
        graphs[graphs.size()-1]->redraw(&this->painter);
    }
    painter.end();
}

void MyGLWidget::draw_line(){
    painter.begin(this);
    glClear(GL_COLOR_BUFFER_BIT);
    painter.end();
    graph->setline(this->lx0->value(),this->ly0->value(),this->lx1->value(),this->ly1->value());
    graphs.pop_back();
    graphs.push_back(graph);
    this->redraw();
}

void MyGLWidget::draw_round(){
    painter.begin(this);
    glClear(GL_COLOR_BUFFER_BIT);
    painter.end();
    QPoint p;
    p.setX(rx->value());
    p.setY(ry->value());
    graph->setround(p,this->rR->value());
    graphs.pop_back();
    graphs.push_back(graph);
    this->redraw();
}

void MyGLWidget::create_polygon(){
    polygon=new Polygon();
    graph=polygon;
}

void MyGLWidget::draw_ellipse(){
    painter.begin(this);
    glClear(GL_COLOR_BUFFER_BIT);
    painter.end();
    QPoint p;
    p.setX(ex->value());
    p.setY(ey->value());
    graph->setellipse(p,this->ea->value(),this->eb->value());
    graphs.pop_back();
    graphs.push_back(graph);
    this->redraw();
}

void MyGLWidget::draw_polygon(){
    QPoint p;
    p.setX(this->px->value());
    p.setY(this->py->value());
    graph->setpolygon(p);
    painter.begin(this);
    graph->draw(&painter);
    painter.end();
}

void MyGLWidget::draw_polygon_finally(){
    graphs.push_back(graph);
    this->redraw();
}

void MyGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0f,1.0f,1.0f,1.0f);
}

void MyGLWidget::paintGL()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,NULL);
    QPen pen;
    pen.setColor(Qt::black);
    painter.setPen(pen);
}

void MyGLWidget::resizeGL()
{

}

void MyGLWidget::mousePressEvent(QMouseEvent *event){
    if(event->buttons()&Qt::LeftButton){
        this->create_graph();
        this->x0=event->x();
        this->y0=event->y();
        check_flag=false;
    }
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event){
    if(check_flag==true){
        this->draw();
    }
    this->x1=event->x();
    this->y1=event->y();
    this->get_graphinformation();
    this->draw();
    check_flag=true;
}

void MyGLWidget::mouseReleaseEvent(QMouseEvent *event){
        if(check_flag==true){
            this->draw();
        }
        this->x1=event->x();
        this->y1=event->y();
        this->get_graphinformation();
        this->graphs.push_back(graph);
        this->draw();
}

void MyGLWidget::draw(){
    glClear(GL_COLOR_BUFFER_BIT);
    this->redraw();
    painter.begin(this);
    if(graph->get_Kind()!=kpolygon){
        graph->draw(&this->painter);
    }
    painter.end();
}

void MyGLWidget::get_buttonjudge(int *buttonjudge){
    this->buttonjudge=buttonjudge;
}

void MyGLWidget::redraw(){
    painter.begin(this);
    for(int i=0;i<this->graphs.size();i++){
        graphs[i]->draw(&this->painter);
        if(graphs[i]->get_Kind()==kpolygon){
            graphs[i]->redraw(&painter);
        }
    }
    painter.end();
}

void MyGLWidget::create_graph(){
    this->graphflag=this->buttonjudge[0];
    switch (this->buttonjudge[0]) {
    case 1:{
        line=new Line();
        graph=line;
    }
        break;
    case 2:{
        round=new Round();
        graph=round;
    }
        break;
    case 3:
        break;
    case 4:{
        ellipse=new Ellipse();
        graph=ellipse;
    }
        break;
    case 5:
        break;
    default:
        break;
    }
}

void MyGLWidget::get_graphinformation(){
    switch (this->buttonjudge[0]) {
    case 1:
        line->setline(this->x0,this->y0,this->x1,this->y1);
        break;
    case 2:{
        QPoint center;
        center.setX(this->x0);
        center.setY(this->y0);
        GLint R=qSqrt((this->x1-this->x0)*(this->x1-this->x0)+(this->y1-this->y0)*(this->y1-this->y0));
        round->setround(center,R);}
        break;
    case 3:
        break;
    case 4:{
        QPoint point;
        GLint a,b;
        point.setX(this->x0);
        point.setY(this->y0);
        a=qFabs(double(this->x1-this->x0));
        b=qFabs(double(this->y1-this->y0));
        ellipse->setellipse(point,a,b);
    }
        break;
    default:
        break;
    }
}

int *MyGLWidget::get_graphflag(){
    return &this->graphflag;
}
