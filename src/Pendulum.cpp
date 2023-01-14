#include <cmath>
#include <iostream>

#include "Pendulum.hpp"
#include "SDL.h"
#include "SDL_Circle.hpp"

Pendulum::Pendulum()
{
    m_mass = 0;
    m_density = 0;
    m_length = 0;
    m_angle = 0;
    m_angleSpeed = 0;
    m_positionX = 0;
    m_positionY = 0;
}

void Pendulum::initialisePendulum(double mass, double density, double length, double angle_t0)
{
    m_mass = mass;
    m_density = density;
    m_length = length;
    m_angle = angle_t0;

    m_positionX = m_length * sin(m_angle);
    m_positionY = -m_length * cos(m_angle);
}

void Pendulum::calculateNextPoint(double dt)
{
    static const double angularSpeedSquared = GRAVITATIONNAL_ACCELERATION / m_length;
    
    double angleAcceleration = - angularSpeedSquared * sin(m_angle);
    m_angleSpeed += angleAcceleration * dt;
    m_angle += m_angleSpeed * dt;

    m_positionX = m_length * sin(m_angle);
    m_positionY = -m_length * cos(m_angle);
}

int Pendulum::SDL_RenderDrawPendulum(SDL_Renderer *renderer, int screenWidth, int screenHeight)
{
    int status = 0;

    int screenSize = std::min<int>(screenWidth, screenHeight); 

    // Draw string
    status += SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int x1 = screenWidth / 2;
    int y1 = screenHeight / 12;

    int x2 = (m_positionX / m_length) * screenSize / 2.2 + x1;
    int y2 = -(m_positionY / m_length) * screenSize / 2.2 + y1;

    status += SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

    // Draw pendulum
    status += SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    static const double radius = (std::pow<double, double>(3.0 * m_mass / 4 / M_PI / m_density, 1.0/3) / m_length) * screenSize;
    status += SDL_RenderFillCircle(renderer, x2, y2, (int)radius);

    return status;
}