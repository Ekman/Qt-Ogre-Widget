#include <OgrePlatform.h>
#include "QOgreWindow.h"
#include "Game.h"
#include <QApplication>

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else

int main(int argc, char **argv)
#endif 
{
	QApplication app(argc, argv);

	// Load plugins
	// Set render system
	// root->initialize

	// Create the window and attach OGRE into it
	QOgreWindow window;
	window.show();

	// Create scene etc

	return app.exec();
}
