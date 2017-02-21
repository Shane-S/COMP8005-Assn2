//
// Created by shane on 2/13/17.
//


#include <netinet/in.h>
#include <stdio.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include "done.h"
#include "server.h"

int accept_client(acceptor_t* acceptor, client_t* out)
{
    struct sockaddr_in peer;
    socklen_t accepted_len = sizeof(peer);
    int peer_sock = accept(acceptor->sock, (struct sockaddr*)&peer, &accepted_len);
    if (peer_sock < 0)
    {
        if (errno != EWOULDBLOCK && errno != EAGAIN)
        {
            atomic_store(&done, 1);

            if (errno != EINTR)
            {
                perror("accept");
            }
        }
        return -1;
    }

    out->peer = peer;
    out->sock = peer_sock;
    return 0;
}

void cleanup_acceptor(acceptor_t* acceptor)
{
    shutdown(acceptor->sock, 0);
    close(acceptor->sock);
    freeaddrinfo(acceptor->info);
}
