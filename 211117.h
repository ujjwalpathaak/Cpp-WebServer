#include <bits/stdc++.h>
#include <winsock2.h>

using namespace std;

class Base2
{
public:
    virtual void errorHandling() = 0;
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