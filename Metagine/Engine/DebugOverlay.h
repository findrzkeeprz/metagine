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

#ifndef _DEBUGOVERLAY_H_
#define _DEBUGOVERLAY_H_

#include "../Public/Public.h"
#include "../Interfaces/IEngine.h"
#include "Font.h"

class MDebugOverlay : public IDrawable, public noncopyable
{
public:

	MDebugOverlay( IEngine* pEngine );
	~MDebugOverlay( void );

	void Render( void );
	float GetDepth( void ) { return 0.0f; }
	void SetActive( bool bActive ) { m_bActive = bActive; }
	bool GetActive( void ) { return m_bActive; }

private:

	bool m_bActive;
	IEngine* m_pEngine;
	shared_ptr<MFont> m_Font;
	IVarPtr m_bDebugOverlay;
};

typedef shared_ptr<MDebugOverlay> MDebugOverlayPtr;

#endif // _DEBUGOVERLAY_H_
