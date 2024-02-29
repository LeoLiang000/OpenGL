//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include "shader_m.h"
//#include "camera.h"
//#include "animator.h"
//#include "model_animation.h"
//#include <iostream>
//
//// ========================================initialize (start)==========================================================
//#pragma region
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);
//unsigned int loadCubemap(vector<std::string> faces);
//static float randomFloat() {
//	float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
//	return r;
//}
//
//// window settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 100.0f));
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//bool MouseButton2(false);
//static glm::vec3 originalEyeCenter(0, 0, 100);
//static glm::vec3 eyeCenter = originalEyeCenter;
//static glm::vec3 lookat(0, 0, 0);
//static glm::vec3 up(0, 5, 0);
//
//static glm::float32 FoV = 45;
//static glm::float32 zNear = 0.1f;
//static glm::float32 zFar = 10000.0f;
//
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//static float ipd = 10.0f;				// Distance between left/right eye.
//glm::mat4 leftViewMatrix;
//glm::mat4 rightViewMatrix;
//
//enum AnaglyphMode {
//	None,
//	ToeIn,
//	Asymmetric,
//	AnaglyphModeCount,
//};
//
//static std::string strAnaglyphMode[] = {
//	"None",
//	"Toe-in",
//	"Asymmetric view frustum",
//	"Invalid",
//};
//
//static AnaglyphMode anaglyphMode = AnaglyphMode::None;
//
//// Helper functions 
//
//static void nextAnaglyphMode() {
//	anaglyphMode = (AnaglyphMode)(((int)anaglyphMode + 1) % (int)AnaglyphModeCount);
//}
//
//static int randomInt() {
//	return rand();
//}
//
//
//static glm::vec3 randomVec3() {
//	return glm::vec3(randomFloat(), randomFloat(), randomFloat());
//}
//
//static void printAnaglyphMode() {
//	std::cout << "Anaglyph mode: " << strAnaglyphMode[(int)anaglyphMode] << std::endl;
//}
//
//#pragma endregion
//// ========================================initialize (end) ===========================================================
//
//int main()
//{
//	// ========================================init (start)==========================================================
//#pragma region
//	// glfw: initialize and configure
//	// ------------------------------
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//	// glfw window creation
//	// --------------------
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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
//	// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
//	stbi_set_flip_vertically_on_load(true);
//
//	// configure global opengl state
//	// -----------------------------
//	glEnable(GL_DEPTH_TEST);
//
//#pragma endregion
//	// ========================================init (end) ===========================================================
//
//	// ========================================init shaders & models (start)==========================================================
//#pragma region
//
//	// build and compile shaders
//	Shader sShader("assets/shaders/shader.vs", "assets/shaders/shader.fs");
//	Model buildingModel("assets/models/building/Castle OBJ.obj");  	// load ufo model
//	stbi_set_flip_vertically_on_load(true); // other models flip
//
//	// draw in wireframe
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//#pragma endregion
//// ========================================init shaders & models (end) ===========================================================
//
//	stbi_set_flip_vertically_on_load(true); // other models flip
//
//#pragma endregion
//// ========================================skybox (end) ===========================================================
//	// random scale factor
//	float scaleX = randomFloat();
//	float scaleY = 2.5 * randomFloat();
//	glm::mat4 projectionMatrix = glm::perspective(glm::radians(FoV), (float)SCR_WIDTH / SCR_HEIGHT, zNear, zFar);
//	printAnaglyphMode();
//
//	// 3D stereo
//
//
//
//
//
//
//
//
//
//
//	// ========================================init render loop (start)==========================================================
//#pragma region
//
//
//
//	// render loop
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
//		// render
//		// ------
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//#pragma endregion
//		// ========================================init render loop (end) ===========================================================
//		
//// ========================================draw building model (start)==========================================================
//#pragma region
//		glm::mat4 projection_ufo = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000000.0f);
//		glm::mat4 view_ufo = camera.GetViewMatrix();
//		glm::mat4 model_plane = glm::mat4(1.0f);
//
//		sShader.use();
//		sShader.setMat4("projection", projection_ufo);
//		sShader.setMat4("view", view_ufo);
//
//		// generate virtual city
//		for (int z = -4; z <= 2; ++z) {
//			for (int x = -4; x <= 4; ++x) {
//				//Building b;
//				if (x == 0 && z == 0) {
//					// tallest building
//					model_plane = glm::translate(model_plane, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
//					model_plane = glm::scale(model_plane, glm::vec3(1.5f, 2.5f, 1.5f));
//					sShader.setMat4("model", model_plane);
//					buildingModel.Draw(sShader);
//				}
//				else {
//					model_plane = glm::translate(model_plane, glm::vec3(10 * x + 50.0f, 0.0f, 10 * z + 30.0f)); // translate it down so it's at the center of the scene
//					model_plane = glm::scale(model_plane, glm::vec3(1.5f, scaleY, 1.5f));
//					sShader.setMat4("model", model_plane);
//					buildingModel.Draw(sShader);
//				}
//			}
//		}
//
//
//#pragma endregion
//// ========================================draw building model (end) ===========================================================
//
//// ========================================end render loop (start)==========================================================
//#pragma region
//// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//// -------------------------------------------------------------------------------
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	// glfw: terminate, clearing all previously allocated GLFW resources.
//	// ------------------------------------------------------------------
//	glfwTerminate();
//	return 0;
//
//#pragma endregion
//	// ========================================end render loop (end) ===========================================================
//}
//
//// ========================================process mouse and keyboard (start)==========================================================
//#pragma region
//
//void processInput(GLFWwindow* window)
//{
//	// Basic
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		camera.ProcessKeyboard(FORWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		camera.ProcessKeyboard(BACKWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		camera.ProcessKeyboard(LEFT, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		camera.ProcessKeyboard(RIGHT, deltaTime);
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
//	//cout << "mouse position: " << "x=" << lastX << ", y=" << lastY << endl;
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
//#pragma endregion
//// ========================================process mouse and keyboard (end) ===========================================================
//// ========================================load cube (start)==========================================================
//#pragma region
//unsigned int loadCubemap(vector<std::string> faces)
//{
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
//
//	int width, height, nrComponents;
//	for (unsigned int i = 0; i < faces.size(); i++)
//	{
//		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
//		if (data)
//		{
//			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//			stbi_image_free(data);
//			cout << "successfully loaded image: " << faces[i].c_str() << endl;
//		}
//		else
//		{
//			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
//			stbi_image_free(data);
//		}
//	}
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//
//	return textureID;
//}
//#pragma endregion
//// ========================================load cube (end) ===========================================================
