#include "host.h"

bool StartHosting()
{
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data)) return false;

    SOCKET host_sock = socket(AF_INET, SOCK_STREAM, 0);;
    if (host_sock == SOCKET_ERROR) return false;

    struct sockaddr_in host_sa = {.sin_family = AF_INET, .sin_port = htons(GetPort()), .sin_addr.S_un.S_addr = INADDR_ANY};

    if (bind(host_sock, (struct sockaddr *)&host_sa, sizeof(host_sa)) == SOCKET_ERROR) return false;
    listen(host_sock, 1);

    struct sockaddr_in client_sa;
    int client_addr_len = sizeof(client_sa);
    printf("waiting for connections...\n");
    SOCKET client_sock = accept(host_sock, (struct sockaddr *)&client_sa, &client_addr_len);
    if (client_sock == INVALID_SOCKET) return false;

    char client_ip[15];
    inet_ntop(AF_INET, &client_sa.sin_addr, client_ip, sizeof(client_ip));

    printf("Connected with ip: %s, you can chat!\n", client_ip);
    
    bool in_chat = true;

    DWORD dwthreadId;

    int buffer_size = GetBufferSize();
    char *buffer = malloc(buffer_size);

    RECEIVE_ARGS recv_args = {.in_chat = &in_chat, .sender = client_sock};

    HANDLE receive_thread = CreateThread(NULL, 0, Receiving, (LPVOID)&recv_args, 0, &dwthreadId);
    while (in_chat)
    {
        Sending(client_sock, buffer, buffer_size);
    }
    free(buffer);
    printf("you interlocutor is ended chat.\n");
    system("pause");

    closesocket(host_sock);
    closesocket(client_sock);
    WSACleanup();

    return true;
}