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

class IBaseInterface
{
public:
    
    /// Virtual function to get the interface's name.
    virtual const char* GetName( void ) = 0;

    /// Virtual function to get the interface's version string.
    virtual const char* GetVersion( void ) = 0;
};

#endif // _IBASEINTERFACE_H_
