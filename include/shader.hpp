#pragma once

#ifndef SHADER_H
#define SHADER_H

namespace graphics{

    class Shader{

        public: 
            unsigned int id;

            Shader();
            Shader(const char* vertexFile, const char* fragmentFile);

            void unload();
    };

    void loadGlShaders();
    void useShader(Shader shader);
    int getShaderLocation(Shader shader, const char* uniform);
}

#endif