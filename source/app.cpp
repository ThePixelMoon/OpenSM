// app.cpp
#include "app.h"
#include "log.h"
#include "xmlresource.h"
#include "xmlbin.h"
#ifdef USE_STEAM
#include <steam/steam_api.h>
#endif

App::App() : m_pWindow(nullptr) {
	m_iWidth = 1024;
	m_iHeight = 768;
	m_sTitle = "OpenSM";
	m_bRunning = false;

	bool SDLInit = SDL_Init(SDL_INIT_VIDEO);
	if (!SDLInit) {
		Log::log(Log::Level::Critical, "SDL_Init failed");
		return;
	}

#ifdef USE_STEAM
	bool SteamInit = SteamAPI_Init();
	if (!SteamInit) {
		Log::log(Log::Level::Critical, "SteamAPI_Init failed");
		return;
	}
#endif
}

App::~App() {
	if (m_pWindow)
		SDL_DestroyWindow(m_pWindow);

	if (m_pRenderer)
		SDL_DestroyRenderer(m_pRenderer);

	SDL_Quit();

#ifdef USE_STEAM
    SteamAPI_Shutdown();
#endif
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

#if NEVER
	Resource resource;
    if (!resource.loadFromXML("data/xml_resources/spore_ABCDE.xml"))
        return false;

    std::string imagePathMsg = "Atlas image path: " + resource.getImagePath();
    Log::log(Log::Level::Info, imagePathMsg.c_str());

    const SpriteInfo* sprite = resource.getSprite("spore_ABCDE");
    if (sprite) {
        std::string spriteMsg = "spore_ABCDE position: (" +
            std::to_string(sprite->x) + ", " + std::to_string(sprite->y) +
            "), size: " + std::to_string(sprite->w) + "x" + std::to_string(sprite->h);
        Log::log(Log::Level::Info, spriteMsg.c_str());
    }

	XMLBin bin;
    if (bin.load("data/xml_bin/001_BC.bin")) {
		Log::log(Log::Level::Info, ("Count/version: " + std::to_string(bin.getCount())).c_str());
		Log::log(Log::Level::Info, ("Fixed string: " + bin.getFixedStr()).c_str());
		for (size_t i = 0; i < bin.getStrings().size(); ++i) {
			Log::log(Log::Level::Info, ("String #" + std::to_string(i + 1) + ": " + bin.getStrings()[i]).c_str());
		}
    }
#endif

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