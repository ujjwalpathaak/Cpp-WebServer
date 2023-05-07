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