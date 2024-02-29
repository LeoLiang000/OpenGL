//#include <iostream>
//#include<glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//
//using namespace std;
//
//
//// ========================================ShaderSource (start)==========================================================
//#pragma region
//    // vertex shader (VS)
//    const char* vertexShaderSource = "#version 330 core\n"
//    "layout (location = 0) in vec3 aPos;\n"
//    "void main()\n"
//    "{\n"
//    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//    "}\0";
//
//    // fragment shader (FS)
//    const char* fragmentShaderSource =
//    "#version 330 core\n"
//    "out vec4 FragColor;\n"
//    "void main(){\n"
//    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);}\n";
//
//#pragma endregion
//// ========================================ShaderSource (end) ===========================================================
//
//    
//
//
//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//}
//
//int main()
//{
// // initialize window (start)
//#pragma region
//    // claim version
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    
//    // create a window
//    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
//    glfwMakeContextCurrent(window);
//
//    // initialize glad that control opengl function pointers
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
// 
//#pragma endregion
//// initialize window (end)
//
//// vertex data (start)
//#pragma region
//    float vertices[] = {
//        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 0 右上
//             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 1 右下
//            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 2 左下
//            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 3 左上
//    };
//    
//    unsigned int indices[] = {
//     0, 1, 3, // first triangle
//     1, 2, 3  // second triangle
//    };
//
//    // create VBO
//    unsigned int VBO, VAO, EBO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
//
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//    // 创建指针position attribute
//    //                 属性ID，属性size，type，normalized，顶点size，属性偏移
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//    // color attribute
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//    // texture coord attribute
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//    glEnableVertexAttribArray(2);
//
//#pragma endregion
//// vertex data (end)
//
//// shader (start)
//#pragma region
//    //VS
//    unsigned int vertexShader;
//    vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//    glCompileShader(vertexShader);
//
//    //FS
//    unsigned int fragmentShader;
//    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//    glCompileShader(fragmentShader);
//
//    // link VS -> FS
//    unsigned int shaderProgram;
//    shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//
//    // 链接完后，delete shader
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//
//#pragma endregion
//// shader (end)
//
//// ========================================texeture (start)==========================================================
//#pragma region
//    unsigned int texture;
//    glGenTextures(1, &texture);
//    glBindTexture(GL_TEXTURE_2D, texture);
//
//    // 为当前绑定的纹理对象设置环绕、过滤方式
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    
//    // load texture image 
//    int width, height, nrChannels;
//    unsigned char* data = stbi_load("assets/container.jpg", &width, &height, &nrChannels, 0);
//    if (data)
//    {
//        cout << "load texture success" << endl;
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }
//    else
//    {
//        std::cout << "Failed to load texture" << std::endl;
//    }
//    stbi_image_free(data);
//
//#pragma endregion
//// texeture (end)
//
//// render loop (start)
//#pragma region
//    // render loop
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // 绘制线框模式图形，只有线条没有填充颜色
//    while (!glfwWindowShouldClose(window))
//    {
//        // keyboard input
//        processInput(window);
//
//        // render command
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        // 绘制三角形draw triangle
//        glUseProgram(shaderProgram);
//        glBindVertexArray(VAO);
//        //glDrawArrays(GL_TRIANGLES, 0, 3);
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//#pragma endregion
//// render loop (end)
//
//    glfwTerminate();
//    return 0;
//}
//
//
//
