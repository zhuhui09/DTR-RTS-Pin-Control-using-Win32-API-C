	
	//====================================================================================================//
	// Program to open the Serial port and control the RTS and DTR pins (SET and CLEAR ) using Win32 API  //
	// EscapeCommFunction() is used to SET and CLEAR the RTS and DTR pins                                 //
	// Baud Rate,Data Rate etc are not set since no serial Communication takes place                      //
	//====================================================================================================//
	
	//====================================================================================================//
	// www.xanthium.in										                                              //
	// Copyright (C) 2015 Rahul.S                                                                         //
	//====================================================================================================//
	
	//====================================================================================================//
	// Compiler/IDE  :	Microsoft Visual Studio Express 2013 for Windows Desktop(Version 12.0)            //
	//               :  gcc 4.8.1 (MinGW)                                                                 //
	// Library       :  Win32 API,windows.h,                                                              //
	// Commands      :  gcc -o SerialPort_RTS_DTR SerialPort_RTS_DTR.c                                    //
	// OS            :	Windows(Windows 7)                                                                //
	// Programmer    :	Rahul.S                                                                           //
	// Date	         :	20-January-2015                                                                   //
	//====================================================================================================//
	
	//====================================================================================================//
	// Sellecting the COM port Number                                                                     //
    //----------------------------------------------------------------------------------------------------//
    // Use "Device Manager" in Windows to find out the COM Port number allotted to USB2SERIAL converter-  // 
    // -in your Computer and substitute in the  CreateFile()                                              //
	//                                                                                                    //
	// for eg:-                                                                                           //
	// If your COM port number is COM32 in device manager(will change according to system)                //
	// then                                                                                               //
	//			    CreateFile("\\\\.\\COM32", , , , );                                                   //
	//====================================================================================================//
	
	#include <Windows.h>
	#include <stdio.h>
	#include <string.h>
	void main(void)
	{
		HANDLE hComm;                          // Handle to the Serial port
		char  ComPortName[] = "\\\\.\\COM24";  // Name of the Serial port(May Change) to be opened,
		BOOL  Status;

		printf("\n\n +------------------------------------------------------------------+");
		printf("\n | Program to Set and Clear the RTS and DTR lines of PC Serial Port |");
		printf("\n | Using Win 32 API                                                 |");
		printf("\n | Please Set the Serial port to use in Source file eg \\\\.\\COM32    |");
	 	printf("\n +------------------------------------------------------------------+");


		//-------------------------- Opening the Serial Port------------------------------------//
		hComm = CreateFile( ComPortName,                  // Name of the Port to be Opened
							GENERIC_READ | GENERIC_WRITE, // Read/Write Access
							0,                            // No Sharing, ports cant be shared
							NULL,                         // No Security
						    OPEN_EXISTING,                // Open existing port only
							0,                            // Non Overlapped I/O
							NULL);                        // Null for Comm Devices

		if (hComm == INVALID_HANDLE_VALUE)
			printf("\n   Error! - Port %s can't be opened", ComPortName);
		else
			printf("\n   Port %s Opened \n", ComPortName);

		//-------------------------Manipulating RTS line of  PC Serial Port-------------------------//

		Status = EscapeCommFunction(hComm, SETRTS); //Setting the RTS line using EscapeCommFunction();
		
		if (Status == FALSE)
			printf("\n   Error! RTS not Set");
		else
			printf("\n   RTS Set,\n   Press Any Key to Continue.......");
		
		_getch(); // Wait for user input

		Status = EscapeCommFunction(hComm, CLRRTS);//Clearing the RTS line using EscapeCommFunction();

		if (Status == FALSE)
			printf("\n   Error! RTS not Cleared");
		else
			printf("\n   RTS Cleared,\n   Press Any Key to Continue.......");

		_getch();

		//-------------------------Manipulating DTR line of  PC Serial Port-------------------------//

		Status = EscapeCommFunction(hComm, SETDTR); //Setting the DTR line using EscapeCommFunction();

		if (Status == FALSE)
			printf("\n   Error! DTR not Set");
		else
			printf("\n   DTR Set,\n   Press Any Key to Continue.......");

		_getch();

		Status = EscapeCommFunction(hComm, CLRDTR);//Clearing the DTR line using EscapeCommFunction();

		if (Status == FALSE)
			printf("\n   Error! DTR not Cleared");
		else
			printf("\n   DTR Cleared,\n   Press Any Key to Continue.......");

		_getch(); 

		CloseHandle(hComm);//Closing the Serial Port

		printf("\n\n   Serial Port Closed ,Press Any Key to Exit");
		printf("\n +------------------------------------------------------------------+");
		_getch();
	}