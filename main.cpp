#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <QBitmap>
#include <QImage>
#include <QRgb>
#include <QColor>

#include "pipeline.h"
#include "camera.h"
#include "texture.h"
#include "lighting_technique.h"
#include "glut_backend.h"
#include "util.h"
#include "mesh.h"
#include "shadow_map_fbo.h"
#include "shadow_map_technique.h"

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
void saveImg(){
    //保存图片



    QImage* img=new QImage(WINDOW_WIDTH,WINDOW_HEIGHT,QImage::Format_ARGB32);
    uchar* tmpBIT = img->bits();


//    //从颜色缓冲区中读取数据
//    int tmpPixelSize = WINDOW_WIDTH*WINDOW_HEIGHT * 4;
//    char* tmpPixelsBuffer = (char*)malloc(tmpPixelSize);
//    //glReadBuffer(GL_FRONT);
//    glReadPixels(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,GL_RGBA, GL_UNSIGNED_BYTE, tmpPixelsBuffer);
//    for (int y = WINDOW_HEIGHT-1; y >=0 ; y--)
//    {
//        for (int x = 0; x < WINDOW_WIDTH; x++)
//        {

//            //蓝色
//            tmpBIT[0] = tmpPixelsBuffer[(y*WINDOW_WIDTH + x) * 4 + 2];
//            //绿色
//            tmpBIT[1] = tmpPixelsBuffer[(y*WINDOW_WIDTH + x) * 4 + 1];
//            //红色
//            tmpBIT[2] = tmpPixelsBuffer[(y*WINDOW_WIDTH + x) * 4 + 0];
//            tmpBIT[3] = 100;//不起作用
//            tmpBIT += 4;
//        }
//    }






//    //从深度缓冲区读取数据
//    int tmpPixelSize = WINDOW_WIDTH*WINDOW_HEIGHT;
//    char* tmpPixelsBuffer = (char*)malloc(tmpPixelSize);
//    //glReadBuffer(GL_NONE);
//    //glReadBuffer(GL_BACK);
//    glReadPixels(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, tmpPixelsBuffer);

//    GLenum aaa = glGetError();
//    for (int y = WINDOW_HEIGHT-1; y >=0 ; y--)
//    {
//        for (int x = 0; x < WINDOW_WIDTH; x++)
//        {
//            //int iii1=tmpPixelsBuffer[(y*WINDOW_WIDTH + x)  + 0];
//            uchar iii=tmpPixelsBuffer[(y*WINDOW_WIDTH + x)  + 0];
//            //int iii=tmpPixelsBuffer[(y*WINDOW_WIDTH + x)  + 0];
//            if(iii<-3){
//                int kk=0;
//            }
//            if(iii<-10){
//                int kk=0;
//            }
//            if(iii<-50){
//                int kk=0;
//            }
//            if(iii>0){
//                int kk=0;
//            }
//            //iii=iii*10;
//            //蓝色
//            tmpBIT[0] = iii;
//            //绿色
//            tmpBIT[1] = iii;
//            //红色
//            tmpBIT[2] = iii;
//            tmpBIT[3] = 255;//不起作用
//            tmpBIT += 4;
//        }
//    }

    //从深度缓冲区读取数据
    int tmpPixelSize = WINDOW_WIDTH*WINDOW_HEIGHT;
    //float* tmpPixelsBuffer = (float*)malloc(tmpPixelSize*4);
    float* tmpPixelsBuffer = new float[ tmpPixelSize ];
    //GLfloat* tmpPixelsBuffer = new GLfloat[ tmpPixelSize ];
    //glReadBuffer(GL_NONE);
    //glReadBuffer(GL_BACK);
    glReadPixels(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,GL_DEPTH_COMPONENT, GL_FLOAT, tmpPixelsBuffer);

    GLenum aaa = glGetError();
    for (int y = WINDOW_HEIGHT-1; y >=0 ; y--)
    {
        for (int x = 0; x < WINDOW_WIDTH; x++)
        {
            //int iii1=tmpPixelsBuffer[(y*WINDOW_WIDTH + x)  + 0];
            float iii=tmpPixelsBuffer[(y*WINDOW_WIDTH + x)  + 0];
            if(iii<0.9){
                int kk=0;
            }
            if(iii<0.8){
                int kk=0;
            }
            if(iii<0.2){
                int kk=0;
            }
            if(iii<0.1){
                int kk=0;
            }
            //iii=iii*10;
            iii*=255;
            //蓝色
            tmpBIT[0] = iii;
            //绿色
            tmpBIT[1] = iii;
            //红色
            tmpBIT[2] = iii;
            tmpBIT[3] = 255;//不起作用
            tmpBIT += 4;
        }
    }


    img->save("a.jpg");
}
class Main : public ICallbacks
{
public:

    Main()
    {
        m_pEffect = NULL;
        m_pShadowMapTech = NULL;
        m_pGameCamera = NULL;
        m_pMesh = NULL;
        m_pQuad = NULL;
        m_scale = 0.0f;

        m_spotLight.AmbientIntensity = 0.0f;
        m_spotLight.DiffuseIntensity = 0.9f;
        m_spotLight.Color = Vector3f(1.0f, 1.0f, 1.0f);
        m_spotLight.Attenuation.Linear = 0.01f;
        m_spotLight.Position  = Vector3f(-20.0, 20.0, 5.0f);
        m_spotLight.Direction = Vector3f(1.0f, -1.0f, 0.0f);
        m_spotLight.Cutoff =  20.0f;

        m_directionalLight.Color = Vector3f(1.0f, 1.0f, 1.0f);
        m_directionalLight.AmbientIntensity = 1.0f;
        m_directionalLight.DiffuseIntensity = 0.01f;
        m_directionalLight.Direction = Vector3f(1.0f, 0.0f, 1.0f);
    }

    virtual ~Main()
    {
        SAFE_DELETE(m_pEffect);
        SAFE_DELETE(m_pShadowMapTech);
        SAFE_DELETE(m_pGameCamera);
        SAFE_DELETE(m_pMesh);
        SAFE_DELETE(m_pQuad);
    }

    bool Init()
    {
        if (!m_shadowMapFBO.Init(WINDOW_WIDTH, WINDOW_HEIGHT)) {
            return false;
        }

        m_pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT);

        m_pEffect = new LightingTechnique();

        if (!m_pEffect->Init()) {
            printf("Error initializing the lighting technique\n");
            return false;
        }

        m_pShadowMapTech = new ShadowMapTechnique();

        if (!m_pShadowMapTech->Init()) {
            printf("Error initializing the shadow map technique\n");
            return false;
        }

        m_pShadowMapTech->Enable();

        m_pQuad = new Mesh();

        if (!m_pQuad->LoadMesh("../Content/quad.obj")) {
            return false;
        }

        m_pMesh = new Mesh();

