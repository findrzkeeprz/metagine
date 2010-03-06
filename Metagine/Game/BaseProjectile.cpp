#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"
#include "../Engine/InputTask.h"
#include "../Engine/RenderTask.h"

MBaseProjectile::MBaseProjectile( int iType, float x, float y, float fSpeed ) :
m_bActive(true),
m_bExpired(false)
{
	if( iType == 0 ) 
		m_TestSprite = ISpritePtr(new MSprite("gogorisset1.png",8,84,5,38,255,0,255,0.99f));
	else if( iType == 1 )
		m_TestSprite = ISpritePtr(new MSprite("gogorisset1.png",17,65,3,38,255,0,255,0.99f));
	else if( iType == 2 )
		m_TestSprite = ISpritePtr(new MSprite("gogorisset1.png",109,124,7,7,255,0,255,0.99f));
	
	
	Engine::GetInstance()->Renderer()->RegisterDrawable(m_TestSprite);
	m_vVelocity.y = fSpeed;
	m_vPosition.x = x;
	m_vPosition.y = y;
	m_TestSprite->SetPosition(m_vPosition.x,m_vPosition.y);
}

MBaseProjectile::~MBaseProjectile( void )
{
	Engine::GetInstance()->Renderer()->RemoveDrawable(m_TestSprite);
	printf(" -> MBaseProjectile object deleted.\n");
}

void MBaseProjectile::UpdateLogic( float fDelta )
{
	m_TestSprite->Animate(true);
	
	if( m_vVelocity.Magnitude() <= 0.0f )
		return;
	
	m_vAcceleration = -m_vVelocity.Normalised();
	//m_vAcceleration *= m_fFriction->GetValueFloat();

	MVector2 vDeltaVelocity = ( ( m_vAcceleration * (float)fDelta ) / 1000.0f );

	// Cap magnitude of change in velocity to remove integration errors
	if( vDeltaVelocity.Magnitude() > m_vVelocity.Magnitude() )
		m_vVelocity.Zero();
	else m_vVelocity += vDeltaVelocity;

	m_vPosition += ( ( m_vVelocity * (float)fDelta ) / 1000.0f );

	if(m_vVelocity.Magnitude() < 0.1f) 
		m_vVelocity.Zero();
		
	m_TestSprite->SetPosition(m_vPosition.x,m_vPosition.y);
}

void MBaseProjectile::CollisionEvent( const IEntityPtr pEntity, const int iType, const float fDelta )
{
	m_bExpired = true;
}

bool MBaseProjectile::GetActive( void )
{
	return m_bActive;
}

bool MBaseProjectile::GetExpired( void )
{
	return m_bExpired;
}

void MBaseProjectile::VKill( void )
{
}

void MBaseProjectile::SetVelocity( MVector2& vVelocity )
{
	m_vVelocity = vVelocity;
}

void MBaseProjectile::SetPosition( float x, float y )
{
	m_vPosition.x = x;
	m_vPosition.y = y;
	m_TestSprite->SetPosition(m_vPosition.x,m_vPosition.y);
}

MVector2 MBaseProjectile::GetPosition( void )
{
	return m_vPosition;
}