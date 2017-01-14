//
// Created by filip on 30.04.16.
//

#include "Panel.h"
#include "Sliders.h"
#include <QBoxLayout>
#include "Button.h"
#include <QLabel>
#include <QImageReader>

Panel::Panel(QWidget *parent, const QString& fileName)
        : QWidget(parent),
          mButtonApply(new Button("Apply")),
          mButtonReset(new Button("Reset")),
          mSliders(new Sliders(this))

{
    QVBoxLayout *layoutPanel = new QVBoxLayout();
    setLayout(layoutPanel);
    layoutPanel->setDirection(QBoxLayout::BottomToTop);
    setMaximumWidth(PANEL_WIDTH);

    /* Content */
    layoutPanel->addWidget(mButtonApply);
    layoutPanel->addWidget(mButtonReset);
    layoutPanel->addWidget(mSliders);

    /* Image */
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage bitmap = reader.read();
    if (!bitmap.isNull()) {
        QLabel *imageLabel = new QLabel();
        layoutPanel->addWidget(imageLabel);
        imageLabel->setBackgroundRole(QPalette::Base);
        imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        imageLabel->setScaledContents(true);
        imageLabel->setPixmap(QPixmap::fromImage(bitmap));
    }

    QObject::connect(mButtonApply, &Button::onPressed,
                     this, &Panel::onButtonApply);

    QObject::connect(mButtonReset, &Button::onPressed,
                     this, &Panel::onButtonReset);

    QObject::connect(mSliders, &Sliders::onSlidersMoved,
                     this, &Panel::onSliderMoved);
}

void Panel::onButtonApply() const
{
    emit onChanged(1,4);
}

void Panel::onButtonReset() const
{
    emit onChanged(1,4);
}

void Panel::onSliderMoved(int sliderIdx, int value) const
{
    emit onChanged(1,4);
}