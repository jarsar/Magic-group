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

void MyGLWidget::setcolor(){
    QColor c(this->red->value(),this->green->value(),this->blue->value());
    QString str = "background-color: rgb(" + red->text() + ", " + green->text() + ", " +blue->text() + ");";
    this->labelshowcolor->setStyleSheet(str);
    this->color=c;
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
        this->save_graph();
        this->draw();
}

void MyGLWidget::draw(){
    glClear(GL_COLOR_BUFFER_BIT);
    this->redraw();
    painter.begin(this);
    switch (this->buttonjudge[0]) {
    case 1:
        line->LineDDA(&this->painter);
        break;
    case 2:
        round->drawround(&this->painter);
        break;
    case 3:
        break;
    case 4:
        ellipse->drawellipse(&this->painter);
        break;
    default:
        break;
    }
    painter.end();
}

void MyGLWidget::get_buttonjudge(int *buttonjudge){
    this->buttonjudge=buttonjudge;
}

void MyGLWidget::redraw(){
    painter.begin(this);
    //line redraw
    for(int i=0;i<this->lines.size();i++){
        this->lines[i]->LineDDA(&this->painter);
    }
    //round redraw
    for(int i=0;i<this->rounds.size();i++){
        this->rounds[i]->drawround(&this->painter);
    }
    //ellipse redraw
    for(int i=0;i<this->ellipses.size();i++){
        this->ellipses[i]->drawellipse(&this->painter);
    }
    painter.end();
}

void MyGLWidget::create_graph(){
    this->graphflag=this->buttonjudge[0];
    switch (this->buttonjudge[0]) {
    case 1:
        line=new Line();
        line->set_color(color);
        break;
    case 2:
        round=new Round();

        break;
    case 3:
        break;
    case 4:
        ellipse=new Ellipse();

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

void MyGLWidget::save_graph(){
    switch (this->buttonjudge[0]) {
    case 1:
        lines.push_back(this->line);
        break;
    case 2:
        rounds.push_back(this->round);
        break;
    case 3:
        break;
    case 4:
        ellipses.push_back(this->ellipse);
        break;
    default:
        break;
    }
}

int *MyGLWidget::get_graphflag(){
    return &this->graphflag;
}
