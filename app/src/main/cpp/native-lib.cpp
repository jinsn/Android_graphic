#include <jni.h>
#include <memory>
#include <string>
#include <mutex>
#include <chrono>
#include <android/log.h>
#include <vector>
#include <map>
#include <unordered_map>
#include <thread>
#include "JThread.h"
#include <cstdio>
#include <cstdlib>
#include "android/native_window.h"
#include "android/native_window_jni.h"
#include <GLES2/gl2.h>
#include <GLES3/gl3.h>
#include <GLES2/gl2ext.h>
#include <GLES3/gl3ext.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <list>
#include <memory>
#include <cstring>
#include <iostream>
#include <sstream>
#include <cmath>
#include <cerrno>
#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define TAG "JSN"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__);

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
static AAssetManager* assetManager;
// utility function for loading a 2D texture from file
// ---------------------------------------------------
std::string jsn="/data/user/0/com.jsn.myapplication/files/girl1.png"; ///data/data/com.jsn.demo1/girl.JPG

class NativeJsn {

};

float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
};
unsigned int indices[] =   {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
};
float vertices1[] = {
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

float verticesCube[] = {
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



// world space positions of our cubes
glm::vec3  cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
};

static std::vector<NativeJsn> jsns;

static std::unordered_map<jobject, NativeJsn *> object_data_map;


extern "C"
JNIEXPORT void JNICALL
Java_com_jsn_demo1_Jsn_native_1construct(JNIEnv *env, jobject thiz) {
    object_data_map[thiz] = new NativeJsn();
    LOGE("JSN");
    LOGE("JSN data:%s", "haha");
    /*    int * a =new int(4);
        int *p = new int[23];
        int (*array)[234]=new int[23][234];
        int(**array_ptr)[234]=&array;
        int b[5];*/
}
extern "C"
JNIEXPORT void JNICALL
Java_com_jsn_demo1_Jsn_native_1deconstruct(JNIEnv *env, jobject thiz) {

    auto p = object_data_map[thiz];
    if (p != nullptr) {
        delete p;
    }
    object_data_map.erase(thiz);

    auto find = object_data_map.find(thiz);
    if (find != object_data_map.end()) {
        if (find->second != nullptr)
            delete find->second;
    }
    object_data_map.erase(find);
    auto it = object_data_map.begin();
    while (it != object_data_map.end()) {
        {
        }
        it++;
    }
}

struct RenderPara {
    EGLDisplay _display;
    EGLSurface _surface;
    EGLContext _context;

    EGLint _width;
    EGLint _height;

    RenderPara() {
        memset(this, 0, sizeof(RenderPara));
    }
};

class Renderer : public JThread {
public://constructor
    Renderer() {
        lock = std::unique_lock<std::mutex>(mutex, std::defer_lock);
    };

    ~Renderer() {
        stop();
        if (_window != nullptr)
            ANativeWindow_release(_window);
        _window = nullptr;
    };
    /*-----------state data start-----------*/
public:
    std::mutex mutex;
    ANativeWindow *_window = nullptr;
    bool windowSet = false; //request window set?
    bool createOpration = false;
    bool isPaused = false;
    bool hasEgl = false;
    bool releaseWhenPause = true;
    bool sizeSet = false;
    bool destroyWindow = false;
    bool destroyWindowOpertion = false;
    bool reCreateDrawResources = true;
    /*-----------state data end------*/
    std::unique_lock<std::mutex> lock;

public:
    long long time=0;


public://--------------------gl data
    RenderPara _renderParam;


public:/*---------lifecycle functions start------------------------------*/
    void resume() {
        mutex.lock();
        isPaused = false;
        mutex.unlock();
    };

    bool isRunning() {
        return t != nullptr;
    };

    bool isPausing() { return isRunning() && isPaused; };

    void pause() { //暂停
        mutex.lock();
        isPaused = true;
        LOGE("pause");
        mutex.unlock();
    };

    void playPause(){
        mutex.lock();
        if(m_State==STATE_PLAYING){
            isPaused= true;
            m_State =STATE_PLAYING;
        }
        if(m_State==STATE_PAUSING){
            isPaused= false;
            m_State=STATE_PAUSING;
        }
        mutex.unlock();
    };

    void surfaceChanged(int w, int h) {
        mutex.lock();
        sizeSet = true;
        _renderParam._width = w;
        _renderParam._height = h;
        LOGE("surface_change");
        mutex.unlock();
    };

    //main thread
    void surfaceDestroyed(JNIEnv *env, jobject surface) {
        mutex.lock();
        destroyWindow = true;
        m_State=STATE_IDLE;
        LOGE("surface_destroyed");
        mutex.unlock();
    };

    //main thread
    void surfaceCreated(JNIEnv *env, jobject surface) {
        mutex.lock();
        _window = ANativeWindow_fromSurface(env, surface);
        windowSet = true;
        LOGE("surface_created,window is nullPtr? %d", _window == nullptr);
        mutex.unlock();
    };

    /*--------------lifecycle functions end------------------*/

    void desrtroyEgl() {
        eglMakeCurrent(_renderParam._display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        eglDestroyContext(_renderParam._display, _renderParam._context);
        eglDestroySurface(_renderParam._display, _renderParam._surface);
        eglTerminate(_renderParam._display);

        _renderParam._display = EGL_NO_DISPLAY;
        _renderParam._surface = EGL_NO_SURFACE;
        _renderParam._context = EGL_NO_CONTEXT;
        //resetCamera();
    };

    void resetCamera() {};

    int dx = -1, dy = -1;
    bool processInput = false;

    //fixme : client api paramaters
    void processInputClient(int dx, int dy) {
        mutex.lock();
        processInput = true;
        this->dx = dx;
        this->dy = dy;
        mutex.unlock();
    };

    bool initEgl() { //after native window
        /*
    * Here specify the attributes of the desired configuration.
    * Below, we select an EGLConfig with at least 8 bits per color
    * component compatible with on-screen windows
    */
        const EGLint attribs[] = {
                EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                EGL_BLUE_SIZE, 8,
                EGL_GREEN_SIZE, 8,
                EGL_RED_SIZE, 8,
                EGL_ALPHA_SIZE, 8,
                EGL_DEPTH_SIZE, 16,
                EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT_KHR,
                EGL_NONE
        };
        EGLint attribList[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE}; // OpenGL 2.0
        EGLint w, h, format;
        EGLint numConfigs;
        EGLConfig config;
        EGLSurface surface;
        EGLContext context;

        EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

        eglInitialize(display, 0, 0);
        /* Here, the application chooses the configuration it desires.
         * find the best match if possible, otherwise use the very first one
         */
        eglChooseConfig(display, attribs, nullptr, 0, &numConfigs);
        std::unique_ptr<EGLConfig[]> supportedConfigs(new EGLConfig[numConfigs]);
        //    assert(supportedConfigs);
        eglChooseConfig(display, attribs, supportedConfigs.get(), numConfigs, &numConfigs);
        LOGE("configure number is:%d", numConfigs);
        //    assert(numConfigs);
        auto i = 0;
        for (; i < numConfigs; i++) {
            auto &cfg = supportedConfigs[i];
            EGLint r, g, b, d,a;
            if (eglGetConfigAttrib(display, cfg, EGL_RED_SIZE, &r) &&
                eglGetConfigAttrib(display, cfg, EGL_GREEN_SIZE, &g) &&
                eglGetConfigAttrib(display, cfg, EGL_BLUE_SIZE, &b) &&
                eglGetConfigAttrib(display, cfg, EGL_ALPHA_SIZE, &a) &&
                eglGetConfigAttrib(display, cfg, EGL_DEPTH_SIZE, &d) &&
                r == 8 && g == 8 && b == 8 && d >= 16 && a ==8) {

                config = supportedConfigs[i];
                LOGE("choose config[%d]", i);
                break;
            }
        }
        if (i == numConfigs) {
            LOGE("config specific failed , choose the first one");
            config = supportedConfigs[0];
        }

        /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
         * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
         * As soon as we picked a EGLConfig, we can safely reconfigure the
         * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
        eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
        if (_window != nullptr) LOGE("window NOT nullPtr");
        surface = eglCreateWindowSurface(display, config, _window, nullptr);
        if (_window != nullptr) LOGE("window NOT nullPtr");
        context = eglCreateContext(display, config, EGL_NO_CONTEXT, attribList);

        if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
            LOGE("GLRenderer::InitRender() eglMakeCurrent failed\n");
            return false;
        }

        eglQuerySurface(display, surface, EGL_WIDTH, &w);
        eglQuerySurface(display, surface, EGL_HEIGHT, &h);

        _renderParam._display = display;
        _renderParam._surface = surface;
        _renderParam._context = context;
        _renderParam._width = w;
        _renderParam._height = h;

        //glEnable(GL_DEPTH_TEST);   /// 关闭透明
        //glDisable(GL_ALPHA_TEST);
        //glEnable(GL_BLEND);
        //(GL_DITHER);
        //glEnable( GL_DEPTH_TEST );
       /* glDepthFunc( GL_LEQUAL );
        glDepthMask( true );*/

        //glEnable(GL_CULL_FACE);     /// 开始剔除操作
        //glEnable(GL_TEXTURE_2D);

        // 黑色背景


        //gl.glClearColor(0, 0, 0, 0);


// 启用阴影平滑

        //lgShadeModel(SMOO);

// 启用深度测试

        glEnable(GL_DEPTH_TEST);

//启用纹理映射



//深度测试的类型

//精细的透视修正

//允许2D贴图,纹理

        glEnable(GL_TEXTURE_2D);

        //glClearColor(0, 0, 0, 0);                   // background color
        //glClearStencil(0);                                               // clear stencil buffer
        glViewport(0, 0, w, h);
        return true;
    };

    int loopCount = 0;

    typedef enum {
        STATE_IDLE=0,
        STATE_PLAYING=1,
        STATE_PAUSING=2,
    } State;

    State  m_State=STATE_IDLE;

    int state(){
        int mStateNow= m_State; //after we have lock ,we copy state immediately ;
        return mStateNow;
    };

    void run() override {
        using namespace std::literals;
        while (true) {
            if (stopFlag)
                break;
            //loopCount++;LOGE("renderLoop:%d",loopCount);
            mutex.lock();

            if (_window != nullptr) {
                if (windowSet) {
                    //gl destroy old window?
                    //gl create window context surface
                    if (hasEgl)
                        desrtroyEgl();
                    int ret = initEgl();
                    LOGE("init_gl:%d:", ret);
                    createOpration = true;
                    hasEgl = true;
                    reCreateDrawResources = true;//cause we recreate egl
                }

                if (destroyWindow) {
                    if (hasEgl)
                        desrtroyEgl();
                    if (_window != nullptr)
                        ANativeWindow_release(_window);
                    LOGE("destroy window");
                    _window = nullptr;
                    hasEgl = false;
                    createOpration = false;
                    destroyWindowOpertion = true;
                }
            }
            if (hasEgl) {
                if (sizeSet) {
                    sizeSet = false;
                    glViewport(0, 0, _renderParam._width, _renderParam._height);
                }
            }
            sizeSet = false;
            windowSet = false;
            destroyWindow = false;
            if (destroyWindowOpertion) {
                destroyWindowOpertion = false;
                isPaused = false;
            }

            /*------------input processing--------*/
            if (_window == nullptr || isPaused) { //if we are waiting for window or we are pausing
                ;//do nothing
                processInput = false;
                dx = -1;
                dy = -1;
            } else {
                if (processInput) {
                    dx; //do something,eg,change camera position;
                    dy; //do something with it
                    processInput = false;
                    dx = -1;
                    dy = -1;
                }
            }
            /*------------------input processing------------*/

            if (isPaused) {
                if (releaseWhenPause) {
                    // release eglcontext
                    LOGE("desrtoy egl when pause if has egl")
                    if (hasEgl) {
                        LOGE("DESTORY")
                        desrtroyEgl();
                    }
                    hasEgl = false;
                }
                //LOGE("sleep for pausing")
                m_State=STATE_PAUSING;
                mutex.unlock();
                std::this_thread::sleep_for(    2ms);
                continue;
            }
            if (createOpration) {
                createOpration = false;
            } else {
                if (_window == nullptr) {
                    if (hasEgl) {
                        desrtroyEgl();
                    }
                    //LOGE("wait for window");
                    m_State=STATE_IDLE;
                    mutex.unlock();
                    std::this_thread::sleep_for(    2ms);
                    continue;
                } else {
                    if (hasEgl) {
                    } else {
                        //gl create window context surface
                        //probably resume ,we reach here ,we have window ,and not pasuing ,so we shall render
                        hasEgl = true;
                        LOGE("initEgl");
                        initEgl();
                        reCreateDrawResources = true;
                    }
                }
            }
            m_State=STATE_PLAYING;
            drawF();
            mutex.unlock();
            std::this_thread::sleep_for(16ms);//render at about 120fps
        }
        //------------------------clean up-----------------------
        if (hasEgl)
            desrtroyEgl();
        if (_window != nullptr)
            ANativeWindow_release(_window);
        _window = nullptr;
        m_State=STATE_IDLE;
        LOGE("Thread ending...");
    };


    const char *vertexShaderSource_lighting_cube =  "#version 320 es\n"
                                                    "precision mediump float;\n"
                                                    "layout (location=0) in vec3 aPos;\n"
                                                    "uniform mat4 projection;\n"
                                                    "uniform mat4 model;\n"
                                                    "uniform mat4 view;\n"
                                                    "void main()\n"
                                                    "{\n"
                                                    "   gl_Position = projection * view * model* vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                                    "}\0";
    const char *fragmentShaderSource_lighting_cube = "#version 320 es\n"
                                                     "precision mediump float;\n"
                                                     "out vec4 FragColor;\n"
                                                     "uniform vec3 uColor;\n"
                                                     "void main()\n"
                                                     "{\n"
                                                     "   FragColor = vec4(uColor, 0.5);\n"
                                                     "}\n\0";

    GLuint vShader, fShader,program;
    GLuint loadShader(GLenum shaderType, const char* pSource) {
        GLuint shader = glCreateShader(shaderType);
        if (shader) {
            glShaderSource(shader, 1, &pSource, NULL);
            glCompileShader(shader);
            //检查错误
            GLint compiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
            if (!compiled) {
                GLint infoLen = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
                if (infoLen) {
                    char* buf = (char*) malloc(infoLen);
                    if (buf) {
                        memset(buf, 0, infoLen);
                        glGetShaderInfoLog(shader, infoLen, NULL, buf);
                        LOGE("GLRenderer::loadShader() shader info log:%s\n", buf);
                        free(buf);
                    }
                    glDeleteShader(shader);
                    shader = 0;
                    LOGE("GLRenderer::loadShader() shader is zero.\n");
                }
            }
        }
        return shader;
    }

public:
    unsigned int loadTexture(char const * path)
    {
        const char* mPath = "girl1.png";
        AAsset* mAsset;
        mAsset = AAssetManager_open(assetManager, mPath,AASSET_MODE_BUFFER);
        size_t len = AAsset_getLength(mAsset);
        LOGE("file name and length is: %s,%d", mPath, len );
        stbi_uc* fileContent = new unsigned char[len];
        AAsset_read(mAsset, fileContent, len);
        AAsset_close(mAsset);
        uint32_t imgWidth, imgHeight, n;
        unsigned char* imageData = stbi_load_from_memory(
                fileContent, len, reinterpret_cast<int*>(&imgWidth),
                reinterpret_cast<int*>(&imgHeight), reinterpret_cast<int*>(&n), 0);
        LOGE("n is :%d",n)
        unsigned int textureID;
        glGenTextures(1, &textureID);

        int width=imgWidth, height=imgHeight, nrComponents=n;
        if (imageData)
        {
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(imageData);
        }
        else
        {
            std::cout << "Texture failed to load at path: " << path << std::endl;
            LOGE("Texture failed to load at path:%s ",path)
            stbi_image_free(imageData);
        }
        return textureID;
    }


public:
    /*------lighting------------ */

    unsigned int programLightingCube,vShaderLightingCube,fShaderLightingCube ;
    static const char* vShaderSourceObjectCube;
    static const char* fShaderSourceObjectCube;
    unsigned int programObjectCube,vShaderObjectCube,fShaderObjectCube ;
    glm::vec3 lightPos=glm::vec3 (0.0f,0.0f,0.0f);
    /*------lighting------------*/

    /*draw stuff*/
    unsigned int VBO, EBO,VAOCUBE,VBOCUBE;
    unsigned int VAO_OBJECT,texture_jsn;

    void drawF() {
        if (reCreateDrawResources) {
            //if we need to recreate something when egl recreated,do it  here
            //load iamge
            texture_jsn= loadTexture(jsn.c_str());
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture_jsn);
            LOGE("recreate egl resources");
            glGenVertexArrays(1, &VAOCUBE);
            glGenVertexArrays(1, &VAO_OBJECT);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &VBOCUBE);
            glGenBuffers(1, &EBO);
            /*----------------------------lighting cube (light source)-------------*/
            programLightingCube = glCreateProgram();
            vShaderLightingCube = loadShader(GL_VERTEX_SHADER, vertexShaderSource_lighting_cube);
            fShaderLightingCube = loadShader(GL_FRAGMENT_SHADER, fragmentShaderSource_lighting_cube);
            glAttachShader(programLightingCube, vShaderLightingCube);
            glAttachShader(programLightingCube, fShaderLightingCube);
            glLinkProgram(programLightingCube);
            glDeleteShader(vShaderLightingCube);
            glDeleteShader(fShaderLightingCube);
            /*--------------------------------OBJECT cube-------------*/
            programObjectCube = glCreateProgram();
            vShaderObjectCube = loadShader(GL_VERTEX_SHADER, vShaderSourceObjectCube);
            fShaderObjectCube = loadShader(GL_FRAGMENT_SHADER, fShaderSourceObjectCube);
            glAttachShader(programObjectCube, vShaderObjectCube);
            glAttachShader(programObjectCube, fShaderObjectCube);
            glLinkProgram(programObjectCube);
            glDeleteShader(vShaderObjectCube);
            glDeleteShader(fShaderObjectCube);

            reCreateDrawResources= false;
        }
        std::chrono::time_point<std::chrono::steady_clock> t_p_ofNow = std::chrono::steady_clock::now();
        auto msOfNow = std::chrono::time_point_cast<std::chrono::milliseconds>(t_p_ofNow);
        long long currentTimeMills = msOfNow.time_since_epoch().count(); //time_stamp of this renderLoop
        glViewport(0, 0, _renderParam._width, _renderParam._height);
        //------------------------gl clear---------------------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        //----------------------------lighting cube color and its model view projection matrix------------------------------------------------//
        double math = sin((double )currentTimeMills * 0.00075);
        double positveData = abs(math);
        double math1 = sin((double )currentTimeMills * 0.00045);
        double positveData1 = abs(math1);
        //double cs = cos((double )currentTimeMills * 0.001);
        glm::vec3 vec1((float) positveData, (float) positveData1, abs(sin((double )currentTimeMills * 0.00030)));//LOGE("color is:%f",(float )positveData);
        //vec1=glm::vec3 (1.0f);
        glUniform3fv(glGetUniformLocation(programLightingCube, "uColor"), 1, &vec1[0]);
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float) _renderParam._width /(float) _renderParam._height, 0.1f,100.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
        glUniformMatrix4fv(glGetUniformLocation(programLightingCube, "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(programLightingCube, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUseProgram(programLightingCube);
        glBindVertexArray(VAOCUBE);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCube), verticesCube, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        lightPos= glm::vec3(0,0,0);
        float x = 4*sin((double )currentTimeMills*0.0012);
        float z = 4*cos((double)currentTimeMills*0.0012);    float absZ= abs(z); //z = absZ;
        float y=0;
        y= 2 *sin((double )currentTimeMills*0.00200);

        auto newCenter =glm::vec3(-2.0,2.0,-2.0); newCenter= glm::vec3(1.0);

        for (int i = 0; i < 1; i++) {
            model = glm::mat4(1.0f);
            lightPos=glm::vec3(x,y ,z );
            lightPos=(glm::vec3)   (glm::translate(glm::mat4(1.0f),newCenter)    * glm::vec4(lightPos, 1.0f));
            model = glm::translate(model,lightPos);
            float angle = 20.0f * i + (float)currentTimeMills * 0.0010;
            model= glm::rotate(model,glm::radians(angle),glm::vec3(1.0f,0.3f,0.5f));
            model= glm::scale(model,glm::vec3(0.4f));
            glUniformMatrix4fv(glGetUniformLocation(programLightingCube, "model"), 1, GL_FALSE, &model[0][0]);
            //glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);
        }
        //----------------------object cube-------------------------------------
        glUseProgram(programObjectCube);
        glBindVertexArray(VAO_OBJECT);
        glBindBuffer(GL_ARRAY_BUFFER, VBOCUBE);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCube), verticesCube, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3*sizeof(float )) );
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6*sizeof (float )));
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER,0);

        glUniform1i(glGetUniformLocation(programObjectCube, "material.img"), 0);
        glUniform3fv(glGetUniformLocation(programObjectCube, "material.ambient"), 1,&glm::vec3(0.2f,0.2f,0.2f)[0]);
        glUniform3fv(glGetUniformLocation(programObjectCube, "material.diffuse"), 1,&glm::vec3(0.5f,0.5f,0.5f)[0]);
        glUniform3fv(glGetUniformLocation(programObjectCube, "material.specular"), 1,&glm::vec3(0.7f,0.7f,0.7f)[0]);
        glUniform1f(glGetUniformLocation(programObjectCube, "material.shinnes"), 64.0f);
        glUniform3fv(glGetUniformLocation(programObjectCube, "lightPos"), 1,&lightPos[0]);
        glUniform3fv(glGetUniformLocation(programObjectCube, "lightColor"), 1,&vec1[0]);
        glUniform3fv(glGetUniformLocation(programObjectCube, "viewPos"), 1,&glm::vec3(0.0f,0.0f,10.0f)[0]);

        glm::mat4 model1 = glm::mat4(1.0f);
        float angle_ob=(float)((double)currentTimeMills*0.012);
         //angle_ob=75.0f;
        model1= glm::rotate(model1,glm::radians(angle_ob),glm::vec3(1.0f,0.3f,0.5f));
        model1= glm::scale(model1,glm::vec3(3.0f));
        glm::mat4 projection1 = glm::mat4(1.0f);
        glm::mat4 view1 = glm::mat4(1.0f);
        projection1 = glm::perspective(glm::radians(45.0f), (float) _renderParam._width /(float) _renderParam._height, 0.1f,100.0f);
        view1 = glm::translate(view1, glm::vec3(0.0f, 0.0f, -10.0f));
        glUniformMatrix4fv(glGetUniformLocation(programObjectCube, "view"), 1, GL_FALSE, &view1[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(programObjectCube, "projection"), 1, GL_FALSE, &projection1[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(programObjectCube, "model"), 1, GL_FALSE, &model1[0][0]);
        // bind diffuse map
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glUseProgram(programLightingCube);
        glBindVertexArray(VAOCUBE);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        eglSwapBuffers(_renderParam._display, _renderParam._surface);
    };

};
//todo add another cpp file
//leave model matrix indentify
const char * Renderer::vShaderSourceObjectCube =  "#version 320 es\n"
                                                  "precision highp float;\n"
                                                  "layout (location=0) in vec3 aPos;\n"
                                                  "layout (location=1) in vec3 aNormal;\n"
                                                  "layout (location=2) in vec2 aTexCoord;\n"
                                                  "out vec3 fragPos;\n"
                                                  "out vec3 normal;\n"
                                                  "out vec2 texCoord;\n"
                                                  "uniform mat4 projection;\n"
                                                  "uniform mat4 model;\n"
                                                  "uniform mat4 view;\n"
                                                  "void main()\n"
                                                  "{\n"
                                                  "   fragPos= vec3(model * vec4(aPos, 1.0) );\n"
                                                  "   normal = normalize(mat3(transpose(inverse(model))) * aNormal) ;\n"
                                                  "   texCoord = aTexCoord ;\n"
                                                  "   gl_Position = projection * view * model* vec4(aPos, 1.0);\n"
                                                  "}\0";

