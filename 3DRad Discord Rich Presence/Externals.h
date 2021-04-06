#pragma once
#include "discord-rpc/win32-dynamic/include/discord_rpc.h"
#include "discord-rpc/win32-dynamic/include/discord_register.h"

enum DiscordEvent
{
	Ready = 1,
	Disconnected,
	Error,
	JoinGame,
	SpectateGame,
	JoinRequest
};

extern DiscordEventHandlers events;
extern DiscordEvent event;
extern DiscordUser* some_person_that_might_join;

extern char* AppID;
extern char* SteamID;
extern char* Status;
extern char* Details;
extern char* LargeImageKey;
extern char* SmallImageKey;
extern char* LargeImageText;
extern char* SmallImageText;
extern char* PartyID;
extern char* MatchSecret;
extern char* JoinSecret;
extern char* SpectateSecret;

extern int64_t StartTimestamp;
extern int64_t EndTimestamp;
extern int PartySize;
extern int PartyMax;
