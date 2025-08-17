#pragma once

#include "shader.hpp"

namespace graphics{

    class Texture{

        public: 
            unsigned int ID;
            int width;
            int height;
            int nrChannels;

        Texture();
        Texture(const char* textureFile);
    };

    class Material{
        public:
            Shader shader;
            Texture texture;

        Material();
    };

    void unloadTexture(Texture texture);
}