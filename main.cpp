#include "scene.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Scene w;
    w.show();
    return a.exec();
}
