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


void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	// add textures
	auto go = std::make_shared<dae::GameObject>();
	auto texture1 = std::make_shared<dae::TextureComponent>("background.tga");
	go->AddComponent(texture1);
	scene.Add(go);
	
	go = std::make_shared<dae::GameObject>();
	auto texture2 = std::make_shared<dae::TextureComponent>("logo.tga");
	texture2->SetPosition(216, 180);
	go->AddComponent(texture2);
	scene.Add(go);

	// add text
	go = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto tc = std::make_shared<dae::TextComponent>("Programming 4 Assignment", font);
	tc->SetPosition(80, 20);
	go->AddComponent(tc);
	
	scene.Add(go);

	// add FPS counter
	go = std::make_shared<dae::GameObject>();
	auto fpstc = std::make_shared<dae::TextComponent>("FPS", font);
	fpstc->SetPosition(80, 60);
	go->AddComponent(fpstc);
	auto fps = std::make_shared<dae::FPSComponent>();
	go->AddComponent(fps);
	
	scene.Add(go);
	
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}