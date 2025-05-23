
#include <mutex>
#include <unordered_map>
#include <poll.h>
#include <string>
#include <sys/socket.h>
#include <vector>
#include <unordered_map>

#include "client.hpp"
#include "protocol.hpp"


class Server
{
    char                                    *m_port;
    int                                     m_socket;

    std::vector <pollfd>                    m_observers;
    std::unordered_map <int, Client>        m_clients;

    std::mutex                              m_mutex;

    int                                     m_id_counter;

    Protocol                                m_protocol;

    Client &RegisterClient (int fd, Client client);
    void UnregisterClient (int fd);

    void HandleClient (Client &client, std::string request);
    
    void Listen ();
    
public:
    Server (char *port);
    Server ();
    ~Server ();
    
    void SetProtocol (Protocol protocol);
    void Broadcast (Client &client, std::string message);

    void Start ();
    void Stop ();
};