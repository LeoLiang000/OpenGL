#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_m.h"
#include "camera.h"
#include "animator.h"
#include "model_animation.h"
#include <iostream>
#include "gui.h"

// ========================================initialize (start)==========================================================
#pragma region
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
unsigned int loadCubemap(vector<std::string> faces);
void render(Model buildingModel, Shader sShader, float scaleY, glm::mat4 projMat, glm::mat4 viewMat);
void twoPassRender(Model buildingModel, Shader sShader, float scaleY, glm::mat4 leftViewMat, glm::mat4 rightViewMat, glm::mat4 LeftProjMat, glm::mat4 RightProjMat = glm::mat4(1.0f), bool isFrustum = false);


static float randomFloat() {
	float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	return r;
}

// UI 
bool isNone(true);
bool isToeIn(false);
bool isFrustum(false);
float convergeDistance = 500.0f;

bool isRotate(false);

// window settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


// camera
Camera camera(glm::vec3(0.0f, 0.0f, 100.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool MouseButton2(false);
static glm::vec3 originalEyeCenter(0, 0, 100);
static glm::vec3 eyeCenter = originalEyeCenter;
static glm::vec3 lookat(0, 0, 0);
static glm::vec3 up(0, 5, 0);
static glm::float32 FoV = 45;
static glm::float32 zNear = 0.1f;
static glm::float32 zFar = 10000.0f;


// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

static float ipd = 10.0f;				// Distance between left/right eye.
glm::mat4 leftViewMatrix;
glm::mat4 rightViewMatrix;

static int randomInt() {
	return rand();
}

static glm::vec3 randomVec3() {
	return glm::vec3(randomFloat(), randomFloat(), randomFloat());
}


#pragma endregion
// ========================================initialize (end) ===========================================================

int main()
{
	// ========================================init (start)==========================================================
#pragma region
	// glfw: initialize and configure
	// ------------------------------
	camera.setMovementSpeed(50.0f);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
	stbi_set_flip_vertically_on_load(true);

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

#pragma endregion
	// ========================================init (end) ===========================================================

	// ========================================init shaders & models (start)==========================================================
#pragma region

	// build and compile shaders
	Shader sShader("assets/shaders/shader.vs", "assets/shaders/shader.fs");
	Model buildingModel("assets/models/building/Castle OBJ.obj");  	// load ufo model
	stbi_set_flip_vertically_on_load(true); // other models flip

	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#pragma endregion
// ========================================init shaders & models (end) ===========================================================

	stbi_set_flip_vertically_on_load(true); // other models flip

#pragma endregion
// ========================================skybox (end) ===========================================================
	// random scale factor
	float scaleX = randomFloat();
	float scaleY = 2.5 * randomFloat();
	// ========================================init render loop (start)==========================================================
#pragma region


	myGUI myGui(window);
	// render loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glm::mat4 projMat = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000000000.0f);
		glm::mat4 viewMat = camera.GetViewMatrix();

		// update camera parameters
		glm::vec3 cameraRight = camera.Position - glm::vec3(ipd / 2, 0.0f, 0.0f);
		glm::vec3 cameraLeft = camera.Position + glm::vec3(ipd / 2, 0.0f, 0.0f);
		glm::mat4 leftViewMat = glm::lookAt(cameraLeft, cameraLeft + camera.Front, camera.Up);
		glm::mat4 rightViewMat = glm::lookAt(cameraRight, cameraRight + camera.Front, camera.Up);

		if (isNone)
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			render(buildingModel, sShader, scaleY, projMat, viewMat);
		}
		else if (isToeIn)  // Toe-in
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			twoPassRender(buildingModel, sShader, scaleY, leftViewMat, rightViewMat, projMat);
		}
		else if (isFrustum)  // Frustum
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			float aspectRatio = static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT);
			float frustumShift = (zNear * ipd / 2) / convergeDistance;

			// Create asymmetric frustum for the left eye
			float left = -aspectRatio * zNear * tan(glm::radians(FoV) / 2.0f) + frustumShift;
			float right = aspectRatio * zNear * tan(glm::radians(FoV) / 2.0f) + frustumShift;
			float top = zNear * tan(glm::radians(FoV) / 2.0f);
			float bottom = -top;
			glm::mat4 leftProjMat = glm::frustum(left, right, bottom, top, zNear, zFar);

			// Create asymmetric frustum for the right eye
			left = -aspectRatio * zNear * tan(glm::radians(FoV) / 2.0f) - frustumShift;
			right = aspectRatio * zNear * tan(glm::radians(FoV) / 2.0f) - frustumShift;
			glm::mat4 rightProjMat = glm::frustum(left, right, bottom, top, zNear, zFar);

			twoPassRender(buildingModel, sShader, scaleY, leftViewMat, rightViewMat, leftProjMat, rightProjMat, true);
		}

