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
using namespace Eigen;

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
void ReadAnimFile();
void ApplyBlendshapeWeights(const vector<float>& weights, Model mNeutralFace);
void applyDeltaM(Model mNeutralFace, std::vector<glm::vec3> deltaM, float weight);
void computeWeights(int vertexNum, int facialExpNums, vector<Vertex> vecNeutralModelVertex);

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
static vector<float> vecWeights;
static vector<float> vecNewWeights;

std::vector<std::string> meshFileNames{
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
		"Mery_r_suck.obj",
};


bool playAnim = false;
vector<vector<float>> animationWeights;

std::vector<int> constraintsIndex;

Eigen::VectorXf m0;
Eigen::VectorXf m;
Eigen::MatrixXf B;
Eigen::MatrixXf I;
Eigen::VectorXf w_prev;

vec3 NearestVertex = vec3(0, 0, 0);

vector<vec3> vecNeutralFaceVertice;
vector<Vertex> vecModelVertexBackup;

float lightX;
float lightY;
float lightZ;
float offsetX(0);
float offsetY(0);
float offsetZ(0);
int minIndex;
bool isOffsetApplied = false;
bool isWireframe = false;
bool isVertexSelected = true;
bool isAnimation = false;
bool isSimulation = false;
bool isPlayAnim = false;
bool isCapture = false;
bool isResetFace = false;

vector<Vertex> newFace;

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

	Model mNeutralFace = Model("assets/blendshapes/high_res/neutral.obj");
	Model mBall = Model("assets/models/ball/ball.obj");

	stbi_set_flip_vertically_on_load(true); // other models flip


#pragma endregion
	// ========================================init shaders & models (end) ===========================================================


	// ========================================PartB Prepare: Facial Animation Replay (start)==========================================================
#pragma region

	vecNeutralFaceVertice = mNeutralFace.vecVertice;
	vecModelVertexBackup = mNeutralFace.vecModelVertex;
	ReadAnimFile();


	vector<Model> vecBlendFacialExps;  // store all blendshape facial expressions
	for (const auto& meshFileName : meshFileNames)
	{
		string tmpPath = "assets/blendshapes/high_res/" + meshFileName;
		vecBlendFacialExps.emplace_back(tmpPath);  // emplace_back: call Model constructor to create model object

		getDeltaM(mNeutralFace, vecBlendFacialExps.back());  // update vecDeltaMs: get all delta between neutral face and blendshapes
	}

	

#pragma endregion
	// ========================================PartB Prepare: Facial Animation Replay (end) ===========================================================



	// ========================================facial animation (start)==========================================================
#pragma region




#pragma endregion
// ========================================facial animation (end) ===========================================================


