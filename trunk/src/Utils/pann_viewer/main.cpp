#include <QApplication>
#include <QMessageBox>

#include "window.h"

#include "Net.h"
#include "Storage.h"

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

    Net net;
    try {
        Storage::load(net, argv[1]);
    } catch(Exception::Base& e) { //TODO catch(FilesystemError)
        err_msg.setText(e.getText().c_str());
        err_msg.exec();
        return -1;
    }

    //Build GL

    Window window;
    window.show();
    return app.exec();
}

