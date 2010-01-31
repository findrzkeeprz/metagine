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

#include <stdio.h>
#include "../Includes/SDL/SDL_keysym.h"
#include "Console.h"
#include "InputManager.h"
#include "Renderer.h"

MConsole::MConsole( void ) :
m_iScrollPoint(0),
m_bToggleAnimUp(false),
m_bToggleAnimDown(true),
m_bToggling(true),
m_sCurrentBuffer("> ")
{
	printf(" -> MConsole object created.\n");
}

MConsole::~MConsole( void )
{
	printf(" -> MConsole object destructed.\n");
}

bool MConsole::Init( void )
{	
	m_Font = new MOutlineFont("m01.TTF",15,255,255,255);
	m_Font->SetColour(255,255,255);
	m_Font->SetColourBG(120,120,255);

	InputManager::GetInstance()->RegisterListener(this);
	Renderer::GetInstance()->RegisterDrawable(this);
	
	return true;
}

void MConsole::Shutdown( void )
{
	printf(" -> MConsole::Shutdown() called.\n");

	if( m_Font ) {
		delete m_Font;
		m_Font = NULL;
	}

	InputManager::GetInstance()->RemoveListener(this);
	Renderer::GetInstance()->RemoveDrawable(this);
}

void MConsole::Echo( const char* pszText )
{
	if( !pszText ) {
		// Error here.
		return;
	}

	std::string sTemp(pszText);
	m_BackBuffer.push_back(sTemp);
}

void MConsole::Execute( const char* pszString )
{
	pszString += 2;
	Echo(pszString);
}

bool MConsole::GetActive( void )
{
	return m_bActive;
}

void MConsole::Render( void* pSurface )
{
	if( m_bToggleAnimDown ) {
		if( m_iScrollPoint < 90 ) {
			m_iScrollPoint += 3;
			m_bToggling = true;
		}
		else {
			m_bToggleAnimDown = false;
			m_bToggling = false;
		}
	} if( m_bToggleAnimUp ) {
		if( m_iScrollPoint > -10 ) {
			m_iScrollPoint -= 3;
			m_bToggling = true;
		}
		else {
			m_bToggleAnimUp = false;
			m_bActive = false;
			m_bToggling = false;
		}
	}
	
	for( int i = 0; i < 5; i++ ) {
		if( m_BackBuffer[i].c_str() ) {
			m_Font->SetPosition(10,m_iScrollPoint - (i * 20));
			m_Font->SetText(m_BackBuffer[(m_BackBuffer.size() - 1) - i]);
			m_Font->Render(pSurface);
		}
	}

	m_Font->SetPosition(10,m_iScrollPoint + 20);
	m_Font->SetText(m_sCurrentBuffer);
	m_Font->Render(pSurface);
}

