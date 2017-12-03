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
