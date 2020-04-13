#include <string>
#include <iostream>
#include "../NetLib/SocketClient.h"

using namespace std;

#pragma comment(lib, "ws2_32.lib")

SOCKET client = 0;

int main()
{
	//auto client = SocketClient::create();
	//bool s = client->connectServer("127.0.0.1", 6010);
	getchar();
	return 0;
}