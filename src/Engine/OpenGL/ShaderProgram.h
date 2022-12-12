#ifndef BLOCKBUILDINGGAME_SHADERPROGRAM_H
#define BLOCKBUILDINGGAME_SHADERPROGRAM_H

#include <string>
#include "Texture2D.h"
#include "glm/glm.hpp"

namespace engine {
    class ShaderProgram {
    private:
        unsigned m_programID{};
        char m_log[512];
        int m_result;

//public functions
    public:

        ShaderProgram(const char *vertexShaderPath, const char *fragmentShaderPath);
        ~ShaderProgram();

        void Bind() const;
        void Unbind() const;

        void SetUniform1f(const char *name, float data) const;
        void SetUniform3f(const char *name, glm::vec3 data) const;
        void SetUniform4f(const char *name, glm::vec4 data) const;

        void SetUniform1i(const char *name, int data) const;

        void SetUniformMatrix4fv(const char *name, int count, bool transpose, const float *data) const;

        void LinkTextureSlotToUniform(const char *name, int slot) const;

//private functions
    private:

        static void SetShaderSource(unsigned int shaderID, const char *shaderSrcString);

        void CompileShader(unsigned int shaderID);
        void AttachShader(unsigned int shaderID) const;
        void LinkShader();

        static void DeleteShader(unsigned int shaderID);
    };
}

#endif //BLOCKBUILDINGGAME_SHADERPROGRAM_H
