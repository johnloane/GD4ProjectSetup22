#include "SocketWrapperPCH.hpp"
#include "Client.hpp"
#include "Player.hpp"

/*Client needs to offer the user a menu where can select
 *1. Echo
 *2. DateAndTime
 *3. Stats
 *4. Quit
 *Take the input from the user, send it to the server and listen and display the response from the server
 */

int main()
{
	Player* alex = new Player();
	std::cout << sizeof(*alex) << std::endl;
	// SocketUtil::StaticInit();
	// UDPSocketPtr clientSocket = SocketUtil::CreateUDPSocket(INET);
	// clientSocket->SetNonBlockingMode(false);
	// Client::DoServiceLoop(clientSocket);
}

void Client::DoServiceLoop(UDPSocketPtr clientSocket)
{
	bool serviceRunning = true;
	string choice;
	char receiveBuffer[kMaxPacketSize];
	//the next 3 lines set the buffer to null
	char* begin = receiveBuffer;
	char* end = begin + sizeof(receiveBuffer);
	std::fill(begin, end, 0);
	SocketAddress senderAddress;
	int bytesReceived = 0;

	while (serviceRunning)
	{
		PrintOptions();
		GetChoice(choice);

		SendDataToServer(clientSocket, (char*)choice.c_str());
		ReceiveDataFromServer(clientSocket, receiveBuffer, senderAddress, bytesReceived, serviceRunning);
	}
}

void Client::PrintOptions()
{
	std::cout << "Please enter: " << std::endl;
	std::cout << "1) To use the EHCO service: " << std::endl;
	std::cout << "2) To use the DATEANDTIME service: " << std::endl;
	std::cout << "3) To use the STATS service: " << std::endl;
	std::cout << "4) To quit: " << std::endl;
}

void Client::GetChoice(string& choice)
{
	std::getline(std::cin, choice);
}

void Client::SendDataToServer(UDPSocketPtr clientSocket, char* input)
{
	SocketAddress serverAddress = SocketAddress(Client::ConvertIPToInt("127.0.0.1"), 50005);
	int bytesSent = clientSocket->SendTo(input, sizeof(input), serverAddress);
}

int Client::ConvertIPToInt(std::string ipString)
{
	int intIP = 0;
	for (int i = 0; i < ipString.length(); i++)
	{
		if (ipString[i] == '.')
		{
			ipString[i] = ' ';
		}
	}
	vector<int> arrayTokens;
	std::stringstream ss(ipString);
	int temp;
	while (ss >> temp)
	{
		arrayTokens.emplace_back(temp);
	}

	for (int i = 0; i < arrayTokens.size(); i++)
	{
		intIP += (arrayTokens[i] << ((3 - i) * 8));
	}
	return intIP;
}

void Client::ReceiveDataFromServer(UDPSocketPtr clientSocket, char* receiveBuffer, SocketAddress socketAddress, int bytesReceived, bool& serviceRunning)
{
	std::cout << sizeof(receiveBuffer) << std::endl;
	bytesReceived = clientSocket->ReceiveFrom(receiveBuffer, kMaxPacketSize, socketAddress);
	if (bytesReceived > 0)
	{
		ProcessReceivedData(receiveBuffer, bytesReceived, socketAddress, serviceRunning);
	}
}

void Client::ProcessReceivedData(char* receiveBuffer, int bytesReceived, SocketAddress socketAddress, bool& serviceRunning)
{
	char key[] = "QUIT";

	if (strcmp(key, receiveBuffer) == 0)
	{
		std::cout << "Server says we need to shut down...." << std::endl;
		serviceRunning = false;
	}

	std::cout << "Got " << bytesReceived << " from " << socketAddress.ToString() << std::endl;
	std::cout << "The message is: " << receiveBuffer << std::endl;
}