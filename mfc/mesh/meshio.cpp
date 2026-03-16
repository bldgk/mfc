//-----------------------------------------------------------------------------
// Product:     OpenCTM src
// File:        meshio.cpp
// Description: Mesh I/O using different file format loaders/savers.
//-----------------------------------------------------------------------------
// Copyright (c) 2009-2010 Marcus Geelnard
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//     1. The origin of this software must not be misrepresented; you must not
//     claim that you wrote the original software. If you use this software
//     in a product, an acknowledgment in the product documentation would be
//     appreciated but is not required.
//
//     2. Altered source versions must be plainly marked as such, and must not
//     be misrepresented as being the original software.
//
//     3. This notice may not be removed or altered from any source
//     distribution.
//-----------------------------------------------------------------------------

#include <memory>
#include "meshio.h"
#include "../time/Timer.h"
#include "options.h"
#include "format/ctm.h"
#include "format/ply.h"
#include "format/stl.h"
#include "format/3ds.h"
#include "format/dae.h"
#include "format/obj.h"
#include "format/lwo.h"
#include "format/off.h"
#include "format/vtk.h"
#include "format/wrl.h"
#include "common.h"


using namespace std;


/// Import a mesh from a file.
int ImportMesh(const char *aFileName, Mesh *aMesh)
{
	auto timer = std::make_unique<Timer>();
	timer->Note();

	string fileExt = UpperCase(ExtractFileExt(string(aFileName)));
	if (fileExt == string(".CTM"))
		Import_CTM(aFileName, aMesh);
	else if (fileExt == string(".PLY"))
		Import_PLY(aFileName, aMesh);
	else if (fileExt == string(".STL"))
		Import_STL(aFileName, aMesh);
	else if (fileExt == string(".3DS"))
		Import_3DS(aFileName, aMesh);
	else if (fileExt == string(".DAE"))
		Import_DAE(aFileName, aMesh);
	else if (fileExt == string(".OBJ"))
		Import_OBJ(aFileName, aMesh);
	else if (fileExt == string(".LWO"))
		Import_LWO(aFileName, aMesh);
	else if (fileExt == string(".OFF"))
		Import_OFF(aFileName, aMesh);
	else if (fileExt == string(".WRL"))
		Import_WRL(aFileName, aMesh);
	else if (fileExt == string(".VTK"))
		Import_VTK(aFileName, aMesh);
	else {
		std::cout << timer->Now() << "Error: " << aFileName << " Unknown input file extension." << std::endl;
		return 1;
	}

	std::cout << "Loading " << aFileName << "... " << timer->Duration() << " ms" << std::endl;
	return 0;
}

/// Export a mesh to a file.
int ExportMesh(const char *aFileName, Mesh *aMesh, Options &aOptions)
{
	auto timer = std::make_unique<Timer>();
	timer->Note();
	string fileExt = UpperCase(ExtractFileExt(string(aFileName)));
	if (fileExt == string(".CTM"))
		Export_CTM(aFileName, aMesh, aOptions);
	else if (fileExt == string(".PLY"))
		Export_PLY(aFileName, aMesh, aOptions);
	else if (fileExt == string(".STL"))
		Export_STL(aFileName, aMesh, aOptions);
	else if (fileExt == string(".3DS"))
		Export_3DS(aFileName, aMesh, aOptions);
	else if (fileExt == string(".DAE"))
		Export_DAE(aFileName, aMesh, aOptions);
	else if (fileExt == string(".OBJ"))
		Export_OBJ(aFileName, aMesh, aOptions);
	else if (fileExt == string(".LWO"))
		Export_LWO(aFileName, aMesh, aOptions);
	else if (fileExt == string(".OFF"))
		Export_OFF(aFileName, aMesh, aOptions);
	else if (fileExt == string(".WRL"))
		Export_WRL(aFileName, aMesh, aOptions);
	else {
		std::cout << timer->Now() << "Error: " << aFileName << " Unknown output file extension." << std::endl;
		return 1;
	}

	std::cout << "Saving " << aFileName << "... " << timer->Duration() << " ms" << std::endl;
	return 0;
}

/// Return a list of supported formats.
void SupportedFormats(list<string> &aList)
{
	aList.push_back(string("OpenCTM (.ctm)"));
	aList.push_back(string("Stanford triangle format (.ply)"));
	aList.push_back(string("Stereolithography (.stl)"));
	aList.push_back(string("3D Studio (.3ds)"));
	aList.push_back(string("COLLADA 1.4/1.5 (.dae)"));
	aList.push_back(string("Wavefront geometry file (.obj)"));
	aList.push_back(string("LightWave object (.lwo)"));
	aList.push_back(string("Geomview object file format (.off)"));
	aList.push_back(string("VRML 2.0 (.wrl) - export only"));
	aList.push_back(string("VTK (.vtk) - import only"));
}
