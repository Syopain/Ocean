#include <QGLWidget>
#include "painter.h"

Painter::Painter(QWidget* parent) :
    Scene(parent),
    color(0.1f, 0.5f, 0.7f)
{

}

void Painter::initializeGL()
{
    Scene::initializeGL();

    glGenTextures(2, texture);

    QImage bump = QGLWidget::convertToGLFormat(QImage("../texture/bump.jfif").mirrored());
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bump.width(), bump.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bump.bits());
    glGenerateMipmap(GL_TEXTURE_2D);
    QImage diffuse = QGLWidget::convertToGLFormat(QImage("../texture/Ocean_Foam-3_diffuseOriginal.png").mirrored());
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, diffuse.width(), diffuse.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, diffuse.bits());
    glGenerateMipmap(GL_TEXTURE_2D);

    glGenVertexArrays(1, &VAO);
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh.size() * sizeof(float), mesh.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    shader.setUniform("texture1", 0);
    shader.setUniform("texture2", 1);
}

void Painter::paintGL()
{
    Scene::paintGL();

    shader.setUniform("color", color);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture[1]);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, mesh.size()/2);

    update();
}

void Painter::processKey()
{
    float delta = 0.005;
    if(key[Qt::Key_Up]) {
        if (key[Qt::Key_R]) color.r += delta;
        if (key[Qt::Key_G]) color.g += delta;
        if (key[Qt::Key_B]) color.b += delta;
    }
    if (key[Qt::Key_Down]) {
        if (key[Qt::Key_R]) color.r -= delta;
        if (key[Qt::Key_G]) color.g -= delta;
        if (key[Qt::Key_B]) color.b -= delta;
    }
    color.r = glm::clamp(color.r, 0.0f, 1.0f);
    color.g = glm::clamp(color.g, 0.0f, 1.0f);
    color.b = glm::clamp(color.b, 0.0f, 1.0f);
    if (key[Qt::Key_R] || key[Qt::Key_G] || key[Qt::Key_B]) {
        qDebug("color(%.0f, %.0f, %.0f)", color.r * 255, color.g * 255, color.b * 255);
    }

    Scene::processKey();
}
