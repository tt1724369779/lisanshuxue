#include "sheet.h"
#include "ui_sheet.h"

sheet::sheet(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sheet)
{
    ui->setupUi(this);
}

sheet::~sheet()
{
    delete ui;
}
