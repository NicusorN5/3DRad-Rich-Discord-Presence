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


extern DiscordRichPresence presence;
extern DiscordEventHandlers events;
extern DiscordEvent event;
extern DiscordUser* some_person_that_might_join;

extern char* AppID;
extern char* SteamID;