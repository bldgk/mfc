//
// Created by webdev on 24.09.2018.
//

#ifndef MFC_OPTIONPARSER_H
#define MFC_OPTIONPARSER_H

#include "options.h"
#include "../nlohmann/json.hpp"
#include <iostream>
#include <map>
#include <memory>


using json = nlohmann::json;


struct ParseException : public std::exception
{
private:
	std::string message;
public:
	ParseException()
	{
		this->message = "";
	}

	ParseException(std::string e) : message(std::move(e)) {}

	const char *what() const noexcept final
	{
		auto res = "Parse error: " + this->message;
		return res.c_str();
	}
};


class OptionParser
{
private:
	void parseScale(Options &, json &);
	void parseUpAxis(Options &, json &);
	void parseFlip(Options &, json &);
	void parseCalcNormals(Options &, json &);
	void parseNoNormals(Options &, json &);
	void parseNoTextureCoordinates(Options &, json &);
	void parseNoColors(Options &, json &);
	void parseMethod(Options &, json &);
	void parseLevel(Options &, json &);
	void parseVertexPrecision(Options &, json &);
	void parseVertexPrecisionRel(Options &, json &);
	void parseNormalPrecision(Options &, json &);
	void parseTexturePrecision(Options &, json &);
	void parseColorPrecision(Options &, json &);
	void parseAttributePrecision(Options &, json &);
	void parseComment(Options &, json &);
	void parseTextureFileName(Options &, json &);
public:
	OptionParser() = default;
	void Parse(Options &, json &);
};


#endif //MFC_OPTIONPARSER_H
