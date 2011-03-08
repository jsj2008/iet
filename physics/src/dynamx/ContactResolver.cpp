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
		
		real epsilon = 0.3;
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
		int maxTries = 100;
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

					cout<<"Collision"<<endl;

//					return;

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
		//return body.GetV().Add(body.GetOmega().CrossProduct(p.Subtract(body.GetPos())));
		return body.GetLinearVel().Add(body.GetAngularVel().CrossProduct(p.Subtract(body.GetPos())));
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
		Vector3 rA = pVec.Subtract(a->GetPos());
		Vector3 rB = pVec.Subtract(b->GetPos());

		Vector3 padot = GetPointVel(*a, pVec);
		Vector3 pbdot = GetPointVel(*b, pVec);
		real vRel = n.DotProduct( padot.Subtract(pbdot) );

		cout<<"vRel is : "<<vRel<<endl;
		fflush(stdout);

		Vector3 kA = rA.CrossProduct(n);
		Vector3 kB = rB.CrossProduct(n);

		Vector3 uA = a->GetInverseInertiaTensorWorld().Multiply(kA);
		Vector3 uB = b->GetInverseInertiaTensorWorld().Multiply(kB);

		real numerator = -(1+epsilon) * vRel;
/*
		real numerator = -(1+epsilon) * 
			(n.DotProduct(a->GetLinearVel().Subtract(b->GetLinearVel()))) 
			 + a->GetAngularVel().DotProduct(kA)
			 - b->GetAngularVel().DotProduct(kB);
			 */

		//Denominator calc
		real t1 = a->GetInverseMass();
		real t2 = b->GetInverseMass();
		Vector3 rACrossNRel;
		a->GetInverseInertiaTensorWorld().Multiply(rA.CrossProduct(n), &rACrossNRel);
		real t3 = n.DotProduct( rACrossNRel.CrossProduct(rA) );
		//real t3 = kA.DotProduct( rACrossNRel );
		//real t3 = kA.DotProduct(uA);

		Vector3 rBCrossNRel;
		a->GetInverseInertiaTensorWorld().Multiply(rB.CrossProduct(n), &rBCrossNRel);
		real t4 = n.DotProduct( rBCrossNRel.CrossProduct(rB) );
//		real t4 = kB.DotProduct( rBCrossNRel );
//		real t4 = kB.DotProduct(uB);

		//Impulse magnitude calculation
		real j = numerator / (t1 + t2 + t3 + t4);
		//real j = numerator / (t1 + t3);
//		real j = numerator / (t2 + t4);
//		real j = numerator / (t1 + t3);

//		j*=3; //HACK
//		j*=2; //HACK

		Vector3 force = n.Multiply(j);

		cout<<"j is : "<<j<<endl;
		cout<<"force is : "<<force<<endl;
		cout<<"numerator is : "<<numerator<<endl;
		cout<<"denomenator is : "<<(t1+t3)<<endl;

		Point3 rAPoint(rA.GetX(), rA.GetY(), rA.GetZ());
		Point3 rBPoint(rB.GetX(), rB.GetY(), rB.GetZ());

		a->SetLinearMomentum(a->GetLinearMomentum().Add(force));
		b->SetLinearMomentum(b->GetLinearMomentum().Subtract(force));

		a->SetAngularMomentum(a->GetAngularMomentum().Add(rA.CrossProduct(force)));
		b->SetAngularMomentum(b->GetAngularMomentum().Subtract(rB.CrossProduct(force)));

		a->SetLinearVel(a->GetLinearMomentum().Multiply(a->GetInverseMass()));
		b->SetLinearVel(b->GetLinearMomentum().Multiply(b->GetInverseMass()));

		a->SetAngularVel(a->GetInverseInertiaTensorWorld().Multiply(a->GetAngularMomentum()));
		b->SetAngularVel(b->GetInverseInertiaTensorWorld().Multiply(b->GetAngularMomentum()));

