#include <QApplication>
#include <QMessageBox>

#include "window.h"

#include "pann.h"

using namespace pann;
using namespace pann::Storage;

//Load net and automatically detect format
void autoload(Net& _obj, std::string _filename);

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
        autoload(*net, argv[1]);
    } catch(IoError& e) {
        QMessageBox::information(0, argv[0], e.what());
        return -1;
    }

    Window window(net);
    window.show();

    return app.exec();
}

void autoload(Net& _obj, std::string _filename)
{
    try {
        std::cout<<"Trying XML...\n";
        load<xml_in>(_obj, _filename);
        return;
    } catch(...) {
    }

    try {
        std::cout<<"Trying TXT...\n";
        load<txt_in>(_obj, _filename);
        return;
    } catch(...) {
    }

    try {
        std::cout<<"Trying BIN...\n";
        load<bin_in>(_obj, _filename);
        return;
    } catch(...) {
    }

    throw IoError()<<"autoload(): Can't load "<<_filename<<"\n";
} //autoload
