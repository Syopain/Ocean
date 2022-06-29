#include "painter.h"

#include <QApplication>

extern "C" {
    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Painter w;
    w.show();
    return a.exec();
}
