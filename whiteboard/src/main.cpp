#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600

float frameBuffer[WINDOW_HEIGHT][WINDOW_WIDTH][3];
float drawnBuffer[WINDOW_HEIGHT][WINDOW_WIDTH][3];
bool mask[WINDOW_HEIGHT][WINDOW_WIDTH];
GLFWwindow* window;

struct color { float r, g, b; };
struct color brushColor { 1.0f, 1.0f, 1.0f };
struct color backColor { 0, 0, 0 };

int brushSize = 4;  // Initial brush size

#define CLAMP(in, low, high) ((in) < (low) ? (low) : ((in) > (high) ? (high) : in))

void SetFrameBufferPixel(int x, int y, struct color lc)
{
    y = WINDOW_HEIGHT - 1 - y;
    x = CLAMP(x, 0, WINDOW_WIDTH - 1);
    y = CLAMP(y, 0, WINDOW_HEIGHT - 1);
    frameBuffer[y][x][0] = lc.r;
    frameBuffer[y][x][1] = lc.g;
    frameBuffer[y][x][2] = lc.b;
}

void SetDrawnBufferPixel(int x, int y, struct color lc)
{
    y = WINDOW_HEIGHT - 1 - y;
    x = CLAMP(x, 0, WINDOW_WIDTH - 1);
    y = CLAMP(y, 0, WINDOW_HEIGHT - 1);
    drawnBuffer[y][x][0] = lc.r;
    drawnBuffer[y][x][1] = lc.g;
    drawnBuffer[y][x][2] = lc.b;
    mask[y][x] = true;
}

void SetBackData(struct color lc)
{
    for (int y = 0; y < WINDOW_HEIGHT; ++y) {
        for (int x = 0; x < WINDOW_WIDTH; ++x) {
            if (!mask[y][x]) {
                SetFrameBufferPixel(x, y, lc);
            }
        }
    }
}

void SetFrameBuffer(struct color lc)
{
    for (int y = 0; y < WINDOW_HEIGHT; ++y) {
        for (int x = 0; x < WINDOW_WIDTH; ++x) {
            SetFrameBufferPixel(x, y, lc);
            mask[y][x] = false;
        }
    }
}

void ClearMaskData()
{
    memset(mask, 0, WINDOW_HEIGHT * WINDOW_WIDTH * sizeof(bool));
}

void Display()
{
    glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB, GL_FLOAT, frameBuffer);
    // Copy the drawn pixels from the drawnBuffer to the frameBuffer
    for (int y = 0; y < WINDOW_HEIGHT; ++y) {
        for (int x = 0; x < WINDOW_WIDTH; ++x) {
            if (mask[y][x]) {
                SetFrameBufferPixel(x, y, { drawnBuffer[y][x][0], drawnBuffer[y][x][1], drawnBuffer[y][x][2] });
            }
        }
    }
}

void DrawSquare(int xpos, int ypos, int size, struct color lc)
{
    int halfSize = size / 2;
    for (int y = xpos - halfSize; y <= xpos + halfSize; ++y) {
        for (int x = ypos - halfSize; x <= ypos + halfSize; ++x) {
            SetDrawnBufferPixel(x, y, lc);
        }
    }
}

void CursorPositionCallback(GLFWwindow* lWindow, double xpos, double ypos)
{
    int framebufferX = WINDOW_HEIGHT - 1 - (int)ypos;  // Invert the new y-coordinate
    int framebufferY = (int)xpos;                     // Swap x and y

    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (state == GLFW_PRESS) {
        DrawSquare(framebufferX, framebufferY, brushSize, brushColor);
        std::cout << "Mouse position is: x - " << framebufferX << ", y - " << framebufferY << std::endl;
    }
}


void MouseCallback(GLFWwindow* lWindow, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        std::cout << "Mouse left button is pressed." << std::endl;
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        SetFrameBuffer(backColor);
        ClearMaskData();  // Clear the mask data when resetting
        std::cout << "Mouse right button is pressed. Screen reset." << std::endl;
    }
}

void CharacterCallback(GLFWwindow* lWindow, unsigned int key)
{
    if (key == '+') {
        brushSize = CLAMP(brushSize * 2, 1, 128);
    }
    else if (key == '-') {
        brushSize = CLAMP(brushSize / 2, 1, 128);
    }
    else if (key >= '0' && key <= '7') {
        int colorIndex = key - '0';
        brushColor.r = (colorIndex & 0b100) ? 1.0f : 0.0f;
        brushColor.g = (colorIndex & 0b010) ? 1.0f : 0.0f;
        brushColor.b = (colorIndex & 0b001) ? 1.0f : 0.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        switch (key) {
        case '!':  // ASCII 33
            backColor.r = 1.0f; backColor.g = 0.0f; backColor.b = 0.0f; break;  // Red
        case '@':  // ASCII 64
            backColor.r = 0.0f; backColor.g = 1.0f; backColor.b = 0.0f; break;  // Green
        case '#':  // ASCII 35
            backColor.r = 0.0f; backColor.g = 0.0f; backColor.b = 1.0f; break;  // Blue
        case '$':  // ASCII 36
            backColor.r = 1.0f; backColor.g = 1.0f; backColor.b = 0.0f; break;  // Yellow
        case '%':  // ASCII 37
            backColor.r = 0.0f; backColor.g = 1.0f; backColor.b = 1.0f; break;  // Cyan
        case '^':  // ASCII 94
            backColor.r = 1.0f; backColor.g = 0.0f; backColor.b = 1.0f; break;  // Magenta
        case '&':  // ASCII 38
            backColor.r = 0.5f; backColor.g = 0.5f; backColor.b = 0.5f; break;  // Gray
        case '*':  // ASCII 42
            backColor.r = 0.0f; backColor.g = 0.0f; backColor.b = 0.0f; break;  // Black
        case '(':  // ASCII 40
            backColor.r = 1.0f; backColor.g = 1.0f; backColor.b = 1.0f; break;  // White
        default:
            return;
        }
        SetBackData(backColor);
    }
    std::cout << "Key " << (char)key << " is pressed." << std::endl;
}

void Init()
{
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GL_FALSE);
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Assignment 1 - Matthew Mar", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, MouseCallback);
    glfwSetCursorPosCallback(window, CursorPositionCallback);
    glfwSetCharCallback(window, CharacterCallback);
    glewExperimental = GL_TRUE;
    glewInit();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    SetFrameBuffer(backColor);
    ClearMaskData();
}

int main()
{
    Init();
    while (glfwWindowShouldClose(window) == 0) {
        glClear(GL_COLOR_BUFFER_BIT);
        Display();
        glFlush();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
