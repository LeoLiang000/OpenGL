//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include "shader_m.h"
//#include "camera.h"
//#include "model_animation.h"
//#include <iostream>
//#include "LightDirectional.h"
//#include "gui.h"
//// ========================================initialize (start)==========================================================
//#pragma region
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);
//unsigned int loadCubemap(vector<std::string> faces);
//unsigned int LoadTextureImageToGPU(const char* filename, GLint internalFormat, GLenum format, int textureSlot);
//unsigned int loadTexture(const char* path);
//
//// window settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//bool MouseButton2(false);
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
//
//float vertices_ground[] = {
//	// positions          // normals           // texture coords
//	-0.5f, -0.0f, -0.5f,   0.0f, 1.0f, 0.0f,   100.0f, 100.0f,   // top right
//	 0.5f, -0.0f, -0.5f,   0.0f, 1.0f, 0.0f,   100.0f, 0.0f,   // bottom right
//	 0.5f, -0.0f,  0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,   // bottom left
//	-0.5f, -0.0f,  0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 100.0f    // top left 
//};
//
//unsigned int indices_ground[] = {
//	0, 1, 2,
//	2, 3, 0
//};
//
//float skyboxVertices[] = {
//	// positions          
//	-1.0f,  1.0f, -1.0f,
//	-1.0f, -1.0f, -1.0f,
//	 1.0f, -1.0f, -1.0f,
//	 1.0f, -1.0f, -1.0f,
//	 1.0f,  1.0f, -1.0f,
//	-1.0f,  1.0f, -1.0f,
//
//	-1.0f, -1.0f,  1.0f,
//	-1.0f, -1.0f, -1.0f,
//	-1.0f,  1.0f, -1.0f,
//	-1.0f,  1.0f, -1.0f,
//	-1.0f,  1.0f,  1.0f,
//	-1.0f, -1.0f,  1.0f,
//
//	 1.0f, -1.0f, -1.0f,
//	 1.0f, -1.0f,  1.0f,
//	 1.0f,  1.0f,  1.0f,
//	 1.0f,  1.0f,  1.0f,
//	 1.0f,  1.0f, -1.0f,
//	 1.0f, -1.0f, -1.0f,
//
//	-1.0f, -1.0f,  1.0f,
//	-1.0f,  1.0f,  1.0f,
//	 1.0f,  1.0f,  1.0f,
//	 1.0f,  1.0f,  1.0f,
//	 1.0f, -1.0f,  1.0f,
//	-1.0f, -1.0f,  1.0f,
//
//	-1.0f,  1.0f, -1.0f,
//	 1.0f,  1.0f, -1.0f,
//	 1.0f,  1.0f,  1.0f,
//	 1.0f,  1.0f,  1.0f,
//	-1.0f,  1.0f,  1.0f,
//	-1.0f,  1.0f, -1.0f,
//
//	-1.0f, -1.0f, -1.0f,
//	-1.0f, -1.0f,  1.0f,
//	 1.0f, -1.0f, -1.0f,
//	 1.0f, -1.0f, -1.0f,
//	-1.0f, -1.0f,  1.0f,
//	 1.0f, -1.0f,  1.0f
//};
//
//float cubeVertices[] = {
//	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//
//	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//
//	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//
//	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//
//	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//
//	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
//};
//
//LightDirectional lightD(glm::vec3(10.0f, 30.0f, 20.0f), glm::vec3(glm::radians(110.0f), glm::radians(30.0f), 0), glm::vec3(1.0f, 0.95f, 0.8f));
//
//float euler_p = 0.0;
//float fresnel_ratio(0.2);
//float refraction_ratio(0.2);
//float etaR(0.65);
//float etaG(0.67);
//float etaB(0.69);
//
//
//glm::vec3 lightPos(5.0f, 1.0f, 0.3f);
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
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
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
//	//stbi_set_flip_vertically_on_load(true);
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
//	Shader shader_reflection("assets/shaders/rendering/Vertexshader_reflection.vert", "assets/shaders/rendering/Fragmentshader_reflection.frag");
//	Shader shader_refraction("assets/shaders/rendering/Vertexshader_refraction.vert", "assets/shaders/rendering/Fragmentshader_refraction.frag");
//	Shader shader_fresnel("assets/shaders/rendering/Vertexshader_fresnel.vert", "assets/shaders/rendering/Fragmentshader_fresnel.frag");
//	Shader shader_chromatic("assets/shaders/rendering/Vertexshader_chromatic.vert", "assets/shaders/rendering/Fragmentshader_chromatic.frag");
//	Shader shader_skybox("assets/shaders/rendering/VertexShader_skybox.vert", "assets/shaders/rendering/FragmentShader_skybox.frag");
//
//	shader_refraction.use();
//	shader_refraction.setVec3("lightD.pos", glm::vec3(lightD.position.x, lightD.position.y, lightD.position.z));
//	shader_refraction.setVec3("lightD.color", glm::vec3(lightD.color.x, lightD.color.y, lightD.color.z));
//	shader_refraction.setVec3("lightD.dirToLight", glm::vec3(lightD.direction.x, lightD.direction.y, lightD.direction.z));
//
//	shader_reflection.use();
//	shader_reflection.setVec3("lightD.pos", glm::vec3(lightD.position.x, lightD.position.y, lightD.position.z));
//	shader_reflection.setVec3("lightD.color", glm::vec3(lightD.color.x, lightD.color.y, lightD.color.z));
//	shader_reflection.setVec3("lightD.dirToLight", glm::vec3(lightD.direction.x, lightD.direction.y, lightD.direction.z));
//
//	Model teapot("assets/models/teapot/teapot.obj");
//	Model ufoModel("assets/models/bone/bone2/bone.obj");
//
//	// test normal map
//	//Shader shader("assets/shaders/normal_map.vs", "assets/shaders/normal_map.fs");
//	//unsigned int diffuseMap = loadTexture("assets/brickwall.jpg");
//	//unsigned int normalMap = loadTexture("assets/brickwall_normal.jpg");
//	//shader.use();
//	//shader.setInt("diffuseMap", 0);
//	//shader.setInt("normalMap", 1);
//
//	// skybox VAO VBO
//	unsigned int skyboxVAO, skyboxVBO;
//	glGenVertexArrays(1, &skyboxVAO);
//	glGenBuffers(1, &skyboxVBO);
//	glBindVertexArray(skyboxVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//
//	// cube VAO VBO
//	unsigned int cubeVAO, cubeVBO;
//	glGenVertexArrays(1, &cubeVAO);
//	glGenBuffers(1, &cubeVBO);
//	glBindVertexArray(cubeVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//
//	// ground VAO VBO
//	unsigned int VBO_ground;
//	glGenBuffers(1, &VBO_ground);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO_ground);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_ground), vertices_ground, GL_STATIC_DRAW);
//
//	unsigned int VAO_ground;
//	glGenVertexArrays(1, &VAO_ground);
//	glBindVertexArray(VAO_ground);
//
//	unsigned int EBO_ground;
//	glGenBuffers(1, &EBO_ground);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_ground);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_ground), indices_ground, GL_STATIC_DRAW);
//
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(2);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//
//	stbi_set_flip_vertically_on_load(true); // other models flip
//
//	unsigned int TexBuffer_ground;
//	TexBuffer_ground = LoadTextureImageToGPU("assets/shaders/rendering/ground.jpg", GL_RGB, GL_RGB, 0);
//	//unsigned int TexBufferB;
//	//TexBufferB = LoadTextureImageToGPU("awesomeface.png", GL_RGBA, GL_RGBA, 1);
//#pragma endregion
//
//#pragma region Init Skybox Texture;
//	vector<std::string> faces
//	{
//		"assets/models/skybox/church/posx.jpg",
//		"assets/models/skybox/church/negx.jpg",
//		"assets/models/skybox/church/posy.jpg",
//		"assets/models/skybox/church/negy.jpg",
//		"assets/models/skybox/church/posz.jpg",
//		"assets/models/skybox/church/negz.jpg"
//	};
//	stbi_set_flip_vertically_on_load(false);
//	unsigned int cubemapTexture = loadCubemap(faces);
//	//stbi_set_flip_vertically_on_load(true);
//
//	// draw in wireframe
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//#pragma endregion
//// ========================================init shaders & models (end) ===========================================================
//#pragma region Prepare MVP matrices
//	//glm::mat4 scale;  glm::scale(transMatrix, glm::vec3(100.0f, 100.0f, 100.0f));
//	glm::mat4 trans;
//	glm::mat4 modelMat;
//	glm::mat4 viewMat;
//	glm::mat4 projMat;
//	projMat = glm::perspective(glm::radians(45.0f), 1400.0f / 1000.0f, 0.1f, 300.0f);
//#pragma endregion
//
//	// initialize IMG UI
//	myGUI myGui(window);
//	// ========================================init render loop (start)==========================================================
//#pragma region
//
//	// render loop
//	while (!glfwWindowShouldClose(window))
//	{
//		float currentTime = glfwGetTime();
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
//
//		//glViewport(0, 0, 1400, 1000);
//		viewMat = camera.GetViewMatrix();
//#pragma endregion
//		// ========================================init render loop (end) ===========================================================
//
//		// ========================================teapot (start)==========================================================
//#pragma region
//		// refraction
//		shader_refraction.use();
//		trans = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
//		trans = glm::rotate(trans, currentTime, glm::vec3(0.0f, 1.0f, 0.0f));
//		modelMat = glm::translate(glm::mat4(1.0f), glm::vec3(-24.0f, 0.0f, -5.0f));
//		shader_refraction.setMat4("transform", trans);
//		shader_refraction.setMat4("modelMat", modelMat);
//		shader_refraction.setMat4("viewMat", viewMat);
//		shader_refraction.setMat4("projMat", projMat);
//		shader_refraction.setVec3("viewPos", camera.Position);
//		shader_refraction.setInt("skybox", 0);
//		shader_refraction.setFloat("refraction_ratio", refraction_ratio);
//		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
//		ufoModel.Draw(shader_refraction);
//
//		// test normal map
//		//shader.use();
//		//glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//		//glm::mat4 view = camera.GetViewMatrix();
//		//shader.use();
//		//shader.setMat4("projection", projection);
//		//shader.setMat4("view", view);
//		//// render normal-mapped quad
//		//glm::mat4 model = glm::mat4(1.0f);
//		////model = glm::translate(glm::mat4(1.0f), glm::vec3(-24.0f, 0.0f, -5.0f));
//		////model = glm::rotate(model, glm::radians((float)glfwGetTime() * -10.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0))); // rotate the quad to show normal mapping from multiple directions
//		//shader.setMat4("model", model);
//		//shader.setVec3("viewPos", camera.Position);
//		//shader.setVec3("lightPos", lightPos);
//		//glActiveTexture(GL_TEXTURE0);
//		//glBindTexture(GL_TEXTURE_2D, diffuseMap);
//		//glActiveTexture(GL_TEXTURE1);
//		//glBindTexture(GL_TEXTURE_2D, normalMap);
//
//		//teapot.Draw(shader);
//
//
//
//		// reflection
//		//shader_reflection.use();
//		//trans = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
//		//trans = glm::rotate(trans, currentTime, glm::vec3(0.0f, 1.0f, 0.0f));
//		//modelMat = glm::translate(glm::mat4(1.0f), glm::vec3(-8.0f, 0.0f, -5.0f));
//		//shader_reflection.setMat4("transform", trans);
//		//shader_reflection.setMat4("modelMat", modelMat);
//		//shader_reflection.setMat4("viewMat", viewMat);
//		//shader_reflection.setMat4("projMat", projMat);
//		//shader_reflection.setInt("skybox", 0);
//		//shader_reflection.setVec3("viewPos", camera.Position);
//		//glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
//		//teapot.Draw(shader_reflection);
//
//		//// fresnel
//		//shader_fresnel.use();
//		//trans = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
//		//trans = glm::rotate(trans, currentTime, glm::vec3(0.0f, 1.0f, 0.0f));
//		//modelMat = glm::translate(glm::mat4(1.0f), glm::vec3(8.0f, 0.0f, -5.0f));
//		//shader_fresnel.setMat4("transform", trans);
//		//shader_fresnel.setMat4("modelMat", modelMat);
//		//shader_fresnel.setMat4("viewMat", viewMat);
//		//shader_fresnel.setMat4("projMat", projMat);
//		//shader_fresnel.setInt("skybox", 0);
//		//shader_fresnel.setVec3("viewPos", camera.Position);
//		//shader_fresnel.setFloat("fresnel_ratio", fresnel_ratio);
//		//glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
//		//teapot.Draw(shader_fresnel);
//
//		////chromatic
//		//shader_chromatic.use();
//		//trans = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
//		//trans = glm::rotate(trans, currentTime, glm::vec3(0.0f, 1.0f, 0.0f));
//		//modelMat = glm::translate(glm::mat4(1.0f), glm::vec3(24.0f, 0.0f, -5.0f));
//		//shader_chromatic.setMat4("transform", trans);
//		//shader_chromatic.setMat4("modelMat", modelMat);
//		//shader_chromatic.setMat4("viewMat", viewMat);
//		//shader_chromatic.setMat4("projMat", projMat);
//		//shader_chromatic.setVec3("viewPos", camera.Position);
//		//shader_chromatic.setInt("skybox", 0);
//		//shader_chromatic.setFloat("etaR", etaR);
//		//shader_chromatic.setFloat("etaG", etaG);
//		//shader_chromatic.setFloat("etaB", etaB);
//		//glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
//		//teapot.Draw(shader_chromatic);
//#pragma endregion
//		// ========================================teapot (end) ===========================================================
//
//		// ========================================skybox (start)==========================================================
//#pragma region
//		//glDepthFunc(GL_LEQUAL);
//		//shader_skybox.use();
//		//viewMat = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
//		//modelMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.04f, 0.0f));
//
//		//shader_skybox.setMat4("modelMat", modelMat);
//		//shader_skybox.setMat4("viewMat", viewMat);
//		//shader_skybox.setMat4("projMat", projMat);
//		//shader_skybox.setInt("skybox", 0);
//
//		//glBindVertexArray(cubeVAO);
//		//glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
//		//glDrawArrays(GL_TRIANGLES, 0, 36);
//		//glDepthFunc(GL_LESS);
//#pragma endregion
//		// ========================================skybox (end) ===========================================================
//
//				// ========================================IMGUI (start)==========================================================
//#pragma region
//		// Start the Dear ImGui frame
//		ImGui_ImplOpenGL3_NewFrame();
//		ImGui_ImplGlfw_NewFrame();
//		ImGui::NewFrame();
//
//		ImGui::Begin("IMGUI Editor");
//
//		// ====== UI content start ======
//		ImGui::SliderFloat("Refraction Ratio", &refraction_ratio, 0.0f, 1.0f);
//		ImGui::SliderFloat("Fresnel Ratio", &fresnel_ratio, 0.0f, 1.0f);
//		ImGui::SliderFloat("Chromatic etaR", &etaR, 0.0f, 1.0f);
//		ImGui::SliderFloat("Chromatic etaG", &etaG, 0.0f, 1.0f);
//		ImGui::SliderFloat("Chromatic etaB", &etaB, 0.0f, 1.0f);
//		// ====== UI content end ======
//
//		ImGui::End();
//		ImGui::Render();
//		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//#pragma endregion
//		// ========================================IMGUI (end) ===========================================================
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
//	// UI
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
//	//camera.ProcessMouseMovement(xoffset, yoffset);
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
//
//unsigned int loadCubemap(vector<std::string> faces)
//{
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
//
//	int width, height, nrChannels;
//	for (unsigned int i = 0; i < faces.size(); i++)
//	{
//		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
//		if (data)
//		{
//			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
//				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//			stbi_image_free(data);
//			std::cout << "Cubemap tex succeeded to load at path: " << faces[i] << std::endl;
//		}
//		else
//		{
//			std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
//			stbi_image_free(data);
//		}
//	}
//
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//
//	return textureID;
//}
//
//unsigned int LoadTextureImageToGPU(const char* filename, GLint internalFormat, GLenum format, int textureSlot)
//{
//	unsigned int TexBuffer;
//	glGenTextures(1, &TexBuffer);
//
//	glActiveTexture(GL_TEXTURE0 + textureSlot);
//	glBindTexture(GL_TEXTURE_2D, TexBuffer);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	// set texture filtering parameters
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	int width, height, nrChannel;
//	unsigned char* data = stbi_load(filename, &width, &height, &nrChannel, 0);
//	if (data)
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else
//	{
//		cout << "Texture image " << filename << " load failed." << endl;
//	}
//	stbi_image_free(data);
//
//	//cout << filename << "Slot:  " << TexBuffer << endl;
//
//	return TexBuffer;
//}
//
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
//
