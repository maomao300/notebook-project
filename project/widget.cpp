#include "widget.h"
#include "ui_widget.h"

#include <QFileDialog>
#include<QDebug>
#include <QBrush>
#include <QMessageBox>
#include <QShortcut>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setLayout(ui->verticalLayout);
    ui->widgetbottom->setLayout(ui->hLayoutlabel);

    QShortcut *shortcutsave = new QShortcut(QKeySequence(tr("Ctrl+s", "File|Save")),this);
    QShortcut *shortcutopen = new QShortcut(QKeySequence(tr("Ctrl+o", "File|Open")),this);
    QShortcut *shortcutinfont = new QShortcut(QKeySequence(tr("Ctrl+=", "File|Save")),this);
    QShortcut *shortcutdefont = new QShortcut(QKeySequence(tr("Ctrl+-", "File|Save")),this);



    QObject::connect(shortcutsave,SIGNAL(activated()),this,SLOT(on_Buttonsave_clicked()));
    QObject::connect(shortcutopen,SIGNAL(activated()),this,SLOT(on_Buttonopen_clicked()));

    QObject::connect(shortcutinfont,&QShortcut::activated,[=](){
        increase_font_size();
    });
    QObject::connect(shortcutdefont,&QShortcut::activated,[=](){
        decrease_font_size();
    });



}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_Buttonopen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                        "D:/Project/QTproject",
                                                        tr("Text files (*.txt)"));
    qDebug()<<fileName<<endl;
      //1.打开文件
      file.setFileName(fileName);
      if(!file.open(QIODevice::ReadWrite|QIODevice::Text))
      {
          qDebug()<<"file open error"<<endl;
          return;
      }
      //读取文件
      this->setWindowTitle(fileName);
      QTextStream in(&file);
     QString str= ui->comboBox->currentText();
     const char* c_str=str.toStdString().c_str();
      in.setCodec(c_str); //设置编码
      while(!in.atEnd())
          {
              QString context =in.readLine();
              //输出一行内容
             ui->textEdit->append(context);
          }
       this->setWindowTitle(fileName+"-notebook");
}

void Widget::on_Buttonsave_clicked()
{

        if(!file.isOpen())
        {
            QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                            "D:/Project/QTproject",
                                            tr("Text files (*.txt)"));
             //1.打开文件
            file.setFileName(fileName);
            if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
            {
                qDebug()<<"file open error"<<endl;
                return;
            }
             this->setWindowTitle(fileName+"-notebook");
        }
        //2.写入
        file.resize(0);
        file.seek(0);
        QTextStream out(&file);
        out.setCodec(ui->comboBox->currentText().toStdString().c_str()); //设置编码
        out<<ui->textEdit->toPlainText();

}

void Widget::on_Buttonclose_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Please note");
     msgBox.setText("The document has been modified.");
     msgBox.setInformativeText("Do you want to save your changes?");
     msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
     msgBox.setDefaultButton(QMessageBox::Save);
     int ret = msgBox.exec();
     switch (ret) {
        case QMessageBox::Save:
            on_Buttonsave_clicked();
            break;
        case QMessageBox::Discard:
         ui->textEdit->clear();
        if(file.isOpen())
        {
            file.close();
            ui->textEdit->clear();
            this->setWindowTitle("notebook");
        }
            break;
        case QMessageBox::Cancel:
            break;
        default:

            break;
      }

}

void Widget::on_comboBox_currentIndexChanged(int index)
{
        ui->textEdit->clear();
        if(file.isOpen())
        {

            QTextStream in(&file);
            in.setCodec(ui->comboBox->itemText(index).toStdString().c_str()); //设置编码
            file.seek(0);
            while(!in.atEnd())
                {
                    QString context =in.readLine();
                    //输出一行内容
                   ui->textEdit->append(context);
                }
        }
}

void Widget::on_textEdit_cursorPositionChanged()
{
    QTextCursor cursor=ui->textEdit->textCursor();
    QString blocknum=QString::number(cursor.blockNumber()+1);
    QString columnnum=QString::number(cursor.columnNumber()+1);
    const QString c_str="L:"+blocknum+",C:"+columnnum;
    ui->labelposition->setText(c_str);
    //设置当前行高亮
    QList<QTextEdit::ExtraSelection> extraselections;
    QTextEdit::ExtraSelection ext;
    //获取当前行
    ext.cursor=ui->textEdit->textCursor();
    //颜色
    QBrush qbrush(Qt::lightGray);
    //设置样式
    ext.format.setBackground(qbrush);
    ext.format.setProperty(QTextFormat::FullWidthSelection,true);
    //添加
    extraselections.append(ext);
    ui->textEdit->setExtraSelections(extraselections);
}

void Widget::increase_font_size()
{   //获取当前字体信息
    QFont font=ui->textEdit->font();
    //获取当前字体的大小
    int fontsize=font.pointSize();
    if(fontsize==-1)return;
    //设置字体大小
    font.setPointSize(fontsize+1);
    ui->textEdit->setFont(font);

}

void Widget::decrease_font_size()
{
    //获取当前字体信息
        QFont font=ui->textEdit->font();
        //获取当前字体的大小
        int fontsize=font.pointSize();
        if(fontsize==-1)return;
        //设置字体大小
        font.setPointSize(fontsize-1);
        ui->textEdit->setFont(font);
}

