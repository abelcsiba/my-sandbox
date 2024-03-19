
#include <iostream>

#include <nghttp2/asio_http2_server.h>

using namespace nghttp2::asio_http2;
using namespace nghttp2::asio_http2::server;

int main(int argc, char **argv)
{
	boost::system::error_code ec;
	boost::asio::ssl::context tls(boost::asio::ssl::context::sslv23);

	tls.use_private_key_file("/opt/certificates/tls.key", boost::asio::ssl::context::pem);
	tls.use_certificate_chain_file("/opt/certificates/tls.crt");

	configure_tls_context_easy(ec, tls);

	http2 server;

	server.handle("/", [](const request &req, const response &res) {
		res.write_head(200);
		res.end("Hello World!\n");
	});

	if (server.listen_and_serve(ec, tls, "127.0.0.1", "8085")) {
		std::cerr << "Failed to launch server: " << ec.message() << std::endl;
	}

	return 0;	
}
