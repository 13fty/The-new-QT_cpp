#include "repair_request_dialog.h"
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QComboBox>
#include <QTextEdit>

// 损坏类型选项
static const QStringList damageTypeOptions = {
    "灯管损坏",
    "水龙头漏水",
    "门窗损坏",
    "床铺损坏",
    "桌椅损坏",
    "其他"
};

RepairRequestDialog::RepairRequestDialog(DormitoryManager *dm, int userId, QWidget *parent)
    : QDialog(parent), m_dormManager(dm), m_userId(userId)
{
    setWindowTitle("宿舍维修报修");
    setMinimumWidth(380);
    setupUi();
}

RepairRequestDialog::~RepairRequestDialog() {}

void RepairRequestDialog::setupUi()
{
    m_damageTypeCombo = new QComboBox(this);
    m_damageTypeCombo->addItems(damageTypeOptions);

    m_descriptionEdit = new QTextEdit(this);
    m_descriptionEdit->setPlaceholderText("可在此补充损坏情况说明（选填）");
    m_descriptionEdit->setMaximumHeight(100);

    QFormLayout *form = new QFormLayout();
    form->addRow("损坏类型：", m_damageTypeCombo);
    form->addRow("补充说明：", m_descriptionEdit);

    QDialogButtonBox *box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(box, &QDialogButtonBox::accepted, this, &RepairRequestDialog::accept);
    connect(box, &QDialogButtonBox::rejected, this, &RepairRequestDialog::reject);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addLayout(form);
    layout->addWidget(box);
}

void RepairRequestDialog::accept()
{
    QString damageType = m_damageTypeCombo->currentText().trimmed();
    QString description = m_descriptionEdit->toPlainText().trimmed();
    if (damageType.isEmpty()) {
        QMessageBox::warning(this, "提示", "请选择损坏类型。");
        return;
    }
    if (m_dormManager->addRepairRequest(m_userId, damageType, description)) {
        QMessageBox::information(this, "提交成功", "报修已提交，请等待维修处理。");
        QDialog::accept();
    } else {
        QMessageBox::warning(this, "提交失败", "您尚未分配宿舍，无法提交报修；或请稍后重试。");
    }
}
