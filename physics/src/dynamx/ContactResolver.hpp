#ifndef  CONTACTRESOLVER_H
#define  CONTACTRESOLVER_H

#include <vector>

#include <dynamx/Vector3.hpp>
#include <dynamx/RigidBody.hpp>
#include <dynamx/Contact.hpp>
#include <dynamx/Core.hpp>

using namespace std;

namespace dynamx
{
	const real THRESHOLD = 0.1;

	/*
	 * =====================================================================================
	 *        Class: ContactResolver
	 *  Description:
	 * =====================================================================================
	 */
	class ContactResolver
	{
		public:
			ContactResolver();

			virtual ~ContactResolver();

			void PrepareContacts(vector<ContactPtr>& contacts,
					real timeStep) const;

			void ResolveContacts(vector<ContactPtr>& contacts,
					real timeStep) const;

			void HandleCollisions(vector<ContactPtr>& contacts,
					real epsilon) const;

			void HandleCollision(ContactPtr& contact,
					real epsilon) const;

			bool IsColliding(ContactPtr& contact) const;

			Vector3 GetPointVel(const RigidBody& body, const Vector3& p) const;
			
		protected:
		private:
	};
}

#endif   // CONTACTRESOLVER_H