//		a->SetAngularVel(a->GetAngularVel().Add(uA.DotProduct(force)));
//		b->SetAngularVel(b->GetAngularVel().Add(uB.DotProduct(force)));

		/*
		a->SetLinearMomentum(a->GetLinearMomentum().Add(force));
//		a->SetLinearMomentum((force));
		b->SetLinearMomentum(b->GetLinearMomentum().Subtract(force));

		a->SetAngularMomentum(a->GetAngularMomentum().Add(rA.CrossProduct(force)));
//		a->SetAngularMomentum((rA.CrossProduct(force)));
		b->SetAngularMomentum(b->GetAngularMomentum().Subtract(rB.CrossProduct(force)));

		//Recompute aux vars
		a->SetLinearVel(a->GetLinearMomentum().Multiply(a->GetInverseMass()));
//		a->SetLinearVel(a->GetLinearVel().Add(a->GetLinearMomentum().Multiply(a->GetInverseMass())));
		b->SetLinearVel(b->GetLinearMomentum().Multiply(b->GetInverseMass()));
//		a->SetAngularVel(a->GetInverseInertiaTensorWorld().Multiply(a->GetLinearMomentum()));
//		a->SetAngularVel(a->GetAngularVel().Add(a->GetInverseInertiaTensorWorld().Multiply(a->GetLinearMomentum())));

		a->SetAngularVel(a->GetAngularVel().Add(uA.DotProduct(force)));
		//a->SetAngularVel(Vector3().Add(uA.DotProduct(force)));

//		b->SetAngularVel(b->GetInverseInertiaTensorWorld().Multiply(b->GetLinearMomentum()));
//		b->SetAngularVel(b->GetAngularVel().Add(b->GetInverseInertiaTensorWorld().Multiply(b->GetLinearMomentum())));
		b->SetAngularVel(b->GetAngularVel().Add(uB.DotProduct(force)));

//		a->AddForceAtBodyPoint(force, Point3(0,0,0));
//		b->AddForceAtBodyPoint(force, Point3(0,0,0));

//		a->AddForceAtPoint(force, p);
//		b->AddForceAtPoint(force, p);

//		a->Integrate(0.4);
		//real timestep = 1.0f / 15.0f; //TODO : Adaptive timestep.
//		real timestep = 0.4; //TODO : Adaptive timestep.
		*/
/*
		a->SetPos(a->GetPos().Add(a->GetLinearVel().Multiply(timestep)));

		//Quaternion qdot = a->GetOrientation();
		Quaternion qdot;
	   	//qdot.AddScaledVector(a->GetAngularVel(), 1.0);
	   	qdot.AddScaledVector(a->GetAngularVel(), -timestep);
		a->SetOrientation(qdot);
		*/

		/*
		//Apply impulse
		a->SetForceAccum(a->GetForceAccum().Add(force));
		b->SetForceAccum(b->GetForceAccum().Subtract(force));
		a->SetTorqueAccum(a->GetTorqueAccum().Add(rA.CrossProduct(force)));
		b->SetTorqueAccum(b->GetTorqueAccum().Add(rB.CrossProduct(force)));
		*/

		/*
		//Recompute aux variables
		a->SetLinearVel(a->GetForceAccum().Multiply(a->GetInverseMass()));
		b->SetLinearVel(b->GetForceAccum().Multiply(b->GetInverseMass()));

		a->SetAngularVel(a->GetInverseInertiaTensorWorld().Multiply(a->GetTorqueAccum()));
		b->SetAngularVel(b->GetInverseInertiaTensorWorld().Multiply(b->GetTorqueAccum()));
		*/

		//a->AddForceAtBodyPoint(force, Point3(0,0,0));
		//b->AddForceAtBodyPoint(force, Point3(0,0,0));

		//a->AddForceAtPoint(force, rAPoint);
		//b->AddForceAtPoint(force, rBPoint);

//		a->ClearAccumulators();
//		b->ClearAccumulators();
/*
		a->SetLinearVel(Vector3(0,0,0));
		b->SetLinearVel(Vector3(0,0,0));

		a->SetAngularVel(Vector3(0,0,0));
		b->SetAngularVel(Vector3(0,0,0));

		a->AddForceAtBodyPoint(force, Point3(0,0,0));
		b->AddForceAtBodyPoint(force, Point3(0,0,0));

		//a->AddForceAtPoint(force, rAPoint);
		//b->AddForceAtPoint(force, rBPoint);
		
		a->AddForceAtPoint(force, p);
		b->AddForceAtPoint(force, p);

//		b->SetAngularVel(b->GetInverseInertiaTensorWorld().Multiply(rB.CrossProduct(force)));

//		a->IntegrAte(0.0001);
//		b->IntegrAte(0.0001);
*/

		//Recompute v and omega
		/*
		a->SetV(a->GetLinearVel().Multiply(a->GetInverseMass()));
		b->SetV(b->GetLinearVel().Multiply(b->GetInverseMass()));

		Vector3 aOmega;
		a->GetInverseInertiaTensorWorld().Multiply(a->GetAngularVel(), &aOmega);
		a->SetOmega(aOmega);

		Vector3 bOmega;
		b->GetInverseInertiaTensorWorld().Multiply(b->GetAngularVel(), &bOmega);
		b->SetOmega(bOmega);
		*/


		/*
		a->SetLinearVel(a->GetLinearVel().Add(force));
		b->SetLinearVel(b->GetLinearVel().Subtract(force));

		a->SetAngularVel(rA.CrossProduct(force));
		b->SetAngularVel(rB.CrossProduct(force));

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
