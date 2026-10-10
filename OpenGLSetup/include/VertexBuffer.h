#pragma once
#include <glad/glad.h>

class VertexBuffer {
public:
    unsigned int ID;
    VertexBuffer(float* vertices, unsigned int size) {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }
    ~VertexBuffer() { glDeleteBuffers(1, &ID); }
    void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, ID); }
    void Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
};