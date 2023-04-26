#include <bits/stdc++.h>
#include <winsock2.h>
using namespace std;

#pragma comment(lib, "ws2_32.lib")
map<string, string> cache;

// void killPort(int port) {
//     // Find the PID of the process using the port
//     string command = "netstat -ano | findstr :"+to_string(port);
//     string output = "";
//     FILE* pipe = _popen(command.c_str(), "r");
//     char buffer[128];
//     while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
//         output += buffer;
//     }
//     _pclose(pipe);
//     size_t pos = output.find_last_of(" ");
//     int pid = stoi(output.substr(pos+1));

//     // Terminate the process
//     command = "taskkill /pid "+to_string(pid)+" /f";
//     system(command.c_str());
// }

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
            string resource(token);
            if (resource == "/")
            {
                string response;
                if (cache.count(resource) > 0)
                {
                    // Serve cached response
                    response = cache[resource];
                }
                else
                {
                    response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
                    string htmlData = "";
                    ifstream MyFile("index.html");
                    while (getline(MyFile, htmlData))
                    {
                        response = response.append(htmlData);
                    }
                    cache[resource] = response;
                }
                cout << response;
                iResult = send(clientSocket, response.c_str(), response.length(), 0);
                if (iResult == SOCKET_ERROR)
                {
                    cout << "send failed: " << WSAGetLastError() << endl;
                }
                cout << "Response sent" << endl;
            }
            if (resource == "/file1")
            {
                string response;
                if (cache.count(resource) > 0)
                {
                    // Serve cached response
                    response = cache[resource];
                }
                else
                {
                    response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
                    string htmlData = "";
                    ifstream MyFile("file1.html");
                    while (getline(MyFile, htmlData))
                    {
                        response = response.append(htmlData);
                    }
                    cache[resource] = response;
                }
                cout << response;
                iResult = send(clientSocket, response.c_str(), response.length(), 0);
                if (iResult == SOCKET_ERROR)
                {
                    cout << "send failed: " << WSAGetLastError() << endl;
                }
                cout << "Response sent" << endl;
            }
            else if (resource == "/file2")
            {
                string response;
                if (cache.count(resource) > 0)
                {
                    // Serve cached response
                    response = cache[resource];
                }
                else
                {
                    response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
                    string htmlData = "";
                    ifstream MyFile("file2.html");
                    while (getline(MyFile, htmlData))
                    {
                        response = response.append(htmlData);
                    }
                    cache[resource] = response;
                }
                cout << response;
                iResult = send(clientSocket, response.c_str(), response.length(), 0);
                if (iResult == SOCKET_ERROR)
                {
                    cout << "send failed: " << WSAGetLastError() << endl;
                }
                cout << "Response sent" << endl;
            }
            else if (resource == "/file3")
            {
                string response;
                if (cache.count(resource) > 0)
                {
                    // Serve cached response
                    response = cache[resource];
                }
                else
                {
                    response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
                    string htmlData = "";
                    ifstream MyFile("file3.html");
                    while (getline(MyFile, htmlData))
                    {
                        response = response.append(htmlData);
                    }
                    cache[resource] = response;
                }
                cout << response;
                iResult = send(clientSocket, response.c_str(), response.length(), 0);
                if (iResult == SOCKET_ERROR)
                {
                    cout << "send failed: " << WSAGetLastError() << endl;
                }
                cout << "Response sent" << endl;
            }
            else if (resource == "/exit")
            {
                    string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
                    string htmlData = "";
                    ifstream MyFile("exit.html");
                    while (getline(MyFile, htmlData))
                    {
                        response = response.append(htmlData);
                    }
                    iResult = send(clientSocket, response.c_str(), response.length(), 0);
            }
        }
    }
    closesocket(clientSocket);
    

}


