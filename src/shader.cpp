#include "shader.h"
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <ostream>
#include <sstream>
#include <stdexcept>

Shader::Shader(GLenum type): shaderType(type) {
    this->shaderObject = glCreateShader(type);
}

Shader::~Shader() {
    glDeleteShader(this->shaderObject);
}

void Shader::LoadAndCompile(const std::string &fname) const{
    std::ifstream fin;
    std::string code;
    fin.exceptions(std::ifstream::failbit|std::ifstream::badbit);
    try {
        fin.open(fname);
        std::stringstream codestream;
        codestream << fin.rdbuf();
        code = codestream.str();
    }catch(std::ifstream::failure e) {
        throw std::runtime_error("Error: Shader: File read failed");
    }
    const char *shaderCode = code.c_str();
    glShaderSource(this->shaderObject, 1, &shaderCode, NULL);
    glCompileShader(this->shaderObject);
    
    int success;
    glGetShaderiv(this->shaderObject, GL_COMPILE_STATUS, &success);
    if(!success) {
        char infolog[512];
        glGetShaderInfoLog(this->shaderObject, 512, NULL, infolog);
        std::ostringstream msg;
        msg << "Error: Shader: Failed to compile shader." << std::endl << "Reason: " << infolog << std::endl;
        throw std::runtime_error(msg.str());
    }
}

inline GLuint Shader::getShaderObject() const{
    return this->shaderObject;
}

ShaderProgram::ShaderProgram() {
    this->progHandle = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(this->progHandle);
}

void ShaderProgram::AttachShader(const Shader &obj) {
    glAttachShader(this->progHandle, obj.getShaderObject());
}

void ShaderProgram::Link() const{
    glLinkProgram(this->progHandle);
    int success;
    glGetProgramiv(this->progHandle, GL_LINK_STATUS, &success);
    if(!success) {
        std::stringstream msg;
        char infoLog[512];
        glGetProgramInfoLog(this->progHandle, 512, nullptr, infoLog);
        msg << "Error: Program: Failed to link shader program." << std::endl << "Reason: " << infoLog << std::endl;
        throw std::runtime_error(msg.str());
    }
}

inline GLuint ShaderProgram::getShaderProgramObject() const{
    return this->progHandle;
}

void ShaderProgram::Use() const {
    glUseProgram(this->progHandle);
}

void ShaderProgram::setUniform(const std::string &key,float value) const {
    int location = glGetUniformLocation(this->progHandle, key.c_str());
    glUniform1f(location, value);
}

void ShaderProgram::setUniform(const std::string &key,int value) const {
    int location = glGetUniformLocation(this->progHandle, key.c_str());
    glUniform1i(location, value);
}

void ShaderProgram::setUniform(const std::string &key,glm::vec3 value) const {
    int location = glGetUniformLocation(this->progHandle, key.c_str());
    glUniform3fv(location, 1, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const std::string &key,glm::vec4 value) const {
    int location = glGetUniformLocation(this->progHandle, key.c_str());
    glUniform4fv(location, 1, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const std::string &key,glm::mat4 value) const {
    int location = glGetUniformLocation(this->progHandle, key.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}