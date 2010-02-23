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
#include "../Engine/Renderer.h"
#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"
#include "../Engine/InputManager.h"
#include "../Public/Public.h"

MGameBoard::MGameBoard( void )
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
	//m_BgSprite = new MSprite("SpaceBG.png",0,true,1.0f);
	m_BgSprite = ISpritePtr(new MSprite("SpaceBG.png",0,true,1.0f));
	Renderer::GetInstance()->RegisterDrawable(m_BgSprite);
	m_PlayerShip = IEntityPtr(new MShip());
	m_TestEnt = IEntityPtr(new MTestEnt());
	Engine::GetInstance()->RegisterEntity(m_PlayerShip);
	Engine::GetInstance()->RegisterEntity(m_TestEnt);
	InputManager::GetInstance()->RegisterListener(boost::shared_dynamic_cast<IInputListener>(m_PlayerShip));
}

void MGameBoard::Kill( void )
{
	m_PlayerShip.reset();
	m_TestEnt.reset();
	m_BgSprite.reset();
}