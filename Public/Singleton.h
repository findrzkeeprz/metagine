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

#ifndef _CSINGLETON_H_
#define _CSINGLETON_H_

template <class T>
class MSingleton
{
protected:

    /// Default constructor, called only once.
    MSingleton( void );
    
    /// Destructor method.
    ~MSingleton( void );

private:

    /// The singleton object, only one per instance.
    static T* m_Singleton;
    
public:
    
    /// Accessor to return the singleton instance.
    /// If the instance has not yet been created, it will create one.
    static T* GetInstance( void )
    {
        if( !m_Singleton ) {
            m_Singleton = new T;
        }
        
        return m_Singleton;
    }   
};

template <class T> T* MSingleton<T>::m_Singleton = NULL;

#endif // _CSINGLETON_H_
