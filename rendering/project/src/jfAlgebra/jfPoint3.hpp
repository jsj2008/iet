#ifndef  JFPOINT3_H
#define  JFPOINT3_H

#include <jfCore/jfCore.hpp>
#include <jfAlgebra/jfVector3.hpp>

/*
 * =====================================================================================
 *        Class: jfPoint3
 *  Description:
 * =====================================================================================
 */
class jfPoint3
{
	public:
		jfPoint3();

		jfPoint3(jfReal x, jfReal y, jfReal z);

		virtual ~jfPoint3();

		jfPoint3 add(const jfVector3&) const;

		void addScaledjfVector(const jfVector3& other, jfReal scale);

		jfReal calculateDistance(const jfPoint3&) const;

		void set(jfReal x, jfReal y, jfReal z) { m_X = x; m_Y = y ; m_Z = z; }

		jfVector3 toVector3() const;

		/*----------------------
		 *  Getters and Setters
		 *----------------------*/
		jfReal getX() const { return m_X; }

		void setX(jfReal val) { m_X = val; }

		jfReal getY() const { return m_Y; }

		void setY(jfReal val) { m_Y = val; }

		jfReal getZ() const { return m_Z; }

		void setZ(jfReal val) { m_Z = val; }

	protected:
		jfReal m_X, m_Y, m_Z;
};

#endif   // JFPOINT3_H
