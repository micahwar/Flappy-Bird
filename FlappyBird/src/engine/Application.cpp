#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "GLErrorManager.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl_gl3.h"

#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"
//prolly won't work
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Cool Sexy Rectangle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        return -1;

    GLCall(std::cout << glGetString(GL_VERSION) << std::endl);
    {
        //float positions[] = {
        //    -50.0f, -50.0f, 0.0f, 0.0f,
		//	 50.0f, -50.0f, 1.0f, 0.0f,
        //     50.0f,  50.0f, 1.0f, 1.0f,
        //    -50.0f,  50.0f, 0.0f, 1.0f
        //};

        //uint32_t indices[] = {
        //    0, 1, 2,
        //    2, 3, 0
        //};

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

       
        //VertexArray va;
        //VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        //VertexBufferLayout layout;
        //layout.Push<float>(2);
        //layout.Push<float>(2);
        //va.AddBuffer(vb, layout);

        //IndexBuffer ib(indices, 6);

        //glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        //glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
        //glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));
        
        //glm::mat4 mvp = proj * view * model;

        //Shader shader("res/shaders/Basic.glsl");
        //shader.Bind();
        //shader.SetUniform4f("u_Color", 0.4f, 0.0f, 0.8f, 1.0f);

        //Texture texture("res/textures/house.png");
        //texture.Bind(0);
        //shader.SetUniform1i("u_Texture", 0);

        //va.Unbind();
        //vb.Unbind();
        //ib.Unbind();
        //shader.Unbind();

        Renderer renderer;
        
        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();
        
		//glm::vec3 translationA(200, 200, 0);
		//glm::vec3 translationB(400, 200, 0);
        //float r = 0.0f;
        //float increment = 0.05f;
        test::Test* currentTest = nullptr;
        test::TestMenu* testMenu = new test::TestMenu(currentTest);
        currentTest = testMenu;
        
        testMenu->RegisterTest<test::TestClearColor>("Clear Color");
        testMenu->RegisterTest<test::TestTexture2D>("Texture2D");
        
        while (!glfwWindowShouldClose(window))
        {
			GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
            renderer.Clear();
			
			test.OnUpdate(0.0f);
			test.OnRender();
			
			ImGui_ImplGlfwGL3_NewFrame();
			
			if (currentTest)
			{
				currentTest->OnUpdate(0.0f);
				currentTest->OnRender();
				ImGui::Begin("Test");
				if (currentTest != testMenu && ImGui::Button("<-"))
				{
					delete currentTest;
					currentTest = testMenu;
				}
				currentTest->OnImGuiRender();
				ImGui::End();
			}
			
			test.OnImGuiRender();
			
            //shader.SetUniform4f("u_Color", r, 0.0f, 0.8f, 1.0f);
            //shader.Bind();
            //{
			//	glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
			//	glm::mat4 mvp = proj * view * model;
			//	shader.SetUniformMat4f("u_MVP", mvp);
				
			//	renderer.Draw(va, ib, shader);
			//}
            //{
			//	glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
			//	glm::mat4 mvp = proj * view * model;
			//	shader.SetUniformMat4f("u_MVP", mvp);
				
			//	renderer.Draw(va, ib, shader);
			//}

            //if (r > 1.0f)
            //    increment = -0.05f;
            //else if (r < 0.0f)
            //    increment = 0.05f;

            //r += increment;
			
			//{
			//	ImGui::SliderFloat("float", &translationA.x, 0.0f, 960.0f);
			//	ImGui::SliderFloat("float", &translationB.x, 0.0f, 960.0f);
			//	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			//}
			ImGui::Render();
        
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
			
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
		delete currentTest;
		if (currentTest != testMenu)
			delete testMenu;
    }
    
    
    
    ImGui_ImpleGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}