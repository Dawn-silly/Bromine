#include "client.h"

bool StartClient()
{
    WSADATA wsa_data;
    WSAStartup(MAKEWORD(2, 2), &wsa_data);

    SOCKET host_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (host_sock == SOCKET_ERROR) return false;

    char ip[15];
    GetIP(ip);
    printf("Destination IP = %s\n", ip);
    struct sockaddr_in host_sa = {.sin_family = AF_INET, .sin_port = htons(GetPort())};
    if (inet_pton(AF_INET, ip, &host_sa.sin_addr) <= 0) return false;

    if (connect(host_sock, (struct sockaddr *)&host_sa, sizeof(host_sa)) == SOCKET_ERROR) return false;

    printf("Connected with ip: %s, you can chat!\n", ip);

    bool in_chat = true;

    DWORD dwthreadId;

    int buffer_size = GetBufferSize();
    char *buffer = malloc(buffer_size);

    RECEIVE_ARGS recv_args = {.in_chat = &in_chat, .sender = host_sock};

    HANDLE receive_thread = CreateThread(NULL, 0, Receiving, (LPVOID)&recv_args, 0, &dwthreadId);
    while (in_chat)
    {
        Sending(host_sock, buffer, buffer_size);
    }
    free(buffer);
    printf("you interlocutor is ended chat.\n");
    system("pause");

    closesocket(host_sock);
    WSACleanup();

    return true;
}