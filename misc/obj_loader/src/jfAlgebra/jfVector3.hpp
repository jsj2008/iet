#ifndef  JFVECTOR3_H
#define  JFVECTOR3_H

#include <assert.h>

#include <jfCore/jfCore.hpp>

class jfPoint3;

/*
 * =====================================================================================
 *        Class: jfVector3
 *  Description:
 * =====================================================================================
 */
class jfVector3
{
	public:
		jfVector3();

		jfVector3(jfReal x, jfReal y, jfReal z);

		jfVector3(const jfPoint3& point);

		virtual ~jfVector3();

		jfVector3 add(const jfVector3& other) const;

		void addScaledVector(const jfVector3& other, jfReal scale);

		jfVector3 subtract(const jfVector3& other) const;

		jfVector3 multiply(const jfReal& scalar) const;

		jfReal dotProduct(const jfVector3& other) const;

		jfVector3 crossProduct(const jfVector3& other) const;

		jfVector3 componentProduct(const jfVector3& other) const;

		jfReal magnitude() const;

		void normalize();

		void clear();

		void set(jfReal x, jfReal y, jfReal z) { m_X = x; m_Y = y ; m_Z = z; }

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


#endif   // JFVECTOR3_H
