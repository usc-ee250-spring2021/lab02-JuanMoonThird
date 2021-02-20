

#include "socket.h"

void talk_to_client(int newsockfd){

	char buf[1024];
	cout << "Enter message to client" << endl;
	string msg = "";
	cin >> msg;
	int bytes_received = read(newsockfd, buf, sizeof(buf));

	string client_message(buf);
	cout << client_message << endl;


	write(newsockfd, msg.c_str(), sizeof(msg));
	shutdown(newsockfd, SHUT_RDWR);
	close(newsockfd);
}


void talk_to_server(int client_socket_fd)
{
	cout << "Enter your message " << endl;
	string msg = "";
	cin >> msg;
	write(client_socket_fd, msg.c_str(), msg.length());
	char buf[1024];
	int bytes_received = read(client_socket_fd, buf, sizeof(buf));

	string server_message(buf);
	cout << server_message << endl;



	shutdown(client_socket_fd, SHUT_RDWR);
	close(client_socket_fd);
}



void my_getaddrinfo(const string hostname_string, const string port_number_string, 
	struct addrinfo **result)
{
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	hints.ai_flags = AI_NUMERICSERV | AI_ADDRCONFIG;
	if(getaddrinfo(hostname_string.c_str(),
		port_number_string.c_str(), &hints, result) != 0){
		perror("getaddrinfo() system call");
		exit(-1);
	}
}


int create_stream_socket_for_server(const string hostname_string, const string port_number_string, 
	struct addrinfo **result)
{
	int socket_fd = (-1);

	my_getaddrinfo(hostname_string, port_number_string, result);
	socket_fd = socket((*result)->ai_family, (*result)->ai_socktype, (*result)->ai_protocol);
	if(socket_fd == (-1)){
		perror("Socket() system call");
		exit(-1);
	}
	return socket_fd;
}



int create_master_socket(const string port_number_string)
{
	struct addrinfo* res = NULL;
	int socket_fd = (-1);
	int reuse_addr = 1;
	string hostname_string = "0.0.0.0";
	signal(SIGPIPE, SIG_IGN);

	socket_fd = create_stream_socket_for_server(hostname_string, port_number_string, &res);

	setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR,
		(void*)(&reuse_addr), sizeof(int));
	bind(socket_fd, res->ai_addr, res->ai_addrlen);
	freeaddrinfo(res);
	listen(socket_fd, 5);
	return socket_fd;
}



int my_connect(int client_socket_fd, const string hostname_string,
 const string port_number_string){

	struct sockaddr_in soc_address;
	memset(&soc_address, 0, sizeof(soc_address));

	if(hostname_string[0] >= '0' && hostname_string[0] <= '9'){
		soc_address.sin_addr.s_addr = inet_addr(hostname_string.c_str());
	}else{
		struct hostent *p_hostent = 
			gethostbyname(hostname_string.c_str());
			memcpy(&soc_address.sin_addr, p_hostent->h_addr, p_hostent->h_length);
	}

	soc_address.sin_family = AF_INET;
	soc_address.sin_port = htons((unsigned short)atoi(port_number_string.c_str()));


	return connect(client_socket_fd, (struct sockaddr*)&soc_address, sizeof(soc_address));
}

int create_client_socket_and_connect(const string hostname_string, const string port_number_string)
{
	int client_socket_fd = (-1);
	struct addrinfo* res = NULL;
	signal(SIGPIPE, SIG_IGN);
	my_getaddrinfo(hostname_string, port_number_string, &res);
	struct addrinfo *ai_ptr = NULL;

	for(ai_ptr = res; ai_ptr != NULL; ai_ptr = ai_ptr->ai_next){
		client_socket_fd = socket(ai_ptr->ai_family, ai_ptr->ai_socktype, ai_ptr->ai_protocol);
		if(client_socket_fd == (-1)){
			continue;
		}

		if(my_connect(client_socket_fd, hostname_string, port_number_string) != (-1)){
			break;
		}
		close(client_socket_fd);
		client_socket_fd = (-1);
	}
	freeaddrinfo(res);
	return client_socket_fd;
}

int my_accept(const int master_socket_fd){
	int newsockfd = (-1);
	while(newsockfd == (-1)){
		struct sockaddr_in client_addr;
		unsigned int clientlen = sizeof(client_addr);
		newsockfd = accept(master_socket_fd, (struct sockaddr*)(&client_addr), &clientlen);

		if(newsockfd == (-1)){
			if(errno == EINTR){
				continue;
			}
			return (-1);
		}
		break;
	}
	return newsockfd;
}