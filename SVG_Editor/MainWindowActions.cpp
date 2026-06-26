#include "MainWindowActions.h"

#include <QAction>
#include <QMenu>

void setupActionsFromDescriptors(QWidget* owner, const QList<ActionDescriptor>& descriptors,
                                 const std::function<void(const char*, QAction*)>& registerAction) {
    for (const ActionDescriptor& descriptor : descriptors) {
        auto* action = new QAction(owner);
        action->setCheckable(descriptor.checkable);
        if (descriptor.shortcut.has_value()) {
            action->setShortcut(*descriptor.shortcut);
        }
        if (descriptor.configure) {
            descriptor.configure(*action);
        }
        if (descriptor.triggered) {
            QObject::connect(action, &QAction::triggered, owner, [triggered = descriptor.triggered]() { triggered(); });
        }
        registerAction(descriptor.id, action);
    }
}

MenuItemDescriptor actionItem(QAction* action) {
    MenuItemDescriptor descriptor;
    descriptor.action = action;
    return descriptor;
}

MenuItemDescriptor submenuItem(QMenu* submenu) {
    MenuItemDescriptor descriptor;
    descriptor.submenu = submenu;
    return descriptor;
}

MenuItemDescriptor separatorItem() {
    MenuItemDescriptor descriptor;
    descriptor.separator = true;
    return descriptor;
}

void populateMenu(const MenuDescriptor& descriptor) {
    if (descriptor.menu == nullptr) {
        return;
    }

    for (const MenuItemDescriptor& item : descriptor.items) {
        if (item.separator) {
            descriptor.menu->addSeparator();
        } else if (item.submenu != nullptr) {
            descriptor.menu->addMenu(item.submenu);
        } else if (item.action != nullptr) {
            descriptor.menu->addAction(item.action);
        }
    }
}

void populateToolbar(const ToolbarDescriptor& descriptor) {
    if (descriptor.toolbar == nullptr) {
        return;
    }

    for (const MenuItemDescriptor& item : descriptor.items) {
        if (item.separator) {
            descriptor.toolbar->addSeparator();
        } else if (item.action != nullptr) {
            descriptor.toolbar->addAction(item.action);
        }
    }
}
