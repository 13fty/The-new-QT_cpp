-- 宿舍维修报修表
CREATE TABLE IF NOT EXISTS repair_requests (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    dormitory_id INTEGER NOT NULL,
    damage_type VARCHAR(50) NOT NULL,
    description TEXT,
    status VARCHAR(20) DEFAULT '待处理',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(id),
    FOREIGN KEY (dormitory_id) REFERENCES dormitories(id)
);
