#pragma once

namespace nc
{
	class Editor
	{
	public:
		void Update();
		void ProcessGui(class Scene* scene);

		enum eResourceType
		{
			TEXTURE,
			MODEL,
			MATERIAL,
			SHADER
		};

	private:
		class Object* m_selected = nullptr;
		class Object* m_rename = nullptr;
		bool m_active = true;
	};
}