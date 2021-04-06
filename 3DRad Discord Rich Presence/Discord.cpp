#include "pch.h"
#include "Discord.h"

DiscordEventHandlers events;
DiscordEvent event;
DiscordUser* some_person_that_might_join = nullptr;

char* AppID = nullptr;
char* SteamID = nullptr;
bool Initialized = false;
char* Status = nullptr;
char* Details = nullptr;
char* LargeImageKey = nullptr;
char* SmallImageKey = nullptr;
char* LargeImageText = nullptr;
char* SmallImageText = nullptr;
char* PartyID = nullptr;
char* MatchSecret = nullptr;
char* JoinSecret = nullptr;
char* SpectateSecret = nullptr;
int64_t StartTimestamp = 0;
int64_t EndTimestamp = 0;
int PartySize = 0;
int PartyMax = 0;

void DLL_EXPORT Initialize(float* Args)
{
	if (!Initialized)
	{
		memset(&events, 0, sizeof(events));
		events.disconnected = e_disconnected;
		events.errored = e_errored;
		events.joinGame = e_joinGame;
		events.joinRequest = e_joinRequest;
		events.ready = e_ready;
		events.spectateGame = e_spectateGame;
	}
	Initialized = true;
}

void DLL_EXPORT Start(float* args)
{
	if (!Initialized) Initialize(nullptr);
	Discord_Initialize(AppID, &events, 1, SteamID);
}

void DLL_EXPORT UpdatePresence(float* args)
{
	DiscordRichPresence presence;
	memset(&presence, 0, sizeof(DiscordRichPresence));

	presence.state = (const char*)Status;
	presence.details = (const char*)Details;

	presence.joinSecret = JoinSecret;

	presence.largeImageKey = LargeImageKey;
	presence.largeImageText = LargeImageText;

	presence.matchSecret = MatchSecret;

	presence.partyId = PartyID; 
	presence.partyMax = PartyMax;
	presence.partySize = PartySize;

	presence.smallImageKey = SmallImageKey;
	presence.smallImageText = SmallImageText;

	presence.spectateSecret = SpectateSecret;

	presence.startTimestamp = StartTimestamp;
	presence.endTimestamp = EndTimestamp;

	Discord_UpdatePresence(&presence);
}

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
	args[0] = (float)event;
	if (event == DiscordEvent::JoinRequest)
	{
		int a = WriteStringToFloatArray(args, (char*)some_person_that_might_join->avatar, 1);
		int b = WriteStringToFloatArray(args, (char*)some_person_that_might_join->username, 1+a);
		int c = WriteStringToFloatArray(args, (char*)some_person_that_might_join->discriminator, 1 + b);
		WriteStringToFloatArray(args, (char*)some_person_that_might_join->userId,c );
	}
}
void DLL_EXPORT SetState(float* args)
{
	Status = ParseStringFromFloatArray(args);
}

void DLL_EXPORT SetDetails(float* args)
{
	Details = ParseStringFromFloatArray(args);
}

void DLL_EXPORT SetStartTimestamp(float* args)
{
	StartTimestamp = (int64_t)args[0];
}

void DLL_EXPORT SetEndTimestamp(float* args)
{
	EndTimestamp = (int64_t)args[0];
}

void DLL_EXPORT SetLargeImageKey(float* args)
{
	LargeImageKey = ParseStringFromFloatArray(args);
}

void DLL_EXPORT SetLargeImageText(float* args)
{
	LargeImageText = ParseStringFromFloatArray(args);
}

void DLL_EXPORT SetSmallImageKey(float* args)
{
	SmallImageKey = ParseStringFromFloatArray(args);
}

void DLL_EXPORT SetSmallImageText(float* args)
{
	SmallImageText = ParseStringFromFloatArray(args);
}

void DLL_EXPORT SetPartyID(float* args)
{
	PartyID = ParseStringFromFloatArray(args);
}

void DLL_EXPORT SetPartySize(float* args)
{
	PartySize = (int)args[0];
}

void DLL_EXPORT SetPartyMax(float* args)
{
	PartyMax = (int)args[0];
}

void DLL_EXPORT SetMatchSecret(float* args)
{
	MatchSecret = ParseStringFromFloatArray(args);
}

void DLL_EXPORT SetJoinSecret(float* args)
{
	JoinSecret = ParseStringFromFloatArray(args);
}

void DLL_EXPORT SetSpectateSecret(float* args)
{
	SpectateSecret = ParseStringFromFloatArray(args);
}

void DLL_EXPORT Shutdown(float* args)
{
	//Free memory to prevent leaks.
	if (AppID != nullptr) delete[] AppID;
	if (SteamID != nullptr) delete[] SteamID;
	if (Status != nullptr) delete[] Status;
	if (Details != nullptr) delete[] Details;
	if (some_person_that_might_join != nullptr) delete some_person_that_might_join;
	//Stop the presence.
	Discord_Shutdown();
}

void DLL_EXPORT TimeNow(float* args)
{
	args[0] = (float)time(nullptr);
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
	//Create the same sting but with less memory usage.
	char* ret = new char[s + 1];
	for (int i = 0; i <= s; i++)
	{
		ret[i] = str[i];
	}
	delete[] str;
	return ret; //This is prone to memory leaks if not used correctly.
	//Store the result in a separate string and then delete it.
}

size_t WriteStringToFloatArray(float* args, char* string, int offset)
{
	int i;
	for (i=0; string[i] != '\0' ; i++)
	{
		args[i + offset] = string[i];
	}
	return i;
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
	MessageBoxA(nullptr, message, "message", MB_OK);
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
