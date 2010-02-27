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

#ifndef _TASKMANAGER_H_
#define _TASKMANAGER_H_

#include "../Public/Public.h"
#include "../Interfaces/IVarManager.h"
#include "../Interfaces/ITask.h"

/// Fix me.
class MTaskManager : public noncopyable
{
public:

	MTaskManager( void );
	~MTaskManager( void );

	void Attach( ITaskPtr pTask, int iType );
	void InitTasks( void );
	void UpdateTasks( void );
	void KillTasks( void );
	void EarlyAbort( void );
	bool GetActive( void ) const;

	enum TaskType 
	{
		INPUT_TASK,
		LOGIC_TASK,
		RENDER_TASK
	};

private:

	bool m_bKilledTasks;
	bool m_bEarlyAbort;
	bool m_bActive;
	vector<pair<ITaskPtr,int>> m_TaskList;
	MTimer m_TaskTimer;
	MTimer m_FrameTimer;
	IVarPtr m_iFrameCap;
};

typedef shared_ptr<MTaskManager> MTaskManagerPtr;

#endif // _TASKMANAGER_H_
