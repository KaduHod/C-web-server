#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

int main()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) 
	{
		std::cout << "Falha ao criar socket. Erro numero: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}	

	std::cout << "Socket criado com sucesso" << std::endl;
	

	sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = INADDR_ANY;
	std::cout << INADDR_ANY << std::endl;
	std::cout << EXIT_FAILURE << std::endl;
	std::cout << AF_INET  << std::endl;
	sockaddr.sin_port = htons(9999);

	if (bind(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) <0 ) {
		std::cout << "Falha ao ligar porta 9999. Erro número" << errno << std::endl;
		exit(EXIT_FAILURE);
	}

	std::cout << "Servidor ligado a porta 9999" << std::endl;


	if(listen(sockfd, 10) < 0) {
		std::cout << "Erro ao escutar socket, Erro número: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

	std::cout << "Socket escutando" << std::endl;
	 

	auto addrlen = sizeof(sockaddr);
	int connection = accept(sockfd, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
	if(connection < 0) {
		std::cout << "Falha ao criar conexão. Erro número: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

	std::cout << "Conexão criada" << std::endl;
	

	char buffer[100];
	auto bytesRead = read(connection, buffer, 100);
	std::cout << "The message was: " << buffer;

	std::string response = "Good talking to you\n";
	send(connection, response.c_str(),  response.size(), 0);

	close(connection);
	close(sockfd);
}

