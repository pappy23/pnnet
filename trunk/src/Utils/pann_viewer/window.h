#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

#include "glwidget.h"

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

class GLWidget;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();

private:
    GLWidget *glWidget;
    QLabel* label;
};

#endif
