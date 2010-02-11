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

#ifndef _OBJECTFACTORY_H_
#define _OBJECTFACTORY_H_

#define OBJECTFACTORY_NAME "MObjectFactory"
#define OBJECTFACTORY_VERSION "01"

#include <vector>
#include "../Public/Singleton.h"
#include "../Interfaces/IObjectFactory.h"
#include "../Interfaces/ISprite.h"

/// Manages game object creation.
/// This class is responsible for the creation and tracking of game
/// objects which can be created dynamically through this interface.
/// If at engine shutdown, there are still allocated game objects
/// which have not been deleted and should have been, it will also
/// delete these to help prevent memory leakage.
class MObjectFactory : public IObjectFactory
{
public:

	/// Default constructor.
	MObjectFactory( void );

	/// Destructor method.
	/// Perform required cleanup operations on graphical subsystems and free
	/// any allocated resources.
	~MObjectFactory( void );

	// Documented in IBaseInterface.h
	const char* GetName( void ) { return OBJECTFACTORY_NAME; }
	const char* GetVersion( void ) { return OBJECTFACTORY_VERSION; }

	// Documented in IObjectFactory.h
	void Shutdown( void );

private:

	//SDL_Surface* m_Screen;					///< Main SDL screen surface.
	//bool m_bFontLibLoaded;					///< Shows the status of the TTF library.
	//std::vector<IDrawable*> m_RenderQueue;	///< A queue of IDrawable objects to render every frame.
};

typedef MSingleton<MObjectFactory> ObjFactory;

#endif // _OBJECTFACTORY_H_
