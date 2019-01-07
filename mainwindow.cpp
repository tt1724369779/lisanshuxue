#include "mainwindow.h"
#include "ui_mainwindow.h"
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
#include <QVBoxLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QTextEdit>
#include <QTextBrowser>
#include <QGroupBox>//模拟方式显示数值
#include <QSpinBox>//数字
#include <QDateEdit>
#include <QTimeEdit>
#include <QDateTimeEdit>
#include <QTabWidget>//不介绍不算控件
#include <QCompleter>
#include <QHBoxLayout>
#include <QDebug>
#include <QPixmap>
#include <QString>
#include <QLCDNumber>
#include <QTabWidget>
#include <QPainter>
#include <bits/stdc++.h>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
//    ui->tabWidgetPage1->setWindowTitle("合式范式");
//    ui->tabWidgetPage2->setWindowTitle("连通图");
    ui->pushButton_open_sheet->setShortcut(QKeySequence::InsertParagraphSeparator);//将小键盘回车键与登录按钮绑定在一起
    ui->pushButton_open_sheet->setShortcut(Qt::Key_Enter);//将字母区回车键与登录按钮绑定在一起
    ui->pushButton_open_sheet->setShortcut(Qt::Key_Return);//将小键盘回车键与登录按钮绑定在一起
    InitUI();
    //ui->lineEdit->setCompleter(new QCompleter(QStringList() << "<->"<<"->"));
    QStringList word_list;
    word_list<<"<->"<<"->";
    QCompleter *completer = new QCompleter(word_list, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit->setCompleter(completer);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitUI()
{   //
    // 初始化窗体其他属性
    InitOther();
}
// 初始化对话框属性
void MainWindow::InitOther(){
    // 设置对话框icon
    setWindowIcon(QIcon(":/res/ico/my.ico"));
    // 设置窗体标题
}


QString input;
string tempch;
string ch;//输入
int len,num_of_basic=0,num_of_element=0;//基本变元，总变元
map<string,int> mp;//防止变元重复储存
map<char,int> pri;//符号优先级
queue<int> subscript;//保存括号下标
vector<string> element;//储存变元，前面是基本变元
int matrix[1500][1500];//真值
int id_of_parentheses[150];//括号匹配

void MainWindow::init(){//对符号优先级赋值
    memset(matrix,0,sizeof(matrix));
    mp.clear();
    pri.clear();
    while(!subscript.empty())
        subscript.pop();
    memset(id_of_parentheses,0,sizeof(id_of_parentheses));
    element.clear();
    num_of_basic=0;
    num_of_element=0;
    mp.clear();
    for(int i=0;i<ch.size();i++){
        if(i<ch.size()-1){
            if(ch[i]=='!'&&ch[i+1]=='!'){
                for(int j=i+2;j<ch.size();j++){
                    ch[j-2]=ch[j];
                }
                ch.resize(ch.size()-2);
                i--;
            }
        }
    }
    len=ch.size();
    pri['&']=1;
    pri['|']=2;
    pri['-']=3;
    pri['<']=4;
}
bool MainWindow::iselement(string temp){//判断是否是变元
    if(temp=="!"||temp=="("||temp==")"||temp=="&"||temp=="|"||temp=="-"||temp=="<"||temp=="<->"||temp=="->"||temp==">")
        return 0;
    else
        return 1;
}
bool MainWindow::judge(){//判断该输入是否有错
    int num_of_bracket=0;//判断括号是否对应
    string pre,next,now;
    for(int i=0;i<len;i++){
        now.clear();
        pre.clear();
        next.clear();
        if(i-1>=0)
            pre+=ch[i-1];
        now+=ch[i];
        if(i+1<len)
            next+=ch[i+1];
        if(ch[i]=='<'&&ch[i+1]!='-'&&ch[i+2]!='>'){
            input.clear();
            input.sprintf("第%d个字符处有误。\n",(i+1));
            return 0;
        }
        else if(ch[i]=='-'&&ch[i+1]!='>'){
            input.clear();
            input.sprintf("第%d个字符处有误。\n",(i+1));
            return 0;
        }
        else if(ch[i]=='>'&&(!iselement(next)&&ch[i+1]!='('&&ch[i+1]!='!')){
            input.clear();
            input.sprintf("第%d个字符处有误。\n",(i+1));
            return 0;
        }
        else if(ch[i]=='!'&&(!iselement(next)&&ch[i+1]!='('&&ch[i+1]!='!')){
            input.clear();
            input.sprintf("第%d个字符处有误。\n",(i+1));
            return 0;
        }
        else if(ch[i]=='|'&&(!iselement(next)&&ch[i+1]!='('&&ch[i+1]!='!')){
            input.clear();
            input.sprintf("第%d个字符处有误。\n",(i+1));
            return 0;
        }
        else if(ch[i]=='&'&&(!iselement(next)&&ch[i+1]!='('&&ch[i+1]!='!')){
            input.clear();
            input.sprintf("第%d个字符处有误。\n",(i+1));
            return 0;
        }
        else if(iselement(now)&&(iselement(next)||ch[i+1]=='>'||ch[i+1]=='!')&&i!=len-1){
            input.clear();
            input.sprintf("第%d个字符处有误。\n",(i+1));
            return 0;
        }
        else if(ch[i]=='('&&(i==len-1||i<len-1&&!(iselement(next)||ch[i+1]=='('||ch[i+1]=='!'))){
            num_of_bracket++;
            input.clear();
            input.sprintf("第%d个字符处有误。\n",(i+1));
            return 0;
        }
        else if(ch[i]==')'&&i<len-1&&!(ch[i+1]=='<'||ch[i+1]=='-'||ch[i+1]=='|'||ch[i+1]=='&'||ch[i+1]==')')){
            num_of_bracket--;
            input.clear();
            input.sprintf("第%d个字符处有误。\n",(i+1));
            return 0;
        }

        if(ch[i]=='<'&&(i==0||(i>0&&!(iselement(pre)||ch[i-1]==')')))){
            input.clear();
            input.sprintf("第%d个字符处有误。\n",(i+1));
            return 0;
        }
        else if(ch[i]=='-'&&(i==0||(i>0&&!(iselement(pre)||ch[i-1]==')'||ch[i-1]=='<')))){
            input.clear();
            input.sprintf("第%d个字符处有误。\n",(i+1));
            return 0;
        }
        else if(ch[i]=='>'&&(i==0||(i>0&&ch[i-1]!='-'))){
            input.clear();
            input.sprintf("第%d个字符处有误。\n",(i+1));
            return 0;
        }
        else if(ch[i]=='!'&&(i>0&&(iselement(pre)||ch[i-1]=='<'||ch[i-1]=='-'||ch[i-1]==')'))){
            input.clear();
            input.sprintf("第%d个字符处有误。\n",(i+1));
            return 0;
        }
        else if(ch[i]=='|'&&(i==0||(i>0&&!(iselement(pre)||ch[i-1]==')')))){
            input.clear();
            input.sprintf("第%d个字符处有误。\n",(i+1));
            return 0;
        }
        else if(ch[i]=='&'&&(i==0||(i>0&&!(iselement(pre)||ch[i-1]==')')))){
            input.clear();
            input.sprintf("第%d个字符处有误。\n",(i+1));
            return 0;
        }
        else if(iselement(now)&&i>0&&(iselement(pre)||ch[i-1]=='<'||ch[i-1]=='-'||ch[i-1]==')')){
            input.clear();
            input.sprintf("第%d个字符处有误。\n",(i+1));
            return 0;
        }
        else if(ch[i]=='('&&i>0&&!(ch[i-1]=='('||ch[i-1]=='>'||ch[i-1]=='!'||ch[i-1]=='|'||ch[i-1]=='&')){
            input.clear();
            input.sprintf("第%d个字符处有误。\n",(i+1));
            return 0;
        }
        else if(ch[i]==')'&&(i==0||(i>0&&!(ch[i-1]==')'||iselement(pre))))){
            input.clear();
            input.sprintf("第%d个字符处有误。\n",(i+1));
            return 0;
        }
    }
    if(num_of_bracket!=0){

        input.clear();
        input.sprintf("左右括号数不匹配\n");
        return 0;
    }
    return 1;
}
string MainWindow::getstring(string str,int l,int r){//赋值一个字符串开始是str的l，到str的r
    string now;
    for(int i=l;i<=r;i++)
        now+=str[i];
    return now;
}
void MainWindow::getelement(){//将输入里的所有基础变元和结合变元放入queue中
    mp.clear();
    element.clear();
    while(!subscript.empty())
        subscript.pop();
    memset(id_of_parentheses,0,sizeof(id_of_parentheses));
    string now;
    for(int i=0;i<len;i++){
        if(ch[i]!='!'&&ch[i]!='('&&ch[i]!=')'&&ch[i]!='<'&&ch[i]!='-'&&ch[i]!='>'&&ch[i]!='&'&&ch[i]!='|'){
            now=ch[i];
            if(!mp[now]){
                element.push_back(now);
                mp[now]=element.size();
                num_of_basic++;
                num_of_element++;
            }
        }
    }
    for(int i=0;i<len;i++){
        if(ch[i]=='(')
            subscript.push(i);
        else if(ch[i]==')'){
            id_of_parentheses[i]=subscript.front();
            id_of_parentheses[subscript.front()]=i;
            now=getstring(ch,subscript.front()+1,i-1);
            if(ch[subscript.front()+1]=='('&&ch[i-1]==')'&&id_of_parentheses[i-1]==subscript.front()+1){
                subscript.pop();
                continue;
            }
            subscript.pop();
            if(!mp[now]){
                mp[now]=1;
                element.push_back(now);
                num_of_element++;
            }
        }
    }
    now=getstring(ch,0,ch.size()-1);
    element.push_back(now);
    num_of_element++;
}
int MainWindow::quit_parentheses(int i,string str){
    deque<char> operate;
    deque<int> argument;
    operate.clear();
    argument.clear();
    vector<char> sentence;
    int num=0,l,r;
    for(int j=0;j<str.size();j++){
        if(str[j]=='('){
            l=j;
            for(int k=j+1;k<str.size();k++){
                if(str[k]=='(')
                    num++;
                else if(str[k]==')'){
                    if(num!=0)
                        num--;
                    else{
                        j=k;
                        r=k;
                        string x;
                        x=getstring(str,l+1,r-1);
                        sentence.push_back((quit_parentheses(i,x)==0)?'0':'1');
                        break;
                    }
                }
            }
        }
        else
            sentence.push_back(str[j]);
    }
    for(int j=0;j<sentence.size();j++){
        char temp=sentence[j];
        if(temp!='('&&temp!=')'&&temp!='|'&&temp!='&'&&temp!='-'&&temp!='<'&&temp!='!'&&temp!='>'){//判断字符是否是运算符
            string comp;
            comp+=temp;
            if(sentence[j]=='1'||sentence[j]=='0')
                continue;
            if((i>>(mp[comp]-1))&1)
                sentence[j]='1';
            else
                sentence[j]='0';
        }
    }
    for(int j=0;j<sentence.size();j++){
        if(sentence[j]=='!'){
            sentence[j]=(sentence[j+1]=='0')?'1':'0';
            for(int k=j+1;k<sentence.size()-1;k++)
                sentence[k]=sentence[k+1];
            sentence.resize(sentence.size()-1);
        }
    }
    for(int j=0;j<sentence.size();j++){
        if(sentence[j]=='<'){
            for(int k=j+1;k<sentence.size()-2;k++)
                sentence[k]=sentence[k+2];
            sentence.resize(sentence.size()-2);
        }
        else if(sentence[j]=='-'){
            for(int k=j+1;k<sentence.size()-1;k++)
                sentence[k]=sentence[k+1];
            sentence.resize(sentence.size()-1);
        }
    }
    for(int j=0;j<sentence.size();j++){
        if(sentence[j]=='0'||sentence[j]=='1'){
            argument.push_back(sentence[j]-'0');
        }
        else{
            char temp=sentence[j];
            if(operate.empty()){
                operate.push_back(temp);
                continue;
            }
            if(pri[operate.back()]>pri[temp]){
                operate.push_back(temp);
                continue;
            }
            temp=operate.back();
            operate.pop_back();
            int num1,num2;
            num1=argument.back();
            argument.pop_back();
            num2=argument.back();
            argument.pop_back();
            if(temp=='|'){
                argument.push_back(num1|num2);
            }
            else if(temp=='&'){
                argument.push_back(num1&num2);
            }
            else if(temp=='-'){
                argument.push_back(num1|(!num2));
            }
            else if(temp=='<'){
                argument.push_back((!num1)&(!num2)|(num1&num2));
            }
            operate.push_back(temp);
        }
    }
    while(!operate.empty()){
        char temp;
        if(!operate.empty()){
            temp=operate.back();
            operate.pop_back();
        }
        else
            break;
        int num1,num2;
        if(!argument.empty()){
            num1=argument.back();
            argument.pop_back();
        }
        else
            break;
        if(!argument.empty()){
            num2=argument.back();
            argument.pop_back();
        }
        else
            break;
        if(temp=='|'){
            argument.push_back(num1|num2);
        }
        else if(temp=='&'){
            argument.push_back(num1&num2);
        }
        else if(temp=='-'){
            argument.push_back(num1|((num2)==0)?1:0);
        }
        else if(temp=='<'){
            argument.push_back(((num1==0)?1:0)&((num2==0)?1:0)|(num1&num2));
        }
    }
    return argument.back();
}
void MainWindow::print(){
    memset(matrix,0,sizeof(matrix));
    int temp=0;
    int j=0;
    while(temp<(1<<num_of_basic)){
        int TF=temp;
        for(int i=0;i<num_of_basic;i++){
            matrix[j][i]=TF&1;
            TF>>=1;
        }
        j++;
        temp++;
    }
    for(int i=0;i<(1<<num_of_basic);i++){
        matrix[i][num_of_element-1]=quit_parentheses(i,element[num_of_element-1]);
    }
    for(int i=0;i<num_of_basic;i++){
        input.clear();
        input=ui->textEdit->toPlainText();
        input+=QString::fromStdString(element[i]);
        input+="   ";
        ui->textEdit->setText(input);
    }
    input.clear();
    input=ui->textEdit->toPlainText();
    input+=QString::fromStdString(tempch);
    input+="\r\n";
    ui->textEdit->setText(input);
    for(int i=0;i<(1<<num_of_basic);i++){
        for(int j=0;j<num_of_basic;j++)
            if(matrix[i][j]==1){
                input.clear();
                input=ui->textEdit->toPlainText();
                input+="T   ";
                ui->textEdit->setText(input);
            }
            else{
                input.clear();
                input=ui->textEdit->toPlainText();
                input+="F   ";
                ui->textEdit->setText(input);
            }
        if(matrix[i][num_of_element-1]==1){
            input.clear();
            input=ui->textEdit->toPlainText();
            input+="T   ";
            ui->textEdit->setText(input);
        }
        else{
            input.clear();
            input=ui->textEdit->toPlainText();
            input+="F   ";
            ui->textEdit->setText(input);
        }
        input.clear();
        input=ui->textEdit->toPlainText();
        input+="\r\n";
        ui->textEdit->setText(input);
    }
    input.clear();
    input=ui->textEdit->toPlainText();
    input+="主析取范式：";
    int flag1=0;
    for(int j=0;j<1<<num_of_basic;j++){
        if(matrix[j][num_of_element-1]==1){
            if(flag1==0)
                flag1=1;
            else
                input+="|";
            int flag2=0;
            for(int k=0;k<num_of_basic;k++){
                if(flag2==0){
                    input+="(";
                    if((j>>k)&1)
                        input+=QString::fromStdString(element[k]);
                    else{
                        input+="!";
                        input+=QString::fromStdString(element[k]);
                    }
                    flag2=1;
                }
                else{
                    input+="&";
                    if((j>>k)&1)
                        input+=QString::fromStdString(element[k]);
                    else{
                        input+="!";
                        input+=QString::fromStdString(element[k]);
                    }
                }
            }
            input+=')';
        }
    }
    ui->textEdit->setText(input);
}
void MainWindow::on_pushButton_clicked()
{
    close();
}

void MainWindow::on_pushButton_open_sheet_clicked()
{
    input.clear();
    ui->textEdit->setText(input);
    input=ui->lineEdit->text();
    if(input.size()==0)
        return;
    /*a = new sheet;
    a->show();*/
    ch.clear();
    tempch.clear();
    tempch=input.toStdString();
    ch=input.toStdString();
    init();
    if(!judge()){
        ui->textEdit->setText(input);
    }
    else{
        getelement();
        print();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    input.clear();
    input=ui->lineEdit->text();
    input+="A";
    ui->lineEdit->setText(input);
}

void MainWindow::on_pushButton_3_clicked()
{
    input.clear();
    input=ui->lineEdit->text();
    input+="B";
    ui->lineEdit->setText(input);
}

void MainWindow::on_pushButton_4_clicked()
{
    input.clear();
    input=ui->lineEdit->text();
    input+="C";
    ui->lineEdit->setText(input);
}

void MainWindow::on_pushButton_5_clicked()
{
    input.clear();
    input=ui->lineEdit->text();
    input+="D";
    ui->lineEdit->setText(input);
}

void MainWindow::on_pushButton_6_clicked()
{
    input.clear();
    input=ui->lineEdit->text();
    input+="E";
    ui->lineEdit->setText(input);
}

void MainWindow::on_pushButton_7_clicked()
{
    input.clear();
    input=ui->lineEdit->text();
    input+="F";
    ui->lineEdit->setText(input);
}

void MainWindow::on_pushButton_8_clicked()
{
    input.clear();
    input=ui->lineEdit->text();
    input+="(";
    ui->lineEdit->setText(input);
}

void MainWindow::on_pushButton_9_clicked()
{
    input.clear();
    input=ui->lineEdit->text();
    input+=")";
    ui->lineEdit->setText(input);
}

void MainWindow::on_pushButton_10_clicked()
{
    input.clear();
    input=ui->lineEdit->text();
    input+="!";
    ui->lineEdit->setText(input);
}

void MainWindow::on_pushButton_11_clicked()
{
    input.clear();
    input=ui->lineEdit->text();
    input+="|";
    ui->lineEdit->setText(input);
}

void MainWindow::on_pushButton_12_clicked()
{
    input.clear();
    input=ui->lineEdit->text();
    input+="&";
    ui->lineEdit->setText(input);
}

void MainWindow::on_pushButton_13_clicked()
{
    input.clear();
    input=ui->lineEdit->text();
    input+="<->";
    ui->lineEdit->setText(input);
}

void MainWindow::on_pushButton_14_clicked()
{
    input.clear();
    input=ui->lineEdit->text();
    input+="->";
    ui->lineEdit->setText(input);
}

void MainWindow::on_pushButton_15_clicked()
{
    input.clear();
    input=ui->lineEdit->text();
    input.resize(input.size()-1);
    ui->lineEdit->setText(input);
}

void MainWindow::on_pushButton_16_clicked()
{
    input.clear();
    ui->lineEdit->setText(input);
    ui->textEdit->setText(input);
}

