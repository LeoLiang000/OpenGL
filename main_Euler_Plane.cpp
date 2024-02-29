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
//#include "gui.h"
//
//// ========================================initialize (start)==========================================================
//#pragma region
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);
//unsigned int loadCubemap(vector<std::string> faces);
//
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
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
////Euler
//int rotateMode = 1;
//
//float euler_y = 0.0;
//float euler_p = 0.0;
//float euler_r = 0.0;
//
//// Quternion
//glm::quat quaternion = glm::angleAxis(glm::radians(0.0f), glm::vec3(1., 0., 0.));
//float old_eulerY = euler_y;
//float old_eulerR = euler_r;
//float old_eulerP = euler_p;
//float delta_p = 0;
//float delta_y = 0;
//float delta_r = 0;
//
//glm::mat4 trans;
//glm::mat4 modelMat;
//glm::mat4 viewMat;
//glm::mat4 projMat = glm::perspective(glm::radians(45.0f), 1400.0f / 1000.0f, 0.1f, 300.0f);
//
//float startTime = glfwGetTime();
//
////bool isEuler(true);
////bool isQuater(false);
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
//	Shader dShader("assets/shaders/shader_ani.vs", "assets/shaders/shader_ani.fs");
//	Shader sShader("assets/shaders/shader.vs", "assets/shaders/shader.fs");
//	Shader skyboxShader("assets/shaders/skybox.vs", "assets/shaders/skybox.fs");
//
//	Model planeModel("assets/models/plane/plane.obj");  	// load ufo model
//	Model rightPropeller("assets/models/plane/rightPropeller.obj");
//	Model leftPropeller("assets/models/plane/leftPropeller.obj");
//	//Model frontPropeller("assets/models/plane/frontPropeller.obj");
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
//// ========================================skybox (start)==========================================================
//#pragma region
//	float skyboxVertices[] = {
//		// positions          
//		-1.0f,  1.0f, -1.0f,
//		-1.0f, -1.0f, -1.0f,
//		 1.0f, -1.0f, -1.0f,
//		 1.0f, -1.0f, -1.0f,
//		 1.0f,  1.0f, -1.0f,
//		-1.0f,  1.0f, -1.0f,
//
//		-1.0f, -1.0f,  1.0f,
//		-1.0f, -1.0f, -1.0f,
//		-1.0f,  1.0f, -1.0f,
//		-1.0f,  1.0f, -1.0f,
//		-1.0f,  1.0f,  1.0f,
//		-1.0f, -1.0f,  1.0f,
//
//		 1.0f, -1.0f, -1.0f,
//		 1.0f, -1.0f,  1.0f,
//		 1.0f,  1.0f,  1.0f,
//		 1.0f,  1.0f,  1.0f,
//		 1.0f,  1.0f, -1.0f,
//		 1.0f, -1.0f, -1.0f,
//
//		-1.0f, -1.0f,  1.0f,
//		-1.0f,  1.0f,  1.0f,
//		 1.0f,  1.0f,  1.0f,
//		 1.0f,  1.0f,  1.0f,
//		 1.0f, -1.0f,  1.0f,
//		-1.0f, -1.0f,  1.0f,
//
//		-1.0f,  1.0f, -1.0f,
//		 1.0f,  1.0f, -1.0f,
//		 1.0f,  1.0f,  1.0f,
//		 1.0f,  1.0f,  1.0f,
//		-1.0f,  1.0f,  1.0f,
//		-1.0f,  1.0f, -1.0f,
//
//		-1.0f, -1.0f, -1.0f,
//		-1.0f, -1.0f,  1.0f,
//		 1.0f, -1.0f, -1.0f,
//		 1.0f, -1.0f, -1.0f,
//		-1.0f, -1.0f,  1.0f,
//		 1.0f, -1.0f,  1.0f
//	};
//
//	// skybox VAO
//	unsigned int skyboxVAO, skyboxVBO;
//	glGenVertexArrays(1, &skyboxVAO);
//	glGenBuffers(1, &skyboxVBO);
//	glBindVertexArray(skyboxVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//
//	// load textures
//	vector<std::string> faces_red_stars
//	{
//		"assets/image/red/v1/right.png",
//		"assets/image/red/v1/left.png",
//		"assets/image/red/v1/top.png",
//		"assets/image/red/v1/bottom.png",
//		"assets/image/red/v1/front.png",
//		"assets/image/red/v1/back.png",
//	};
//	stbi_set_flip_vertically_on_load(false); // cube map dont flip
//	unsigned int cubemapTexture = loadCubemap(faces_red_stars);
//	stbi_set_flip_vertically_on_load(true); // other models flip
//
//#pragma endregion
//// ========================================skybox (end) ===========================================================
//
//
//	// ========================================init render loop (start)==========================================================
//#pragma region
//	glm::mat4 rotateMat;
//	myGUI myGui(window);  // initialize IMG UI
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
//		// Euler
//		//if (rotateMode == 1)
//		if (isEuler) {
//
//			rotateMat = glm::scale(glm::mat4(1.0f), glm::vec3(5.0f, 5.0f, 5.0f));
//			rotateMat = glm::rotate(rotateMat, glm::radians(euler_r), glm::vec3(0.0f, 0.0f, 1.0f));
//			rotateMat = glm::rotate(rotateMat, glm::radians(euler_y), glm::vec3(0.0f, 1.0f, 0.0f));
//			rotateMat = glm::rotate(rotateMat, glm::radians(euler_p), glm::vec3(1.0f, 0.0f, 0.0f));
//		}
//		else if (isQuater)
//		{
//			delta_p = euler_p - old_eulerP;
//			delta_y = euler_y - old_eulerY;
//			delta_r = euler_r - old_eulerR;
//
//			glm::vec3 rotationAxisX = glm::vec3(glm::toMat4(quaternion) * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));  //calculate current rotation axis vector based on current quaternion 
//			glm::quat rotX = glm::angleAxis(glm::radians(delta_p), rotationAxisX);  //compute new quaternion 
//			quaternion = rotX * quaternion;
//
//			glm::vec3 rotationAxisY = glm::vec3(glm::toMat4(quaternion) * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
//			glm::quat rotY = glm::angleAxis(glm::radians(delta_y), rotationAxisY);
//			quaternion = rotY * quaternion;
//
//			glm::vec3 rotationAxisZ = glm::vec3(glm::toMat4(quaternion) * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
//			glm::quat rotZ = glm::angleAxis(glm::radians(delta_r), rotationAxisZ);
//			quaternion = rotZ * quaternion;
//
//			old_eulerP = euler_p;
//			old_eulerY = euler_y;
//			old_eulerR = euler_r;
//
//			rotateMat = glm::scale(glm::mat4(1.0f), glm::vec3(5.0f, 5.0f, 5.0f));
//			rotateMat = glm::toMat4(quaternion);
//		}
//
//		
//// ========================================draw plane model (start)==========================================================
//#pragma region
//		glm::mat4 projection_ufo = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
//		glm::mat4 view_ufo = camera.GetViewMatrix();
//		glm::mat4 model_plane = glm::mat4(1.0f);
//
//		sShader.use();
//		sShader.setMat4("projection", projection_ufo);
//		sShader.setMat4("view", view_ufo);
//
//		model_plane = glm::translate(model_plane, glm::vec3(0.0f, 18.0f, 0.0f)); // translate it down so it's at the center of the scene
//		model_plane *= rotateMat;  // rotate model
//		sShader.setMat4("model", model_plane);
//		planeModel.Draw(sShader);
//
//		// right propeller
//		glm::mat4 trans_rightPropeller = glm::translate(rotateMat, glm::vec3(-4.5f, 0.095f, 1.85f));
//		trans_rightPropeller = glm::rotate(trans_rightPropeller, glm::radians(360.0f * (currentFrame - startTime)), glm::vec3(0.0f, 0.0f, 1.0f));
//		trans_rightPropeller = glm::translate(trans_rightPropeller, glm::vec3(4.5f, -0.095f, -1.85f));
//		modelMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 18.0f, 0.0f));
//		modelMat = modelMat * trans_rightPropeller;
//		sShader.setMat4("model", modelMat);
//		rightPropeller.Draw(sShader);
//
//		// left propeller
//		glm::mat4 trans_leftPropeller = glm::translate(rotateMat, glm::vec3(4.5f, 0.095f, 1.85f));
//		trans_leftPropeller = glm::rotate(trans_leftPropeller, glm::radians(360.0f * (currentFrame - startTime)), glm::vec3(0.0f, 0.0f, 1.0f));
//		trans_leftPropeller = glm::translate(trans_leftPropeller, glm::vec3(-4.5f, -0.095f, -1.85f));
//		modelMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 18.0f, 0.0f));
//		modelMat = modelMat * trans_leftPropeller;
//		sShader.setMat4("model", modelMat);
//		leftPropeller.Draw(sShader);
//
//
//
//#pragma endregion
//// ========================================draw plane model (end) ===========================================================
//
//		//myGui.createGUI();  // create IMG UI
//
//// ========================================draw skybox (start)==========================================================
//#pragma region
//
//		skyboxShader.use();
//
//		glm::mat4 view_skybox = camera.GetViewMatrix();
//		glm::mat4 projection_skybox = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//
//		// draw skybox as last
//		glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
//		skyboxShader.use();
//		view_skybox = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
//		skyboxShader.setMat4("view", view_skybox);
//		skyboxShader.setMat4("projection", projection_skybox);
//		// skybox cube
//		glBindVertexArray(skyboxVAO);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		glBindVertexArray(0);
//		glDepthFunc(GL_LESS);
//
//#pragma endregion
//// ========================================draw skybox (end) ===========================================================
//
//
//// ========================================IMGUI (start)==========================================================
//#pragma region
//		// Start the Dear ImGui frame
//		ImGui_ImplOpenGL3_NewFrame();
//		ImGui_ImplGlfw_NewFrame();
//		ImGui::NewFrame();
//
//		ImGui::Begin("IMGUI Editor");
//
//			//ImGui::Text();
//			if (ImGui::RadioButton("Euler", isEuler)) {
//				isQuater = false; // Ensure only one is selected
//				isEuler = true;
//			}
//			ImGui::SameLine();
//			if (ImGui::RadioButton("Quaternion", isQuater)) {
//				isEuler = false; // Ensure only one is selected
//				isQuater = true;
//			}
//			//ImGui::SliderInt("slider int", &i1, -1, 3);
//
//			ImGui::SliderFloat("X Axis", &euler_p, 0.0f, 360.0f);
//			ImGui::SliderFloat("Y Axis", &euler_y, 0.0f, 360.0f);
//			ImGui::SliderFloat("Z Axis", &euler_r, 0.0f, 360.0f);
//
//		ImGui::End();
//		ImGui::Render();
//		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//#pragma endregion
//// ========================================IMGUI (end) ===========================================================
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
//	
//	// Roration mode
//	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
//		rotateMode = 1;  // Euler
//	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
//		rotateMode = 2;  // Quaternions
//	
//	// Euler angle
//	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
//		euler_r -= .2f;
//	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
//		euler_y -= .2f;
//	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
//		euler_p -= .2f;
//
//	// UI
//	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
//        MouseButton2 = true;
//    else
//        MouseButton2 = false;
//
//
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
