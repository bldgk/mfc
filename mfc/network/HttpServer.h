//
// Created by webdev on 19.09.2018.
//

#ifndef MESHFORMATCONVERTER_HTTPSERVER_H
#define MESHFORMATCONVERTER_HTTPSERVER_H

#include <evpp/http/http_server.h>
#include <iostream>


class HttpServer
{
public:
	static void DefaultHandler(evpp::EventLoop *,
							   const evpp::http::ContextPtr &,
							   const evpp::http::HTTPSendResponseCallback &);

	HttpServer() {}

	~HttpServer() {}

	void SetServerName(std::string, std::string);

	void Start(std::map<std::string, evpp::http::HTTPRequestCallback> &);
	void Start(std::string, std::string, int, std::map<std::string, evpp::http::HTTPRequestCallback> &);

private:
	std::string port;
	std::string host;
	std::string serverName;
	std::string serverVersion;

	void initApiHandlers(evpp::http::Server &, std::map<std::string, evpp::http::HTTPRequestCallback> &);

	void createHttpServer(int, std::map<std::string, evpp::http::HTTPRequestCallback> &);

	void logStarted();
};


#endif //MESHFORMATCONVERTER_HTTPSERVER_H
