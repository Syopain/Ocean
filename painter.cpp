#include <QGLWidget>
#include "painter.h"

Painter::Painter(QWidget* parent) :
    Scene(parent)
{

}

void Painter::initializeGL()
{
    Scene::initializeGL();

    glGenTextures(1, &texture);

    QImage bump = QGLWidget::convertToGLFormat(QImage("../texture/bump.jpeg").mirrored());
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bump.width(), bump.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bump.bits());
    glGenerateMipmap(GL_TEXTURE_2D);

    glGenVertexArrays(1, &VAO);
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh.size() * sizeof(float), mesh.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Painter::paintGL()
{
    Scene::paintGL();

    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, mesh.size()/2);

    update();
}
