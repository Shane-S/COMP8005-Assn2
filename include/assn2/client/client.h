

#ifndef COMP8005_ASSN2_CLIENT_H
#define COMP8005_ASSN2_CLIENT_H

typedef struct
{
    char* ip;
    char* port;
    unsigned int num_of_clients;
    unsigned int max_requests;
} client_info;

int start_client(client_info client_datas);
void print_usage(char const* name);
void *clients(void *info);
int close_socket(int* socket);
int set_reuse(int* socket);
int connect_to_server(const char *port, const char *ip);

#endif