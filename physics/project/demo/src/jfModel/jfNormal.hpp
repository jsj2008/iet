#ifndef  JFNORMAL_H
#define  JFNORMAL_H

#include <jfCore/jfCore.hpp>
#include <jfAlgebra/jfVector3.hpp>

/*
 * =====================================================================================
 *        Class: jfNormal
 *  Description:
 * =====================================================================================
 */
class jfNormal
{
	public:
		jfNormal();

		virtual ~jfNormal();

		void set(jfReal x, jfReal y, jfReal z)
		{
			m_Normal.set(x,y,z);
		}

		jfVector3 getVector()
		{
			return m_Normal;
		}

		jfNormalId getId() const
		{
			return m_Id;
		}

		void setId(jfNormalId val)
		{
			m_Id = val;
		}

	protected:
		jfNormalId m_Id;
		jfVector3 m_Normal;

	private:
};


#endif   // JFNORMAL_H
