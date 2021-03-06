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

#include "../Includes/SDL/SDL_keysym.h"
#include "Console.h"
#include "Engine.h"
#include "InputTask.h"
#include "RenderTask.h"
#include "VarManager.h"
#include "Var.h"

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
	Shutdown();
	
	printf(" -> MConsole object destructed.\n");
}

bool MConsole::Init( void )
{	
	m_bActive = Engine::GetInstance()->VarManager()->CreateVar("b_con_active",true);
	m_iFontSpacing = Engine::GetInstance()->VarManager()->CreateVar("b_con_fontspacing",15);
	m_iPositionX = Engine::GetInstance()->VarManager()->CreateVar("b_con_posx",10);
	m_iPositionYon = Engine::GetInstance()->VarManager()->CreateVar("b_con_posyon",60);
	m_iPositionYoff = Engine::GetInstance()->VarManager()->CreateVar("b_con_posyoff",-30);
	m_iScrollFactor = Engine::GetInstance()->VarManager()->CreateVar("b_con_scrollfactor",3);
	
	m_Font = shared_ptr<MFont>(new MFont("crayon_alphabet.ttf",15,193,254,154,0.0f));
	Engine::GetInstance()->Renderer()->RegisterDrawable(m_Font);
	
	return true;
}

void MConsole::Shutdown( void )
{
	printf(" -> MConsole::Shutdown() called.\n");

	m_Font.reset();
	m_bActive.reset();
	m_iFontSpacing.reset();
	m_iPositionX.reset();
	m_iPositionYon.reset();
	m_iPositionYoff.reset();
	m_iScrollFactor.reset();
	
	m_BackBuffer.clear();
	m_CmdHistory.clear();
}

void MConsole::Echo( const char* pszText, ... )
{
	if( !pszText ) {
		// Error here.
		return;
	}

	char szTmp[512] = "";
	va_list va_alist; 
	va_start(va_alist,pszText); 
	vsprintf_s(szTmp,pszText,va_alist); 
	va_end(va_alist); 

	m_BackBuffer.push_back(szTmp);
}

void MConsole::Execute( const string& sCmd )
{
	string sArg0;
	string sArg1;
	size_t split;
	bool bMultipleArgs = false;
	
	if( ( split = sCmd.find_first_of(" ") ) != string::npos ) {
		sArg0 = sCmd.substr(0,split);
		sArg1 = sCmd.substr(split + 1);
	
		// Discard the remainder of the string.
		if( ( split = sArg1.find_first_of(" ") ) != string::npos )
			sArg1.erase(split);
	}
	
	bMultipleArgs = sArg0.empty() ? false : true;
	if( !bMultipleArgs ) sArg0 = sCmd;

	IVarPtr pVar = Engine::GetInstance()->VarManager()->GetVarByName(bMultipleArgs ? sArg0.c_str() : sCmd.c_str());

	if( pVar ) {
		switch( pVar->GetType() ) {
			case MVar::CVAR_INT: 
				{ 
					if( bMultipleArgs ) pVar->SetValueInt(atoi(sArg1.c_str()));
					Echo("\"%s\" (int) = %i",sArg0.c_str(),pVar->GetValueInt());
				} break;
			case MVar::CVAR_BOOL:
				{
					if( bMultipleArgs ) {
						if( sArg1[0] == '0' ) pVar->SetValueBool(false);
						else if( sArg1[0] == '1' ) pVar->SetValueBool(true);
						else {
							Echo("Invalid boolean value...");
							break;
						}
					}
					Echo("\"%s\" (bool) = %i",sArg0.c_str(),pVar->GetValueBool());
				} break;
			case MVar::CVAR_FLOAT:
				{
					if( bMultipleArgs ) pVar->SetValueFloat((float)atof(sArg1.c_str()));
					else Echo("\"%s\" (float) = %f",sArg0.c_str(),pVar->GetValueFloat());
				} break;
			
			default: break;
		}
	} else Echo("Error: \"%s\" is not a valid variable or command.",sArg0.c_str());
}

bool MConsole::GetActive( void )
{
	return m_bActive->GetValueBool();
}

float MConsole::GetDepth( void )
{
	// We want this on top of all layers.
	return 0.0f;
}

