#include <tgbot/tgbot.h>

int main(int argc, char* argv[]) {
	if (argc >= 3) {
		TgBot::Bot bot("6617076030:AAHiPvJ8FDVI2qCEvS1gXAmNikV1bSwK9QE");	//	need tocken
		bot.getApi().sendMessage(argv[1], argv[2]);		//	chat_id,	message-word
	}

	return 0;
}