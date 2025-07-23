// main.cpp
#include "log.h"
#include "app.h"

int main(int argc, char* argv[]) {
	Log::log(Log::Level::Debug, "OpenSM started");

    App app;
    if (!app.Initialize())
        return -1;

	return 0;
}