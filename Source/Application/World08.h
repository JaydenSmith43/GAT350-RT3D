#pragma once
#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Core/Math/Transform.h"
#include <vector>

namespace nc
{
	class World08 : public World
	{
	public:
		const uint32_t INVERT_MASK = (1 << 0);
		const uint32_t GRAYSCALE_MASK  = (1 << 1);
		const uint32_t COLORTINT_MASK  = (1 << 2);

	public:
		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	private:
		float m_time;
		float m_speed = 10.0f;
		float m_blend{ 1 };

		float m_specularOffset = 0.3f;
		float m_outline = 0.3f;
		int m_celLevels = 4;

		uint32_t m_params{ 0 };

		float m_refraction{ 1 };
		glm::vec3 m_ambientColor{ 0.2f };
		glm::vec3 m_outlineColor{ 0 };
	};
}