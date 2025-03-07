#pragma once
#include "Framework/System.h"
#include <glm/glm/glm.hpp>
#include <SDL2-2.28.4/include/SDL.h>
#include <vector>
#include <array>

namespace nc
{
	// Input system that holds the state of input devices (keyboard, mouse).
	class InputSystem : public ISystem
	{
	public:
		InputSystem() = default;
		~InputSystem() = default;

		bool Initialize() override;
		void Shutdown() override;

		void Update() override;

		// keyboard
		// Use (SDL_SCANCODE_<KEY>) to check if the key is down this frame.
		bool GetKeyDown(uint32_t key) const { return m_keyboardState[key]; }
		// Use (SDL_SCANCODE_<KEY>) to check if the key was down last frame.
		bool GetPreviousKeyDown(uint32_t key) const { return m_prevKeyboardState[key]; }

		// mouse
		// Get mouse position relative to the top left of the screen in pixel coordinates.
		const glm::vec2& GetMousePosition() const { return m_mousePosition; }
		// Get mouse relaive to previous mouse position
		glm::vec2 GetMouseRelative() const { return m_mousePosition - m_prevMousePosition; }
		// Use (0 = left, 1 = middle, 2 = right) to check if the mouse button is down this frame.
		bool GetMouseButtonDown(uint32_t button) { return m_mouseButtonState[button]; }
		// Use (0 = left, 1 = middle, 2 = right) to check if the mouse button was down last frame.
		bool GetPreviousMouseButtonDown(uint32_t button) { return m_prevMouseButtonState[button]; }

	private:
		std::vector<uint8_t> m_keyboardState;
		std::vector<uint8_t> m_prevKeyboardState;

		glm::vec2 m_mousePosition;
		glm::vec2 m_prevMousePosition;
		std::array<uint8_t, 3> m_mouseButtonState{ 0, 0, 0 };
		std::array<uint8_t, 3> m_prevMouseButtonState{ 0, 0, 0 };
	};
}