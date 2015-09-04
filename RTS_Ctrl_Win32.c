	//====================================================================================================//
	//Program to open the Serial port and control the RTS pins (SET and CLEAR ) using Win32 API           //
	//EscapeCommFunction() is used to SET and CLEAR the RTS pin                                           //
	//====================================================================================================//
	
	//====================================================================================================//
	// www.xanthium.in										                                              //
	// Copyright (C) 2015 Rahul.S                                                                         //
	//====================================================================================================//
	
	//====================================================================================================//
	// Compiler/IDE  :	Microsoft Visual Studio Express 2013 for Windows Desktop(Version 12.0)            //
	//               :  gcc 4.8.1 (MinGW)                                                                 //
	// Library       :  Win32 API,windows.h,                                                              //
	// Commands      :  gcc -o RTS_Ctrl_Win32 RTS_Ctrl_Win32.c                                            //
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
	void main(void)
	{
		HANDLE hComm;                          // Handle to the Serial port
		char  ComPortName[] = "\\\\.\\COM24";  // Name of the Serial port(May Change) to be opened,
		BOOL  Status;
		
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
			printf("\n\n   RTS Set,\n\n   Press Any Key to Continue.......");
		
		_getch(); // Wait for user input

		Status = EscapeCommFunction(hComm, CLRRTS);//Clearing the RTS line using EscapeCommFunction();

		if (Status == FALSE)
			printf("\n   Error! RTS not Cleared");
		else
			printf("\n\n   RTS Cleared,\n\n   Press Any Key to Continue.......");

		_getch();
		
		CloseHandle(hComm);//Closing the Serial Port
	}