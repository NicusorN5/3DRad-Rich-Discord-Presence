// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Discord.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
	events.disconnected = e_disconnected;
	events.errored = e_errored;
	events.joinGame = e_joinGame;
	events.joinRequest = e_joinRequest;
	events.ready = e_ready;
	events.spectateGame = e_spectateGame;
    return TRUE;
}

