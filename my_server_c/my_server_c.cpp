#include <memory>
#include <cmath>
#include <iostream>
using namespace std;
#include <socket.hpp>

int main() {
	try
	{		
		std::cout << "Server C..." << std::endl;
		std::cout << "Please pick a port number: ";
		unsigned short portNumber;
		std::cin >> portNumber;
		SocketBase sBase( SOCK_STREAM, IPPROTO_TCP) ;
		sBase.bind("127.0.0.1", portNumber);				
		std::cout << "Port " << portNumber <<  " is being used." << std::endl;

		sBase.listen();
		std::cout << "Waiting for an incomming connection" << std::endl;

		SocketBase sAccepted;
		sAccepted.accept( sBase );

		std::cout << "A client is now connected" << std::endl;

		float squareRoot;
		sAccepted.recv( &squareRoot );

		std::cout << squareRoot << " Recieved..." << std::endl;
		std::cout << "Finding the square root of " << squareRoot << std::endl;

		squareRoot = sqrtf(squareRoot);
		sAccepted.send(&squareRoot);

		
	}
	catch( std::runtime_error const& e ) {
	cerr << e.what() << endl;
	}
	catch( std::exception const& e ) {
		cerr << e.what() << endl;
	}
}