#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    count=new int[1];
    count[1]=0;
    graph_judge=new int[1];
    graph_judge[0]=0;
    ui->setupUi(this);
    ui->myGLWidget->get_buttonjudge(this->graph_judge);
    this->mytoolbar();
    QString str = "background-color : rgb(0,0,0)";
    this->ui->showcolor_label->setStyleSheet(str);
    time_stackedwidget_refresh=new QTimer(this);
    connect(time_stackedwidget_refresh,SIGNAL(timeout()),this,SLOT(set_choosemenu()));
    time_stackedwidget_refresh->start(1);
    connect(this,SIGNAL(choosemenu(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
    //设置颜色属性
    this->ui->myGLWidget->get_information(ui->spinBox_red,ui->spinBox_green,ui->spinBox_blue,ui->showcolor_label,ui->stackedWidget);
    connect(ui->ColorConfirmButton,SIGNAL(clicked(bool)),ui->myGLWidget,SLOT(setcolor()));
    //设置图形属性
    this->ui->myGLWidget->set_line(ui->spinBox_lx0,ui->spinBox_ly0,ui->spinBox_lx1,ui->spinBox_ly1);
    this->ui->myGLWidget->set_round(ui->spinBox_rR,ui->spinBox_rx,ui->spinBox_ry);
    this->ui->myGLWidget->set_ellipse(ui->spinBox_ex,ui->spinBox_ey,ui->spinBox_ea,ui->spinBox_eb);
    this->ui->myGLWidget->set_polygon(ui->spinBox_px,ui->spinBox_py);
    //修改直线
    connect(ui->lineconfirmButton,SIGNAL(clicked(bool)),ui->myGLWidget,SLOT(draw_line()));
    //修改圆
    connect(ui->roundconfirmButton,SIGNAL(clicked(bool)),ui->myGLWidget,SLOT(draw_round()));
    //修改椭圆
    connect(ui->ellipseconfirmButton,SIGNAL(clicked(bool)),ui->myGLWidget,SLOT(draw_ellipse()));
    //画多边形
    connect(ui->startButton,SIGNAL(clicked(bool)),ui->myGLWidget,SLOT(create_polygon()));
    connect(ui->addconfirmButton,SIGNAL(clicked(bool)),ui->myGLWidget,SLOT(draw_polygon()));
    connect(ui->polygonconfirmButton,SIGNAL(clicked(bool)),ui->myGLWidget,SLOT(draw_polygon_finally()));
    //圆，椭圆，多边形填充
    connect(ui->fillButton,SIGNAL(clicked(bool)),ui->myGLWidget,SLOT(fill_color()));
    //设置图形变换属性
    this->ui->myGLWidget->set_graph_change(ui->spinBox_tx,ui->spinBox_ty,ui->spinBox_rotate_x,ui->spinBox_rotate_y,ui->SpinBox_angel,ui->spinBox_zoom_x,ui->spinBox_zoom_y,ui->SpinBox_zfactor_x,ui->SpinBox_zfactor_y);
    //平移
    connect(ui->traconfirmButton,SIGNAL(clicked(bool)),ui->myGLWidget,SLOT(translation_graph()));
    //旋转
    connect(ui->rotateconfirmButton,SIGNAL(clicked(bool)),ui->myGLWidget,SLOT(rotate_graph()));
    //缩放
    connect(ui->zoomconfirmButton,SIGNAL(clicked(bool)),ui->myGLWidget,SLOT(zoom_graph()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mytoolbar(){
    QAction *lineAction=new QAction(QString::QString("line"));
    lineToolButton=new ToolButton(QIcon::QIcon(":/new/png/lineStatic.png"),QIcon::QIcon(":/new/png/linePressed.png"),count,graph_judge,lineAction);
    ui->mainToolBar->addWidget(lineToolButton);

    QAction *roundAction=new QAction(QString::QString("round"));
    roundToolButton=new ToolButton(QIcon::QIcon(":/new/png/roundStatic.png"),QIcon::QIcon(":/new/png/roundPressed.png"),count,graph_judge,roundAction);
    ui->mainToolBar->addWidget(roundToolButton);

    QAction *curveAction=new QAction(QString::QString("curve"));
    curveToolButton=new ToolButton(QIcon::QIcon(":/new/png/curveStatic.png"),QIcon::QIcon(":/new/png/curvePressed.png"),count,graph_judge,curveAction);
    ui->mainToolBar->addWidget(curveToolButton);

    QAction *ellipseAction=new QAction(QString::QString("ellipse"));
    ellipseToolButton=new ToolButton(QIcon::QIcon(":/new/png/ellipseStatic.png"),QIcon::QIcon(":/new/png/ellipsePressed.png"),count,graph_judge,ellipseAction);
    ui->mainToolBar->addWidget(ellipseToolButton);

    QAction *polygonAction=new QAction(QString::QString("polygon"));
    polygonToolButton=new ToolButton(QIcon::QIcon(":/new/png/polygonStatic.png"),QIcon::QIcon(":/new/png/polygonPressed.png"),count,graph_judge,polygonAction);
    ui->mainToolBar->addWidget(polygonToolButton);

    QAction *translationAction=new QAction(QString::QString("translation"));
    translationToolButton=new ToolButton(QIcon::QIcon(":/new/png/translationStatic.png"),QIcon::QIcon(":/new/png/translationPressed.png"),count,graph_judge,translationAction);
    ui->mainToolBar->addWidget(translationToolButton);

    QAction *rotateAction=new QAction(QString::QString("rotate"));
    rotateToolButton=new ToolButton(QIcon::QIcon(":/new/png/rotateStatic.png"),QIcon::QIcon(":/new/png/rotatePressed.png"),count,graph_judge,rotateAction);
    ui->mainToolBar->addWidget(rotateToolButton);

    QAction *zoomAction=new QAction(QString::QString("zoom"));
    zoomToolButton=new ToolButton(QIcon::QIcon(":/new/png/zoomStatic.png"),QIcon::QIcon(":/new/png/zoomPressed.png"),count,graph_judge,zoomAction);
    ui->mainToolBar->addWidget(zoomToolButton);

    QAction *fillAction=new QAction(QString::QString("fill"));
    fillToolButton=new ToolButton(QIcon::QIcon(":/new/png/fillStatic.png"),QIcon::QIcon(":/new/png/fillPressed.png"),count,graph_judge,fillAction);
    ui->mainToolBar->addWidget(fillToolButton);

    QAction *cutAction=new QAction(QString::QString("cut"));
    cutToolButton=new ToolButton(QIcon::QIcon(":/new/png/cutStatic.png"),QIcon::QIcon(":/new/png/cutPressed.png"),count,graph_judge,cutAction);
    ui->mainToolBar->addWidget(cutToolButton);

    QAction *triDAction=new QAction(QString::QString("3D"));
    triDToolButton=new ToolButton(QIcon::QIcon(":/new/png/3dStatic.png"),QIcon::QIcon(":/new/png/3dPressed.png"),count,graph_judge,triDAction);
    ui->mainToolBar->addWidget(triDToolButton);
}

void MainWindow::set_choosemenu(){
    switch (this->graph_judge[0]) {
    case 1:
        emit choosemenu(1);
        break;
    case 2:
        emit choosemenu(2);
        break;
    case 3:
        emit choosemenu(3);
        break;
    case 4:
        emit choosemenu(4);
        break;
    case 5:
        emit choosemenu(5);
        break;
    case 6:
        emit choosemenu(6);
        break;
    case 7:
        emit choosemenu(7);
        break;
    case 8:
        emit choosemenu(8);
        break;
    case 9:
        emit choosemenu(9);
        break;
    case 10:
        emit choosemenu(10);
        break;
    case 11:
        emit choosemenu(11);
        break;
    default:
        break;
    }
}
