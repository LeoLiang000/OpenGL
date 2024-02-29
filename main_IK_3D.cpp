//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include <glm/gtc/quaternion.hpp>
//#include <glm/gtx/quaternion.hpp>
//
//#include "shader_m.h"
//#include "camera.h"
//#include "model_animation.h"
//#include <iostream>
//#include "LightDirectional.h"
//#include "gui.h"
//
//#define _USE_MATH_DEFINES
//#include <math.h>
//// ========================================initialize (start)==========================================================
//#pragma region
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);
//unsigned int loadCubemap(vector<std::string> faces);
//unsigned int LoadTextureImageToGPU(const char* filename, GLint internalFormat, GLenum format, int textureSlot);
//unsigned int loadTexture(const char* path);
//bool CCDoverCondition(glm::vec3 _target_position, glm::vec3 _limb1_position, float _humanchain_length, glm::vec3 _humanchain_endPosition);
//void processInput_cube(GLFWwindow* window);
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
//float fresnel_ratio(0.2);
//float refraction_ratio(0.2);
//
//
//int screenWidth = 800;
//int screenHeight = 600;
//int cursorPosX = screenWidth / 2;
//int cursorPosY = screenHeight / 2;
//
//
//glm::vec3 lightPos(5.0f, 1.0f, 0.3f);
//float posx(0.0f);
//float posy(0.0f);
//float posz(0.0f);
//
//float posX = 1.0;
//float posY = 1.0;
//
//float theta_1;  // bone 1 rotation
//float theta_2;  // bone 2 rotation
//
//glm::vec3 cube_position(0.0f, 0.0f, 0.0f);
//float cube_x = 3.0;
//float cube_y = 0.0;
//float cube_z = 0.0;
//
//#pragma endregion
//// ========================================initialize (end) ===========================================================
//
//
//#pragma region CCD Loop Over Condition
//bool CCDoverCondition(glm::vec3 _target_position, glm::vec3 _limb1_position, float _humanchain_length, glm::vec3 _humanchain_endPosition)
//{
//	bool over = false;
//
//	if (glm::length(_target_position - _limb1_position) <= 0.95 * _humanchain_length)
//	{
//		if (_humanchain_length && glm::length(_target_position - _humanchain_endPosition) < 0.1)
//			over = true;
//	}
//	else if (glm::length(_target_position - _limb1_position) <= _humanchain_length)
//	{
//		if (_humanchain_length && glm::length(_target_position - _humanchain_endPosition) < 0.2)
//			over = true;
//	}
//	else
//	{
//		glm::vec3 p2e = _humanchain_endPosition - _limb1_position;
//		glm::vec3 p2t = _target_position - _limb1_position;
//		glm::vec3 e2t = _target_position - _humanchain_endPosition;
//		float angle = std::acos(glm::dot(glm::normalize(p2e), glm::normalize(p2t)));
//
//		if (angle < 0.01 && glm::length(e2t) < 0.5)
//			over = true;
//	}
//
//	return over;
//}
//#pragma endregion
//
//void processInput_cube(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
//	{
//		//cube_position += 0.1f * camera.Forward;
//		cube_position += 0.1f * glm::vec3(0.0f, 0.0f, -1.0f);
//	}
//	else if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
//	{
//		//cube_position += -0.1f * camera.Forward;
//		cube_position += -0.1f * glm::vec3(0.0f, 0.0f, -1.0f);
//	}
//
//
//	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
//	{
//		//cube_position += 0.1f * camera.Right;
//		cube_position += 0.1f * glm::vec3(1.0f, 0.0f, 0.0f);
//	}
//	else if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
//	{
//		//cube_position += -0.1f * camera.Right;
//		cube_position += -0.1f * glm::vec3(1.0f, 0.0f, 0.0f);
//	}
//
//
//	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
//	{
//		//cube_position += 0.1f * camera.Up;
//		cube_position += 0.1f * glm::vec3(0.0f, 1.0f, 0.0f);
//	}
//	else if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
//	{
//		//cube_position += -0.1f * camera.Up;
//		cube_position += -0.1f * glm::vec3(0.0f, 1.0f, 0.0f);
//	}
//
//}
//
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
//	Shader shader_ground("assets/shaders/Animation/kinematic/VertexShader_ground.vert", "assets/shaders/Animation/kinematic/FragmentShader_ground.frag");
//	Shader shader_cube("assets/shaders/Animation/kinematic/VertexShader_cube.vert", "assets/shaders/Animation/kinematic/FragmentShader_cube.frag");
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
//	//Model teapot("assets/models/teapot/teapot.obj");
//	//Model ufoModel("assets/models/bone/bone2/bone.obj");
//	Model human("assets/models/human/human.obj");
//	Model human_limb("assets/models/human//limb/limb.obj");
//	Model human_finger("assets/models/human/finger/finger.obj");
//	Model cube("assets/models/cube/cube.obj");
//
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
//	//projMat = glm::perspective(glm::radians(45.0f), 1400.0f / 1000.0f, 0.1f, 13000.0f);
//#pragma endregion
//
//	// initialize IMG UI
//	myGUI myGui(window);
//	// ========================================init render loop (start)==========================================================
//#pragma region
//
//	glm::mat4 boneScale;
//	projMat = glm::ortho(-1000.0f, 1000.0f, -1000.0f, 1000.0f, -50.0f, 1000.0f);  // same size regardless of distacne from camera
//
//
//	glm::vec3 bone1_position = glm::vec3(0.0f);
//	glm::vec3 bone2_position = glm::vec3(0.0f);
//
//	glm::vec3 bonechain_endPosition = glm::vec3(0.0f);
//	//float L1 = 1.5;
//	//float L2 = 1.5;
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
//
//
//	// ========================================IK prepare (start)==========================================================
//#pragma region
//	glm::vec3 rotAxis;
//	glm::quat rot;
//
//	glm::vec3 limb1_position = glm::vec3(0.5f, 3.8f, 0.0f);
//	glm::vec3 limb2_position = glm::vec3(0.0f);
//	glm::vec3 limb3_position = glm::vec3(0.0f);
//	glm::vec3 finger1_position = glm::vec3(0.0f);
//	glm::vec3 humanchain_endPosition = glm::vec3(0.0f);
//	float limb1_length = 1.05;
//	float limb2_length = 1.05;
//	float limb3_length = 1.25;
//	float finger1_length = 1.0;
//	float humanchain_length = 4.35;
//
//	glm::quat limb1_quat = glm::angleAxis(glm::radians(0.1f), glm::vec3(1., 0., 0.));
//	glm::quat limb2_quat = glm::angleAxis(glm::radians(0.1f), glm::vec3(1., 0., 0.));
//	glm::quat limb3_quat = glm::angleAxis(glm::radians(-0.1f), glm::vec3(1., 0., 0.));
//	glm::quat finger1_quat = glm::angleAxis(glm::radians(-0.1f), glm::vec3(1., 0., 0.));
//#pragma endregion
//
//#pragma region Preparation for Cubic Spline
//	glm::mat4 B(
//		0.0f, 1.0f, 8.0f, 27.0f,
//		0.0f, 1.0f, 4.0f, 9.0f,
//		0.0f, 1.0f, 2.0f, 3.0f,
//		1.0f, 1.0f, 1.0f, 1.0f
//	);
//	B = glm::inverse(glm::transpose(B)); // transpose is because the order in Opengl is already transposed
//
//	glm::vec4 spline_p1(1.0f, 5.5f, -1.0f, 0.0f);
//	glm::vec4 spline_p2(2.0f, 3.f, 1.0f, 0.0f);
//	glm::vec4 spline_p3(3.0f, 5.5f, -1.0f, 0.0f);
//	glm::vec4 spline_p4(4.0f, 3.0f, 0.5f, 0.0f);
//	glm::mat4 G(spline_p1, spline_p2, spline_p3, spline_p4);
//
//	std::vector<glm::vec3> splinePoints;
//
//	for (int i = 0; i <= 30; i++)
//	{
//		//float time = 0.1 * i;
//		float time = (std::atan(5 * (0.1 * i - 1.5)) + M_PI / 2) / M_PI * 3.0;
//		glm::vec4 t(std::pow(time, 3), std::pow(time, 2), time, 1);
//		glm::vec3 p = glm::vec3(G * B * t);
//		splinePoints.push_back(p);
//
//		std::cout << p.x << " " << p.y << " " << p.z << std::endl;
//	}
//
//	for (int i = 29; i >= 0; i--)
//	{
//		//float time = 0.1 * i;
//		float time = (std::atan(5 * (0.1 * i - 1.5)) + M_PI / 2) / M_PI * 3.0;
//		glm::vec4 t(std::pow(time, 3), std::pow(time, 2), time, 1);
//		glm::vec3 p = glm::vec3(G * B * t);
//		splinePoints.push_back(p);
//
//		std::cout << p.x << " " << p.y << " " << p.z << std::endl;
//	}
//#pragma endregion
//// ========================================IK prepare (end) ===========================================================
//
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
//		processInput_cube(window);
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
//
//
//// ========================================IK Bone Setting (start)==========================================================
//#pragma region
//		glm::vec3 bone1_position = glm::vec3(posx, posy, posz);
//
//		float posX = (cursorPosX - (screenWidth / 2)) / float(screenWidth / 2) * 5.0f;
//		float posY = -(cursorPosY - (screenHeight / 2)) / float(screenHeight / 2) * 5.0f;  // minus symbol check
//
//
//		//cout << "x=" << posX << ", y="<< posY << endl;
//
//		// bone parameters
//		float L1 = 2;  // bone 1 length
//		float L2 = 1.5;  // bone 2 length
//		float d = std::sqrt(posX * posX + posY * posY);  // distance of target to origin 
//		float theta_T = std::acos(posX / std::sqrt(posX * posX + posY * posY));  // angle for target point
//		float angle_T;
//
//		float tempTheta_1 = std::acos((L1 * L1 + posX * posX + posY * posY - L2 * L2) / (2 * L1 * std::sqrt(posX * posX + posY * posY)));  // cos rule
//		float tempTheta_2 = std::acos(-(L1 * L1 + L2 * L2 - posX * posX - posY * posY) / (2 * L1 * L2));  // cos rule
//
//		//cout << "d=" << d << ", theta_T=" << theta_T << endl;
//
//		// target over the distance of two bones' length sum
//		if (d > (L1 + L2))
//		{
//			//if (posY > 0) theta_1 = std::acos(posX / std::sqrt(posX * posX + posY * posY));
//			if (posY > 0) theta_1 = theta_T;
//			else theta_1 = -theta_T;
//
//			theta_2 = 0;
//		}
//		// target inside the area two bones can reach to
//		else if (d < std::abs(L1 - L2))
//		{
//			if (posY > 0) theta_1 = theta_T;
//			else theta_1 = -theta_T;
//
//			theta_2 = M_PI;
//		}
//		// to avoid the bones flip when go beyond x_axis or y_axis, devide them to 2 cases
//		else if (posY > 0)
//		{
//			theta_1 = tempTheta_1 + theta_T;
//			theta_2 = -tempTheta_2;
//		}
//		else
//		{
//			theta_1 = -(theta_T - tempTheta_1);
//			theta_2 = -tempTheta_2;
//		}
//#pragma endregion
//		// ========================================IK Bone Setting (end) ===========================================================
//
//
//// ========================================CCD 3D (start)==========================================================
//#pragma region
//		float time = glfwGetTime();
//		cube_position = splinePoints[int(time * 10) % 61];
//
//		int counter = 5000;
//		float clip_angle = 0.05;
//
//		trans = glm::toMat4(limb1_quat);
//		limb2_position = glm::mat3(trans) * glm::vec3(limb1_length, 0.0f, 0.0f) + limb1_position;
//		trans *= glm::toMat4(limb2_quat);
//		limb3_position = glm::mat3(trans) * glm::vec3(limb2_length, 0.0f, 0.0f) + limb2_position;
//		trans *= glm::toMat4(limb3_quat);
//		finger1_position = glm::mat3(trans) * glm::vec3(limb3_length, 0.0f, 0.0f) + limb3_position;
//		trans *= glm::toMat4(finger1_quat);
//		humanchain_endPosition = glm::mat3(trans) * glm::vec3(finger1_length, 0.0f, 0.0f) + finger1_position;
//
//		while (--counter)
//		{
//			if (CCDoverCondition(cube_position, limb1_position, humanchain_length, humanchain_endPosition))
//				break;
//
//			glm::vec3 p2e;
//			glm::vec3 p2t;
//			float angle;
//			p2e = glm::normalize(humanchain_endPosition - finger1_position);
//			p2t = glm::normalize(cube_position - finger1_position);
//			angle = std::acos(std::max(std::min(glm::dot(p2e, p2t), 1.0f), -1.0f));
//
//			if (angle >= 0.005)
//			{
//				if (angle > clip_angle) angle = clip_angle;
//
//				rotAxis = glm::normalize(glm::cross(p2e, p2t));
//				rot = glm::angleAxis(angle, rotAxis);
//				finger1_quat = rot * finger1_quat;
//
//				trans = glm::toMat4(limb1_quat);
//				limb2_position = glm::mat3(trans) * glm::vec3(limb1_length, 0.0f, 0.0f) + limb1_position;
//				trans *= glm::toMat4(limb2_quat);
//				limb3_position = glm::mat3(trans) * glm::vec3(limb2_length, 0.0f, 0.0f) + limb2_position;
//				trans *= glm::toMat4(limb3_quat);
//				finger1_position = glm::mat3(trans) * glm::vec3(limb3_length, 0.0f, 0.0f) + limb3_position;
//				trans *= glm::toMat4(finger1_quat);
//				humanchain_endPosition = glm::mat3(trans) * glm::vec3(finger1_length, 0.0f, 0.0f) + finger1_position;
//			}
//			if (CCDoverCondition(cube_position, limb1_position, humanchain_length, humanchain_endPosition))
//				break;
//
//			p2e = glm::normalize(humanchain_endPosition - limb3_position);
//			p2t = glm::normalize(cube_position - limb3_position);
//			angle = std::acos(std::max(std::min(glm::dot(p2e, p2t), 1.0f), -1.0f));
//
//			if (angle >= 0.005)
//			{
//				if (angle > clip_angle) angle = clip_angle;
//
//				rotAxis = glm::normalize(glm::cross(p2e, p2t));
//				rot = glm::angleAxis(angle, rotAxis);
//				limb3_quat = rot * limb3_quat;
//
//				trans = glm::toMat4(limb1_quat);
//				limb2_position = glm::mat3(trans) * glm::vec3(limb1_length, 0.0f, 0.0f) + limb1_position;
//				trans *= glm::toMat4(limb2_quat);
//				limb3_position = glm::mat3(trans) * glm::vec3(limb2_length, 0.0f, 0.0f) + limb2_position;
//				trans *= glm::toMat4(limb3_quat);
//				finger1_position = glm::mat3(trans) * glm::vec3(limb3_length, 0.0f, 0.0f) + limb3_position;
//				trans *= glm::toMat4(finger1_quat);
//				humanchain_endPosition = glm::mat3(trans) * glm::vec3(finger1_length, 0.0f, 0.0f) + finger1_position;
//			}
//			if (CCDoverCondition(cube_position, limb1_position, humanchain_length, humanchain_endPosition))
//				break;
//
//			p2e = glm::normalize(humanchain_endPosition - limb2_position);
//			p2t = glm::normalize(cube_position - limb2_position);
//			angle = std::acos(std::max(std::min(glm::dot(p2e, p2t), 1.0f), -1.0f));
//
//			if (angle >= 0.005)
//			{
//				if (angle > clip_angle) angle = clip_angle;
//
//				rotAxis = glm::normalize(glm::cross(p2e, p2t));
//				rot = glm::angleAxis(angle, rotAxis);
//				limb2_quat = rot * limb2_quat;
//
//				trans = glm::toMat4(limb1_quat);
//				limb2_position = glm::mat3(trans) * glm::vec3(limb1_length, 0.0f, 0.0f) + limb1_position;
//				trans *= glm::toMat4(limb2_quat);
//				limb3_position = glm::mat3(trans) * glm::vec3(limb2_length, 0.0f, 0.0f) + limb2_position;
//				trans *= glm::toMat4(limb3_quat);
//				finger1_position = glm::mat3(trans) * glm::vec3(limb3_length, 0.0f, 0.0f) + limb3_position;
//				trans *= glm::toMat4(finger1_quat);
//				humanchain_endPosition = glm::mat3(trans) * glm::vec3(finger1_length, 0.0f, 0.0f) + finger1_position;
//			}
//			if (CCDoverCondition(cube_position, limb1_position, humanchain_length, humanchain_endPosition))
//				break;
//
//			p2e = glm::normalize(humanchain_endPosition - limb1_position);
//			p2t = glm::normalize(cube_position - limb1_position);
//			angle = std::acos(std::max(std::min(glm::dot(p2e, p2t), 1.0f), -1.0f));
//
//			if (angle >= 0.005)
//			{
//				if (angle > clip_angle) angle = clip_angle;
//
//				rotAxis = glm::normalize(glm::cross(p2e, p2t));
//				rot = glm::angleAxis(angle, rotAxis);
//				limb1_quat = rot * limb1_quat;
//
//				trans = glm::toMat4(limb1_quat);
//				limb2_position = glm::mat3(trans) * glm::vec3(limb1_length, 0.0f, 0.0f) + limb1_position;
//				trans *= glm::toMat4(limb2_quat);
//				limb3_position = glm::mat3(trans) * glm::vec3(limb2_length, 0.0f, 0.0f) + limb2_position;
//				trans *= glm::toMat4(limb3_quat);
//				finger1_position = glm::mat3(trans) * glm::vec3(limb3_length, 0.0f, 0.0f) + limb3_position;
//				trans *= glm::toMat4(finger1_quat);
//				humanchain_endPosition = glm::mat3(trans) * glm::vec3(finger1_length, 0.0f, 0.0f) + finger1_position;
//			}
//		}
//#pragma endregion
//// ========================================CCD 3D (end) ===========================================================
//
//
//				// ========================================teapot (start)==========================================================
//#pragma region
//
//		shader_reflection.use();
//		trans = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
//		modelMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
//		shader_reflection.setMat4("transform", trans);
//		shader_reflection.setMat4("modelMat", modelMat);
//		shader_reflection.setMat4("viewMat", viewMat);
//		shader_reflection.setMat4("projMat", projMat);
//		shader_ground.setVec3("viewPos", camera.Position);
//		human.Draw(shader_reflection);
//
//		trans = glm::toMat4(limb1_quat);
//		modelMat = glm::translate(glm::mat4(1.0f), limb1_position);
//		shader_reflection.setMat4("transform", trans);
//		shader_reflection.setMat4("modelMat", modelMat);
//		shader_reflection.setMat4("viewMat", viewMat);
//		shader_reflection.setMat4("projMat", projMat);
//		shader_ground.setVec3("viewPos", camera.Position);
//		human_limb.Draw(shader_reflection);
//
//		trans *= glm::toMat4(limb2_quat);
//		modelMat = glm::translate(glm::mat4(1.0f), limb2_position);
//		shader_reflection.setMat4("transform", trans);
//		shader_reflection.setMat4("modelMat", modelMat);
//		human_limb.Draw(shader_reflection);
//
//		trans *= glm::toMat4(limb3_quat);
//		modelMat = glm::translate(glm::mat4(1.0f), limb3_position);
//		shader_reflection.setMat4("transform", trans);
//		shader_reflection.setMat4("modelMat", modelMat);
//		human_limb.Draw(shader_reflection);
//
//		glm::vec3 finger_z = glm::mat3(trans) * glm::vec3(0.0f, 0.0f, 1.0f);
//		rot = glm::angleAxis(glm::radians(45.0f), finger_z);
//		glm::quat subfinger_quat = rot * finger1_quat;
//		glm::mat4 trans2 = trans * glm::toMat4(subfinger_quat);
//		modelMat = glm::translate(glm::mat4(1.0f), finger1_position);
//		shader_reflection.setMat4("transform", trans2);
//		shader_reflection.setMat4("modelMat", modelMat);
//		human_finger.Draw(shader_reflection);
//
//		rot = glm::angleAxis(glm::radians(-45.0f), finger_z);
//		subfinger_quat = rot * finger1_quat;
//		trans2 = trans * glm::toMat4(subfinger_quat);
//		modelMat = glm::translate(glm::mat4(1.0f), finger1_position);
//		shader_reflection.setMat4("transform", trans2);
//		shader_reflection.setMat4("modelMat", modelMat);
//		human_finger.Draw(shader_reflection);
//
//		trans *= glm::toMat4(finger1_quat);
//		modelMat = glm::translate(glm::mat4(1.0f), finger1_position);
//		shader_reflection.setMat4("transform", trans);
//		shader_reflection.setMat4("modelMat", modelMat);
//		shader_reflection.setMat4("viewMat", viewMat);
//		shader_reflection.setMat4("projMat", projMat);
//		shader_ground.setVec3("viewPos", camera.Position);
//		human_finger.Draw(shader_reflection);
//
//		shader_cube.use();
//		trans = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f));
//		modelMat = glm::translate(glm::mat4(1.0f), cube_position);
//		shader_cube.setMat4("transform", trans);
//		shader_cube.setMat4("modelMat", modelMat);
//		shader_cube.setMat4("viewMat", viewMat);
//		shader_cube.setMat4("projMat", projMat);
//		cube.Draw(shader_cube);
//
//		// bone 1
//		//shader_refraction.use();
//
//		//boneScale = glm::scale(glm::mat4(1.0f), glm::vec3(L1, L1, 1.0f));
//		//modelMat = glm::translate(glm::mat4(1.0f), bone1_position);
//		//modelMat = glm::rotate(modelMat, theta_1, glm::vec3(0.0f, 0.0f, 1.0f));
//
//		//shader_refraction.setMat4("transform", modelMat * boneScale);
//		//shader_refraction.setMat4("modelMat", modelMat);
//		//shader_refraction.setMat4("viewMat", viewMat);
//		//shader_refraction.setMat4("projMat", projMat);
//		//shader_refraction.setVec3("viewPos", camera.Position);
//		//shader_refraction.setInt("skybox", 0);
//		//shader_refraction.setFloat("refraction_ratio", refraction_ratio);
//		//glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
//		//ufoModel.Draw(shader_refraction);
//
//		//// bone 2
//		//shader_reflection.use();
//
//
//		//glm::vec3 bone2_position = glm::mat3(glm::rotate(glm::mat4(1.0f), theta_1, glm::vec3(0.0f, 0.0f, 1.0f)))
//		//	* (bone1_position + glm::vec3(L1, 0.0f, 0.0f));
//		//boneScale = glm::scale(glm::mat4(1.0f), glm::vec3(L2, L2, 1.0f));
//		//modelMat = glm::translate(modelMat, bone2_position);
//		//modelMat = glm::rotate(modelMat, theta_2, glm::vec3(0.0f, 0.0f, 1.0f));
//
//		//shader_reflection.setMat4("transform", modelMat * boneScale);
//		//shader_reflection.setMat4("modelMat", modelMat);
//		//shader_reflection.setMat4("viewMat", viewMat);
//		//shader_reflection.setMat4("projMat", projMat);
//		//shader_reflection.setInt("skybox", 0);
//		//shader_reflection.setVec3("viewPos", camera.Position);
//		//glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
//		//ufoModel.Draw(shader_reflection);
//
//
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
//		ImGui::SliderFloat("Bone1 PosX", &posx, -100.0f, 100.0f);
//		ImGui::SliderFloat("Bone1 PosY", &posy, -100.0f, 100.0f);
//		ImGui::SliderFloat("Bone1 PosZ", &posz, -100.0f, 100.0f);
//
//		ImGui::SliderFloat("PosX", &posX, -10.0f, 10.0f);
//		ImGui::SliderFloat("PosY", &posY, -10.0f, 10.0f);
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
//
//	cursorPosX = xpos;
//	cursorPosY = ypos;
//
//	//xoffset *= .5;
//	//yoffset *= .5;
//
//	// Update the angles for arm rotation based on cursor movement
//	// Here, you can use xoffset and yoffset to control the rotation speed of the arm
//	// You can experiment with different scaling factors for xoffset and yoffset to achieve the desired effect
//	theta_1 += yoffset;
//	//theta_2 -= xoffset;
//
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
//
