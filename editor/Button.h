//
// Created by filip on 04.05.16.
//

#ifndef FILLWAVE_QT_EXAMPLE_BUTTON_H
#define FILLWAVE_QT_EXAMPLE_BUTTON_H

#include <QPushButton>

class QString;

class Button : public QPushButton
{
    Q_OBJECT
public:
    explicit Button(const QString &name, QWidget *parent = 0);
    virtual ~Button();

    void keyPressEvent(QKeyEvent *) override;

    signals:
    void onPressed();
};

#endif //FILLWAVE_QT_EXAMPLE_BUTTON_H
