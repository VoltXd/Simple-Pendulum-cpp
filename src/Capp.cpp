#include <chrono>

#include "Capp.hpp"

Capp::Capp()
{
    m_window = nullptr;
    m_renderer = nullptr;
    m_screenWidth = 800;
    m_screenHeigth = 600;
    m_isRunning = true;

    m_previousTimePoint = std::chrono::high_resolution_clock::now();

    m_pendulum1.initialisePendulum(1, 7860, 2, M_PI/2);
    m_pendulum2.initialisePendulum(2, 7860, 2, -M_PI/4);
}

int Capp::run()
{
    int status = initialise();
    if (status != 0)
        return status;
 
    while (m_isRunning)
    {
        input();
        update();
        render();
    }

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();

    return 0;
}

int Capp::initialise()
{
    int status = 0;

    status += SDL_Init(SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_VIDEO);
    if (status != 0)
        return status;

    m_window = SDL_CreateWindow("Simple Pendulum", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_screenWidth, m_screenHeigth, SDL_WINDOW_SHOWN);
    if (m_window == nullptr)
        return -1;
    
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (m_renderer == nullptr)
        return -1;

    return status;
}

void Capp::input()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                m_isRunning = false;
                break;
        }
    }
}

void Capp::update()
{
    auto timePoint = std::chrono::high_resolution_clock::now();
    unsigned long long elapsedTimeMicroSeconds = std::chrono::duration_cast<std::chrono::microseconds>(timePoint - m_previousTimePoint).count();
    m_previousTimePoint = timePoint;

    m_pendulum1.calculateNextPoint(elapsedTimeMicroSeconds * 1e-6);
    m_pendulum2.calculateNextPoint(elapsedTimeMicroSeconds * 1e-6);
}

void Capp::render()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    m_pendulum1.SDL_RenderDrawPendulum(m_renderer, m_screenWidth, m_screenHeigth);  
    m_pendulum2.SDL_RenderDrawPendulum(m_renderer, m_screenWidth, m_screenHeigth);  

    SDL_RenderPresent(m_renderer);
}