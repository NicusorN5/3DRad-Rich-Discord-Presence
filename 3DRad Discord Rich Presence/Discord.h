#pragma once

#include "Externals.h"
#include <time.h>

#define DLL_EXPORT __declspec(dllexport)

//Initialization related functions
/*Sets the application ID used by Discord*/
void DLL_EXPORT SetAppID(float* args);
/*Sets the steam ID if needed.*/
void DLL_EXPORT SetSteamID(float* args);
/*Gets an integer in args[0] and some text regarding the lastest event.*/
void DLL_EXPORT GetLastestEvent(float* args);

//Presence related functions
/*Set state details*/
void DLL_EXPORT SetState(float* args);
/*Set presence details.*/
void DLL_EXPORT SetDetails(float* args);
/*Sets the starting timestamp.*/
void DLL_EXPORT SetStartTimestamp(float* args);
/*Sets the ending timestamp. Uses UNIX format? */
void DLL_EXPORT SetEndTimestamp(float* args);
/*Sets the large image*/
void DLL_EXPORT SetLargeImageKey(float* args);
/*Sets the large image text*/
void DLL_EXPORT SetLargeImageText(float* args);
/*Sets the small image*/
void DLL_EXPORT SetSmallImageKey(float* args);
/*Sets the text for the small image*/
void DLL_EXPORT SetSmallImageText(float* args);
/*Sets the party identifier (ID)*/
void DLL_EXPORT SetPartyID(float* args);
/*Sets the current party size*/
void DLL_EXPORT SetPartySize(float* args);
/*Sets the maximum party size*/
void DLL_EXPORT SetPartyMax(float* args);
/*Sets the match secret*/
void DLL_EXPORT SetMatchSecret(float* args);
/*Sets the join secret*/
void DLL_EXPORT SetJoinSecret(float* args);
/*Sets the spectate secret*/
void DLL_EXPORT SetSpectateSecret(float* args);

//Stopping related functions
/*Stops the presence.*/
void DLL_EXPORT Shutdown(float* args);

//Other helpfull functions
void DLL_EXPORT TimeNow(float* args);

//Internal functions
/*Taken from 3DRadSpace Extender
Link: https://github.com/NicusorN5/3D_Rad_Extender_Lib/wiki/ParseStringFromFloatArray
Converts a float* to a char* */
char* ParseStringFromFloatArray(float* args);

size_t WriteStringToFloatArray(float* args, char* string, int offset);

void e_ready(const DiscordUser* request);
void e_disconnected(int errorCode, const char* message);
void e_errored(int errorCode, const char* message);
void e_joinGame(const char* joinSecret);
void e_spectateGame(const char* spectateSecret);
void e_joinRequest(const DiscordUser* request);