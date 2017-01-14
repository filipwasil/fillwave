//
// Created by filip on 25.04.16.
//

#ifndef FILLWAVE_QT_EXAMPLE_MAINWIDGET_H
#define FILLWAVE_QT_EXAMPLE_MAINWIDGET_H
#include <QWidget>

class QPushButton;
class Renderer;
class Panel;

class MainWidget : public QWidget
{
Q_OBJECT

public:
    MainWidget(int argc, char* argv[], QWidget* parent = 0);
    virtual ~MainWidget();

private:
    Panel *mPanel;
    Renderer *mRenderer;
};

#endif //FILLWAVE_QT_EXAMPLE_MAINWIDGET_H
