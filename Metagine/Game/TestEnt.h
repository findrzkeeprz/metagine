#include "../Interfaces/ISprite.h"
#include "../Interfaces/IEntity.h"

class MTestEnt : public IEntity
{
public:

	MTestEnt( float x, float y, float fSpeed );
	~MTestEnt( void );

	// Documented in IEntity.h
	void UpdateLogic( int iDelta );
	bool GetActive( void );
	ISpritePtr GetSprite( void ) { return m_TestSprite; }
	void CollisionEvent( IEntityPtr pEntity, int iDelta );
	void VKill( void );

private:

	ISpritePtr m_TestSprite;
	MVector2 m_vPosition;
	MVector2 m_vVelocity;
	MVector2 m_vAcceleration;
	bool m_bActive;
};