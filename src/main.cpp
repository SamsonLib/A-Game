#include "bgfx/defines.h"
#include <stdexcept>
#include <bx/bx.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <GLFW/glfw3.h>

#if defined(_WIN32) || defined(_WIN64)
        #define PLATFORM_WINDOWS
        #define GLFW_EXPOSE_NATIVE_WIN32
#elif defined(__APPLE__)
        #define PLATFORM_MACOS
        #define GLFW_EXPOSE_NATIVE_COCOA
#elif defined(__linux__)
        #define PLATFORM_LINUX
        #define GLFW_EXPOSE_NATIVE_WAYLAND
        #define GLFW_EXPOSE_NATIVE_X11
#else
        #error "Unsupported platform"
#endif

#include <GLFW/glfw3native.h>
#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <print>

constexpr int WINDOW_WIDTH  = 1280;
constexpr int WINDOW_HEIGHT = 720;

void errorCallback(int error, const char* description)
{
        std::println(stderr, "GLFW Error {}: {}", error, description);
}

int main()
{
        glfwSetErrorCallback(errorCallback);

        if (!glfwInit())
                throw std::runtime_error("Failed to initialize GLFW");

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

#ifdef PLATFORM_MACOS
        glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
#endif

        GLFWwindow* window = glfwCreateWindow(
                WINDOW_WIDTH,
                WINDOW_HEIGHT,
                "Nice Game",
                nullptr,
                nullptr
        );

        if (!window) {
                glfwTerminate();
                throw std::runtime_error("Failed to create GLFW window");
        }

        bgfx::RenderFrame();
        bgfx::Init init;

#ifdef PLATFORM_WINDOWS
        std::println("Platform: Windows");
        init.platformData.ndt  = nullptr;
        init.platformData.nwh  = glfwGetWin32Window(window);
        init.platformData.type = bgfx::NativeWindowHandleType::Win32;
#elif defined(PLATFORM_MACOS)
        std::println("Platform: macOS");
        init.platformData.ndt  = nullptr;
        init.platformData.nwh  = glfwGetCocoaWindow(window);
        init.platformData.type = bgfx::NativeWindowHandleType::Cocoa;
#elif defined(PLATFORM_LINUX)
        if (glfwGetPlatform() == GLFW_PLATFORM_WAYLAND) {
                std::println("Platform: Linux (Wayland)");
                init.platformData.ndt  = glfwGetWaylandDisplay();
                init.platformData.nwh  = glfwGetWaylandWindow(window);
                init.platformData.type = bgfx::NativeWindowHandleType::Wayland;
        } else {
                std::println("Platform: Linux (X11)");
                init.platformData.ndt  = glfwGetX11Display();
                init.platformData.nwh  = (void*)(uintptr_t)glfwGetX11Window(window);
                init.platformData.type = bgfx::NativeWindowHandleType::Default;
        }
#endif

        init.resolution.width  = (uint32_t)WINDOW_WIDTH;
        init.resolution.height = (uint32_t)WINDOW_HEIGHT;

        if (!bgfx::init(init))
                throw std::runtime_error("Failed to initialize BGFX");

        bgfx::setDebug(BGFX_DEBUG_TEXT);
        bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x141414ff, 1.0f, 0);

        while (!glfwWindowShouldClose(window)) {
                bgfx::setViewRect(0, 0, 0, uint16_t(WINDOW_WIDTH), uint16_t(WINDOW_HEIGHT));

                bgfx::touch(0);
                bgfx::dbgTextClear();

                bgfx::dbgTextPrintf(0, 1, 0x0f, "Hello, Debug World!");

                bgfx::frame();
                glfwPollEvents();
        }
        
        bgfx::shutdown();
        glfwDestroyWindow(window);
        glfwTerminate();
}