void MConsole::Render( void )
{
	if( m_bToggleAnimDown ) {
		if( m_iScrollPoint < m_iPositionYon->GetValueInt() ) {
			m_iScrollPoint += m_iScrollFactor->GetValueInt();
			m_bToggling = true;
		}
		else {
			m_bToggleAnimDown = false;
			m_bToggling = false;
		}
	} if( m_bToggleAnimUp ) {
		if( m_iScrollPoint > m_iPositionYoff->GetValueInt() ) {
			m_iScrollPoint -= m_iScrollFactor->GetValueInt();
			m_bToggling = true;
		}
		else {
			m_bToggleAnimUp = false;
			m_bActive->SetValueBool(false);
			m_bToggling = false;
		}
	}
	
	for( int i = 0; i < 5; i++ ) {
		if( m_BackBuffer[i].c_str() ) {
			m_Font->SetPosition(m_iPositionX->GetValueInt(),m_iScrollPoint - (i * m_iFontSpacing->GetValueInt()));
			m_Font->SetText(m_BackBuffer[(m_BackBuffer.size() - 1) - i]);
			m_Font->Render();
		}
	}

	m_Font->SetPosition(m_iPositionX->GetValueInt(),m_iScrollPoint + m_iFontSpacing->GetValueInt());
	m_Font->SetText(m_sCurrentBuffer);
	m_Font->Render();
}

