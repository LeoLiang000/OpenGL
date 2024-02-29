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


// ========================================initialize (start)==========================================================
#pragma region
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);


// window settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


// camera
Camera camera(glm::vec3(0.0f, 0.0f, 100.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
	Shader dShader("assets/shaders/shader_ani.vs", "assets/shaders/shader_ani.fs");
	Shader sShader("assets/shaders/shader.vs", "assets/shaders/shader.fs");

	Model ufoModel("assets/models/plane/plane.obj");  	// load ufo model

	float angle = 0.0f; // 初始化角度变量
	float radius = 50.0f; // 圆形轨迹的半径




	stbi_set_flip_vertically_on_load(true); // other models flip

	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#pragma endregion
// ========================================init shaders & models (end) ===========================================================


	// ========================================init render loop (start)==========================================================
#pragma region

	// render loop
	while (!glfwWindowShouldClose(window))
	{
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
#pragma endregion
		// ========================================init render loop (end) ===========================================================

		// ========================================draw ufo model (start)==========================================================
#pragma region
		sShader.use();
		glm::mat4 projection_ufo = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		glm::mat4 view_ufo = camera.GetViewMatrix();
		sShader.setMat4("projection", projection_ufo);
		sShader.setMat4("view", view_ufo);

		float timeValue = glfwGetTime();

		glm::mat4 model_ufo = glm::mat4(1.0f);
		model_ufo = glm::translate(model_ufo, glm::vec3(-3.0f, 7.0f, -2.0f)); // translate it down so it's at the center of the scene
		model_ufo = glm::scale(model_ufo, glm::vec3(.5f, .5f, .5f));	// it's a bit too big for our scene, so scale it down
		model_ufo = glm::rotate(model_ufo, timeValue * glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		// 更新模型矩阵，此处只改变位置
		model_ufo = glm::translate(model_ufo, glm::vec3(0.0, 0.0, 0.0));

		sShader.setMat4("model", model_ufo);
		//lightShader.setMat4("model", model_ufo);
		ufoModel.Draw(sShader);

#pragma endregion
		// ========================================draw ufo model (end) ===========================================================


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
