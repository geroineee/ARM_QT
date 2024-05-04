#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {class testwindow;}

class testwindow : public QDialog
{
    Q_OBJECT

public:
    explicit testwindow(QWidget *parent = nullptr);
    ~testwindow();

private slots:
    void on_button_cancel_clicked();
    void on_button_apply_clicked();

signals:
    void sendQuery(QString);

private:
    Ui::testwindow *ui;

protected:
    void closeEvent(QCloseEvent *evnt);
};

#endif // TESTWINDOW_H
