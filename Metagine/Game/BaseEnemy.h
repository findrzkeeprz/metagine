#include "GameBoard.h"
#include "../Interfaces/ISprite.h"
#include "../Interfaces/IEntity.h"

class MBaseEnemy : public IEntity
{
public:

	MBaseEnemy( float x, float y, MGameBoard* pBoard, int iIndex, int iRow );
	~MBaseEnemy( void );

	// Documented in IEntity.h
	void UpdateLogic( float fDelta );
	bool GetActive( void );
	bool GetExpired( void );
	ISpritePtr GetSprite( void ) { return m_TestSprite; }
	void CollisionEvent( const IEntityPtr pEntity, const int iType, const float fDelta );
	void VKill( void );
	void SetVelocity( MVector2& vVelocity );
	MVector2 GetVelocity( void );
	void SetPosition( float x, float y );
	MVector2 GetPosition( void );


private:

	MGameBoard* m_pBoard;
	ISpritePtr m_TestSprite;
	MVector2 m_vPosition;
	MVector2 m_vVelocity;
	MVector2 m_vAcceleration;
	MTimer m_ShotTimer;
	bool m_bActive;
	bool m_bExpired;
	int m_iIndex;
	int m_iRow;
};