#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_m.h"
#include "camera.h"
#include "model_animation.h"
#include <iostream>
#include "LightDirectional.h"
#include "gui.h"
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;
using namespace glm;
// ========================================initialize (start)==========================================================
#pragma region
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
unsigned int loadCubemap(vector<std::string> faces);
unsigned int LoadTextureImageToGPU(const char* filename, GLint internalFormat, GLenum format, int textureSlot);
unsigned int loadTexture(const char* path);
float limitValue(float value, float min_value, float max_value);
void updatePosition();
glm::vec3 hermiteInterpolate(const glm::vec3& p0, const glm::vec3& t0, const glm::vec3& p1, const glm::vec3& t1, float t);
glm::vec3 lerp(const glm::vec3& start, const glm::vec3& end, float t);
float easeInOut(float t);
void ccd(glm::vec3 PosTgt);
// window settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
bool MouseButton2(false);

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 100.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int screenWidth = 800;
int screenHeight = 600;
int cursorPosX = screenWidth / 2;
int cursorPosY = screenHeight / 2;

float posx(0.0f);
float posy(0.0f);
float posz(0.0f);

float theta_1;  // bone 1 rotation
float theta_2;  // bone 2 rotation

float posX(10.0);
float posY(10.0);
float posZ(5.0);

bool is2D(true);
bool is3D(false);
bool is3DSpline(false);
float endDistance(0.2);

float L1 = 2.5;																	// bone 1 length
float L2 = 2.5;																	// bone 2 length
float L3 = 2.5;																	// bone 3 length

float currentTimeCCD = 0.0f;														// Current time in the animation



glm::mat4 trans;
glm::mat4 modelMat;
glm::mat4 viewMat;
glm::mat4 projMat;
//projMat = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, -100.0f, 100.0f);  // same size regardless of distacne from camera

glm::vec3 rotAxis;
glm::quat rot;

glm::vec3 PosL1 = glm::vec3(0.0f);					// bone 1 position
glm::vec3 PosL2 = glm::vec3(0.0f);					// bone 2 position
glm::vec3 PosL3 = glm::vec3(0.0f);					// bone 3 position
glm::vec3 PosEnd = glm::vec3(0.0f);					// end-effector position					

glm::quat QuatL1 = glm::angleAxis(glm::radians(0.01f), glm::vec3(1.0f, 0.0f, 0.0f));
glm::quat QuatL2 = glm::angleAxis(glm::radians(0.01f), glm::vec3(1.0f, 0.0f, 0.0f));
glm::quat QuatL3 = glm::angleAxis(glm::radians(0.01f), glm::vec3(1.0f, 0.0f, 0.0f));

glm::mat4 rotMat1(1.0f);
glm::mat4 rotMat2(1.0f);
glm::mat4 rotMat3(1.0f);

// Define a set of control points for the spline
std::vector<glm::vec3> controlPoints = {
	glm::vec3(0, 0, 0),   // Starting position
	glm::vec3(2, 5, -1),  // First control point
	glm::vec3(5, 10, 0),  // Second control point
	glm::vec3(10, 5, 1),  // Third control point
	glm::vec3(15, 0, 0)   // Ending position
};

float totalDuration = 5.0f;														// Total duration of the Hermite curve animation



float limitValue(float value, float min_value, float max_value) {
	return std::max(min_value, std::min(value, max_value));
}

#pragma endregion
// ========================================initialize (end) ===========================================================

