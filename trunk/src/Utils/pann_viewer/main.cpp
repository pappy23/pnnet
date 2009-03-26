#include <QApplication>
#include <QMessageBox>

#include "window.h"

#include "pann.h"

using namespace pann;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMessageBox err_msg;

    if(argc != 2)
    {
        //TODO replace pann_viewer with argv[0]
        err_msg.setText("Usage: pann_viewer <filename>");
        err_msg.exec();
        return -1;
    }

    Net *net = new Net;

    try {
        Storage::load(*net, argv[1]);
    } catch(E<Exception::FilesystemError>& e) {
        err_msg.setText(e.what());
        err_msg.exec();
        return -1;
    }

    Window window(net);
    window.show();

    return app.exec();
}

