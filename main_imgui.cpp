//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include "shader_m.h"
//#include "camera.h"
//#include "model.h"
//
//#include "imgui.h"
//#include "imgui_impl_glfw.h"
//#include "imgui_impl_opengl3.h"
//
//#include <iostream>
//
//
//// ========================================init (start)==========================================================
//#pragma region
//    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//    void processInput(GLFWwindow* window);
//
//    // settings
//    const unsigned int SCR_WIDTH = 800;
//    const unsigned int SCR_HEIGHT = 600;
//
//    // camera
//    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//    float lastX = SCR_WIDTH / 2.0f;
//    float lastY = SCR_HEIGHT / 2.0f;
//    bool firstMouse = true;
//
//    // timing
//    float deltaTime = 0.0f;
//    float lastFrame = 0.0f;
//#pragma endregion
//// ========================================init (end) ===========================================================
//
//// lighting 
//    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
//
//
//int main()
//{
//
//// ========================================init window (start)==========================================================
//#pragma region
//        // glfw: initialize and configure
//    // ------------------------------
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//    // glfw window creation
//    // --------------------
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
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
//    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
//    stbi_set_flip_vertically_on_load(false);
//
//
//
//    // Here we can check the version of OpenGL that is being used
//    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
//    const GLubyte* version = glGetString(GL_VERSION); // version as a string
//    std::cout << "Renderer: " << renderer << std::endl;
//    std::cout << "OpenGL version supported: " << version << std::endl;
//
//
//
//
//    // configure global opengl state
//    // -----------------------------
//    glEnable(GL_DEPTH_TEST);
//#pragma endregion
//// ========================================init window (end) ===========================================================
//
//    // build and compile shaders
//    // -------------------------
//    Shader ourShader("assets/models/blackman/shaders/shader.vs", "assets/models/blackman/shaders/shader.fs");
//    //Shader lightShader("assets/shaders/light_caster.vs", "assets/shaders/light_caster.vs");
//    Shader lightShader("assets/shaders/multi_lights.vs", "assets/shaders/multi_lights.fs");
//
//    // load models
//    // -----------
//    //Model ourModel("assets/models/backpack/backpack.obj");
//    //Model ourModel("assets/models/blackman/textures/nanosuit.obj");
//    Model ourModel("assets/models/ufo/Low_poly_UFO.obj");
//    //Model ourModel("assets/models/tcd campus/scene06/tcd.obj");
//
//
//
//// ========================================light (start)==========================================================
//#pragma region
//    glm::vec3 pointLightPositions[] = {
//        glm::vec3(0.7f,  -5.2f,  2.0f),
//        glm::vec3(2.3f, -3.3f, -4.0f),
//        glm::vec3(-4.0f,  -2.0f, -2.0f),
//        glm::vec3(0.0f,  -5.0f, -3.0f)
//    };
//
//    lightShader.use();
//    lightShader.setInt("material.diffuse", 0);
//    lightShader.setInt("material.specular", 1);
//
//
//// ========================================imgui (start)==========================================================
//#pragma region
//
//    ImGui::CreateContext();
//    ImGuiIO& io = ImGui::GetIO(); (void)io;
//
//    ImGui::StyleColorsDark();   // Setup Dear ImGui style: ImGui::StyleColorsLight(); StyleColorsDark
//
//    // Setup Platform/Renderer backends
//    ImGui_ImplGlfw_InitForOpenGL(window, true);
//    ImGui_ImplOpenGL3_Init("#version 330");
//    bool DrawLight = true;
//    float light_pos;
//    glm::vec3 light_color = glm::vec3(1, 1, 1);
//    int counter(0);
//
//#pragma endregion
//// ========================================imgui (end) ===========================================================
//
//
//
//#pragma endregion
//// ========================================light (end) ===========================================================
//
//
//    
//    // draw in wireframe
//    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//    // render loop
//    // -----------
//    while (!glfwWindowShouldClose(window))
//    {
//
//// ========================================init loop (start)==========================================================
//#pragma region
//                // per-frame time logic
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
//        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//#pragma endregion
//// ========================================init loop (end) ===========================================================
//
//// ========================================light (start)==========================================================
//#pragma region
//        lightShader.use();
//        //lightShader.setVec3("light.direction", -1.0f, -1.0f, -1.0f);
//        lightShader.setVec3("viewPos", camera.Position);
//        lightShader.setFloat("material.shininess", 32.0f);
//
//        // light properties
//        // directional light
//        lightShader.setVec3("dirLight.direction", -0.5f, -4.0f, -0.5f);
//        lightShader.setVec3("dirLight.ambient", 0.5f, 0.5f, 0.5f);
//        lightShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
//        lightShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
//        // point light 1
//        lightShader.setVec3("pointLights[0].position", pointLightPositions[0]);
//        lightShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
//        lightShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
//        lightShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
//        lightShader.setFloat("pointLights[0].constant", 1.0f);
//        lightShader.setFloat("pointLights[0].linear", 0.09f);
//        lightShader.setFloat("pointLights[0].quadratic", 0.032f);
//        // point light 2
//        lightShader.setVec3("pointLights[1].position", pointLightPositions[1]);
//        lightShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
//        lightShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
//        lightShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
//        lightShader.setFloat("pointLights[1].constant", 1.0f);
//        lightShader.setFloat("pointLights[1].linear", 0.09f);
//        lightShader.setFloat("pointLights[1].quadratic", 0.032f);
//        // point light 3
//        lightShader.setVec3("pointLights[2].position", pointLightPositions[2]);
//        lightShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
//        lightShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
//        lightShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
//        lightShader.setFloat("pointLights[2].constant", 1.0f);
//        lightShader.setFloat("pointLights[2].linear", 0.09f);
//        lightShader.setFloat("pointLights[2].quadratic", 0.032f);
//        // point light 4
//        lightShader.setVec3("pointLights[3].position", pointLightPositions[3]);
//        lightShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
//        lightShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
//        lightShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
//        lightShader.setFloat("pointLights[3].constant", 1.0f);
//        lightShader.setFloat("pointLights[3].linear", 0.09f);
//        lightShader.setFloat("pointLights[3].quadratic", 0.032f);
//        // spotLight
//        lightShader.setVec3("spotLight.position", camera.Position);
//        lightShader.setVec3("spotLight.direction", camera.Front);
//        lightShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
//        lightShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
//        lightShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
//        lightShader.setFloat("spotLight.constant", 1.0f);
//        lightShader.setFloat("spotLight.linear", 0.09f);
//        lightShader.setFloat("spotLight.quadratic", 0.032f);
//        lightShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
//        lightShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
//
//
//        // view/projection transformations
//        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        glm::mat4 view = camera.GetViewMatrix();
//        glm::mat4 model = glm::mat4(1.0f);
//        // world transformation
//        lightShader.setMat4("projection", projection);
//        lightShader.setMat4("view", view);
//        lightShader.setMat4("model", model);
//
//
//        //// view/projection transformations
//        //glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        //glm::mat4 view = camera.GetViewMatrix();
//        //lightShader.setMat4("projection", projection);
//        //lightShader.setMat4("view", view);
//
//        // render the loaded model
//        glm::mat4 model2 = glm::mat4(1.0f);
//        model2 = glm::translate(model, glm::vec3(0.0f, -5.0f, 0.0f)); // translate it down so it's at the center of the scene
//        model2 = glm::scale(model2, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
//        //model = glm::rotate(model, timeValue * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // rotate the first model over time around the y-axis
//        lightShader.setMat4("model", model2);
//        ourModel.Draw(lightShader);
//
//#pragma endregion
//// ========================================light (end) ===========================================================
//
//
//
//        // don't forget to enable shader before setting uniforms
//        //ourShader.use();
//        //// view/projection transformations
//        //glm::mat4 projection2 = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
//        //glm::mat4 view2 = camera.GetViewMatrix();
//        //ourShader.setMat4("projection", projection2);
//        //ourShader.setMat4("view", view2);
//        //// render the loaded model
//        //glm::mat4 model3 = glm::mat4(1.0f);
//        //model3 = glm::translate(model3, glm::vec3(0.0f, -5.0f, 0.0f)); // translate it down so it's at the center of the scene
//        //model3 = glm::scale(model3, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
//        ////model = glm::rotate(model, timeValue * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // rotate the first model over time around the y-axis
//        //ourShader.setMat4("model", model3);
//        //ourModel.Draw(ourShader);
//        //float timeValue = glfwGetTime();
//
//        // ========================================light (start)==========================================================
//#pragma region
//
//        //lightShader.use();
//        ////lightShader.setVec3("objectColor", 1.0f, 1.0f, 1.0f);
//        //lightShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
//        //lightShader.setVec3("lightPos", lightPos);
//
//        //model = glm::translate(model, glm::vec3(0, -2, 0));
//        //model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
//
//        //lightShader.setMat4("model", model);
//        //lightShader.setMat4("view", view);
//        //lightShader.setMat4("projection", projection);
//
//        //glDrawArrays(GL_TRIANGLES, 0, 36);
//        //ourModel.Draw(ourShader);
//
//        // view/projection transformations
//        
//        //glm::mat4 projection2 = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        //glm::mat4 projection2 = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        //glm::mat4 view2 = camera.GetViewMatrix();
//        //lightShader.setMat4("projection", projection2);
//        //lightShader.setMat4("view", view2);
//
//        // world transformation
//       /* glm::mat4 model2 = glm::mat4(1.0f);
//        lightShader.setMat4("model", model2);*/
//
//
//
//#pragma endregion
//        // ========================================light (end) ===========================================================
//
//
//// ========================================imgui (start)==========================================================
//#pragma region
//        // Start the Dear ImGui frame
//        ImGui_ImplOpenGL3_NewFrame();
//        ImGui_ImplGlfw_NewFrame();
//        ImGui::NewFrame();
//
//        ImGui::Begin("Hello, Leo!");
//        ImGui::Text("This is some useful text.");
//        ImGui::Checkbox("Draw Light", &DrawLight);
//        ImGui::SliderFloat("Light Position", &light_pos, 0.0f, 1.0f);
//        ImGui::ColorEdit3("Light Color", (float*)&light_color);
//        if (ImGui::Button("Button"))
//            counter++;
//        ImGui::SameLine(); // display at same line
//        ImGui::Text("counter = %d", counter);
//
//        ImGui::End();
//
//        ImGui::Render();
//        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//#pragma endregion
//// ========================================imgui (end) ===========================================================
//
//
//        //glm::mat4 model2 = glm::mat4(1.0f);
//        //model2 = glm::translate(model2, glm::vec3(10.0f, -5.0f, 0.0f)); // translate it down so it's at the center of the scene
//        //model2 = glm::scale(model2, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
//        //model2 = glm::rotate(model2, timeValue * glm::radians(-50.0f), glm::vec3(1.0f, 1.0f, 0.0f)); // rotate the first model over time around the y-axis
//        //ourShader.setMat4("model", model2);
//        //ourModel.Draw(ourShader);
//
//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        // -------------------------------------------------------------------------------
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // Cleanup imgui
//    ImGui_ImplOpenGL3_Shutdown();
//    ImGui_ImplGlfw_Shutdown();
//    ImGui::DestroyContext();
//
//    // glfw: terminate, clearing all previously allocated GLFW resources.
//    // ------------------------------------------------------------------
//    glfwTerminate();
//    return 0;
//}
//
//
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        camera.ProcessKeyboard(FORWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        camera.ProcessKeyboard(BACKWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        camera.ProcessKeyboard(LEFT, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        camera.ProcessKeyboard(RIGHT, deltaTime);
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
//    camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//// ----------------------------------------------------------------------
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//    camera.ProcessMouseScroll(static_cast<float>(yoffset));
//}