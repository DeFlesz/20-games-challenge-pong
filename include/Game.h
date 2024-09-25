#include <iostream>

#include <glm/glm.hpp>
#include <glad.h>
#include <GLFW/glfw3.h>

#include "Paddle.h"
#include "Ball.h"

class Game
{
private:
    /* data */
    GLFWwindow *window;
    const int WIDTH;
    const int HEIGHT;
    const int PADDLE_H = 200;
    const int PADDLE_W = 80;
    const int BALL_SIZE = 80;

    bool is_running = true;

    Paddle player1{PADDLE_W, PADDLE_H};
    Paddle player2{PADDLE_W, PADDLE_H};
    Ball ball{BALL_SIZE};

    void PlayersInput();
    void BallCollisions();

    void Init();
    void PollEvents();
    void Render();

    void Run();

    unsigned int ball_vao;
    unsigned int ball_vbo;
    unsigned int ball_ebo;

    unsigned int paddle_vao;
    unsigned int paddle_vbo;
    unsigned int paddle_ebo;

    unsigned int shader;

    unsigned int indices[6] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
    
    float BALL_W = (float)ball.getSize()/800;
    float BALL_H = (float)ball.getSize()/600;

    float ball_vertices[12] =
    {
        -BALL_W, BALL_H, 0.0f,
        BALL_W, BALL_H, 0.0f,
        BALL_W, -BALL_H, 0.0f,
        -BALL_W, -BALL_H, 0.0f
    };

    float P_HORIZONTALLY = (float)player1.GetWidth()/800;
    float P_VERTICALLY = (float)player1.GetHeight()/600;

    float paddle_vertices[12] =
    {
        -P_HORIZONTALLY, P_VERTICALLY, 0.0f,
        P_HORIZONTALLY, P_VERTICALLY, 0.0f,
        P_HORIZONTALLY, -P_VERTICALLY, 0.0f,
        -P_HORIZONTALLY, -P_VERTICALLY, 0.0f
    };
public:
    Game(int width, int height);
    ~Game();
};