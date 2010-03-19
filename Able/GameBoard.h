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

#ifndef _GAMEBOARD_H_
#define _GAMEBOARD_H_

#include "../Interfaces/ISprite.h"
#include "Ship.h"
#include "BaseProjectile.h"

#define INVADERS_NUM_ROWS 6
#define INVADERS_NUM_COLS 12

class MGameBoard
{
public:

	MGameBoard( void );
	~MGameBoard( void );

	void Init( void );
	void Kill( void );
	void CollisionEvent( int iType, int iIndex, int iRow );
	IEntity* GetEnemyEntity( int iRow, int iIndex );

private:

	ISpritePtr m_BgSprite;
	ISpritePtr m_pMonkey;
	ISpritePtr m_pShieldBar;
	ISpritePtr m_pHealthBar;
	IEntityPtr m_PlayerShip;
	IEntityPtr m_pEnemies[INVADERS_NUM_ROWS][INVADERS_NUM_COLS];
	IEntityPtr m_pEnemy;
	IVarPtr m_fSpeedTier1;
	IVarPtr m_fSpeedTier2;
	IVarPtr m_fSpeedTier3;
	IVarPtr m_fSpeedTier4;
	bool m_bRowShift;
	bool m_bReachedBottom;
	int m_iRowDepth;
	int m_iSpeedTier;
};

#endif // _GAMEBOARD_H_