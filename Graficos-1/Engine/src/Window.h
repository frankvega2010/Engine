#ifndef WWINDOW_H
#define WWINDOW_H

#define DLLEXPORT __declspec(dllexport)

#include "../libs/GLFW/include/glfw3.h"
#include "gl/GL.h"

namespace Basegame
{
	class DLLEXPORT Window
	{
	private:
		int width;
		int height;
		const char* name;
		GLFWwindow* window;
	public:
		Window(int w, int h, const char* n);
		~Window();
		void SetBackgroundColor(int r, int g, int b, int a);
		bool GetOpened();
		void Clear();
		void SwapBuffers();
		void PollEvents();
		void Init();
		void DeInit();
	};
}
#endif
