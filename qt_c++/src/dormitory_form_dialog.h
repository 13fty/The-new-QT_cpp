#ifndef DORMITORY_FORM_DIALOG_H
#define DORMITORY_FORM_DIALOG_H

#include <QDialog>
#include "dormitory_manager.h"

class QLineEdit;
class QComboBox;
class QCheckBox;

class DormitoryFormDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DormitoryFormDialog(DormitoryManager *dm, QWidget *parent = nullptr, int editDormId = -1);
    ~DormitoryFormDialog();

private slots:
    void accept() override;

private:
    void setupUi();
    void loadDormitory(int dormId);

    DormitoryManager *m_dormManager;
    int m_editDormId;

    QLineEdit *m_nameEdit;
    QLineEdit *m_buildingEdit;
    QLineEdit *m_roomEdit;
    QComboBox *m_capacityCombo;
    QComboBox *m_genderCombo;
    QComboBox *m_scheduleCombo;
    QCheckBox *m_acceptDifferentMajorCheck;
};

#endif // DORMITORY_FORM_DIALOG_H
