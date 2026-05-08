#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    QFile file;
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void increase_font_size();
    void decrease_font_size();

private slots:
    void on_Buttonopen_clicked();

    void on_Buttonsave_clicked();

    void on_Buttonclose_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_textEdit_cursorPositionChanged();


private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
