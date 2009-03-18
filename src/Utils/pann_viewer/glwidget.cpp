#include <QtGui>

#include <cmath>

#include "glwidget.h"

using namespace std;
using namespace pann;

GLWidget::GLWidget(Net* _net, QLabel* _label, QWidget *parent)
    : QGLWidget(parent), net_wr(_net), info_label(_label)
{
    setInfoNet();
    //setInfoNeuron(1);
    
    calcCoords();

    object = 0;
    xRot = 0;
    yRot = 0;
    zRot = 0;

    bgColor = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);
    neuronColor = QColor(255, 0, 0);
    linkColor = QColor(0, 255, 0);
}

GLWidget::~GLWidget()
{
    makeCurrent();
    glDeleteLists(object, 1);
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

        for(unsigned thread = 0; thread < cache.data[layer].size(); ++thread)
        {
            for(unsigned number = 0; number < cache.data[layer][thread].size(); ++number)
            {
                ConstNeuronIter neuronIter = cache.data[layer][thread][number];
                Coords c;
                c.x = (GLdouble) ((GLdouble)layer - (GLdouble)total_layers/2 + 1) * 100;
                c.y = (GLdouble) ((GLdouble)number -(GLdouble)layer_size/2 + 1) * 50;
                c.z = (GLdouble)0;
                coords[neuronIter] = c;
            }
        }
    }
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
        <<endl;

    info_label->setText(ost.str().c_str());
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}

void GLWidget::setXRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::setYRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::setZRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
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
    glTranslated(0.0, 0.0, -10.0);
    glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotated(zRot / 16.0, 0.0, 0.0, 1.0);
    drawNetModel();
}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-0.5, +0.5, +0.5, -0.5, 4.0, 15.0);
    glOrtho(-width/2,width/2, -height/2,height/2 ,-(width+height)/4,(width+height)/4);
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
    //TODO: show key hint to user via info_label
    //FIXME: not working
    switch(e->key())
    {
        case Qt::Key_Up:
            glRotated(5.0,1.0,0.0,0.0);
            break;
        case Qt::Key_Down:
            glRotated(-5.0,1.0,0.0,0.0);
            break;
        case Qt::Key_Left:
            glRotated(5.0,0.0,1.0,0.0);
            break;
        case Qt::Key_Right:
            glRotated(-5.0,0.0,1.0,0.0);
            break;
        case Qt::Key_Plus:
            glScaled(1.1,1.1,1.1);
            break;
        case Qt::Key_Minus:
            glScaled(0.9,0.9,0.9);
            break;
        case Qt::Key_W:
            glTranslated(0.0,0.1,0.0);
            break;
        case Qt::Key_Z:
            glTranslated(0.0,-0.1,0.0);
            break;
        case Qt::Key_A:
            glTranslated(-0.1,0.0,0.0);
            break;
        case Qt::Key_S:
            glTranslated(0.1,0.0,0.0);
            break;
        case Qt::Key_Space:
            glLoadIdentity();
            break;
        default:
            return;
    }

    updateGL();
} 

void GLWidget::drawNetModel()
{
    const GLdouble neuronRadius = 7;

    GLUquadric* q = gluNewQuadric();

    glLineWidth(1.5);
    glPointSize(1.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    gluQuadricNormals(q, GLU_SMOOTH);

    //DEBUG:
    glColor3d(0, 0, 255);
    gluSphere(q, neuronRadius+20, 20, 20); 

    //For every neuron draw Link::in connections
    map<unsigned, Neuron>::const_iterator iter = net_wr.getNeurons().begin();
    for(; iter != net_wr.getNeurons().end(); ++iter)
    {
        Coords to_coords = coords[iter];

        //Draw neuron
        qglColor(neuronColor);
        glPushMatrix();
        glTranslated(to_coords.x, to_coords.y, to_coords.z);
        gluSphere(q, neuronRadius, 20, 20); 
        glPopMatrix();

        //Draw it's Link::in connections
        qglColor(linkColor);
        list<Link>::const_iterator link_iter = iter->second.links.begin();
        for(; link_iter != iter->second.links.end(); ++link_iter)
        {
            if(link_iter->getDirection() == Link::out)
                continue;

            Coords from_coords = coords[link_iter->getToIter()];

    glBegin(GL_LINES);
            glVertex3d(from_coords.x, from_coords.y, from_coords.z);
            glVertex3d(to_coords.x, to_coords.y, to_coords.z);
    glEnd();
        }
    }


    gluDeleteQuadric(q);
}

void GLWidget::normalizeAngle(int *angle)
{
    while (*angle < 0)
        *angle += 360 * 16;
    while (*angle > 360 * 16)
        *angle -= 360 * 16;
}
