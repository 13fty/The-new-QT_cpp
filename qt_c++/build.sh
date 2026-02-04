#!/bin/bash
# 宿舍管理系统 - 一键编译脚本
# 在 macOS 26 / 新 Xcode 下会自动移除已废弃的 AGL 框架引用，避免链接错误
set -e
cd "$(dirname "$0")"
rm -f .qmake.stash
qmake DormManager.pro CONFIG+=sdk_no_version_check
# 新 SDK 中 AGL 已移除，从 Makefile 中去掉对 AGL 的链接
sed -i '' 's/ -framework AGL//g' Makefile 2>/dev/null || true
sed -i '' 's|-I.*AGL.framework/Headers/||g' Makefile 2>/dev/null || true
make
echo ""
echo "编译完成。运行: ./DormManager.app/Contents/MacOS/DormManager"
