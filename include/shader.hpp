#pragma once

namespace graphics{

    class Shader{

        public: 
            unsigned int id;

            Shader();
            Shader(const char** vertexShaderTxt, const char** fragmentShaderTxt);
            // Shader(std::string vertexShaderFile, std::string fragmentShaderFile);

            void unload();
    };

    void loadGlShaders();
    void useShader(Shader shader);
    void useBaseShader();
}