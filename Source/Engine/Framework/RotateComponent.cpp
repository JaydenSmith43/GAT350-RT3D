#include "RotateComponent.h"
#include "Framework.h"

namespace nc
{
	CLASS_DEFINITION(RotateComponent);

	bool nc::RotateComponent::Initialize()
	{
		return true;
	}

	void nc::RotateComponent::Update(float dt)
	{
		m_owner->transform.euler += euler * dt;

		glm::quat rotation = EulerToQuaternion(euler * dt);
		m_owner->transform.rotation = m_owner->transform.rotation * rotation;
	}

	void nc::RotateComponent::SetProgram(const res_t<Program> program, const std::string& name)
	{
		program->SetUniform(name + ".euler", euler); //radians?
	}

	void nc::RotateComponent::ProcessGui()
	{
		ImGui::DragFloat3("Rotate", glm::value_ptr(euler));
	}

	void nc::RotateComponent::Read(const nc::json_t& value)
	{
		READ_NAME_DATA(value, "rotation", euler);
	}

}
