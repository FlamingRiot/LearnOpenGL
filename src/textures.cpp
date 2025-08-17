#include <iostream>

#include <glad/glad.h>
#include <glfw3.h>

#include "textures.hpp"
#include "graphics.hpp"
#include "stb_image.h"

namespace graphics{

    Texture::Texture(){}
    
    Texture::Texture(const char* textureFile){
        // Create texture object
        unsigned int textureId;
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        // Set texture filtering/wrapping modes for currently bound texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Load texture image
        unsigned char *data = stbi_load(textureFile, &width, &height, &nrChannels, 0);

        if (data){
              // Send texture data to texture object
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else{
            std::cout << "[TEXTURE] Failed to load texture : " << textureFile << std::endl;
        }
        
        // Free image memory
        stbi_image_free(data);
    }

    Material::Material(){
        this->shader = baseShader;
    }
}