// WC.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "TakeMultiScreenShot.h"
#include "SetWallpaper.h"
#include "GetSystemInfo.h"
#include "KeyLogger.h"
using namespace std;

int main()
{
    printf("\t---------------------------------------------\n");
    printf("\t\t\tRunning WC v1.0\n");
    printf("\t---------------------------------------------\n");
    //TakeScreenshot();
    //SetBackgroundFromURL("http://t0.gstatic.com/licensed-image?q=tbn:ANd9GcTROLLYosETNJ2leQ8C5uIj4bsCdEC6GQ2XrCJGkCowkV5FDuDXu4ySmmXE2sRdUHhRD7Y8R3e3R0Cg8oTPIuE");
    //GetExternalIP();
    //StartLogger();

	ShowWindow(GetConsoleWindow(), SW_SHOW);

	std::cout << GetDesktopDirectory() << std::endl;

	//ListDirContents("C:\\Users\\tomlo\\Pictures\\fpdf");
	//
	//std::string myText;
	//
	//// Read from the text file
	//std::ifstream MyReadFile("C:\\Users\\tomlo\\Pictures\\fpdf\\install.txt");
	//// Use a while loop together with the getline() function to read the file line by line
	//while (getline(MyReadFile, myText)) {
	//	// Output the text from the file
	//	std::cout << myText;
	//}
	//if (ControlledFolderAccessEnabled == 0) {
	//	std::ofstream outfile;
	//	outfile.open("C:\\Users\\tomlo\\Pictures\\fpdf\\install.txt", std::ios_base::app); // append instead of overwrite
	//	outfile << "Data";
	//}

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
