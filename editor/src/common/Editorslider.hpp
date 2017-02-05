#ifndef EDITORSLADER_H
#define EDITORSLADER_H

#include <QWidget>

class QSlider;
class QMouseEvent;

class EditorSlider : public QWidget
{
    Q_OBJECT
public:
    explicit EditorSlider(const QString& name, QWidget *parent = 0);

private:
    QSlider *mSlider;

    virtual void    mouseMoveEvent(QMouseEvent *ev);
    virtual void	mousePressEvent(QMouseEvent *ev);
    virtual void	mouseReleaseEvent(QMouseEvent *ev);

signals:
    void notify(int type, int value);
public slots:
//    void log(int a);
};

#endif // EDITORSLADER_H
