#include "World05.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtx/color_space.hpp>

namespace nc
{
    bool World05::Initialize()
    {
        m_scene = std::make_unique<Scene>();
        m_scene->Load("scenes/scene.json");
        m_scene->Initialize();

        //{
        //    auto actor = CREATE_CLASS(Actor);
        //    actor->name = "camera1";
        //    actor->transform.position = glm::vec3{ 0, 0, 3 };
        //    actor->transform.rotation = glm::radians(glm::vec3{ 0, 180, 0 });

        //    auto cameraComponent = CREATE_CLASS(CameraComponent);
        //    cameraComponent->SetPerspective(70.0f, ENGINE.GetSystem<Renderer>()->GetWidth() / (float)ENGINE.GetSystem<Renderer>()->GetHeight(), 0.1f, 100.0f);
        //    actor->AddComponent(std::move(cameraComponent));

        //    auto cameraController = CREATE_CLASS(CameraController);
        //    cameraController->speed = 5;
        //    cameraController->sensitivity = 5;
        //    cameraController->m_owner = actor.get();
        //    cameraController->Initialize();
        //    actor->AddComponent(std::move(cameraController));

        //    m_scene->Add(std::move(actor));
        //}

        
        for (int i = 0; i < 10; i++)
        {
            auto actor = CREATE_CLASS_BASE(Actor, "tree");
            actor->name = StringUtils::CreateUnique("tree");
            actor->transform.position = glm::vec3{ randomf(-10, 10), 0, randomf(-10, 10) };
            actor->transform.scale = glm::vec3{ randomf(0.5f, 3.0f), randomf(0.5f, 3.0f), 0 };
            actor->Initialize();
            m_scene->Add(std::move(actor));
        }


        return true;
    }

    void World05::Shutdown()
    {
    }

    void World05::Update(float dt)
    {
        ENGINE.GetSystem<Gui>()->BeginFrame();

        m_scene->Update(dt);
        m_scene->ProcessGui();

        //m_transform.rotation.z += 180 * dt;

        auto actor = m_scene->GetActorByName<Actor>("actor1");

        //actor->transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_A) ? m_speed * -dt : 0;
        //actor->transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_D) ? m_speed * +dt : 0;
        //actor->transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_W) ? m_speed * -dt : 0;
        //actor->transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_S) ? m_speed * +dt : 0;

        m_time += dt;
        
        auto material = actor->GetComponent<ModelComponent>()->material;

        material->ProcessGui();
        material->Bind();

        material = GET_RESOURCE(Material, "materials/refraction.mtrl");
        if (material)
        {
            ImGui::Begin("Refraction");

            //m_refraction = 1 + std::fabs(std::sin(m_time * 0.1f));

            ImGui::DragFloat("IOR", &m_refraction, 0.01f, 1.0f, 3.0f);
            auto program = material->GetProgram();
            program->Use();
            program->SetUniform("ior", m_refraction);

            ImGui::End();
        }
        
        //material->GetProgram()->SetUniform("ambientLight", m_ambientColor);

        ENGINE.GetSystem<Gui>()->EndFrame();
    }

    void World05::Draw(Renderer& renderer)
    {
        // pre-render
        renderer.BeginFrame();

        // render
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //gl_cullback
        m_scene->Draw(renderer);

        ENGINE.GetSystem<Gui>()->Draw();

        // post-render
        renderer.EndFrame();
    }
}
