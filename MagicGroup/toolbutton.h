#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

#include <QIcon>
#include <QString>
#include <QActionEvent>
#include <QToolButton>
#include <QAction>
#include<QTimer>

class ToolButton : public QToolButton
{
    Q_OBJECT
public:
    ToolButton(const QIcon &staticIcon, const QIcon &pressedIcon,int *count,int *graph_judge, QAction *act);
    bool toolbutton_press();
protected:
    void mousePressEvent(QMouseEvent *);
private slots:
    void button_activejudge();
private:
    QAction *myaction;
    QIcon sIcon, pIcon;
    int *flag;
    int *judge;
    int old_flag;
    QTimer *flag_check;
};

#endif // TOOLBUTTON_H
