#ifndef  JFVERTEXTEXTURE_H
#define  JFVERTEXTEXTURE_H

#include <jfCore/jfCore.hpp>

/*
 * =====================================================================================
 *        Class: jfVertexTexture
 *  Description:
 * =====================================================================================
 */
class jfVertexTexture
{
	public:
		jfVertexTexture();

		virtual ~jfVertexTexture();


		jfReal getU() const
		{
			return m_U;
		}

		void setU(jfReal val)
		{
			m_U = val;
		}

		jfReal getV() const
		{
			return m_V;
		}

		void setV(jfReal val)
		{
			m_V = val;
		}

		jfVertexTextureId getId() const
		{
			return m_Id;
		}

		void setId(jfVertexTextureId val)
		{
			m_Id = val;
		}
		
	protected:
		jfReal m_U, m_V;
		jfVertexTextureId m_Id;

	private:
};


#endif   // JFVERTEXTEXTURE_H
