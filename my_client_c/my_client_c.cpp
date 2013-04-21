#include <iostream>
#include <socket.hpp>

int main() {
	try 
	{
		std::cout << "Client C..." << std::endl;
		std::cout << "Please the port number that was used for Server C: ";
		unsigned short portNumber;
		std::cin >> portNumber;
		SocketBase sBase( SOCK_STREAM, IPPROTO_TCP) ;
		sBase.connect("127.0.0.1", portNumber);				
		std::cout << "Client is now connected to Server C using port: " << portNumber << std::endl;

		std::cout << "Enter a number to be square rooted: ";
		float squareRoot;
		std:: cin >> squareRoot;
		float originalSR = squareRoot;
		std::cout << "Now square rooting " << squareRoot << std::endl;

		sBase.send<float>( &squareRoot );
		sBase.recv<float>( &squareRoot );

		std::cout << "The square root of " << originalSR << " is: " << squareRoot << std::endl;

	}
	catch( std::runtime_error const& e ) {
		std::cerr << e.what() << std::endl;
	}
	catch( std::exception const& e ) {
		std::cerr << e.what() << std::endl;
	}
}