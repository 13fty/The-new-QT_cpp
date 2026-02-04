#include "dormitory_form_dialog.h"
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QMessageBox>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QVBoxLayout>

DormitoryFormDialog::DormitoryFormDialog(DormitoryManager *dm, QWidget *parent, int editDormId)
    : QDialog(parent), m_dormManager(dm), m_editDormId(editDormId)
{
    setWindowTitle(editDormId < 0 ? "添加宿舍" : "编辑宿舍");
    setMinimumWidth(400);
    setupUi();
    if (editDormId >= 0)
        loadDormitory(editDormId);
}

DormitoryFormDialog::~DormitoryFormDialog() {}

void DormitoryFormDialog::setupUi()
{
    m_nameEdit = new QLineEdit(this);
    m_nameEdit->setPlaceholderText("请输入宿舍名称");
    m_buildingEdit = new QLineEdit(this);
    m_buildingEdit->setPlaceholderText("请输入楼栋号");
    m_roomEdit = new QLineEdit(this);
    m_roomEdit->setPlaceholderText("请输入房间号");

    m_capacityCombo = new QComboBox(this);
    m_capacityCombo->addItems({"4人", "6人", "8人"});
    m_genderCombo = new QComboBox(this);
    m_genderCombo->addItems({"男", "女"});
    m_scheduleCombo = new QComboBox(this);
    m_scheduleCombo->addItems({"早", "晚"});

    m_acceptDifferentMajorCheck = new QCheckBox("接受不同专业", this);

    QFormLayout *form = new QFormLayout();
    form->addRow("宿舍名称：", m_nameEdit);
    form->addRow("楼栋：", m_buildingEdit);
    form->addRow("房间号：", m_roomEdit);
    form->addRow("容量：", m_capacityCombo);
    form->addRow("性别：", m_genderCombo);
    form->addRow("作息类型：", m_scheduleCombo);
    form->addRow("", m_acceptDifferentMajorCheck);

    QDialogButtonBox *box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(box, &QDialogButtonBox::accepted, this, &DormitoryFormDialog::accept);
    connect(box, &QDialogButtonBox::rejected, this, &DormitoryFormDialog::reject);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addLayout(form);
    layout->addWidget(box);
}

void DormitoryFormDialog::loadDormitory(int dormId)
{
    QList<Dormitory> list = m_dormManager->getDormitories();
    for (const Dormitory &d : list) {
        if (d.id == dormId) {
            m_nameEdit->setText(d.name);
            m_buildingEdit->setText(d.building);
            m_roomEdit->setText(d.roomNumber);
            int capIndex = -1;
            if (d.capacity == 4) capIndex = 0;
            else if (d.capacity == 6) capIndex = 1;
            else if (d.capacity == 8) capIndex = 2;
            if (capIndex >= 0) m_capacityCombo->setCurrentIndex(capIndex);
            m_genderCombo->setCurrentText(d.gender);
            m_scheduleCombo->setCurrentText(d.scheduleType);
            m_acceptDifferentMajorCheck->setChecked(d.acceptDifferentMajor);
            break;
        }
    }
}

void DormitoryFormDialog::accept()
{
    QString name = m_nameEdit->text().trimmed();
    QString building = m_buildingEdit->text().trimmed();
    QString roomNumber = m_roomEdit->text().trimmed();
    if (name.isEmpty() || building.isEmpty() || roomNumber.isEmpty()) {
        QMessageBox::warning(this, "提示", "请填写宿舍名称、楼栋和房间号。");
        return;
    }
    int capacity = m_capacityCombo->currentText().remove("人").toInt();
    QString gender = m_genderCombo->currentText();
    QString scheduleType = m_scheduleCombo->currentText();
    bool acceptDifferentMajor = m_acceptDifferentMajorCheck->isChecked();

    bool ok = false;
    if (m_editDormId < 0) {
        ok = m_dormManager->addDormitory(name, building, roomNumber, capacity, gender, scheduleType, acceptDifferentMajor);
        if (ok) QMessageBox::information(this, "成功", "宿舍已添加。");
    } else {
        ok = m_dormManager->updateDormitory(m_editDormId, name, building, roomNumber, capacity, gender, scheduleType, acceptDifferentMajor);
        if (ok) QMessageBox::information(this, "成功", "宿舍信息已更新。");
    }
    if (!ok) {
        QMessageBox::warning(this, "失败", "操作失败，请检查楼栋与房间号是否重复。");
        return;
    }
    QDialog::accept();
}
