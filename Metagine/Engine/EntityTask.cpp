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

#include "EntityTask.h"

MEntityTask::MEntityTask( void )
{
	printf(" -> MEntityTask object created.\n");
}

MEntityTask::~MEntityTask( void )
{
	printf(" -> MEntityTask object destructed.\n");
}

void MEntityTask::VInit( void )
{
	memset(&m_pEntities,0,1024);
	m_pCollisionResolver = shared_ptr<MCollisionResolver>(new MCollisionResolver());
}

void MEntityTask::VKill( void )
{
	printf(" -> MEntityTask::VKill() called.\n");
	
	vector<IEntityPtr>::iterator entity = m_Entities.begin();
	for( entity = m_Entities.begin(); entity < m_Entities.end(); ++entity ) {
		if( *entity ) {
			printf(" -> Releasing queued entity object (0x%X).\n",(*entity).get());
			entity->reset();
		}
	}

	m_Entities.clear();
	m_pCollisionResolver.reset();
}

void MEntityTask::VFrame( const float fDelta )
{
	if( m_Entities.size() == 0 )
		return;
	
	// Perform a pre-frame check and queue expired entities for deletion.
	vector<IEntityPtr>::iterator entity;
	for( entity = m_Entities.begin(); entity < m_Entities.end(); ++entity ) {
		if( (*entity)->GetExpired() ) {
			printf(" -> Entity object has expired. Scheduling for deletion (0x%X).\n",(*entity).get());
			m_ExpiredEntities.push_back((*entity));
		}
	}

	// Delete any entities that have expired during the last frame.
	if( m_ExpiredEntities.size() > 0 ) {
		for( entity = m_ExpiredEntities.begin(); entity < m_ExpiredEntities.end(); ++entity ) {
			RemoveEntity((*entity));
			(*entity).reset();
		}

		m_ExpiredEntities.clear();
	}
	
	// Advance active entities forwards one game frame and
	// create array of naked pointers for collision detection.
	int iCount = 0;
	for( entity = m_Entities.begin(); entity < m_Entities.end(); ++entity ) {
		if( (*entity)->GetActive() ) {
			(*entity)->UpdateLogic(fDelta);
			m_pEntities[iCount] = (*entity).get();
			++iCount;
		}
	}
	
	m_pCollisionResolver->Resolve(&m_pEntities[0],iCount,fDelta);
}

void MEntityTask::RegisterEntity( IEntityPtr pEntity )
{
	if( !pEntity ) {
		// Error msg here
		//return false;
	}

	m_Entities.push_back(pEntity);
	printf(" -> Registered entity (0x%X) with logic queue.\n",pEntity.get());
}

void MEntityTask::RemoveEntity( IEntityPtr pEntity )
{
	vector<IEntityPtr>::iterator entity = m_Entities.begin();
	while( entity != m_Entities.end() ) {
		if( (*entity) && ((*entity) == pEntity) ) {
			printf(" -> Removing object (0x%X) from entity queue.\n",pEntity);
			(*entity)->VKill();
			(*entity).reset();
			entity = m_Entities.erase(entity);
		} else ++entity;
	}
}

int MEntityTask::GetEntityCount( void )
{
	return (int)m_Entities.size();
}
