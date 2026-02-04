#ifndef REPAIR_REQUEST_DIALOG_H
#define REPAIR_REQUEST_DIALOG_H

#include <QDialog>
#include "dormitory_manager.h"

class QComboBox;
class QTextEdit;

class RepairRequestDialog : public QDialog
{
    Q_OBJECT
public:
    explicit RepairRequestDialog(DormitoryManager *dm, int userId, QWidget *parent = nullptr);
    ~RepairRequestDialog();

private slots:
    void accept() override;

private:
    void setupUi();

    DormitoryManager *m_dormManager;
    int m_userId;
    QComboBox *m_damageTypeCombo;
    QTextEdit *m_descriptionEdit;
};

#endif // REPAIR_REQUEST_DIALOG_H
