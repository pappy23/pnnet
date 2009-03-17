#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QLabel>
#include <QKeyEvent>

#include "Includes.h"

#include "NetPublicWrapper.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(pann::Net* _net, QLabel* _label, QWidget *parent = 0);
    ~GLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent* e);

private:
    pann::NetPublicWrapper net_wr;
    QLabel* info_label; //TODO Replace it with QTextEdit and do nice html formatting

    void setInfoNeuron(unsigned); //fill info label with Neuron info
    void setInfoNet(); //fill info label with Net info

    void normalizeAngle(int *angle);
    void getNeuronCoords(pann::ConstNeuronIter _iter, const pann::NetCache& _cache, GLdouble& _x, GLdouble& _y, GLdouble& _z);
    void drawNetModel();

    GLuint object;
    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;
    QColor bgColor;
    QColor neuronColor;
    QColor linkColor;
};

#endif
