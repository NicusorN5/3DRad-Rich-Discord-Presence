#include "pch.h"
#include "Discord.h"

void DLL_EXPORT SetAppID(float* args)
{
	AppID = ParseStringFromFloatArray(args); //No need to delete since we store the reference in AppID;
}

void DLL_EXPORT SetSteamID(float* args)
{
	SteamID = ParseStringFromFloatArray(args);
}
void DLL_EXPORT GetLastestEvent(float* args)
{
	
}
void DLL_EXPORT SetState(float* args)
{
	presence.state = ParseStringFromFloatArray(args);
}

void DLL_EXPORT SetDetails(float* args)
{
	presence.details = ParseStringFromFloatArray(args);
}

void DLL_EXPORT SetStartTimestamp(float* args)
{
	presence.startTimestamp = args[0];
}

void DLL_EXPORT SetEndTimestamp(float* args)
{
	presence.endTimestamp = args[0];
}

void DLL_EXPORT SetLargeImageKey(float* args)
{
	presence.largeImageKey = ParseStringFromFloatArray(args);
}

void DLL_EXPORT SetLargeImageText(float* args)
{
	presence.largeImageText = ParseStringFromFloatArray(args);
}

void DLL_EXPORT SetSmallImageKey(float* args)
{
	presence.smallImageKey = ParseStringFromFloatArray(args);
}

void DLL_EXPORT SetSmallImageText(float* args)
{
	presence.smallImageText = ParseStringFromFloatArray(args);
}

void DLL_EXPORT SetPartyID(float* args)
{
	presence.partyId = ParseStringFromFloatArray(args);
}

void DLL_EXPORT SetPartySize(float* args)
{
	presence.partySize = args[0];
}

void DLL_EXPORT SetPartyMax(float* args)
{
	presence.partyMax = args[0];
}

void DLL_EXPORT SetMatchSecret(float* args)
{
	presence.matchSecret = ParseStringFromFloatArray(args);
}

void DLL_EXPORT SetJoinSecret(float* args)
{
	presence.joinSecret = ParseStringFromFloatArray(args);
}

void DLL_EXPORT SetSpectateSecret(float* args)
{
	presence.spectateSecret = ParseStringFromFloatArray(args);
}

void DLL_EXPORT Shutdown(float* args)
{
	//Free memory to prevent leaks.
	if (AppID != nullptr) delete[] AppID;
	if (SteamID != nullptr) delete[] SteamID;
	if (some_person_that_might_join != nullptr) delete some_person_that_might_join;
	//Stop the presence.
	Discord_Shutdown();
}

char* ParseStringFromFloatArray(float* args)
{
	char* str = new char[16383]; //Oh yes, that's how many arguments the args[] can have, as documented in 3D Rad's documentation.
	int s;
	for (int i = 0; ; i++)
	{
		str[i] = (uint8_t)args[i];
		if (args[i] == 0)
		{
			s = i;
			break;
		}
	}
	char* ret = new char[s + 1];
	for (int i = 0; i <= s; i++)
	{
		ret[i] = str[i];
	}
	delete[] str;
	return ret; //This is prone to memory leaks if not used correctly.
	//Store the result in a separate string and then delete it.
}

void e_ready(const DiscordUser* request)
{
	event = DiscordEvent::Ready;
}

void e_disconnected(int errorCode, const char* message)
{
	event = DiscordEvent::Disconnected;
}

void e_errored(int errorCode, const char* message)
{
	event = DiscordEvent::Error;
}

void e_joinGame(const char* joinSecret)
{
	event = DiscordEvent::JoinGame;
}

void e_spectateGame(const char* spectateSecret)
{
	event = DiscordEvent::SpectateGame;
}

void e_joinRequest(const DiscordUser* request)
{
	event = DiscordEvent::JoinRequest;
	some_person_that_might_join = new DiscordUser;
	some_person_that_might_join->avatar = request->avatar;
	some_person_that_might_join->discriminator = request->discriminator;
	some_person_that_might_join->userId = request->userId;
	some_person_that_might_join->username = request->username;
}
