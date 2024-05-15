#include "pyramid.h"
#include "Renderer3D.h"
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <cmath> // Include the cmath library for trigonometric functions

// Creates an array of points
std::vector<Point3D> points{
    Point3D{ 1, 0, 0 },
    Point3D{ 0, 2, 0 },
    Point3D{ 2, 2, 0 },
    Point3D{ 0, 4, 0 },
    Point3D{ 2, 4, 0 },
};

// Creates an array of edges (This holds indices referencing the points array)
std::vector<Edge> edges{
    Edge{ 0, 1 },
    Edge{ 0, 2 },
    Edge{ 0, 3 },
    Edge{ 0, 4 },
    Edge{ 1, 2 },
    Edge{ 1, 3 },
    Edge{ 3, 4 },
    Edge{ 4, 2 },
};

// Default C++ function
int main(int argc, char* argv[])
{
    // Creating a window and a renderer
    SDL_Window* window;
    SDL_Renderer* renderer;

    // Creates a centered window with 960 width and 540 height
    window = SDL_CreateWindow("Pyramid Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;

    // Creating an instance of the Renderer3D class
    Renderer3D render3D(window, renderer, points, edges);

    // Variables for animation
    float scale = 1.0f;
    float scaleSpeed = 0.005f; // Adjust this value to control the speed of the pulse
    bool increasing = true;

    while (running)
    {
        // If the quit button is pressed, the loop breaks
        if (SDL_QuitRequested()) { running = false; break; }

        // Update scale for animation
        if (increasing) {
            scale += scaleSpeed;
            if (scale >= 1.2f) // Set a maximum scale
                increasing = false;
        } else {
            scale -= scaleSpeed;
            if (scale <= 0.8f) // Set a minimum scale
                increasing = true;
        }

        // Scale the coordinates of the points
        for (int i = 0; i < points.size(); ++i) {
            points[i].x *= scale;
            points[i].y *= scale;
            points[i].z *= scale;
        }

        // Calls the function created in the Renderer3D class (render3D is an instance of the class defined above)
        render3D.render();
    }

    return 0;
}
