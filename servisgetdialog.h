#ifndef SERVISGETDIALOG_H
#define SERVISGETDIALOG_H

#include <QDialog>

namespace Ui {
class ServisGetDialog;
}

class ServisGetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServisGetDialog(QWidget *parent = nullptr);
    ~ServisGetDialog();

private:
    Ui::ServisGetDialog *ui;
};

#endif // SERVISGETDIALOG_H
