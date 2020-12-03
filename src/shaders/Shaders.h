
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:

	// the program ID
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath) {
		
		// 1. retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			//open file
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			//transfer content into a stream variable
			std::stringstream vShaderStream, fShaderStream;
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			//convert to string and store in string variables
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch(std::ifstream::failure e){
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}

		std::cout << vertexCode << std::endl;

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		// 2. compile shaders
		//initialize glad
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;

		}

		unsigned int vertex, fragment;
		int success;
		char infoLog[1052];
		
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

		if (!success) {
			glGetShaderInfoLog(vertex, 1052, NULL, infoLog);
			std::cout << "ERROR: VERTEX SHADER DID NOT COMPILE" << std::endl;
		}

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment ,1 ,&fShaderCode ,NULL);
		glCompileShader(fragment);


		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

		if (!success) {
			glGetShaderInfoLog(fragment, 1052, NULL, infoLog);
			std::cout << "ERROR: FRAGMENT SHADER DID NOT COMPILE" << std::endl;
		}

		ID = glCreateProgram();
		glAttachShader(ID,vertex);
		glAttachShader(ID,fragment);
		glLinkProgram(ID);


		glGetProgramiv(ID, GL_COMPILE_STATUS, &success);

		if (!success) {
			glGetProgramInfoLog(ID, 1052, NULL, infoLog);
			std::cout << "ERROR: SHADER PROGRAM DID NOT COMPILE" << std::endl;
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}

	~Shader() {}

	void use() {
		glUseProgram(ID);
	}

	void setFloat(const std::string& name, float value) const {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

	void setInt(const std::string& name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

	void setBool(const std::string& name, bool value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}

private:



};
#endif