void MConsole::UpdateInput( bool bKeys[] )
{
	// Quick hack...
	//if( !bKeys ) return;
	//bool keysHeld[323] = { false };
	//keysHeld[event.key.keysym.sym] = true;	}
	
	// Toggle the console.
	if( bKeys[SDLK_F5] && !m_bToggling ) {
		if( m_bActive )
			m_bToggleAnimUp = true;
		else {
			m_bActive = true;
			m_bToggleAnimDown = true;
		}
	}
	
	if( m_bActive ) {
		bool bShiftMod = (bKeys[SDLK_LSHIFT] || bKeys[SDLK_RSHIFT]) ? true : false;
		if( bKeys[SDLK_a] ) m_sCurrentBuffer.append((bShiftMod == true) ? "A" : "a");
		else if( bKeys[SDLK_b] ) m_sCurrentBuffer.append((bShiftMod == true) ? "B" : "b");
		else if( bKeys[SDLK_c] ) m_sCurrentBuffer.append((bShiftMod == true) ? "C" : "c");
		else if( bKeys[SDLK_d] ) m_sCurrentBuffer.append((bShiftMod == true) ? "D" : "d");
		else if( bKeys[SDLK_e] ) m_sCurrentBuffer.append((bShiftMod == true) ? "E" : "e");
		else if( bKeys[SDLK_f] ) m_sCurrentBuffer.append((bShiftMod == true) ? "F" : "f");
		else if( bKeys[SDLK_g] ) m_sCurrentBuffer.append((bShiftMod == true) ? "G" : "g");
		else if( bKeys[SDLK_h] ) m_sCurrentBuffer.append((bShiftMod == true) ? "H" : "h");
		else if( bKeys[SDLK_i] ) m_sCurrentBuffer.append((bShiftMod == true) ? "I" : "i");
		else if( bKeys[SDLK_j] ) m_sCurrentBuffer.append((bShiftMod == true) ? "J" : "j");
		else if( bKeys[SDLK_k] ) m_sCurrentBuffer.append((bShiftMod == true) ? "K" : "k");
		else if( bKeys[SDLK_l] ) m_sCurrentBuffer.append((bShiftMod == true) ? "L" : "l");
		else if( bKeys[SDLK_m] ) m_sCurrentBuffer.append((bShiftMod == true) ? "M" : "m");
		else if( bKeys[SDLK_n] ) m_sCurrentBuffer.append((bShiftMod == true) ? "N" : "n");
		else if( bKeys[SDLK_o] ) m_sCurrentBuffer.append((bShiftMod == true) ? "O" : "o");
		else if( bKeys[SDLK_p] ) m_sCurrentBuffer.append((bShiftMod == true) ? "P" : "p");
		else if( bKeys[SDLK_q] ) m_sCurrentBuffer.append((bShiftMod == true) ? "Q" : "q");
		else if( bKeys[SDLK_r] ) m_sCurrentBuffer.append((bShiftMod == true) ? "R" : "r");
		else if( bKeys[SDLK_s] ) m_sCurrentBuffer.append((bShiftMod == true) ? "S" : "s");
		else if( bKeys[SDLK_t] ) m_sCurrentBuffer.append((bShiftMod == true) ? "T" : "t");
		else if( bKeys[SDLK_u] ) m_sCurrentBuffer.append((bShiftMod == true) ? "U" : "u");
		else if( bKeys[SDLK_v] ) m_sCurrentBuffer.append((bShiftMod == true) ? "V" : "v");
		else if( bKeys[SDLK_w] ) m_sCurrentBuffer.append((bShiftMod == true) ? "W" : "w");
		else if( bKeys[SDLK_x] ) m_sCurrentBuffer.append((bShiftMod == true) ? "X" : "x");
		else if( bKeys[SDLK_y] ) m_sCurrentBuffer.append((bShiftMod == true) ? "Y" : "y");
		else if( bKeys[SDLK_z] ) m_sCurrentBuffer.append((bShiftMod == true) ? "Z" : "z");
		else if( bKeys[SDLK_0] ) m_sCurrentBuffer.append((bShiftMod == true) ? ")" : "0");
		else if( bKeys[SDLK_1] ) m_sCurrentBuffer.append((bShiftMod == true) ? "!" : "1");
		else if( bKeys[SDLK_2] ) m_sCurrentBuffer.append((bShiftMod == true) ? "\"" : "2");
		else if( bKeys[SDLK_3] ) m_sCurrentBuffer.append((bShiftMod == true) ? "�" : "3");
		else if( bKeys[SDLK_4] ) m_sCurrentBuffer.append((bShiftMod == true) ? "$" : "4");
		else if( bKeys[SDLK_5] ) m_sCurrentBuffer.append((bShiftMod == true) ? "%" : "5");
		else if( bKeys[SDLK_6] ) m_sCurrentBuffer.append((bShiftMod == true) ? "^" : "6");
		else if( bKeys[SDLK_7] ) m_sCurrentBuffer.append((bShiftMod == true) ? "&" : "7");
		else if( bKeys[SDLK_8] ) m_sCurrentBuffer.append((bShiftMod == true) ? "*" : "8");
		else if( bKeys[SDLK_9] ) m_sCurrentBuffer.append((bShiftMod == true) ? "(" : "9");

		// Special cases.
		else if( bKeys[SDLK_RETURN] ) {
			Execute(m_sCurrentBuffer.c_str());
			m_sCurrentBuffer = "> ";
		} else if( bKeys[SDLK_BACKSPACE] ) {
			if( m_sCurrentBuffer.length() > 2 )
				m_sCurrentBuffer.erase(m_sCurrentBuffer.end() - 1);
		}

		/*switch( iKey ) { // (day == WEEKEND) ? 12 : 9;
			//case SDLK_a: { m_sCurrentBuffer.append("a"); } break;
			case SDLK_a: { m_sCurrentBuffer.append((bShiftMod == true) ? "A" : "a"); } break;
			case SDLK_b: { m_sCurrentBuffer.append("b"); } break;
			case SDLK_c: { m_sCurrentBuffer.append("c"); } break;
			case SDLK_d: { m_sCurrentBuffer.append("d"); } break;
			case SDLK_e: { m_sCurrentBuffer.append("e"); } break;
			case SDLK_f: { m_sCurrentBuffer.append("f"); } break;
			case SDLK_g: { m_sCurrentBuffer.append("g"); } break;
			case SDLK_h: { m_sCurrentBuffer.append("h"); } break;
			case SDLK_i: { m_sCurrentBuffer.append("i"); } break;
			case SDLK_j: { m_sCurrentBuffer.append("j"); } break;
			case SDLK_k: { m_sCurrentBuffer.append("k"); } break;
			case SDLK_l: { m_sCurrentBuffer.append("l"); } break;
			case SDLK_m: { m_sCurrentBuffer.append("m"); } break;
			case SDLK_n: { m_sCurrentBuffer.append("n"); } break;
			case SDLK_o: { m_sCurrentBuffer.append("o"); } break;
			case SDLK_p: { m_sCurrentBuffer.append("p"); } break;
			case SDLK_q: { m_sCurrentBuffer.append("q"); } break;
			case SDLK_r: { m_sCurrentBuffer.append("r"); } break;
			case SDLK_s: { m_sCurrentBuffer.append("s"); } break;
			case SDLK_t: { m_sCurrentBuffer.append("t"); } break;
			case SDLK_u: { m_sCurrentBuffer.append("u"); } break;
			case SDLK_v: { m_sCurrentBuffer.append("v"); } break;
			case SDLK_w: { m_sCurrentBuffer.append("w"); } break;
			case SDLK_x: { m_sCurrentBuffer.append("x"); } break;
			case SDLK_y: { m_sCurrentBuffer.append("y"); } break;
			case SDLK_z: { m_sCurrentBuffer.append("z"); } break;
			case SDLK_0: { m_sCurrentBuffer.append("0"); } break;
			case SDLK_1: { m_sCurrentBuffer.append("1"); } break;
			case SDLK_2: { m_sCurrentBuffer.append("2"); } break;
			case SDLK_3: { m_sCurrentBuffer.append("3"); } break;
			case SDLK_4: { m_sCurrentBuffer.append("4"); } break;
			case SDLK_5: { m_sCurrentBuffer.append("5"); } break;
			case SDLK_6: { m_sCurrentBuffer.append("6"); } break;
			case SDLK_7: { m_sCurrentBuffer.append("7"); } break;
			case SDLK_8: { m_sCurrentBuffer.append("8"); } break;
			case SDLK_9: { m_sCurrentBuffer.append("9"); } break;
			case SDLK_PERIOD: { m_sCurrentBuffer.append("."); } break;
			case SDLK_UNDERSCORE: { m_sCurrentBuffer.append("_"); } break;
			case SDLK_SPACE: { m_sCurrentBuffer.append(" "); } break;
			
			// Some special cases.
			case SDLK_RETURN: 
				{ 
					Execute(m_sCurrentBuffer.c_str());
					m_sCurrentBuffer = "> ";
				} break;
			case SDLK_BACKSPACE: 
				{ 
					if( m_sCurrentBuffer.length() > 2 )
						m_sCurrentBuffer.erase(m_sCurrentBuffer.end() - 1); 
					
				} break;

			default: break;
		}*/
	}
}