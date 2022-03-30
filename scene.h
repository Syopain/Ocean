#ifndef SCENE_H
#define SCENE_H

#include <QOpenGLWidget>
#include <qopenglfunctions_3_3_core.h>
#include <QElapsedTimer>
#include <bitset>
#include "shader.h"
#include "camera.h"
#include "mesh.h"

class Scene : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    Scene(QWidget *parent = nullptr);
    ~Scene();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    Shader shader;

private:
    void processKey();
    Camera camera;
    QElapsedTimer timer;
    float delta_time = 0.0;
    float last_frame = 0.0;
    std::bitset<64> key;
    bool is_static = false;
    bool is_line = false;
};
#endif // SCENE_H
