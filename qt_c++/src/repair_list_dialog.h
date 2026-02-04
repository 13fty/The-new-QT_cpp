#ifndef REPAIR_LIST_DIALOG_H
#define REPAIR_LIST_DIALOG_H

#include <QDialog>
#include "dormitory_manager.h"

class QTableWidget;
class QPushButton;

class RepairListDialog : public QDialog
{
    Q_OBJECT
public:
    explicit RepairListDialog(DormitoryManager *dm, QWidget *parent = nullptr);
    ~RepairListDialog();

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void onMarkProcessed();
    void refreshTable();

private:
    DormitoryManager *m_dormManager;
    QTableWidget *m_table;
    QPushButton *m_markProcessedBtn;
};

#endif // REPAIR_LIST_DIALOG_H
