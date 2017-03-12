#pragma once

#include <QWidget>

namespace common {
    class MenuWidgetTranslator : public QObject {
    Q_OBJECT
    public:
        MenuWidgetTranslator(QWidget *menuWidget);

    public slots:

        void update();

    signals:

        void updateScene(QWidget *menuElement);

    private:
        QWidget *mMenuWidget;
    };
}
