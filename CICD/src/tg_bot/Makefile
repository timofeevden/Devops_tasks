all: build 

build: 
	rm -f bot_message 
	g++ tg_bot.cpp -o bot_message --std=c++14 -I/usr/local/include -lTgBot -lboost_system -lssl -lcrypto -lpthread 
