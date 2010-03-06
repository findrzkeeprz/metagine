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

#ifndef _RENDERTASK_H_
#define _RENDERTASK_H_

#include "ThirdParty.h"
#include "../Public/Public.h"
#include "../Public/BaseTypes.h"
#include "../Public/Interfaces.h"

/// Manages game rendering functionality.
/// This class is responsible for initialisation and cleanup of anything
/// related to rendering output. This is currently handled with the SDL library.
/// The object also manages IDrawable objects that have been registered and
/// will call each objects IDrawable::Render() function every frame.
class MRenderTask : public IRenderTask, public noncopyable
{
public:

	/// Default constructor.
	MRenderTask( void );

	/// Destructor method.
	/// Perform required cleanup operations on graphical subsystems and free
	/// any allocated resources.
	~MRenderTask( void );

	/// Initialise the renderer component.
	/// Initialise the graphical subsystems and allocate any required resources
	/// such as the SDL and TTF libraries.
	//bool Init( int iWidth, int iHeight );
	
	
	void VInit( void );
	void VKill( void );
	void VFrame( const float fDelta );

	/// Determines whether the TTF font library has been loaded.
	bool FontLibLoaded( void );

	/// Register an IDrawable object with the renderer.
	/// This will register the specified IDrawable object for automatic calls
	/// to IDrawable::Render() on every render frame.
	/// @param pDrawable A pointer to the IDrawable object to be registered.
	void RegisterDrawable( IDrawablePtr pDrawable );

	/// Remove a registered IDrawable object from the renderer.
	/// Searches the list of registered IDrawable objects and removes it from
	/// the list so that the object will not be rendered in future frames.
	/// Note that this does not delete the allocated object.
	/// @param pDrawable A pointer to the IDrawable object to be removed.
	void RemoveDrawable( IDrawablePtr pDrawable );

	/// Renders the game view.
	/// This is called repeatedly to render the game view. It also recursively
	/// calls IDrawable::Render() on any active objects that the renderer is
	/// currently tracking.
	//void Frame( void );

	int GetDrawableCount( void );
	int GetScreenWidth( void );
	int GetScreenHeight( void );

private:

	static bool SpriteSortFunc( IDrawablePtr pData1, IDrawablePtr pData2 );

	SDL_Surface* m_Screen;						///< Main SDL screen surface.
	bool m_bFontLibLoaded;						///< Shows the status of the TTF library.
	vector<IDrawablePtr> m_RenderQueue;			///< A queue of IDrawable objects to render every frame.
	int m_iResolution[2];						///< Resolution of the engine screen.
};

#endif // _RENDERTASK_H_
