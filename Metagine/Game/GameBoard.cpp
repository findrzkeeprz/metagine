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

#include "GameBoard.h"
#include "BaseEnemy.h"
#include "../Engine/RenderTask.h"
#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"
#include "../Engine/InputTask.h"
#include "../Public/Public.h"

MGameBoard::MGameBoard( void ) :
m_bRowShift(false),
m_iRowDepth(1),
m_iSpeedTier(0),
m_bReachedBottom(false)
{

}

MGameBoard::~MGameBoard( void )
{
}

void MGameBoard::Init( void )
{
	m_BgSprite = ISpritePtr(new MSprite("Sprites/SpaceBG.png",1024,576,0.0f));
	m_pMonkey = ISpritePtr(new MSprite("Sprites/gogorisset1.png",273,9,37,42,255,0,255,1.0f));
	m_pHealthBar = ISpritePtr(new MSprite("Manifests/HealthBar.xml"));
	m_pShieldBar = ISpritePtr(new MSprite("Manifests/ShieldBar.xml"));
	m_PlayerShip = IEntityPtr(new MShip());
	
	m_pMonkey->SetPosition(15,10);
	m_pShieldBar->SetPosition(60,20);
	m_pHealthBar->SetPosition(60,35);
	
	Engine::GetInstance()->Renderer()->RegisterDrawable(m_BgSprite);
	Engine::GetInstance()->Renderer()->RegisterDrawable(m_pMonkey);
	Engine::GetInstance()->Renderer()->RegisterDrawable(m_pHealthBar);
	Engine::GetInstance()->Renderer()->RegisterDrawable(m_pShieldBar);
	Engine::GetInstance()->EntityManager()->RegisterEntity(m_PlayerShip);
	Engine::GetInstance()->InputManager()->RegisterListener(dynamic_pointer_cast<IInputListener>(m_PlayerShip));

	m_fSpeedTier1 = Engine::GetInstance()->VarManager()->CreateVar("f_speedtier1",75.0f);
	m_fSpeedTier2 = Engine::GetInstance()->VarManager()->CreateVar("f_speedtier2",100.0f);
	m_fSpeedTier3 = Engine::GetInstance()->VarManager()->CreateVar("f_speedtier3",150.0f);
	m_fSpeedTier4 = Engine::GetInstance()->VarManager()->CreateVar("f_speedtier4",300.0f);
	
	for( int i = 0; i < INVADERS_NUM_ROWS; ++i ) {
		for( int j = 0; j < INVADERS_NUM_COLS; ++j ) {
			m_pEnemies[i][j] = IEntityPtr(new MBaseEnemy(MVector2(20.0f + (j * 50),80.0f + (i * 30)),this,j,i));
			Engine::GetInstance()->EntityManager()->RegisterEntity(m_pEnemies[i][j]);
		}
	}
}

void MGameBoard::Kill( void )
{
	m_PlayerShip.reset();
	m_pEnemy.reset();
	m_BgSprite.reset();
	m_pMonkey.reset();
	m_fSpeedTier1.reset();
	m_fSpeedTier2.reset();
	m_fSpeedTier3.reset();
	m_fSpeedTier4.reset();

	for( int i = 0; i < INVADERS_NUM_ROWS; ++i ) {
		for( int j = 0; j < INVADERS_NUM_COLS; ++j ) {
			m_pEnemies[i][j].reset();
		}
	}
}

void MGameBoard::CollisionEvent( int iType, int iIndex, int iRow )
{
	if( !m_bReachedBottom && iType == COLLISION_LEFT_SCREEN ) {
		m_bRowShift = true;
		for( int i = 0; i < INVADERS_NUM_ROWS; ++i ) {
			for( int j = 0; j < INVADERS_NUM_COLS; ++j ) {
				if( m_pEnemies[i][j] ) {
					m_pEnemies[i][j]->SetVelocity(MVector2(50.0f,0.0f));
					switch( m_iSpeedTier ) {
						case 1: m_pEnemies[i][j]->SetVelocity(MVector2(m_fSpeedTier1->GetValueFloat(),0.0f)); break;
						case 2: m_pEnemies[i][j]->SetVelocity(MVector2(m_fSpeedTier2->GetValueFloat(),0.0f)); break;
						case 3: m_pEnemies[i][j]->SetVelocity(MVector2(m_fSpeedTier3->GetValueFloat(),0.0f)); break;
						case 4: m_pEnemies[i][j]->SetVelocity(MVector2(m_fSpeedTier4->GetValueFloat(),0.0f)); break;
					}
				}
			}
		}
	} else if( !m_bReachedBottom && iType == COLLISION_RIGHT_SCREEN ) {
		for( int i = 0; i < INVADERS_NUM_ROWS; ++i ) {
			for( int j = 0; j < INVADERS_NUM_COLS; ++j ) {
				if( m_pEnemies[i][j] ) {
					m_pEnemies[i][j]->SetVelocity(MVector2(-50.0f,0.0f));
					switch( m_iSpeedTier ) {
						case 1: m_pEnemies[i][j]->SetVelocity(MVector2(-m_fSpeedTier1->GetValueFloat(),0.0f)); break;
						case 2: m_pEnemies[i][j]->SetVelocity(MVector2(-m_fSpeedTier2->GetValueFloat(),0.0f)); break;
						case 3: m_pEnemies[i][j]->SetVelocity(MVector2(-m_fSpeedTier3->GetValueFloat(),0.0f)); break;
						case 4: m_pEnemies[i][j]->SetVelocity(MVector2(-m_fSpeedTier4->GetValueFloat(),0.0f)); break;
					}
				}
			}
		}

		if( m_bRowShift ) {
			if( m_iSpeedTier < 4 ) ++m_iSpeedTier;
			
			for( int i = 0; i < INVADERS_NUM_ROWS; ++i ) {
				for( int j = 0; j < INVADERS_NUM_COLS; ++j ) {
					if( m_pEnemies[i][j] ) {
						MVector2 vPosition = m_pEnemies[i][j]->GetPosition();
						m_pEnemies[i][j]->SetPosition(MVector2(vPosition.x,vPosition.y + 20.0f));
					}
				}
			}

			m_bRowShift = false;
		}
	}

	else if( !m_bReachedBottom && iType == COLLISION_LOWER_SCREEN ) {
		for( int i = 0; i < INVADERS_NUM_ROWS; ++i ) {
			for( int j = 0; j < INVADERS_NUM_COLS; ++j ) {
				if( m_pEnemies[i][j] ) {
					if( rand() % 1 == 1 )
						m_pEnemies[i][j]->SetVelocity(MVector2(rand() % 500 + 300,-rand() % 500 + 300));
					else
						m_pEnemies[i][j]->SetVelocity(MVector2(-rand() % 500 + 300,-rand() % 500 + 300));
				}
			}
		}

		m_bReachedBottom = true;
	}
	
	else if( iType == COLLISION_ENTITY ) {
		m_pEnemies[iRow][iIndex].reset();
	}
}

IEntity* MGameBoard::GetEnemyEntity( int iRow, int iIndex )
{
	return m_pEnemies[iRow][iIndex].get();
}