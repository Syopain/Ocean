#ifndef MESH_H
#define MESH_H
#include <QVector>

class Mesh
{
public:
    Mesh();
    float const* data() const
    {
        return vertices_.constData();
    }
    int size() const
    {
        return vertices_.size();
    }
private:
    void generate(int inner, int outer, float layer);

    QVector<float> vertices_;
};

#endif // MESH_H
