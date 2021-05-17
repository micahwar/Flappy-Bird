#pragma once

#include "Renderer.h"
#include "Camera.h"
#include "Shape.h"
#include "Shader.h"
#include "Texture.h"
#include "glm/gtc/matrix_transform.hpp"
#include <memory>


class Engine
{
private:
	int m_Width, m_Height;
	float m_Rotation;
	glm::mat4 m_Proj, m_View;
	Renderer m_Renderer;
	Camera m_Camera;
	std::unordered_map<int, std::unique_ptr<VertexArray>> m_VAO;
	std::unordered_map<int, std::unique_ptr<VertexBuffer>> m_VBO;
	std::unique_ptr<IndexBuffer> m_IBO;

	std::unique_ptr<Shader> m_FlatColorShader;
	std::unique_ptr<Shader> m_TextureShader;
public:
	Engine(int w, int h);
	~Engine();

	void Clear();
	void Background(int rgb);
	void Background(Texture* texture);
	void Background(int r, int g, int b);
	void SetDrawColor(int rgb);
	void SetDrawColor(int r, int g, int b);
	//void Rect(int x, int y, int w, int h);
	void Rect(Shape* shape, int id);
	void Rect(Shape* shape, int id, Texture* texture);
	void Rotate(float angle);
	void SetRotate(float angle);
	void PushRect(Shape rect);
	void DrawBuffer();
	int GetWidth();
	int GetHeight();
	Camera GetCamera();
	int GetCameraX();
	int GetCameraY();
	void MoveCamera(int x);
	Texture* LoadImage(std::string& filepath);
private:
	float NormaliseRGB(int c);
	void PerformDrawRect(Shader& shader, glm::mat4& mvp, int id);
	void PerformDrawRect(Shader& shader, Texture& texture, glm::mat4& mvp, int id);
};