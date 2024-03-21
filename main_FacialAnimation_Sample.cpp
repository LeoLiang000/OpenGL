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

#include<Eigen/Dense>
#define NOMINMAX
#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <vector>

#include "mesh_Facial_Animation.h"
#include "shader_Facial_Animation.h"
#include "vbo_Facial_Animation.h"

using namespace glm;
using namespace std;

// ========================================initialize (start)==========================================================
#pragma region
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
unsigned int loadCubemap(vector<std::string> faces);

// facial animation functions
void getDeltaM(Model modelNeutral, Model modelBlend);
int pickNearestVertex(int mouseX, int mouseY, mat4 VM, mat4 P);

// window settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


// camera
Camera camera(glm::vec3(0.0f, 0.0f, 100.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool MouseButton2(false);
bool MouseButton1(false);


// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;


glm::mat4 trans;
glm::mat4 modelMat;
glm::mat4 viewMat;
glm::mat4 projMat = glm::perspective(glm::radians(45.0f), 1400.0f / 1000.0f, 0.1f, 300.0f);

float startTime = glfwGetTime();

//bool isEuler(true);
//bool isQuater(false);

#pragma endregion
// ========================================initialize (end) ===========================================================


// ========================================facial init (start)==========================================================
#pragma region

vector <vector<vec3>> vecDeltaMs;
vector<float> vecWeights;

std::vector<std::string> mesh_file_names{
		"Mery_jaw_open.obj",
		"Mery_kiss.obj",
		"Mery_l_brow_lower.obj",
		"Mery_l_brow_narrow.obj",
		"Mery_l_brow_raise.obj",
		"Mery_l_eye_closed.obj",
		"Mery_l_eye_lower_open.obj",
		"Mery_l_eye_upper_open.obj",
		"Mery_l_nose_wrinkle.obj",
		"Mery_l_puff.obj",
		"Mery_l_sad.obj",
		"Mery_l_smile.obj",
		"Mery_l_suck.obj",
		"Mery_r_brow_lower.obj",
		"Mery_r_brow_narrow.obj",
		"Mery_r_brow_raise.obj",
		"Mery_r_eye_closed.obj",
		"Mery_r_eye_lower_open.obj",
		"Mery_r_eye_upper_open.obj",
		"Mery_r_nose_wrinkle.obj",
		"Mery_r_puff.obj",
		"Mery_r_sad.obj",
		"Mery_r_smile.obj",
};


bool playAnim = false;
vector<vector<float>> animationWeights;

std::vector<int> constraintsIndex;

Eigen::VectorXf m0;
Eigen::VectorXf m;
Eigen::MatrixXf B;


vec3 NearestVertex = vec3(0, 0, 0);

vector<vec3> vecNeutralFaceVertice;
float lightX;
float lightY;
float lightZ;
float offsetX(0);
float offsetY(0);
float offsetZ(0);
int minIndex;
bool isOffsetApplied = false;
bool isWireframe = false;

#pragma endregion
// ========================================facial init (end) ===========================================================

int main()
{
	// ========================================init (start)==========================================================
#pragma region

	glfwInit();  //glfw: initializeand configure
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "FacialAnimation", NULL, NULL);
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

	glEnable(GL_DEPTH_TEST);  // configure global opengl state

#pragma endregion
	// ========================================init (end) ===========================================================

	// ========================================init shaders & models (start)==========================================================
#pragma region

	Shader sShader("assets/shaders/phong.vs", "assets/shaders/phong.fs");
	Shader shaderBall("assets/shaders/Animation/kinematic/ball.vs", "assets/shaders/Animation/kinematic/ball.fs");
	bool isUpdateVertice(true);
	Model mNeutralFace = Model("assets/blendshapes/high_res/neutral.obj", isUpdateVertice);
	Model mBall = Model("assets/models/ball/ball.obj");

	vecNeutralFaceVertice = mNeutralFace.vecVertice;




	std::vector<Model> vecBlendFacialExps;  // store all blendshape facial expressions
	for (const auto& fileName : mesh_file_names)
	{
		string tmpPath = "assets/blendshapes/high_res/" + fileName;
		vecBlendFacialExps.emplace_back(tmpPath);  // emplace_back: call Model constructor to create model object

		getDeltaM(mNeutralFace, vecBlendFacialExps.back());  // get delta between neutral face and blendshapes

	}

	// calculate delta between neutral face and other facial expressions
	



	


	for (auto elem : vecBlendFacialExps) {
		cout << elem.vecModelVertex.size() << endl;
		//for (const auto& vertex : elem.vecModelVertex) {
		//	std::cout << "Position: ("
		//		<< vertex.Position.x << ", "
		//		<< vertex.Position.y << ", "
		//		<< vertex.Position.z << ")\n";
		//}
	}





	stbi_set_flip_vertically_on_load(true); // other models flip


#pragma endregion
// ========================================init shaders & models (end) ===========================================================




// ========================================facial animation (start)==========================================================
#pragma region

	


#pragma endregion
// ========================================facial animation (end) ===========================================================


// ========================================init render loop (start)==========================================================
#pragma region
	glm::mat4 rotateMat;
	myGUI myGui(window);  // initialize IMG UI
	vec3 initialPositions;
	//std::vector<glm::vec3> initialPositions;
	// render loop
	while (!glfwWindowShouldClose(window))
	{
		if (isWireframe)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // draw in wireframe
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
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


		// ========================================draw face model (start)==========================================================
#pragma region
		glm::mat4 projMat = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		glm::mat4 viewMat = camera.GetViewMatrix();
		glm::mat4 modelMat = glm::mat4(1.0f);
		vec3 lightPos(10.0f, 50.0f, 50.0f);

		// pick nearest vertex by clicking right mouse
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
		{
			offsetX = 0.0f;
			offsetY = 0.0f;
			offsetZ = 0.0f;
			minIndex = pickNearestVertex(lastX, lastY, viewMat, projMat);
			initialPositions = mNeutralFace.vecModelVertex[minIndex].Position;
		}

		if (offsetX != 0.0 || offsetY != 0.0 || offsetZ != 0.0)
		{
			mNeutralFace.vecModelVertex[minIndex].Position = initialPositions + vec3(offsetX, offsetY, offsetZ);
		}

		// draw face
		sShader.use();
		sShader.setMat4("projection", projMat);
		sShader.setMat4("view", viewMat);
		sShader.setVec3("lightPos", lightPos);
		modelMat = glm::translate(modelMat, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		sShader.setMat4("model", modelMat);

		mNeutralFace.updateMeshVertices(mNeutralFace.vecModelVertex);  // update new position of selected vertex
		mNeutralFace.Draw(sShader);

		// draw target ball
		glm::mat4 modelMat2 = glm::translate(glm::mat4(1.0f), mNeutralFace.vecModelVertex[minIndex].Position); // translate it to nearest vertex
		shaderBall.use();
		shaderBall.setMat4("projection", projMat);
		shaderBall.setMat4("view", viewMat);
		shaderBall.setMat4("model", modelMat2);
		mBall.Draw(shaderBall);  // draw target ball




		//cout << "offset applied: " << isOffsetApplied << endl;


		//cout << "x:" << vecNeutralFaceVertice[minIndex].x << endl;
		
		//update new vertice and then draw
		//for (int i=0; i< mNeutralFace.vecModelVertex.size(); i++)
		//{
		//	mNeutralFace.vecModelVertex[i].Position = vecNeutralFaceVertice[i];
		//}


		//mNeutralFace.Draw(sShader);
		

#pragma endregion
		// ========================================draw face model (end) ===========================================================

		// ========================================IMGUI (start)==========================================================
#pragma region
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("IMGUI Editor");

		//ImGui::Text();
		//if (ImGui::RadioButton("isOffestApplied", isOffsetApplied)) {
		//	
		//}
		//else {
		//	isOffsetApplied = true;
		//}

		//ImGui::Checkbox("isOffestApplied", &isOffsetApplied);
		ImGui::Checkbox("isWireframe", &isWireframe);

		//ImGui::SliderInt("slider int", &i1, -1, 3);

		ImGui::SliderFloat("lightX", &lightX, -1000.0f, 10000.0f);
		ImGui::SliderFloat("lightY", &lightY, -1000.0f, 10000.0f);
		ImGui::SliderFloat("lightZ", &lightZ, -1000.0f, 10000.0f);

		ImGui::SliderFloat("offsetX", &offsetX, -10.0f, 10.0f);
		ImGui::SliderFloat("offsetY", &offsetY, -10.0f, 10.0f);
		ImGui::SliderFloat("offsetZ", &offsetZ, -10.0f, 10.0f);

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

	// UI
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
		MouseButton2 = true;
	else
		MouseButton2 = false;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
		MouseButton1 = true;
	else
		MouseButton1 = false;





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


void getDeltaM(Model modelNeutral, Model modelBlend)
{
	vector<vec3> deltaM;

	for (int i = 0; i < modelNeutral.vecModelVertex.size(); i++) 
	{
		vec3 tmpVertex;

		tmpVertex.x = modelNeutral.vecModelVertex[i].Position.x - modelBlend.vecModelVertex[i].Position.x;
		tmpVertex.y = modelNeutral.vecModelVertex[i].Position.y - modelBlend.vecModelVertex[i].Position.y;
		tmpVertex.z = modelNeutral.vecModelVertex[i].Position.z - modelBlend.vecModelVertex[i].Position.z;

		deltaM.push_back(tmpVertex);
	}

	vecDeltaMs.push_back(deltaM);
	vecWeights.push_back(0.0f);
}

int pickNearestVertex(int mouseX, int mouseY, mat4 VM, mat4 PM)
{
	// find nearest vertex from mouse click
	// convert mouse coordinates to normalized device coordinate NDC
	float x = (2.0f * lastX) / SCR_WIDTH - 1.0f;
	float y = 1.0f - (2.0f * lastY) / SCR_HEIGHT;
	float z = 1.0f; // For a ray, we can use z = 1.0f to shoot the ray forward.

	vec3 ray_ndc = vec3(static_cast<float>(x), static_cast<float>(y), z);
	vec4 ray_clip = vec4(ray_ndc, -1.0f);
	vec4 ray_eye = inverse(PM) * ray_clip;
	ray_eye = vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);

	vec4 ray_eye_world = inverse(VM) * ray_eye;
	vec3 ray_wor = vec3(ray_eye_world.x, ray_eye_world.y, ray_eye_world.z);
	ray_wor = normalize(ray_wor); // It's a direction so should be normalized.

	float minDistance = std::numeric_limits<float>::max();
	int closestVertexIndex = -1;
	for (size_t i = 0; i < vecNeutralFaceVertice.size(); ++i) {

		glm::vec3 vecToVertex = vecNeutralFaceVertice[i] - camera.Position;
		float projectionLength = glm::dot(vecToVertex, ray_wor);
		glm::vec3 projectionPoint = camera.Position + projectionLength * ray_wor;
		float distance = glm::length(vecNeutralFaceVertice[i] - projectionPoint);

		if (distance < minDistance) {
			minDistance = distance;
			closestVertexIndex = i;
		}
	}
	//vec3& vertex = vecNeutralFaceVertice[closestVertexIndex];
	return closestVertexIndex;
}


//vec3 pickVertex(int x, int y, mat4 VM, mat4 P, Model& NeutralFace)
//{
//	vec3 window;
//	window.x = x;
//	window.y = height - y - 1;
//	glReadPixels(x, height - y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &window.z);
//
//	vec3 mouseVerticePosition = unProject(window, VM, P, vec4(0.0f, 0.0f, SCR_WIDTH, SCR_HEIGHT));
//
//	// find nearest vertex 
//	double minDist = numeric_limits<double>::max();  // minimum distance of mouse position and vertex of neutral face
//	double tmpDist;
//	GLuint closestVerIndex = 0; // index of closest vertex
//
//	// brute force through all vertices to find nearest one 
//	for (int j = 0; j < NeutralFace.vecModelVertex.size(); j++)
//	{
//		tmpDist = distance(mouseVerticePosition, NeutralFace.vecModelVertex[j].Position);
//
//		if (tmpDist <= minDist)
//		{
//			minDist = tmpDist;
//			closestVerIndex = j;
//		}
//	}
//	vec3 vertex = NeutralFace.vecModelVertex[closestVerIndex].Position;
//
//	constraintsIndex.push_back(closestVerIndex); //add index of constrained vertex to list of constraints
//	m0.conservativeResize(constraintsIndex.size() * 3);
//	m0(3 * constraintsIndex.size() - 3) = vertex.x;
//	m0(3 * constraintsIndex.size() - 2) = vertex.y;
//	m0(3 * constraintsIndex.size() - 1) = vertex.z;
//
//	return vertex;
//}
























float calcDistance(const vec3& p1, const vec3& p2) {
	return std::sqrt((p2.x - p1.x) * (p2.x - p1.x) +
					 (p2.y - p1.y) * (p2.y - p1.y) +
					 (p2.z - p1.z) * (p2.z - p1.z));
}

void read_anim_text_file() {
	fstream newfile;
	std::string delimiter = " ";
	std::string weight;
	newfile.open("assets/blendshapes/blendshape_animation.txt", ios::in);
	if (newfile.is_open())
	{
		string line;
		while (getline(newfile, line)) {
			size_t pos = 0;
			vector<float> lineWeights;

			while ((pos = line.find(delimiter)) != std::string::npos) {
				std::string weight = line.substr(0, pos);
				lineWeights.push_back(std::stof(weight));
				line.erase(0, pos + delimiter.length());
			}
			animationWeights.push_back(lineWeights);
		}
		newfile.close(); //close the file object.
	}
}

void removeWordFromLine(std::string& line, const std::string& word)
{
	auto n = line.find(word);
	if (n != std::string::npos)
	{
		line.erase(n, word.length());
	}
}

//glm::mat4 view;
//glm::mat4 persp_proj;
//void init_facial()
//{
//	glUseProgram(shaderProgramID);
//
//	// load mesh into a vertex buffer array
//	int matrix_location = glGetUniformLocation(shaderProgramID, "model");
//	int view_mat_location = glGetUniformLocation(shaderProgramID, "view");
//	int proj_mat_location = glGetUniformLocation(shaderProgramID, "proj");
//
//	// Root of the Hierarchy
//	view = glm::mat4(1.0f);
//	view = glm::translate(view, glm::vec3(0.0f, -15.0f, -50.0f));
//	persp_proj = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
//
//	// update uniforms & draw
//	glUniformMatrix4fv(proj_mat_location, 1, GL_FALSE, glm::value_ptr(persp_proj));
//	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, glm::value_ptr(view));
//
//	glm::mat4 modelNeutralFace;
//	loadNeutral(modelNeutralFace, matrix_location);
//
//	glm::mat4 modelVertexPicker;
//	loadVertexPicker(modelVertexPicker, matrix_location);
//
//	
//
//	
//
//
//	string mesh_neutral = "assets/blendshapes/high-res-blendshapes/neutral.obj";
//	string mesh_vertex = "assets/blendshapes/high-res-blendshapes/picker.dae";
//
//	read_anim_text_file();
//
//	for (std::string name : mesh_file_names) {
//		std::string label = name;
//		removeWordFromLine(label, ".obj");
//		removeWordFromLine(label, "Mery_");
//		labels.push_back(label);
//	}
//
//	// Set up the shaders
//	shaderProgramID = CompileShaders();
//
//
//	//mesh_data_vertex_picker = load_mesh(MESH_VERTEX);
//
//	std::cout << "Calculating deltaM vertices..." << std::endl;
//	for (std::string name : mesh_file_names) {
//		std::string filepath = "models/high-res2/" + name;
//
//		ModelData mesh_data = load_mesh(filepath.c_str());
//
//
//		calcDeltaM(mesh_data);
//
//	}
//	std::cout << "Finished loading deltaM vertices." << std::endl;
//
//}



//bool activate = false;
//glm::vec3 rotate_face = glm::vec3(0, -10.0f, 0);
//void loadNeutral(glm::mat4& modelNeutral, int matrix_location)
//{
//	modelNeutral = glm::mat4(1.0f);
//	generateObjectBufferMesh(mesh_data_neutral, shaderProgramID);
//	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, glm::value_ptr(modelNeutral));
//	glDrawArrays(GL_TRIANGLES, 0, mesh_data_neutral.mPointCount);
//}
//
//glm::vec3 pickerLocation = glm::vec3(0, 0, 0);
//void loadVertexPicker(glm::mat4& modelVertexPicker, int matrix_location)
//{
//
//	modelVertexPicker = glm::mat4(1.0f);
//	modelVertexPicker = glm::translate(modelVertexPicker, pickerLocation);
//
//	//generateObjectBufferMesh(mesh_data_vertex_picker, shaderProgramID);
//
//	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, glm::value_ptr(modelVertexPicker));
//	glDrawArrays(GL_TRIANGLES, 0, mesh_data_vertex_picker.mPointCount);
//}
//
//void applyDeltaM(ModelData& mesh_data_neutral, std::vector<glm::vec3> deltaM, float weight)
//{
//
//	for (unsigned int i = 0; i < mesh_data_neutral.mPointCount; i++) {
//		mesh_data_neutral.mVertices[i].x -= deltaM[i].x * weight;
//		mesh_data_neutral.mVertices[i].y -= deltaM[i].y * weight;
//		mesh_data_neutral.mVertices[i].z -= deltaM[i].z * weight;
//	}
//
//}
//
//glm::vec3 vertexPicker(int x, int y, glm::mat4 VM, glm::mat4 P, ModelData currentFaceMesh)
//{
//	glm::vec3 window;
//	window.x = x;
//	window.y = height - y - 1;
//	glReadPixels(x, height - y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &window.z);
//
//	glm::vec3 mouseVerticePosition = glm::unProject(window, VM, P, glm::vec4(0.0f, 0.0f, width, height));
//
//	// find nearest vertex 
//	GLfloat dist = 10;
//	GLfloat temp = 0.0f;
//	GLuint v_index = 0; // index of closest vertex
//
//	// brute force through all vertices to find nearest one 
//	for (int j = 0; j < currentFaceMesh.mVertices.size(); j++)
//	{
//		temp = calcDistance(mouseVerticePosition, currentFaceMesh.mVertices[j]);
//		if (temp <= dist) {
//			dist = temp;
//
//			v_index = j;
//		}
//
//	}
//
//	glm::vec3 vertex = currentFaceMesh.mVertices[v_index];
//	constraints_index.push_back(v_index); //add index of constrained vertex to list of constraints
//	m0.conservativeResize(constraints_index.size() * 3);
//	m0(3 * constraints_index.size() - 3) = vertex.x;
//	m0(3 * constraints_index.size() - 2) = vertex.y;
//	m0(3 * constraints_index.size() - 1) = vertex.z;
//	return vertex;
//}
//
//void getMouseLocation(int x, int y, glm::mat4 VM, glm::mat4 P, int chosenVertexIndex) {
//	glm::vec3 window;
//	window.x = x;
//	window.y = height - y - 1;
//	glReadPixels(x, height - y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &window.z);
//
//	glm::vec3 targetVerticePos = glm::unProject(window, VM, P, glm::vec4(0.0f, 0.0f, width, height));
//
//	pickerLocation = targetVerticePos;
//
//	if (targetVerticePos.z < -100.0f) {
//		cout << "OUT OF BOUNDS" << endl;
//	}
//	//works better if you set the target vertice z the same
//	targetVerticePos.z = mesh_data_neutral.mVertices[constraints_index.back()].z;
//	//std::cout << "object coords are " << glm::to_string(targetVerticePos) << endl;
//
//
//
//	//constraints.push_back(v_index); //add index of constrained vertex to list of constraints
//	m.conservativeResize(constraints_index.size() * 3);
//	m(3 * constraints_index.size() - 3) = targetVerticePos.x;
//	m(3 * constraints_index.size() - 2) = targetVerticePos.y;
//	m(3 * constraints_index.size() - 1) = targetVerticePos.z;
//
//	cout << "m0" << m0 << endl;
//	cout << "m" << m << endl;
//
//}
//
//float alpha = 1;
//float mu = 0.001;
//Eigen::VectorXf blendshapeSolver(std::vector<ModelData> expressionMeshes) {
//	Eigen::MatrixXf Bbar(constraints_index.size() * 3, mesh_file_names.size());
//
//	for (int i = 0; i < constraints_index.size(); i++) {
//		for (int j = 0; j < mesh_file_names.size(); j++) {
//			Bbar(3 * i, j) = expressionMeshes[j].mVertices[constraints_index[i]].x;
//			Bbar(3 * i + 1, j) = expressionMeshes[j].mVertices[constraints_index[i]].y;
//			Bbar(3 * i + 2, j) = expressionMeshes[j].mVertices[constraints_index[i]].z;
//		}
//	}
//
//	//Left side of Equation
//	Eigen::MatrixXf LHS =
//		Bbar.transpose() * Bbar +
//		(alpha + mu) * Eigen::MatrixXf::Identity(mesh_file_names.size(), mesh_file_names.size());
//
//	//Right Side Of Equation
//	Eigen::VectorXf RHS(mesh_file_names.size());
//
//	//put mWeights into Eigen
//	Eigen::VectorXf mWeightsCurrent(mesh_file_names.size());
//	for (int i = 0; i < mWeights.size(); i++) {
//		cout << "glm mWeights: " << mWeights[i];
//		mWeightsCurrent(i) = mWeights[i];
//	}
//	cout << endl;
//	cout << "eigen mWeightsCurrent: " << mWeightsCurrent << endl;
//
//	RHS = Bbar.transpose() * (m - m0) + alpha * mWeightsCurrent;
//
//	//solve Equation
//	Eigen::LDLT<Eigen::MatrixXf> solver(LHS);
//	Eigen::VectorXf mWeightsNew = solver.solve(RHS);
//	cout << "eigen mWeightsNEW: " << mWeightsNew << endl;
//
//	return mWeightsNew;
//
//}
//
//int frame_num = 0;
//int mouse_x;
//bool mouseClickedDown = false;
//bool mouseClickedUp = false;
//glm::vec2 mousePosDown;
//glm::vec2 mousePosUp;
//int chosen_vertex_index = -1;
//void updateScene() {
//
//	static DWORD last_time = 0;
//	DWORD curr_time = glfwGetTime();
//	if (last_time == 0)
//		last_time = curr_time;
//	float delta = (curr_time - last_time) * 0.001f;
//	last_time = curr_time;
//
//	mesh_data_neutral = mesh_data_neutral_original;
//
//	if (playAnim) {
//
//		for (int i = 0; i < mesh_file_names.size(); i++) {
//			applyDeltaM(mesh_data_neutral, deltaMs[i], animationWeights[frame_num][i]);
//		}
//		frame_num++;
//		if (frame_num == animationWeights.size()) {
//			playAnim = false;
//		}
//	}
//	else {
//		for (int i = 0; i < mesh_file_names.size(); i++) {
//			applyDeltaM(mesh_data_neutral, deltaMs[i], mWeights[i]);
//			frame_num = 0;
//		}
//	}
//
//	if (mouseClickedDown) {
//		//std::cout << "MOUSE DOWN X: " << mousePosDown.x << std::endl;
//		//std::cout << "MOUSE DOWN Y: " << mousePosDown.y << std::endl;
//
//		int mesh_index = -1;
//
//		//std::cout << "View Martrix " << glm::to_string(view) << std::endl;
//
//		glm::vec3 mouseVertex = vertexPicker((int)mousePosDown.x, (int)mousePosDown.y, view, persp_proj, mesh_data_neutral);
//		//std::cout << "mesh index " << mesh_index << std::endl;
//		//std::cout << "chosen vertix is: " << glm::to_string(mouseVertex) << std::endl;
//		pickerLocation = mouseVertex;
//		mouseClickedDown = false;
//	}
//	if (mouseClickedUp) {
//		std::cout << "MOUSE UP X: " << mousePosUp.x << std::endl;
//		std::cout << "MOUSE UP Y: " << mousePosUp.y << std::endl;
//		//std::vector<ModelData> fa;
//		//neutral.push_back(mesh_data_neutral);
//
//
//		getMouseLocation((int)mousePosUp.x, (int)mousePosUp.y, view, persp_proj, chosen_vertex_index);
//		//mWeights[mesh_index]=1.0f;
//		//std::cout << "mesh index " << mesh_index << std::endl;
//
//		Eigen::VectorXf mWeightsNew = blendshapeSolver(facialExpressions);
//
//		//convert from eigen back to glm
//		std::vector<float> mWeightsNewGlm;
//		for (int i = 0; i < mWeightsNew.size(); i++) {
//			mWeightsNewGlm.push_back(mWeightsNew[i]);
//		}
//
//		mWeights = mWeightsNewGlm;
//
//		mouseClickedUp = false;
//	}
//}
