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

#include "TaskManager.h"
#include "ThirdParty.h"
#include "Engine.h"

MTaskManager::MTaskManager( void ) :
m_bKilledTasks(false),
m_bEarlyAbort(false),
m_bActive(false)
{
	m_FrameTimer.Start();
	m_TaskTimer.Start();

	m_iFrameCap = Engine::GetInstance()->VarManager()->CreateVar("i_framecap",0);
}

MTaskManager::~MTaskManager( void )
{
	if( !m_bKilledTasks )
		KillTasks();

	m_TaskList.clear();
}

void MTaskManager::Attach( ITaskPtr pTask, int iType )
{
	assert(pTask);
	assert(iType <= this->RENDER_TASK);

	m_TaskList.push_back(make_pair(pTask,iType));
}

void MTaskManager::InitTasks( void )
{
	vector<pair<ITaskPtr,int>>::iterator task;
	for( task = m_TaskList.begin(); task < m_TaskList.end(); ++task ) {
		(*task).first->VInit();
	}

	m_bActive = true;
}

void MTaskManager::UpdateTasks( void )
{
	float fDelta = m_TaskTimer.GetTicks();
	m_FrameTimer.Start();
	
	vector<pair<ITaskPtr,int>>::iterator task;
	for( task = m_TaskList.begin(); task < m_TaskList.end(); ++task ) {
		if( !m_bEarlyAbort ) {
			if( (*task).second == this->RENDER_TASK )
				m_TaskTimer.Start();
			(*task).first->VFrame(fDelta);
		} else {
			m_bActive = false;
			break;
		}
	}

	// Limit the engine tick rate.
	//int iFrameCap = m_iFrameCap->GetValueInt();
	//if( iFrameCap > 0 && m_FrameTimer.GetTicks() < ( 1000 / iFrameCap ) )
	//	SDL_Delay(( 1000 / iFrameCap ) - (int)m_FrameTimer.GetTicks());
}

void MTaskManager::KillTasks( void )
{
	vector<pair<ITaskPtr,int>>::iterator task;
	for( task = m_TaskList.begin(); task < m_TaskList.end(); ++task ) {
		(*task).first->VKill();
		(*task).first.reset();
	}

	m_bActive = false;
	m_bKilledTasks = true;
}

void MTaskManager::EarlyAbort( void )
{
	m_bEarlyAbort = true;
}

bool MTaskManager::GetActive( void ) const
{
	return m_bActive;
}


