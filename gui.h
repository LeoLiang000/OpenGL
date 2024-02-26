#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glm/gtc/type_ptr.hpp>

//float euler_r = 0.0;
float metallic(1);
float roughness(1);

bool isEuler = true;
bool isQuater = false;

class myGUI
{
public:
	myGUI(GLFWwindow* window) {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui::StyleColorsDark();   // Setup Dear ImGui style: ImGui::StyleColorsLight(); StyleColorsDark

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
        bool DrawLight = true;
        float light_pos;
        glm::vec3 light_color = glm::vec3(1, 1, 1);
        int counter(0);
	}

    void createGUI() {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Hello, Leo!");

            ImGui::Text("IMGUI Editor");

            if (ImGui::RadioButton("Euler", isEuler)) {
                isQuater = false; // Ensure only one is selected
                isEuler = true;
            }

            ImGui::SameLine();

            if (ImGui::RadioButton("Quaternion", isQuater)) {
                isEuler = false; // Ensure only one is selected
                isQuater = true;
            }

            //ImGui::SliderFloat("X Axis", &euler_r, 0.0f, 100.0f);
            //ImGui::SliderFloat("Y Axis", &_smoothness, 0.0f, 100.0f);
            //ImGui::SliderFloat("Z Axis", &_smoothness, 0.0f, 100.0f);
            //ImGui::SliderFloat("metallic", &metallic, 0.0f, 100.0f);
            //ImGui::SliderFloat("roughness", &roughness, 0.0f, 100.0f);

            //ImGui::SliderFloat("Light Position", &light_pos, 0.0f, 1.0f);
            //ImGui::ColorEdit3("Light Color", (float*)&light_color);
            //if (ImGui::Button("Button"))
            //    counter++;
            //ImGui::SameLine(); // display at same line
            //ImGui::Text("counter = %d", counter);

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void deleteBuffer() {

    }
};
