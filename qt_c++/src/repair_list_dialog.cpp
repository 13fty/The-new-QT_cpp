#include "repair_list_dialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QHeaderView>
#include <QMessageBox>
#include <QShowEvent>

RepairListDialog::RepairListDialog(DormitoryManager *dm, QWidget *parent)
    : QDialog(parent), m_dormManager(dm)
{
    setWindowTitle("宿舍维修管理");
    setMinimumSize(720, 400);
    resize(800, 450);

    m_table = new QTableWidget(this);
    m_table->setColumnCount(10);
    m_table->setHorizontalHeaderLabels(
        {"ID", "宿舍", "楼栋", "房间号", "报修人", "学号", "损坏类型", "补充说明", "状态", "提交时间"});
    m_table->horizontalHeader()->setStretchLastSection(true);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setSelectionMode(QAbstractItemView::SingleSelection);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->verticalHeader()->setVisible(false);

    m_markProcessedBtn = new QPushButton("标记为已处理", this);
    QPushButton *closeBtn = new QPushButton("关闭", this);
    QPushButton *refreshBtn = new QPushButton("刷新", this);

    connect(m_markProcessedBtn, &QPushButton::clicked, this, &RepairListDialog::onMarkProcessed);
    connect(closeBtn, &QPushButton::clicked, this, &RepairListDialog::accept);
    connect(refreshBtn, &QPushButton::clicked, this, &RepairListDialog::refreshTable);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(m_markProcessedBtn);
    btnLayout->addWidget(refreshBtn);
    btnLayout->addStretch();
    btnLayout->addWidget(closeBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_table);
    mainLayout->addLayout(btnLayout);
}

RepairListDialog::~RepairListDialog() {}

void RepairListDialog::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);
    refreshTable();
}

void RepairListDialog::refreshTable()
{
    m_table->setRowCount(0);
    QList<QMap<QString, QVariant>> list = m_dormManager->getRepairRequestsForAdmin();
    for (const QMap<QString, QVariant> &row : list) {
        int r = m_table->rowCount();
        m_table->insertRow(r);
        m_table->setItem(r, 0, new QTableWidgetItem(row["id"].toString()));
        m_table->setItem(r, 1, new QTableWidgetItem(row["dorm_name"].toString()));
        m_table->setItem(r, 2, new QTableWidgetItem(row["building"].toString()));
        m_table->setItem(r, 3, new QTableWidgetItem(row["room_number"].toString()));
        m_table->setItem(r, 4, new QTableWidgetItem(row["user_name"].toString()));
        m_table->setItem(r, 5, new QTableWidgetItem(row["student_id"].toString()));
        m_table->setItem(r, 6, new QTableWidgetItem(row["damage_type"].toString()));
        m_table->setItem(r, 7, new QTableWidgetItem(row["description"].toString()));
        m_table->setItem(r, 8, new QTableWidgetItem(row["status"].toString()));
        m_table->setItem(r, 9, new QTableWidgetItem(row["created_at"].toDateTime().toString("yyyy-MM-dd hh:mm")));
    }
    m_table->hideColumn(0);
}

void RepairListDialog::onMarkProcessed()
{
    int row = m_table->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "提示", "请先选择一条报修记录。");
        return;
    }
    int repairId = m_table->item(row, 0)->text().toInt();
    if (m_dormManager->setRepairStatus(repairId, "已处理")) {
        QMessageBox::information(this, "成功", "已标记为已处理。");
        refreshTable();
    } else {
        QMessageBox::warning(this, "失败", "操作失败，请重试。");
    }
}
