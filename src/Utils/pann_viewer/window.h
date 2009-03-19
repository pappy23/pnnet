#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

#include "glwidget.h"

#include "NetPublicWrapper.h"

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(pann::Net* _net);

private:
    GLWidget *glWidget;
    QLabel* label;

protected:
    void mouseDoubleClickEvent(QMouseEvent* event);
};

#endif
