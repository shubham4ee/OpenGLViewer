#pragma once
#include "VertexBuffer.h"

class VertexArray {
public:
    unsigned int ID;
    VertexArray() { glGenVertexArrays(1, &ID); }
    ~VertexArray() { glDeleteVertexArrays(1, &ID); }

    void LinkAttrib(VertexBuffer& vb, unsigned int layout, unsigned int numComponents, unsigned int stride, void* offset) {
        Bind();
        vb.Bind();
        glVertexAttribPointer(layout, numComponents, GL_FLOAT, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(layout);
        vb.Unbind();
    }
    void Bind() const { glBindVertexArray(ID); }
    void Unbind() const { glBindVertexArray(0); }
};