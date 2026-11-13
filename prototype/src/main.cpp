#include "glad/glad.h"
#include <assimp/aabb.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SDL3/SDL.h>

#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_opengl3.h"

#include "engine/ecs_core/component_manager.hpp"
#include "engine/ecs_core/entity_manager.hpp"
#include "engine/components/transform.hpp"
#include "engine/components/mesh.hpp"

#include "engine/renderer/model_loader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

unsigned int VAO, VBO, EBO;
const int WIDTH = 800;
const int HEIGHT = 600;

// Cube Data
float vertices[] = {
    // ===== FRONT FACE (Normals +Z) =====
    // Position           // Normals
    -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f, // Index 0 (Bottom-Left)
     0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f, // Index 1 (Bottom-Right)
     0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f, // Index 2 (Top-Right)
    -0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f, // Index 3 (Top-Left)
    // ===== BACK FACE (Normals -Z) =====
    -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f, // Index 4 (Bottom-Left)
     0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f, // Index 5 (Bottom-Right)
     0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f, // Index 6 (Top-Right)
    -0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f, // Index 7 (Top-Left)
    // ===== TOP FACE (Normals +Y) =====
    -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f, // Index 8 (Front-Left)
     0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f, // Index 9 (Front-Right)
     0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f, // Index 10 (Back-Right)
    -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f, // Index 11 (Back-Left)
    // ===== BOTTOM FACE (Normals -Y) =====
    -0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f, // Index 12 (Front-Left)
     0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f, // Index 13 (Front-Right)
     0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f, // Index 14 (Back-Left)
    -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f, // Index 15 (Back-Right)
    // ===== RIGHT FACE (Normals +X) =====
     0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f, // Index 16 (Back-Bottom)
     0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f, // Index 17 (Back-Top)
     0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f, // Index 18 (Front-Top)
     0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f, // Index 19 (Front-Bottom)
    // ===== LEFT FACE (Normals -X) =====
    -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f, // Index 20 (Back-Bottom)
    -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f, // Index 21 (Back-Top)
    -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f, // Index 22 (Front-Top)
    -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f, // Index 23 (Front-Bottom)
};
unsigned int indices[] = {
    // FRONT FACE
    0, 1, 2,
    0, 2, 3,
    // BACK FACE
    5, 4, 7,
    5, 7, 6,
    // TOP FACE
    8, 9, 10,
    8, 10, 11,
    // BOTTOM FACE
    12, 13, 14,
    12, 14, 15,
    // RIGHT FACE
    19, 16, 17,
    19, 17, 18,
    // LEFT FACE
    20, 23, 22,
    20, 22, 21
};

glm::vec3 cubeColor = glm::vec3(1.0f, 0.0f, 0.0f);

// Light Data
glm::vec3 lightPos = glm::vec3(-3.0f, 3.0f, 2.0f);

// Camera Data
/*
float camRad = 5.0f;
glm::vec3 camTarget = glm::vec3(0.0f, 0.0f, 0.0f);
float camYaw = 0.0f;
float camPitch = 45.0f;
glm::vec3 cameraPos = glm::vec3(camRad * std::sin(glm::radians(camYaw)) * std::cos(glm::radians(camPitch)) + camTarget.x,
                                camRad * std::sin(glm::radians(camPitch)) + camTarget.y,
                                camRad * std::cos(glm::radians(camYaw)) * std::cos(glm::radians(camPitch)) + camTarget.z);
float fieldOfView = 45.0f;
*/

/**
 * @brief Compiles a shader from a given source file path
 * @param path The specified path to the shader, relative to the build path (e.g. ../assets/shaders)
 * @param type The shader type to be compiled (e.g. GL_VERTEX_SHADER, GL_FRAGMENT_SHADER)
 * @return The OpenGL ID for the successully created shader
 */
