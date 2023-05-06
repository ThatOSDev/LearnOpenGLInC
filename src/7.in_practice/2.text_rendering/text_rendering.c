#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <learnopengl/shader.h>

#include <stdio.h>

typedef struct GLYPH_TYP
{
    unsigned int texture;
    vec2         size;
    float        width;
    float        height;
    float        bearing_left;
    float        bearing_top;
    unsigned int advance;
    char         value;
} GLYPH_T;

typedef struct GLYPHS_TYP
{
    size_t  size;
    GLYPH_T** items;
} ALLGLYPHS_T;

unsigned int SCR_WIDTH  = 800;
unsigned int SCR_HEIGHT = 600;
mat4 projection = GLM_MAT4_IDENTITY_INIT;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void RenderText(unsigned int program, int textSize, ALLGLYPHS_T characters, float x, float y, float scale, vec3 color);

GLYPH_T* get_character(char c, const char* fontpath, int size)
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        perror("ERROR::FREETYPE: Could not init FreeType Library");

    FT_Face face;
    if (FT_New_Face(ft, fontpath, 0, &face))
        perror("ERROR::FREETYPE: Failed to load font");

    FT_Set_Pixel_Sizes(face, 0, size);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        perror("ERROR::FREETYTPE: Failed to load Glyph");

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    GLYPH_T* character = calloc(1, sizeof(struct GLYPH_TYP));
    character->texture = texture;
    character->width = face->glyph->bitmap.width;
    character->height = face->glyph->bitmap.rows;
    character->bearing_left = face->glyph->bitmap_left;
    character->bearing_top = face->glyph->bitmap_top;
    character->advance = face->glyph->advance.x;
    character->value = c;
    glBindTexture(GL_TEXTURE_2D, 0);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    return character;
}

static ALLGLYPHS_T Characters(const char* text, const char* fontpath, int size)
{
    ALLGLYPHS_T list;
    list.size = 0;
    list.items = (void*)0;
    for (int i = 0; i < strlen(text); i++)
    {
        GLYPH_T* character = get_character(text[i], fontpath, size);
        list.size += 1;
        if (list.items == (void*)0)
        {
            list.items = calloc(list.size, sizeof(struct CHARACTER_STRUCT*));
        } else {
            list.items = realloc(list.items, sizeof(struct CHARACTER_STRUCT*) * list.size);
        }

        list.items[list.size - 1] = character;
    }
    return list;
}

unsigned int draw_mesh(unsigned int program, unsigned int texture, float x, float y, float w, float h, unsigned int VBO, vec3 color)
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glUseProgram(program);

    setVec3_XYZ(program, "textColor", color[0], color[1], color[2]);
    unsigned int vertex = glGetAttribLocation(program, "vertex");
    unsigned int model = glGetUniformLocation(program, "model");

    float vertices[6][4] = {
        { 0,     0 + h,   0.0, 0.0 },
        { 0,     0,       0.0, 1.0 },
        { 0 + w, 0,       1.0, 1.0 },

        { 0,     0 + h,   0.0, 0.0 },
        { 0 + w, 0,       1.0, 1.0 },
        { 0 + w, 0 + h,   1.0, 0.0 }
    };

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    mat4 matrixModel = GLM_MAT4_IDENTITY_INIT;

    glm_translate(matrixModel, (vec3){ x, y, 0 });

    glUniformMatrix4fv(model, 1, GL_FALSE, matrixModel[0]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, vertices, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(vertex);
    glVertexAttribPointer(vertex, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    return program;
}

int main(int argc, char* argv[])
{
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

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    // OpenGL state
    // ------------
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // compile and setup the shader
    // ----------------------------
    //unsigned int programID = LoadShaders("text.vs", "text.fs");
    unsigned int programID = LoadShaders("src/7.in_practice/2.text_rendering/text.vs", "src/7.in_practice/2.text_rendering/text.fs");

    glm_ortho(0.0f, (float)SCR_WIDTH, 0, (float)SCR_HEIGHT, -10.0f, 100.0f, projection);
    useShader(programID);
    glUniformMatrix4fv(glGetUniformLocation(programID, "projection"), 1, GL_FALSE, projection[0]);

    int textSize1 = 14;
    int textSize2 = 20;
	// find path to font
    const char* font_name = "resources/fonts/Antonio-Bold.ttf";

    ALLGLYPHS_T text1 = Characters("This is a sample text", font_name, textSize1);
    ALLGLYPHS_T text2 = Characters("(C) LearnOpenGL.com", font_name, textSize2);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        RenderText(programID, textSize1, text1, 25, 25, 1.0f, (vec3){1.0f, 1.0f, 1.0f});
        RenderText(programID, textSize2, text2, 540, 570, 1.0f, (vec3){0.0f, 1.0f, 0.0f});

        glUniformMatrix4fv(glGetUniformLocation(programID, "projection"), 1, GL_FALSE, projection[0]);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ShaderCleanUp(programID);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    SCR_WIDTH  = width;
    SCR_HEIGHT = height;
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glm_ortho(0, SCR_WIDTH, 0, SCR_HEIGHT, -10.0f, 100.0f, projection);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void RenderText(unsigned int program, int textSize, ALLGLYPHS_T characters, float x, float y, float scale, vec3 color)
{
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    float tempX = x;
    float tempY = y;
    y = (SCR_HEIGHT - textSize) - tempY;
    GLYPH_T* character2;

    for (int i = 0; i < characters.size; i++)
    {
        GLYPH_T* character = characters.items[i];
        if(i - 1 >= 0) {character2 = characters.items[i - 1];}

        if(character->value == '\n')
        {
            y -= textSize;
            x = tempX;
            continue;
        } else if(i - 1 >= 0 && character2->value == ' ' && x > (SCR_WIDTH - (textSize * 8)))
        {
            y -= textSize;
            x = tempX;
        }

        unsigned int texture = character->texture;

        GLfloat xpos = x + character->bearing_left * scale;
        GLfloat ypos = y - (character->height - character->bearing_top) * scale;

        GLfloat w = character->width * scale;
        GLfloat h = character->height * scale;

        draw_mesh(program, texture, xpos, ypos, w, h, VBO, color);

        x += (character->advance >> 6) * scale;
    }

    glDeleteBuffers(1, &VBO);
}

