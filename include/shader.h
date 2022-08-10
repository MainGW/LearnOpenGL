#ifndef __SHADER_H__
#define __SHADER_H__

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string> 

class ShaderException : public std::exception {
public:
    ShaderException(const char *error) {
        pError = std::string(strdup(error));
    }

    ~ShaderException() = default;

    virtual const char *what() const noexcept {
        return pError.c_str();
    }
private:
    std::string pError;
};


class ShaderProgramException : public std::exception {
public:
    ShaderProgramException(const char *error) {
        pError = std::string(strdup(error));
    }
    ~ShaderProgramException() = default;
    virtual const char *what() const noexcept {
        return pError.c_str();
    }
private:
    std::string pError;
};

/**
 * @brief OpenGL Shader Class
 * @author wanaoi
 * @since v1.0
 */
class Shader
{
private:
    GLenum shaderType;
    GLuint shaderObject;
public:
    /**
     * @brief Construct a new Shader object
     * 
     * @param type Shader type
     */
    explicit Shader(GLenum type);  
    
    /**
     * @brief Destroy the Shader object
     */
    ~Shader();

    /**
     * @brief Load GLSL Source code from file and compile it. 
     * 
     * @param fname GLSL File's name.
     */
    void LoadAndCompile(const std::string& fname) const; 

    /**
     * @brief Get the Shader Object Handle
     * 
     * @return GLuint shader handle
     */
    [[nodiscard]] GLuint getShaderObject() const;
   
}; 

/**
 * @brief A shader program of OpenGL
 * 
 */
class ShaderProgram
{
private:
    int progHandle;
public:
    /**
     * @brief Construct a new Shader Program object
     * 
     * @param vertShader Vertex shader of the program.
     * @param fragShader Fragment shader of the program;
     */
    explicit ShaderProgram();

    /**
     * @brief Destroy the Shader Program object
     */
    ~ShaderProgram();

    /**
     * @brief Attach a shader object;
     */
    void AttachShader(const Shader &obj) const;

    /**
     * @brief Link the shader program.
     */
    void Link() const;

    /**
     * @brief Get the Shader Program Handle
     * 
     * @return GLuint the shader program handle
     */
    [[nodiscard]] GLuint getShaderProgramObject() const;

    /**
     * @brief Activate the shader program
     */
    void Use() const;

    /**
     * @brief Set the Uniform object
     * 
     * @param key the name of the uniform variable
     * @param value the value of the uniform variable
     */
    void setUniform(const std::string &key,float value) const;
    void setUniform(const std::string &key,int value) const;
    void setUniform(const std::string &key,glm::vec3 value) const;
    void setUniform(const std::string &key,glm::vec4 value) const;
    void setUniform(const std::string &key,glm::mat4 value) const;
};
#endif
