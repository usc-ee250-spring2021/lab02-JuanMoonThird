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


int main(){

	string host_string = "52.188.16.160", port_number_string = "48756";

	int client_socket_fd = create_client_socket_and_connect(host_string, port_number_string);

	if(client_socket_fd != (-1)){
		talk_to_server(client_socket_fd);
	}

}