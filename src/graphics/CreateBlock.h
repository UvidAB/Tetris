#include <glad/glad.h>
#include <array>
#include <iostream>
#include <vector>
//depended on these two libraries
#include "../maths/mat.h"
#include "../maths/vec.h"
#include "src/graphics/Textures.h"



/*
- handle textures in this class
- 



*/
namespace engine { namespace graphics {
		class CreateBlock {

		private:
			unsigned int _VAO;
			unsigned int _VBO;
			unsigned int _EBO;

		public:
			math::Mat4f position, translations, rotations, scale;
			int tex_num = 3;

		private:
			std::vector<float> _vertices = {
				//postions
				-0.125f,   0.125f, 0.0f,   0.0f, 1.0f, // top left
				-0.125f,  -0.125f, 0.0f,   0.0f, 0.0f, // bottom left
				 0.125f,   0.125f, 0.0f,   1.0f, 1.0f, // top right
				 0.125f,  -0.125f, 0.0f,   1.0f, 0.0f, // bottom right

			};
			std::vector<unsigned int> _indices = {
				0, 1, 3,   // first triangle
				0, 2, 3,  // second triangle
			};
			
			void init() {
				math::Mat4f initRotations(0, math::Vec3f({ 0, 0, 0 }));
				rotations = initRotations;

				math::Mat4f initTranslations(math::Vec3f({ 0, 0, 0 }));
				translations = initTranslations;

				//Scaled 0.5 Each block is halfed the stated size from above
				math::Mat4f initScale(math::Vec3f({ 0, 0, 0 }), math::Vec3f({ 0.5, 0.5, 0.5 }));
				scale = initScale;
				position = initScale;

				Texture tex3("block.png", tex_num);


				//---------------------------
				glGenVertexArrays(1, &_VAO);
				glBindVertexArray(_VAO);

				glGenBuffers(1, &_VBO);
				glBindBuffer(GL_ARRAY_BUFFER, _VBO);

				glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_STATIC_DRAW);

				glGenBuffers(1, &_EBO);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), _indices.data(), GL_STATIC_DRAW);

				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(0);

				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
				glEnableVertexAttribArray(1);

				glBindVertexArray(0);
			}

		public:
			CreateBlock() {
				init();
			}

			void bindVAO() {
				glBindVertexArray(_VAO);
			}

			void bindVBO() {
				glBindBuffer(GL_ARRAY_BUFFER, _VBO);
			}

			void bindEBO() {
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
			}

			void applyTranslations(float x0, float y0, float z0) {

				math::Mat4f translate(math::Vec3f({ x0, y0, z0 }));
				translations = translations * translate;

				position = translations * scale * rotations;
			}

			void setAngle(float angle0, math::Vec3f axis) {
				math::Mat4f rotation(angle0, axis);
				rotations = rotations * rotation;

				position = translations * scale * rotations;
			}
			
		};
		
}	
}