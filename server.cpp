#include <bits/stdc++.h>
#include <winsock2.h>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

void handleClient(SOCKET clientSocket)
{
    char buffer[1024];
    int iResult = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (iResult == SOCKET_ERROR)
    {
        cout << "recv failed: " << WSAGetLastError() << endl;
        closesocket(clientSocket);
        return;
    }

    buffer[iResult] = '\0';

    cout << "Received data: " << iResult << endl;

    char *token = strtok(buffer, " ");
    if (token != NULL)
    {
        token = strtok(NULL, " ");
        if (token != NULL)
        {
            if (strcmp(token, "/") == 0)
            {
                string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
                string htmlData = "";
                ifstream MyFile("index.html");
                while (getline(MyFile, htmlData))
                {
                    response = response.append(htmlData);
                }
                cout << response;
                iResult = send(clientSocket, response.c_str(), response.length(), 0);
                if (iResult == SOCKET_ERROR)
                {
                    cout << "send failed: " << WSAGetLastError() << endl;
                }
                cout << "Response sent" << endl;
            }
            if (strcmp(token, "/file1") == 0)
            {
                string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
                string htmlData = "";
                ifstream MyFile("file1.html");
                while (getline(MyFile, htmlData))
                {
                    response = response.append(htmlData);
                }
                cout << response;
                iResult = send(clientSocket, response.c_str(), response.length(), 0);
                if (iResult == SOCKET_ERROR)
                {
                    cout << "send failed: " << WSAGetLastError() << endl;
                }
                cout << "Response sent" << endl;
            }
            else if (strcmp(token, "/file2") == 0)
            {
                string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
                string htmlData = "";
                ifstream MyFile("file2.html");
                while (getline(MyFile, htmlData))
                {
                    response = response.append(htmlData);
                }
                cout << response;
                iResult = send(clientSocket, response.c_str(), response.length(), 0);
                if (iResult == SOCKET_ERROR)
                {
                    cout << "send failed: " << WSAGetLastError() << endl;
                }
                cout << "Response sent" << endl;
            }
            else if (strcmp(token, "/file3") == 0)
            {
                string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
                string htmlData = "";
                ifstream MyFile("file3.html");
                while (getline(MyFile, htmlData))
                {
                    response = response.append(htmlData);
                }
                cout << response;
                iResult = send(clientSocket, response.c_str(), response.length(), 0);
                if (iResult == SOCKET_ERROR)
                {
                    cout << "send failed: " << WSAGetLastError() << endl;
                }
                cout << "Response sent" << endl;
            }
        }
    }
    closesocket(clientSocket);
}

int main()
{
    // Windows Sockets struct.
    WSADATA wsaData;

    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (iResult != 0)
    {
        cout << "Error in WSAStartup" << endl;
        cout << "WSAStartup failed: ";
        cout << iResult << endl;
        return 1;
    }

    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (listenSocket == INVALID_SOCKET)
    {
        int error = WSAGetLastError();
        switch (error)
        {
        case WSAEINTR:
            printf("Error: WSAEINTR - Interrupted function call\n");
            break;
        default:
            printf("Error: %d\n", error);
            break;
        }

        // Deleteling the socket
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(8080);

    iResult = bind(listenSocket, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
    if (iResult == SOCKET_ERROR)
    {
        cout << "bind failed: ";
        cout << WSAGetLastError() << endl;

        // Cleaning the socket
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    iResult = listen(listenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR)
    {
        cout << "listen failed: ";
        cout << WSAGetLastError() << endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    cout << "Web server running on port 8080" << endl;

    // Adding multithreading
    vector<thread> threads;

    while (true)
    {
        SOCKET clientSocket = accept(listenSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET)
        {
            cout << "accept failed: ";
            cout << WSAGetLastError() << endl;
            closesocket(listenSocket);
            WSACleanup();
            return 1;
        }

        cout << "Client connected" << endl;

        threads.push_back(thread(handleClient, clientSocket));
    }

    for (auto &thread : threads)
    {
        thread.join();
    }

    closesocket(listenSocket);
    WSACleanup();

    return 0;
}