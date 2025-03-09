#pragma once
#include "Singleton.h"

#define WIN32_LEAN_AND_MEAN
#include <wtypes.h>
#include <SDL.h>
#include <Xinput.h>

#include <vector>
#include <memory>

#include "Command.h"

namespace dae
{
	class InputManagerImpl;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();

		void BindKeyCommand(SDL_Keycode key, std::unique_ptr<GameActorCommand> cmd);
		void BindBtnCommand(unsigned int btn, std::unique_ptr<GameActorCommand> cmd);

		bool ProcessInput();


	private:

		InputManagerImpl* m_pImpl;
	};



}
