#pragma once
#include <glad/glad.h>
#include <array>
#include <iostream>
#include <vector>
//depended on these two libraries
#include "../maths/mat.h"
#include "../maths/vec.h"
#include "../graphics/CreateBlock.h"





/*
- add draw method
- figure out how to use create block to create a shape
		- use matrix class to adjust coordinates of the block so they align in to shape in local space
		- ...
		- ...
- rename to createShape
- figure out how to rotate the whole object

*/

namespace engine {namespace graphics {
#define NUM_OF_BLOCKS 4


		class CreateLblock {
		private:
			CreateBlock _block[NUM_OF_BLOCKS];

		public:
			/*
			i = 1 = L_block
			i = 2 = Line block
			i = 3 = T block
			*/
			CreateLblock(int i) {

				init();
			}

			void drawShape(Shader shader) {
				for (int i = 0; i < NUM_OF_BLOCKS; i++) {
					unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
					glUniformMatrix4fv(transformLoc, 1, GL_FALSE, _block[i].position.to_glfloat());
					_block[i].bindVAO();
					shader.setInt("texture1", _block[i].tex_num);
					glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
					glBindVertexArray(0);
				
				}
			}

			void applyTranslations(float x0, float y0, float z0) {
				for (int i = 0; i < NUM_OF_BLOCKS; i++) {
					_block[i].applyTranslations(x0, y0, z0);
				
				}
			
			}

		private:
			
			void init() {
				/*
					- each block has to be transfromed individualy at  the timne of drwing

				
				
				*/
				//Creates an L block
				_block[1].applyTranslations(0, 0.125, 0);
				_block[2].applyTranslations(0, 0.25, 0);
				_block[3].applyTranslations(0.125, 0, 0);

			}

			
	

		};
	
	
}
}