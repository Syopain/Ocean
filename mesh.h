#ifndef MESH_H
#define MESH_H
#include <QVector>

class Mesh
{
public:
    Mesh();
    float const* data() const
    {
        return vertices.constData();
    }
    int size() const
    {
        return vertices.size();
    }
private:
    void generate(int inner, int outer, float layer);

    QVector<float> vertices;
    QVector<int> indices;
};

#endif // MESH_H
