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

#ifndef _MENGINE_H_
#define _MENGINE_H_

#include "ThirdParty.h"
#include "../Public/Public.h"
#include "../Public/BaseTypes.h"
#include "../Public/Interfaces.h"
#include "../Game/GameBoard.h"

/// Main game engine interface.
/// This object is responsible for the creation and
/// destruction of all other crucial game systems. It should be the first and
/// last piece of code that is executed at game runtime. This object is also
/// responsible for interfacing game components through a simple interface
/// tracking system.
class MEngine : public IEngine, public noncopyable
{
public:

    /// Default constructor.
	/// Performs some simple class member initialisation. The main object
	/// initialisation is performed in Init() rather than here.
    MEngine( void );
    

    /// Destructor method.
    /// Makes a call to Shutdown() and triggers a global game engine shutdown
    /// procedure involving all registered IBaseInterface classes.
    ~MEngine( void );
    
    bool Init( void );
    void Shutdown( void );
	void UpdateEntities( int iDelta );
	bool RegisterEntity( IEntityPtr );
	void RemoveEntity( IEntityPtr );
	IConsolePtr				Console( void )				{ return m_pConsole; }
	IVarManagerPtr			VarManager( void )			{ return m_pVarManager; }
	IRendererPtr			Renderer( void )			{ return m_pRenderer; }
	IInputManagerPtr		InputManager( void )		{ return m_pInputManager; }
	ICollisionResolverPtr	CollisionResolver( void )	{ return m_pCollisionResolver; }

private:

    void Run( void );

    // Handle player input.
    void HandleInput( void );

    // Load the game module.
	bool LoadGameModule( void );

private:

    vector<IBaseInterfacePtr> m_Interfaces;	///< Container of all registered game interfaces.
	vector<IEntityPtr> m_Entities;				///< Collection of all game entities.
	bool m_bActive;							   		///< Identifies whether the engine is currently active.
	
	SDL_Event m_Event;								///< SDL event object.
	MTimer m_FpsTimer;
	MTimer m_GameTimer;
	IVarPtr m_iFpsMax;								///< Maximum FPS limit.
	IVarPtr m_bFpsCap;								///< Whether the FPS is regulated or not.	
	IVarPtr m_iGameRefresh;
	MGameBoard m_GameBoard;
	
	//IBaseInterfacePtr m_pConsole;
	//IBaseInterfacePtr m_pVarManager;
	//IBaseInterfacePtr m_pRenderer;
	//IBaseInterfacePtr m_pInputManager;
	//IBaseInterfacePtr m_pCollisionResolver;

	IConsolePtr m_pConsole;
	IVarManagerPtr m_pVarManager;
	IRendererPtr m_pRenderer;
	IInputManagerPtr m_pInputManager;
	ICollisionResolverPtr m_pCollisionResolver;

	//IEntity
	// Game interface pointer.
	//IGame* m_pGame;
};

typedef MSingleton<MEngine> Engine;

#endif // _MENGINE_H_
