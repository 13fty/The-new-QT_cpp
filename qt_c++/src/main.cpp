#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QDir>
#include <QFile>

static QString getDatabasePath()
{
    // 优先使用项目根目录下的 database/database.db（从项目根运行）
    QString path = "database/database.db";
    if (QFile::exists(path))
        return QDir().absoluteFilePath(path);
    // 从可执行文件所在目录查找（如从 build 目录或 .app 内运行）
    QDir appDir(QCoreApplication::applicationDirPath());
    if (QFile::exists(appDir.absoluteFilePath("database/database.db")))
        return appDir.absoluteFilePath("database/database.db");
    return appDir.absoluteFilePath("../database/database.db");
}

bool initDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(getDatabasePath());

    if (!db.open()) {
        QMessageBox::critical(nullptr, "数据库错误",
            QString("无法打开数据库: %1").arg(db.lastError().text()));
        return false;
    }

    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    if (!initDatabase()) {
        return -1;
    }
    
    MainWindow w;
    w.show();
    
    return a.exec();
}



