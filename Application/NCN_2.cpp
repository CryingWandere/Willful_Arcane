//_______________________________________________________________________________________________\\
//

#ifndef _DEBUG
#pragma comment( linker, "/subsystem:windows /ENTRY:mainCRTStartup" )
#endif

#include "application.hpp"

#include < Windows.h >

#include < stdexcept >
#include < iostream >

int main()
{
	try
	{
		int screenX = GetSystemMetrics( SM_CXSCREEN );
		int screenY = GetSystemMetrics( SM_CYSCREEN );

		Application app( screenX, screenY );

		app.run();
	}
	catch ( std::exception& e )
	{
		std::cout << "\nException called: " << e.what() << std::endl;
	}

	std::cin.clear();
	std::cin.ignore( 32767, '\n' );
	std::cin.get();

	return 0;
}
