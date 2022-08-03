#ifndef SERVERSERVISDIALOG_H
#define SERVERSERVISDIALOG_H

#include <QDialog>

namespace Ui {
class ServerServisDialog;
}

class ServerServisDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerServisDialog(QWidget *parent = nullptr);
    ~ServerServisDialog();

private:
    Ui::ServerServisDialog *ui;
};

#endif // SERVERSERVISDIALOG_H