void MConsole::UpdateInput( const Uint8* pKeyState, const int iKey, const bool bKeyDown )
{
	// Toggle the console.
	if( pKeyState[SDLK_F5] && !m_bToggling ) {
		if( m_bActive->GetValueBool() ) {
			m_bToggleAnimUp = true;
			Engine::GetInstance()->InputManager()->SetKeyRepeat(1,1);
		} else {
			m_bActive->SetValueBool(true);
			m_bToggleAnimDown = true;
			Engine::GetInstance()->InputManager()->SetKeyRepeat(500,SDL_DEFAULT_REPEAT_INTERVAL);
		}
	}

	if( m_bActive->GetValueBool() && bKeyDown ) {
		bool bShiftMod = ( pKeyState[SDLK_LSHIFT] || pKeyState[SDLK_RSHIFT] ) ? true : false;
		switch( iKey ) {
			case SDLK_a: { m_sCurrentBuffer.append((bShiftMod == true) ? "A" : "a"); } break;
			case SDLK_b: { m_sCurrentBuffer.append((bShiftMod == true) ? "B" : "b"); } break;
			case SDLK_c: { m_sCurrentBuffer.append((bShiftMod == true) ? "C" : "c"); } break;
			case SDLK_d: { m_sCurrentBuffer.append((bShiftMod == true) ? "D" : "d"); } break;
			case SDLK_e: { m_sCurrentBuffer.append((bShiftMod == true) ? "E" : "e"); } break;
			case SDLK_f: { m_sCurrentBuffer.append((bShiftMod == true) ? "F" : "f"); } break;
			case SDLK_g: { m_sCurrentBuffer.append((bShiftMod == true) ? "G" : "g"); } break;
			case SDLK_h: { m_sCurrentBuffer.append((bShiftMod == true) ? "H" : "h"); } break;
			case SDLK_i: { m_sCurrentBuffer.append((bShiftMod == true) ? "I" : "i"); } break;
			case SDLK_j: { m_sCurrentBuffer.append((bShiftMod == true) ? "J" : "j"); } break;
			case SDLK_k: { m_sCurrentBuffer.append((bShiftMod == true) ? "K" : "k"); } break;
			case SDLK_l: { m_sCurrentBuffer.append((bShiftMod == true) ? "L" : "l"); } break;
			case SDLK_m: { m_sCurrentBuffer.append((bShiftMod == true) ? "M" : "m"); } break;
			case SDLK_n: { m_sCurrentBuffer.append((bShiftMod == true) ? "N" : "n"); } break;
			case SDLK_o: { m_sCurrentBuffer.append((bShiftMod == true) ? "O" : "o"); } break;
			case SDLK_p: { m_sCurrentBuffer.append((bShiftMod == true) ? "P" : "p"); } break;
			case SDLK_q: { m_sCurrentBuffer.append((bShiftMod == true) ? "Q" : "q"); } break;
			case SDLK_r: { m_sCurrentBuffer.append((bShiftMod == true) ? "R" : "r"); } break;
			case SDLK_s: { m_sCurrentBuffer.append((bShiftMod == true) ? "S" : "s"); } break;
			case SDLK_t: { m_sCurrentBuffer.append((bShiftMod == true) ? "T" : "t"); } break;
			case SDLK_u: { m_sCurrentBuffer.append((bShiftMod == true) ? "U" : "u"); } break;
			case SDLK_v: { m_sCurrentBuffer.append((bShiftMod == true) ? "V" : "v"); } break;
			case SDLK_w: { m_sCurrentBuffer.append((bShiftMod == true) ? "W" : "w"); } break;
			case SDLK_x: { m_sCurrentBuffer.append((bShiftMod == true) ? "X" : "x"); } break;
			case SDLK_y: { m_sCurrentBuffer.append((bShiftMod == true) ? "Y" : "y"); } break;
			case SDLK_z: { m_sCurrentBuffer.append((bShiftMod == true) ? "Z" : "z"); } break;
			case SDLK_0: { m_sCurrentBuffer.append((bShiftMod == true) ? ")" : "0"); } break;
			case SDLK_1: { m_sCurrentBuffer.append((bShiftMod == true) ? "!" : "1"); } break;
			case SDLK_2: { m_sCurrentBuffer.append((bShiftMod == true) ? "\"" : "2"); } break;
			case SDLK_3: { m_sCurrentBuffer.append((bShiftMod == true) ? "�" : "3"); } break;
			case SDLK_4: { m_sCurrentBuffer.append((bShiftMod == true) ? "$" : "4"); } break;
			case SDLK_5: { m_sCurrentBuffer.append((bShiftMod == true) ? "%" : "5"); } break;
			case SDLK_6: { m_sCurrentBuffer.append((bShiftMod == true) ? "^" : "6"); } break;
			case SDLK_7: { m_sCurrentBuffer.append((bShiftMod == true) ? "&" : "7"); } break;
			case SDLK_8: { m_sCurrentBuffer.append((bShiftMod == true) ? "*" : "8"); } break;
			case SDLK_9: { m_sCurrentBuffer.append((bShiftMod == true) ? "(" : "9"); } break;
			case SDLK_MINUS: { m_sCurrentBuffer.append((bShiftMod == true) ? "_" : "-"); } break;
			case SDLK_PERIOD: { m_sCurrentBuffer.append("."); } break;
			case SDLK_SPACE: { m_sCurrentBuffer.append(" "); } break;
			
			// Some special cases.
			case SDLK_RETURN: 
				{ 
					if( m_sCurrentBuffer.length() > 2) {
						Execute(m_sCurrentBuffer.c_str()+2);
						m_CmdHistory.push_back(m_sCurrentBuffer.c_str()+2);
						m_iHistoryIndex = (int)m_CmdHistory.size() - 1;
						m_sCurrentBuffer = "> ";
					}
				} break;
			case SDLK_BACKSPACE: 
				{ 
					if( m_sCurrentBuffer.length() > 2 )
						m_sCurrentBuffer.erase(m_sCurrentBuffer.end() - 1); 		
				} break;
			case SDLK_UP:
				{
					if( m_iHistoryIndex < 0) {
						m_iHistoryIndex = (int)m_CmdHistory.size() - 1;
						m_sCurrentBuffer = "> ";
						break;
					} else if( m_iHistoryIndex > (int)m_CmdHistory.size() - 1 ) {
						m_iHistoryIndex = 0;
						m_sCurrentBuffer = "> ";
						break;
					}
					
					m_sCurrentBuffer = "> ";
					m_sCurrentBuffer.append(m_CmdHistory[m_iHistoryIndex]);
					--m_iHistoryIndex;
				} break;
			case SDLK_DOWN:
				{
					if( m_iHistoryIndex > (int)m_CmdHistory.size() - 1 ) {
						m_iHistoryIndex = 0;
						m_sCurrentBuffer = "> ";
						break;
					} else if( m_iHistoryIndex < 0) {
						m_iHistoryIndex = (int)m_CmdHistory.size() - 1;
						m_sCurrentBuffer = "> ";
						break;
					}
					
					m_sCurrentBuffer = "> ";
					m_sCurrentBuffer.append(m_CmdHistory[m_iHistoryIndex]);
					++m_iHistoryIndex;
				} break;

			default: break;
		}
	}
}