const char *Renderer::fShaderSourceObjectCube = "#version 320 es\n"
                                                "precision highp float;\n"
                                                "struct Material{\n"
                                                "    vec3 ambient;\n"
                                                "    vec3 diffuse;\n"
                                                "    vec3 specular;\n"
                                                "    float shinness;\n"
                                                "    sampler2D img;\n"
                                                "};\n"
                                                "out vec4 FragColor;\n"
                                                "uniform vec3 lightPos;\n"
                                                "uniform vec3 lightColor;\n"
                                                "uniform vec3 viewPos;\n"
                                                "uniform Material material;\n"
                                                "in vec3 normal;\n"
                                                "in vec3 fragPos;\n"
                                                "in vec2 texCoord;\n"
                                                "void main()\n"
                                                "{\n"
                                                "    vec3  ambient=  lightColor* material.ambient * texture(material.img, texCoord).rgb; \n" //ambient
                                                "    vec3 lightDir=  normalize (lightPos- fragPos); \n "
                                                "    vec3  diffuse= lightColor *material.diffuse * max(0.0,dot(normal,lightDir )) * texture(material.img,texCoord).rgb; \n" //diffuse
                                                "    float cosineData = dot(lightDir,normal);\n "
                                                "    float spec = 0.0;\n "
                                                "    if(cosineData<=0.0){ \n"
                                                "        spec=0.0001;"
                                                "    }else{ \n"
                                                "        vec3  refDir= reflect( normalize(fragPos- lightPos), normalize(normal)); \n"
                                                "        float  strength=max(0.0001,dot(normalize(refDir),normalize(viewPos-fragPos) )); \n"
                                                "        spec= pow(strength, material.shinness); \n"
                                                "    }"
                                                "    vec3  specular= material.specular * spec *  vec3(0.2) * lightColor ; \n"   //specular
                                                "    vec3 result = ambient+ diffuse + specular  ;\n"
                                                "    FragColor = vec4(result , 1.0);\n"
                                                "}\n\0";

