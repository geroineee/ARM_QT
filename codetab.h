#ifndef CODETAB_H
#define CODETAB_H

#include <QWidget>

namespace Ui
{
class CodeTab;
}
class CodeTab : public QWidget
{
    Q_OBJECT

public:
    explicit CodeTab(QWidget *parent = nullptr);
    ~CodeTab();

private:
    Ui::CodeTab *ui;
};

#endif // CODETAB_H
