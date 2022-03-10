#include "scene.h"
#include <QDebug>
#include <QString>
#include <QTimer>
#include <QtMath>
#include <QImage>
#include <QKeyEvent>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Scene::Scene(QWidget *parent) :
    QOpenGLWidget(parent),
    shader("../shader.vert", "../shader.frag"),
    camera(glm::vec3(0.0f, 0.0f, 3.0f))
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
    float current_frame = timer.elapsed() / 1000.f;
    delta_time = current_frame - last_frame;
    last_frame = current_frame;
    processKey();
    shader.setUniform("view", camera.lookAt());
    glm::mat4 projection(1.0f);
    projection = glm::perspective(camera.zoom(0), static_cast<float>(width()) / height(), 0.1f, 100.0f);
    shader.setUniform("projection", projection);

    update();
}

void Scene::resizeGL(int width, int height)
{

}


void Scene::keyPressEvent(QKeyEvent* event)
{
    //qDebug() << __func__ + QString("();");

    switch (event->key()) {
        case Qt::Key_W:
            if (!event->isAutoRepeat()) key['w'-'a'] = true;
            break;
        case Qt::Key_S:
            if (!event->isAutoRepeat()) key['s'-'a'] = true;
            break;
        case Qt::Key_A:
            if (!event->isAutoRepeat()) key['a'-'a'] = true;
            break;
        case Qt::Key_D:
            if (!event->isAutoRepeat()) key['d'-'a'] = true;
            break;
        case Qt::Key_Space:
            if (!event->isAutoRepeat()) key[26] = true;
            break;
        case Qt::Key_Control:
            if (!event->isAutoRepeat()) key[27] = true;
            break;
        case Qt::Key_Return:
            showFullScreen();
            break;
        case Qt::Key_Escape:
            showNormal();
            break;
    }

    QOpenGLWidget::keyPressEvent(event);
}

void Scene::keyReleaseEvent(QKeyEvent* event)
{
    switch (event->key()) {
        case Qt::Key_W:
            if (!event->isAutoRepeat()) key['w'-'a'] = false;
            break;
        case Qt::Key_S:
            if (!event->isAutoRepeat()) key['s'-'a'] = false;
            break;
        case Qt::Key_A:
            if (!event->isAutoRepeat()) key['a'-'a'] = false;
            break;
        case Qt::Key_D:
            if (!event->isAutoRepeat()) key['d'-'a'] = false;
            break;
        case Qt::Key_Space:
            if (!event->isAutoRepeat()) key[26] = false;
            break;
        case Qt::Key_Control:
            if (!event->isAutoRepeat()) key[27] = false;
            break;
    }
}

void Scene::processKey()
{
    if (key['w'-'a']) camera.forward(delta_time);	// Key_W
    if (key['s'-'a']) camera.backward(delta_time);	// Key_S
    if (key['a'-'a']) camera.left(delta_time);		// Key_A
    if (key['d'-'a']) camera.right(delta_time);		// Key_D
    if (key[26]) camera.rise(delta_time);			// Key_Space
    if (key[27]) camera.drop(delta_time);			// Key_Control
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
