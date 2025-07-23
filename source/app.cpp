// app.cpp
#include "app.h"
#include "log.h"

App::App() : m_pWindow(nullptr) {
	m_iWidth = 1024;
	m_iHeight = 768;
	m_sTitle = "OpenSM";
	m_bRunning = false;

	bool m_SDLInit = SDL_Init(SDL_INIT_VIDEO);
	if (!m_SDLInit) {
		Log::log(Log::Level::Critical, "SDL_Init failed");
		return;
	}
}

App::~App() {
	if (m_pWindow)
		SDL_DestroyWindow(m_pWindow);

	if (m_pRenderer)
		SDL_DestroyRenderer(m_pRenderer);

	SDL_Quit();
}

bool App::Initialize() {
	m_pWindow = SDL_CreateWindow(m_sTitle.c_str(), m_iWidth, m_iHeight, 0);
	if (!m_pWindow) {
		Log::log(Log::Level::Critical, "SDL_CreateWindow failed");
		return false;
	}

	m_pRenderer = SDL_CreateRenderer(m_pWindow, NULL);
	if (!m_pRenderer) {
		Log::log(Log::Level::Critical, "SDL_CreateRenderer failed");
		SDL_DestroyWindow(m_pWindow);
		return false;
	}

	m_bRunning = true;
    while (m_bRunning) {
        while (SDL_PollEvent(&m_event)) {
            if (m_event.type == SDL_EVENT_QUIT) {
                m_bRunning = false;
            }
        }

        SDL_RenderClear(m_pRenderer);
		/// TODO: rendering stuff
		SDL_RenderPresent(m_pRenderer);

        SDL_Delay(16); // ~60 FPS
    }

	return true;
}