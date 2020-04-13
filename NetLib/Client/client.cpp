#include <string>
#include <iostream>
#include "../NetLib/ISocketClient.h"

using namespace std;

#pragma comment(lib, "ws2_32.lib")

SOCKET client = 0;

int main()
{
	auto client = ISocketClient::create();

	client->onDisconnect = []() {
		cout << "disconnect" << endl;
	};

	client->onRecv = [&client](const char* data,int count) {
		cout << "recv data:" << data << endl;
		client->sendMessage("Thanks you!", 12);
	};

	bool s = client->connectServer("127.0.0.1", 6010);

	getchar();
	return 0;
}