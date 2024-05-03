#ifndef TEXTWINDOW_H
#define TEXTWINDOW_H

#include <QDialog>
#include <QResizeEvent>

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

protected:
    void resizeEvent(QResizeEvent *event);
};



#endif // TEXTWINDOW_H
