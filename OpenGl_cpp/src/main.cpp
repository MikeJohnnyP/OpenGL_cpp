#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "function_callback.h"
#include <iostream>

const int SCR_WIDTH = 640;
const int SCR_HEIGHT = 480;

const char *vertexShaderSource = "#version 330 core\n"
								"layout (location = 0) in vec3 aPos;\n"
								"void main()\n"
								"{\n"
								"  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
								"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
									"out vec4 FragColor;\n"
									"void main()\n"
									"{\n"
									"  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
									"}\0";
int main()
{
    if (!glfwInit()) {
        std::cout << "glfw failed to initiallize" << std::endl;
        return -1;
    }
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "MyOpenGl", NULL, NULL);
    if (window == NULL) {
        std::cout << "Window can't initiallize" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // set Window hint for major and minor opengl version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);


    // set OpenGL core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLAD failed to init" << std::endl;
        return -1;
    }



    // set glViewPort
    glfwSetFramebufferSizeCallback(window,
				framebuffer_size_callback);

    // set color state to clear buffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // create vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check error if shader is not created
    int success;
    char inforLog[512];  // store a ERROR log
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, inforLog);
        std::cout << "ERROR::VERTEX_SHADER::COMPLITATION_FAILED\n" << inforLog << std::endl;
    }

    // create fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // check fragment shader if it not compile
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, inforLog);
        std::cout << "ERROR::FRAGMENT_SHADER::COMPLITATION_FAILED\n" << inforLog << std::endl;
    }

    // create shader program to link all previous compiled shader
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    

    // Check shader program linking status 
    glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shaderProgram, 512, NULL, inforLog);
        std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << inforLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

     //created a vertices of triangle
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    // initiallize a buffer that contains my vertices
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
						vertices, GL_STATIC_DRAW);

    // Gennerate a VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
	 
    // set vertex attirb 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
		// Use this program 
        glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
       // clear color buffer every frame
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}
