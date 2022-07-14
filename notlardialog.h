#ifndef NOTLARDIALOG_H
#define NOTLARDIALOG_H

#include <QDialog>

namespace Ui {
class notlarDialog;
}

class notlarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit notlarDialog(QWidget *parent = nullptr);
    ~notlarDialog();
public slots:
    void initialize(QString s);
private:
    Ui::notlarDialog *ui;

};

#endif // NOTLARDIALOG_H
