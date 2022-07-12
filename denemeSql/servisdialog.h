#ifndef SERVISDIALOG_H
#define SERVISDIALOG_H

#include <QDialog>

namespace Ui {
class ServisDialog;
}

class ServisDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServisDialog(QWidget *parent = nullptr);
    ~ServisDialog();

private:
    Ui::ServisDialog *ui;
};

#endif // SERVISDIALOG_H
