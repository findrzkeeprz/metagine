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

#include "RenderTask.h"

MRenderTask::MRenderTask( void ) :
m_Screen(NULL),
m_bFontLibLoaded(false),
m_bShaderCompatible(true),
m_glCreateProgramObjectARB(NULL),
m_glDeleteObjectARB(NULL),
m_glCreateShaderObjectARB(NULL),
m_glShaderSourceARB(NULL),
m_glCompileShaderARB(NULL),
m_glGetObjectParameterivARB(NULL),
m_glAttachObjectARB(NULL),
m_glGetInfoLogARB(NULL),
m_glLinkProgramARB(NULL),
m_glUseProgramObjectARB(NULL),
m_glGetUniformLocationARB(NULL),
m_glUniform1fARB(NULL),
m_glUniform1iARB(NULL)
{
	printf(" -> MRenderTask object created.\n");
}

MRenderTask::~MRenderTask( void )
{
	printf(" -> MRenderTask object destructed.\n");
}

void MRenderTask::VInit( void )
{
	printf(" -> MRenderTask::VInit() called.\n");
	printf(" -> Initialising SDL subsystem.\n");

	m_iResolution[0] = 1024;
	m_iResolution[1] = 576;
	
	if( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) == -1 ) {
		printf(" -! ERROR initialising SDL.\n");
		return;
	} else if( ( m_Screen = SDL_SetVideoMode(m_iResolution[0],m_iResolution[1],32,SDL_OPENGL) ) == NULL ) {
		printf(" -! ERROR setting SDL video mode.\n");
		return;
	} else if( TTF_Init() == -1 ) {
		printf(" -! ERROR initialising SDL_TTF subsystem.\n");
		m_bFontLibLoaded = false;
		return;
	} else {
		m_bFontLibLoaded = true;
	}

	// Set the window caption.
	SDL_WM_SetCaption("Able in Space",NULL);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

	glEnable( GL_TEXTURE_2D );
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glViewport(0,0,m_iResolution[0],m_iResolution[1]);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f,m_iResolution[0],m_iResolution[1],0.0f,-1.0f,1.0f);
	glMatrixMode(GL_TEXTURE);
	glRotatef(180.0f,0.0f,0.0f,1.0f);
	glScalef(-1.0f,1.0f,1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//m_bShaderCompatible = InitExtensions();
	//if( m_bShaderCompatible ) InitShaders();
}

void MRenderTask::VKill( void )
{
	printf(" -> MRenderTask::VKill() called.\n");
	
	vector<IDrawablePtr>::iterator it = m_RenderQueue.begin();
	for( it = m_RenderQueue.begin(); it < m_RenderQueue.end(); ++it ) {
		if( *it ) {
			printf(" -> Releasing queued drawable object (0x%X).\n",(*it).get());
			it->reset();
		}
	}

	// Do some housekeeping.
	m_RenderQueue.clear();
	SDL_Quit();
	TTF_Quit();
}

void MRenderTask::VFrame( const float fDelta )
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	
	// Render all queued objects.
	//printf("=====BEGIN======\n");
	vector<IDrawablePtr>::reverse_iterator it;
	for( it = m_RenderQueue.rbegin(); it < m_RenderQueue.rend(); ++it ) {
	//	printf(" DEPTH: %f\n",(*it)->GetDepth());
		if( (*it)->GetActive() ) (*it)->Render();
	}
	//printf("=====END=======\n");
	
	SDL_GL_SwapBuffers();
	glFinish();
}


bool MRenderTask::FontLibLoaded( void )
{
	return m_bFontLibLoaded;
}

void MRenderTask::RegisterDrawable( IDrawablePtr pDrawable )
{
	if( !pDrawable ) {
		// Error msg here
		return;
	}

	// Push back and then re-sort the container based on depth.
	// Sprites need to be drawn back-to-front otherwise areas
	// with transparency will appear as the background colour.
	m_RenderQueue.push_back(IDrawablePtr(pDrawable));
	sort(m_RenderQueue.begin(),m_RenderQueue.end(),MRenderTask::SpriteSortFunc);
	
	printf(" -> Registered object (0x%X) with rendering queue.\n",pDrawable);
}

void MRenderTask::RemoveDrawable( IDrawablePtr pDrawable )
{
	vector<IDrawablePtr>::iterator it = m_RenderQueue.begin();
	while( it != m_RenderQueue.end() ) {
		if( (*it) && ((*it) == pDrawable) ) {
			printf(" -> Removing object (0x%X) from rendering queue.\n",pDrawable);
			it = m_RenderQueue.erase(it);
		} else ++it;
	}

	// Resort based on depth.
	sort(m_RenderQueue.begin(),m_RenderQueue.end(),MRenderTask::SpriteSortFunc);
}

bool MRenderTask::SpriteSortFunc( IDrawablePtr pData1, IDrawablePtr pData2 )
{
	return pData1->GetDepth() > pData2->GetDepth();
}

int MRenderTask::GetScreenWidth( void )
{
	return m_iResolution[0];
}

int MRenderTask::GetScreenHeight( void )
{
	return m_iResolution[1];
}

int MRenderTask::GetDrawableCount( void )
{
	return (int)m_RenderQueue.size();
}

