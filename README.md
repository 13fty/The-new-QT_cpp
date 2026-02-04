# 宿舍管理系统 (DormManager)

[![Qt](https://img.shields.io/badge/Qt-5.15.16-green.svg)](https://www.qt.io/)
[![Platform](https://img.shields.io/badge/Platform-macOS-blue.svg)](https://www.apple.com/macos/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

一个基于Qt C++开发的智能宿舍管理系统，采用贪心算法进行最优宿舍分配。

## ✨ 功能特性

### 用户管理
- 🔐 **身份认证** - 学生注册登录系统，支持密码加密存储
- 👥 **权限控制** - 管理员与普通用户角色分离
- 📋 **用户信息** - 管理学生基本信息（ID、姓名、性别、专业等）

### 宿舍管理（管理员功能）
- 🏠 **宿舍维护** - 增删改查宿舍信息
- 🛏️ **床位管理** - 管理每个宿舍的床位配置和占用状态
- 📊 **分配管理** - 查看宿舍分配情况和统计信息

### 智能分配系统
- 🤖 **智能匹配** - 基于贪心算法的多维度宿舍分配
- 🎯 **批量分配** - 支持一键为所有未分配学生分配宿舍
- 📈 **匹配分析** - 提供匹配分数和匹配率统计

### 偏好设置
- ⚙️ **多维偏好** - 支持容量、性别、作息、专业、爱好等多维度偏好设置
- 🌙 **作息类型** - 支持早起型、夜猫型等作息偏好
- 👥 **社交偏好** - 支持安静型、社交型等性格偏好

### 消息系统
- 💬 **实时消息** - 用户间实时消息通信
- 📬 **消息管理** - 查看、标记已读、回复消息
- 🔔 **消息提醒** - 实时消息提醒和未读计数

### 维修管理
- 🔧 **报修系统** - 学生可以报告宿舍维修问题
- 📋 **请求列表** - 管理员查看和处理维修请求
- ✅ **状态跟踪** - 跟踪维修请求的处理状态

## 🚀 快速开始

### 环境要求

- macOS 10.13 或更高版本
- Qt 5.15.16 或兼容版本
- Xcode 命令行工具

### 安装依赖

```bash
# 安装Qt5
brew install qt@5

# 安装Xcode命令行工具（如果未安装）
xcode-select --install
```

### 编译运行

```bash
# 克隆项目
git clone https://github.com/13fty/DormManager.git
cd DormManager

# 编译并运行
make && ./DormManager.app/Contents/MacOS/DormManager
```

### 管理员账号

- **用户名**: admin123
- **密码**: 050715

## 📁 项目结构

```
DormManager/
├── src/                                  # 源代码目录
│   ├── main.cpp                         # 程序入口
│   ├── mainwindow.h/cpp                 # 主窗口（登录、注册、消息界面）
│   ├── dormitory_manager.h/cpp          # 核心业务逻辑层
│   ├── dormitory_manager_dialog.h/cpp   # 宿舍管理对话框
│   ├── dormitory_form_dialog.h/cpp      # 宿舍编辑/添加表单
│   ├── repair_list_dialog.h/cpp         # 维修请求列表对话框
│   ├── repair_request_dialog.h/cpp      # 维修请求报修对话框
│   ├── mainwindow.ui                    # Qt Designer UI文件
│   └── mainwindow.ui.backup             # UI备份文件
├── resources/                            # 资源文件
│   ├── icons/                           # 图标文件
│   ├── image/                           # 图片文件
│   └── icons.qrc                        # 资源文件配置
├── database/                             # 数据库相关
│   ├── database.sql                     # 初始数据库结构
│   ├── add_dormitories.sql              # 添加示例宿舍脚本
│   ├── repair_requests.sql              # 维修请求相关脚本
│   ├── smart_assignment.sql             # 智能分配脚本
│   ├── enhance_preferences.sql          # 增强偏好设置脚本
│   ├── redesign_dormitories.sql         # 重新设计宿舍脚本
│   ├── update_database.sql              # 数据库更新脚本
│   └── update_dormitory_gender.sql      # 宿舍性别更新脚本
├── docs/                                 # 文档
│   └── Remind.md                        # 详细说明文档
├── build.sh                             # 自动构建脚本（macOS兼容）
├── DormManager.pro                      # Qt项目文件
├── Makefile                             # Make编译配置
└── DormManager.app/                     # 编译输出的macOS应用程序
    └── Contents/
        ├── MacOS/
        │   └── DormManager              # 可执行文件
        ├── Resources/
        └── Info.plist
```

## 🏗️ 系统架构

### 核心架构设计

系统采用 **分层架构** 模式，分为以下几层：

#### 1. **表现层 (Presentation Layer)**
- `MainWindow` - 主窗口，提供登录、注册、消息系统等UI界面
- `DormitoryManagerDialog` - 宿舍管理对话框
- `DormitoryFormDialog` - 宿舍表单编辑/添加
- `RepairListDialog` - 维修请求列表
- `RepairRequestDialog` - 维修报修对话框

#### 2. **业务逻辑层 (Business Logic Layer)**
- `DormitoryManager` - 核心业务逻辑类，处理：
  - 智能宿舍分配
  - 用户偏好管理
  - 宿舍和床位管理
  - 消息系统
  - 维修请求处理

#### 3. **数据访问层 (Data Access Layer)**
- SQLite数据库
- Qt SQL模块进行数据库操作

### 主要类和结构体

#### DormitoryManager 类
核心业务逻辑类，提供以下主要功能：
- **宿舍管理**: `addDormitory()`, `updateDormitory()`, `deleteDormitory()`
- **分配算法**: `assignDormitory()`, `findBestMatch()`, `batchAssignDormitories()`
- **用户偏好**: `saveUserPreferences()`, `getUserPreferences()`
- **消息系统**: `sendMessage()`, `getMessages()`
- **维修管理**: `addRepairRequest()`, `getRepairRequestsForAdmin()`

#### 关键数据结构
```cpp
// 宿舍信息
struct Dormitory {
    int id;
    QString name;              // 宿舍名称
    QString building;          // 建筑
    QString roomNumber;        // 房间号
    int capacity;              // 容量
    int currentCount;          // 当前人数
    QString gender;            // 性别
    QString scheduleType;      // 作息类型
    bool acceptDifferentMajor; // 是否接受不同专业
};

// 学生偏好
struct StudentPreference {
    int userId;
    int preferCapacity;        // 偏好容量
    QString scheduleType;      // 作息偏好
    bool preferSameMajor;      // 是否偏好同专业
    bool preferSameGender;     // 是否偏好同性别
    bool isEarlyBird;          // 早起型
    bool isNightOwl;           // 夜猫型
    bool isQuiet;              // 安静型
    bool isSocial;             // 社交型
    QString hobbies;           // 爱好
    QString specialNeeds;      // 特殊需求
};

// 分配结果
struct AssignmentResult {
    int userId;
    int dormitoryId;
    int bedId;
    QString dormitoryName;
    int bedNumber;
    bool isUpper;
    int matchScore;            // 匹配分数
};
```

## 🧠 智能分配算法

### 贪心分配算法

系统采用贪心算法进行宿舍分配，每次选择分数最高的学生-床位对进行分配：

- **容量匹配权重**: 100分（完全匹配）/ 1分（不匹配）
- **作息匹配权重**: 8分（匹配）/ 3分（不匹配）
- **性别匹配权重**: 6分（匹配）/ 2分（不匹配）
- **宿舍状态权重**: 4分（空宿舍优先）
- **专业匹配权重**: 3分（同专业优先）

### 测试结果

- 容量匹配率: 90.7%
- 性别匹配率: 100.0%
- 作息匹配率: 90.7%
- 综合匹配率: 84.8%

## 🛠️ 开发

### 详细编译步骤

**方式一：使用脚本（推荐，自动处理 macOS 26/Xcode 兼容）**

```bash
chmod +x build.sh
./build.sh
./DormManager.app/Contents/MacOS/DormManager
```

**方式二：手动编译**

```bash
# 1. 生成 Makefile
qmake DormManager.pro CONFIG+=sdk_no_version_check

# 2. （可选）若出现 ld: framework 'AGL' not found，执行一次：
sed -i '' 's/ -framework AGL//g' Makefile

# 3. 编译项目
make

# 4. 运行程序（需在项目根目录执行，以便找到 database/database.db）
./DormManager.app/Contents/MacOS/DormManager
```

### 清理编译文件

```bash
# 清理所有编译生成的文件
make clean

# 或者删除所有生成的文件
rm -rf *.o moc_* ui_* DormManager.app
```

## 📚 代码模块说明

### 主要模块文件

| 文件 | 说明 |
|------|------|
| `main.cpp` | 程序入口，初始化数据库连接 |
| `mainwindow.h/cpp` | 主窗口，包含登录、注册、消息、宿舍分配等界面 |
| `dormitory_manager.h/cpp` | 核心业务逻辑，处理分配、偏好、消息等 |
| `dormitory_manager_dialog.h/cpp` | 宿舍列表管理对话框 |
| `dormitory_form_dialog.h/cpp` | 宿舍添加/编辑表单对话框 |
| `repair_request_dialog.h/cpp` | 维修报修对话框 |
| `repair_list_dialog.h/cpp` | 维修请求列表对话框 |

### 类之间的关系

```
MainWindow (UI主类)
    ├── 包含 DormitoryManager (业务逻辑)
    ├── 创建 DormitoryManagerDialog
    ├── 创建 DormitoryFormDialog
    ├── 创建 RepairRequestDialog
    └── 创建 RepairListDialog

DormitoryManager (业务逻辑)
    ├── 管理 Dormitory (宿舍)
    ├── 管理 StudentPreference (学生偏好)
    ├── 管理 AssignmentResult (分配结果)
    └── 与 SQLite 数据库交互
```

## 📊 数据库操作

### 数据库初始化

系统使用 SQLite 数据库，主要表结构：

- **users** - 用户表（学生和管理员）
- **dormitories** - 宿舍表
- **beds** - 床位表
- **assignments** - 宿舍分配记录表
- **student_preferences** - 学生偏好表
- **messages** - 消息表
- **repair_requests** - 维修请求表

### 常用数据库操作

#### 清空用户数据并重置宿舍

```sql
-- 清空所有分配和偏好信息
DELETE FROM assignments;
DELETE FROM student_preferences;
DELETE FROM messages;
DELETE FROM users WHERE id > 1; -- 保留admin账户

-- 重置宿舍和床位状态
UPDATE beds SET is_occupied = 0;
UPDATE dormitories SET current_count = 0;
```

#### 设置宿舍性别（男女交替）

```sql
UPDATE dormitories SET gender = CASE WHEN id % 2 = 0 THEN '男' ELSE '女' END;
```

#### 查看宿舍分配情况

```sql
SELECT d.name, d.capacity, d.current_count, 
       COUNT(a.id) as assigned_count
FROM dormitories d
LEFT JOIN assignments a ON d.id = a.dormitory_id
GROUP BY d.id;
```

#### 批量插入示例宿舍

参考 `database/` 目录下的 SQL 脚本文件，如：
- `add_dormitories.sql` - 添加示例宿舍
- `enhance_preferences.sql` - 增强偏好设置
- `smart_assignment.sql` - 智能分配配置

## ⚠️ 常见问题

### 编译问题

#### 问题：`ld: framework 'AGL' not found`
**解决方案**：运行自动修复
```bash
sed -i '' 's/ -framework AGL//g' Makefile
make
```

#### 问题：找不到 database.db
**解决方案**：确保从项目根目录运行程序
```bash
cd /path/to/DormManager
./DormManager.app/Contents/MacOS/DormManager
```

#### 问题：Qt not found
**解决方案**：确保已安装Qt
```bash
brew install qt@5
# 并确保 qmake 在 PATH 中
export PATH="/usr/local/opt/qt@5/bin:$PATH"
```

### 运行问题

#### 数据库初始化失败
- 检查 `database/database.db` 是否存在
- 检查文件权限：`chmod 644 database/database.db`
- 重新运行初始化 SQL 脚本

#### 管理员登录失败
- 检查默认账户是否存在：`admin123 / 050715`
- 查看数据库中的 users 表是否有数据

## 🧪 测试

### 测试数据

系统提供默认管理员账户用于测试：
- **用户名**: admin123
- **密码**: 050715

### 功能测试清单

- [ ] **用户认证** - 注册新账户、登录、密码验证
- [ ] **宿舍管理** - 新增、编辑、删除宿舍
- [ ] **智能分配** - 单个学生分配、批量分配、匹配分数计算
- [ ] **偏好设置** - 保存和读取用户偏好
- [ ] **消息系统** - 发送消息、接收消息、标记已读
- [ ] **维修管理** - 报修、查看、标记完成

### 性能指标

根据测试数据统计：
- **容量匹配率**: 90.7%
- **性别匹配率**: 100.0%
- **作息匹配率**: 90.7%
- **综合匹配率**: 84.8%

## 🤝 贡献

欢迎提交Issue和Pull Request来改进这个项目！

1. Fork 这个项目
2. 创建你的特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交你的更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 打开一个 Pull Request

## 📄 许可证

本项目采用 MIT 许可证 - 查看 [LICENSE](LICENSE) 文件了解详情。

## 📞 联系方式

如有问题或建议，请通过以下方式联系：

- 提交 [Issue](https://github.com/13fty/DormManager/issues)
- 发送邮件至: hqq916674@gmail.com

---

⭐ 如果这个项目对你有帮助，请给它一个星标！ 
