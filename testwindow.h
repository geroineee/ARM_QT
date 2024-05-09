#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {class testwindow;}

class testwindow : public QDialog
{
    Q_OBJECT

public:
    void setRedactorMode(bool);

    explicit testwindow(QWidget *parent = nullptr);
    ~testwindow();

private slots:
    void on_button_cancel_clicked();
    void on_button_add_variant_clicked();
    void on_button_back_to_edie_test_clicked();

signals:
    void sendQuery(QString);

private:
    bool isRedactor; //  определяет, является ли окно редактором, либо окном добавления

    Ui::testwindow *ui;

protected:
    void closeEvent(QCloseEvent *evnt);
};

#endif // TESTWINDOW_H
