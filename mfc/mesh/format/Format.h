//
// Created by webdev on 25.09.2018.
//

#ifndef MFC_FORMAT_H
#define MFC_FORMAT_H

#include "../mesh.h"


class Format
{
public:
	virtual void Import(const std::string &, Mesh &) {}

	virtual void Export(const std::string &, Mesh &, Options &options) {};
};


#endif //MFC_FORMAT_H
