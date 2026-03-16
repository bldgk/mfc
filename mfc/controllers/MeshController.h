//
// Created by webdev on 21.09.2018.
//

#ifndef MFC_MESHCONTROLLER_H
#define MFC_MESHCONTROLLER_H

#include <evpp/http/http_server.h>
#include <evpp/http/context.h>
#include "../nlohmann/json.hpp"
#include <chrono>
#include "mfc/time/Timer.h"
#include "../mesh/MeshConverter.h"
#include <fstream>
#include <sstream>

using json = nlohmann::json;


class MeshController
{
public:
	static void Convert(evpp::EventLoop *,
						const evpp::http::ContextPtr &,
						const evpp::http::HTTPSendResponseCallback &);

	static void ConvertData(evpp::EventLoop *,
						const evpp::http::ContextPtr &,
						const evpp::http::HTTPSendResponseCallback &);

	static void ConvertFile(evpp::EventLoop *,
						const evpp::http::ContextPtr &,
						const evpp::http::HTTPSendResponseCallback &);
};


#endif //MFC_MESHCONTROLLER_H