void errorHandling()
{
    int error = WSAGetLastError();
    if (error == WSAEINTR)
    {
        throw runtime_error("Error: WSAEINTR - Interrupted function call");
    }
    else if (error == WSAEFAULT)
    {
        throw runtime_error("Error: WSAEFAULT - Bad address.");
    }
    else if (error == WSAEINVAL)
    {
        throw runtime_error("Error: WSAEINVAL - Invalid argument.");
    }
    else if (error == WSAEISCONN)
    {
        throw runtime_error("Error: WSAEISCONN - Socket is already connected.");
    }
    else if (error == WSAEBADF)
    {
        throw runtime_error("Error: WSAEBADF - File handle is not valid.");
    }
    else if (error == WSAETIMEDOUT)
    {
        throw runtime_error("Error: WSAETIMEDOUT - Connection timed out.");
    }
    else if (error == WSA_INVALID_PARAMETER)
    {
        throw runtime_error("Error: WSA_INVALID_PARAMETER - One or more parameters are invalid.");
    }
    else if (error == WSAENOTCONN)
    {
        throw runtime_error("Error: WSAENOTCONN - Socket is not connected.");
    }
    else if (error == WSAEADDRINUSE)
    {
        throw runtime_error("Error: WSAEADDRINUSE - Address already in use.");
    }
    else if (error == WSAEADDRNOTAVAIL)
    {
        throw runtime_error("Error: WSAEADDRNOTAVAIL - Cannot assign requested address.");
    }
    else if (error == WSAEACCES)
    {
        throw runtime_error("Error: WSAEACCES - Permission denied.");
    }
    else if (error == WSAEPROCLIM)
    {
        throw runtime_error("Error: WSAEPROCLIM - Too many processes.");
    }
    else if (error == WSANOTINITIALISED)
    {
        throw runtime_error("Error: WSANOTINITIALISED - Successful WSAStartup not yet performed.");
    }
    else if (error == WSASYSCALLFAILURE)
    {
        throw runtime_error("Error: WSASYSCALLFAILURE - System call failure.");
    }
    else
    {
        throw runtime_error("Unknown error: " + std::to_string(error));
    }
}

class WebServer
{
public:
    WebServer();
    ~WebServer();
    void start();
    void stop();

private:
    WSADATA wsaData;
    SOCKET listenSocket;
    int port;
    vector<thread> threads;

    void initialize();
    void bindAndListen();
    void acceptConnections();
    // void processClient(SOCKET clientSocket);
    void sendResponse(SOCKET clientSocket, const string &response);
};

WebServer::WebServer()
{
    port = 8080;
}

WebServer::~WebServer()
{
    stop();
}

void WebServer::start()
{
    initialize();
    bindAndListen();
    acceptConnections();
}

void WebServer::stop()
{
    closesocket(listenSocket);
    WSACleanup();
    for (auto &thread : threads)
    {
        thread.join();
    }
}

void WebServer::initialize()
{
    try
    {
        int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0)
        {
            cout << "Error in WSAStartup" << endl;
            cout << "WSAStartup failed: ";
            errorHandling();
            exit(1);
        }
    }
    catch (const exception &e)
    {
        cout << "WSAStartup failed: ";
        cout << e.what() << endl;
        WSACleanup();
        exit(1);
    }
}

