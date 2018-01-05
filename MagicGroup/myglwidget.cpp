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

void MyGLWidget::set_graph_change(QSpinBox *tx, QSpinBox *ty, QSpinBox *rotate_x, QSpinBox *rotate_y, QDoubleSpinBox *angel, QSpinBox *zoom_x, QSpinBox *zoom_y, QDoubleSpinBox *factor_x, QDoubleSpinBox *factor_y)
{
    this->tx=tx;
    this->ty=ty;
    this->rotate_x=rotate_x;
    this->rotate_y=rotate_y;
    this->angel=angel;
    this->zoom_x=zoom_x;
    this->zoom_y=zoom_y;
    this->factor_x=factor_x;
    this->factor_y=factor_y;
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

void MyGLWidget::fill_color(){
    QColor color(this->red->value(),this->green->value(),this->blue->value());
    QString str = "background-color: rgb(" + red->text() + ", " + green->text() + ", " +blue->text() + ");";
    this->labelshowcolor->setStyleSheet(str);
    this->graph->set_color(color);
    painter.begin(this);
    this->graph->fillgraph(&this->painter);
    painter.end();
}

void MyGLWidget::translation_graph()
{
    switch (this->graph->get_Kind()) {
    case kline:{
        line->translation_line(this->tx->value(),this->ty->value());
        this->graphs.pop_back();
        this->graph=line;
        this->graphs.push_back(this->graph);
    }
        break;
    case kround:{
        round->translation_round(this->tx->value(),this->ty->value());
        this->graphs.pop_back();
        this->graph=round;
        this->graphs.push_back(this->graph);
    }
        break;
    case kellipse:{
            ellipse->translation_ellipse(this->tx->value(),this->ty->value());
            this->graphs.pop_back();
            this->graph=ellipse;
            this->graphs.push_back(this->graph);
        }
        break;
    case kpolygon:{
            polygon->traslation_polygon(this->tx->value(),this->ty->value());
            this->graphs.pop_back();
            this->graph=polygon;
            this->graphs.push_back(this->graph);
        }
        break;
    default:
        break;
    }
    painter.begin(this);
    glClear(GL_COLOR_BUFFER_BIT);
    painter.end();
    this->redraw();
}

void MyGLWidget::rotate_graph()
{
    switch (this->graph->get_Kind()) {
    case kline:{
        line->rotate_line(rotate_x->value(),rotate_y->value(),angel->value());
        this->graphs.pop_back();
        this->graph=line;
        this->graphs.push_back(this->graph);
    }
        break;
    case kround:{
        round->rotate_round(rotate_x->value(),rotate_y->value(),angel->value());
        this->graphs.pop_back();
        this->graph=round;
        this->graphs.push_back(this->graph);
    }
        break;
    case kellipse:{
            ellipse->rotate_ellipse(rotate_x->value(),rotate_y->value(),angel->value());
            this->graphs.pop_back();
            this->graph=ellipse;
            this->graphs.push_back(this->graph);
        }
        break;
    case kpolygon:{
            polygon->rotate_polygon(rotate_x->value(),rotate_y->value(),angel->value());
            this->graphs.pop_back();
            this->graph=polygon;
            this->graphs.push_back(this->graph);
        }
        break;
    default:
        break;
    }
    painter.begin(this);
    glClear(GL_COLOR_BUFFER_BIT);
    painter.end();
    this->redraw();
}

void MyGLWidget::zoom_graph()
{
    switch (this->graph->get_Kind()) {
    case kline:{
        line->zoom_line(zoom_x->value(),zoom_y->value(),factor_x->value(),factor_y->value());
        this->graphs.pop_back();
        this->graph=line;
        this->graphs.push_back(this->graph);
    }
        break;
    case kround:{
        round->zoom_round(zoom_x->value(),zoom_y->value(),factor_x->value(),factor_y->value());
        this->graphs.pop_back();
        this->graph=round;
        this->graphs.push_back(this->graph);
    }
        break;
    case kellipse:{
            ellipse->zoom_ellipse(zoom_x->value(),zoom_y->value(),factor_x->value(),factor_y->value());
            this->graphs.pop_back();
            this->graph=ellipse;
            this->graphs.push_back(this->graph);
        }
        break;
    case kpolygon:{
            polygon->zoom_polyogn(zoom_x->value(),zoom_y->value(),factor_x->value(),factor_y->value());
            this->graphs.pop_back();
            this->graph=polygon;
            this->graphs.push_back(this->graph);
        }
        break;
    default:
        break;
    }
    painter.begin(this);
    glClear(GL_COLOR_BUFFER_BIT);
    painter.end();
    this->redraw();
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
        if(graphs[i]->get_Kind()==kellipse){
            if(graphs[i]->get_is_rotate()==true){
                graphs[i]->redraw(&painter);
            }else{
                graphs[i]->draw(&this->painter);
            }
        }else{
            graphs[i]->draw(&this->painter);
            if(graphs[i]->get_Kind()==kpolygon){
                graphs[i]->redraw(&painter);
            }
            if(graphs[i]->get_fill()==true){
                graphs[i]->fillgraph(&this->painter);
            }
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
