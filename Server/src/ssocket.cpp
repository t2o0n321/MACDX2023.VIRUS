#include "ssocket.hpp"

MySocket::Socket::Socket(int port) : connectionFailed(true)
{
    this->Port = port;
}

int MySocket::Socket::Init()
{
    // Create socket
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0)
    {
        this->connectionFailed = true;
        // std::cerr << "Error creating socket" << std::endl;
        return -1;
    }
    this->connectionFailed = false;
    this->socket_fd = sock_fd;
    return sock_fd;
}

bool MySocket::Socket::Listen(SERVERFP toDo)
{

    // todo
    toDo();

    // Bind socket to port
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(this->Port);
    addr.sin_addr.s_addr = INADDR_ANY;
    memset(addr.sin_zero, 0, sizeof(addr.sin_zero));
    int bindResult = bind(this->socket_fd, (sockaddr *)&addr, sizeof(addr));
    if (bindResult < 0)
    {
        this->connectionFailed = true;
        // std::cerr << "Failed to bind socket" << std::endl;
        return false;
    }

    this->connectionFailed = false;
    // Listen for incomming connections
    int listenResult = listen(this->socket_fd, SOMAXCONN);
    if (listenResult < 0)
    {
        this->connectionFailed = true;
        std::cerr << "Failed to listen" << std::endl;
        return false;
    }
    this->connectionFailed = false;

    std::cout << "Listening on port " << this->Port << std::endl;
    return true;
}

std::pair<int, sockaddr_in> MySocket::Socket::Accept()
{
    // Client data
    std::pair<int, sockaddr_in> result;

    // Accept from client
    int client_sock_fd;
    sockaddr_in cAddr;
    socklen_t client_sock_len = sizeof(cAddr);

    if ((client_sock_fd = accept(this->socket_fd, (sockaddr *)&cAddr, &client_sock_len)) < 0)
    {
        this->connectionFailed = true;
        // std::cerr << "Failed to accept to client" << std::endl;
        close(client_sock_fd);
        result = std::make_pair(-1, cAddr);
        return result;
    }

    this->connectionFailed = false;
    result = std::make_pair(client_sock_fd, cAddr);
    // char buffer[MAX_CLIENT_BUFFER_SIZE] = {0};
    // int bytes_read = read(client_sock_fd, buffer, sizeof(buffer));

    return result;
}

bool MySocket::Socket::isNotConnected()
{
    return this->connectionFailed;
}

int MySocket::Socket::Send(int clientFd, XDATA data)
{
    RC4 r(INET_KEY);
    std::string toSend = r.encrypt(data);
    int res;
    try
    {
        res = send(clientFd, toSend.c_str(), toSend.size(), 0);
    }
    catch (...)
    {
        res = -1;
    }
    return res;
}

void MySocket::Socket::Close()
{
    close(this->socket_fd);
}

std::string MySocket::Socket::Recv(int clientFd)
{
    char buf[10000];
    int res = recv(clientFd, buf, sizeof(buf), 0);
    if (res == SOCKET_ERROR || res == 0)
    {
        std::cout << "Failed to receive from client " << clientFd << std::endl;
        return "";
    }
    std::string data(buf);
    return data;
}

void checkConnection(std::map<int, std::string> &clientDatas)
{
    std::map<int, std::string>::iterator it;
    if (clientDatas.empty())
        return;

    char buf[4096];

    for (it = clientDatas.begin(); it != clientDatas.end();)
    {
        memset(buf, 0, sizeof(buf));

        // std::cout << it->first << std::endl;
        int recvRes = recv(it->first, buf, sizeof(buf), MSG_PEEK);
        // std::cout << recvRes << std::endl;
        if (recvRes == 0)
        {
            close(it->first);
            it = clientDatas.erase(it);
        }
        // Socket not ready for reading
        else if (recvRes == SOCKET_ERROR && errno == EAGAIN)
        {
            // std::cout << "Socket not ready for reading" << std::endl;
            close(it->first);
            it = clientDatas.erase(it);
        }
        // Error in recv from client
        else if (recvRes == SOCKET_ERROR)
        {
            // std::cout << "Error in recv from client" << std::endl;
            close(it->first);
            it = clientDatas.erase(it);
        }
        else
        {
            ++it;
        }
    }
    return;
}