void WebServer::bindAndListen()
{
    try
    {
        listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (listenSocket == INVALID_SOCKET)
        {
            cout << "socket failed: ";
            errorHandling();
            closesocket(listenSocket);
        }

        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        serverAddr.sin_port = htons(port);

        int iResult = bind(listenSocket, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
        if (iResult == SOCKET_ERROR)
        {
            cout << "bind failed: ";
            errorHandling();
            closesocket(listenSocket);
        }

        iResult = listen(listenSocket, SOMAXCONN);
        if (iResult == SOCKET_ERROR)
        {
            cout << "listen failed: ";
            errorHandling();
            closesocket(listenSocket);
        }
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
        WSACleanup();
        exit(1);
    }
    cout << "Web server running on port " << port << endl;
}

void WebServer::acceptConnections()
{
    try
    {
        while (true)
        {
            SOCKET clientSocket = accept(listenSocket, NULL, NULL);
            if (clientSocket == INVALID_SOCKET)
            {
                cout << "accept failed: ";
                errorHandling();
                closesocket(listenSocket);
            }
            threads.push_back(thread(handleClient, clientSocket));
        }
        for (auto &thread : threads)
        {
            thread.join();
        }
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
        WSACleanup();
        exit(1);
    }
}

// void WebServer::processClient(SOCKET clientSocket)
// {
//     char buffer[1024];
//     int iResult = recv(clientSocket, buffer, sizeof(buffer), 0);
//     if (iResult == SOCKET_ERROR)
//     {
//         cout << "recv failed: " << WSAGetLastError() << endl;
//         closesocket(clientSocket);
//         return;
//     }

//     buffer[iResult] = '\0';

//     cout << "Received data: " << iResult << endl;

//     char *token = strtok(buffer, " ");
//     if (token != NULL)
//     {
//         token = strtok(NULL, " ");
//         if (token != NULL)
//         {
//             if (strcmp(token, "/") == 0)
//             {
//                 string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
//                 string htmlData = "";
//                 ifstream MyFile("index.html");
//                 while (getline(MyFile, htmlData))
//                 {
//                     response = response.append(htmlData);
//                 }
//                 cout << response;
//                 iResult = send(clientSocket, response.c_str(), response.length(), 0);
//                 if (iResult == SOCKET_ERROR)
//                 {
//                     cout << "send failed: " << WSAGetLastError() << endl;
//                 }
//                 cout << "Response sent" << endl;
//             }
//             if (strcmp(token, "/file1") == 0)
//             {
//                 string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
//                 string htmlData = "";
//                 ifstream MyFile("file1.html");
//                 while (getline(MyFile, htmlData))
//                 {
//                     response = response.append(htmlData);
//                 }
//                 cout << response;
//                 iResult = send(clientSocket, response.c_str(), response.length(), 0);
//                 if (iResult == SOCKET_ERROR)
//                 {
//                     cout << "send failed: " << WSAGetLastError() << endl;
//                 }
//                 cout << "Response sent" << endl;
//             }
//             else if (strcmp(token, "/file2") == 0)
//             {
//                 string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
//                 string htmlData = "";
//                 ifstream MyFile("file2.html");
//                 while (getline(MyFile, htmlData))
//                 {
//                     response = response.append(htmlData);
//                 }
//                 cout << response;
//                 iResult = send(clientSocket, response.c_str(), response.length(), 0);
//                 if (iResult == SOCKET_ERROR)
//                 {
//                     cout << "send failed: " << WSAGetLastError() << endl;
//                 }
//                 cout << "Response sent" << endl;
//             }
//             else if (strcmp(token, "/file3") == 0)
//             {
//                 string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
//                 string htmlData = "";
//                 ifstream MyFile("file3.html");
//                 while (getline(MyFile, htmlData))
//                 {
//                     response = response.append(htmlData);
//                 }
//                 cout << response;
//                 iResult = send(clientSocket, response.c_str(), response.length(), 0);
//                 if (iResult == SOCKET_ERROR)
//                 {
//                     cout << "send failed: " << WSAGetLastError() << endl;
//                 }
//                 cout << "Response sent" << endl;
//             }
//         }
//     }

//     closesocket(clientSocket);
// }

// void WebServer::sendResponse(SOCKET clientSocket, const string &response)
// {
//     try
//     {
//         int iResult = send(clientSocket, response.c_str(), static_cast<int>(response.length()), 0);
//         if (iResult == SOCKET_ERROR)
//         {
//             cout << "send failed: ";
//             errorHandling();
//             closesocket(clientSocket);
//         }
//     }
//     catch (const exception &e)
//     {
//         cout << e.what() << endl;
//         WSACleanup();
//         exit(1);
//     }
// }

int main()
{
    WebServer server;
    server.start();
    return 0;
}