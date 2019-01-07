#ifndef SHEET_H
#define SHEET_H

#include <QMainWindow>

namespace Ui {
class sheet;
}

class sheet : public QMainWindow
{
    Q_OBJECT

public:
    explicit sheet(QWidget *parent = 0);
    ~sheet();

private:
    Ui::sheet *ui;
};

#endif // SHEET_H
