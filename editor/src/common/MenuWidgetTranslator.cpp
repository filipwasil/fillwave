#include "MenuWidgetTranslator.h"

namespace common {
    MenuWidgetTranslator::MenuWidgetTranslator(QWidget *menuWidget) :
        mMenuWidget(menuWidget) {

    }

    void MenuWidgetTranslator::update() {
        if (!mMenuWidget) {
            return;
        }
        emit updateScene(mMenuWidget);
    }
}