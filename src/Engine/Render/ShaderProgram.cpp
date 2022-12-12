#include "ShaderProgram.h"
#include "Engine/Util/FileIO.h"
#include <glad/glad.h>
#include <iostream>

namespace engine
{
    ShaderProgram::ShaderProgram(const char *vertexShaderPath, const char *fragmentShaderPath)
    {
        std::string vertexShaderSource = GetStringFromFile(vertexShaderPath);
        std::string fragmentShaderSource = GetStringFromFile(fragmentShaderPath);

        m_programID = glCreateProgram();

        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        SetShaderSource(vertexShader, vertexShaderSource.c_str());
        CompileShader(vertexShader);
        AttachShader(vertexShader);

        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        SetShaderSource(fragmentShader, fragmentShaderSource.c_str());
        CompileShader(fragmentShader);
        AttachShader(fragmentShader);

        LinkShader();

        DeleteShader(vertexShader);
        DeleteShader(fragmentShader);

    }

    ShaderProgram::~ShaderProgram()
    {
        glDeleteShader(m_programID);
    }

    void ShaderProgram::Bind() const
    {
        glUseProgram(m_programID);
    }
    void ShaderProgram::Unbind() const
    {
        glUseProgram(0);
    }

    void ShaderProgram::SetUniform1f(const char* name, float data) const
    {
        Bind();
        int uniformLocation = glGetUniformLocation(m_programID, name);
        if(uniformLocation == -1)
        {
            std::cout << "Error while retrieving location of Uniform: " << name << std::endl;
            return;
        }
        glUniform1f(uniformLocation, data);
    }

    void ShaderProgram::SetUniform3f(const char* name, glm::vec3 data) const
    {
        int uniformLocation = glGetUniformLocation(m_programID, name);
        if(uniformLocation == -1)
        {
            std::cout << "Error while retrieving location of Uniform: " << name << std::endl;
            return;
        }
        Bind();
        glUniform3f(uniformLocation, data.x, data.y, data.z);
    }

    void ShaderProgram::SetUniform4f(const char* name, glm::vec4 data) const
    {
        int uniformLocation = glGetUniformLocation(m_programID, name);
        if(uniformLocation == -1)
        {
            std::cout << "Error while retrieving location of Uniform: " << name << std::endl;
            return;
        }
        Bind();
        glUniform4f(uniformLocation, data.x, data.y, data.z, data.w);
    }

    void ShaderProgram::SetUniform1i(const char* name, int data) const
    {
        Bind();
        int uniformLocation = glGetUniformLocation(m_programID, name);
        if(uniformLocation == -1)
        {
            std::cout << "Error while retrieving location of Uniform: " << name << std::endl;
            return;
        }
        glUniform1i(uniformLocation, data);
    }

    void ShaderProgram::SetUniformMatrix4fv(const char* name, int count, bool transpose, const float* data) const
    {
        Bind();
        int uniformLocation = glGetUniformLocation(m_programID, name);
        if(uniformLocation == -1)
        {
            std::cout << "Error while retrieving location of Uniform: " << name << std::endl;
            return;
        }
        glUniformMatrix4fv(uniformLocation, count, transpose, data);
    }

    void ShaderProgram::LinkTextureSlotToUniform(const char* name, int slot) const
    {
        SetUniform1i(name, slot);
    }

    // Private Functions
    // ------------------------------------------------------------------------------------

    void ShaderProgram::SetShaderSource(unsigned int shaderID, const char* shaderSrcString)
    {
        glShaderSource(shaderID, 1, &shaderSrcString, nullptr);
    }

    void ShaderProgram::CompileShader(unsigned int shaderID)
    {
        glCompileShader(shaderID);
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &m_result);
        if(!m_result)
        {
            glGetShaderInfoLog(shaderID, 512, nullptr, m_log);
            std::cout << "[Shader Compilation Error]:" << std::endl << m_log << std::endl;
        }
    }

    void ShaderProgram::AttachShader(unsigned int shaderID) const
    {
        glAttachShader(m_programID, shaderID);
    }

    void ShaderProgram::LinkShader()
    {
        glLinkProgram(m_programID);
        glGetProgramiv(m_programID, GL_LINK_STATUS, &m_result);
        if(!m_result)
        {
            glGetProgramInfoLog(m_programID, 512, nullptr, m_log);
            std::cout << "[Linking Error]:" << std::endl << m_log << std::endl;
        }
    }

    void ShaderProgram::DeleteShader(unsigned int shaderID)
    {
        glDeleteShader(shaderID);
    }
}