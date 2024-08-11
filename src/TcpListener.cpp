#include "../include/TcpListener.h"


//Структура данных сервера
struct sockaddr_in serv_addr;
socklen_t serverlen = sizeof serv_addr;

//Структура данных подключенного клиента
struct sockaddr_in client_addr;
socklen_t clientlen = sizeof client_addr;

//Структура событий EPOLL
struct epoll_event ev, events[MAX_EVENTS];


TcpListener::TcpListener(const char *ip_address, int port) :
                    m_server_ip_address(ip_address),
                    m_port(port),
                    m_server_socket(0),
                    m_epoll_file_description(0),
                    m_status(false)
                    {}

TcpListener::~TcpListener() {
    close(m_epoll_file_description);
    close(m_server_socket);
}

// Инициализация сокета сервера
int TcpListener::init() {
    // create socket
    if ((m_server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        Log(log_console, log_file, CRITICAL, "Socket error");
        exit(1);
    }

    fcntl(m_server_socket, F_SETFL, O_NONBLOCK);

    serv_addr.sin_family = AF_INET; // IP версии IP4 или IP6
    serv_addr.sin_port = htons(m_port);
    serv_addr.sin_addr.s_addr = inet_addr(m_server_ip_address);


    int yes = 1;
    if (setsockopt(m_server_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))) {
        Log(log_console, log_file, CRITICAL, "Socket error set options");
        exit(1);
    }



    if (bind(m_server_socket, (struct sockaddr *) &serv_addr, serverlen) == -1) {
        Log(log_console, log_file, CRITICAL, "Socket bind error");
        close(m_server_socket);
        exit(1);
    }


    if (listen(m_server_socket, 1) == -1) {
        Log(log_console, log_file, CRITICAL, "Socket listen error");
        close(m_server_socket);
        exit(1);
    }

    m_epoll_file_description = epoll_create1(0);
    if (m_epoll_file_description == -1) {
        Log(log_console, log_file, CRITICAL, "Socket epoll create error");
        exit(EXIT_FAILURE);
    }

    ev.events = EPOLLIN;
    ev.data.fd = m_server_socket;
    if (epoll_ctl(m_epoll_file_description, EPOLL_CTL_ADD, m_server_socket, &ev) == -1) {
        Log(log_console, log_file, CRITICAL, "Socket epoll listen error");
        exit(EXIT_FAILURE);
    }

    return 0;
}

int TcpListener::run() {
    for (;;) {
        int ready = epoll_wait(m_epoll_file_description, events, MAX_EVENTS, -1);
        if (ready == -1) {
            Log(log_console, log_file, CRITICAL, "Socket epoll wait error");
            exit(EXIT_FAILURE);
        }

        for (int n = 0; n < ready; ++n) {
            if (events[n].data.fd == m_server_socket) {
                int client_socket = accept(m_server_socket, (struct sockaddr *) &client_addr, &clientlen);
                if (client_socket == -1) {
                    Log(log_console, log_file, ERROR, "User socket accept error");
                    exit(EXIT_FAILURE);
                }

                fcntl(client_socket, F_SETFL, O_NONBLOCK);;
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = client_socket;
                if (epoll_ctl(m_epoll_file_description, EPOLL_CTL_ADD, client_socket,&ev) == -1) {
                    Log(log_console, log_file, ERROR, "User socket add to epoll control accept error");
                    exit(EXIT_FAILURE);
                }
            } else {
                clientRawData(events[n].data.fd);
            }
        }
    }
}