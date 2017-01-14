//
// Created by filip on 04.05.16.
//

#include "Button.h"
#include <QString>

Button::Button(const QString &name, QWidget *parent) :
    QPushButton(name, parent)
{

}

Button::~Button() {

}

void Button::keyPressEvent(QKeyEvent *) {
    emit onPressed();
}
