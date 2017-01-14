//
// Created by filip on 30.04.16.
//

#ifndef FILLWAVE_QT_EXAMPLE_SLIDERS_H
#define FILLWAVE_QT_EXAMPLE_SLIDERS_H

#include <QWidget>

class EditorSlider;

class Sliders : public QWidget
{
    Q_OBJECT
public:
    explicit Sliders(QWidget *parent = 0);
private:
    EditorSlider *mCount;
    EditorSlider *mSize;
    EditorSlider *mLife;
    EditorSlider *mCut;

signals:
    void onSlidersMoved(int slider, int value);
public slots:
    void onSliderMoved(int slider, int value);
};

#endif // FILLWAVE_QT_EXAMPLE_SLIDERS_H
