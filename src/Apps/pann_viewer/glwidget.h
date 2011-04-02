#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QLabel>
#include <QKeyEvent>

#include "pann.h"

struct NetInfo
{
    unsigned neurons;
    unsigned links;
};

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(pann::Net* _net, QLabel* _label, QWidget *parent = 0);
    ~GLWidget();

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void setScale(float);
    void setTranslation(float, float, float);
    void restoreDefaults();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent* e);
    void wheelEvent(QWheelEvent* e);

private:
    pann::Net* p_net;
    QLabel* info_label;

    void calcCoords();

    void setInfoNeuron(unsigned); //fill info label with Neuron info
    void setInfoNet(NetInfo _net_info); //fill info label with Net info

    void normalizeAngle(int *angle);

    //Main drawing
    void drawNetModel();

    //Rotation
    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;

    //Scale
    float scale;

    //Translation (move object)
    float xTrans;
    float yTrans;
    float zTrans;
    
    //Params
    bool drawLinks;
    float neuronRadius;
    unsigned linkRate;
};

#endif
