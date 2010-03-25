#include "GameBoard.h"
#include "../Metagine/Interfaces/ISprite.h"
#include "../Metagine/Interfaces/IEntity.h"

#include "BaseEntity.h"

class MBaseEnemy : public MBaseEntity
{
public:

	MBaseEnemy( MVector2 vPosition, MGameBoard* pBoard, int iIndex, int iRow );
	~MBaseEnemy( void );

	void UpdateLogic( float fDelta );
	void CollisionEvent( IEntity* pEntity, const int iType, const float fDelta );
	void VKill( void );
	
private:

	MGameBoard* m_pBoard;
	MVector2 m_vAcceleration;
	MTimer m_ShotTimer;
	int m_iIndex;
	int m_iRow;
};