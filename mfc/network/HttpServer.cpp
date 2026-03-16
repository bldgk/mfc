//
// Created by webdev on 19.09.2018.
//

#include "HttpServer.h"


void HttpServer::Start(std::map<std::string, evpp::http::HTTPRequestCallback> &api)
{
	this->host = "127.0.0.1";
	this->port = "3653";

	this->createHttpServer(1, api);
}

void HttpServer::Start(std::string host, std::string port, int thread_num,
					   std::map<std::string, evpp::http::HTTPRequestCallback> &api)
{
	if (host.empty())
		host = "127.0.0.1";
	if (port.empty())
		port = "3653";

	this->host = host;
	this->port = port;

	this->createHttpServer(thread_num, api);
}

void HttpServer::createHttpServer(int thread_num, std::map<std::string, evpp::http::HTTPRequestCallback> &api)
{
	std::vector<int> ports = {3652};
	ports.push_back(stoi(this->port));

	evpp::http::Server server(thread_num);
	server.SetThreadDispatchPolicy(evpp::ThreadDispatchPolicy::kIPAddressHashing);
	server.RegisterDefaultHandler(HttpServer::DefaultHandler);
	this->initApiHandlers(server, api);
	server.Init(ports);

	this->logStarted();
	server.Start();
	while (!server.IsStopped()) {
		usleep(1);
	}
}

void HttpServer::DefaultHandler(evpp::EventLoop *loop,
								const evpp::http::ContextPtr &ctx,
								const evpp::http::HTTPSendResponseCallback &cb)
{
	(void) loop;
	(void) ctx;
	cb("default");
}

void HttpServer::logStarted()
{
	std::cout << this->serverName << " " << this->serverVersion << " is running on " << this->host << ":" << this->port << std::endl;
}

void HttpServer::initApiHandlers(evpp::http::Server &server, std::map<std::string, evpp::http::HTTPRequestCallback> &api)
{
	for (const auto &route_it : api) {
		server.RegisterHandler(route_it.first, route_it.second);
	}
}

void HttpServer::SetServerName(std::string server_name, std::string server_version)
{
	this->serverName = std::move(server_name);
	this->serverVersion = std::move(server_version);
}