        return m_pMesh->LoadMesh("../Content/phoenix_ugv.md2");

//        Texture* m_Textures = new Texture(GL_TEXTURE_2D, "../Content/bricks.jpg");
//        bool Ret = m_Textures->Load();
//        m_Textures->Bind(GL_TEXTURE0);


//        Vector3f Pos(-10.0f, 4.0f, 0.0f);
//        Vector3f Target(1.0f, 0.0f, 1.0f);
//        Vector3f Up(0.0, 1.0f, 0.0f);
//        m_pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, Pos, Target, Up);

//        m_pEffect = new LightingTechnique();

//        if (!m_pEffect->Init()){
//            printf("Error initializing the lighting technique\n");
//            return false;
//        }

//        m_pEffect->Enable();

//        m_pEffect->SetTextureUnit(0);

//        m_pMesh = new Mesh();

//        return m_pMesh->LoadMesh("../Content/phoenix_ugv.md2");
    }

    void Run()
    {
        GLUTBackendRun(this);
    }

    virtual void RenderSceneCB()
    {
        m_pGameCamera->OnRender();
        m_scale += 0.05f;

        ShadowMapPass();

        RenderPass();

        glutSwapBuffers();



//        glEnable(GL_DEPTH_TEST);
//        m_pGameCamera->OnRender();
//        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//        m_scale += 0.01f;
//        Pipeline p;
//        p.Scale(0.1f, 0.1f, 0.1f);
//        p.Rotate(0.0f, m_scale, 0.0f);
//        p.WorldPos(0.0f, 0.0f, 10.0f);
//        p.SetCamera(m_pGameCamera->GetPos(), m_pGameCamera->GetTarget(), m_pGameCamera->GetUp());
//        p.SetPerspectiveProj(60.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 100.0f);
//        m_pEffect->SetWVP(p.GetWVPTrans());
//        m_pEffect->SetWorldMatrix(p.GetWorldTrans());
//        m_pEffect->SetDirectionalLight(m_directionalLight);
//        m_pEffect->SetEyeWorldPos(m_pGameCamera->GetPos());
//        m_pEffect->SetMatSpecularIntensity(0.0f);
//        m_pEffect->SetMatSpecularPower(0);
//        m_pMesh->Render();
//        saveImg();
//        glutSwapBuffers();


    }

    virtual void ShadowMapPass()
    {
        m_shadowMapFBO.BindForWriting();


        glClear(GL_DEPTH_BUFFER_BIT);
        //glEnable(GL_DEPTH_TEST);
        //glDepthRange(0,0.5);

        Pipeline p;
        p.Scale(0.1f, 0.1f, 0.1f);
        p.Rotate(0.0f, m_scale, 0.0f);
        p.WorldPos(0.0f, 0.0f, 5.0f);
        p.SetCamera(m_spotLight.Position, m_spotLight.Direction, Vector3f(0.0f, 1.0f, 0.0f));
        p.SetPerspectiveProj(20.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 50.0f);
        m_pShadowMapTech->SetWVP(p.GetWVPTrans());

        m_pMesh->Render();
        //saveImg();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);


//        m_shadowMapFBO.BindForWriting();
//        glDepthRange(0,0.5);

//        //glDepthRange(1,0);
//        //glClearDepth(200.0);
//        glClear(GL_DEPTH_BUFFER_BIT);
//        glEnable(GL_DEPTH_TEST);




//        //saveImg();

//        Pipeline p;
//        p.Scale(0.2f, 0.2f, 0.2f);
//        p.Rotate(0.0f, m_scale, 0.0f);
//        p.WorldPos(0.0f, 0.0f, 5.0f);
//        p.SetCamera(m_spotLight.Position, m_spotLight.Direction, Vector3f(0.0f, 1.0f, 0.0f));
//        p.SetPerspectiveProj(60.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 50.0f);
//        m_pShadowMapTech->SetWVP(p.GetWVPTrans());
//        m_pMesh->Render();

//        //saveImg();
//        glEnable(GL_TEXTURE_2D);
//        glDrawBuffer(GL_NONE);
//        glReadBuffer(GL_NONE);
//        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    virtual void RenderPass()
    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_pShadowMapTech->SetTextureUnit(0);
        m_shadowMapFBO.BindForReading(GL_TEXTURE0);

        Pipeline p;
        p.Scale(5.0f, 5.0f, 5.0f);
        p.WorldPos(0.0f, 0.0f, 10.0f);
        p.SetCamera(m_pGameCamera->GetPos(), m_pGameCamera->GetTarget(), m_pGameCamera->GetUp());
        p.SetPerspectiveProj(60.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 50.0f);
        m_pShadowMapTech->SetWVP(p.GetWVPTrans());
        m_pQuad->Render();





//        glBindFramebuffer(GL_FRAMEBUFFER, 0);
//        glDepthRange(1,0);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        //saveImg();

//        m_pShadowMapTech->SetTextureUnit(0);
//        m_shadowMapFBO.BindForReading(GL_TEXTURE0);

//        //glGenerateMipmapEXT(GL_TEXTURE_2D);

//        Pipeline p;
//        p.Scale(5.0f, 5.0f, 5.0f);
//        p.WorldPos(0.0f, 0.0f, 10.0f);
//        p.SetCamera(m_pGameCamera->GetPos(), m_pGameCamera->GetTarget(), m_pGameCamera->GetUp());
//        p.SetPerspectiveProj(60.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 50.0f);
//        m_pShadowMapTech->SetWVP(p.GetWVPTrans());
//        m_pQuad->Render();
//        //saveImg();
    }

    virtual void IdleCB()
    {
        RenderSceneCB();
    }

    virtual void SpecialKeyboardCB(int Key, int x, int y)
    {
        m_pGameCamera->OnKeyboard(Key);
    }


    virtual void KeyboardCB(unsigned char Key, int x, int y)
    {
        switch (Key) {
            case 'q':
                glutLeaveMainLoop();
                break;
        }
    }


    virtual void PassiveMouseCB(int x, int y)
    {
        m_pGameCamera->OnMouse(x, y);
    }

private:

    LightingTechnique* m_pEffect;
    ShadowMapTechnique* m_pShadowMapTech;
    Camera* m_pGameCamera;
    float m_scale;
    SpotLight m_spotLight;
    Mesh* m_pMesh;
    Mesh* m_pQuad;
    ShadowMapFBO m_shadowMapFBO;
    DirectionalLight m_directionalLight;
};


int main(int argc, char** argv)
{
    GLUTBackendInit(argc, argv);

    if (!GLUTBackendCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 32, false, "OpenGL tutors")) {
        return 1;
    }

    Main* pApp = new Main();

    if (!pApp->Init()) {
        return 1;
    }

    const GLubyte* name = glGetString(GL_VENDOR); //返回负责当前OpenGL实现厂商的名字
    const GLubyte* biaoshifu = glGetString(GL_RENDERER); //返回一个渲染器标识符，通常是个硬件平台
    const GLubyte* OpenGLVersion = glGetString(GL_VERSION); //返回当前OpenGL实现的版本号
    const GLubyte* gluVersion = gluGetString(GLU_VERSION); //返回当前GLU工具库版本
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    printf("OpenGL实现厂商的名字：%s\n", name);
    printf("渲染器标识符：%s\n", biaoshifu);
    printf("OpenGL实现的版本号：%s\n", OpenGLVersion);
    printf("OGLU工具库版本：%s\n", gluVersion);
    printf("GLSL Version : %s\n", glslVersion);

    GLint m_maxRenderBufferSize;
    glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &m_maxRenderBufferSize);

    pApp->Run();

    delete pApp;

    return 0;
}
