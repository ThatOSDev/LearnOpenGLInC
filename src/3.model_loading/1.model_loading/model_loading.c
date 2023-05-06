
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cglm/cglm.h>

#include <learnopengl/camera.h>
#include <learnopengl/model.h>

#include <stdio.h> // printf()
#include <assert.h>

void framebuffer_size_callback(GLFWwindow *, int, int);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void processInput(GLFWwindow *windows);

static int32_t screenWidth, screenHeight;
static float deltaTime = 0.0f;
static float lastFrame = 0.0f;
static double lastX = 0.0;
static double lastY = 0.0;
bool firstMouse = true;

int main(void)
{
	glfwInit();

    int count;
    int windowWidth, windowHeight;
    int monitorX, monitorY;

    GLFWmonitor** monitors = glfwGetMonitors(&count);
    const GLFWvidmode* videoMode = glfwGetVideoMode(monitors[0]);
    windowWidth = videoMode->width / 1.5;
    windowHeight = windowWidth / 16 * 9;

    glfwGetMonitorPos(monitors[0], &monitorX, &monitorY); // Setting up to Center Window

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_VISIBLE , GLFW_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
	if (window == NULL)
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return 1;
	}

	glfwSetWindowPos(window, monitorX + (videoMode->width - windowWidth) / 2,
                             monitorY + (videoMode->height - windowHeight) / 2);

	glfwShowWindow(window);  // Once window is centered, then show it.

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD\n");
		return 1;
	}

	screenWidth = 800;
	screenHeight = 600;

	lastX = screenWidth / 2;
	lastY = screenHeight / 2;

	glViewport(0, 0, screenWidth, screenHeight);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	unsigned int objectShader = LoadShaders("src/3.model_loading/1.model_loading/transform.vert", "src/3.model_loading/1.model_loading/object.frag");
	if (!objectShader) {
		return 1;
	}

	unsigned int lampShader = LoadShaders("src/3.model_loading/1.model_loading/transform.vert", "src/3.model_loading/1.model_loading/light.frag");
	if (!lampShader) {
		return 1;
	}

	printf("Loading the backpack model...\n");
	Model model = loadModel("resources/objects/backpack/backpack.obj");
	printf("Backback model loaded.\n");

	glEnable(GL_DEPTH_TEST);

	uint32_t VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	uint32_t lampVAO;
	glGenVertexArrays(1, &lampVAO);
	glBindVertexArray(lampVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	CreateCameraVector((vec3){0.0f, 0.0f, 3.0f});

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    vec3 pointLightPositions[] = {
        { 0.7f,  20.0f,  2.0f },
        { 2.3f, 15.0f, -4.0f },
        { -4.0f,  10.0f, -12.0f },
        { 0.0f,  0.0f, -3.0f }
    };

    vec3 pointLightColors[] = {
        { 0.0f, 1.0f, 1.0f, },
        { 1.0f, 1.0f, 1.0f, },
        { 1.0f, 1.0f, 1.0f, },
        { 1.0f, 0.0f, 0.0f, }
    };

	lastFrame = (float) glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		GLenum error = glGetError();
		if (error) {
			printf("error: %i\n", error);
		}

		float currentFrame = (float) glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        useShader(objectShader);
        mat4 view = GLM_MAT4_IDENTITY_INIT;
        Camera_GetViewMatrix(view);

        mat4 projection = GLM_MAT4_IDENTITY_INIT;
        glm_perspective(glm_rad(Camera->Zoom), screenWidth / (float)screenHeight, 0.1f, 100.0f, projection);

        setMat4(objectShader, "view", view);
        setMat4(objectShader, "projection", projection);
        setMat4(objectShader, "model", GLM_MAT4_IDENTITY);

        setFloat(objectShader, "material.shininess", 32);

        setVec3(objectShader, "dirLight.direction", (vec3){-0.2f, -1.0f, -0.3f});
        setVec3(objectShader, "dirLight.ambient", (vec3){0.05f, 0.05f, 0.05f});
        setVec3(objectShader, "dirLight.diffuse", (vec3){0.4f, 0.4f, 0.4f});
        setVec3(objectShader, "dirLight.specular", (vec3){0.5f, 0.5f, 0.5f});

        setVec3(objectShader, "viewPos", Camera->Position);
        setVec3(objectShader, "spotLight.position", Camera->Position);
        setVec3(objectShader, "spotLight.direction", Camera->Front);
        setFloat(objectShader, "spotLight.cutOff", (float) cos(glm_rad(12.5f)));
        setFloat(objectShader, "spotLight.outerCutOff", (float) cos(glm_rad(15.0f)));

        setVec3(objectShader, "spotLight.ambient", (vec3){0.0f, 0.0f, 0.0f});
        setVec3(objectShader, "spotLight.diffuse", (vec3){1.0f, 1.0f, 1.0f});
        setVec3(objectShader, "spotLight.specular", (vec3){1.0f, 1.0f, 1.0f});
        setFloat(objectShader, "spotLight.constant", 1.0f);
        setFloat(objectShader, "spotLight.linear", 0.09f);
        setFloat(objectShader, "spotLight.quadratic", 0.032f);

        setInt(objectShader, "usedPointLights", 4);

        char uniformNameBuf[100];
        for (int i = 0; i < 4; i++) {
            sprintf(uniformNameBuf, "pointLights[%i].position", i);
            setVec3(objectShader, uniformNameBuf, pointLightPositions[i]);
            sprintf(uniformNameBuf, "pointLights[%i].constant", i);
            setFloat(objectShader, uniformNameBuf, 1.0f);
            sprintf(uniformNameBuf, "pointLights[%i].linear", i);
            setFloat(objectShader, uniformNameBuf, 0.09f);
            sprintf(uniformNameBuf, "pointLights[%i].quadratic", i);
            setFloat(objectShader, uniformNameBuf, 0.032f);

            sprintf(uniformNameBuf, "pointLights[%i].ambient", i);
            vec3 ambient = {0, 0, 0};
            glm_vec3_muladds(pointLightColors[i], 0.2f, ambient);
            setVec3(objectShader, uniformNameBuf, ambient);

            sprintf(uniformNameBuf, "pointLights[%i].diffuse", i);
            vec3 diffuse = {0, 0, 0};
            glm_vec3_muladds(pointLightColors[i], 0.5f, diffuse);
            setVec3(objectShader, uniformNameBuf, diffuse);

            sprintf(uniformNameBuf, "pointLights[%i].specular", i);
            setVec3(objectShader, uniformNameBuf, pointLightColors[i]);
        }

        assert(glGetError() == GL_NO_ERROR);
        model_draw(&model, objectShader);
        assert(glGetError() == GL_NO_ERROR);

        useShader(lampShader);
        setMat4(lampShader, "view", view);
        setMat4(lampShader, "projection", projection);
        for (int i = 0; i < 4; i++) {
            mat4 lampModel = GLM_MAT4_IDENTITY_INIT;
            glm_translate(lampModel, pointLightPositions[i]);
            glm_scale(lampModel, (vec3){0.2f, 0.2f, 0.2f});
            setMat4(lampShader, "model", lampModel);
            setVec3(lampShader, "lightColor", pointLightColors[i]);
            glBindVertexArray(lampVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	ShaderCleanUp(objectShader);
    ShaderCleanUp(lampShader);
    Camera_CleanUp();
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	screenWidth = width;
	screenHeight = height;
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        Camera_ProcessKeyboard(FORWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        Camera_ProcessKeyboard(BACKWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        Camera_ProcessKeyboard(LEFT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        Camera_ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    float xpos = (float)(xposIn);
    float ypos = (float)(yposIn);

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

    Camera_ProcessMouseMovement(xoffset, yoffset, true);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	Camera_ProcessMouseScroll(yoffset);
}


