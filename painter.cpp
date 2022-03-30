#include "painter.h"

Painter::Painter(QWidget* parent) :
    Scene(parent)
{

}

void Painter::initializeGL()
{
    Scene::initializeGL();

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

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, mesh.size()/2);

    update();
}
