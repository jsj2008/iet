#ifndef  PLANE_H
#define  PLANE_H

#include <dynamx/Vector3.hpp>
#include <dynamx/Point3.hpp>

namespace dynamx
{
	class Plane
	{
		public:
			Plane();

			virtual ~Plane();

			/*----------------------
			 *  Getters and Setters
			 *----------------------*/
			Point3 GetPos() const { return m_Pos; }

			void SetPos(const Point3& val) { m_Pos = val; }

			void SetNormal(const Vector3& val) { m_Normal = val; }

			Vector3 GetNormal() const { return m_Normal; }

		protected:
			Point3 m_Pos;
			Vector3 m_Normal;
		private:
	};
}

#endif   // PLANE_H