#pragma endregion
// ========================================draw building model (end) ===========================================================

		// ========================================IMGUI (start)==========================================================
#pragma region
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("IMGUI Editor");

		// ====== UI content start ======

		if (ImGui::Checkbox("Model Rotating", &isRotate)) {
			if (isRotate) {
				isRotate = true;
			}
			else {
				isRotate = false;
			}
		}

		if (ImGui::RadioButton("None", isNone))
		{
			isNone = true;
			isToeIn = false;
			isFrustum = false;
		}
		ImGui::SameLine();
		if (ImGui::RadioButton("Toe-in", isToeIn))
		{
			isNone = false;
			isToeIn = true;
			isFrustum = false;
		}
		ImGui::SameLine();
		if (ImGui::RadioButton("Frustum", isFrustum))
		{
			isNone = false;
			isToeIn = false;
			isFrustum = true;
		}
		if (isFrustum)
		{
			ImGui::SliderFloat("Converge Distance", &convergeDistance, 10.0f, 800.0f);
			ImGui::SliderFloat("FOV", &FoV, 0.0f, 100.0f);
		}


		// ====== UI content end ======

		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#pragma endregion
		// ========================================IMGUI (end) ===========================================================

// ========================================end render loop (start)==========================================================
#pragma region
// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;

#pragma endregion
	// ========================================end render loop (end) ===========================================================
}

// ========================================process mouse and keyboard (start)==========================================================
#pragma region

void processInput(GLFWwindow* window)
{
	// Basic
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
		MouseButton2 = true;
	else
		MouseButton2 = false;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;
	//cout << "mouse position: " << "x=" << lastX << ", y=" << lastY << endl;
	if (MouseButton2)
		camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
#pragma endregion
// ========================================process mouse and keyboard (end) ===========================================================
// ========================================load cube (start)==========================================================
#pragma region
unsigned int loadCubemap(vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrComponents;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			cout << "successfully loaded image: " << faces[i].c_str() << endl;
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}
#pragma endregion
// ========================================load cube (end) ===========================================================

void render(Model buildingModel, Shader sShader, float scaleY, glm::mat4 projMat, glm::mat4 viewMat)
{

	glm::mat4 modelBuilding = glm::mat4(1.0f);
	if (isRotate)
	{
		float time = glfwGetTime();
		modelBuilding = glm::rotate(modelBuilding,  time * glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	sShader.use();
	sShader.setMat4("projection", projMat);
	sShader.setMat4("view", viewMat);

	// generate virtual city
	for (int z = -4; z <= 2; ++z) {
		for (int x = -4; x <= 4; ++x) {
			//Building b;
			if (x == 0 && z == 0) {
				// tallest building
				modelBuilding = glm::translate(modelBuilding, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
				modelBuilding = glm::scale(modelBuilding, glm::vec3(1.5f, 2.5f, 1.5f));
				sShader.setMat4("model", modelBuilding);
				buildingModel.Draw(sShader);
			}
			else {
				modelBuilding = glm::translate(modelBuilding, glm::vec3(10 * x + 50.0f, 0.0f, 10 * z + 30.0f)); // translate it down so it's at the center of the scene
				modelBuilding = glm::scale(modelBuilding, glm::vec3(1.5f, scaleY, 1.5f));
				sShader.setMat4("model", modelBuilding);
				buildingModel.Draw(sShader);
			}
		}
	}
}

void twoPassRender(Model buildingModel, Shader sShader, float scaleY, glm::mat4 leftViewMat, glm::mat4 rightViewMat, glm::mat4 LeftProjMat, glm::mat4 RightProjMat, bool isFrustum)
{
	// 1.red channel
	glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	render(buildingModel, sShader, scaleY, LeftProjMat, leftViewMat);

	// 2.green channel
	if (!isFrustum)
	{
		// Toe-in
		glColorMask(GL_FALSE, GL_TRUE, GL_TRUE, GL_TRUE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		render(buildingModel, sShader, scaleY, LeftProjMat, rightViewMat);

		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	}
	else
	{
		// Frustum
		glColorMask(GL_FALSE, GL_TRUE, GL_TRUE, GL_TRUE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		render(buildingModel, sShader, scaleY, RightProjMat, rightViewMat);

		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	}

}