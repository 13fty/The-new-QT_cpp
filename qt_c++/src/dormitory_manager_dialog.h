#ifndef DORMITORY_MANAGER_DIALOG_H
#define DORMITORY_MANAGER_DIALOG_H

#include <QDialog>
#include "dormitory_manager.h"

class QTableWidget;
class QPushButton;

class DormitoryManagerDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DormitoryManagerDialog(DormitoryManager *dm, QWidget *parent = nullptr);
    ~DormitoryManagerDialog();

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void onAdd();
    void onEdit();
    void onDelete();
    void onClose();

private:
    void refreshTable();

    DormitoryManager *m_dormManager;
    QTableWidget *m_table;
    QPushButton *m_addBtn;
    QPushButton *m_editBtn;
    QPushButton *m_deleteBtn;
};

#endif // DORMITORY_MANAGER_DIALOG_H
