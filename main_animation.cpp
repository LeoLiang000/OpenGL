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
//	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//	void processInput(GLFWwindow* window);
//
//	// skybox
//	//unsigned int loadTexture(const char* path);
//	unsigned int loadCubemap(vector<std::string> faces);
//
//	// window settings
//	const unsigned int SCR_WIDTH = 800;
//	const unsigned int SCR_HEIGHT = 600;
//
//#pragma endregion
//// ========================================default claim (end) ===========================================================
//
//// ========================================init camera (start)==========================================================
//#pragma region
//
//	// camera
//	Camera camera(glm::vec3(0.0f, 0.0f, 100.0f));
//	float lastX = SCR_WIDTH / 2.0f;
//	float lastY = SCR_HEIGHT / 2.0f;
//	bool firstMouse = true;
//
//	// timing
//	float deltaTime = 0.0f;
//	float lastFrame = 0.0f;
//
//#pragma endregion
//// ========================================init camera (end) ===========================================================
//
//int main()
//{
//// ========================================initialize (start)==========================================================
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
//// ========================================initialize (end) ===========================================================
//
//// ========================================init shaders & models (start)==========================================================
//#pragma region
//
//	// build and compile shaders
//	Shader dShader("assets/shaders/shader_ani.vs", "assets/shaders/shader_ani.fs");
//	Shader lightShader("assets/shaders/multi_lights.vs", "assets/shaders/multi_lights.fs");
//	Shader skyboxShader("assets/shaders/skybox.vs", "assets/shaders/skybox.fs");
//	Shader sShader("assets/shaders/normal_map.vs", "assets/shaders/normal_map.fs");
//	//Shader cubeShader("assets/shaders/cubemaps.vs", "assets/shaders/cubemaps.fs");
//	//Shader sShader("assets/shaders/shader.vs", "assets/shaders/shader.fs");
//	
//	// load animation models
//	// animation 1
//	Model dModel("assets/models/zombie2/Zombie Walk.dae");
//	Animation danceAnimation("assets/models/zombie2/Zombie Walk.dae", &dModel);
//	Animator animator(&danceAnimation);
//
//	// animation 2
//	Model dModel2("assets/models/zombie/Walking.dae");
//	Animation danceAnimation2("assets/models/zombie/Walking.dae", &dModel2);
//	Animator animator2(&danceAnimation2);
//	//Model dModel3("assets/models/zombie_female/Zombie Scream.dae");
//
//	// load scene model
//	Model sModel("assets/models/tcd campus/scene06/tcd.obj");  // campus model
//	Model ufoModel("assets/models/ufo/Low_poly_UFO.obj");  	// load ufo model
//
//	float angle = 0.0f; // 初始化角度变量
//	float radius = 50.0f; // 圆形轨迹的半径
//
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
//// ========================================light (end) ===========================================================
//
//// ========================================init skybox shader (start)==========================================================
//#pragma region
//	//set shader
//	skyboxShader.use();
//	skyboxShader.setInt("skybox", 0);
//
//#pragma endregion
//// ========================================init skybox shader (end) ===========================================================
//
//// ========================================init render loop (start)==========================================================
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
//		animator.UpdateAnimation(deltaTime);
//		animator2.UpdateAnimation(deltaTime);
//
//		// render
//		// ------
//		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//#pragma endregion
//// ========================================init render loop (end) ===========================================================
//
//// ========================================light (start)==========================================================
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
//// ========================================light (end) ===========================================================
//
//// ========================================draw scene model (start)==========================================================
//#pragma region
//
//		//use lighting shader to render the loaded model
//		glm::mat4 model_scene = glm::mat4(1.0f);
//		model_scene = glm::translate(model_scene, glm::vec3(10.0f, -0.4f, 50.0f)); // translate it down so it's at the center of the scene
//		model_scene = glm::scale(model_scene, glm::vec3(90.0f, 90.0f, 90.0f));	// it's a bit too big for our scene, so scale it down
//		lightShader.setMat4("model", model_scene);
//		sModel.Draw(lightShader);
//
//#pragma endregion
//// ========================================draw scene model (end) ===========================================================
//
//// ========================================draw ufo model (start)==========================================================
//#pragma region
//		sShader.use();
//		glm::mat4 projection_ufo = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
//		glm::mat4 view_ufo = camera.GetViewMatrix();
//		sShader.setMat4("projection", projection_ufo);
//		sShader.setMat4("view", view_ufo);
//
//		float timeValue = glfwGetTime();
//
//		glm::mat4 model_ufo = glm::mat4(1.0f);
//		model_ufo = glm::translate(model_ufo, glm::vec3(-300.0f, 70.0f, -200.0f)); // translate it down so it's at the center of the scene
//		model_ufo = glm::scale(model_ufo, glm::vec3(5.0f, 5.0f, 5.0f));	// it's a bit too big for our scene, so scale it down
//		model_ufo = glm::rotate(model_ufo, timeValue * glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//
//		// up and down rotation
//		float height = sin(timeValue) * 5.0f;
//		//model_ufo = glm::translate(model_ufo, glm::vec3(0.0f, height, 0.0f));
//
//		//travel distsnce
//		angle += .0003f * timeValue; // speed 是转圈的速度
//		angle = fmod(angle, 360.0f); // 保证角度不会超过360度
//
//		// 计算模型在圆形轨迹上的新位置
//		float x_ufo = radius * cos(angle);
//		float z_ufo = radius * sin(angle);
//
//		// 更新模型矩阵，此处只改变位置
//		model_ufo = glm::translate(model_ufo, glm::vec3(x_ufo, height, z_ufo));
//
//		sShader.setMat4("model", model_ufo);
//		//lightShader.setMat4("model", model_ufo);
//		ufoModel.Draw(sShader);
//
//#pragma endregion
//// ========================================draw ufo model (end) ===========================================================
//
//// ========================================draw animation model (start)==========================================================
//#pragma region
//
//		// ============animation 1=================
//		dShader.use();
//
//		// view & projection transformations
//		glm::mat4 dprojection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
//		glm::mat4 dview = camera.GetViewMatrix();
//		dShader.setMat4("projection", dprojection);
//		dShader.setMat4("view", dview);
//
//		auto transforms = animator.GetFinalBoneMatrices();
//		for (int i = 0; i < transforms.size(); ++i)
//			dShader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
//
//		float x, y, z;
//		y = -5.0f;
//		x = -190.0f;
//		z = -380.0f;
//
//
//
//		//glm::mat4 model_zombie1 = glm::mat4(1.0f);
//		//model_zombie1 = glm::translate(model_zombie1, glm::vec3(x, y, z));
//		//model_zombie1 = glm::scale(model_zombie1, glm::vec3(-.05f, .05f, -.05f));
//		//model_zombie1 = glm::rotate(model_zombie1, glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//
//		//dShader.setMat4("model", model_zombie1);
//		//dModel.Draw(dShader);
//		for (int j = 0; j <= 20; ++j)
//		{
//			for (int i = 0; i <= 10; ++i)
//			{
//				glm::mat4 model_zombie1 = glm::mat4(1.0f);
//				model_zombie1 = glm::translate(model_zombie1, glm::vec3(x, y, z)); // translate it down so it's at the center of the scene
//				model_zombie1 = glm::scale(model_zombie1, glm::vec3(.05f, .05f, .05f));	// it's a bit too big for our scene, so scale it down
//				//model_zombie1 = glm::rotate(model_zombie1, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
//				dShader.setMat4("model", model_zombie1);
//				dModel.Draw(dShader);
//				x -= 5.0f;
//				//z -= 5.0f;
//				//if (i % 2 == 0)
//				//{
//				//	model_zombie1 = glm::scale(model_zombie1, glm::vec3(.05f, .05f, .05f));	// it's a bit too big for our scene, so scale it down
//				//	model_zombie1 = glm::rotate(model_zombie1, glm::radians(static_cast < float>(50.0f + i * 1.5)), glm::vec3(0.0f, 1.0f, 0.0f));
//				//	x -= 5.0f;
//				//	z -= 5.0f;
//				//}
//				//else
//				//{
//				//	//model_zombie1 = glm::translate(model_zombie1, glm::vec3(x, y, z)); // translate it down so it's at the center of the scene
//				//	model_zombie1 = glm::scale(model_zombie1, glm::vec3(.05f, .05f, .05f));	// it's a bit too big for our scene, so scale it down
//				//	model_zombie1 = glm::rotate(model_zombie1, glm::radians(static_cast < float>(30.0f + i * 1.5)), glm::vec3(0.0f, 1.0f, 0.0f));
//				//	x -= 20.0f;
//				//	z -= 10.0f;
//				//}
//			}
//			z += 5.0f;
//			x = -190.0f;
//		}
//
//
//		// =================animation 2=================
//		auto transforms2 = animator2.GetFinalBoneMatrices();
//		for (int i = 0; i < transforms2.size(); ++i)
//			dShader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms2[i]);
//
//		x = -200.0f;
//		z = -400.0f;
//		for (int j = 0; j <= 8; ++j)
//		{
//			for (int i = 0; i <= 10; ++i)
//			{
//				glm::mat4 model_zombie2 = glm::mat4(1.0f);
//				model_zombie2 = glm::translate(model_zombie2, glm::vec3(x, y, z));
//				model_zombie2 = glm::scale(model_zombie2, glm::vec3(-.05f, .05f, -.05f));
//				//model_zombie2 = glm::rotate(model_zombie2, glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//				dShader.setMat4("model", model_zombie2);
//				dModel2.Draw(dShader);
//				x -= 5.0f;
//			}
//			z -= 5.0f;
//			x = -200.0f;
//		}
//
//
//		//for (int i = 0; i <= 5; ++i)
//		//{
//		//	glm::mat4 model_zombie2 = glm::mat4(1.0f);
//		//	if (i % 2 == 0)
//		//	{
//		//		model_zombie2 = glm::translate(model_zombie2, glm::vec3(x, y, z)); // translate it down so it's at the center of the scene
//		//		model_zombie2 = glm::scale(model_zombie2, glm::vec3(.5f, .5f, .5f));	// it's a bit too big for our scene, so scale it down
//		//	}
//		//	else
//		//	{
//		//		model_zombie2 = glm::translate(model_zombie2, glm::vec3(x, y, z)); // translate it down so it's at the center of the scene
//		//		model_zombie2 = glm::scale(model_zombie2, glm::vec3(-.5f, .5f, -.5f));	// it's a bit too big for our scene, so scale it down
//		//	}
//
//		//	dShader.setMat4("model", model_zombie2);
//		//	dModel2.Draw(dShader);
//
//		//	x -= 50.0f;
//		//	z -= 50.0f;
//		//}
//
//#pragma endregion
//// ========================================draw animation model (end) ===========================================================
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
//        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
//        skyboxShader.use();
//        view_skybox = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
//        skyboxShader.setMat4("view", view_skybox);
//        skyboxShader.setMat4("projection", projection_skybox);
//        // skybox cube
//        glBindVertexArray(skyboxVAO);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        glBindVertexArray(0);
//		glDepthFunc(GL_LESS);
//
//#pragma endregion
//// ========================================draw skybox (end) ===========================================================
//
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
//// ========================================end render loop (end) ===========================================================
//}
//
//// ========================================process mouse and keyboard (start)==========================================================
//#pragma region
//
//	// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//	// ---------------------------------------------------------------------------------------------------------
//	void processInput(GLFWwindow* window)
//	{
//		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//			glfwSetWindowShouldClose(window, true);
//
//		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//			camera.ProcessKeyboard(FORWARD, deltaTime);
//		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//			camera.ProcessKeyboard(BACKWARD, deltaTime);
//		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//			camera.ProcessKeyboard(LEFT, deltaTime);
//		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//			camera.ProcessKeyboard(RIGHT, deltaTime);
//	}
//
//	// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//	// ---------------------------------------------------------------------------------------------
//	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//	{
//		// make sure the viewport matches the new window dimensions; note that width and 
//		// height will be significantly larger than specified on retina displays.
//		glViewport(0, 0, width, height);
//	}
//
//	// glfw: whenever the mouse moves, this callback is called
//	// -------------------------------------------------------
//	void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//	{
//		if (firstMouse)
//		{
//			lastX = xpos;
//			lastY = ypos;
//			firstMouse = false;
//		}
//
//		float xoffset = xpos - lastX;
//		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//		lastX = xpos;
//		lastY = ypos;
//		//cout << "mouse position: " << "x=" << lastX << ", y=" << lastY << endl;
//		camera.ProcessMouseMovement(xoffset, yoffset);
//	}
//
//	// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//	// ----------------------------------------------------------------------
//	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//	{
//		camera.ProcessMouseScroll(yoffset);
//	}
//#pragma endregion
//// ========================================process mouse and keyboard (end) ===========================================================
//
//// ========================================load cube (start)==========================================================
//#pragma region
//	unsigned int loadCubemap(vector<std::string> faces)
//	{
//		unsigned int textureID;
//		glGenTextures(1, &textureID);
//		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
//
//		int width, height, nrComponents;
//		for (unsigned int i = 0; i < faces.size(); i++)
//		{
//			unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
//			if (data)
//			{
//				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//				stbi_image_free(data);
//				cout << "successfully loaded image: " << faces[i].c_str() << endl;
//			}
//			else
//			{
//				std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
//				stbi_image_free(data);
//			}
//		}
//		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//
//		return textureID;
//	}
//#pragma endregion
//// ========================================load cube (end) ===========================================================
