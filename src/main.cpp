#include <iostream>
#include <stdexcept>
#include <random>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <shader.h>
#include <camera.h>

using namespace std;

const int WIDTH=800, HEIGHT=600;

float vert[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

void size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

Camera c(glm::vec3(0.0f, 0.0f, 3.0f));

void processKeyboardInput(GLFWwindow *window) {
    float speed = 0.1f;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        c.translation(c.getCameraFront() * speed);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        c.translation(c.getCameraFront() * -speed);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        c.translation(c.getCameraRight() * -speed);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        c.translation(c.getCameraRight() * speed);
}

float lastx = 400.0f, lasty = 300.0f;
bool firstMouse = true;
float yaw = -90.0f, pitch = 0.0f;
void processMouseInput(GLFWwindow *window, double xpos, double ypos) {
    if(firstMouse) {
        lastx = xpos;
        lasty = ypos;
        firstMouse = false;
    }

    float xoffset = xpos-lastx, yoffset=ypos-lasty;
    lastx = xpos, lasty = ypos;
    xoffset *= 0.1f;
    yoffset *= -0.1f;

    cout << yaw << " " << pitch << endl;

    yaw += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch =  89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    c.rotateByEulerAngle(glm::vec3(yaw, 0.0f, pitch));
}

int main()
{
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "Hello, world", nullptr, nullptr);

    if(window == nullptr) {
		cerr << "创建窗口失败。" << endl;
	    glfwTerminate();
        return -1;
	}

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, processMouseInput);
    glfwSetFramebufferSizeCallback(window, size_callback);
    glfwShowWindow(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cerr << "Failed to initalize GLAD."  << endl;
        return -1;
    }

    Shader vShader(GL_VERTEX_SHADER), fShader(GL_FRAGMENT_SHADER);
    ShaderProgram program;
    try {

        vShader.LoadAndCompile("rsrc/vert.glsl");
        fShader.LoadAndCompile("rsrc/frag.glsl");

        program.AttachShader(vShader);
        program.AttachShader(fShader);
        program.Link();
    } catch (std::runtime_error &e) {
        cerr << e.what() << endl;
        glfwTerminate();
        return -1;
    }

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int w, h, n;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("rsrc/a.png", &w, &h, &n, 0);

    if(!data) {
        cerr << "Error: Image: Failed to read texture image." << endl;
        return -1;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    glEnable(GL_DEPTH_TEST);

    program.Use();
    program.setUniform("texture1", 0);

    default_random_engine e;
    uniform_real_distribution<float> u(-5, 5);
    e.seed(time(nullptr));
    auto *cubePos = new glm::vec3[10];
    cubePos[0] = glm::vec3(0, 0, 0);
    for(int i = 1;i < 10;i++) cubePos[i] = glm::vec3(u(e), u(e), u(e));

    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        processKeyboardInput(window);

        glm::mat4 model = glm::mat4(1.0f), view = glm::mat4(1.0f), projection = glm::mat4(1.0f);
        view  = c.getViewMatrix();
        projection = glm::perspective(glm::radians(45.0f), (float)WIDTH/HEIGHT, 0.1f, 100.0f);

        program.Use();
        program.setUniform("model", model);
        program.setUniform("view", view);
        program.setUniform("projection", projection);
    
        glBindVertexArray(VAO);
        for(int i = 0; i < 10;i++) {
            model = glm::mat4(1.0);
            model = glm::translate(model, cubePos[i]);
            model = glm::rotate(model, glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f));
            program.setUniform("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        //cout << glm::to_string(c.getCameraPos())  << " " << glm::to_string(c.getCameraFront()) << endl;


        glfwSwapBuffers(window);
		glfwPollEvents();
	}

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
