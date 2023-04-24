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

void MySocket::Socket::Close()
{
    close(this->socket_fd);
}