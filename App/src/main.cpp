#include "Engine/Core/Log.h"
#include "Engine/Core/EngineAPI.h"
#include "Engine/Application/Application.h"

using namespace Frisk;

class Game : public Application {
public:
	using Application::Application;
};

int main() {
	Game game({1280, 720, "Frisky Engine"});
	game.Run();

	std::cin.get();
}