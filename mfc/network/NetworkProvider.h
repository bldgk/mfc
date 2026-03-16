//
// Created by webdev on 19.09.2018.
//

#ifndef MFC_NETWORKPROVIDER_H
#define MFC_NETWORKPROVIDER_H

#include <iostream>
#include <memory>
#include "HttpServer.h"


class NetworkProvider
{
	static evpp::http::HTTPRequestCallback createHandler(evpp::http::HTTPRequestCallback);
public:
	static std::map<std::string, evpp::http::HTTPRequestCallback> routes;
	static int Init(int, char *[]);
	static void API(std::string, evpp::http::HTTPRequestCallback);

	NetworkProvider() = default;
};


#endif //MFC_NETWORKPROVIDER_H
