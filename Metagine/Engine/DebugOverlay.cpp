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

#include "DebugOverlay.h"

MDebugOverlay::MDebugOverlay( IEngine* pEngine )
{
	printf(" -> MDebugOverlay object created.\n");
	
	m_pEngine = pEngine;
	m_Font = shared_ptr<MFont>(new MFont("crayon_alphabet.ttf",15,193,254,154,0.0f));
	m_pEngine->Renderer()->RegisterDrawable(m_Font);
	m_bDebugOverlay = m_pEngine->VarManager()->CreateVar("b_debugoverlay",false);
}

MDebugOverlay::~MDebugOverlay( void )
{
	m_Font.reset();
	m_bDebugOverlay.reset();
	
	printf(" -> MDebugOverlay object destructed.\n");
}

void MDebugOverlay::Render( void *pSurface )
{
	if( m_bDebugOverlay->GetValueBool() ) {
		int iCount = 0;
	
		for( int i = 0; i < 4; ++i ) {
			iCount = m_pEngine->EntityManager()->CollisionResolver()->GetEntitiesInPartition(i);
			m_Font->SetPosition(15,100 + (i * 20));
			m_Font->SetText((boost::format("Partition[%1%]: %2%") % i % iCount).str());
			m_Font->Render(pSurface);
		}

		iCount = m_pEngine->Renderer()->GetDrawableCount();
		m_Font->SetPosition(15,180);
		m_Font->SetText((boost::format("Drawables: %1%") % iCount).str());
		m_Font->Render(pSurface);

		iCount = m_pEngine->EntityManager()->GetEntityCount();
		m_Font->SetPosition(15,200);
		m_Font->SetText((boost::format("Entities: %1%") % iCount).str());
		m_Font->Render(pSurface);
	}
}