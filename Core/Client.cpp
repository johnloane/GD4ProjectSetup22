#include "SocketWrapperPCH.hpp"

/*Client needs to offer the user a menu where can select
 *1. Echo
 *2. DateAndTime
 *3. Stats
 *4. Quit
 *Take the input from the user, send it to the server and listen and display the response from the server
 */

int main()
{
	SocketUtil::StaticInit();
	UDPSocketPtr client_socket = SocketUtil::CreateUDPSocket(INET);
	
}