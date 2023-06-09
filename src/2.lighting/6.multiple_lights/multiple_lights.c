#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <cglm/cglm.h>

#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>

#include <stdio.h>
#include <stdbool.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
unsigned int loadTexture(const char *path);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// lighting
vec3 lightPos = {1.2f, 1.0f, 2.0f};

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
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    // unsigned int programID = LoadShaders("6.multiple_lights.vs", "6.multiple_lights.fs");
    unsigned int lightingShaderID = LoadShaders("src/2.lighting/6.multiple_lights/6.multiple_lights.vs", "src/2.lighting/6.multiple_lights/6.multiple_lights.fs");
    // unsigned int programID = LoadShaders("6.light_cube.vs", "6.light_cube.fs");
     unsigned int lightCubeShaderID = LoadShaders("src/2.lighting/6.multiple_lights/6.light_cube.vs", "src/2.lighting/6.multiple_lights/6.light_cube.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
    // positions all containers
    vec3 cubePositions[] = {
        { 0.0f,  0.0f,  0.0f},
        { 2.0f,  5.0f, -15.0f},
        {-1.5f, -2.2f, -2.5f},
        {-3.8f, -2.0f, -12.3f},
        { 2.4f, -0.4f, -3.5f},
        {-1.7f,  3.0f, -7.5f},
        { 1.3f, -2.0f, -2.5f},
        { 1.5f,  2.0f, -2.5f},
        { 1.5f,  0.2f, -1.5f},
        {-1.3f,  1.0f, -1.5f}
    };

    // positions of the point lights
    vec3 pointLightPositions[] = {
        {0.7f,  0.2f,  2.0f},
        {2.3f, -3.3f, -4.0f},
        {-4.0f,  2.0f, -12.0f},
        {0.0f,  0.0f, -3.0f}
    };
    // first, configure the cube's VAO (and VBO)
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // load textures (we now use a utility function to keep the code more organized)
    // -----------------------------------------------------------------------------
    unsigned int diffuseMap = loadTexture("resources/textures/container2.png");
    unsigned int specularMap = loadTexture("resources/textures/container2_specular.png");

    // shader configuration
    // --------------------
    useShader(lightingShaderID);
    setInt(lightingShaderID, "material.diffuse", 0);
    setInt(lightingShaderID, "material.specular", 1);

    // This is put here, since you only need to call it once.
    // Only reason to put it in the loop is if you constantly change the background color.
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // Create the camera and give it a position
    // Check the CreateCameraScalar in the camera.h file for fine tunning your camera options
    CreateCameraVector((vec3){0.0f, 0.0f, 3.0f});


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = (float)(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        useShader(lightingShaderID);
        setVec3(lightingShaderID, "viewPos", Camera->Position);
        setFloat(lightingShaderID, "material.shininess", 32.0f);

        /*
           Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
           the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
           by defining light types as classes and set their values in there, or by using a more efficient uniform approach
           by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
        */
        // directional light
        setVec3_XYZ(lightingShaderID, "dirLight.direction", -0.2f, -1.0f, -0.3f);
        setVec3_XYZ(lightingShaderID, "dirLight.ambient", 0.05f, 0.05f, 0.05f);
        setVec3_XYZ(lightingShaderID, "dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        setVec3_XYZ(lightingShaderID, "dirLight.specular", 0.5f, 0.5f, 0.5f);
        // point light 1
        setVec3(lightingShaderID, "pointLights[0].position", pointLightPositions[0]);
        setVec3_XYZ(lightingShaderID, "pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        setVec3_XYZ(lightingShaderID, "pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        setVec3_XYZ(lightingShaderID, "pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        setFloat(lightingShaderID, "pointLights[0].constant", 1.0f);
        setFloat(lightingShaderID, "pointLights[0].linear", 0.09f);
        setFloat(lightingShaderID, "pointLights[0].quadratic", 0.032f);
        // point light 2
        setVec3(lightingShaderID, "pointLights[1].position", pointLightPositions[1]);
        setVec3_XYZ(lightingShaderID, "pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        setVec3_XYZ(lightingShaderID, "pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        setVec3_XYZ(lightingShaderID, "pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        setFloat(lightingShaderID, "pointLights[1].constant", 1.0f);
        setFloat(lightingShaderID, "pointLights[1].linear", 0.09f);
        setFloat(lightingShaderID, "pointLights[1].quadratic", 0.032f);
        // point light 3
        setVec3(lightingShaderID, "pointLights[2].position", pointLightPositions[2]);
        setVec3_XYZ(lightingShaderID, "pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        setVec3_XYZ(lightingShaderID, "pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        setVec3_XYZ(lightingShaderID, "pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        setFloat(lightingShaderID, "pointLights[2].constant", 1.0f);
        setFloat(lightingShaderID, "pointLights[2].linear", 0.09f);
        setFloat(lightingShaderID, "pointLights[2].quadratic", 0.032f);
        // point light 4
        setVec3(lightingShaderID, "pointLights[3].position", pointLightPositions[3]);
        setVec3_XYZ(lightingShaderID, "pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        setVec3_XYZ(lightingShaderID, "pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        setVec3_XYZ(lightingShaderID, "pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        setFloat(lightingShaderID, "pointLights[3].constant", 1.0f);
        setFloat(lightingShaderID, "pointLights[3].linear", 0.09f);
        setFloat(lightingShaderID, "pointLights[3].quadratic", 0.032f);
        // spotLight
        setVec3(lightingShaderID, "spotLight.position", Camera->Position);
        setVec3(lightingShaderID, "spotLight.direction", Camera->Front);
        setVec3_XYZ(lightingShaderID, "spotLight.ambient", 0.0f, 0.0f, 0.0f);
        setVec3_XYZ(lightingShaderID, "spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        setVec3_XYZ(lightingShaderID, "spotLight.specular", 1.0f, 1.0f, 1.0f);
        setFloat(lightingShaderID, "spotLight.constant", 1.0f);
        setFloat(lightingShaderID, "spotLight.linear", 0.09f);
        setFloat(lightingShaderID, "spotLight.quadratic", 0.032f);
        setFloat(lightingShaderID, "spotLight.cutOff", cos(glm_rad(12.5f)));
        setFloat(lightingShaderID, "spotLight.outerCutOff", cos(glm_rad(15.0f)));

        // view/projection transformations
        mat4 projection = GLM_MAT4_IDENTITY_INIT;
        glm_perspective(glm_rad(Camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f, projection);
        mat4 view = GLM_MAT4_IDENTITY_INIT;
        Camera_GetViewMatrix(view);
        setMat4(lightingShaderID, "projection", projection);
        setMat4(lightingShaderID, "view", view);

        // world transformation
        mat4 model = GLM_MAT4_IDENTITY_INIT;
        setMat4(lightingShaderID, "model", model);

        // bind diffuse map
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);
        // bind specular map
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);

        // render containers
        glBindVertexArray(cubeVAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm_mat4_identity(model);
            glm_translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            glm_rotate(model, glm_rad(angle), (vec3){1.0f, 0.3f, 0.5f});
            setMat4(lightingShaderID, "model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

         // also draw the lamp object(s)
         useShader(lightCubeShaderID);
         setMat4(lightCubeShaderID, "projection", projection);
         setMat4(lightCubeShaderID, "view", view);

         // we now draw as many light bulbs as we have point lights.
         glBindVertexArray(lightCubeVAO);
         for (unsigned int i = 0; i < 4; i++)
         {
             glm_mat4_identity(model);
             glm_translate(model, pointLightPositions[i]);
             glm_scale(model, (vec3){0.2f, 0.2f, 0.2f}); // Make it a smaller cube
             setMat4(lightCubeShaderID, "model", model);
             glDrawArrays(GL_TRIANGLES, 0, 36);
         }


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);
    ShaderCleanUp(lightingShaderID);
    ShaderCleanUp(lightCubeShaderID);
    Camera_CleanUp();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        Camera_ProcessKeyboard(FORWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        Camera_ProcessKeyboard(BACKWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        Camera_ProcessKeyboard(LEFT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        Camera_ProcessKeyboard(RIGHT, deltaTime);
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
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
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

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Camera_ProcessMouseScroll((float)(yoffset));
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        printf("Texture failed to load at path: %s\n", path);
        stbi_image_free(data);
    }

    return textureID;
}
