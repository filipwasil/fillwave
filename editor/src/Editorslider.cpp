#include "Editorslider.hpp"
#include <QVBoxLayout>
#include <QSlider>
#include <QLabel>
#include  <QMouseEvent>

EditorSlider::EditorSlider(const QString& name, QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setDirection(QBoxLayout::LeftToRight);
    setLayout(layout);
    QLabel *label = new QLabel(name);
    label->setFixedWidth(50);
    layout->addWidget(label);
    mSlider = new QSlider(Qt::Horizontal);
    layout->addWidget(mSlider);
}

void EditorSlider::mouseMoveEvent(QMouseEvent *ev)
{
    emit notify(1,1);
}

void EditorSlider::mousePressEvent(QMouseEvent *ev)
{
    emit notify(1,2);
}

void EditorSlider::mouseReleaseEvent(QMouseEvent *ev)
{
    emit notify(1,3);
}



