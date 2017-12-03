#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTimer>
#include <QToolButton>
#include "toolbutton.h"
#include"line.h"
#include<iostream>
#include<QList>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void mytoolbar();
private:
    Ui::MainWindow *ui;
private:
    QTimer *time_referesh_buttonflag;
private:
    ToolButton *lineToolButton;
    ToolButton *curveToolButton;
    ToolButton *roundToolButton;
    ToolButton *ellipseToolButton;
    ToolButton *polygonToolButton;
    ToolButton *translationToolButton;
    ToolButton *rotateToolButton;
    ToolButton *zoomToolButton;
    ToolButton *fillToolButton;
    ToolButton *cutToolButton;
    ToolButton *triDToolButton;
public:
    int *count;//用于判断toolbar上是哪个action
    int *graph_judge;//用于判断哪个action处于active状态
};

#endif // MAINWINDOW_H
