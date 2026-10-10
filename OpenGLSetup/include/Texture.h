#pragma once
#include <glad/glad.h>
#include <stb_image.h>
#include <string>
#include <iostream>

class Texture {
public:
    unsigned int ID;
    Texture(const char* imagePath, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
        glGenTextures(1, &ID);
        glActiveTexture(slot);
        glBindTexture(texType, ID);

        glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(texType, 0, format, width, height, 0, format, pixelType, data);
            glGenerateMipmap(texType);
        }
        else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }
    void Bind() { glBindTexture(GL_TEXTURE_2D, ID); }
};