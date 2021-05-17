#include "Engine.h"
#include "GLErrorManager.h"
#include "glm/glm.hpp"
#include <iostream>
#include <glm/gtx/rotate_vector.hpp>

Engine::Engine(int w, int h)
	: m_Width(w), m_Height(h), m_Camera(300, 0), m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f))
{
	m_View = (glm::translate(glm::mat4(1.0f), glm::vec3(m_Camera.GetX(), m_Camera.GetY(), 0)));
	//m_View = (glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)));
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	m_FlatColorShader = std::make_unique<Shader>("res/shaders/Basic.glsl");
	m_TextureShader = std::make_unique<Shader>("res/shaders/Textured.glsl");
	SetDrawColor(0);

	uint32_t indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	m_IBO = std::make_unique<IndexBuffer>(indices, 6);
}

Engine::~Engine()
{
}

void Engine::MoveCamera(int x)
{
	m_Camera.Move(x);
	m_View = (glm::translate(glm::mat4(1.0f), glm::vec3(m_Camera.GetX(), m_Camera.GetY(), 0)));
}

Texture* Engine::LoadImage(std::string& filepath)
{
	return new Texture(filepath);
}

void Engine::Clear()
{
	m_Renderer.Clear();
}

void Engine::Background(int rgb)
{
	float nrgb = NormaliseRGB(rgb);
	GLCall(glClearColor(nrgb, nrgb, nrgb, 1.0f));
}

void Engine::Background(Texture* texture)
{
	//std::cout << m_Camera.GetX() << std::endl;
	Shape shape = Shape(0 - m_Camera.GetX(), 0, 960, 540);
	Rect(&shape, 10, texture);
}

void Engine::Background(int r, int g, int b)
{
	GLCall(glClearColor(NormaliseRGB(r), NormaliseRGB(g), NormaliseRGB(b), 1.0f));
}

void Engine::SetDrawColor(int rgb)
{
	float nrgb = NormaliseRGB(rgb);
	m_FlatColorShader->Bind();
	m_FlatColorShader->SetUniform4f("u_Color", nrgb, nrgb, nrgb, 1.0f);
}

void Engine::SetDrawColor(int r, int g, int b)
{
	m_FlatColorShader->Bind();
	m_FlatColorShader->SetUniform4f("u_Color", NormaliseRGB(r), NormaliseRGB(g), NormaliseRGB(b), 1.0f);
}

//void Engine::Rect(int x, int y, int w, int h)
//{
//}

void Engine::Rect(Shape* shape, int id)
{
	if (m_VAO.find(id) == m_VAO.end())
	{
		float positions[] = {
			 0.0f,  0.0f,
			(float)shape->w,  0.0f,
			(float)shape->w, (float)shape->h,
			 0.0f, (float)shape->h
		};

		m_VAO[id] = (std::make_unique<VertexArray>());
		m_VBO[id] = (std::make_unique<VertexBuffer>(positions, 4 * 2 * sizeof(float)));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		m_VAO[id]->AddBuffer(*(m_VBO[id]), layout);
	}
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(shape->x, shape->y, 1.0f));
	glm::mat4 mvp = m_Proj * m_View * glm::rotate(model, m_Rotation, glm::vec3(0, 0, 1));
	m_FlatColorShader->SetUniformMat4f("u_MVP", mvp);

	m_Renderer.Draw(*(m_VAO[id]), *m_IBO, *m_FlatColorShader);
}

void Engine::Rect(Shape* shape, int id, Texture* texture)
{
	if (m_VAO.find(id) == m_VAO.end())
	{
		float positions[] = {
			 0.0f,  0.0f, 0.0f, 0.0f,
			(float)shape->w,  0.0f, 1.0f, 0.0f,
			(float)shape->w, (float)shape->h, 1.0f, 1.0f,
			 0.0f, (float)shape->h, 0.0f, 1.0f
		};

		m_VAO[id] = (std::make_unique<VertexArray>());
		m_VBO[id] = (std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float)));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		m_VAO[id]->AddBuffer(*(m_VBO[id]), layout);
	}
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(shape->x, shape->y, 1.0f));
	glm::mat4 mvp = m_Proj * m_View * glm::rotate(model, m_Rotation, glm::vec3(0, 0, 1));
	
	m_TextureShader->Bind();
	texture->Bind();
	m_TextureShader->SetUniformMat4f("u_MVP", mvp);
	m_TextureShader->SetUniform1i("u_Texture", 0);
	m_Renderer.Draw(*(m_VAO[id]), *m_IBO, *m_TextureShader);
}

void Engine::Rotate(float angle)
{
	m_Rotation += angle;
}

void Engine::SetRotate(float angle)
{
	m_Rotation = angle;
}

//void Engine::PushRect(Shape rect)
//{
//}
//
//void Engine::DrawBuffer()
//{
//}

int Engine::GetWidth()
{
	return m_Width;
}

int Engine::GetHeight()
{
	return m_Height;
}

int Engine::GetCameraX()
{
	return m_Camera.GetX();
}

int Engine::GetCameraY()
{
	return m_Camera.GetY();
}

float Engine::NormaliseRGB(int c)
{
	return 0.0f + ((1.0f - 0.0f) / (255.0f - 0.0f)) * (c - 0.0f);
}

Camera Engine::GetCamera()
{
	return m_Camera;
}