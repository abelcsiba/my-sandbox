
#include <iostream>
#include <nghttp2/asio_http2_server.h>

//#include "server/TrafficServer.hh"

using namespace nghttp2::asio_http2;
using namespace nghttp2::asio_http2::server;

struct Test {
public:
	void handle_request(const request &req, const response &res) {
		res.write_head(200);
		res.end("{ \'message\': \'Hello World!\'}");
	}
};

int main(int argc, char **argv)
{
	boost::system::error_code ec;
	boost::asio::ssl::context tls(boost::asio::ssl::context::tlsv12);

	tls.use_private_key_file("/opt/certificates/tls.key", boost::asio::ssl::context::pem);
	tls.use_certificate_chain_file("/opt/certificates/tls.crt");
	tls.load_verify_file("/opt/certificates/ca.crt");

	tls.set_verify_mode(boost::asio::ssl::verify_peer | boost::asio::ssl::verify_fail_if_no_peer_cert);

	configure_tls_context_easy(ec, tls);

	http2 server;

	Test test;

	server.handle("/", [&test](const request &req, const response &res) {
		std::cerr << "Message handled here again!" << std::endl;
		test.handle_request(req, res);
	});

	if (server.listen_and_serve(ec, tls, "0.0.0.0", "8443")) {
		std::cerr << "Failed to launch server: " << ec.message() << std::endl;
	}

	/*TrafficServer *trafficServer = new TrafficServer("TrafficServer", "localhost", "80");

	trafficServer->start();*/

	return 0;	
}
