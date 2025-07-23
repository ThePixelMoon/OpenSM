// app.h

#ifndef APP_H
#define APP_H

#include <SDL3/SDL.h>
#include <string>

class App {
public:
	App();
	~App();

	bool Initialize();

private:
	SDL_Window *m_pWindow;
	SDL_Event m_event;
	SDL_Renderer *m_pRenderer;
	int m_iWidth;
	int m_iHeight;
	std::string m_sTitle;
	bool m_bRunning;
};

#endif // APP_H