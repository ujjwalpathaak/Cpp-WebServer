#include <bits/stdc++.h>
#include <winsock2.h>
// #include "211117.h"
// #include "211418.h"
// #include "211105.h"

using namespace std;

#pragma comment(lib, "ws2_32.lib")
map<string, string> cache;

class CClient
{
public:
    virtual void handleClient(SOCKET clientSocket, int iResult, string strResource) = 0;
};

class Home : public CClient
{
public:
    void handleClient(SOCKET clientSocket, int iResult, string strResource) override
    {
        string strResponse;
        if (cache.count(strResource) > 0)
        {
            strResponse = cache[strResource];
        }
        else
        {
            strResponse = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
            string strHTMLData = "";
            ifstream MyFile("index.html");
            while (getline(MyFile, strHTMLData))
            {
                strResponse = strResponse.append(strHTMLData);
            }
            cache[strResource] = strResponse;
        }

        iResult = send(clientSocket, strResponse.c_str(), strResponse.length(), 0);

        if (iResult == SOCKET_ERROR)
        {
            cout << "send failed: " << WSAGetLastError() << endl;
        }
        cout << "strResponse sent" << endl;
    }
};

class CFile1 : public CClient
{
public:
    void handleClient(SOCKET clientSocket, int iResult, string strResource) override
    {
        string strResponse;
        if (cache.count(strResource) > 0)
        {
            strResponse = cache[strResource];
        }
        else
        {
            strResponse = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
            string strHTMLData = "";
            ifstream MyFile("file1.html");
            while (getline(MyFile, strHTMLData))
            {
                strResponse = strResponse.append(strHTMLData);
            }
            cache[strResource] = strResponse;
        }
        iResult = send(clientSocket, strResponse.c_str(), strResponse.length(), 0);
        if (iResult == SOCKET_ERROR)
        {
            cout << "send failed: " << WSAGetLastError() << endl;
        }
        cout << "strResponse sent" << endl;
    }
};
class CFile2 : public CClient
{
public:
    void handleClient(SOCKET clientSocket, int iResult, string strResource) override
    {

        string strResponse;
        if (cache.count(strResource) > 0)
        {
            strResponse = cache[strResource];
        }
        else
        {
            strResponse = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
            string strHTMLData = "";
            ifstream MyFile("file2.html");
            while (getline(MyFile, strHTMLData))
            {
                strResponse = strResponse.append(strHTMLData);
            }
            cache[strResource] = strResponse;
        }
        iResult = send(clientSocket, strResponse.c_str(), strResponse.length(), 0);
        if (iResult == SOCKET_ERROR)
        {
            cout << "send failed: " << WSAGetLastError() << endl;
        }
        cout << "strResponse sent" << endl;
    }
};

class CFile3 : public CClient
{
public:
    void handleClient(SOCKET clientSocket, int iResult, string strResource) override
    {

        string strResponse;
        if (cache.count(strResource) > 0)
        {
            strResponse = cache[strResource];
        }
        else
        {
            strResponse = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
            string strHTMLData = "";
            ifstream MyFile("file3.html");
            while (getline(MyFile, strHTMLData))
            {
                strResponse = strResponse.append(strHTMLData);
            }
            cache[strResource] = strResponse;
        }
        iResult = send(clientSocket, strResponse.c_str(), strResponse.length(), 0);
        if (iResult == SOCKET_ERROR)
        {
            cout << "send failed: " << WSAGetLastError() << endl;
        }
        cout << "strResponse sent" << endl;
    }
};

class CExit : public CClient
{
public:
    void handleClient(SOCKET clientSocket, int iResult, string strResource) override
    {

        string strResponse = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
        string strHTMLData = "";
        ifstream MyFile("exit.html");
        while (getline(MyFile, strHTMLData))
        {
            strResponse = strResponse.append(strHTMLData);
        }
        iResult = send(clientSocket, strResponse.c_str(), strResponse.length(), 0);
    }
};