using RenderPtr =std::shared_ptr<Renderer>;
std::unordered_map<std::string, RenderPtr> activityThreadMap;
std::string handle = "handle_of_main_activity";

extern "C"
JNIEXPORT void JNICALL
Java_com_jsn_demo1_MainActivity_native_1surface_1changed(JNIEnv *env, jobject thiz,
                                                         jobject surface, jint w, jint h) {
    auto it = activityThreadMap.find(handle);
    if (it != activityThreadMap.end()) {
        activityThreadMap[handle]->surfaceChanged(w, h);
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_jsn_demo1_MainActivity_native_1surface_1destroyed(JNIEnv *env, jobject thiz,
                                                           jobject surface) {
    auto it = activityThreadMap.find(handle);
    if (it != activityThreadMap.end()) {
        activityThreadMap[handle]->surfaceDestroyed(env, surface);
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_jsn_demo1_MainActivity_native_1destroy(JNIEnv *env, jobject thiz) {
    activityThreadMap[handle]->stop();
    activityThreadMap.erase(handle);
}
//native Activity   onCreate()
extern "C"
JNIEXPORT void JNICALL
Java_com_jsn_demo1_MainActivity_native_1create(JNIEnv *env, jobject thiz) {
    LOGE("handle:%llu", thiz);
    auto it = activityThreadMap.find(handle);
    if (it == activityThreadMap.end()) {
        LOGE("MAKE A RENDERER SHARED");
        activityThreadMap[handle] = std::make_shared<Renderer>();
        //------------------dump unorder map--------------------------------------------
        //   Helper lambda function to print     key-value pairs
        /*   auto print_key_value = [](const auto& key, const auto& value) {
               std::cout << "Key:[" << key << "] Value:[" << value << "]\n";
           };
           for( const std::pair<jobject , std::shared_ptr<Renderer>>& n : activityThreadMap ) {
               print_key_value(n.first, n.second);
           }*/
    }
    activityThreadMap[handle]->start();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jsn_demo1_MainActivity_native_1surface_1created(JNIEnv *env, jobject thiz,
                                                         jobject surface) {
    LOGE("handle:%llu", thiz);
    auto it = activityThreadMap.find(handle);
    if (it == activityThreadMap.end()) {
        LOGE("Thread not found when SurfaceCreated()");
        activityThreadMap[handle] = std::make_shared<Renderer>();
    }
    activityThreadMap[handle]->start();
    activityThreadMap[handle]->surfaceCreated(env, surface);
    for (const auto &n: activityThreadMap) { //std::pair<std::basic_string<char> , std::shared_ptr<Renderer>>
        auto entry =(std::ostringstream() << "Key:[" << n.first
                                                                            << "] Value:["
                                                                            << n.second
                                                                            << "]\n").str();
        LOGE("entry:%s", entry.c_str());
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jsn_demo1_MainActivity_native_1pause(JNIEnv *env, jobject thiz) {
    auto it = activityThreadMap.find(handle);
    if (it != activityThreadMap.end()) {
        activityThreadMap[handle]->pause();
    } else {
        LOGE("Thread not found when onPause()");
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_jsn_demo1_MainActivity_native_1resume(JNIEnv *env, jobject thiz) {
    auto it = activityThreadMap.find(handle);
    if (it != activityThreadMap.end()) {
        activityThreadMap[handle]->resume();
    } else {
        LOGE("Thread not found when onResume()");
    }
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_jsn_demo1_MainActivity_rState(JNIEnv *env, jobject thiz) {
    if(auto it =activityThreadMap.find(handle) != activityThreadMap.end()){
        return activityThreadMap[handle]->state();
    }
    return -1;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_jsn_demo1_MainActivity_native_1PlayPause(JNIEnv *env, jobject thiz) {
    if(auto it =activityThreadMap.find(handle) != activityThreadMap.end()){
        activityThreadMap[handle] -> playPause();
    }
}



extern "C"
JNIEXPORT void JNICALL
Java_com_jsn_demo1_MainActivity_nativeAssetManager(JNIEnv *env, jobject thiz, jobject assets) {
    assetManager = AAssetManager_fromJava(env, assets);
    if (assetManager == NULL) {
        __android_log_print(ANDROID_LOG_ERROR, "NATIVE", "error loading asset   maanger");
    } else {
        __android_log_print(ANDROID_LOG_ERROR, "NATIVE", "loaded asset  manager");
    }
}