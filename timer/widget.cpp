#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QTimer>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QKeyEvent>
#include <QDialog>
#include <QFormLayout>
#include <QSpinBox>
#include <QKeySequenceEdit>
#include <QDialogButtonBox>
#include <QFont>
#include <QThread>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //input dialog
    QDialog dialog(this);
    QFormLayout form(&dialog);
    dialog.setWindowTitle("User inputs");

    // Value1
    QString value1 = QString("Name: ");
    QLineEdit *lineEdit = new QLineEdit(&dialog);
    form.addRow(value1, lineEdit);
    // Value2
    QString value2 = QString("Time(2 decimals maximum): ");
    QDoubleSpinBox *spinbox = new QDoubleSpinBox(&dialog);
    spinbox->setMinimum(0.00);
    spinbox->setMaximum(9999999.99);
    form.addRow(value2, spinbox);


    //Key Binding for start and pause
    QString value3 = QString("Key for start: ");
    QKeySequenceEdit * startkey = new QKeySequenceEdit(&dialog);
    form.addRow(value3, startkey);

    QString value4 = QString("Key for pause: ");
    QKeySequenceEdit * pausekey = new QKeySequenceEdit(&dialog);
    form.addRow(value4, pausekey);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Process when OK button is clicked
    if (dialog.exec() == QDialog::Accepted) {
        // Do something here







    //文件生成

    QString path("C:\\timer_output");
    QDir dir;
    if(!dir.exists(path)){
        dir.mkpath(path);
    }
    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("yyyy_MM_dd_hh_mm_ss");

    this->setWindowTitle(lineEdit->text());
    QString totalpath(path + "\\Timer_output_" +lineEdit->text()+"_"+ formattedTime + ".txt" );











    //计时器
    QTimer* timer = new QTimer(this);
    static int num2 = 0; //计时器counter

    timer->start(10); //倒计时小数点后两位精度
    double n = spinbox->value();

    //写入用户输入的倒计时
    QFile file(totalpath);
    if(file.open(QIODevice::Append)){
        qDebug("here");
        QTextStream out(&file);
        out << "Input: "<<QString::number(n, 'f', 2) << "s"<< "\n\n";
        file.close();
    }
    else{
        qDebug("failed");
    }


    connect(timer, &QTimer::timeout,[=](){

        static double num = n;  //小数点后两位
        ui->label->setText(QString::number(num, 'f', 2));
        num-=0.01;
        if(num <= 0){
           double n = num2/100.00;
           timer->stop();


           if (QMessageBox::Ok == QMessageBox::information(this, "info", "TimeOut!",QMessageBox::Ok)){
               QFile file(totalpath); //写入计时器最终计数
               if(file.open(QIODevice::Append)){
                   qDebug("here");
                   QTextStream out(&file);
                   out <<"\n"<< "final: ";

                   out << QString::number(n, 'f', 2) << "s"<< "\n";
                   file.close();
               }
               else{
                   qDebug("failed");
               }
               this->close();
           }

      }

    });

    QTimer * timer2 = new QTimer(this);

    timer2->start(); //0.01秒间隔

    connect(timer2, &QTimer::timeout,[=](){
        num2++;
    });

    QKeySequence resume = QKeySequence(startkey->keySequence());
    QKeySequence pause = QKeySequence(pausekey->keySequence());
    ui->btnstart->setText("Running");
    ui->btnstop->setText("Pause(" + pause.toString() + ")");
    QFont font1 = ui->btnstop->font();
    font1.setBold(true);
    font1.setPointSize(6);
    QFont font2 = ui->btnstart->font();
    font2.setPointSize(4);
    font2.setBold(false);

    ui->btnstart->setFont(font1);
    ui->btnstart->setShortcut(resume);
    ui->btnstop->setShortcut(pause);

    //点击暂停按钮 实现停止定时器
    connect(ui->btnstop, &QPushButton::clicked, [=]{
       timer2->stop();
       ui->btnstop->setText("Pausing");
       ui->btnstart->setText("Resume(" + resume.toString() + ")");
       ui->btnstop->setFont(font1);
       ui->btnstart->setFont(font2);
       ui->btnstart->setShortcut(resume);
       ui->btnstop->setShortcut(pause);

       QFile file(totalpath);
       if(file.open(QIODevice::Append)){
           qDebug("here");
           QTextStream out(&file);
           out << "Stopped: ";
           double n = num2/100.00;
           out << QString::number(n, 'f', 2) <<"s"<<"\n";
           file.close();
       }
       else{
           qDebug("failed");
       }
    });

    connect(ui->btnstart, &QPushButton::clicked, [=]{
        timer2->start(10);
        ui->btnstart->setText("Running");
        ui->btnstop->setText("Pause(" + pause.toString() + ")");
        ui->btnstart->setFont(font1);
        ui->btnstop->setFont(font2);
        ui->btnstart->setShortcut(resume);
        ui->btnstop->setShortcut(pause);
        QFile file(totalpath);
        if(file.open(QIODevice::Append)){
            qDebug("here");
            QTextStream out(&file);
            out << "Started: ";
            double n = num2/100.00;
            out << QString::number(n, 'f', 2) << "s"<< "\n";
            file.close();
        }
        else{
            qDebug("failed");
        }


    });

}
}



Widget::~Widget()
{
    delete ui;
}





