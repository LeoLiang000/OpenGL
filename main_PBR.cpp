//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
////#define STB_IMAGE_IMPLEMENTATION
////#include "stb_image.h"
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include "shader_m.h"
//#include "camera.h"
//#include "model_animation.h"
//
//#include <iostream>
//#include "gui.h"
//#include "LightDirectional.h"
//
//
//// ========================================claim functions & init (start)==========================================================
//#pragma region
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);
//unsigned int loadTexture(const char* path);
//void renderSphere();
//
//// settings
//const unsigned int SCR_WIDTH = 1280;
//const unsigned int SCR_HEIGHT = 720;
//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//float lastX = 800.0f / 2.0;
//float lastY = 600.0 / 2.0;
//bool firstMouse = true;
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//// Phong
////float _smoothness(5.0);
//bool MouseButton2(false);
//bool blinn = false;
//
//
//glm::mat4 trans;
//
//#pragma endregion
//// ========================================claim functions (end) ===========================================================
//
//
//
//// ========================================init (start)==========================================================
//#pragma region
//
//int main()
//{
//    // glfw: initialize and configure
//    // ------------------------------
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_SAMPLES, 4);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//    // glfw window creation
//    // --------------------
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Rendering", NULL, NULL);
//    glfwMakeContextCurrent(window);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetScrollCallback(window, scroll_callback);
//
//    // tell GLFW to capture our mouse
//    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//    // glad: load all OpenGL function pointers
//    // ---------------------------------------
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    // configure global opengl state
//    // -----------------------------
//    glEnable(GL_DEPTH_TEST);
//#pragma endregion
//// ========================================init (end) ===========================================================
//
//// ========================================create shaders (start)==========================================================
//#pragma region
//    Shader shader("assets/shaders/pbr.vs", "assets/shaders/pbr.fs");
//    Shader shaderPhong("assets/shaders/phongTest.vs", "assets/shaders/phongTest.fs");
//    //Shader shaderPhong("assets/shaders/BPhong.vs", "assets/shaders/BPhong.fs");
//    Shader shaderNonPhoto("assets/shaders/nonPhoto.vs", "assets/shaders/nonPhoto.fs");
//
//    unsigned int floorTexture = loadTexture("assets/container.jpg");
//
//    shaderNonPhoto.use();
//    LightDirectional lightD(glm::vec3(40.0f, 30.0f, 20.0f), glm::vec3(glm::radians(110.0f), glm::radians(30.0f), 0), glm::vec3(5.0f, 5.0f, 5.0f));
//    shaderNonPhoto.setVec3("lightD.pos", glm::vec3(lightD.position.x, lightD.position.y, lightD.position.z));
//    shaderNonPhoto.setVec3("lightD.color", glm::vec3(lightD.color.x, lightD.color.y, lightD.color.z));
//    shaderNonPhoto.setVec3("lightD.dirToLight", glm::vec3(lightD.direction.x, lightD.direction.y, lightD.direction.z));
//
//    shader.use();
//    shader.setVec3("albedo", 0.5f, 0.0f, 0.0f);
//    shader.setFloat("ao", 1.0f);
//    // lights
//    // ------
//    glm::vec3 lightPositions[] = { glm::vec3(-10.0f,  10.0f, 10.0f) };
//    glm::vec3 lightColors[] = { glm::vec3(300.0f, 300.0f, 300.0f) };
//    int nrRows = 7;
//    int nrColumns = 7;
//    float spacing = 2.5;
//
//    //phong light position
//    glm::vec3 PhonglightPos(0.0f, 0.0f, 0.0f);
//
//    // initialize static shader uniforms before rendering
//    // --------------------------------------------------
//    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//    shader.use();
//    shader.setMat4("projection", projection);
//#pragma endregion
//// ========================================create shaders (end) ===========================================================
//
//    myGUI myGui(window);  // initialize IMG UI
//
//// ========================================RenderLoop (start)==========================================================
//#pragma region
//        // render loop
//    // -----------
//    while (!glfwWindowShouldClose(window))
//    {
//        float timeValue = glfwGetTime();
//
//        // per-frame time logic
//        // --------------------
//        float currentFrame = static_cast<float>(glfwGetTime());
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        // input
//        // -----
//        processInput(window);
//
//        // render
//        // ------
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//
//
//#pragma endregion
//// ========================================RenderLoop (end) ===========================================================
//
//// ========================================model_PBR (start)==========================================================
//#pragma region
//        shader.use();
//        glm::mat4 view = camera.GetViewMatrix();
//        shader.setMat4("view", view);
//        shader.setVec3("camPos", camera.Position);
//        shader.setFloat("roughness", roughness); // set UI value
//        shader.setFloat("metallic", metallic);
//        // render rows*column number of spheres with varying metallic/roughness values scaled by rows and columns respectively
//        glm::mat4 model = glm::mat4(1.0f);
//        glm::mat4 model_phong = glm::mat4(1.0f);
//        glm::mat4 model_nonPhoto = glm::mat4(1.0f);
//
//        for (int row = 0; row < nrRows; ++row)
//        {
//            shader.setFloat("metallic", 1.1 * (float)row / (float)nrRows);
//            for (int col = 0; col < nrColumns; ++col)
//            {
//                // we clamp the roughness to 0.05 - 1.0 as perfectly smooth surfaces (roughness of 0.0) tend to look a bit off
//                // on direct lighting.
//                shader.setFloat("roughness", glm::clamp((float)col / (float)nrColumns, 0.05f, 1.0f));
//                model = glm::mat4(1.0f);
//                model = glm::translate(model, glm::vec3(
//                    (col - (nrColumns / 2)) * spacing,
//                    (row - (nrRows / 2)) * spacing,
//                    0.0f
//                ));
//                model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
//                model = glm::rotate(model, timeValue * glm::radians(2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//                shader.setMat4("model", model);
//                shader.setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
//                renderSphere();
//            }
//        }
//
//        // render light source (simply re-render sphere at light positions)
//        // this looks a bit off as we use the same shader, but it'll make their positions obvious and 
//        // keeps the codeprint small.
//        for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
//        {
//            glm::vec3 newPos = lightPositions[i] + glm::vec3(5 * timeValue * glm::radians(90.0f), 0.0, 15.0f);
//            shader.setVec3("lightPositions[" + std::to_string(i) + "]", newPos);
//            shader.setVec3("lightColors[" + std::to_string(i) + "]", lightColors[i]);
//
//            model = glm::mat4(1.0f);
//            model = glm::translate(model, newPos);
//            model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
//            model = glm::rotate(model, timeValue * glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//
//            shader.setMat4("model", model);
//            shader.setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
//            //renderSphere();
//        }
//#pragma endregion
//// ========================================model_PBR (end) ===========================================================
//
//// ========================================model_Phong (start)==========================================================
//#pragma region
//
//        shaderPhong.use();
//        glm::mat4 projPhong = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        glm::mat4 viewPhong = camera.GetViewMatrix();
//        shaderPhong.setMat4("projection", projPhong);
//        shaderPhong.setMat4("view", viewPhong);
//        shaderPhong.setVec3("lightPos", 20.0f, 0.0f, 15.0f);
//        shaderPhong.setVec3("objectColor", 1.0f, 0.0f, 0.0f);
//        shaderPhong.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
//
//        for (int row = 0; row < nrRows; ++row)
//        {
//            for (int col = 0; col < nrColumns; ++col)
//            {
//                model_phong = glm::mat4(1.0f);
//                model_phong = glm::translate(model_phong, glm::vec3(
//                    40 + (col - (nrColumns / 2)) * spacing,
//                    (row - (nrRows / 2)) * spacing,
//                    0.0f
//                ));
//                model_phong = glm::rotate(model_phong, timeValue * glm::radians(25.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//                glm::vec3 lightPos = glm::vec3(
//                    40 + (col - (nrColumns / 2)) * spacing,
//                    (row - (nrRows / 2)) * spacing,
//                    15.0f
//                );
//                shaderPhong.setFloat("ambientStrength", 0.1 * row);
//                shaderPhong.setMat4("model", model_phong);
//                shaderPhong.setVec3("lightPos", lightPos); // Update light position
//                //shaderPhong.setMat4("model", model_phong);
//                renderSphere();
//            }
//        }
//#pragma endregion
//// ========================================model_Phong (end) ===========================================================
//
//// ========================================non_Physical (start)==========================================================
//#pragma region
//        shaderNonPhoto.use();
//
//
//        for (int row = 0; row < nrRows; ++row)
//        {
//            for (int col = 0; col < nrColumns; ++col)
//            {
//                glm::mat4 projNonPhoto = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//                glm::mat4 viewNonPhoto = camera.GetViewMatrix();
//                trans = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
//                trans = glm::rotate(trans, timeValue * glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//                shaderNonPhoto.setMat4("transform", trans);
//
//                shaderNonPhoto.setMat4("projMat", projNonPhoto);
//                shaderNonPhoto.setMat4("viewMat", viewNonPhoto);
//                shaderNonPhoto.setVec3("viewPos", camera.Position);
//                shaderNonPhoto.setFloat("diffuse_upper_bound", 1.0f + 0.05f * row);
//                shaderNonPhoto.setFloat("diffuse_lower_bound", 0.90f);
//                shaderNonPhoto.setFloat("specular_bound", 0.25f + 0.1f * col);
//
//                model_nonPhoto = glm::mat4(1.0f);
//                model_nonPhoto = glm::translate(
//                    model_nonPhoto, 
//                    glm::vec3(80 + (col - (nrColumns / 2)) * spacing,
//                    (row - (nrRows / 2)) * spacing,
//                    0.0f
//                ));
//                model_nonPhoto = glm::rotate(model_nonPhoto, timeValue * glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//
//                glm::vec3 lightPos = glm::vec3(
//                    10 + (col - (nrColumns / 2)) * spacing,
//                    (row - (nrRows / 2)) * spacing,
//                    15.0f
//                );
//                lightPos += glm::vec3(15 * timeValue * glm::radians(15.0f), 0.0, 15.0f);
//                shaderNonPhoto.setVec3("lightPosition", lightPos);
//                shaderNonPhoto.setMat4("modelMat", model_nonPhoto);
//                renderSphere();
//            }
//        }
//
//#pragma endregion
//// ========================================non_Physical (end) ===========================================================
//
//        //myGui.createGUI();  // create IMG UI
//
//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        // -------------------------------------------------------------------------------
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // glfw: terminate, clearing all previously allocated GLFW resources.
//    // ------------------------------------------------------------------
//    glfwTerminate();
//    return 0;
//}
//
//// ========================================input process (start)==========================================================
//#pragma region
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        camera.ProcessKeyboard(FORWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        camera.ProcessKeyboard(BACKWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        camera.ProcessKeyboard(LEFT, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        camera.ProcessKeyboard(RIGHT, deltaTime);
//    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
//        MouseButton2 = true;
//    else
//        MouseButton2 = false;
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    // make sure the viewport matches the new window dimensions; note that width and 
//    // height will be significantly larger than specified on retina displays.
//    glViewport(0, 0, width, height);
//}
//
//// glfw: whenever the mouse moves, this callback is called
//// -------------------------------------------------------
//void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
//{
//    float xpos = static_cast<float>(xposIn);
//    float ypos = static_cast<float>(yposIn);
//
//    if (firstMouse)
//    {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//
//    float xoffset = xpos - lastX;
//    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//    lastX = xpos;
//    lastY = ypos;
//
//    if (MouseButton2)
//        camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//// ----------------------------------------------------------------------
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//    camera.ProcessMouseScroll(static_cast<float>(yoffset));
//}
//
//// renders (and builds at first invocation) a sphere
//// -------------------------------------------------
//unsigned int sphereVAO = 0;
//unsigned int indexCount;
//void renderSphere()
//{
//    if (sphereVAO == 0)
//    {
//        glGenVertexArrays(1, &sphereVAO);
//
//        unsigned int vbo, ebo;
//        glGenBuffers(1, &vbo);
//        glGenBuffers(1, &ebo);
//
//        std::vector<glm::vec3> positions;
//        std::vector<glm::vec2> uv;
//        std::vector<glm::vec3> normals;
//        std::vector<unsigned int> indices;
//
//        const unsigned int X_SEGMENTS = 64;
//        const unsigned int Y_SEGMENTS = 64;
//        const float PI = 3.14159265359f;
//        for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
//        {
//            for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
//            {
//                float xSegment = (float)x / (float)X_SEGMENTS;
//                float ySegment = (float)y / (float)Y_SEGMENTS;
//                float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
//                float yPos = std::cos(ySegment * PI);
//                float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
//
//                positions.push_back(glm::vec3(xPos, yPos, zPos));
//                uv.push_back(glm::vec2(xSegment, ySegment));
//                normals.push_back(glm::vec3(xPos, yPos, zPos));
//            }
//        }
//
//        bool oddRow = false;
//        for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
//        {
//            if (!oddRow) // even rows: y == 0, y == 2; and so on
//            {
//                for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
//                {
//                    indices.push_back(y * (X_SEGMENTS + 1) + x);
//                    indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
//                }
//            }
//            else
//            {
//                for (int x = X_SEGMENTS; x >= 0; --x)
//                {
//                    indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
//                    indices.push_back(y * (X_SEGMENTS + 1) + x);
//                }
//            }
//            oddRow = !oddRow;
//        }
//        indexCount = static_cast<unsigned int>(indices.size());
//
//        std::vector<float> data;
//        for (unsigned int i = 0; i < positions.size(); ++i)
//        {
//            data.push_back(positions[i].x);
//            data.push_back(positions[i].y);
//            data.push_back(positions[i].z);
//            if (normals.size() > 0)
//            {
//                data.push_back(normals[i].x);
//                data.push_back(normals[i].y);
//                data.push_back(normals[i].z);
//            }
//            if (uv.size() > 0)
//            {
//                data.push_back(uv[i].x);
//                data.push_back(uv[i].y);
//            }
//        }
//        glBindVertexArray(sphereVAO);
//        glBindBuffer(GL_ARRAY_BUFFER, vbo);
//        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
//        unsigned int stride = (3 + 2 + 3) * sizeof(float);
//        glEnableVertexAttribArray(0);
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
//        glEnableVertexAttribArray(1);
//        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
//        glEnableVertexAttribArray(2);
//        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
//    }
//
//    glBindVertexArray(sphereVAO);
//    glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
//}
//
//// utility function for loading a 2D texture from file
//// ---------------------------------------------------
//unsigned int loadTexture(char const* path)
//{
//    unsigned int textureID;
//    glGenTextures(1, &textureID);
//
//    int width, height, nrComponents;
//    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
//    if (data)
//    {
//        GLenum format;
//        if (nrComponents == 1)
//            format = GL_RED;
//        else if (nrComponents == 3)
//            format = GL_RGB;
//        else if (nrComponents == 4)
//            format = GL_RGBA;
//
//        glBindTexture(GL_TEXTURE_2D, textureID);
//        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//        stbi_image_free(data);
//    }
//    else
//    {
//        std::cout << "Texture failed to load at path: " << path << std::endl;
//        stbi_image_free(data);
//    }
//
//    return textureID;
//}
//#pragma endregion
//// ========================================input process (end) ===========================================================
//
