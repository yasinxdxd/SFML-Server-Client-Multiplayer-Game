#include <Server.h>

int main(int argc, char* argv[])
{									//IF CLIENT AND SERVER ON SAME COMPUTER:::::
	Server GameServer(50000);		// different port for Client side.
									// client send to the server's recieving port
									// server send to the clients's recieving port
									// client recieve from the server's sending port
									// server recieve to the clients's sending port

	while (true)
	{
		GameServer.Run();
	}


	return 0;
}