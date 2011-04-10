#ifndef  FPSTIMER_H
#define  FPSTIMER_H

#include <SDL/SDL.h>

/*
 * =====================================================================================
 *        Class: FpsTimer
 *  Description:
 * =====================================================================================
 */
class FpsTimer
{
	public:
		FpsTimer();

		virtual ~FpsTimer();

		void Start();

        void Stop();

        void Pause();

        void UnPause();

        int GetTicks();

    protected:
        int m_StartTicks;
        int m_PausedTicks;
        bool m_IsPaused;
        bool m_IsStarted;
	
	protected:
	private:
};


#endif   // FPSTIMER_H
