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
//#define _USE_MATH_DEFINES
//#include <math.h>
//#include "LightDirectional.h"
//
//
//// ========================================initialize (start)==========================================================
//#pragma region
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);
//unsigned int loadTexture(const char* path);
//
//
//// window settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//int screenWidth = 1001;
//int screenHeight = 1001;
//int cursorPosX = screenWidth / 2;
//int cursorPosY = screenHeight / 2;
//
//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 100.0f));
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//LightDirectional lightD(glm::vec3(10.0f, 30.0f, 20.0f), glm::vec3(glm::radians(110.0f), glm::radians(30.0f), 0), glm::vec3(1.0f, 0.95f, 0.8f));
//
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
//	// ========================================init (end) ===========================================================
//
//	// ========================================init shaders & models (start)==========================================================
//#pragma region
//
//	// build and compile shaders
//
//	Shader shader_blinnPhong("assets/shaders/Animation/kinematic/VertexShader_blinnPhong.vert", "assets/shaders/Animation/kinematic/FragmentShader_blinnPhong.frag");
//
//	Shader dShader("assets/shaders/shader_ani.vs", "assets/shaders/shader_ani.fs");
//	//Shader sShader("assets/shaders/shader.vs", "assets/shaders/shader.fs");
//	//Shader sShader("assets/shaders/normal_map.vs", "assets/shaders/normal_map.fs");
//	Shader sShader("assets/shaders/BPhong.vs", "assets/shaders/BPhong.fs");
//	Shader sShader2("assets/shaders/normal_map.vs", "assets/shaders/normal_map.fs");
//	unsigned int diffuseMap = loadTexture("assets/models/bone/bone2/Blank image.jpg");
//
//	sShader.use();
//	sShader.setVec3("lightD.pos", glm::vec3(lightD.position.x, lightD.position.y, lightD.position.z));
//	sShader.setVec3("lightD.color", glm::vec3(lightD.color.x, lightD.color.y, lightD.color.z));
//	sShader.setVec3("lightD.dirToLight", glm::vec3(lightD.direction.x, lightD.direction.y, lightD.direction.z));
//
//
//
//	//sShader.use();
//	//sShader.setInt("diffuseMap", 0);
//	//Model ufoModel("assets/models/plane/plane.obj");  	// load ufo model
//	Model ufoModel("assets/models/bone/bone2/bone.obj");
//	Model ufoModel2("assets/models/bone/bone2/bone.obj");
//
//	//float angle = 0.0f; // 初始化角度变量
//	//float radius = 50.0f; // 圆形轨迹的半径
//
//
//	stbi_set_flip_vertically_on_load(true); // other models flip
//
//	glm::mat4 boneScale;
//	glm::mat4 trans;
//	glm::mat4 modelMat;
//	//modelMat = glm::rotate(modelMat, glm::radians(0.0f), glm::vec3(1.0f, 0, 0));
//	glm::mat4 viewMat;
//	glm::mat4 projMat;
//	projMat = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -5.0f, 5.0f);
//
//	// bone setting
//	glm::vec3 bone1_position = glm::vec3(0.0f);
//	glm::vec3 bone2_position = glm::vec3(0.0f);
//
//	//float bone1_length = 1.5;
//	//float bone2_length = 1.5;
//
//	glm::quat bone1_quat = glm::angleAxis(glm::radians(0.0f), glm::vec3(1., 0., 0.));
//	glm::quat bone2_quat = glm::angleAxis(glm::radians(0.0f), glm::vec3(1., 0., 0.));
//
//	glm::quat rot1 = glm::angleAxis(glm::radians(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
//	glm::quat rot2 = glm::angleAxis(glm::radians(1.1f), glm::vec3(0.0f, 0.0f, 1.0f));
//
//	bone1_quat = rot1 * bone1_quat;
//	bone2_quat = rot2 * bone2_quat;
//
//	glm::vec3 rotAxis;
//	glm::quat rot;
//
//
//
//	// draw in wireframe
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//#pragma endregion
//// ========================================init shaders & models (end) ===========================================================
//
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
//		//float positionX = (lastX - (SCR_WIDTH / 2)) / float(SCR_WIDTH / 2) * 10.0f;
//		//float positionY = -(lastY - (SCR_HEIGHT / 2)) / float(SCR_HEIGHT / 2) * 10.0f;
//
//
//		float positionX = (cursorPosX - (screenWidth / 2)) / float(screenWidth / 2) * 10.0f;
//		float positionY = -(cursorPosY - (screenHeight / 2)) / float(screenHeight / 2) * 10.0f;
//
//
//		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
//		viewMat = camera.GetViewMatrix();
//
//		// render
//		// ------
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//#pragma endregion
//		// ========================================init render loop (end) ===========================================================
//
//		// ========================================draw ufo model (start)==========================================================
//#pragma region
//
//		glm::vec3 bone1_position = glm::vec3(0.0f, 0.0f, 0.0f);
//		float bone1_length = 4;
//		float bone2_length = 2;
//
//		float angle_T;
//		float angle_1;
//		float bone1_angle;
//		float bone2_angle;
//
//		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
//		glm::mat4 view = camera.GetViewMatrix();
//		glm::mat4 model = glm::mat4(1.0f);
//
//
//		// 2D analytical solution
//		// when the target is over the distance the two bones can reach to
//		if (std::sqrt(positionX * positionX + positionY * positionY) > (bone1_length + bone2_length))
//		{
//			if (positionY > 0) bone1_angle = std::acos(positionX / std::sqrt(positionX * positionX + positionY * positionY));
//			else bone1_angle = -std::acos(positionX / std::sqrt(positionX * positionX + positionY * positionY));
//
//			bone2_angle = 0;  // ?
//		}
//		// when the target is inside the area the two bones can reach to
//		else if (std::sqrt(positionX * positionX + positionY * positionY) < std::abs(bone1_length - bone2_length))
//		{
//			if (positionY > 0) bone1_angle = std::acos(positionX / std::sqrt(positionX * positionX + positionY * positionY));
//			else bone1_angle = -std::acos(positionX / std::sqrt(positionX * positionX + positionY * positionY));
//
//			bone2_angle = M_PI;
//		}
//		// to avoid the bones flip when go beyond x_axis or y_axis, devide them to 2 cases
//		else if (positionY > 0)
//		{
//			angle_T = std::acos(positionX / std::sqrt(positionX * positionX + positionY * positionY));
//			angle_1 = std::acos((bone1_length * bone1_length + positionX * positionX + positionY * positionY - bone2_length * bone2_length) / (2 * bone1_length * std::sqrt(positionX * positionX + positionY * positionY)));
//			bone1_angle = angle_1 + angle_T;
//			bone2_angle = -std::acos(-(bone1_length * bone1_length + bone2_length * bone2_length - positionX * positionX - positionY * positionY) / (2 * bone1_length * bone2_length));
//		}
//		else
//		{
//			angle_T = std::acos((bone1_length * bone1_length + positionX * positionX + positionY * positionY - bone2_length * bone2_length) / (2 * bone1_length * std::sqrt(positionX * positionX + positionY * positionY)));
//			angle_1 = std::acos(positionX / std::sqrt(positionX * positionX + positionY * positionY));
//			bone1_angle = -(angle_1 - angle_T);
//			bone2_angle = -std::acos(-(bone1_length * bone1_length + bone2_length * bone2_length - positionX * positionX - positionY * positionY) / (2 * bone1_length * bone2_length));
//		}
//
//		//shader_blinnPhong.use();
//		//boneScale = glm::scale(glm::mat4(1.0f), glm::vec3(bone1_length, bone1_length, 1.0f));
//		//trans = glm::rotate(boneScale, bone1_angle, glm::vec3(0.0f, 0.0f, 1.0f));
//		//modelMat = glm::translate(glm::mat4(1.0f), bone1_position);
//		//shader_blinnPhong.setMat4("transform", trans);
//		//shader_blinnPhong.setMat4("modelMat", modelMat);
//		//shader_blinnPhong.setMat4("viewMat", viewMat);
//		//shader_blinnPhong.setVec3("viewPos", camera.Position);
//
//		//glm::mat4 projection_ufo = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
//		//shader_blinnPhong.setMat4("projMat", projection_ufo);
//
//		//ufoModel.Draw(shader_blinnPhong);
//
//		//glm::vec3 bone2_position = glm::mat3(glm::rotate(glm::mat4(1.0f), bone1_angle, glm::vec3(0.0f, 0.0f, 1.0f)))
//		//	* (bone1_position + glm::vec3(bone1_length, 0.0f, 0.0f));
//		//boneScale = glm::scale(glm::mat4(1.0f), glm::vec3(bone2_length, bone2_length, 1.0f));
//		//trans = glm::rotate(trans, bone2_angle, glm::vec3(0.0f, 0.0f, 1.0f));
//		//modelMat = glm::translate(glm::mat4(1.0f), bone2_position);
//		//shader_blinnPhong->SetMatrix("transform", trans * boneScale);
//		//shader_blinnPhong->SetMatrix("modelMat", modelMat);
//		//shader_blinnPhong->SetMatrix("viewMat", viewMat);
//		//shader_blinnPhong->SetMatrix("projMat", projMat);
//
//		//bone.Draw(shader_blinnPhong);
//
//		sShader.use();
//		boneScale = glm::scale(glm::mat4(1.0f), glm::vec3(bone1_length, bone1_length, 1.0f));
//		trans = glm::rotate(glm::mat4(1.0f), bone1_angle, glm::vec3(0.0f, 0.0f, 1.0f));
//		//glm::mat4 projection_ufo = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
//		//glm::mat4 view_ufo = camera.GetViewMatrix();
//		sShader.setMat4("projection", projection);
//		sShader.setMat4("view", view);
//		sShader.setMat4("transform", trans * boneScale);
//		glm::mat4 model_ufo = glm::translate(model, bone1_position);
//		sShader.setMat4("model", model_ufo);
//		ufoModel.Draw(sShader);
//
//
//		////bone 2
//		sShader2.use();
//		boneScale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1*bone2_length, 0.1*bone2_length, 1.0f));
//		trans = glm::rotate(glm::mat4(1.0f), bone2_angle, glm::vec3(0.0f, 0.0f, 1.0f));
//		//glm::mat4 projection_ufo2 = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
//		//glm::mat4 view_ufo2 = camera.GetViewMatrix();
//		//sShader2.setMat4("projection", projection_ufo2);
//		//sShader2.setMat4("view", view_ufo2);
//		sShader2.setMat4("transform", trans * boneScale);
//
//		glm::mat4 model_ufo2 = glm::mat4(1.0f);
//		model_ufo2 = glm::translate(model_ufo2, bone2_position);
//
//		sShader2.setMat4("model", model_ufo2);
//		ufoModel2.Draw(sShader2);
//
//
//
//
//		//sShader.use();
//		//glm::vec3 bone2_position = glm::mat3(glm::rotate(glm::mat4(1.0f), bone1_angle, glm::vec3(0.0f, 0.0f, 1.0f))) * (bone1_position + glm::vec3(bone1_length, 0.0f, 0.0f));
//		//boneScale = glm::scale(glm::mat4(1.0f), glm::vec3(bone2_length, bone2_length, 1.0f));
//		//trans = glm::rotate(trans, bone2_angle, glm::vec3(0.0f, 0.0f, 1.0f));
//		//model_ufo = glm::translate(model_ufo, bone2_position);
//		//sShader.setMat4("transform", trans * boneScale);
//		//sShader.setMat4("model", model_ufo);
//		//sShader.setMat4("view", view_ufo);
//		//sShader.setMat4("projection", projMat);
//		//ufoModel.Draw(sShader);
//
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
//
//// utility function for loading a 2D texture from file
//// ---------------------------------------------------
//unsigned int loadTexture(char const* path)
//{
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//
//	int width, height, nrComponents;
//	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
//	if (data)
//	{
//		GLenum format;
//		if (nrComponents == 1)
//			format = GL_RED;
//		else if (nrComponents == 3)
//			format = GL_RGB;
//		else if (nrComponents == 4)
//			format = GL_RGBA;
//
//		glBindTexture(GL_TEXTURE_2D, textureID);
//		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat 
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		stbi_image_free(data);
//	}
//	else
//	{
//		std::cout << "Texture failed to load at path: " << path << std::endl;
//		stbi_image_free(data);
//	}
//
//	return textureID;
//}



				//float IPD = 6.0f;																		// Typical human IPD in centimeters
				//glm::vec3 leftCameraPosition = originalEyeCenter - glm::vec3(IPD / 2, 0.0f, 0.0f);		// Calculate left and right camera positions based on IPD
				//glm::vec3 rightCameraPosition = originalEyeCenter + glm::vec3(IPD / 2, 0.0f, 0.0f);
				//glm::vec3 leftDirection = glm::normalize(eyeCenter - leftCameraPosition);				// Direction vectors from cameras to the convergence point (eyeCenter)
				//glm::vec3 rightDirection = glm::normalize(eyeCenter - rightCameraPosition);

				//glm::vec3 forward(0, 0, -1);															// Initial forward vector (assuming no toe-in, cameras are pointing down the Z-axis)
				//float leftAngle = acos(limitValue(glm::dot(forward, leftDirection), -1, 1));			// Calculate rotation angles using the dot product, which gives the cosine of the angle
				//float rightAngle = acos(limitValue(glm::dot(forward, rightDirection), -1, 1));
				//glm::vec3 leftCross = glm::cross(forward, leftDirection);								// Correct the angles based on the sign of the cross product to determine if rotation is left or right
				//if (glm::dot(leftCross, up) < 0) leftAngle = -leftAngle;
				//glm::vec3 rightCross = glm::cross(forward, rightDirection);
				//if (glm::dot(rightCross, up) < 0) rightAngle = -rightAngle;