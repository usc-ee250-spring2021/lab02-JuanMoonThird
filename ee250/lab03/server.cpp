#include <iomanip>
#include <sstream>
#include <string>


using namespace std;


#include <arpa/inet.h>
#include <netdb.h>

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "socket.h"



int main()
{

	string port_number_string = "2020";
	int master_socket_fd = create_master_socket(port_number_string);
	for(;;){
		int newsockfd = my_accept(master_socket_fd);
		if(newsockfd == (-1)){
			break;
		}
		talk_to_client(newsockfd);
	}
	shutdown(master_socket_fd, SHUT_RDWR);
	close(master_socket_fd);
}