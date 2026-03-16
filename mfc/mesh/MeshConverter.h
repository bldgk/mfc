//
// Created by webdev on 21.09.2018.
//

#ifndef MFC_MESHCONVERTER_H
#define MFC_MESHCONVERTER_H

#include <iostream>
#include "mfc/time/Timer.h"
#include "../nlohmann/json.hpp"
#include "mesh.h"
#include "meshio.h"
#include "MeshProcessor.h"
#include "OptionsProcessor.h"
#include <fstream>


using json = nlohmann::json;


struct FileNotExistsException : public std::exception
{
private:
	std::string message;
public:
	FileNotExistsException()
	{
		this->message = "";
	}

	explicit FileNotExistsException(std::string e) : message(std::move(e)) {}

	const char *what() const noexcept final
	{
		auto res = "File error: " + this->message + " does not exists";
		return res.c_str();
	}
};


class MeshConverter
{
	void overrideOptions(Mesh &, Options &);
	int importMesh(std::string &, Mesh &);
	int exportMesh(std::string, Mesh &, Options &);
public:
	int convert(std::string, std::string, Options &);
	MeshConverter() = default;

	void Convert(std::string, json &, json &);
	void Convert(json &, json &, json &);
};


#endif //MFC_MESHCONVERTER_H
