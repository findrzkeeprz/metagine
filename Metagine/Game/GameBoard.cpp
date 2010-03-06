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
m_iRowDepth(1)
{

}

MGameBoard::~MGameBoard( void )
{
	//if( m_PlayerShip ) {
	//	delete m_PlayerShip;
	//	m_PlayerShip = NULL;
	//}
}

void MGameBoard::Init( void )
{
	m_BgSprite = ISpritePtr(new MSprite("SpaceBG.png",1024,576,1.0f));
	m_pMonkey = ISpritePtr(new MSprite("gogorisset1.png",273,9,37,42,255,0,255,0.0f));
	m_PlayerShip = IEntityPtr(new MShip());
	m_pMonkey->SetPosition(10,10);
	
	Engine::GetInstance()->Renderer()->RegisterDrawable(m_BgSprite);
	Engine::GetInstance()->Renderer()->RegisterDrawable(m_pMonkey);
	Engine::GetInstance()->EntityManager()->RegisterEntity(m_PlayerShip);
	Engine::GetInstance()->InputManager()->RegisterListener(dynamic_pointer_cast<IInputListener>(m_PlayerShip));
	
	for( int i = 0; i < INVADERS_NUM_ROWS; ++i ) {
		for( int j = 0; j < INVADERS_NUM_COLS; ++j ) {
			//m_pEnemies[i][j] = IEntityPtr(new MBaseEnemy(20.0f + (j * 50),80.0f + (i * 30),this,j,i));
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

	for( int i = 0; i < INVADERS_NUM_ROWS; ++i ) {
		for( int j = 0; j < INVADERS_NUM_COLS; ++j ) {
			m_pEnemies[i][j].reset();
		}
	}
}

void MGameBoard::CollisionEvent( int iType, int iIndex, int iRow )
{
	if( iType == COLLISION_LEFT_SCREEN ) {
		m_bRowShift = true;
		for( int i = 0; i < INVADERS_NUM_ROWS; ++i ) {
			for( int j = 0; j < INVADERS_NUM_COLS; ++j ) {
				if( m_pEnemies[i][j] ) m_pEnemies[i][j]->SetVelocity(MVector2(80.0f,0.0f));
			}
		}
	} else if( iType == COLLISION_RIGHT_SCREEN ) {
		for( int i = 0; i < INVADERS_NUM_ROWS; ++i ) {
			for( int j = 0; j < INVADERS_NUM_COLS; ++j ) {
				if( m_pEnemies[i][j] ) m_pEnemies[i][j]->SetVelocity(MVector2(-80.0f,0.0f));
			}
		}

		if( m_bRowShift ) {
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
	
	else if( iType == COLLISION_ENTITY ) {
		m_pEnemies[iRow][iIndex].reset();
	}
}

IEntity* MGameBoard::GetEnemyEntity( int iRow, int iIndex )
{
	return m_pEnemies[iRow][iIndex].get();
}