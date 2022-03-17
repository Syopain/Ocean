#include "mesh.h"

Mesh::Mesh()
{
    /*
    int n = 100;
    for (int i = -n; i < n; ++i) {
        for (int j = -n; j < n; ++j) {
            float layer = 10;

            vertices.push_back(i/layer);
            vertices.push_back(j/layer);
            vertices.push_back((i+1)/layer);
            vertices.push_back(j/layer);
            vertices.push_back((i+1)/layer);
            vertices.push_back((j+1)/layer);

            vertices.push_back(i/layer);
            vertices.push_back(j/layer);
            vertices.push_back((i+1)/layer);
            vertices.push_back((j+1)/layer);
            vertices.push_back(i/layer);
            vertices.push_back((j+1)/layer);

            if (i < n-1 && j < n-1) {
                int r = i + n;
                int c = j + n;
                indices.push_back(r*n*2 + c);			// 1
                indices.push_back(r*n*2 + c + 1);		// 2
                indices.push_back((r+1)*n*2 + c + 1);   // 3
                indices.push_back(r*n*2 + c);			// 1
                indices.push_back((r+1)*n*2 + c + 1);   // 3
                indices.push_back((r+1)*n*2 + c);		// 4
            }
        }
    }
    n = 100;
    for (int i = -n; i < n; ++i) {
        for (int j = -n; j < n; ++j) {
            if (abs(j) < 50 && abs(i) < 50) continue;
            float layer = 5;

            vertices.push_back(i/layer);
            vertices.push_back(j/layer);
            vertices.push_back((i+1)/layer);
            vertices.push_back(j/layer);
            vertices.push_back((i+1)/layer);
            vertices.push_back((j+1)/layer);

            vertices.push_back(i/layer);
            vertices.push_back(j/layer);
            vertices.push_back((i+1)/layer);
            vertices.push_back((j+1)/layer);
            vertices.push_back(i/layer);
            vertices.push_back((j+1)/layer);
        }
    }*/
    generate(0, 15, 8);
    generate(15, 30, 4);
    generate(30, 60, 2);
    generate(60, 120, 1);
    generate(120, 360, 0.5);
    generate(360, 720, 0.25);
}

void Mesh::generate(int inner, int outer, float layer)
{
    int n = outer * layer;

    for (int i = -n; i < n; ++i) {
        for (int j = -n; j < n; ++j) {
            if (std::max(abs(j), abs(i)) < inner * layer) continue;

            vertices.push_back(i/layer);
            vertices.push_back(j/layer);
            vertices.push_back((i+1)/layer);
            vertices.push_back(j/layer);
            vertices.push_back((i+1)/layer);
            vertices.push_back((j+1)/layer);

            vertices.push_back(i/layer);
            vertices.push_back(j/layer);
            vertices.push_back((i+1)/layer);
            vertices.push_back((j+1)/layer);
            vertices.push_back(i/layer);
            vertices.push_back((j+1)/layer);
        }
    }

}
