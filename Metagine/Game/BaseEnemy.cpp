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

#include "BaseEnemy.h"
#include "BaseExplosion.h"
#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"
#include "../Engine/InputTask.h"
#include "../Engine/RenderTask.h"

MBaseEnemy::MBaseEnemy( MVector2 vPosition, MGameBoard* pBoard, int iIndex, int iRow ) :
MBaseEntity(vPosition,MVector2(50.0f,0.0f),true,true,ENTITY_ENEMY_INVADER),
m_pBoard(pBoard),
m_iIndex(iIndex),
m_iRow(iRow)
{
	switch( iRow ) {
		case 0: { m_pSprite = ISpritePtr(new MSprite("Manifests/Enemy1.xml")); } break;
		case 1: { m_pSprite = ISpritePtr(new MSprite("Manifests/Enemy2.xml")); } break;
		case 2: { m_pSprite = ISpritePtr(new MSprite("Manifests/Enemy3.xml")); } break;
		case 3: { m_pSprite = ISpritePtr(new MSprite("Manifests/Enemy4.xml")); } break;
		case 4: { m_pSprite = ISpritePtr(new MSprite("Manifests/Enemy5.xml")); } break;
		case 5: { m_pSprite = ISpritePtr(new MSprite("Manifests/Enemy6.xml")); } break;
	}

	Engine::GetInstance()->Renderer()->RegisterDrawable(m_pSprite);
	m_ShotTimer.Start();
	srand(timeGetTime());
}

MBaseEnemy::~MBaseEnemy( void )
{
	Engine::GetInstance()->Renderer()->RemoveDrawable(m_pSprite);
	
	printf(" -> MBaseEnemy object deleted.\n");
}

void MBaseEnemy::UpdateLogic( float fDelta )
{
	m_pSprite->Animate(true);
	m_vPosition += ( ( m_vVelocity * (float)fDelta ) / 1000.0f );
	m_pSprite->SetPosition(m_vPosition.x,m_vPosition.y);

	//if( m_ShotTimer.GetTicks() > 5000 && ( rand() % 8 + 1 ) == 5 ) {
	for( int i = m_iRow + 1; i < INVADERS_NUM_ROWS; ++i ) {
			if( m_pBoard->GetEnemyEntity(i,m_iIndex) )
				return;
		}
	
	if( ( rand() % 1000 + 1 ) == 500 ) 
	{
		/*IEntityPtr pBullet(new MBaseProjectile(MVector2(m_vPosition.x + 15,m_vPosition.y + 35),
			MVector2(0.0f,400.0f),2));
			
		Engine::GetInstance()->EntityManager()->RegisterEntity(pBullet);
		Engine::GetInstance()->AudioTask()->PlaySound("Shoot2.wav");*/

		IEntityPtr pBullet(new MBaseProjectile(MVector2(m_vPosition.x + 15,m_vPosition.y + 35),
			MVector2(0.0f,400.0f),2));
		Engine::GetInstance()->EntityManager()->RegisterEntity(pBullet);
		Engine::GetInstance()->AudioTask()->PlaySound("Shoot2.wav");
	}
		
		//m_ShotTimer.Start();
}

void MBaseEnemy::CollisionEvent( IEntity* pEntity, const int iType, const float fDelta )
{
	if( iType == COLLISION_ENTITY ) {
		if( pEntity->GetType() != ENTITY_ENEMY_INVADER && pEntity->GetType() != ENTITY_ENEMY_PROJECTILE )
			m_bExpired = true;
	}

	m_pBoard->CollisionEvent(iType,m_iIndex,m_iRow);
}


void MBaseEnemy::VKill( void )
{
	IEntityPtr pExplosion(new MBaseExplosion(
		MVector2(m_vPosition.x + 5,m_vPosition.y),m_vVelocity));
	
	Engine::GetInstance()->EntityManager()->RegisterEntity(pExplosion);
	Engine::GetInstance()->AudioTask()->PlaySound("Explosion1.wav");
	Engine::GetInstance()->Renderer()->RemoveDrawable(m_pSprite);
}