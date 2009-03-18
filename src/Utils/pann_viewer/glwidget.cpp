#include <QtGui>

#include <cmath>

#include "glwidget.h"

using namespace std;
using namespace pann;

GLWidget::GLWidget(Net* _net, QLabel* _label, QWidget *parent)
    : QGLWidget(parent), net_wr(_net), info_label(_label)
{
    bgColor = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);
    neuronColor = QColor(255, 0, 0);
    linkColor = QColor(0, 255, 0);

    calcCoords();

    restoreDefaults();

    setInfoNet();
    //setInfoNeuron(1);
}

GLWidget::~GLWidget()
{
//    makeCurrent();
}

void GLWidget::calcCoords()
{
    const NetCache& cache = net_wr.getCache();
    unsigned total_layers = cache.data.size();
    for(unsigned layer = 0; layer < total_layers; ++layer)
    {
        unsigned layer_size = 0;
        for(unsigned thread = 0; thread < cache.data[layer].size(); ++thread)
            layer_size += cache.data[layer][thread].size();

        unsigned neuron_number = 0;
        for(unsigned thread = 0; thread < cache.data[layer].size(); ++thread)
        {
            for(unsigned i = 0; i < cache.data[layer][thread].size(); ++i)
            {
                ConstNeuronIter neuronIter = cache.data[layer][thread][i];
                unsigned planeRows = sqrt(layer_size);
                unsigned planeCols = layer_size / planeRows;

                Coords c;
                c.x = (GLdouble) ( (GLdouble)layer - total_layers/2.0 + 1.0) * 100;
                c.y = (GLdouble) ( (GLdouble)(neuron_number / planeCols) - planeRows/2.0 + 1.0 ) * 40.0;
                c.z = (GLdouble) ( (GLdouble)(neuron_number % planeCols) - planeCols/2.0 + 1.0 ) * 40.0;
                coords[neuronIter] = c;
                neuron_number++;
            }
        }
    }
}

void GLWidget::drawNetModel()
{
    srand(42); //for linkRate

    GLUquadric* q = gluNewQuadric();

    glLineWidth(1.5);
    glPointSize(1.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    gluQuadricNormals(q, GLU_SMOOTH);

    //DEBUG:
    //glColor3d(0, 0, 255);
    //gluSphere(q, neuronRadius+20, 20, 20); 

    //For every neuron draw Link::in connections
    map<unsigned, Neuron>::const_iterator iter = net_wr.getNeurons().begin();
    for(; iter != net_wr.getNeurons().end(); ++iter)
    {
        Coords to_coords = coords[iter];

        //Draw neuron
        qglColor(neuronColor);
        glPushMatrix();
        glTranslated(to_coords.x, to_coords.y, to_coords.z);
        gluSphere(q, neuronRadius, 12, 12); 
        glPopMatrix();

        if(drawLinks)
        {
            //Draw it's Link::in connections
            qglColor(linkColor);
            list<Link>::const_iterator link_iter = iter->second.links.begin();
            for(; link_iter != iter->second.links.end(); ++link_iter)
            {
                if(link_iter->getDirection() == Link::out)
                    continue;

                if(link_iter->getToIter()->first == net_wr.net->getBiasId() && !drawBiasLinks)
                    continue;

                if(rand() % linkRate)
                    continue;

                Coords from_coords = coords[link_iter->getToIter()];

                glBegin(GL_LINES);
                glVertex3d(from_coords.x, from_coords.y, from_coords.z);
                glVertex3d(to_coords.x, to_coords.y, to_coords.z);
                glEnd();
            }
        }
    }

    gluDeleteQuadric(q);
}

void GLWidget::setInfoNeuron(unsigned _id)
{
    const Neuron* n = &(net_wr.getNeurons().find(_id)->second);
    ostringstream ost;
    ost<<"Neuron info:\n"
        <<"ID: "<<_id<<endl
        <<"ActivationFunction: "<<n->getActivationFunction()->getName()
            <<" ("<<n->getActivationFunction()->getId()<<")"<<endl
        <<"Owner: "<<n->getOwnerThread()<<endl
        <<"Receptive field: "<<n->receptiveField<<endl
        <<"Activation value: "<<n->activationValue<<endl
        <<"Links: "<<n->links.size()<<endl
        <<endl;

    info_label->setText(ost.str().c_str());
}

void GLWidget::setInfoNet()
{
    ostringstream ost;
    ost<<"Net info:\n"
        <<"Neurons: "<<net_wr.getNeurons().size()<<endl
        <<"Weights: "<<net_wr.getWeights().size()<<endl
        <<"Threads: "<<net_wr.net->getThreadCount()<<endl
        <<endl<<endl;

    if(!drawLinks)
        ost<<"Note: links are not shown"<<endl;

    if(!drawBiasLinks)
        ost<<"Note: bias connections are not shown"<<endl;

    ost<<"Note: only every "<<linkRate<<"-th link is shown"<<endl;
    
    ost<<endl<<endl;
    
    ost<<"Hint: "<<endl;
    ost<<"'W', 'A', 'S', 'D' - move around"<<endl;
    ost<<"'+', '-' - zoom"<<endl;
    ost<<"'Up', 'Down', 'Left', 'Right' - rotate X-Y"<<endl;
    ost<<"Drag with left mouse button - rotate X-Y"<<endl;
    ost<<"Drag with right mouse button - rotate X-Z"<<endl;

    info_label->setText(ost.str().c_str());
}

void GLWidget::normalizeAngle(int *angle)
{
    while (*angle < 0)
        *angle += 360 * 16;
    while (*angle > 360 * 16)
        *angle -= 360 * 16;
}

void GLWidget::setXRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != xRot) {
        xRot = angle;
        updateGL();
    }
}

