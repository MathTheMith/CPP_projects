#include <SDL.h>
#include <iostream>
#include <algorithm>
#include "main.hpp"

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
const int PADDLE_SPEED = 20;
const float BALL_SPEED_X = 20;
const float BALL_SPEED_Y = 15;
const int PADDLE_MARGIN = 20;
const int AI_ACTIVATION_X = 1000;

int main(int argc, char* argv[]) {
    Bar bar1, bar2;
    Ball m_ball;
    
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Erreur SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Pong SDL2",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS
    );

    if (!window) {
        std::cerr << "Erreur création fenêtre: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Erreur création renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    bar1.pos_x = PADDLE_MARGIN;
    bar1.pos_y = WINDOW_HEIGHT / 2 - bar1.lenght / 2;
    bar2.pos_x = WINDOW_WIDTH - PADDLE_MARGIN - bar2.width;
    bar2.pos_y = WINDOW_HEIGHT / 2 - bar2.lenght / 2;
    
    m_ball.pos_x = WINDOW_WIDTH / 2 - m_ball.size / 2;
    m_ball.pos_y = WINDOW_HEIGHT / 2 - m_ball.size / 2;
    
    float ball_vel_x = BALL_SPEED_X;
    float ball_vel_y = BALL_SPEED_Y;
    
    bool running = true;
    SDL_Event event;
    const Uint8* keys = SDL_GetKeyboardState(NULL);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || 
                (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                running = false;
            }
        }
        
        if (keys[SDL_SCANCODE_UP] && bar1.pos_y > PADDLE_MARGIN) {
            bar1.pos_y -= PADDLE_SPEED;
        }
        if (keys[SDL_SCANCODE_DOWN] && 
            bar1.pos_y < WINDOW_HEIGHT - bar1.lenght - PADDLE_MARGIN) {
            bar1.pos_y += PADDLE_SPEED;
        }
        
        if (m_ball.pos_x >= AI_ACTIVATION_X) {
            int paddle_center = bar2.pos_y + bar2.lenght / 2;
            int ball_center = m_ball.pos_y + m_ball.size / 2;
            
            if (ball_center > paddle_center + 10) {
                bar2.pos_y = std::min(bar2.pos_y + PADDLE_SPEED, 
                    WINDOW_HEIGHT - bar2.lenght - PADDLE_MARGIN);
            } else if (ball_center < paddle_center - 10) {
                bar2.pos_y = std::max(bar2.pos_y - PADDLE_SPEED, PADDLE_MARGIN);
            }
        }
        
        m_ball.pos_x += static_cast<int>(ball_vel_x);
        m_ball.pos_y += static_cast<int>(ball_vel_y);
        
        if (m_ball.pos_y <= 0 || m_ball.pos_y >= WINDOW_HEIGHT - m_ball.size) {
            ball_vel_y = -ball_vel_y;
            m_ball.pos_y = std::clamp(m_ball.pos_y, 0, WINDOW_HEIGHT - m_ball.size);
        }
        
        if (ball_vel_x < 0 &&
            m_ball.pos_x <= bar1.pos_x + bar1.width &&
            m_ball.pos_x >= bar1.pos_x &&
            m_ball.pos_y + m_ball.size >= bar1.pos_y &&
            m_ball.pos_y <= bar1.pos_y + bar1.lenght) {
            ball_vel_x = -ball_vel_x * 1.02f;
            ball_vel_y *= 1.02f;
            m_ball.pos_x = bar1.pos_x + bar1.width;
        }
        
        if (ball_vel_x > 0 &&
            m_ball.pos_x + m_ball.size >= bar2.pos_x &&
            m_ball.pos_x <= bar2.pos_x + bar2.width &&
            m_ball.pos_y + m_ball.size >= bar2.pos_y &&
            m_ball.pos_y <= bar2.pos_y + bar2.lenght) {
            ball_vel_x = -ball_vel_x * 1.02f;
            ball_vel_y *= 1.02f;
            m_ball.pos_x = bar2.pos_x - m_ball.size;
        }
        
        if (m_ball.pos_x < 0 || m_ball.pos_x > WINDOW_WIDTH) {
            running = false;
        }
        
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderClear(renderer);
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect rect1 = {bar1.pos_x, bar1.pos_y, bar1.width, bar1.lenght};
        SDL_Rect rect2 = {bar2.pos_x, bar2.pos_y, bar2.width, bar2.lenght};
        SDL_Rect ball = {m_ball.pos_x, m_ball.pos_y, m_ball.size, m_ball.size};
        
        SDL_RenderFillRect(renderer, &rect1);
        SDL_RenderFillRect(renderer, &rect2);
        SDL_RenderFillRect(renderer, &ball);
        
        SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}