#include "World08.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtx/color_space.hpp>

namespace nc
{
    bool World08::Initialize()
    {
        m_scene = std::make_unique<Scene>();
        m_scene->Load("scenes/scene_editor.json");
        m_scene->Load("scenes/scene_celshading.json");
        m_scene->Initialize();

        m_editor = std::make_unique<Editor>(); //make unique and shard pointer; shared pointer is for multiple ownership, no one owns m_editor so it can be its own unique pointer.

        // create depth texture
        auto texture = std::make_shared<Texture>(); // delete all other things here
        texture->CreateDepthTexture(1024, 1024);
        ADD_RESOURCE("depth_texture", texture);

        // create depth buffer
        auto framebuffer = std::make_shared<Framebuffer>();
        framebuffer->CreateDepthBuffer(texture);
        ADD_RESOURCE("depth_buffer", framebuffer);

        // set depth texture to debug sprite
        auto material = GET_RESOURCE(Material, "mAterials/sprite.mtrl");
        if (material)
        {
            material->albedoTexture = texture;
        }

        auto materials = GET_RESOURCES(Material);
        for (auto material : materials)
        {
            material->depthTexture = texture;
        }

        return true;
    }

    void World08::Shutdown()
    {
    }

    void World08::Update(float dt)
    {
        m_time += dt;

        ENGINE.GetSystem<Gui>()->BeginFrame();

        m_scene->Update(dt);

        m_editor->Update();
        m_editor->ProcessGui(m_scene.get()); //.get() raw pointer

        // set cell-shading gui
        ImGui::Begin("Cel");
        ImGui::SliderInt("Levels", &m_celLevels, 1, 10);
        ImGui::SliderFloat("Specular Cutoff", &m_specularOffset, 0, 1);
        ImGui::SliderFloat("Outline", &m_outline, 0, 1);
        ImGui::ColorEdit3("Outline Color", glm::value_ptr(m_outlineColor));


        ImGui::End();

        // set program
        auto program = GET_RESOURCE(Program, "shaders/lit_phong_cel.prog");
        if (program)
        {
            //levels, specular cutoff, outline
            program->Use();
            program->SetUniform("celLevels", m_celLevels);
            program->SetUniform("celSpecularCutoff", m_specularOffset);
            program->SetUniform("celOutline", m_outline);
            program->SetUniform("celColor", m_outlineColor);
        }

        ENGINE.GetSystem<Gui>()->EndFrame();
    }

    void World08::Draw(Renderer& renderer)
    {
        // *** PASS 1 ***
        auto framebuffer = GET_RESOURCE(Framebuffer, "depth_buffer");
        renderer.SetViewport(framebuffer->GetSize().x, framebuffer->GetSize().y);
        framebuffer->Bind();
        
        renderer.ClearDepth();
        auto program = GET_RESOURCE(Program, "shaders/shadow_depth.prog");
        program->Use();
        
        auto lights = m_scene->GetComponents<LightComponent>();
        for (auto light : lights)
        {
            if (light->castShadow)
            {
                glm::mat4 shadowMatrix = light->GetShadowMatrix();
                program->SetUniform("shadowVP", shadowMatrix);
            }
        }

        auto models = m_scene->GetComponents<ModelComponent>();
        for (auto model : models)
        {
            if (model->castShadow)
            {
                //glCullFace(GL_FRONT); //remove bias with this active
                program->SetUniform("model", model->m_owner->transform.GetMatrix());
                model->model->Draw();
            }
        }

        m_scene->Draw(renderer);

        framebuffer->Unbind();

        // *** PASS 2 ***
        //m_scene->GetActorByName("postprocess")->active = true;

        renderer.ResetViewport();
        renderer.BeginFrame();
        m_scene->Draw(renderer);

        //m_scene->GetActorByName("postprocess")->Draw(renderer);

        ENGINE.GetSystem<Gui>()->Draw();

        // post-render
        renderer.EndFrame();
    }
}
