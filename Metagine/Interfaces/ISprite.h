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

#ifndef _ISPRITE_H_
#define _ISPRITE_H_

#include "../Public/Public.h"
#include "../Interfaces/IDrawable.h"

class ISprite : public IDrawable
{
public:

	/// Virtual destructor method.
	virtual ~ISprite( void ) { };

	/// Loads an external image to display as a game sprite.
	/// This loads an image file relative to the main engine executable.
	/// The file should be of a correct image format, which will then
	/// be converted to the correct screen format.
	/// @param sName The relative file name of the external image.
	//virtual void* LoadImageFile( const string& sFileName ) = 0;
	
	/// Sets the screen position of the sprite.
	/// This will set the 2D position of the sprite on the game screen. Setting
	/// this to an off-screen positions will cause the sprite to not be drawn.
	/// @param x The x-screen coordinate.
	/// @param y The y-screen coordinate.
	virtual void SetPosition( float x, float y ) = 0;
	
	/// Sets the rotation of the sprite.
	/// This will only work if the sprite was created with the relevant settings
	/// passed to the constructor. Sets the current sprite texture to a pre-
	/// cached surface previously created.
	/// @param iAngle An angle between 0 and 359.
	virtual void SetRotation( double iAngle ) = 0;

	virtual float GetPositionX( void ) = 0;
	virtual float GetPositionY( void ) = 0;

	virtual unsigned int GetSurface( void ) = 0;

	virtual int GetWidth( void ) = 0;
	virtual int GetHeight( void ) = 0;

	virtual void Animate( bool bLoop ) = 0;
};

typedef shared_ptr<ISprite> ISpritePtr;

#endif // _ISPRITE_H_