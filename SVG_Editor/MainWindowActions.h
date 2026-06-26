#pragma once

#include <QList>
#include <QKeySequence>
#include <QToolBar>

#include <functional>
#include <optional>

class QAction;
class QMenu;
class QWidget;

struct ActionDescriptor {
    const char* id = "";
    std::optional<QKeySequence::StandardKey> shortcut;
    bool checkable = false;
    std::function<void(QAction&)> configure;
    std::function<void()> triggered;
};

struct MenuItemDescriptor {
    const char* id = "";
    bool separator = false;
    QMenu* submenu = nullptr;
    QAction* action = nullptr;
};

struct MenuDescriptor {
    QMenu* menu = nullptr;
    QList<MenuItemDescriptor> items;
};

struct ToolbarDescriptor {
    QToolBar* toolbar = nullptr;
    QList<MenuItemDescriptor> items;
};

void setupActionsFromDescriptors(QWidget* owner, const QList<ActionDescriptor>& descriptors,
                                 const std::function<void(const char*, QAction*)>& registerAction);

MenuItemDescriptor actionItem(QAction* action);
MenuItemDescriptor submenuItem(QMenu* submenu);
MenuItemDescriptor separatorItem();

void populateMenu(const MenuDescriptor& descriptor);
void populateToolbar(const ToolbarDescriptor& descriptor);
