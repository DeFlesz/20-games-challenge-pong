#include "Game.h"

Game::Game(int width, int height)
    : WIDTH(width), HEIGHT(height)
{
    Init();
    Run();
}

Game::~Game()
{

}

void Game::Init() 
{
    glfwInit();

    window = glfwCreateWindow(WIDTH, HEIGHT, "Okno", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        std::cout << "fail...\n";
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        is_running = false;
    }

    glViewport(0, 0, WIDTH, HEIGHT);

        const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
    
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    
    shader = glCreateProgram();
    char infoLog[512];
    int success;
    
    glAttachShader(shader, vertexShader);
    glAttachShader(shader, fragmentShader);
    glLinkProgram(shader);

    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(shader);

    

    glGenVertexArrays(1, &ball_vao);
    glBindVertexArray(ball_vao);

    glGenBuffers(1, &ball_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, ball_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ball_vertices), ball_vertices, GL_ARRAY_BUFFER);

    glGenBuffers(1, &ball_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ball_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    

    glGenVertexArrays(1, &paddle_vao);
    glBindVertexArray(paddle_vao);

    glGenBuffers(1, &paddle_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, paddle_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(paddle_vertices), paddle_vertices, GL_ARRAY_BUFFER);

    glGenBuffers(1, &paddle_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, paddle_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Game::PollEvents() 
{
    glfwPollEvents();
}

void Game::Render() {
    //  salmon color
    glClearColor(1.0f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(shader);
    glBindVertexArray(ball_vao);
    // glBindVertexArray(paddle_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


    // final render step swapping buffers
    glfwSwapBuffers(window);
}

void Game::Run()
{
    while (is_running && !glfwWindowShouldClose(window))
    {
        // pollEvents();
        // doStuff();
        // render();
        PollEvents();
        PlayersInput();
        Render();
    }
}

void Game::BallCollisions()
{
    //Check against walls and player paddles
}

void Game::PlayersInput()
{
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        std::cout << "Player 1 wants to move up" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        std::cout << "Player 1 wants to move down" << std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        std::cout << "Player 2 wants to move up" << std::endl;   
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        std::cout << "Player 2 wants to move down" << std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        std::cout << "Players want to pause" << std::endl;   
    }
}

