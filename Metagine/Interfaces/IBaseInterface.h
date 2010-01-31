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

#ifndef _IBASEINTERFACE_H_
#define _IBASEINTERFACE_H_

/// Public interface for main game components.
class IBaseInterface
{
public:
    
    virtual ~IBaseInterface( void ) { };    

    /// Gets the textual name of the interface.
    /// This would normally should normally return the name of the interface
    /// as it appears at the source-code level. Exceptions may apply.
    virtual const char* GetName( void ) = 0;

    /// Gets the version number of the interface.
    /// This is important because some external modules may require a specific
    /// version of a certain interface. By doing a simple version check we can
    /// rule out any runtime incompatibility nasties.
    virtual const char* GetVersion( void ) = 0;

	/// Shutdown routine for participating interfaces.
    /// This gives interfaces that are registered with the MEngine class an
    /// opportunity to perform cleanup operations before object deletion.
    /// @see MEngine::~MEngine()
    /// @see MEngine::Shutdown()
	virtual void Shutdown( void ) { };
};

#endif // _IBASEINTERFACE_H_
