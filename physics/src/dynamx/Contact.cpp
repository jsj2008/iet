#include "Contact.hpp"

namespace dynamx
{
	Contact::Contact()
		:
			m_ClosestPoint(new Point3()),
			m_CollisionNormal(new Vector3())
	{
	}

	Contact::~Contact()
	{
		delete m_ClosestPoint;
		delete m_CollisionNormal;
	}

}
