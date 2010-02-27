#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"
#include "../Engine/InputTask.h"
#include "../Engine/RenderTask.h"

MTestEnt::MTestEnt( float x, float y, float fSpeed ) :
m_bActive(true)
{
	m_TestSprite = ISpritePtr(new MSprite("Explosion1.xml"));
	Engine::GetInstance()->Renderer()->RegisterDrawable(m_TestSprite);
	m_vVelocity.y = -fSpeed;
	m_vPosition.x = x;
	m_vPosition.y = y;
	m_TestSprite->SetPosition((int)m_vPosition.x,(int)m_vPosition.y);
}

MTestEnt::~MTestEnt( void )
{
	printf(" -> I'm getting deleted!\n");
	Engine::GetInstance()->Renderer()->RemoveDrawable(m_TestSprite);
}

void MTestEnt::UpdateInput( const bool bKeys[], const int iKey, const bool bKeyDown )
{
}

void MTestEnt::UpdateLogic( int iDelta )
{
	m_TestSprite->Animate(true);
	
	if( m_vVelocity.Magnitude() <= 0.0f )
		return;
	
	m_vAcceleration = -m_vVelocity.Normalised();
	//m_vAcceleration *= m_fFriction->GetValueFloat();

	MVector2 vDeltaVelocity = ( ( m_vAcceleration * (float)iDelta ) / 1000.0f );

	// Cap magnitude of change in velocity to remove integration errors
	if( vDeltaVelocity.Magnitude() > m_vVelocity.Magnitude() )
		m_vVelocity.Zero();
	else m_vVelocity += vDeltaVelocity;

	m_vPosition += ( ( m_vVelocity * (float)iDelta ) / 1000.0f );

	if(m_vVelocity.Magnitude() < 0.1f) 
		m_vVelocity.Zero();
		
	m_TestSprite->SetPosition((int)m_vPosition.x,(int)m_vPosition.y);
}

void MTestEnt::CollisionEvent( IEntityPtr pEntity, int iDelta )
{
	//printf("i can haz collisions!\n");
}

bool MTestEnt::GetActive( void )
{
	return m_bActive;
}