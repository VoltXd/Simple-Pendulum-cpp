#pragma once

#include "SDL.h"

class Pendulum
{
    public:
    Pendulum();
    
    void initialisePendulum(double mass, double density, double length, double angle_t0);
    void calculateNextPoint(double dt);

    int SDL_RenderDrawPendulum(SDL_Renderer *renderer, int screenWidth, int screenHeight);

    private:
    double m_mass;
    double m_density;
    double m_length;
    double m_angle;
    double m_angleSpeed;
    double m_positionX;
    double m_positionY;

    const double GRAVITATIONNAL_ACCELERATION = 9.80665;
};