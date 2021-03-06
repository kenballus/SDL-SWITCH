/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2014 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
	  claim that you wrote the original software. If you use this software
	  in a product, an acknowledgment in the product documentation would be
	  appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
	  misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "SDL_config.h"

#include "SDL_error.h"
#include "SDL_thread.h"
#include "../SDL_systhread.h"
#include "../SDL_thread_c.h"
#include <switch.h>

#define STACKSIZE       (4 * 1024)

void ThreadEntry(void *arg)
{
	SDL_RunThread(arg);
//	while(1) SDL_Delay(-1); // this is for RyujiNX
}

int SDL_SYS_CreateThread(SDL_Thread *thread, void *args)
{
	s32 priority = 0x2B;
	Thread *tempThread;
	void* stack_mem;
	int rc=-1;
	
	tempThread = malloc(sizeof(Thread));
	stack_mem = malloc(STACKSIZE); // I think this is a memory leak.
	
/*
	// Set priority of new thread higher than the current thread 
	svcGetThreadPriority(&priority, CURRENT_KTHREAD); //  0x2C is the usual priority of the main thread.
	if(priority>0x0) priority--;
*/
	rc = threadCreate(tempThread, ThreadEntry, args, stack_mem, STACKSIZE, priority, -2);
	if (R_FAILED(rc))
	{
		SDL_SetError("Create Thread failed");
		return(-1);
	}
	
	rc = threadStart(tempThread);
	if (R_FAILED(rc))
	{
		SDL_SetError("Start Thread failed");
		return(-1);
	}

	thread->handle = tempThread;
	
	thread->threadid = (int) tempThread->handle;
 
	return 0;
}

void SDL_SYS_SetupThread(void)
{
	 //Nothing, probably
}

Uint32 SDL_ThreadID(void)
{
	return (int) armGetTls();
}

void SDL_SYS_WaitThread(SDL_Thread *thread)
{

	if(thread->handle) {
		threadWaitForExit((Thread *) thread->handle);
		threadClose((Thread *) thread->handle);
		free(thread);
		thread->handle = NULL;
	}	

}

void SDL_SYS_KillThread(SDL_Thread *thread)
{
	if(thread->handle)
	{
//		threadPause((Thread *) thread->handle);
		threadClose((Thread *) thread->handle);
		free(thread);
		thread->handle = NULL;
	}
}

