#ifndef  JFWINDOW_H
#define  JFWINDOW_H

#include <jfCore/jfCore.hpp>

/*
 * =====================================================================================
 *        Class: jfWindow
 *  Description:
 * =====================================================================================
 */
class jfWindow
{
	public:
		jfWindow(jfUint32 width, jfUint32 height,  jfString title);

		virtual ~jfWindow();

		virtual void init() = 0;

		virtual void toggleFullscreen() = 0;

		jfUint32 GetHeight() const
		{
			return m_Height;
		}

		void SetHeight(const jfUint32& val)
		{
			m_Height = val;
		}

		jfUint32 GetWidth() const
		{
			return m_Width;
		}

		void SetWidth(const jfUint32& val)
		{
			m_Width = val;
		}

	protected:
		jfUint32 m_Width;
		jfUint32 m_Height;
		jfString m_Title;

	private:
};


#endif   // JFWINDOW_H
