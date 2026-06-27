#include "Engine/Application/Application.h"

using namespace Frisk;

class Game : public Application {
public:
	using Application::Application;
};

int main() {
	Game game({1280, 720, "Frisky Engine", VEC3(150, 150, 255)});
	game.Run();
}
