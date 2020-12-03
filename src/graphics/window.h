#pragma once
#include <iostream>
#include <atomic>
#include <GLFW/glfw3.h>



namespace engine {namespace graphics{
	
	class Window {
	private:
		const char* m_Name;
		int m_Width;
		int m_Height;

		static bool _keys[1024];
		
	public:
		GLFWwindow* m_window;
		bool isFinished = false;
		~Window();
		void update();
		bool closed() const;
		void processInput();
		void set_key_callback(void (*f)(int, int)) { userKeyPressed = f; }
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

		static Window& make(int height, int width, const char* name);

		static Window& get(const char* name);

		Window(int height, int width, const char* name);

	private:
		bool init();
		

		

		static std::unique_ptr<Window> _windowInst ;
		void (*userKeyPressed)(int, int) = nullptr;
		  
	};
	
	}

}