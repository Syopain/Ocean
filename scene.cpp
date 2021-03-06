#include <QDebug>
#include <QString>
#include <QTimer>
#include <QtMath>
#include <QImage>
#include <QKeyEvent>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <QVector>
#include "scene.h"

Scene::Scene(QWidget *parent) :
    QOpenGLWidget(parent),
    shader("../shader.vert", "../shader.frag"),
    camera(glm::vec3(0.0f, 10.0f, 0.0f))
{
    resize(1280, 960);
    timer.start();
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
}

Scene::~Scene()
{
}

void Scene::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.5f, 0.8f, 0.9f, 1.0);
    glEnable(GL_DEPTH_TEST);
    shader.load();
    shader.use();
}

void Scene::paintGL()
{
    FPS++;
    float current_frame = timer.elapsed() / 1000.f;
    if (floor(current_frame) - floor(last_frame) == 1) {
        qDebug("FPS:%d", FPS);
        FPS = 0;
    }
    delta_time = current_frame - last_frame;
    last_frame = current_frame;

    static float static_frame = current_frame;
    if (!is_static) static_frame = current_frame;
    processKey();
    shader.setUniform("model", glm::mat4(1.0f));
    shader.setUniform("view", camera.lookAt());
    shader.setUniform("projection", glm::perspective(camera.zoom(0), static_cast<float>(width()) / height(), 0.1f, 3200.0f));
    shader.setUniform("time", static_frame);
    shader.setUniform("camera", camera.position());

    //if(is_static) shader.setUniform("time", last_frame);

    if(is_line) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Scene::resizeGL(int width, int height)
{
    Q_UNUSED(width)
    Q_UNUSED(height)
}


void Scene::keyPressEvent(QKeyEvent* event)
{
    if (!event->isAutoRepeat()) key[event->key()] = true;
    switch (event->key()) {
        case Qt::Key_C:
            is_static = !is_static;
            break;
        case Qt::Key_L:
            is_line = !is_line;
            break;
        case Qt::Key_Return:
            showFullScreen();
            break;
        case Qt::Key_Escape:
            if (isFullScreen())
                showNormal();
            else
                close();
            break;
    }

    QOpenGLWidget::keyPressEvent(event);
}

void Scene::keyReleaseEvent(QKeyEvent* event)
{
    if (!event->isAutoRepeat()) key[event->key()] = false;

    QOpenGLWidget::keyReleaseEvent(event);
}

void Scene::processKey()
{
    if (key[Qt::Key_W]) camera.forward(delta_time);
    if (key[Qt::Key_S]) camera.backward(delta_time);
    if (key[Qt::Key_A]) camera.left(delta_time);
    if (key[Qt::Key_D]) camera.right(delta_time);
    if (key[Qt::Key_Space]) camera.rise(delta_time);
    if (key[Qt::Key_Control]) camera.drop(delta_time);
}

void Scene::mouseMoveEvent(QMouseEvent* event)
{
    float const sensitivity = 0.05f;
    if (hasFocus()) {
        QCursor::setPos(mapToGlobal(QPoint(width()/2, height()/2)));
        float dx = event->x() - width()/2;
        float dy = height()/2 - event->y();
        camera.rotate(dy * sensitivity, dx * sensitivity);
    }
    QOpenGLWidget::mouseMoveEvent(event);
}

void Scene::focusInEvent(QFocusEvent* event)
{
    setCursor(Qt::BlankCursor);
    QCursor::setPos(mapToGlobal(QPoint(width()/2, height()/2)));
    QOpenGLWidget::focusInEvent(event);
}

void Scene::focusOutEvent(QFocusEvent* event)
{
    setCursor(Qt::ArrowCursor);
    QOpenGLWidget::focusOutEvent(event);
}

void Scene::wheelEvent(QWheelEvent* event)
{
    camera.zoom(event->angleDelta().y());
    QOpenGLWidget::wheelEvent(event);
}
