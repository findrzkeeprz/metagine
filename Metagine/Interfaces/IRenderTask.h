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

#ifndef _IRENDERER_H_
#define _IRENDERER_H_

#include "../Public/Public.h"
#include "../Interfaces/ITask.h"
#include "../Interfaces/IDrawable.h"

/// Public interface for the MRenderer class.
class IRenderTask : public ITask
{
public:

	virtual ~IRenderTask( void ) { };

	/// Determines whether the TTF font library has been loaded.
	virtual bool FontLibLoaded( void ) = 0;

	/// Register an IDrawable object with the renderer.
	/// This will register the specified IDrawable object for automatic calls
	/// to IDrawable::Render() on every render frame.
	/// @param pDrawable A pointer to the IDrawable object to be registered.
	virtual void RegisterDrawable( IDrawablePtr pDrawable ) = 0;

	/// Remove a registered IDrawable object from the renderer.
	/// Searches the list of registered IDrawable objects and removes it from
	/// the list so that the object will not be rendered in future frames.
	/// Note that this does not delete the allocated object.
	/// @param pDrawable A pointer to the IDrawable object to be removed.
	virtual void RemoveDrawable( IDrawablePtr pDrawable ) = 0;

	/// Renders the game view.
	/// This is called repeatedly to render the game view. It also recursively
	/// calls IDrawable::Render() on any active objects that the renderer is
	/// currently tracking.
	//virtual void Frame( void ) = 0;
	virtual int GetDrawableCount( void ) = 0;

	virtual int GetScreenWidth( void ) = 0;
	virtual int GetScreenHeight( void ) = 0;
};

typedef shared_ptr<IRenderTask> IRendererPtr;

#endif // _IRENDERER_H_
