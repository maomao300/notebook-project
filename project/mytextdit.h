#ifndef MYTEXTDIT_H
#define MYTEXTDIT_H

#include <QTextEdit>



class mytextdit : public QTextEdit
{
public:
    mytextdit(QWidget* parent);
    int ctr_key_pressed=0;

protected:
    void wheelEvent(QWheelEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
};

#endif // MYTEXTDIT_H
