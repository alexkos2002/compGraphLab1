//#include <GL/glew.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader_s.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    Shader ourShader("vertexShader.glsl", "fragmentShader.glsl");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
         0.0f,  0.0f, 0.0f,  
        -0.125f, -0.125f, 0.0f,  
         0.125f, -0.125f, 0.0f,  
         0.0f,  -0.25f, 0.0f,
         0.25f, 0.0f, 0.0f,
         0.25f, -0.25f, 0.0f,
        -0.125f, -0.375f, 0.0f, 
         0.375f, -0.375f, 0.0f,
         0.5f, -0.25f, 0.0f, 
         0.625f, -0.375f, 0.0f,
        -0.185f, 0.125f, 0.0f,
        -0.31f, 0.0f, 0.0f, 
        -0.185f, 0.0f, 0.0f,
        -0.185f, -0.125f, 0.0f,
        -0.185f, 0.350f, 0.0f,
         0.165f, 0.0f, 0.0f,
        -0.185f, 0.525f, 0.0f,
        -0.36f, 0.35f, 0.0f,
        -0.085f, -0.165f, 0.0f,
        -0.04f, -0.21f, 0.0f,
        -0.0685f, -0.0765f,
        -0.64f, -0.81f
    };
    unsigned int indices[] = {  // note that we start from 0!
        17, 16, 14,   // head triangle
        14, 12, 15,   // neck triangle
        10, 11, 13,   // paws triangle
        0, 1, 2,      // upper bag triangle
        1, 2, 3,      // lower bar triangle
        0, 4, 5,      // back triangle 
        2, 6, 7,      // lower paws triangle
        5, 7, 8,      // upper tail triangle
        7, 8, 9,      // lower tail triangle
        //18, 19, 20,   // upper bebra triangle
        //18, 19, 21    // lower bebra triangle
    };

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    // render loop
    // -----------

    float curX = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // render
        // ------
        glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();

        float timeValue = glfwGetTime();

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            curX = curX - 0.001;
        }
        else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            curX = curX + 0.001;
        }

        std::cout << std::to_string(curX);

        // curX = sin(timeValue) / 2.0f + 0.5f; // for periodical movement in opposite directions
        // update position of all vertices in direction of vector moveVec
        glm::vec3 moveVec(curX, 0.0f, 0.0f);
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, moveVec);

        ourShader.setMatrix4fv("transform", trans);

        timeValue = timeValue * 20;

        // update the uniform color
        float redValue = (sin(timeValue) / 2.0f + 0.5f) < 0.5f ? 0.0f : 1.0f;
        float greenValue = (sin(timeValue) / 2.0f + 0.5f) < 0.5f ? 0.0f : 0.9f;
        float blueValue = (sin(timeValue) / 2.0f + 0.5f) < 0.5f ? 1.0f : 0.0f;

        //int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        //glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);*/

        ourShader.setFloat("outRed", redValue);
        ourShader.setFloat("outGreen", greenValue);
        ourShader.setFloat("outBlue", blueValue);

        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

        glDrawElements(GL_TRIANGLES, 9 * 3, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    ourShader.deleteProgram();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}