void GLWidget::setYRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != yRot) {
        yRot = angle;
        updateGL();
    }
}

void GLWidget::setZRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != zRot) {
        zRot = angle;
        updateGL();
    }
}

void GLWidget::setScale(float _scale)
{
    if(_scale != scale && _scale > 0.1 && _scale < 10.0)
    {
        scale = _scale;
        updateGL();
    }
}

void GLWidget::setTranslation(float _x, float _y, float _z)
{
    //if()
    {
        xTrans = _x;
        yTrans = _y;
        zTrans = _z;
        updateGL();
    }
}

void GLWidget::restoreDefaults()
{
    setTranslation(0, 0, 0);
    setScale(1.0);
    setXRotation(0);
    setYRotation(0);
    setZRotation(0);

    neuronRadius = 7;
    drawLinks = true;
    drawBiasLinks = false;
    linkRate = 2;

    updateGL();
}

void GLWidget::initializeGL()
{
    qglClearColor(bgColor.dark());
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    //glTranslated(0.0, 0.0, -10.0);
    glTranslated(xTrans, yTrans, zTrans);
    glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotated(zRot / 16.0, 0.0, 0.0, 1.0);
    glScaled(scale,scale,scale);
    drawNetModel();
}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width/2,width/2, -height/2,height/2 ,-(width+height)/2,(width+height)/2);
    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    //TODO: detect click on neuron
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }
    lastPos = event->pos();
}

void GLWidget::keyPressEvent(QKeyEvent* e)
{
    const int rotationDelta = 30.0;
    const float scaleDelta = 0.05;
    const float translateDelta = 10;
    
    //TODO: show key hint to user via info_label
    switch(e->key())
    {
        case Qt::Key_Up:
            setXRotation(xRot + rotationDelta);
            break;
        case Qt::Key_Down:
            setXRotation(xRot - rotationDelta);
            break;
        case Qt::Key_Left:
            setYRotation(yRot + rotationDelta);
            break;
        case Qt::Key_Right:
            setYRotation(yRot - rotationDelta);
            break;
        case Qt::Key_Plus:
            setScale(scale + scaleDelta);
            break;
        case Qt::Key_Minus:
            setScale(scale - scaleDelta);
            break;
        case Qt::Key_W:
            setTranslation(xTrans, yTrans - translateDelta, zTrans);
            break;
        case Qt::Key_S:
            setTranslation(xTrans, yTrans + translateDelta, zTrans);
            break;
        case Qt::Key_A:
            setTranslation(xTrans + translateDelta, yTrans, zTrans);
            break;
        case Qt::Key_D:
            setTranslation(xTrans - translateDelta, yTrans, zTrans);
            break;
        case Qt::Key_Space:
            restoreDefaults();
            break;
        default:
            return;
    }
    //updateGL();
} 