class CClientResponse : public CClient
{
public:
    void processClient2(SOCKET clientSocket)
    {
        char charBuffer[1024];
        int iResult = recv(clientSocket, charBuffer, sizeof(charBuffer), 0);
        if (iResult == SOCKET_ERROR)
        {
            cout << "recv failed: " << WSAGetLastError() << endl;
            closesocket(clientSocket);
            return;
        }

        charBuffer[iResult] = '\0';

        char *token = strtok(charBuffer, " ");
        if (token != NULL)
        {
            token = strtok(NULL, " ");
            if (token != NULL)
            {
                string strResource(token);
                if (strResource == "/")
                {
                    Home objHome;
                    objHome.handleClient(clientSocket, iResult, strResource);
                }
                if (strResource == "/file1")
                {
                    CFile1 objHome;
                    objHome.handleClient(clientSocket, iResult, strResource);
                }
                else if (strResource == "/file2")
                {
                    CFile2 objHome;
                    objHome.handleClient(clientSocket, iResult, strResource);
                }
                else if (strResource == "/file3")
                {
                    CFile3 objHome;
                    objHome.handleClient(clientSocket, iResult, strResource);
                }
                else if (strResource == "/exit")
                {
                    CExit objHome;
                    objHome.handleClient(clientSocket, iResult, strResource);
                }
                closesocket(clientSocket);
            }
        }
    }
    void handleClient(SOCKET clientSocket, int iResult, string strResource) { return; };
};

class CBase
{
public:
    virtual void start() = 0;
    virtual void stop() = 0;

private:
    virtual void initialize() = 0;
    virtual void bindAndListen() = 0;
    virtual void acceptConnections() = 0;
};

class Base2
{
public:
    virtual void errorHandling() = 0;
};

class CWebServer : public CBase
{
public:
    CWebServer();
    ~CWebServer();
    void start();
    void stop();

private:
    WSADATA wsaData;
    SOCKET listenSocket;
    int iPort;
    vector<thread> threads;

    void initialize();
    void bindAndListen();
    void acceptConnections();
};
class CErrorHandling : public Base2
{
public:
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
};

CWebServer::CWebServer()
{
    iPort = 8080;
}

CWebServer::~CWebServer()
{
    stop();
}

void CWebServer::start()
{
    initialize();
    bindAndListen();
    acceptConnections();
}

void CWebServer::stop()
{
    closesocket(listenSocket);
    WSACleanup();
    for (auto &thread : threads)
    {
        thread.join();
    }
}

void CWebServer::initialize()
{
    try
    {
        int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0)
        {
            cout << "Error in WSAStartup" << endl;
            cout << "WSAStartup failed: ";
            CErrorHandling objError;
            objError.errorHandling();
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

void CWebServer::bindAndListen()
{
    try
    {
        listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (listenSocket == INVALID_SOCKET)
        {
            cout << "socket failed: ";
            CErrorHandling objError;
            objError.errorHandling();
            closesocket(listenSocket);
        }

        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        serverAddr.sin_port = htons(iPort);

        int iResult = bind(listenSocket, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
        if (iResult == SOCKET_ERROR)
        {
            cout << "bind failed: ";
            CErrorHandling objError;
            objError.errorHandling();
            closesocket(listenSocket);
        }

        iResult = listen(listenSocket, SOMAXCONN);
        if (iResult == SOCKET_ERROR)
        {
            cout << "listen failed: ";
            CErrorHandling objError;
            objError.errorHandling();
            closesocket(listenSocket);
        }
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
        WSACleanup();
        exit(1);
    }
    cout << "Web objServer running on iPort " << iPort << endl;
}

void CWebServer::acceptConnections()
{
    try
    {
        while (true)
        {
            SOCKET clientSocket = accept(listenSocket, NULL, NULL);
            if (clientSocket == INVALID_SOCKET)
            {
                cout << "accept failed: ";
                CErrorHandling objError;
                objError.errorHandling();
                closesocket(listenSocket);
            }
            CClientResponse myObj;
            threads.push_back(thread(&CClientResponse::processClient2, &myObj, clientSocket));
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

int main()
{
    CWebServer objServer;
    objServer.start();
    return 0;
}