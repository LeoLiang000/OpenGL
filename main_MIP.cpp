﻿//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include "shader_m.h"
//#include "camera.h"
//#include "model_animation.h"
//#include "gui.h"
//
//#include <iostream>
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);
//unsigned int loadTexture(const char* path, int mipmap);
//void renderQuad();
//
//// settings
//const unsigned int SCR_WIDTH = 1280;
//const unsigned int SCR_HEIGHT = 720;
//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//float lastX = (float)SCR_WIDTH / 2.0;
//float lastY = (float)SCR_HEIGHT / 2.0;
//bool firstMouse = true;
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//int mipmap = 0;
//float bias(0);
//bool MouseButton2(false);
//float lightX(10);
//float lightY(0);
//float lightZ(1);
//
//int mipType(0);  // mipmap type
//bool isMipLinear(true);
//bool isMipNearest(false);
//bool isNonMipLinear(false);
//bool isNonMipNearest(false);
//
//
//int main()
//{
//	// glfw: initialize and configure
//	// ------------------------------
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
//#endif
//
//	// glfw window creation
//	// --------------------
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "MipMapping", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//
//	// tell GLFW to capture our mouse
//	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	// glad: load all OpenGL function pointers
//	// ---------------------------------------
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	// configure global opengl state
//	// -----------------------------
//	glEnable(GL_DEPTH_TEST);
//
//	// build and compile shaders
//	// -------------------------
//	Shader shader("assets/shaders/rendering/mip/mip.vs", "assets/shaders/rendering/mip/mip.fs");
//
//	shader.use();
//	shader.setInt("diffuseMap", 0);
//	shader.setInt("normalMap", 1);
//
//	myGUI myGui(window);
//
//	// render loop
//	// -----------
//	while (!glfwWindowShouldClose(window))
//	{
//		// per-frame time logic
//		// --------------------
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		// input
//		// -----
//		processInput(window);
//
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//// ========================================Render MipMap (start)==========================================================
//#pragma region
//		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
//		glm::mat4 view = camera.GetViewMatrix();
//		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 2.0f));
//
//		shader.use();
//		shader.setMat4("projection", projection);
//		shader.setMat4("view", view);
//		shader.setMat4("model", model);
//		shader.setVec3("viewPos", camera.Position);
//
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, loadTexture("assets/chess_board.jpg", mipType));
//
//		renderQuad();
//#pragma endregion
//// ========================================Render MipMap (end) ===========================================================
//
//
//		// ========================================IMGUI (start)==========================================================
//#pragma region
//		// Start the Dear ImGui frame
//		ImGui_ImplOpenGL3_NewFrame();
//		ImGui_ImplGlfw_NewFrame();
//		ImGui::NewFrame();
//
//		ImGui::Begin("IMGUI Editor");
//
//		// ====== UI content start ======
//
//		if (ImGui::RadioButton("Mipmap Linear", isMipLinear)) 
//		{
//			isMipLinear = true;
//			isMipNearest = false;
//			isNonMipLinear = false;
//			isNonMipNearest = false;
//			mipType = 0;
//		}
//		ImGui::SameLine();
//		if (ImGui::RadioButton("Mipmap Nearest", isMipNearest))
//		{
//			isMipLinear = false;
//			isMipNearest = true;
//			isNonMipLinear = false;
//			isNonMipNearest = false;
//			mipType = 3;
//		}
//		
//		if (ImGui::RadioButton("No Mipmap Linear", isNonMipLinear))
//		{
//			isMipLinear = false;
//			isMipNearest = false;
//			isNonMipLinear = true;
//			isNonMipNearest = false;
//			mipType = 1;
//		}
//		ImGui::SameLine();
//		if (ImGui::RadioButton("No Mipmap Nearest", isNonMipNearest))
//		{
//			isMipLinear = false;
//			isMipNearest = false;
//			isNonMipLinear = false;
//			isNonMipNearest = true;
//			mipType = 2;
//		}
//
//		// ====== UI content end ======
//
//		ImGui::End();
//		ImGui::Render();
//		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//#pragma endregion
//		// ========================================IMGUI (end) ===========================================================
//
//
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	glfwTerminate();
//	return 0;
//}
//
//// renders a 1x1 quad in NDC with manually calculated tangent vectors
//// ------------------------------------------------------------------
//unsigned int quadVAO = 0;
//unsigned int quadVBO;
//void renderQuad()
//{
//	if (quadVAO == 0)
//	{
//		// positions
//		glm::vec3 pos1(-10.0f, 10.0f, 0.0f);  // Top-left
//		glm::vec3 pos2(-10.0f, -10.0f, 0.0f); // Bottom-left
//		glm::vec3 pos3(10.0f, -10.0f, 0.0f);  // Bottom-right
//		glm::vec3 pos4(10.0f, 10.0f, 0.0f);   // Top-right
//		// texture coordinates
//		glm::vec2 uv1(0.0f, 10.0f);
//		glm::vec2 uv2(0.0f, 0.0f);
//		glm::vec2 uv3(10.0f, 0.0f);
//		glm::vec2 uv4(10.0f, 10.0f);
//		// normal vector
//		glm::vec3 nm(0.0f, 0.0f, 1.0f);
//
//		// calculate tangent/bitangent vectors of both triangles
//		glm::vec3 tangent1, bitangent1;
//		glm::vec3 tangent2, bitangent2;
//		// triangle 1
//		// ----------
//		glm::vec3 edge1 = pos2 - pos1;
//		glm::vec3 edge2 = pos3 - pos1;
//		glm::vec2 deltaUV1 = uv2 - uv1;
//		glm::vec2 deltaUV2 = uv3 - uv1;
//
//		GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
//
//		tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
//		tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
//		tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
//		tangent1 = glm::normalize(tangent1);
//
//		bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
//		bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
//		bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
//		bitangent1 = glm::normalize(bitangent1);
//
//		// triangle 2
//		// ----------
//		edge1 = pos3 - pos1;
//		edge2 = pos4 - pos1;
//		deltaUV1 = uv3 - uv1;
//		deltaUV2 = uv4 - uv1;
//
//		f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
//
//		tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
//		tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
//		tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
//		tangent2 = glm::normalize(tangent2);
//
//
//		bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
//		bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
//		bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
//		bitangent2 = glm::normalize(bitangent2);
//
//
//		float quadVertices[] = {
//			// positions            // normal         // texcoords  // tangent                          // bitangent
//			pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
//			pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
//			pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
//
//			pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
//			pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
//			pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z
//		};
//		// configure plane VAO
//		glGenVertexArrays(1, &quadVAO);
//		glGenBuffers(1, &quadVBO);
//		glBindVertexArray(quadVAO);
//		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//		glEnableVertexAttribArray(0);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0);
//		glEnableVertexAttribArray(1);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float)));
//		glEnableVertexAttribArray(2);
//		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(6 * sizeof(float)));
//		glEnableVertexAttribArray(3);
//		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float)));
//		glEnableVertexAttribArray(4);
//		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));
//	}
//	glBindVertexArray(quadVAO);
//	glDrawArrays(GL_TRIANGLES, 0, 6);
//	glBindVertexArray(0);
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		camera.ProcessKeyboard(FORWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		camera.ProcessKeyboard(BACKWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		camera.ProcessKeyboard(LEFT, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		camera.ProcessKeyboard(RIGHT, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
//		mipmap = 1;
//	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
//		mipmap = 0;
//	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
//		MouseButton2 = true;
//	else
//		MouseButton2 = false;
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	// make sure the viewport matches the new window dimensions; note that width and 
//	// height will be significantly larger than specified on retina displays.
//	glViewport(0, 0, width, height);
//}
//
//// glfw: whenever the mouse moves, this callback is called
//// -------------------------------------------------------
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//	lastX = xpos;
//	lastY = ypos;
//	if (MouseButton2)
//		camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//// ----------------------------------------------------------------------
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	camera.ProcessMouseScroll(yoffset);
//}
//
//unsigned int loadTexture(char const* path, int type)
//{
//	std::string filename = path;
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//	int width, height, nrComponents;
//	// stbi_set_flip_vertically_on_load(true);
//	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
//	if (data) {
//		GLenum format;
//		if (nrComponents == 1) {
//			format = GL_RED;
//		}
//		else if (nrComponents == 3) {
//			format = GL_RGB;
//		}
//		else if (nrComponents == 4) {
//			format = GL_RGBA;
//		}
//
//		glBindTexture(GL_TEXTURE_2D, textureID);
//		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//		switch (type) {
//		case 0: // mipmap
//			glGenerateMipmap(GL_TEXTURE_2D);
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//			break;
//		case 1: // no mipmap, gl_linear
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//			break;
//		case 2: // no mipmap, gl_nearst
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//			break;
//		case 3: // mipmap, nearst
//			glGenerateMipmap(GL_TEXTURE_2D);
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//			break;
//		}
//	}
//	else {
//		std::cout << "MODEL::Texture failed to load at path: " << path << "\n";
//	}
//	stbi_image_free(data);
//	return textureID;
//}
//
//
//
