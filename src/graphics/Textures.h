#pragma once
#include <glad/glad.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "../image/stb_image.h"


namespace engine{
namespace graphics {

	class Texture {
	private:
		int _width, _height, _nrChannels;
		unsigned char* _data;
		char _buffer[300];
		unsigned int _texture;
		unsigned int _tex_num;
	public:
		Texture(const char* texturePath, unsigned int tex_num) {
			
			strncpy_s(_buffer, "C:/Users/hemas/source/repos/FirstGameEngine/FirstGameEngine/src/image/", sizeof(_buffer));
			strcat_s(_buffer, sizeof(_buffer), texturePath);
			_tex_num = tex_num;
			init();
		
		}
		void init() {

			glActiveTexture(GL_TEXTURE0 + _tex_num);
			glGenTextures(1, &_texture);
			glBindTexture(GL_TEXTURE_2D, _texture);

			stbi_set_flip_vertically_on_load(true);

			_data = stbi_load(_buffer, &_width, &_height, &_nrChannels, 0);
			if (_data)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _data); 
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
				std::cout << "Failed to load texture" << std::endl;
			}

			stbi_image_free(_data);


			
		}
		~Texture() {
		}


		void textureParameters() {
			

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}


		
		







	};





}

}