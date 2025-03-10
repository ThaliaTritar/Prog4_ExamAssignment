#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "RotationComponent.h"

#include "InputManager.h"
#include "Command.h"
#include "MoveCommand.h"


void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	// add textures
	auto go = std::make_shared<dae::GameObject>();
	auto texture1 = std::make_shared<dae::TextureComponent>(go,"background.tga");
	go->AddComponent(texture1);
	scene.Add(go);
	
	go = std::make_shared<dae::GameObject>();
	auto texture2 = std::make_shared<dae::TextureComponent>(go,"logo.tga");
	go->SetLocalPosition(glm::vec3{ 216, 180,0 });
	go->AddComponent(texture2);
	scene.Add(go);

	// add text
	go = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto tc = std::make_shared<dae::TextComponent>(go,"Programming 4 Assignment", font);
	go->SetLocalPosition(glm::vec3{ 80, 20,0 });
	go->AddComponent(tc);
	scene.Add(go);

	
	// FPS COMPONENT
	//-------------
	go = std::make_shared<dae::GameObject>();
	auto fpstc = std::make_shared<dae::TextComponent>(go,"FPS", font);
	go->AddComponent(fpstc);
	auto fps = std::make_shared<dae::FPSComponent>(go);
	go->AddComponent(fps);
	go->SetLocalPosition(glm::vec3{ 80, 60,0 });
	scene.Add(go);
	


	// MOVING SPRITES
	//----------------
	auto& inputManager = dae::InputManager::GetInstance();

	// add bubblun 
	auto bubblun = std::make_shared<dae::GameObject>();
	auto bubblunTexture = std::make_shared<dae::TextureComponent>(bubblun, "Bubblun.png");
	bubblun->AddComponent(bubblunTexture);
	bubblun->SetLocalPosition({ 100,100,0 });

	bubblun->SetSpeed(50.0f);
	inputManager.BindKeyCommand(SDLK_w, std::make_unique<dae::MoveUpCommand>(dae::MoveUpCommand(bubblun.get())));
	inputManager.BindKeyCommand(SDLK_s, std::make_unique<dae::MoveDownCommand>(dae::MoveDownCommand(bubblun.get())));
	inputManager.BindKeyCommand(SDLK_a, std::make_unique<dae::MoveLeftCommand>(dae::MoveLeftCommand(bubblun.get())));
	inputManager.BindKeyCommand(SDLK_d, std::make_unique<dae::MoveRightCommand>(dae::MoveRightCommand(bubblun.get())));
	
	// add bobblun 
	auto bobblun = std::make_shared<dae::GameObject>();
	auto bobblunTexture = std::make_shared<dae::TextureComponent>(bobblun, "Bobblun.png");
	bobblun->AddComponent(bobblunTexture);
	bobblun->SetLocalPosition({ 20,20,0 });

	bobblun->SetSpeed(100.f);
	inputManager.BindBtnCommand(XINPUT_GAMEPAD_DPAD_UP,		std::make_unique<dae::MoveUpCommand>(dae::MoveUpCommand(bobblun.get())));
	inputManager.BindBtnCommand(XINPUT_GAMEPAD_DPAD_DOWN,	std::make_unique<dae::MoveDownCommand>(dae::MoveDownCommand(bobblun.get())));
	inputManager.BindBtnCommand(XINPUT_GAMEPAD_DPAD_LEFT,	std::make_unique<dae::MoveLeftCommand>(dae::MoveLeftCommand(bobblun.get())));
	inputManager.BindBtnCommand(XINPUT_GAMEPAD_DPAD_RIGHT,	std::make_unique<dae::MoveRightCommand>(dae::MoveRightCommand(bobblun.get())));

	scene.Add(bubblun);
	scene.Add(bobblun);


}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}