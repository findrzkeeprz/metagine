#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"
#include "../Engine/InputManager.h"
#include "../Engine/Renderer.h"

MTestEnt::MTestEnt( void ) :
m_bActive(true)
{
	// This will all need to go through the engine interface in future.
	m_TestSprite = new MSprite("Ship1.png",0,true,71,0,50,65,255,0,255,0.95f);

	// Center the ship on the center of the screen initially.
	//int iCenter = (Renderer::GetInstance()->GetScreenWidth() / 2) - ( m_TestSprite->GetWidth() / 2 );
	m_fPosition[0] = 50.0f;
	m_fPosition[1] = 400.0f;
	m_fVelocity[0] = 0.0f;
	m_fVelocity[1] = 0.0f;
	m_TestSprite->SetPosition((int)m_fPosition[0],(int)m_fPosition[1]);

	//InputManager::GetInstance()->RegisterListener(this);
	Engine::GetInstance()->RegisterEntity(this);
}

MTestEnt::~MTestEnt( void )
{
}

void MTestEnt::UpdateInput( const bool bKeys[], const int iKey, const bool bKeyDown )
{
}

void MTestEnt::UpdateLogic( int iDelta )
{
}

void MTestEnt::CollisionEvent( IEntity* pEntity )
{
	//printf("i can haz collisions!\n");
}

bool MTestEnt::GetActive( void )
{
	return m_bActive;
}