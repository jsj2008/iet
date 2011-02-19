#ifndef  EDGE_H
#define  EDGE_H

#include <dynamx/Point3.hpp>
#include <dynamx/Vector3.hpp>

namespace dynamx
{
	/*
	 * =====================================================================================
	 *        Class: Edge
	 *  Description:
	 * =====================================================================================
	 */
	class Edge
	{
		public:
			Edge();

			virtual ~Edge();


			Point3 GetOrigin() const
			{
				return m_Origin;
			}

			void SetOrigin(const Point3& val)
			{
				m_Origin = val;
			}

			real GetLength() const
			{
				return m_Length;
			}

			void SetLength(const real val)
			{
				m_Length = val;
			}

			Vector3 GetDirection() const
			{
				return m_Direction;
			}

			void SetDirection(const Vector3& val)
			{
				m_Direction = val;
			}

		protected:
			Point3 m_Origin;
			real m_Length;
			Vector3 m_Direction;
		private:
	};

}

#endif   // EDGE_H
