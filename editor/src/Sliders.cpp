//
// Created by filip on 30.04.16.
//

#include "Sliders.h"
#include <QVBoxLayout>
#include "Editorslider.hpp"

Sliders::Sliders(QWidget *parent) : QWidget(parent),
                                    mCount(new EditorSlider("Count")),
                                    mSize(new EditorSlider("Size")),
                                    mLife(new EditorSlider("Life")),
                                    mCut(new EditorSlider("Cut"))
{
    /* Layout */
    QVBoxLayout *layoutSliders = new QVBoxLayout();
    setLayout(layoutSliders);
    layoutSliders->setDirection(QBoxLayout::BottomToTop);

    layoutSliders->addWidget(mCount);
    layoutSliders->addWidget(mSize);
    layoutSliders->addWidget(mLife);
    layoutSliders->addWidget(mCut);

    QObject::connect(mCount, &EditorSlider::notify,
                     this, &Sliders::onSliderMoved);

    QObject::connect(mSize, &EditorSlider::notify,
                     this, &Sliders::onSliderMoved);

    QObject::connect(mCut, &EditorSlider::notify,
                     this, &Sliders::onSliderMoved);

    QObject::connect(mLife, &EditorSlider::notify,
                     this, &Sliders::onSliderMoved);

}

void Sliders::onSliderMoved(int , int ) {
    emit onSlidersMoved(1,3);
}