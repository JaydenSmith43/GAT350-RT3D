#include "World01.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"

namespace nc
{
    bool World01::Initialize()
    {
        //for (int i = 0; i < 50; i++)
        //{
        //    m_positions.push_back({ randomf(-1, 1), randomf(-1, 1) });
        //}
        
        return true;
    }

    void World01::Shutdown()
    {
    }

    void World01::Update(float dt)
    {
        m_angle += 360 * dt;
        m_position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_A) ? -dt : 0;
        m_position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_D) ? dt : 0;

        m_angle += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_Q) ? dt * 180 : 0;
        m_angle += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_E) ? -dt * 180 : 0;

        m_position.y += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_W) ? dt : 0;
        m_position.y += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_S) ? -dt : 0;
        m_time += dt;
    }

    void World01::Draw(Renderer& renderer)
    {
        // pre-render
        renderer.BeginFrame();
        
        // render
        glPushMatrix();
        glTranslatef(m_position.x, m_position.y, 0);

        glRotatef(m_angle, 0, 0, 1);
        //glRotatef(m_angle, 0, 1, 0);
        //glScalef((sin(m_time * 5) + 1) * 0.5f, 1, 1);
        glScalef(1, 1, 1);

        glBegin(GL_TRIANGLES);

        glColor3f(1, 0, 0);
        glVertex2f(-0.5f, -0.5f);

        glColor3f(0, 1, 0);
        glVertex2f(0, 0.5f);

        glColor3f(0, 0, 1);
        glVertex2f(0.5f, -0.5f);

        glEnd();
        glPopMatrix();

        // ship
        glPushMatrix();
        glTranslatef((sin(m_time * 5)), 0.5f, 0);
        glScalef((sin(m_time * 5) + 1) / 2, 1, 1);
        glRotatef(m_time * 360, 0, 0, 1);

        glBegin(GL_QUAD_STRIP);

        glColor3f(1, sin(m_time), 0);
        glVertex2f(-1.0f, -0.45f);

        glColor3f(1, sin(m_time), 0);
        glVertex2f(-1.0f, -0.35f);

        glColor3f(1, sin(m_time), 0);
        glVertex2f(-0.8f, -0.5f);

        glColor3f(1, sin(m_time), 0);
        glVertex2f(-0.8f, -0.2f);

        glColor3f(sin(m_time), 1, 0);
        glVertex2f(-0.2f, -0.5f);

        glColor3f(sin(m_time), 1, 0);
        glVertex2f(-0.2f, -0.2f);



        glColor3f(1, sin(m_time), 0);
        glVertex2f(0.4f, -0.8f);

        glColor3f(1, sin(m_time), 0);
        glVertex2f(0.4f, 0.1f);

        glEnd();

        glPopMatrix();
        
        // post-render
        renderer.EndFrame();
    }
}