int main()
{
	// ========================================init (start)==========================================================
#pragma region
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	GLFWcursor* crosshairCursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
	glfwSetCursor(window, crosshairCursor);

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
	//stbi_set_flip_vertically_on_load(true);

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// change cursor appearance
	if (is2D)
	{

	}


#pragma endregion
	// ========================================init (end) ===========================================================

	// ========================================init shaders & models (start)==========================================================
#pragma region

	Shader shader("assets/shaders/Animation/kinematic/normal_map.vs", "assets/shaders/Animation/kinematic/normal_map.fs");
	Shader shaderBall("assets/shaders/Animation/kinematic/ball.vs", "assets/shaders/Animation/kinematic/ball.fs");

	Model boneModel("assets/models/bone/bone4/bone.obj");
	Model boneModel2("assets/models/bone/bone4/bone.obj");
	Model boneModel3("assets/models/bone/bone4/bone.obj");
	Model targetBall("assets/models/ball/ball.obj");


	stbi_set_flip_vertically_on_load(true); // other models flip

#pragma endregion

// ========================================init shaders & models (end) ===========================================================
#pragma region Prepare MVP matrices

#pragma endregion

	// initialize IMG UI
	myGUI myGui(window);
// ========================================init render loop (start)==========================================================
#pragma region

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		//float currentTime = glfwGetTime();
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glViewport(0, 0, 1400, 1000);

#pragma endregion
// ========================================IK Bone Setting (end) ===========================================================



// ========================================draw bone (start)==========================================================
#pragma region
		
		if (is2D)
		{

			// cursor position
			posX = (cursorPosX - (screenWidth / 2)) / float(screenWidth / 2) * 3.5f;
			posY = -(cursorPosY - (screenHeight / 2)) / float(screenHeight / 2) * 3.5f;  // minus symbol check

			float L1 = 2.5;																			// bone 1 length
			float L2 = 1.5;																			// bone 2 length
			float L3 = 1.5;																			// bone 3 length

			// IK analytical solution
			float d = std::sqrt(posX * posX + posY * posY);											// distance of target to origin 
			float theta_T = std::acos(posX / d);													// angle for target point with respect to axis-x
			float tmpCos_1T = limitValue((L1 * L1 + d * d - L2 * L2) / (2 * L1 * d), -1.0f, 1.0f);  // cos(theta1 - thetaT), clamp range into [-1, 1]
			float tmpCos_2 = limitValue(-(L1 * L1 + L2 * L2 - d * d) / (2 * L1 * L2), -1.0f, 1.0f); // cos(theta2), clamp range into [-1, 1]
			float tempTheta_1 = std::acos(tmpCos_1T);												// convert to radian
			float tempTheta_2 = std::acos(tmpCos_2);												// convert to radian

			// target point is over distance of sum length of two bones
			if (d > (L1 + L2))  
			{
				theta_1 = std::atan2(posY, posX);
				theta_2 = 0;
			}
			// normal case
			else if (posY > 0)
			{
				theta_1 = tempTheta_1 + theta_T;
				theta_2 = -tempTheta_2;
			}
			else
			{
				theta_1 = -(theta_T - tempTheta_1);
				theta_2 = -tempTheta_2;
			}

			projMat = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, -100.0f, 100.0f);  // same size regardless of distacne from camera

			// bone 1
			glm::mat4 rotMat = glm::scale(glm::mat4(1.0f), glm::vec3(5.0f));
			rotMat = glm::rotate(rotMat, theta_1, glm::vec3(0.0f, 0.0f, 1.0f));
			glm::mat4 modelBone1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
			modelBone1 = modelBone1 * rotMat;  // rotate first, then translate

			shader.use();
			shader.setMat4("projection", projMat);
			shader.setMat4("view", camera.GetViewMatrix());
			shader.setVec3("viewPos", camera.Position);
			shader.setMat4("model", modelBone1);
			boneModel.Draw(shader);

			// bone 2 (hierarchical structure: rotate at pivot point)
			glm::mat4 transBone2 = glm::translate(rotMat, glm::vec3(L1, 0.0f, 0.0f));
			transBone2 = glm::rotate(transBone2, theta_2, glm::vec3(0.0f, 0.0f, 1.0f));
			glm::mat4 modelBone2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
			modelBone2 = modelBone2 * transBone2;
			shader.setMat4("model", modelBone2);
			boneModel2.Draw(shader);

			// target ball
			shaderBall.use();
			shaderBall.setMat4("projection", projMat);
			shaderBall.setMat4("view", camera.GetViewMatrix());
			shaderBall.setVec3("viewPos", camera.Position);
			modelMat = translate(mat4(1.0f), vec3(lastX, lastY, 0.0f));
			shaderBall.setMat4("model", modelMat);
			targetBall.Draw(shaderBall);
		}
		else if(is3D)
		{
			glm::vec3 PosTgt = glm::vec3(posX, posY, posZ);
			projMat = glm::perspective(glm::radians(45.0f), 1400.0f / 1000.0f, 0.1f, 10000.0f);
			
			ccd(PosTgt);  // move end-effector to target point
			
			// draw bone1
			trans = rotMat1;
			modelMat = translate(mat4(1.0f), PosL1);

			shader.use();
			shader.setMat4("projection", projMat);
			shader.setMat4("view", camera.GetViewMatrix());
			shader.setVec3("viewPos", camera.Position);
			shader.setMat4("model", modelMat * trans);
			boneModel.Draw(shader);

			// draw bone2
			trans *= rotMat2;
			modelMat = translate(mat4(1.0f), PosL2);
			shader.setMat4("model", modelMat * trans);
			boneModel2.Draw(shader);

			// draw bone3
			trans *= rotMat3;
			modelMat = translate(mat4(1.0f), PosL3);
			shader.setMat4("model", modelMat * trans);
			boneModel3.Draw(shader); 

			// draw target ball
			shaderBall.use();
			shaderBall.setMat4("projection", projMat);
			shaderBall.setMat4("view", camera.GetViewMatrix());
			shaderBall.setVec3("viewPos", camera.Position);
			modelMat = translate(mat4(1.0f), PosTgt);
			shaderBall.setMat4("model", modelMat);
			targetBall.Draw(shaderBall);
		}
		else if (is3DSpline)
		{
			glm::vec3 PosTgt;																// target point

			currentTimeCCD += deltaTime;
			if (currentTimeCCD > totalDuration)
			{
				ccd(PosEnd);
				currentTimeCCD = 0.0f;
			}
				
			float t = currentTimeCCD / totalDuration;
			float easedT = easeInOut(t);
			glm::vec3 startPos = glm::vec3(6.0f, 2.0f, 5.0f);								// Starting position of the Hermite curve
			glm::vec3 endPos = glm::vec3(-0.3f, -0.6f, -1.0f);								// Ending position of the Hermite curve
			PosTgt = lerp(startPos, endPos, easedT);										// interpolate new points
			ccd(PosTgt);																	// ccd to target point

			// draw bone1
			projMat = glm::perspective(glm::radians(45.0f), 1400.0f / 1000.0f, 0.1f, 10000.0f);

			trans = rotMat1;
			modelMat = translate(mat4(1.0f), PosL1);

			shader.use();
			shader.setMat4("projection", projMat);
			shader.setMat4("view", camera.GetViewMatrix());
			shader.setVec3("viewPos", camera.Position);
			shader.setMat4("model", modelMat * trans);
			boneModel.Draw(shader);

			// draw bone2
			trans *= rotMat2;
			modelMat = translate(mat4(1.0f), PosL2);
			shader.setMat4("model", modelMat * trans);
			boneModel2.Draw(shader);

			// draw bone3
			trans *= rotMat3;
			modelMat = translate(mat4(1.0f), PosL3);
			shader.setMat4("model", modelMat * trans);
			boneModel3.Draw(shader);

			// draw target ball
			shaderBall.use();
			shaderBall.setMat4("projection", projMat);
			shaderBall.setMat4("view", camera.GetViewMatrix());
			shaderBall.setVec3("viewPos", camera.Position);
			modelMat = translate(mat4(1.0f), PosTgt);
			shaderBall.setMat4("model", modelMat);
			targetBall.Draw(shaderBall);
		}



