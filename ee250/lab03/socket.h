#include <iomanip>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;


#include <arpa/inet.h>
#include <netdb.h>

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>




void talk_to_client(int newsockfd);


void talk_to_server(int client_socket_fd);


void my_getaddrinfo(const string hostname_string, const string port_number_string, 
	struct addrinfo **result);


int create_stream_socket_for_server(const string hostname_string, const string port_number_string, 
	struct addrinfo **result);


int create_master_socket(const string port_number_string);


int my_connect(int client_socket_fd, const string hostname_string,
 const string port_number_string);


int create_client_socket_and_connect(const string hostname_string, const string port_number_string);

int my_accept(const int master_socket_fd);