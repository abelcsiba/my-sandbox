#ifndef __HTTP2Server_HH__
#define __HTTP2Server__HH__

#include <string>
#include <iostream>
#include <nghttp2/asio_http2_server.h>

#include "CertEnv.hh"

using namespace nghttp2::asio_http2;
using namespace nghttp2::asio_http2::server;

enum ServerState {
    ACTIVE = 0,
    RUNNING,
    STOPPED
};

class HTTP2Server {
public:
    HTTP2Server(std::string _serverName, std::string _hostAddress, std::string _port) : serverName(_serverName), hostAddress(_hostAddress), port(_port), tls(boost::asio::ssl::context::tlsv12) { state = ACTIVE; }
    ~HTTP2Server() {
        server.stop();
        server.join();
    }

    void start() {
        if (state == RUNNING) {
            return;
        }
        
        if (!configureTls()) {
            return;
        }

        boost::system::error_code ec;
        if (server.listen_and_serve(ec, tls, hostAddress, port, true)) {
            std::cerr << "Unable to start server!" << std::endl;
            state = STOPPED;
            return;
        }
        
        state = RUNNING;
    }

    void stop() {
        server.stop();
        server.join();
    }

    virtual void registerHandlers() = 0;

private:
    http2 server;
    std::string serverName;
    std::string port;
    std::string hostAddress;
    ServerState state;

    boost::asio::ssl::context tls;

    bool configureTls() {

        char* tls_cert = std::getenv(CertEnv::CERT_PATH.c_str());
        char* tls_key = std::getenv(CertEnv::KEY_PATH.c_str());
        char* tls_ca = std::getenv(CertEnv::CA_PATH.c_str());

        if (strlen(tls_cert) == 0 || strlen(tls_key) == 0 || strlen(tls_ca) == 0) {
            std::cerr << "Missing certificate information!" << std::endl;
            return false;
        }

        tls.use_private_key_file(tls_key, boost::asio::ssl::context::pem);
	    tls.use_certificate_chain_file(tls_cert);
	    tls.load_verify_file(tls_ca);

        tls.set_verify_mode(boost::asio::ssl::verify_peer | boost::asio::ssl::verify_fail_if_no_peer_cert);

        boost::system::error_code ec;
	    configure_tls_context_easy(ec, tls);

        return true;
    }

};


#endif