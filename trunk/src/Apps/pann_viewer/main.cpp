#include <QApplication>
#include <QMessageBox>

#include "window.h"

#include "pann.h"

using namespace pann;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if(argc != 2)
    {
        //TODO replace pann_viewer with argv[0]
        QMessageBox::information(0, argv[0], "Usage: pann_viewer <filename>");
        return -1;
    }

    if(!QGLFormat::hasOpenGL())
    {
        QMessageBox::information(0, argv[0], "System does not support OpenGL");
        return -1;
    }

    Net *net = new Net;

    try {
        Storage::load(*net, argv[1]);
    } catch(E<Exception::FilesystemError>& e) {
        QMessageBox::information(0, argv[0], e.what());
        return -1;
    }

    Window window(net);
    window.show();

    return app.exec();
}

