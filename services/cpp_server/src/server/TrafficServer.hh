

#ifndef __TrafficServer_HH__
#define __TrafficServer_HH__

#include "HTTP2Server.hh"

class TrafficServer : public HTTP2Server {

public:
    TrafficServer(std::string _serverName, std::string _hostAddress, std::string _port) : HTTP2Server(_serverName, _hostAddress, _port) {}
    ~TrafficServer() {}
    void registerHandlers() override;
};


#endif