#include <thread>
#include <atomic>
#include "window.h"




namespace engine {
	
	namespace graphics {
		std::unique_ptr<Window> Window::_windowInst(nullptr);
		Window& Window::get(const char *name) {
			return *_windowInst.get();
		}

		Window& Window::make(int height, int width, const char* name) {
			if (_windowInst.get() == nullptr) {
				_windowInst = std::make_unique<Window>(height, width, name);
			}
			return *_windowInst.get();
		}

		bool Window::_keys[1024];
		
		Window::Window(int height, int width, const char* name) {
			m_Name = name;
			m_Width = width;
			m_Height = height;
			if (!init()) {
				glfwTerminate();
			}
			for (int i = 0; i < 1024; i++) {
				_keys[i] = false;
			}
		}

		Window::~Window() {
			isFinished = true;
			glfwTerminate();
		}

		bool Window::init() {
			if (!glfwInit()) {
				glfwTerminate();
				std::cout << "failed to initialize glfw" << std::endl;
				return false;
			}

			m_window = glfwCreateWindow(m_Height, m_Width, m_Name, NULL, NULL);
			glfwMakeContextCurrent(m_window);
			glfwSetWindowUserPointer(m_window, this);
			glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {Window::get("hello").key_callback(window, key, scancode, action, mods); });

			if (!m_window) {
				glfwTerminate();
				std::cout << "Window failed to create" << std::endl;
				return false;
			}
			
			return true;
		}
	
			
		void Window::update() {
			glfwPollEvents();
			glfwSwapBuffers(m_window);
			processInput();
		}

		void Window::processInput() {
			if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
				glfwSetWindowShouldClose(m_window, true);
			}
		}

		void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if(userKeyPressed != nullptr)
				userKeyPressed(key, action);
		}

	


		bool Window::closed() const{
			return glfwWindowShouldClose(m_window);
		}

		
	}
}






