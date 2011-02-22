#include "FpsTimer.hpp"

FpsTimer::FpsTimer()
{
}

FpsTimer::~FpsTimer()
{
}

void FpsTimer::Start()
{
    m_IsStarted = true;
    m_IsPaused = false;
    m_StartTicks = SDL_GetTicks();
}
    
void FpsTimer::Stop()
{       
    m_IsStarted = false;
    m_IsPaused = false;
}
    
void FpsTimer::Pause()
{
    if(m_IsStarted &&
            (!m_IsPaused))
    {
        m_IsPaused = true;
        m_PausedTicks = SDL_GetTicks() - m_StartTicks;
    }
}

void FpsTimer::UnPause()
{
}

int FpsTimer::GetTicks()
{
    if(m_IsStarted)
    {
        if(m_IsPaused)
        {
            return m_PausedTicks;
        }
        else
        {
            return SDL_GetTicks() - m_StartTicks;
        }
    }
    else
    {
        return 0;
    }
}

