#pragma once

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

    void unloadTexture(Texture texture);
}