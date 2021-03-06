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

    void processKey() override;
private:
    unsigned int VAO;
    unsigned int texture[10];
    Mesh mesh;
    glm::vec3 color;
    int status = 1;
};

#endif // PAINTER_H
