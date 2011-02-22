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
	const real THRESHOLD = 0.01;

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

			void PrepareContacts(vector<Contact>& contacts,
					real timeStep) const;

			void ResolveContacts(vector<Contact>& contacts,
					real timeStep) const;

			void HandleCollisions(vector<Contact>& contacts,
					real epsilon) const;

			void HandleCollision(Contact& contact,
					real epsilon) const;

			bool IsColliding(Contact& contact) const;

			Vector3 GetPointVel(const RigidBody& body, const Vector3& p) const;
			
		protected:
		private:
	};
}

#endif   // CONTACTRESOLVER_H
