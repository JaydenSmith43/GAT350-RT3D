#pragma once
#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Core/Math/Transform.h"
#include <vector>

namespace nc
{
	class World04 : public World
	{
		struct light_t
		{
			enum eType
			{
				Point,
				Directional,
				Spot
			};
			eType type;
			glm::vec3 position;
			glm::vec3 direction;
			glm::vec3 color;
			float intensity;
			float range;
			float innerAngle;
			float outerAngle;
		};

	public:
		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	private:
		float m_time;
		float m_speed = 10.0f;

		light_t m_lights[3]; //to make dynamic, make it a vector
		int m_selected = 0;
		glm::vec3 m_ambientColor{ 0.2f} ;

		Transform m_transform;
		res_t<Model> m_model;
	};
}