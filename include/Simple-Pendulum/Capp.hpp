#pragma once

#include <chrono>

#include "SDL.h"
#include "Pendulum.hpp"

class Capp
{
    public:
    Capp();
    int run();

    private:
    int initialise();
    void input();
    void update();
    void render();

    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    int m_screenWidth;
    int m_screenHeigth;
    bool m_isRunning;

    Pendulum m_pendulum1;
    Pendulum m_pendulum2;

    std::chrono::high_resolution_clock::time_point m_previousTimePoint;
};