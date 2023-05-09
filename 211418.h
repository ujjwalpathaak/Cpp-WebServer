#include <bits/stdc++.h>
#include <winsock2.h>
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
    void handleClient(SOCKET clientSocket, int iResult, string strResource)
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
    void handleClient(SOCKET clientSocket, int iResult, string strResource)
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
    void handleClient(SOCKET clientSocket, int iResult, string strResource)
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
    void handleClient(SOCKET clientSocket, int iResult, string strResource)
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
    void handleClient(SOCKET clientSocket, int iResult, string strResource)
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