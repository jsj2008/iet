#include "ContactResolver.hpp"

namespace dynamx
{
	ContactResolver::ContactResolver()
	{
	}

	ContactResolver::~ContactResolver()
	{
	}

	void ContactResolver::PrepareContacts(vector<ContactPtr>& contacts,
			real timeStep) const
	{
		// Generate contact velocity and axis information.
		vector<ContactPtr>::const_iterator contact;
		for(contact = contacts.begin(); contact != contacts.end(); contact++)
		{
			// Calculate the internal contact data (inertia, basis, etc).
			(*contact)->GetA()->CalculateInternals();
			(*contact)->GetB()->CalculateInternals();
		}
	}

	void ContactResolver::ResolveContacts(vector<ContactPtr>& contacts,
			real timeStep) const
	{
		// Prepare the contacts for processing
		PrepareContacts(contacts, timeStep);
		
		real epsilon = 0.5;
		HandleCollisions(contacts, epsilon);
	}

	bool ContactResolver::IsColliding(ContactPtr& contact) const
	{
		shared_ptr<RigidBody> a = contact->GetA();
		shared_ptr<RigidBody> b = contact->GetB();
		Vector3 n = contact->GetCollisionNormal();
		Point3 p = contact->GetClosestPoint();
		Vector3 pVec = contact->GetClosestPoint().ToVector3();
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

	void ContactResolver::HandleCollisions(vector<ContactPtr>& contacts,
			real epsilon) const
	{
		bool hadCollision;
		int maxTries = 1000;
		int i = 0;
		do
		{
			i++;
			if(i>maxTries)
			{
				break;
			}
			hadCollision = false;
			vector<ContactPtr>::iterator contact;
			for(contact = contacts.begin(); contact != contacts.end(); contact++)
			{
				if(IsColliding((*contact)))
				{
					// Calculate the internal contact data (inertia, basis, etc).
					HandleCollision(*contact, epsilon);

					hadCollision = true;

//					return;

					//odediscontinuous here?
				}
			}
			cout<<"hi"<<endl;
			fflush(stdout);
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
	void ContactResolver::HandleCollision(ContactPtr& contact,
			real epsilon) const
	{
		shared_ptr<RigidBody> a = contact->GetA();
		shared_ptr<RigidBody> b = contact->GetB();
		Vector3 n = contact->GetCollisionNormal();
		Point3 p = contact->GetClosestPoint();
		Vector3 pVec = contact->GetClosestPoint().ToVector3();
		Vector3 padot = GetPointVel(*a, pVec);
		Vector3 pbdot = GetPointVel(*b, pVec);
		Vector3 ra = pVec.Subtract(a->GetPos());
		Vector3 rb = pVec.Subtract(b->GetPos());
		real vRel = n.DotProduct( padot.Subtract(pbdot) );
//		real vRel = n.DotProduct( a->GetLinearVel().Subtract(b->GetLinearVel()) );

		Vector3 kA = ra.CrossProduct(n);
		Vector3 kB = rb.CrossProduct(n);
		real numerator = -(1+epsilon) * vRel;
//		real numerator = -(1+epsilon) * vRel + (a->GetOmega().DotProduct(kA) - (b->GetOmega().DotProduct(kB))) ;

		//Denominator calc
		real t1 = a->GetInverseMass();
		real t2 = b->GetInverseMass();
		Vector3 raCrossNRel;
		a->GetInverseInertiaTensor().Multiply(ra.CrossProduct(n), &raCrossNRel);
		real t3 = n.DotProduct( raCrossNRel.CrossProduct(ra) );
	//	real t3 = kA.DotProduct( raCrossNRel );

		Vector3 rbCrossNRel;
		a->GetInverseInertiaTensor().Multiply(rb.CrossProduct(n), &rbCrossNRel);
		real t4 = n.DotProduct( rbCrossNRel.CrossProduct(rb) );
//		real t4 = kB.DotProduct( rbCrossNRel );

		//Impulse magnitude calculation
		real j = numerator / (t1 + t2 + t3 + t4);

//		j*=3; //HACK
		j*=2; //HACK

		Vector3 force = n.Multiply(j);

		/*
        Point3 ptRa(ra.GetX(), ra.GetY(), ra.GetZ());
        Point3 ptRb(rb.GetX(), rb.GetY(), rb.GetZ());

		real forcePower = 10;
		Vector3 va = ra.Multiply(forcePower);
		Vector3 vb = rb.Multiply(forcePower);
        a->AddForceAtPoint(force, Point3(va.GetX(), va.GetY(), va.GetZ()));
        b->AddForceAtPoint(force, Point3(vb.GetX(), vb.GetY(), vb.GetZ()));
		*/

		a->SetLinearMomentum(a->GetLinearMomentum().Add(force));
		b->SetLinearMomentum(b->GetLinearMomentum().Subtract(force));

		a->SetAngularMomentum(a->GetAngularMomentum().Add(kA.Multiply(j)));
		b->SetAngularMomentum(b->GetAngularMomentum().Add(kB.Multiply(j)));

		//Recompute v and omega
		a->SetV(a->GetLinearMomentum().Multiply(a->GetInverseMass()));
		b->SetV(b->GetLinearMomentum().Multiply(b->GetInverseMass()));

		Vector3 aOmega;
		a->GetInverseInertiaTensorWorld().Multiply(a->GetAngularVel(), &aOmega);
		a->SetOmega(a->GetOmega().Add(aOmega));

		Vector3 bOmega;
		b->GetInverseInertiaTensorWorld().Multiply(b->GetAngularVel(), &bOmega);
		b->SetOmega(b->GetOmega().Add(bOmega));

		/*
		a->SetLinearVel(a->GetLinearVel().Add(force));
		b->SetLinearVel(b->GetLinearVel().Subtract(force));

		a->SetAngularVel(ra.CrossProduct(force));
		b->SetAngularVel(rb.CrossProduct(force));

		//Recompute v and omega
		a->SetV(a->GetLinearVel().Multiply(a->GetInverseMass()));
		b->SetV(b->GetLinearVel().Multiply(b->GetInverseMass()));

		Vector3 aOmega;
		a->GetInverseInertiaTensorWorld().Multiply(a->GetAngularVel(), &aOmega);
		a->SetOmega(aOmega);

		Vector3 bOmega;
		b->GetInverseInertiaTensorWorld().Multiply(b->GetAngularVel(), &bOmega);
		b->SetOmega(bOmega);
		*/
	}

}