#pragma endregion
// ========================================draw bone (end) ===========================================================


// ========================================IMGUI (start)==========================================================
#pragma region
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("IMGUI Editor");

		// ====== UI content start ======
		if (ImGui::RadioButton("2D", is2D)) 
		{
			is3D = false; // Ensure only one is selected
			is2D = true;
			is3DSpline = false;
		}
		ImGui::SameLine();
		if (ImGui::RadioButton("3D", is3D)) 
		{
			is2D = false; // Ensure only one is selected
			is3D = true;
			is3DSpline = false;
		}
		ImGui::SameLine();
		if (ImGui::RadioButton("3D Spline", is3DSpline))
		{
			is2D = false; // Ensure only one is selected
			is3D = false;
			is3DSpline = true;
		}

		if (is3D)
		{
			ImGui::SliderFloat("Ending Distance", &endDistance, 0.001f, 10.0f);
			//ImGui::SliderInt("Iteration Times", &iterNum, 1000, 6000);
			ImGui::SliderFloat("PosX", &posX, -50.0f, 50.0f);
			ImGui::SliderFloat("PosY", &posY, -50.0f, 50.0f);
			ImGui::SliderFloat("PosZ", &posZ, -50.0f, 50.0f);
		}
		if (is3DSpline)
		{
			ImGui::SliderFloat("Ending Distance", &endDistance, 0.0001f, .4f);
			ImGui::SliderFloat("Total Duration", &totalDuration, 0.5f, 10.0f);

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
	// UI
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

	cursorPosX = xpos;
	cursorPosY = ypos;

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


unsigned int loadCubemap(vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			std::cout << "Cubemap tex succeeded to load at path: " << faces[i] << std::endl;
		}
		else
		{
			std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
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

unsigned int LoadTextureImageToGPU(const char* filename, GLint internalFormat, GLenum format, int textureSlot)
{
	unsigned int TexBuffer;
	glGenTextures(1, &TexBuffer);

	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, TexBuffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannel;
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannel, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Texture image " << filename << " load failed." << endl;
	}
	stbi_image_free(data);

	//cout << filename << "Slot:  " << TexBuffer << endl;

	return TexBuffer;
}

unsigned int loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

// bones hierarchical structure
void updatePosition()
{
	PosL2 = glm::mat3(rotMat1) * glm::vec3(L1, 0.0f, 0.0f) + PosL1;					// bone 2 start position
	PosL3 = glm::mat3(rotMat1 * rotMat2) * glm::vec3(L2, 0.0f, 0.0f) + PosL2;		// bone 3 start position
	PosEnd = mat3(rotMat1 * rotMat2 * rotMat3) * vec3(L3, 0.0f, 0.0f) + PosL3;		// end-effector start position
}


glm::vec3 lerp(const glm::vec3& start, const glm::vec3& end, float t) {
	return start + t * (end - start);
}

// Ease-In-Ease-Out function
float easeInOut(float t) {
	return t < 0.5 ? 2 * t * t : -1 + (4 - 2 * t) * t;
}

void ccd(glm::vec3 PosTgt)
{
	updatePosition();																// update bone positions after rotated

	int iterNum = 3000;																// max iteration times
	while (--iterNum)
	{
		if (distance(PosTgt, PosEnd) < endDistance) break;

		glm::vec3 vecP2E;															// vector point to end-effector
		glm::vec3 vecP2T;															// vector point to target point

		// 1. rotate bone3 to target point
		vecP2E = normalize(PosEnd - PosL3);											// bone3 -> end-effector
		vecP2T = normalize(PosTgt - PosL3);											// bone3 -> target
		float theta = acos(limitValue(dot(vecP2E, vecP2T), -1, 1));					// rotation theta
		rotAxis = normalize(cross(vecP2T, vecP2E));									// rotation axis
		rotMat3 = glm::rotate(rotMat3, theta, rotAxis);

		updatePosition();															// update bone positions after rotated
		if (distance(PosTgt, PosEnd) < endDistance) break;

		// 2. rotate bone2 to target point
		vecP2E = normalize(PosEnd - PosL2);											// bone2 -> end-effector
		vecP2T = normalize(PosTgt - PosL2);											// bone2 -> target
		theta = acos(limitValue(dot(vecP2E, vecP2T), -1, 1));						// rotation theta
		rotAxis = normalize(cross(vecP2T, vecP2E));									// rotation axis
		rotMat2 = glm::rotate(rotMat2, theta, rotAxis);

		updatePosition();															// update bone positions after rotated
		if (distance(PosTgt, PosEnd) < endDistance) break;

		// 3. rotate bone1 to target point
		vecP2E = normalize(PosEnd - PosL1);											// bone1 -> end-effector
		vecP2T = normalize(PosTgt - PosL1);											// bone1 -> target
		theta = acos(limitValue(dot(vecP2E, vecP2T), -1, 1));						// rotation theta
		rotAxis = normalize(cross(vecP2T, vecP2E));									// rotation axis
		rotMat1 = glm::rotate(rotMat1, theta, rotAxis);

		updatePosition();
		if (distance(PosTgt, PosEnd) < endDistance) break;

	}
}