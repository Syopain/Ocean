#include "mesh.h"

Mesh::Mesh()
{
    generate(0, 50, 8);
    generate(50, 100, 4);
    generate(100, 200, 2);
    generate(200, 400, 1);
    generate(400, 800, 0.5);
    generate(800, 1600, 0.25);
    generate(1600, 3800, 0.125); // l * 2/sqrt(3)
}

#if 1	// repair cracks
void Mesh::generate(int inner, int outer, float layer)
{
    outer *= layer;
    inner *= layer;

    for (int i = -outer; i < outer; ++i) {
        for (int j = -outer; j < outer; ++j) {
            if (std::max(abs(j), abs(i)) <= inner) continue;

            vertices_.push_back(i/layer);
            vertices_.push_back(j/layer);
            vertices_.push_back((i+1)/layer);
            vertices_.push_back(j/layer);
            if (-i == inner + 1 && j >= -inner && j < inner) {
                vertices_.push_back((i+1)/layer);
                vertices_.push_back((j+0.5f)/layer);
                vertices_.push_back(i/layer);
                vertices_.push_back(j/layer);
                vertices_.push_back((i+1)/layer);
                vertices_.push_back((j+0.5f)/layer);
            }
            vertices_.push_back((i+1)/layer);
            vertices_.push_back((j+1)/layer);

            vertices_.push_back(i/layer);
            vertices_.push_back(j/layer);
            vertices_.push_back((i+1)/layer);
            vertices_.push_back((j+1)/layer);
            if (-j == inner + 1 && i >= -inner && i < inner) {
                vertices_.push_back((i+0.5)/layer);
                vertices_.push_back((j+1)/layer);
                vertices_.push_back(i/layer);
                vertices_.push_back(j/layer);
                vertices_.push_back((i+0.5)/layer);
                vertices_.push_back((j+1)/layer);
            }
            vertices_.push_back(i/layer);
            vertices_.push_back((j+1)/layer);
        }
    }
    for (int i = -inner; i <= inner; ++i) {
        vertices_.push_back(i/layer);
        vertices_.push_back(inner/layer);
        vertices_.push_back(i/layer);
        vertices_.push_back((inner+1)/layer);
        vertices_.push_back((i+1)/layer);
        vertices_.push_back((inner+1)/layer);

        vertices_.push_back(inner/layer);
        vertices_.push_back(i/layer);
        vertices_.push_back((inner+1)/layer);
        vertices_.push_back(i/layer);
        vertices_.push_back((inner+1)/layer);
        vertices_.push_back((i+1)/layer);

        if (i == inner) break;

        vertices_.push_back(i/layer);
        vertices_.push_back(inner/layer);
        vertices_.push_back((i+0.5f)/layer);
        vertices_.push_back(inner/layer);
        vertices_.push_back((i+1)/layer);
        vertices_.push_back((inner+1)/layer);

        vertices_.push_back((i+0.5f)/layer);
        vertices_.push_back(inner/layer);
        vertices_.push_back((i+1)/layer);
        vertices_.push_back((inner+1)/layer);
        vertices_.push_back((i+1)/layer);
        vertices_.push_back(inner/layer);

        vertices_.push_back(inner/layer);
        vertices_.push_back(i/layer);
        vertices_.push_back(inner/layer);
        vertices_.push_back((i+0.5f)/layer);
        vertices_.push_back((inner+1)/layer);
        vertices_.push_back((i+1)/layer);

        vertices_.push_back(inner/layer);
        vertices_.push_back((i+0.5f)/layer);
        vertices_.push_back((inner+1)/layer);
        vertices_.push_back((i+1)/layer);
        vertices_.push_back(inner/layer);
        vertices_.push_back((i+1)/layer);

    }
}
#else
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
#endif