unsigned int createShader(std::string path, unsigned int type) {
    std::ifstream shaderStream(path);
    if (!shaderStream.is_open()) {
        std::cerr << "Failed to open shader at " << path;
    }
    std::stringstream shaderSStream;
    shaderSStream << shaderStream.rdbuf();
    std::string shaderSourceStr = shaderSStream.str();
    const GLchar* shaderSourceCStr = shaderSourceStr.c_str();

    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderSourceCStr, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        glDeleteShader(shader); 
        std::cerr << "Shader Compilation Failed (" + path + "):\n" + std::string(infoLog);
    }
    return shader;
}

int main() {

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Error: Failed to initialize SDL3: " << SDL_GetError() << "\n";
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_Window* window = SDL_CreateWindow(
        "Prototype",
        WIDTH,
        HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE 
    );

    if (!window) {
        std::cerr << "Error: Failed to create SDL window: " << SDL_GetError() << "\n";
        SDL_Quit();
        return -1;
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        std::cerr << "Error: Failed to create OpenGL context: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    SDL_GL_MakeCurrent(window, glContext);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Error: Failed to initialize Glad loader!\n";
        SDL_GL_DestroyContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGuiStyle& style = ImGui::GetStyle();
    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init();

    glViewport(0, 0, WIDTH, HEIGHT);

    // Depth Culling
    glEnable(GL_DEPTH_TEST);

    // Initialize and Compile Shaders
    unsigned int vertexShader = createShader("assets/shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
    unsigned int fragmentShader = createShader("assets/shaders/fragment_shader.glsl", GL_FRAGMENT_SHADER);

    // Attach the shaders to the program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Delete the shader resources after attaching
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    bool isRunning = true;
    SDL_Event event;

    // Initialize entity manager and create 2 cube entities
    EntityManager manager;
    Entity cube1 = manager.CreateEntity();
    Entity cube2 = manager.CreateEntity();

    // Create transform components and store at the cube entity id indices
    ComponentManager components;
    components.AddComponent<Transform>(cube1, 1.0, 0.0, 0.0, 0.0, 45.0, 0.0, 1.0, 1.0, 1.0);
    components.AddComponent<Transform>(cube2, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 2.0, 1.0);

    std::vector<float> vertexList(std::begin(vertices), std::end(vertices));
    std::vector<unsigned int> indexList(std::begin(indices), std::end(indices));

    components.AddComponent<Mesh>(cube1, vertexList, indexList, 0, 0, 0);
    components.AddComponent<Mesh>(cube2, vertexList, indexList, 0, 0, 0);

    ModelLoader modelLoader(shaderProgram);

    modelLoader.SetupMesh(components.GetComponent<Mesh>(cube1));
    modelLoader.SetupMesh(components.GetComponent<Mesh>(cube2));

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT) {
                isRunning = false;
            }
            if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.key == SDLK_ESCAPE) {
                    isRunning = false; // Press ESC to quit
                }
            }
        }

        glClearColor(0.12f, 0.20f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // Model matrix with cube rotated 45 degrees
        // Get all entities with transform components, and render them
        auto entities = components.GetEntitiesWith<Transform>();
        for (Entity entity : entities) {
            auto& transform = components.GetComponent<Transform>(entity);
            auto& mesh = components.GetComponent<Mesh>(entity);

            modelLoader.DrawMesh(transform, mesh);
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
        ImGui::BeginMainMenuBar();
        if (ImGui::BeginMenu("Insert")) {
            if (ImGui::MenuItem("Cube")) {
                //modelLoader.drawModels();

                Entity newCube = manager.CreateEntity();

                components.AddComponent<Transform>(newCube, 0.0, 0.0, 0.0, 0.0, 45.0, 0.0, 1.0, 1.0, 1.0);
                components.AddComponent<Mesh>(newCube, vertexList, indexList, 0, 0, 0);
                modelLoader.SetupMesh(components.GetComponent<Mesh>(newCube));
            }
            ImGui::EndMenu();
        }
	ImGui::Separator();
        ImGui::Text("%.1f FPS", io.Framerate);
        ImGui::EndMainMenuBar();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DestroyContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
