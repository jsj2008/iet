#ifndef  JFVERTEX_H
#define  JFVERTEX_H

#include <vector>
#include <map>

#include <jfCore/jfCore.hpp>
#include <jfAlgebra/jfPoint3.hpp>

using namespace std;

/*
 * =====================================================================================
 *        Class: jfVertex
 *  Description:
 * =====================================================================================
 */
class jfVertex
{
	public:
		jfVertex();

		virtual ~jfVertex();

		void addFaceId(jfFaceId val)
		{
			m_FaceIds.push_back(val);
		}

		vector<jfFaceId> getFaceIds() const
		{
			return m_FaceIds;
		}

		void setPos(const jfPoint3& val)
		{
			m_Pos = val;
		}

		jfPoint3 getPos() const
		{
			return m_Pos;
		}

		jfVertexId getId() const
		{
			return m_Id;
		}

		void setId(jfVertexId val)
		{
			m_Id = val;
		}

	protected:
		jfVertexId m_Id;
		jfPoint3 m_Pos;
		vector<jfFaceId> m_FaceIds;

	private:
};


#endif   // JFVERTEX_H
