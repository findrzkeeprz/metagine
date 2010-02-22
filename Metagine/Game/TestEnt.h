#include "../Interfaces/ISprite.h"
#include "../Interfaces/IEntity.h"

class MTestEnt : public IEntity
{
public:

	MTestEnt( void );
	~MTestEnt( void );

	// Documented in IInputListener.h
	void UpdateInput( const bool bKeys[], const int iKey, const bool bKeyDown );

	// Documented in IEntity.h
	void UpdateLogic( int iDelta );
	bool GetActive( void );
	ISprite* GetSprite( void ) { return m_TestSprite; }
	void CollisionEvent( IEntity* pEntity, int iDelta );

private:

	ISprite* m_TestSprite;
	float m_fPosition[2];
	float m_fVelocity[2];
	bool m_bActive;
};