//
// Created by webdev on 19.09.2018.
//

#include "network/NetworkProvider.h"
#include "controllers/MeshController.h"
#include <iostream>
#include <vector>
#include <string>
#include <memory>

//template<class T, class... Args>
//auto make_unique_vector(Args ...args) {
//	std::vector<std::unique_ptr<T>> v;
//	v.reserve(sizeof...(args));
//	(v.emplace_back(std::make_unique<T>(args)), ...);
//	return v;
//}

int main(int argc, char **argv)
{
	google::InitGoogleLogging("XXX");
	google::SetStderrLogging(3);


//	auto v = make_unique_vector<std::string>("abc","def","xyz");
//
//	for(const auto& p: v)
//		std::cout << *p << '\n';

	NetworkProvider::API("/convert", &MeshController::Convert);
	NetworkProvider::API("/convert-data", &MeshController::ConvertData);
	NetworkProvider::API("/convert-file", &MeshController::ConvertFile);
	if (!NetworkProvider::Init(argc, argv))
		return 0;
}