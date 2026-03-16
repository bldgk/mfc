//
// Created by webdev on 19.09.2018.
//

#include "NetworkProvider.h"
#include <memory>


std::map<std::string, evpp::http::HTTPRequestCallback> NetworkProvider::routes;

int NetworkProvider::Init(int argc, char *argv[])
{
	std::string port;
	std::string host;
	int thread_num = 24;

	if (argc > 1) {
		if (std::string("-h") == argv[1] || std::string("--h") == argv[1] ||
			std::string("-help") == argv[1] || std::string("--help") == argv[1]) {
			std::cout << "usage : " << argv[0] << " <host> <listen_port> <thread_num>\n";
			std::cout << " e.g. : " << argv[0] << " 127.0.0.1 3653 24\n";
			return 0;
		}
	}

	if (argc == 2) {
		host = argv[1];
	} else if (argc == 3) {
		host = argv[1];
		port = argv[2];
	} else if (argc == 4) {
		host = argv[1];
		port = argv[2];
		thread_num = atoi(argv[3]);
	}

//	auto _http_server_settings = Settings::getSettings("httpserver");
//
//	if (port.empty())
//		port = _http_server_settings->configs->value("port").toString().toStdString();
//
//	if (host.empty())
//		host = _http_server_settings->configs->value("host").toString().toStdString();

	auto _http_server = std::make_unique<HttpServer>();
	_http_server->SetServerName("mfc", "0.0.0.3");
	_http_server->Start(host, port, thread_num, NetworkProvider::routes);
	return 0;
}

void NetworkProvider::API(std::string url, evpp::http::HTTPRequestCallback route)
{
	NetworkProvider::routes.insert(std::make_pair(url, NetworkProvider::createHandler(route)));
}

evpp::http::HTTPRequestCallback NetworkProvider::createHandler(evpp::http::HTTPRequestCallback api)
{
	return [=](evpp::EventLoop *loop,
			   const evpp::http::ContextPtr &ctx,
			   const evpp::http::HTTPSendResponseCallback &respcb)
	{
		api(loop, ctx, respcb);
	};
}