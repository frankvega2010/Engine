#ifndef WWINDOW_H
#define WWINDOW_H

#define DLLEXPORT __declspec(dllexport)

struct GLFWwindow;

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
	GLFWwindow* GetWindow();
};

#endif
