#ifndef INFORMATIONMUSTERIDIALOG_H
#define INFORMATIONMUSTERIDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QtWidgets>

#include <QStringListModel>
class ListModel: public QStringListModel {

  public:
    using QStringListModel::QStringListModel;
    mutable QString draggedData = "";

  protected:
    // for drag site

    // encodes dragged items (different from default).
    virtual QMimeData* mimeData(const QModelIndexList& qMIndices) const override;

    // for drop site

    // returns which kind of drop actions are supported.
    virtual Qt::DropActions supportedDropActions() const override
    {
      return Qt::MoveAction;
    }

    // checks whether certain dragged MIME data is droppable.
    virtual bool canDropMimeData(
      const QMimeData* pQMimeData, // dragged data
      Qt::DropAction action, // not evaluated
      int row, // not evaluated
      int column, // uninteresting for lists (but relevant for tables and trees)
      const QModelIndex& qMIndex) // uninteresting for lists (but relevant for trees)
      const override
    {
      return pQMimeData->hasText();
    }

    // drops dragged MIME data into model.
    virtual bool dropMimeData(
      const QMimeData* pQMimeData, // dropped data
      Qt::DropAction action, // not evaluated
      int row, // where to insert
      int column, // uninteresting for lists (but relevant for tables and trees)
      const QModelIndex& qMIndex) // uninteresting for lists (but relevant for trees)
      override;
};

namespace Ui {
class InformationMusteriDialog;
}

class InformationMusteriDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InformationMusteriDialog(QWidget *parent = nullptr);
    ~InformationMusteriDialog();

    QString username;
public slots:
    void initialize(QSqlDatabase d, QString s, QString username);
protected:
    ListModel* l;
private slots:

    void setLog(QString log);
    void fillListViews();

    void changes();

    void updateChangesMusteri();
    void updateChangesToplam();

    void on_filter_selectionChanged();
    void on_filter_textChanged(const QString &arg1);

    void listViewMusteriChanged();
    void listViewToplamChanged();

private:
    Ui::InformationMusteriDialog *ui;

    QSqlDatabase database;

    QString seriNo;

    ListModel* toplam = new ListModel();
    ListModel* musteri = new ListModel();

};

#endif // INFORMATIONMUSTERIDIALOG_H
