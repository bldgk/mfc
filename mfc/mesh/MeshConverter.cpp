//
// Created by webdev on 21.09.2018.
//

#include "MeshConverter.h"


int MeshConverter::convert(std::string input, std::string output, Options &options)
{
	Mesh mesh;

	auto err = this->importMesh(input, mesh);
	if (err == 1) {
		return err;
	}

	auto meshProcessor = std::make_unique<MeshProcessor>();
	meshProcessor->PreProcessMesh(mesh, options);

	this->overrideOptions(mesh, options);
	this->exportMesh(std::move(output), mesh, options);
	std::remove(input.c_str());
	return 0;
}

void MeshConverter::overrideOptions(Mesh &mesh, Options &options)
{
	// Override comment?
	if (!options.mComment.empty())
		mesh.mComment = options.mComment;

	// Override texture file name?
	if (!options.mTexFileName.empty())
		mesh.mTexFileName = options.mTexFileName;
}

int MeshConverter::importMesh(std::string &file, Mesh &mesh)
{
	std::ifstream stream(file);
	if (!stream.good())
		throw FileNotExistsException(file);

	return ImportMesh(file.c_str(), &mesh);
}

int MeshConverter::exportMesh(std::string file, Mesh &mesh, Options &options)
{
	return ExportMesh(file.c_str(), &mesh, options);
}

void MeshConverter::Convert(json &files, json &format, json &j_options)
{
	Options options;
	auto optionProcessor = std::make_unique<OptionsProcessor>();
	optionProcessor->Process(options, j_options);
	for (const auto &file : files) {
		std::string f = file;
		auto fileName = f.substr(0, f.find_last_of('.'));
		std::string fileExtension = format;

		auto err = this->convert(file, fileName.append(".").append(fileExtension), options);
		if (err == 1) {
			continue;
		}
	}
}

void MeshConverter::Convert(std::string file, json &format, json &j_options)
{
	Options options;
	auto optionProcessor = std::make_unique<OptionsProcessor>();
	optionProcessor->Process(options, j_options);

	auto fileName = file.substr(0, file.find('.'));
	std::string fileExtension = format;

	this->convert(std::move(file), fileName.append(".").append(fileExtension), options);
}