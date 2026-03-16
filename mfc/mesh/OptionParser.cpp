//
// Created by webdev on 24.09.2018.
//

#include "OptionParser.h"


void OptionParser::parseScale(Options &options, json &j_options)
{
	if (j_options.count("scale")) {
		options.mScale = std::atof(j_options.at("scale").dump().c_str());
	}
}

void OptionParser::parseUpAxis(Options &options, json &j_options)
{
	if (j_options.count("upaxis")) {
		std::map<std::string, UpAxis> axis {
				{"X",  uaX},
				{"Y",  uaY},
				{"Z",  uaZ},
				{"-X", uaNX},
				{"-Y", uaNY},
				{"-Z", uaNZ}
		};
		auto upAxis = j_options.at("upaxis");
		if (axis.count(upAxis)) {
			options.mUpAxis = axis.at(upAxis);
		} else
			throw ParseException("Invalid up axis (use X, Y, Z, -X, -Y or -Z).");
	}
}

void OptionParser::parseFlip(Options &options, json &j_options)
{
	if (j_options.count("flip")) {
		options.mFlipTriangles = true;
	}
}

void OptionParser::parseCalcNormals(Options &options, json &j_options)
{
	if (j_options.count("calc-normals")) {
		options.mCalcNormals = true;
	}
}

void OptionParser::parseNoNormals(Options &options, json &j_options)
{
	if (j_options.count("no-normals")) {
		options.mNoNormals = true;
	}
}

void OptionParser::parseNoTextureCoordinates(Options &options, json &j_options)
{
	if (j_options.count("no-texcoords")) {
		options.mNoTexCoords = true;
	}
}

void OptionParser::parseNoColors(Options &options, json &j_options)
{
	if (j_options.count("no-colors")) {
		options.mNoColors = true;
	}
}

void OptionParser::parseMethod(Options &options, json &j_options)
{
	if (j_options.count("method")) {
		std::map<std::string, CTMenum> axis {
				{"raw", CTM_METHOD_RAW},
				{"mg1", CTM_METHOD_MG1},
				{"mg2", CTM_METHOD_MG2}
		};
		auto method = j_options.at("method");
		if (axis.count(method)) {
			options.mMethod = axis.at(method);
		} else
			throw ParseException("Invalid method (use RAW, MG1 or MG2).");
	}
}

void OptionParser::parseLevel(Options &options, json &j_options)
{
	if (j_options.count("level")) {
		auto level = std::stoi(j_options.at("level").dump());
		if (level > 0 && level < 9) {
			options.mLevel = level;
		} else
			throw ParseException("Invalid compression level (it must be in the range 0 - 9).");
	}
}

void OptionParser::parseVertexPrecision(Options &options, json &j_options)
{
	if (j_options.count("vprec")) {
		options.mVertexPrecision = std::atof(j_options.at("vprec").dump().c_str());
	}
}

void OptionParser::parseVertexPrecisionRel(Options &options, json &j_options)
{
	if (j_options.count("vprecrel")) {
		options.mVertexPrecisionRel = std::atof(j_options.at("vprecrel").dump().c_str());
	}
}

void OptionParser::parseNormalPrecision(Options &options, json &j_options)
{
	if (j_options.count("nprec")) {
		options.mNormalPrecision = std::atof(j_options.at("nprec").dump().c_str());
	}
}

void OptionParser::parseTexturePrecision(Options &options, json &j_options)
{
	if (j_options.count("tprec")) {
		options.mTexMapPrecision = std::atof(j_options.at("tprec").dump().c_str());
	}
}

void OptionParser::parseColorPrecision(Options &options, json &j_options)
{
	if (j_options.count("cprec")) {
		options.mColorPrecision = std::atof(j_options.at("cprec").dump().c_str());
	}
}

void OptionParser::parseAttributePrecision(Options &options, json &j_options)
{
	if (j_options.count("aprec")) {
		options.mAttributePrecision = std::atof(j_options.at("aprec").dump().c_str());
	}
}

void OptionParser::parseComment(Options &options, json &j_options)
{
	if (j_options.count("comment")) {
		options.mComment = j_options.at("comment").dump();
	}
}

void OptionParser::parseTextureFileName(Options &options, json &j_options)
{
	if (j_options.count("texfile")) {
		options.mTexFileName = j_options.at("texfile").dump();
	}
}

void OptionParser::Parse(Options &options, json &j_options)
{
	this->parseScale(options, j_options);
	this->parseUpAxis(options, j_options);
	this->parseFlip(options, j_options);
	this->parseCalcNormals(options, j_options);
	this->parseNoNormals(options, j_options);
	this->parseNoTextureCoordinates(options, j_options);
	this->parseNoColors(options, j_options);
	this->parseMethod(options, j_options);
	this->parseLevel(options, j_options);
	this->parseVertexPrecision(options, j_options);
	this->parseVertexPrecisionRel(options, j_options);
	this->parseNormalPrecision(options, j_options);
	this->parseTexturePrecision(options, j_options);
	this->parseColorPrecision(options, j_options);
	this->parseAttributePrecision(options, j_options);
	this->parseComment(options, j_options);
	this->parseTextureFileName(options, j_options);
}