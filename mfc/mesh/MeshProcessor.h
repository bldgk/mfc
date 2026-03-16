//
// Created by webdev on 21.09.2018.
//

#ifndef MFC_MESHPROCESSOR_H
#define MFC_MESHPROCESSOR_H

#include <stdexcept>
#include <vector>
#include <iostream>
#include <list>
#include <string>
#include <cctype>
#include "options.h"
#include "mesh.h"
#include "meshio.h"
#include "mfc/time/Timer.h"


class MeshProcessor
{
public:
	MeshProcessor() = default;
	void PreProcessMesh(Mesh &, Options &);
};


#endif //MFC_MESHPROCESSOR_H
