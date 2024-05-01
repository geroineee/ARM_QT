#ifndef USERCODEWINDOW_H
#define USERCODEWINDOW_H

#include <QDialog>

namespace Ui {
class usercodewindow;
}

class usercodewindow : public QDialog
{
    Q_OBJECT

public:
    explicit usercodewindow(QWidget *parent = nullptr, QString text_code = "");
    ~usercodewindow();

private:
    Ui::usercodewindow *ui;
};

#endif // USERCODEWINDOW_H
