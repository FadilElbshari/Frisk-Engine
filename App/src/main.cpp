#include "Engine/Application/Application.h"

using namespace Frisk;

class Game : public Application {
public:
	using Application::Application;

protected:
    virtual void OnUpdate() override {

    }
};

int main() {
	Game game({1280, 720, "Frisky Engine Window", VEC3(120, 120, 255)});
	game.Run();
}
