#ifndef PAINTER_H
#define PAINTER_H
#include <scene.h>


class Painter : public Scene
{
    Q_OBJECT

public:
    Painter(QWidget *parent = nullptr);
protected:
    void initializeGL() override;
    void paintGL() override;
private:
    unsigned int VAO;
    Mesh mesh;
};

#endif // PAINTER_H
