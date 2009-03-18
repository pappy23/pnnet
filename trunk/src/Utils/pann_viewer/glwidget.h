#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QLabel>
#include <QKeyEvent>

#include "Includes.h"
#include "NetPublicWrapper.h"
#include "Util.h"

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

private:
    pann::NetPublicWrapper net_wr;
    QLabel* info_label; //TODO Replace it with QTextEdit and do nice html formatting

    struct Coords
    {
        GLdouble x, y, z;
    };
    std::map<pann::ConstNeuronIter, Coords, pann::NeuronIterCompare> coords;

    void calcCoords();

    void setInfoNeuron(unsigned); //fill info label with Neuron info
    void setInfoNet(); //fill info label with Net info

    void normalizeAngle(int *angle);
    void drawNetModel();

    //Rotation
    int xRot;
    int yRot;
    int zRot;
    //Scale
    float scale;
    //Translation (move object)
    float xTrans;
    float yTrans;
    float zTrans;
    //Params
    bool drawBiasLinks;
    bool drawLinks;
    float neuronRadius;
    unsigned linkRate;

    QPoint lastPos;
    QColor bgColor;
    QColor neuronColor;
    QColor linkColor;
};

#endif
