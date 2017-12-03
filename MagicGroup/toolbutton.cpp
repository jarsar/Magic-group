#include "toolbutton.h"

ToolButton::ToolButton(const QIcon &staticIcon, const QIcon &pressedIcon,int *count,int *graph_judge, QAction *act)
{
    this->sIcon = staticIcon;
    this->pIcon = pressedIcon;
    this->setDefaultAction(act);
    this->setIcon(staticIcon);
    flag=count;
    judge=graph_judge;
    myaction=act;
    flag_check=new QTimer(this);
    connect(flag_check,SIGNAL(timeout()),this,SLOT(button_activejudge()));
    flag_check->start(1);
}

void ToolButton::mousePressEvent(QMouseEvent *)
{
    if(myaction->text()=="line"){
        this->judge[0]=1;
    }
    else if(myaction->text()=="round"){
        this->judge[0]=2;
    }
    else if(myaction->text()=="curve"){
         this->judge[0]=3;
    }
    else if(myaction->text()=="ellipse"){
         this->judge[0]=4;
    }
    else if(myaction->text()=="polygon"){
         this->judge[0]=5;
    }
    else if(myaction->text()=="translation"){
         this->judge[0]=6;
    }
    else if(myaction->text()=="rotate"){
         this->judge[0]=7;
    }
    else if(myaction->text()=="zoom"){
         this->judge[0]=8;
    }
    else if(myaction->text()=="fill"){
         this->judge[0]=9;
    }
    else if(myaction->text()=="cut"){
         this->judge[0]=10;
    }
    else if(myaction->text()=="3D"){
         this->judge[0]=11;
    }

    flag[0]=flag[0]+1;
    old_flag=flag[0];
    this->setIcon(pIcon);
}

void ToolButton::button_activejudge(){
    if(old_flag!=flag[0])
        setIcon(sIcon);
}
