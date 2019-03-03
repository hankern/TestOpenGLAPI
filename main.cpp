//#include <stdio.h>
//#include <string.h>

//#include <math.h>
//#include <GL/glew.h>
//#include <GL/freeglut.h>

//#include "ogldev_util.h"
//#include "ogldev_math_3d.h"

//GLuint VBO;
//// 索引缓冲对象的句柄
//GLuint IBO;
//GLuint gWorldLocation;

//const char* pVSFileName = "shader.vs";
//const char* pFSFileName = "shader.fs";


//static void RenderSceneCB()
//{
//    glClear(GL_COLOR_BUFFER_BIT);

//    static float Scale = 0.0f;

//    Scale += 0.01f;

//    Matrix4f World;

//    World.m[0][0] = cosf(Scale); World.m[0][1] = 0.0f; World.m[0][2] = -sinf(Scale); World.m[0][3] = 0.0f;
//    World.m[1][0] = 0.0;         World.m[1][1] = 1.0f; World.m[1][2] = 0.0f        ; World.m[1][3] = 0.0f;
//    World.m[2][0] = sinf(Scale); World.m[2][1] = 0.0f; World.m[2][2] = cosf(Scale) ; World.m[2][3] = 0.0f;
//    World.m[3][0] = 0.0f;        World.m[3][1] = 0.0f; World.m[3][2] = 0.0f        ; World.m[3][3] = 1.0f;

//    glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, &World.m[0][0]);

//    glEnableVertexAttribArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

//    // 每次在绘制之前绑定索引缓冲
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
//    // 索引绘制图形
//    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

//    glDisableVertexAttribArray(0);

//    glutSwapBuffers();
//}


//static void InitializeGlutCallbacks()
//{
//    glutDisplayFunc(RenderSceneCB);
//    glutIdleFunc(RenderSceneCB);
//}

//static void CreateVertexBuffer()
//{
//    // 金字塔的四个顶点
//    Vector3f Vertices[4];
//    Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
//    Vertices[1] = Vector3f(0.0f, -1.0f, 1.0f);
//    Vertices[2] = Vector3f(1.0f, -1.0f, 0.0f);
//    Vertices[3] = Vector3f(0.0f, 1.0f, 0.0f);

//    glGenBuffers(1, &VBO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
//}

//// 创建索引缓冲器
//static void CreateIndexBuffer()
//{
//    // 四个三角形面的顶点索引集
//    unsigned int Indices[] = { 0, 3, 1,
//                               1, 3, 2,
//                               2, 3, 0,
//                               0, 1, 2 };
//    // 创建缓冲区
//    glGenBuffers(1, &IBO);
//    // 绑定缓冲区
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
//    // 添加缓冲区数据
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
//}

//static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
//{
//    GLuint ShaderObj = glCreateShader(ShaderType);

//    if (ShaderObj == 0) {
//        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
//        exit(1);
//    }

//    const GLchar* p[1];
//    p[0] = pShaderText;
//    GLint Lengths[1];
//    Lengths[0]= strlen(pShaderText);
//    glShaderSource(ShaderObj, 1, p, Lengths);
//    glCompileShader(ShaderObj);
//    GLint success;
//    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
//    if (!success) {
//        GLchar InfoLog[1024];
//        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
//        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
//        exit(1);
//    }

//    glAttachShader(ShaderProgram, ShaderObj);
//}

//static void CompileShaders()
//{
//    GLuint ShaderProgram = glCreateProgram();

//    if (ShaderProgram == 0) {
//        fprintf(stderr, "Error creating shader program\n");
//        exit(1);
//    }

//    string vs, fs;

//    if (!ReadFile(pVSFileName, vs)) {
//        exit(1);
//    };

//    if (!ReadFile(pFSFileName, fs)) {
//        exit(1);
//    };

//    AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
//    AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

//    GLint Success = 0;
//    GLchar ErrorLog[1024] = { 0 };

//    glLinkProgram(ShaderProgram);
//    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
//    if (Success == 0) {
//        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
//        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
//        exit(1);
//    }

//    glValidateProgram(ShaderProgram);
//    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
//    if (!Success) {
//        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
//        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
//        exit(1);
//    }

//    glUseProgram(ShaderProgram);

//    gWorldLocation = glGetUniformLocation(ShaderProgram, "gWorld");
//    assert(gWorldLocation != 0xFFFFFFFF);
//}

//int main(int argc, char** argv)
//{
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
//    glutInitWindowSize(800, 600);
//    glutInitWindowPosition(100, 100);
//    glutCreateWindow("Tutorial 10");

//    InitializeGlutCallbacks();

//    // Must be done after glut is initialized!
//    GLenum res = glewInit();
//    if (res != GLEW_OK) {
//      fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
//      return 1;
//    }

//    printf("GL version: %s\n", glGetString(GL_VERSION));

