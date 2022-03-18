#include "mesh.h"

Mesh::Mesh()
{
    generate(0, 20, 8);
    generate(20, 50, 4);
    generate(50, 100, 2);
    generate(100, 200, 1);
    generate(200, 400, 0.5);
    generate(400, 800, 0.25);
    generate(800, 1600, 0.125);
}

void Mesh::generate(int inner, int outer, float layer)
{
    int n = outer * layer;

    for (int i = -n; i < n; ++i) {
        for (int j = -n; j < n; ++j) {
            if (std::max(abs(j), abs(i)) < inner * layer) continue;

            vertices_.push_back(i/layer);
            vertices_.push_back(j/layer);
            vertices_.push_back((i+1)/layer);
            vertices_.push_back(j/layer);
            vertices_.push_back((i+1)/layer);
            vertices_.push_back((j+1)/layer);

            vertices_.push_back(i/layer);
            vertices_.push_back(j/layer);
            vertices_.push_back((i+1)/layer);
            vertices_.push_back((j+1)/layer);
            vertices_.push_back(i/layer);
            vertices_.push_back((j+1)/layer);
        }
    }
}
