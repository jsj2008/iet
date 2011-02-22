#include "ContactResolver.hpp"

namespace dynamx
{
	ContactResolver::ContactResolver()
	{
	}

	ContactResolver::~ContactResolver()
	{
	}

	void ContactResolver::PrepareContacts(vector<Contact>& contacts,
			real timeStep) const
	{
		// Generate contact velocity and axis information.
		vector<Contact>::const_iterator contact;
		for(contact = contacts.begin(); contact != contacts.end(); contact++)
		{
			// Calculate the internal contact data (inertia, basis, etc).
			(*contact).GetA()->CalculateInternals();
			(*contact).GetB()->CalculateInternals();
		}
	}

	void ContactResolver::ResolveContacts(vector<Contact>& contacts,
			real timeStep) const
	{
		// Prepare the contacts for processing
		PrepareContacts(contacts, timeStep);
		
		real epsilon = 0.05;
		HandleCollisions(contacts, epsilon);
	}

	bool ContactResolver::IsColliding(Contact& contact) const
	{
		shared_ptr<RigidBody> a = contact.GetA();
		shared_ptr<RigidBody> b = contact.GetB();
		Vector3 n = contact.GetCollisionNormal();
		Point3 p = contact.GetClosestPoint();
		Vector3 pVec = contact.GetClosestPoint().ToVector3();
		Vector3 padot = GetPointVel(*a, pVec);
		Vector3 pbdot = GetPointVel(*b, pVec);

		real vRel = n.DotProduct( padot.Subtract(pbdot) );

		if(vRel > THRESHOLD)
		{
			return false;
		}
		else if(vRel > -THRESHOLD)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	void ContactResolver::HandleCollisions(vector<Contact>& contacts,
			real epsilon) const
	{
		bool hadCollision;
		do
		{
			hadCollision = false;
			vector<Contact>::iterator contact;
			for(contact = contacts.begin(); contact != contacts.end(); contact++)
			{
				if(IsColliding((*contact)))
				{
					// Calculate the internal contact data (inertia, basis, etc).
					HandleCollision(*contact, epsilon);

					hadCollision = true;

					//odediscontinuous here?
				}
			}
		}
		while(hadCollision);
	}

	/* Return the velocity of a point on a rigid body */
	//@ref : Baraff SIGGRAPH 2001 COURSE NOTES G47
	Vector3 ContactResolver::GetPointVel(const RigidBody& body, const Vector3& p) const
	{
		return body.GetV().Add(body.GetOmega().CrossProduct(p.Subtract(body.GetPos())));
	}

	//@ref : Baraff SIGGRAPH 2001 COURSE NOTES G47
	void ContactResolver::HandleCollision(Contact& contact,
			real epsilon) const
	{
		shared_ptr<RigidBody>  a = contact.GetA();
		shared_ptr<RigidBody> b = contact.GetB();
		Vector3 n = contact.GetCollisionNormal();
		Point3 p = contact.GetClosestPoint();
		Vector3 pVec = contact.GetClosestPoint().ToVector3();
		Vector3 padot = GetPointVel(*a, pVec);
		Vector3 pbdot = GetPointVel(*b, pVec);
		Vector3 ra = pVec.Subtract(a->GetPos());
		Vector3 rb = pVec.Subtract(b->GetPos());
		real vRel = n.DotProduct( padot.Subtract(pbdot) );
		real numerator = -(1+epsilon) * vRel;

		//Denominator calc
		real t1 = a->GetInverseMass();
		real t2 = b->GetInverseMass();
		Vector3 raCrossNRel;
		a->GetInverseInertiaTensor().Multiply(ra.CrossProduct(n), &raCrossNRel);
		real t3 = n.DotProduct( raCrossNRel.CrossProduct(ra) );

		Vector3 rbCrossNRel;
		a->GetInverseInertiaTensor().Multiply(rb.CrossProduct(n), &rbCrossNRel);
		real t4 = n.DotProduct( rbCrossNRel.CrossProduct(rb) );

		//Impulse magnitude calculation
		real j = numerator / (t1 + t2 + t3 + t4);
		Vector3 force = n.Multiply(j);

		a->SetLinearVel(a->GetLinearVel().Add(force));
		b->SetLinearVel(b->GetLinearVel().Subtract(force));

		a->SetAngularVel(ra.CrossProduct(force));
		b->SetAngularVel(rb.CrossProduct(force));

		//Recompute v and omega
		a->SetV(a->GetLinearVel().Multiply(a->GetInverseMass()));
		b->SetV(b->GetLinearVel().Multiply(b->GetInverseMass()));

		Vector3 aOmega;
		a->GetInverseInertiaTensor().Multiply(a->GetAngularVel(), &aOmega);
		a->SetOmega(aOmega);

		Vector3 bOmega;
		b->GetInverseInertiaTensor().Multiply(b->GetAngularVel(), &bOmega);
		b->SetOmega(bOmega);
	}

}