//    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

//    CreateVertexBuffer();
//    CreateIndexBuffer();

//    CompileShaders();

//    glutMainLoop();

//    return 0;
//}









//#include <QCoreApplication>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "ogldev_util.h"
#include "pipeline.h"
#include "camera.h"
#include "texture.h"

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";
struct Vertex
{
    Vector3f m_pos;
    Vector2f m_tex;

    Vertex() {}

    Vertex(Vector3f pos, Vector2f tex)
    {
        m_pos = pos;
        m_tex = tex;
    }
};


GLuint VBO;
GLuint IBO;
GLuint gWVPLocation;
GLuint gSampler;
Texture* pTexture = NULL;
Camera* pGameCamera = NULL;


static void RenderSceneCB()
{
    pGameCamera->OnRender();

    glClear(GL_COLOR_BUFFER_BIT);

    static float Scale = 0.0f;

    Scale += 0.1f;

    Pipeline p;
    p.Rotate(0.0f, Scale, 0.0f);
    p.WorldPos(0.0f, 0.0f, 3.0f);
    p.SetCamera(pGameCamera->GetPos(), pGameCamera->GetTarget(), pGameCamera->GetUp());
    p.SetPerspectiveProj(60.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 100.0f);

    glUniformMatrix4fv(gWVPLocation, 1, GL_TRUE, (const GLfloat*)p.GetTrans());

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    //pTexture->Bind(GL_TEXTURE0);
    pTexture->Bind(GL_TEXTURE31);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glutSwapBuffers();
}


static void SpecialKeyboardCB(int Key, int x, int y)
{
    pGameCamera->OnKeyboard(Key);
}


static void KeyboardCB(unsigned char Key, int x, int y)
{
    switch (Key) {
        case 'q':
            glutLeaveMainLoop();
    }
}


static void PassiveMouseCB(int x, int y)
{
    pGameCamera->OnMouse(x, y);
}


static void InitializeGlutCallbacks()
{
    glutDisplayFunc(RenderSceneCB);
    glutIdleFunc(RenderSceneCB);
    glutSpecialFunc(SpecialKeyboardCB);
    glutPassiveMotionFunc(PassiveMouseCB);
    glutKeyboardFunc(KeyboardCB);
}


static void CreateVertexBuffer()
{
    Vertex Vertices[4] = { Vertex(Vector3f(-1.0f, -1.0f, 0.5773f), Vector2f(0.0f, 0.0f)),
                           Vertex(Vector3f(0.0f, -1.0f, -1.15475), Vector2f(0.5f, 0.0f)),
                           Vertex(Vector3f(1.0f, -1.0f, 0.5773f),  Vector2f(1.0f, 0.0f)),
                           Vertex(Vector3f(0.0f, 1.0f, 0.0f),      Vector2f(0.5f, 1.0f)) };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}


static void CreateIndexBuffer()
{
    unsigned int Indices[] = { 0, 3, 1,
                               1, 3, 2,
                               2, 3, 0,
                               1, 2, 0 };

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}


static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        exit(0);
    }

    const GLchar* p[1];
    p[0] = pShaderText;
    GLint Lengths[1];
    Lengths[0]= strlen(pShaderText);
    glShaderSource(ShaderObj, 1, p, Lengths);
    glCompileShader(ShaderObj);
    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        exit(1);
    }

    glAttachShader(ShaderProgram, ShaderObj);
}


static void CompileShaders()
{
    GLuint ShaderProgram = glCreateProgram();

    if (ShaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }

//    AddShader(ShaderProgram, pVS, GL_VERTEX_SHADER);
//    AddShader(ShaderProgram, pFS, GL_FRAGMENT_SHADER);
    string vs, fs;

    if (!ReadFile(pVSFileName, vs)) {
        exit(1);
    };

    if (!ReadFile(pFSFileName, fs)) {
        exit(1);
    };
    AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
    AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
    if (Success == 0) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    glValidateProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    glUseProgram(ShaderProgram);

    gWVPLocation = glGetUniformLocation(ShaderProgram, "gWVP");
    assert(gWVPLocation != 0xFFFFFFFF);
    gSampler = glGetUniformLocation(ShaderProgram, "gSampler");
    assert(gSampler != 0xFFFFFFFF);
}


int main(int argc, char** argv)
{
    //QCoreApplication a(argc, argv);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tutorial 16");
    //glutGameModeString("1280x1024@32");
    //glutEnterGameMode();

    InitializeGlutCallbacks();

    pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT);

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) {
      fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
      return 1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    CreateVertexBuffer();
    CreateIndexBuffer();

    CompileShaders();

    glUniform1i(gSampler, 0);

    pTexture = new Texture(GL_TEXTURE_2D, "test.png");

    if (!pTexture->Load()) {
        return 1;
    }

    glutMainLoop();

    return 0;
}
