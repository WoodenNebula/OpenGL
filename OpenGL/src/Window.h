#pragma once

#include <GLFW/glfw3.h>

#include <string>

struct WindowProps {
    std::string Title;
    uint32_t Width, Height;

    WindowProps(const std::string& title = "SandBox", uint32_t width = 800,
                uint32_t height = 720)
        : Title(title), Width(width), Height(height) {}
};

class Window {
   private:
    GLFWwindow* m_WindowHandle;
    struct WindowData {
        std::string Title;
        uint32_t Width, Height;
        bool VSync;
    };

    WindowData m_Data;

   public:
    Window(const WindowProps& props);
    ~Window();

    static Window* Create(const WindowProps& props = WindowProps());

    void OnUpdate();

    inline GLFWwindow* GetWindowHandle() const { return m_WindowHandle; }

    inline uint32_t GetWidth() const { return m_Data.Width; }
    inline uint32_t GetHeight() const { return m_Data.Height; }

    void SetVSync(bool enabled);

    inline bool IsVSync() const { return m_Data.VSync; }

   private:
    /// TODO : further abstract error cases
    void Init(const WindowProps& props);
    void Shutdown();
};