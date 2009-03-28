#include <QtGui>

#include <cmath>

#include "glwidget.h"

using namespace std;
using namespace pann;

GLWidget::GLWidget(Net* _net, QLabel* _label, QWidget *parent)
    : QGLWidget(parent), p_net(_net), info_label(_label)
{
    calcCoords();

    restoreDefaults();
    drawNetModel();

    setInfoNet();
    //setInfoNeuron(1);
}

GLWidget::~GLWidget()
{
//    makeCurrent();
}

void GLWidget::calcCoords()
{
    const NetCache& cache = p_net->getCache();

    unsigned total_layers = cache.data.size();
    unsigned total_threads = cache.data[0].size();

    //Form colors for threads
    srand(42);
    vector<QColor> threadColors;
    for(unsigned i = 0; i < total_threads; ++i)
        threadColors.push_back(QColor(200 + rand() % 55 , rand() % 100, rand() % 100));

    for(unsigned layer = 0; layer < total_layers; ++layer)
    {
        unsigned layer_size = 0;
        for(unsigned thread = 0; thread < total_threads; ++thread)
            layer_size += cache.data[layer][thread].size();

        unsigned neuron_number = 0;
        for(unsigned thread = 0; thread < total_threads; ++thread)
        {
            for(unsigned i = 0; i < cache.data[layer][thread].size(); ++i)
            {
                const Neuron* neuronIter = cache.data[layer][thread][i];
                unsigned planeRows = sqrt(layer_size);
                unsigned planeCols = layer_size / planeRows;

                const Attributes& oglHint = neuronIter->oglHint;
                Coords c;

                if(oglHint.is(OpenGlHint::coord_x))
                    c.x = oglHint[OpenGlHint::coord_x];
                else
                    c.x = (GLdouble) ( (GLdouble)layer - total_layers/2.0 + 1.0) * 100;

                if(oglHint.is(OpenGlHint::coord_y))
                    c.y = oglHint[OpenGlHint::coord_y];
                else
                    c.y = (GLdouble) ( (GLdouble)(neuron_number / planeCols) - planeRows/2.0 + 1.0 ) * 40.0;
                
                if(oglHint.is(OpenGlHint::coord_z))
                    c.z = oglHint[OpenGlHint::coord_z];
                else
                    c.z = (GLdouble) ( (GLdouble)(neuron_number % planeCols) - planeCols/2.0 + 1.0 ) * 40.0;

                c.color = threadColors[thread];
                if(oglHint.is(OpenGlHint::color_r))
                    c.color.setRed(oglHint[OpenGlHint::color_r]);
                if(oglHint.is(OpenGlHint::color_g))
                    c.color.setGreen(oglHint[OpenGlHint::color_g]);
                if(oglHint.is(OpenGlHint::color_b))
                    c.color.setBlue(oglHint[OpenGlHint::color_b]);

                coords[neuronIter] = c;
                neuron_number++;
            }
        }
    }
}

void GLWidget::drawNetModel()
{
    GLUquadric* q = gluNewQuadric();
    gluQuadricNormals(q, GLU_SMOOTH);

    glNewList(1,GL_COMPILE);
    
    const Neuron* biasNeuron = (p_net->getNeurons().find(p_net->getBiasId()))->second;

    //For every neuron draw Link::in connections
    map<unsigned, Neuron*>::const_iterator iter = p_net->getNeurons().begin();
    for(; iter != p_net->getNeurons().end(); ++iter)
    {
        Coords to_coords = coords[iter->second];

        //Draw neuron
        glPushMatrix();
        qglColor(to_coords.color);
        glTranslated(to_coords.x, to_coords.y, to_coords.z);
        gluSphere(q, neuronRadius, 12, 12); 
        glPopMatrix();

        if(drawLinks)
        {
            //Draw it's Link::in connections
            qglColor(QColor(0, 255, 0));
            list<Link>::const_iterator link_iter = iter->second->links.begin();
            for(; link_iter != iter->second->links.end(); ++link_iter)
            {
                if(link_iter->getDirection() == Link::out)
                    continue;

                if(link_iter->getTo() == biasNeuron && !drawBiasLinks)
                    continue;

                if(linkRate > 1 && (rand() % linkRate != 0))
                    continue;

                Coords from_coords = coords[link_iter->getTo()];

                glBegin(GL_LINES);
                glVertex3d(from_coords.x, from_coords.y, from_coords.z);
                glVertex3d(to_coords.x, to_coords.y, to_coords.z);
                glEnd();
            }
        }
    }

    glEndList();

    gluDeleteQuadric(q);
}

void GLWidget::setInfoNeuron(unsigned _id)
{
    const Neuron* n = p_net->getNeurons().find(_id)->second;
    ostringstream ost;
    ost<<"Neuron info:\n"
        <<"ID: "<<_id<<endl
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
        <<"Neurons: "<<p_net->getNeurons().size()<<endl
        <<"Threads: "<<p_net->getThreadCount()<<endl
        <<endl<<endl;

    if(!drawLinks)
        ost<<"Note: links are not shown"<<endl;

    if(!drawBiasLinks)
        ost<<"Note: bias connections are not shown"<<endl;

    ost<<"Note: only every "<<linkRate<<"-th link is shown"<<endl;
    
    ost<<endl<<endl;
    
    ost<<"Hint: "<<endl;
    ost<<"'W', 'A', 'S', 'D', drag with mouse middle button - move around"<<endl;
    ost<<"'+', '-', mouse wheel  - zoom"<<endl;
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
    //TODO: customize this parametrs on the fly
    drawLinks = true;
    drawBiasLinks = true;
    linkRate = 1;

    updateGL();
}

void GLWidget::initializeGL()
{
    // Antialiasing
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
    glLineWidth(1.5);
    glPointSize(1.0);

    //Light
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHT0);
    GLfloat position[]  = { -width()/5.0f, height()/2.0f, 100.0f , 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, position);
 
    GLfloat specular[] = {0.5f, 0.5f, 0.5f , 1.0f};
    GLfloat ambient[]  = {0.2f, 0.2f, 0.2f , 1.0f};
    GLfloat diffuse[]  = {0.8f, 0.8f, 0.8f , 1.0f};
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

    float specReflection[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, specReflection);
    glMateriali(GL_FRONT, GL_SHININESS, 50);

/*
    GLfloat material_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat material_emission[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_emission);
*/

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    qglClearColor(QColor::fromCmykF(0.39, 0.39, 0.0, 0.0).dark());
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslated(xTrans, yTrans, zTrans);
    glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotated(zRot / 16.0, 0.0, 0.0, 1.0);
    glScaled(scale,scale,scale);
    glCallList(1);
}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width/2,width/2, -height/2,height/2 ,-(width+height),(width+height));
    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
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
    } else if (event->buttons() & Qt::MidButton) {
        setTranslation(xTrans + dx, yTrans - dy, zTrans);
    }
    lastPos = event->pos();
}

void GLWidget::keyPressEvent(QKeyEvent* e)
{
    const int rotationDelta = 30.0;
    const float scaleDelta = 0.05;
    const float translateDelta = 10;
    
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

void GLWidget::wheelEvent(QWheelEvent* event)
{
//    setTranslation(xTrans - x() + width() / 2.0, yTrans + y() - height() / 2.0, zTrans);
    setScale(scale + event->delta() / 200.0);
}