// ========================================init render loop (start)==========================================================
#pragma region
	glm::mat4 rotateMat;
	myGUI myGui(window);  // initialize IMG UI
	vec3 initialPositions;
	int frame_num = 0;
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
		vector<int> vecIndex;

		if (isVertexSelected)
		{
			// pick nearest vertex by clicking right mouse
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
			{
				offsetX = 0.0f;  // reset offset for next selected point
				offsetY = 0.0f;
				offsetZ = 0.0f;

				minIndex = pickNearestVertex(lastX, lastY, viewMat, projMat);
				initialPositions = mNeutralFace.vecModelVertex[minIndex].Position;
				
			}

			for (size_t i = 0; i < mNeutralFace.vecModelVertex.size(); ++i)
			{
				// store repetitive points
				if (mNeutralFace.vecModelVertex[i].Position == mNeutralFace.vecModelVertex[minIndex].Position)
				{
					vecIndex.push_back(i);
				}
			}


			if (offsetX != 0.0 || offsetY != 0.0 || offsetZ != 0.0)
			{
				for (int i : vecIndex)
				{
					mNeutralFace.vecModelVertex[i].Position = initialPositions + vec3(offsetX, offsetY, offsetZ);
				}
			
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
		}

		else if (isAnimation)
		{
			if (isPlayAnim)
			{
				mNeutralFace.vecModelVertex = vecModelVertexBackup;
				if (frame_num >= animationWeights.size()) {
					isPlayAnim = false;
					frame_num = 0;
				}
				std::vector<float> weights = animationWeights[frame_num];
				for (int i = 0; i < mNeutralFace.vecModelVertex.size(); i++)
				{
					vec3 finalResult(0.0f);
					for (int j = 0; j < weights.size(); j++)
					{
						finalResult += vecDeltaMs[j][i] * weights[j];
					}

					mNeutralFace.vecModelVertex[i].Position += finalResult;

				}
			}

			frame_num++;

			sShader.use();
			sShader.setMat4("projection", projMat);
			sShader.setMat4("view", viewMat);
			sShader.setVec3("lightPos", lightPos);
			modelMat = glm::translate(modelMat, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
			sShader.setMat4("model", modelMat);

			//mNeutralFace.updateMeshVertices(vecModelVertexBackup);
			mNeutralFace.updateMeshVertices(mNeutralFace.vecModelVertex);  // update new position of selected vertex

			mNeutralFace.Draw(sShader);

		}

		else if (isSimulation)
		{
			if (!isCapture)
			{
				// reset to neutral face
				mNeutralFace.vecModelVertex = vecModelVertexBackup;

				for (int i = 0; i < mNeutralFace.vecModelVertex.size(); i++)
				{
					vec3 tmpDelta(0.0f);
					for (int j = 0; j < vecWeights.size(); j++)
					{
						tmpDelta += vecDeltaMs[j][i] * vecWeights[j];
					}

					mNeutralFace.vecModelVertex[i].Position += tmpDelta;
				}
			}
			else 
			{
				newFace = mNeutralFace.vecModelVertex;
				
				if (isResetFace)
				{
					mNeutralFace.vecModelVertex = vecModelVertexBackup;
				}



			}


			sShader.use();
			sShader.setMat4("projection", projMat);
			sShader.setMat4("view", viewMat);
			sShader.setVec3("lightPos", lightPos);
			modelMat = glm::translate(modelMat, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
			sShader.setMat4("model", modelMat);

			//mNeutralFace.updateMeshVertices(vecModelVertexBackup);
			mNeutralFace.updateMeshVertices(mNeutralFace.vecModelVertex);  // update new position of selected vertex

			mNeutralFace.Draw(sShader);

			//reset
			//mNeutralFace.vecModelVertex = vecModelVertexBackup;
			//mNeutralFace.updateMeshVertices(mNeutralFace.vecModelVertex);




		}
	


			//for (const auto& frameWeights : animationWeights) {
			//	ApplyBlendshapeWeights(frameWeights, mNeutralFace);

			//	// ... (The rest of your rendering and application loop)
			//}

		







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
		if (ImGui::RadioButton("Vertex Pick", isVertexSelected)) {
			isVertexSelected = true;
			isAnimation = false;
			isSimulation = false;
		}
		ImGui::SameLine();
		if ((ImGui::RadioButton("Animation", isAnimation))) {
			isVertexSelected = false;
			isAnimation = true;
			isSimulation = false;
		}
		ImGui::SameLine();
		if ((ImGui::RadioButton("Simulation", isSimulation))) {
			isVertexSelected = false;
			isAnimation = false;
			isSimulation = true;
		}

		ImGui::Checkbox("Wireframe", &isWireframe);
		ImGui::SameLine();
		// ImGui::Checkbox("Capture Face", &isCapture);
		if (ImGui::Button("Capture Face"))
		{
			computeWeights(mNeutralFace.vecModelVertex.size(), vecBlendFacialExps.size(), mNeutralFace.vecModelVertex);
		}

		if (ImGui::Button("Reset Neutral Face"))
		{
			mNeutralFace.vecModelVertex = vecModelVertexBackup;
			std::fill(vecWeights.begin(), vecWeights.end(), 0.0f);
		}
		if (ImGui::Button("Reconstruct Face"))
		{
			// reset to neutral face
			mNeutralFace.vecModelVertex = vecModelVertexBackup;

			for (int i = 0; i < mNeutralFace.vecModelVertex.size(); i++)
			{
				vec3 tmpDelta(0.0f);
				for (int j = 0; j < vecNewWeights.size(); j++)
				{
					tmpDelta += vecDeltaMs[j][i] * vecNewWeights[j];
					vecWeights[j] = vecNewWeights[j];
				}

				mNeutralFace.vecModelVertex[i].Position += tmpDelta;
			}
		}
		
		//ImGui::Checkbox("Reset Neutral Face", &isResetFace);

		if (isSimulation)
		{
			ImGui::SliderFloat("jaw_open", &vecWeights[0], 0.0f, 1.0f);
			ImGui::SliderFloat("kiss", &vecWeights[1], 0.0f, 1.0f);
			ImGui::SliderFloat("l_brow_lower", &vecWeights[2], 0.0f, 1.0f);
			ImGui::SliderFloat("l_brow_narrow", &vecWeights[3], 0.0f, 1.0f);
			ImGui::SliderFloat("l_brow_raise", &vecWeights[4], 0.0f, 1.0f);
			ImGui::SliderFloat("l_eye_closed", &vecWeights[5], 0.0f, 1.0f);
			ImGui::SliderFloat("l_eye_lower_open", &vecWeights[6], 0.0f, 1.0f);
			ImGui::SliderFloat("l_eye_upper_open", &vecWeights[7], 0.0f, 1.0f);
			ImGui::SliderFloat("l_nose_wrinkle", &vecWeights[8], 0.0f, 1.0f);
			ImGui::SliderFloat("l_puff", &vecWeights[9], 0.0f, 1.0f);
			ImGui::SliderFloat("l_sad", &vecWeights[10], 0.0f, 1.0f);
			ImGui::SliderFloat("l_smile", &vecWeights[11], 0.0f, 1.0f);
			ImGui::SliderFloat("l_suck", &vecWeights[12], 0.0f, 1.0f);
			ImGui::SliderFloat("r_brow_lower", &vecWeights[13], 0.0f, 1.0f);
			ImGui::SliderFloat("r_brow_narrow", &vecWeights[14], 0.0f, 1.0f);
			ImGui::SliderFloat("r_brow_raise", &vecWeights[15], 0.0f, 1.0f);
			ImGui::SliderFloat("r_eye_closed", &vecWeights[16], 0.0f, 1.0f);
			ImGui::SliderFloat("r_eye_lower_open", &vecWeights[17], 0.0f, 1.0f);
			ImGui::SliderFloat("r_eye_upper_open", &vecWeights[18], 0.0f, 1.0f);
			ImGui::SliderFloat("r_nose_wrinkle", &vecWeights[19], 0.0f, 1.0f);
			ImGui::SliderFloat("r_puff", &vecWeights[20], 0.0f, 1.0f);
			ImGui::SliderFloat("r_sad", &vecWeights[21], 0.0f, 1.0f);
			ImGui::SliderFloat("r_smile", &vecWeights[22], 0.0f, 1.0f);
			ImGui::SliderFloat("r_suck", &vecWeights[23], 0.0f, 1.0f);


		}
		else
		{
			ImGui::Checkbox("PlayAnimation", &isPlayAnim);

			ImGui::SliderFloat("offsetX", &offsetX, -50.0f, 50.0f);
			ImGui::SliderFloat("offsetY", &offsetY, -50.0f, 50.0f);
			ImGui::SliderFloat("offsetZ", &offsetZ, -50.0f, 50.0f);
		}


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


void getDeltaM(Model modelNeutral, Model modelBlend)
{
	vector<vec3> deltaM;

	for (int i = 0; i < modelNeutral.vecModelVertex.size(); i++)
	{
		vec3 tmpVertex;

		tmpVertex.x = modelNeutral.vecModelVertex[i].Position.x - modelBlend.vecModelVertex[i].Position.x;
		tmpVertex.y = modelNeutral.vecModelVertex[i].Position.y - modelBlend.vecModelVertex[i].Position.y;
		tmpVertex.z = modelNeutral.vecModelVertex[i].Position.z - modelBlend.vecModelVertex[i].Position.z;

		deltaM.push_back(-tmpVertex);
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
	return closestVertexIndex;
}


void ReadAnimFile() {
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

void computeWeights(int vertexNum, int facialExpNums, vector<Vertex> vecNeutralModelVertex)
{
	unsigned int num_rows = static_cast<unsigned int>(vertexNum) * 3;
	unsigned int num_cols = static_cast<unsigned int>(facialExpNums);

	// Equation: (BT.B + (a+u).I).W = BT.(m-m0) + a.Wt-1
	float a(0.1);																	 // alpha	
	float u(0.001);																	 // mu
	Eigen::MatrixXf B(num_rows, num_cols);											 // Matrix B: containing deltas to solve weights
	Eigen::MatrixXf I = MatrixXf::Identity(num_cols, num_cols);						 // Identity Matrix I
	Eigen::VectorXf m(num_rows);													 // Vector New Facial Vertice Matrix
	Eigen::VectorXf m0(num_rows);													 // Vector Previous Facial Vertice Matrix
	Eigen::VectorXf w_prev(num_cols);												 // The weights from the previous time step

	// populate matrix B
	for (unsigned int col = 0; col < vecDeltaMs.size(); ++col) {
		for (unsigned int row = 0; row < vecDeltaMs[0].size(); ++row) { // iterate over vertices
			B(row * 3 + 0, col) = vecDeltaMs[col][row].x;							 // X component
			B(row * 3 + 1, col) = vecDeltaMs[col][row].y;							 // Y component
			B(row * 3 + 2, col) = vecDeltaMs[col][row].z;							 // Z component
		}
	}

	// populate m and m0 with the current and original positions of the vertices
	assert(vertexNum == vecNeutralFaceVertice.size());
	for (unsigned int i = 0; i < vertexNum; ++i) {
		m(i * 3 + 0) = vecNeutralModelVertex[i].Position.x;							 // Current X position
		m(i * 3 + 1) = vecNeutralModelVertex[i].Position.y;							 // Current Y position
		m(i * 3 + 2) = vecNeutralModelVertex[i].Position.z;							 // Current Z position

		m0(i * 3 + 0) = vecNeutralFaceVertice[i].x;									 // Original X position
		m0(i * 3 + 1) = vecNeutralFaceVertice[i].y;									 // Original Y position
		m0(i * 3 + 2) = vecNeutralFaceVertice[i].z;									 // Original Z position
	}


	// populate weights from the previous time step
	for (unsigned int i = 0; i < vecWeights.size(); ++i) {
		w_prev(i) = vecWeights[i];
	}

	// set up the equation
	MatrixXf leftEquation = B.transpose() * B + (a + u) * I;
	VectorXf rightEquation = B.transpose() * (m - m0) + a * w_prev;
	VectorXf w = leftEquation.ldlt().solve(rightEquation);

	vecNewWeights.resize(num_cols);
	for (unsigned int i = 0; i < num_cols; ++i) {
		vecNewWeights[i] = w(i);
	}



}