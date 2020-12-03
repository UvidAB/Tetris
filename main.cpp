#include <chrono>
#include <vector>
#include <thread>
#include <algorithm>
#include <atomic>
#include <array>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "src/maths/vec.h"
#include "src/maths/mat.h"
#include "src/shaders/Shaders.h"
#include "src/graphics/window.h"
#include "src/graphics/CreateObject.h"

#define STB_IMAGE_IMPLEMENTATION
#include "src/image/stb_image.h"






using namespace ::engine::math;
using namespace ::engine::graphics;

/*
void frames();
void rotate_90(CreateObject& lBlock);
*/

void gravity(CreateLblock& lblock);


Window& window = Window::make(800,600,"hello");

namespace engine {
	void set_key_callback(void (*func)(int, int))
	{
		window.set_key_callback(func);
	}
}

std::atomic_bool z = false;

void handle_tetris_input(int key_type, int event_type)
{
	if (key_type == GLFW_KEY_Z && event_type == GLFW_PRESS) {
		z = true;
	}
	
	
}


int main()
{
	
	Shader shader("Shader.vs","Shader.fs");
	


	

	Mat4f begin(Vec3f({ 0, 0, 0 }), Vec3f({ 0, 0, 0 }));
	Mat4f trans = begin;

	CreateLblock lblock(1);
	

	float angle = 0;
	float y_translation = 0;
	float counter = 0;
	unsigned int next = 0;
	

	engine::set_key_callback(handle_tetris_input);


	while (!window.closed()) {
	
		window.update();
		shader.use();
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		lblock.drawShape(shader);

		/*
		unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, base.position.to_glfloat());
		base.bindVAO();
		shader.setInt("texture1", 1);
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		*/

		//
		/*
		if (z) {
			rotate_90(lBlock);
			z = false;
		}
		*/

		/*
		Mat4f t2(Vec3f({ 0, 0, 0 }), Vec3f({ 0.5, 0.5, 0.5}));
		Mat4f t1(Vec3f({ lBlock.x, lBlock.y, lBlock.z }));
		Mat4f r1(lBlock.angle, Vec3f({ 0, 0, 1 }));
		Mat4f r2(0, Vec3f({ 0, 0, 0 }));
		Mat4f t3 = t1 * t2;
		Mat4f r3 = r1 * r2;
		trans =  t3 *  r1 ;
		*/
	

		gravity(lblock);

		

	}

}

void frames() {
	std::this_thread::sleep_for(std::chrono::nanoseconds(10));
	std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(10));
}


// user functions
/*
void rotate_90(CreateObject& lBlock) {
	float angle = (int)(lBlock.angle + 90) % 360;
	angle = (float)angle;
	lBlock.setAngle(90, Vec3f({0, 0, 1}));
}
*/

void gravity(CreateLblock& lblock) {
	lblock.applyTranslations(0, -0.01, 0);
}




