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
//
//// ========================================default claim (start)==========================================================
//#pragma region
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);
//
//
//// window settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//#pragma endregion
//// ========================================default claim (end) ===========================================================
//
//// ========================================init camera (start)==========================================================
//#pragma region
//
//	// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 100.0f));
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//#pragma endregion
//// ========================================init camera (end) ===========================================================
//
//int main()
//{
//	// ========================================initialize (start)==========================================================
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
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
//	// ========================================initialize (end) ===========================================================
//
//	// ========================================init shaders & models (start)==========================================================
//#pragma region
//
//	// build and compile shaders
//	Shader dShader("assets/shaders/shader_ani.vs", "assets/shaders/shader_ani.fs");
//	Shader lightShader("assets/shaders/multi_lights.vs", "assets/shaders/multi_lights.fs");
//	Shader sShader("assets/shaders/shader.vs", "assets/shaders/shader.fs");
//	Shader ShaderPbr("assets/shaders/shader.vs", "assets/shaders/shader.fs");
//
//	ShaderPbr.use();
//	ShaderPbr.setVec3("albedo", 0.5f, 0.0f, 0.0f);
//	ShaderPbr.setFloat("ao", 1.0f);
//
//	glm::vec3 lightPositions[] = { glm::vec3(-10.0f,  10.0f, 10.0f) };
//	glm::vec3 lightColors[] = { glm::vec3(300.0f, 300.0f, 300.0f) };
//
//	glm::mat4 ProjectionPbr = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//	ShaderPbr.use();
//	ShaderPbr.setMat4("projection", ProjectionPbr);
//
//
//	Model ufoModel("assets/models/ufo/Low_poly_UFO.obj");  	// load ufo model
//	//Model ufoModel("assets/models/blackman/textures/nanosuit.obj");  	// load ufo model
//	//Model ufoModel("assets/models/bunny.obj");  	// load ufo model
//
//	float angle = 0.0f; // 初始化角度变量
//	float radius = 50.0f; // 圆形轨迹的半径
//
//
//
//
//	stbi_set_flip_vertically_on_load(true); // other models flip
//
//	// draw in wireframe
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//#pragma endregion
//// ========================================init shaders & models (end) ===========================================================
//
//// ========================================light (start)==========================================================
//#pragma region
//	glm::vec3 pointLightPositions[] = {
//		glm::vec3(-500.0f, 5.0f,  2.0f),
//		glm::vec3(-230.0f, 3.3f, -4.0f),
//		glm::vec3(-400.0f,  2.0f, -2.0f),
//		glm::vec3(-110.0f,  5.0f, -3.0f)
//	};
//
//	lightShader.use();
//	lightShader.setInt("material.diffuse", 0);
//	lightShader.setInt("material.specular", 1);
//#pragma endregion
//	// ========================================light (end) ===========================================================
//
//	// ========================================init render loop (start)==========================================================
//#pragma region
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
//		// ========================================light (start)==========================================================
//#pragma region
//		lightShader.use();
//		//lightShader.setVec3("light.direction", -1.0f, -1.0f, -1.0f);
//		lightShader.setVec3("viewPos", camera.Position);
//		lightShader.setFloat("material.shininess", 32.0f);
//
//		// light properties
//		// directional light
//		lightShader.setVec3("dirLight.direction", -0.5f, -4.0f, -0.5f);
//		lightShader.setVec3("dirLight.ambient", 0.3f, 0.3f, 0.3f);
//		lightShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
//		lightShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
//		// point light 1
//		lightShader.setVec3("pointLights[0].position", pointLightPositions[0]);
//		lightShader.setVec3("pointLights[0].ambient", 0.5f, 0.5f, 0.5f);
//		lightShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
//		lightShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
//		lightShader.setFloat("pointLights[0].constant", 1.0f);
//		lightShader.setFloat("pointLights[0].linear", 0.09f);
//		lightShader.setFloat("pointLights[0].quadratic", 0.032f);
//		// point light 2
//		lightShader.setVec3("pointLights[1].position", pointLightPositions[1]);
//		lightShader.setVec3("pointLights[1].ambient", 0.5f, 0.5f, 0.5f);
//		lightShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
//		lightShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
//		lightShader.setFloat("pointLights[1].constant", 1.0f);
//		lightShader.setFloat("pointLights[1].linear", 0.09f);
//		lightShader.setFloat("pointLights[1].quadratic", 0.032f);
//		// point light 3
//		lightShader.setVec3("pointLights[2].position", pointLightPositions[2]);
//		lightShader.setVec3("pointLights[2].ambient", 0.5f, 0.5f, 0.5f);
//		lightShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
//		lightShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
//		lightShader.setFloat("pointLights[2].constant", 1.0f);
//		lightShader.setFloat("pointLights[2].linear", 0.09f);
//		lightShader.setFloat("pointLights[2].quadratic", 0.032f);
//		// point light 4
//		lightShader.setVec3("pointLights[3].position", pointLightPositions[3]);
//		lightShader.setVec3("pointLights[3].ambient", 0.5f, 0.5f, 0.5f);
//		lightShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
//		lightShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
//		lightShader.setFloat("pointLights[3].constant", 1.0f);
//		lightShader.setFloat("pointLights[3].linear", 0.09f);
//		lightShader.setFloat("pointLights[3].quadratic", 0.032f);
//		// spotLight
//		lightShader.setVec3("spotLight.position", camera.Position);
//		lightShader.setVec3("spotLight.direction", camera.Front);
//		lightShader.setVec3("spotLight.ambient", 5.0f, 5.0f, 5.0f);
//		lightShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
//		lightShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
//		lightShader.setFloat("spotLight.constant", 1.0f);
//		lightShader.setFloat("spotLight.linear", 0.09f);
//		lightShader.setFloat("spotLight.quadratic", 0.032f);
//		lightShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
//		lightShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(20.0f)));
//
//		// view/projection transformations
//		glm::mat4 projection_light = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
//		glm::mat4 view_light = camera.GetViewMatrix();
//		glm::mat4 model_light = glm::mat4(1.0f);
//		// world transformation
//		lightShader.setMat4("projection", projection_light);
//		lightShader.setMat4("view", view_light);
//		lightShader.setMat4("model", model_light);
//
//#pragma endregion
//		// ========================================light (end) ===========================================================
//
//		// ========================================draw ufo model (start)==========================================================
//#pragma region
//		//sShader.use();
//		//glm::mat4 projection_ufo = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
//		//glm::mat4 view_ufo = camera.GetViewMatrix();
//		//sShader.setMat4("projection", projection_ufo);
//		//sShader.setMat4("view", view_ufo);
//
//		ShaderPbr.use();
//		glm::mat4 viewPbr = camera.GetViewMatrix();
//		ShaderPbr.setMat4("view", viewPbr);
//		ShaderPbr.setVec3("camPos", camera.Position);
//		ShaderPbr.setFloat("metallic", 1.0);
//		ShaderPbr.setFloat("roughness", glm::clamp(1.0f, 0.05f, 1.0f));
//
//		float timeValue = glfwGetTime();
//
//		glm::mat4 model_ufo = glm::mat4(1.0f);
//		model_ufo = glm::translate(model_ufo, glm::vec3(-3.0f, 7.0f, -2.0f)); // translate it down so it's at the center of the scene
//		model_ufo = glm::scale(model_ufo, glm::vec3(.5f, .5f, .5f));	// it's a bit too big for our scene, so scale it down
//		//model_ufo = glm::rotate(model_ufo, timeValue * glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//
//		// 更新模型矩阵，此处只改变位置
//		//model_ufo = glm::translate(model_ufo, glm::vec3(0.0, 0.0, 0.0));
//		ShaderPbr.setMat4("model", model_ufo);
//		ShaderPbr.setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model_ufo))));
//
//		//sShader.setMat4("model", model_ufo);
//		lightShader.setMat4("model", model_ufo);
//		ufoModel.Draw(lightShader);
//
//#pragma endregion
//		// ========================================draw ufo model (end) ===========================================================
//
//
//		// ========================================end render loop (start)==========================================================
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
//	// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//	// ---------------------------------------------------------------------------------------------------------
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
//	camera.ProcessMouseMovement(xoffset, yoffset);
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
