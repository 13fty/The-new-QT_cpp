#include "dormitory_manager_dialog.h"
#include "dormitory_form_dialog.h"
#include <QShowEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QHeaderView>
#include <QMessageBox>

DormitoryManagerDialog::DormitoryManagerDialog(DormitoryManager *dm, QWidget *parent)
    : QDialog(parent), m_dormManager(dm)
{
    setWindowTitle("宿舍管理");
    setMinimumSize(720, 480);
    resize(800, 520);

    m_table = new QTableWidget(this);
    m_table->setColumnCount(9);
    m_table->setHorizontalHeaderLabels(
        {"ID", "宿舍名称", "楼栋", "房间号", "容量", "性别", "当前人数", "作息类型", "接受不同专业"});
    m_table->horizontalHeader()->setStretchLastSection(true);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setSelectionMode(QAbstractItemView::SingleSelection);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->verticalHeader()->setVisible(false);

    m_addBtn = new QPushButton("添加宿舍", this);
    m_editBtn = new QPushButton("编辑宿舍", this);
    m_deleteBtn = new QPushButton("删除宿舍", this);
    QPushButton *closeBtn = new QPushButton("关闭", this);

    connect(m_addBtn, &QPushButton::clicked, this, &DormitoryManagerDialog::onAdd);
    connect(m_editBtn, &QPushButton::clicked, this, &DormitoryManagerDialog::onEdit);
    connect(m_deleteBtn, &QPushButton::clicked, this, &DormitoryManagerDialog::onDelete);
    connect(closeBtn, &QPushButton::clicked, this, &DormitoryManagerDialog::onClose);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(m_addBtn);
    btnLayout->addWidget(m_editBtn);
    btnLayout->addWidget(m_deleteBtn);
    btnLayout->addStretch();
    btnLayout->addWidget(closeBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_table);
    mainLayout->addLayout(btnLayout);
}

DormitoryManagerDialog::~DormitoryManagerDialog() {}

void DormitoryManagerDialog::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);
    refreshTable();
}

void DormitoryManagerDialog::refreshTable()
{
    m_table->setRowCount(0);
    QList<Dormitory> list = m_dormManager->getDormitories();
    for (const Dormitory &d : list) {
        int row = m_table->rowCount();
        m_table->insertRow(row);
        m_table->setItem(row, 0, new QTableWidgetItem(QString::number(d.id)));
        m_table->setItem(row, 1, new QTableWidgetItem(d.name));
        m_table->setItem(row, 2, new QTableWidgetItem(d.building));
        m_table->setItem(row, 3, new QTableWidgetItem(d.roomNumber));
        m_table->setItem(row, 4, new QTableWidgetItem(QString::number(d.capacity)));
        m_table->setItem(row, 5, new QTableWidgetItem(d.gender));
        m_table->setItem(row, 6, new QTableWidgetItem(QString::number(d.currentCount)));
        m_table->setItem(row, 7, new QTableWidgetItem(d.scheduleType));
        m_table->setItem(row, 8, new QTableWidgetItem(d.acceptDifferentMajor ? "是" : "否"));
    }
    m_table->hideColumn(0);
}

void DormitoryManagerDialog::onAdd()
{
    DormitoryFormDialog dlg(m_dormManager, this, -1);
    if (dlg.exec() == QDialog::Accepted)
        refreshTable();
}

void DormitoryManagerDialog::onEdit()
{
    int row = m_table->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "提示", "请先选择要编辑的宿舍。");
        return;
    }
    int dormId = m_table->item(row, 0)->text().toInt();
    DormitoryFormDialog dlg(m_dormManager, this, dormId);
    if (dlg.exec() == QDialog::Accepted)
        refreshTable();
}

void DormitoryManagerDialog::onDelete()
{
    int row = m_table->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "提示", "请先选择要删除的宿舍。");
        return;
    }
    int dormId = m_table->item(row, 0)->text().toInt();
    QString name = m_table->item(row, 1)->text();
    if (QMessageBox::question(this, "确认删除",
            QString("确定要删除宿舍「%1」吗？").arg(name),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No) != QMessageBox::Yes)
        return;
    if (m_dormManager->deleteDormitory(dormId)) {
        QMessageBox::information(this, "成功", "宿舍已删除。");
        refreshTable();
    } else {
        QMessageBox::warning(this, "失败", "删除失败，可能该宿舍已有入住学生。");
    }
}

void DormitoryManagerDialog::onClose()
{
    accept();
}
