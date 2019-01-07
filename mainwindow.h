#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "sheet.h"
#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QPaintEvent>
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QPainterPath>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QBrush>
#include <QMessageBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <Qpalette>
#include <QtDebug>
#include <QPushButton>
#include <QLabel>
#include <QMainWindow>
#include <bits/stdc++.h>
using namespace std;
//class QStackedWidget;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init();
    bool iselement(string temp);
    bool judge();
    string getstring(string str,int l,int r);
    void getelement();
    int quit_parentheses(int i,string str);
    void print();
    void InitOther();
    void InitUI();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_open_sheet_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_15_clicked();
    void on_pushButton_16_clicked();


private:
    Ui::MainWindow *ui;
    sheet *a;
    string ch;//输入
    int len,num_of_basic=0,num_of_element=0;//基本变元，总变元
    map<string,int> mp;//防止变元重复储存
    map<char,int> pri;//符号优先级
    queue<int> subscript;//保存括号下标
    vector<string> element;//储存变元，前面是基本变元
    int matrix[20][20];//真值
    int id_of_parentheses[150];//括号匹配
//    QStackedWidget *m_pStackedWidget;
};

#endif // MAINWINDOW_H