bool MRenderTask::InitExtensions( void )
{
	printf(" -> MRenderTask::InitExtensions called\n");
	
	char* pszExtensions = (char*)glGetString(GL_EXTENSIONS);

	if( !MMiscFuncs::FindString("GL_ARB_shader_objects",pszExtensions) ||
		!MMiscFuncs::FindString("GL_ARB_shading_language_100",pszExtensions) ||
		!MMiscFuncs::FindString("GL_ARB_vertex_shader",pszExtensions) ||
		!MMiscFuncs::FindString("GL_ARB_fragment_shader",pszExtensions) ) {
			printf(" -! ERROR graphics hardware is not shader compatible!\n");
			return false;
	}

	m_glCreateProgramObjectARB = (PFNGLCREATEPROGRAMOBJECTARBPROC)SDL_GL_GetProcAddress("glCreateProgramObjectARB");
    m_glDeleteObjectARB = (PFNGLDELETEOBJECTARBPROC)SDL_GL_GetProcAddress("glDeleteObjectARB");
    m_glCreateShaderObjectARB = (PFNGLCREATESHADEROBJECTARBPROC)SDL_GL_GetProcAddress("glCreateShaderObjectARB");
    m_glShaderSourceARB = (PFNGLSHADERSOURCEARBPROC)SDL_GL_GetProcAddress("glShaderSourceARB");
    m_glCompileShaderARB = (PFNGLCOMPILESHADERARBPROC)SDL_GL_GetProcAddress("glCompileShaderARB");
    m_glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC)SDL_GL_GetProcAddress("glGetObjectParameterivARB");
    m_glAttachObjectARB = (PFNGLATTACHOBJECTARBPROC)SDL_GL_GetProcAddress("glAttachObjectARB");
    m_glGetInfoLogARB = (PFNGLGETINFOLOGARBPROC)SDL_GL_GetProcAddress("glGetInfoLogARB");
    m_glLinkProgramARB = (PFNGLLINKPROGRAMARBPROC)SDL_GL_GetProcAddress("glLinkProgramARB");
    m_glUseProgramObjectARB = (PFNGLUSEPROGRAMOBJECTARBPROC)SDL_GL_GetProcAddress("glUseProgramObjectARB");
    m_glGetUniformLocationARB = (PFNGLGETUNIFORMLOCATIONARBPROC)SDL_GL_GetProcAddress("glGetUniformLocationARB");
    m_glUniform1fARB = (PFNGLUNIFORM1FARBPROC)SDL_GL_GetProcAddress("glUniform1fARB");
    m_glUniform1iARB = (PFNGLUNIFORM1IARBPROC)SDL_GL_GetProcAddress("glUniform1iARB");

	if( !m_glCreateProgramObjectARB		||
		!m_glDeleteObjectARB			||
		!m_glCreateShaderObjectARB		||
		!m_glShaderSourceARB			||
		!m_glCompileShaderARB			||
		!m_glGetObjectParameterivARB	||
		!m_glAttachObjectARB			||
		!m_glGetInfoLogARB				||
		!m_glLinkProgramARB				||
		!m_glUseProgramObjectARB		||
		!m_glGetUniformLocationARB		||
		!m_glUniform1fARB				||
		!m_glUniform1iARB ) {
			printf(" -! ERROR graphics hardware is shader compatible but unable to obtain required pointers!\n");
			return false;
	}

	printf(" -> Shader support successfully initialised.\n");
	return true;
}

char* shader_frag_source = "uniform sampler2D tex; void main() \
						   { \
						   vec4 texel = texture2D(tex, gl_TexCoord[0].st); \
						   vec4 tempcolor = (texel.r + texel.g + texel.b + texel.a) / 4.0f; \
						   gl_FragColor = tempcolor; }\0";

/*char* shader_frag_source = "void main() \
						   { \
						   vec3 R0 = texture2DRect( S, gl_TexCoord[0].st ).rgb; \
						   gl_FragColor = vec4( mix( vec3( dot( R0, vec3( 0.2125, 0.7154, 0.0721 ) ) ),R0, T ), gl_Color.a ); }\0";*/

//char* shader_vert_source = "void main() { gl_TexCoord[0] = -gl_MultiTexCoord0; gl_Position = ftransform(); }\0";
char* shader_vert_source = "void main() { gl_TexCoord[0] = -gl_MultiTexCoord0; gl_Position = ftransform(); }\0";

void MRenderTask::InitShaders( void )
{
	m_iShaderProg = m_glCreateProgramObjectARB();
	m_iShaderVert = m_glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	m_iShaderFrag = m_glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	m_glShaderSourceARB(m_iShaderVert,1,(const char**)&shader_vert_source,NULL);
	m_glShaderSourceARB(m_iShaderFrag,1,(const char**)&shader_frag_source,NULL);
	m_glCompileShaderARB(m_iShaderVert);
	m_glCompileShaderARB(m_iShaderFrag);
	m_glAttachObjectARB(m_iShaderProg, m_iShaderVert);
	m_glAttachObjectARB(m_iShaderProg, m_iShaderFrag);
	m_glLinkProgramARB(m_iShaderProg);
	m_glUseProgramObjectARB(m_iShaderProg);
}