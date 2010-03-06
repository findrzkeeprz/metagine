#include "BaseEnemy.h"
#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"
#include "../Engine/InputTask.h"
#include "../Engine/RenderTask.h"

MBaseEnemy::MBaseEnemy( float x, float y, MGameBoard* pBoard, int iIndex, int iRow ) :
m_bActive(true),
m_bExpired(false),
m_pBoard(pBoard),
m_iIndex(iIndex),
m_iRow(iRow)
{
	switch( iRow ) {
		case 0: { m_TestSprite = ISpritePtr(new MSprite("Enemy1.xml")); } break;
		case 1: { m_TestSprite = ISpritePtr(new MSprite("Enemy2.xml")); } break;
		case 2: { m_TestSprite = ISpritePtr(new MSprite("Enemy3.xml")); } break;
		case 3: { m_TestSprite = ISpritePtr(new MSprite("Enemy4.xml")); } break;
		case 4: { m_TestSprite = ISpritePtr(new MSprite("Enemy5.xml")); } break;
		case 5: { m_TestSprite = ISpritePtr(new MSprite("Enemy6.xml")); } break;
	}

	Engine::GetInstance()->Renderer()->RegisterDrawable(m_TestSprite);
	m_vPosition.x = x;
	m_vPosition.y = y;
	m_vVelocity.x = 50.0f;

	m_ShotTimer.Start();
	srand(timeGetTime());
}

MBaseEnemy::~MBaseEnemy( void )
{
	Engine::GetInstance()->Renderer()->RemoveDrawable(m_TestSprite);
	
	printf(" -> MBaseEnemy object deleted.\n");
}

void MBaseEnemy::UpdateLogic( float fDelta )
{
	//m_TestSprite->Animate(true);
	m_vPosition += ( ( m_vVelocity * (float)fDelta ) / 1000.0f );
	m_TestSprite->SetPosition(m_vPosition.x,m_vPosition.y);

	//if( m_ShotTimer.GetTicks() > 5000 && ( rand() % 8 + 1 ) == 5 ) {
	/*if( ( rand() % 1000 + 1 ) == 500 ) {
		if( m_iRow == INVADERS_NUM_ROWS - 1 ) {
			IEntityPtr pBullet(new MBaseProjectile(2,m_vPosition.x + 15,m_vPosition.y + 35,400.0f));
			Engine::GetInstance()->EntityManager()->RegisterEntity(pBullet);
			Engine::GetInstance()->AudioTask()->PlaySound("Shoot2.wav");
		} else {
			for( int i = m_iRow + 1; i < INVADERS_NUM_ROWS; ++i ) {
				if( m_pBoard->GetEnemyEntity(i,m_iIndex) )
					return;
			}

			IEntityPtr pBullet(new MBaseProjectile(2,m_vPosition.x + 15,m_vPosition.y + 35,400.0f));
			Engine::GetInstance()->EntityManager()->RegisterEntity(pBullet);
			Engine::GetInstance()->AudioTask()->PlaySound("Shoot2.wav");
		}
	}*/

	//	m_ShotTimer.Start();
	//}
}

void MBaseEnemy::CollisionEvent( const IEntityPtr pEntity, const int iType, const float fDelta )
{
	if( iType == COLLISION_ENTITY )
		m_bExpired = true;

	m_pBoard->CollisionEvent(iType,m_iIndex,m_iRow);
}

bool MBaseEnemy::GetActive( void )
{
	return m_bActive;
}

bool MBaseEnemy::GetExpired( void )
{
	return m_bExpired;
}

void MBaseEnemy::VKill( void )
{
	Engine::GetInstance()->AudioTask()->PlaySound("Explosion1.wav");
	Engine::GetInstance()->Renderer()->RemoveDrawable(m_TestSprite);
}

void MBaseEnemy::SetVelocity( MVector2& vVelocity )
{
	m_vVelocity = vVelocity;
}

void MBaseEnemy::SetPosition( float x, float y )
{
	m_vPosition.x = x;
	m_vPosition.y = y;
	m_TestSprite->SetPosition(m_vPosition.x,m_vPosition.y);
}

MVector2 MBaseEnemy::GetPosition( void )
{
	return m_vPosition;
}