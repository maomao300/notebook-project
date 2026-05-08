#include "mytextdit.h"

#include <QWheelEvent>
#include<QDebug>
#include<QWidget>

mytextdit::mytextdit(QWidget *parent):QTextEdit(parent)//通过调用基类构造函数传入 parent，使当前控件成为父 widget 的子对象，从而纳入 UI 体系。
{

}

void mytextdit::wheelEvent(QWheelEvent *e)
{
    qDebug()<<e->angleDelta().y();
    if(ctr_key_pressed==1)//定义一个变量，判断按键是否按下，从实现crtl+鼠标滚轮，放大/缩小字体的功能
    {
        if(e->angleDelta().y()>0)//滚轮向前滚
        {
            zoomIn();//QTextEdit的函数，作用：放大字体
        }else if(e->angleDelta().y()<0)
        {
            zoomOut();//减小字体
        }
        e->accept();//这里表示，该事件已经被当前控件处理完毕，否则会向上层父控件继续传播。
    }
    else
    QTextEdit::wheelEvent(e);//针对事件没有被处理的情况，调用基类QTextEdit对这个事件的处理
}

void mytextdit::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Control)
    {
        ctr_key_pressed=1;
    }
    QTextEdit::keyPressEvent(e);
}

void mytextdit::keyReleaseEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Control)
    {
        ctr_key_pressed=0;
    }
    QTextEdit::keyReleaseEvent(e);
}


