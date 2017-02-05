//
// Created by filip on 30.04.16.
//

#ifndef PANEL_H
#define PANEL_H

#include <QWidget>

class QPushButton;
class Sliders;
class Button;

class Panel : public QWidget
{
    Q_OBJECT
public:
    explicit Panel(QWidget *parent = 0, const QString& fileName = "");

signals:
    void onChanged(int sliderNo, int value) const;

public slots:
    void onButtonApply() const;
    void onButtonReset() const;
    void onSliderMoved(int sliderIdx, int value) const;

private:
    static constexpr int PANEL_WIDTH = 200;
    Button *mButtonApply;
    Button *mButtonReset;
    Sliders *mSliders;
};


#endif //FILLWAVE_QT_EXAMPLE_PANEL_H
