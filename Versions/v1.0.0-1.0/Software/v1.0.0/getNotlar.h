#ifndef GETNOTLAR_H
#define GETNOTLAR_H

#include <QDialog>

namespace Ui {
class notlar;
}

class notlar : public QDialog
{
    Q_OBJECT

public:
    explicit notlar(QWidget *parent = nullptr);
    ~notlar();

private:
    Ui::notlar *ui;
};

#endif // GETNOTLAR_H
