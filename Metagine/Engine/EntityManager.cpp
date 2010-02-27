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

#include "EntityManager.h"

MEntityManager::MEntityManager( void )
{
	printf(" -> MEntityManager object created.\n");
}

MEntityManager::~MEntityManager( void )
{
	printf(" -> MEntityManager object destructed.\n");
}

void MEntityManager::VInit( void )
{
}

void MEntityManager::VKill( void )
{
}

void MEntityManager::VFrame( const int iDelta )
{
	vector<IEntityPtr>::iterator it;
	for( it = m_Entities.begin(); it < m_Entities.end(); ++it ) {
		if( (*it)->GetActive() )
			(*it)->UpdateLogic(iDelta);
	}

	m_CollisionResolver.Resolve(m_Entities,iDelta);
}

void MEntityManager::RegisterEntity( IEntityPtr pEntity )
{
	if( !pEntity ) {
		// Error msg here
		//return false;
	}

	m_Entities.push_back(pEntity);
	printf(" -> Registered entity (0x%X) with logic queue.\n",pEntity.get());
}

void MEntityManager::RemoveEntity( IEntityPtr pEntity )
{
	vector<IEntityPtr>::iterator it = m_Entities.begin();
	while( it != m_Entities.end() ) {
		if( (*it) && ((*it) == pEntity) ) {
			printf(" -> Removing object (0x%X) from entity queue.\n",pEntity);
			(*it).reset();
			it = m_Entities.erase(it);
		} else ++it;
	}
}

