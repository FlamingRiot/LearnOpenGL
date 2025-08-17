#pragma once

namespace graphics{

    class Shader{

        public: 
            unsigned int ID;

            Shader();
            Shader(const char* vertexFile, const char* fragmentFile);

            void unload();
    };

    void loadGlShaders();
    void useShader(Shader shader);
    int getShaderLocation(Shader shader, const char* uniform);
}