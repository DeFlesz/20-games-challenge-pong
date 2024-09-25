#include <glm/vec2.hpp>

class Paddle
{
private:
    /* data */
    int width;
    int height;
    
    int x_pos;
    int y_pos;
public:
    Paddle(int width = 80, int height = 200);
    ~Paddle();

    int GetWidth();
    int GetHeight();
};