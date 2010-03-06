// This file is part of Metagine.
// 
// Metagine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Metagine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Metagine.  If not, see <http://www.gnu.org/licenses/>.

#ifndef _COLLISIONRESOLVER_H_
#define _COLLISIONRESOLVER_H_

#include "../Public/Public.h"
#include "../Public/BaseTypes.h"
#include "../Public/Interfaces.h"

/// Fix me.
class MCollisionResolver : public ICollisionResolver, public noncopyable
{
public:

	/// Default constructor.
	MCollisionResolver( void );
	~MCollisionResolver( void );

	void VInit( void );
	void VFrame( const int iDelta );
	void VKill( void );

	void ProcessEntityPairs( void );
	void DeterminePartition( IEntity* pEntity );
	bool CheckScreenBoundary( IEntity* pEntity );
	void Resolve( IEntity** pEntities, int iCount, float fDelta );
	int GetEntitiesInPartition( const int iPartition );
	bool RectangleIntersects( float x1, float y1, float x2, float y2, int w1, int h1, int w2, int h2 );

private:

	vector<IEntity*> m_Partitions[4];
	vector<pair<IEntity*,IEntity*>> m_EntityPairs;
	float m_fDelta;
	int m_iLastSize[4];
};

//typedef MSingleton<MCollisionResolver> CollisionResolver;

#endif // _COLLISIONRESOLVER_H_