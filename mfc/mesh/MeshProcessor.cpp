//
// Created by webdev on 21.09.2018.
//

#include "MeshProcessor.h"


void MeshProcessor::PreProcessMesh(Mesh &mesh, Options &options)
{
	// Nothing to do?
	if ((options.mScale == 1.0f) && (options.mUpAxis == uaZ) &&
		(!options.mFlipTriangles) && (!options.mCalcNormals))
		return;

	// Create 3x3 transformation matrices for the vertices and the normals
	Vector3 vX, vY, vZ;
	Vector3 nX, nY, nZ;
	switch (options.mUpAxis) {
		case uaX:
			nX = Vector3(0.0f, 0.0f, 1.0f);
			nY = Vector3(0.0f, 1.0f, 0.0f);
			nZ = Vector3(-1.0f, 0.0f, 0.0f);
			break;
		case uaY:
			nX = Vector3(1.0f, 0.0f, 0.0f);
			nY = Vector3(0.0f, 0.0f, 1.0f);
			nZ = Vector3(0.0f, -1.0f, 0.0f);
			break;
		case uaZ:
			nX = Vector3(1.0f, 0.0f, 0.0f);
			nY = Vector3(0.0f, 1.0f, 0.0f);
			nZ = Vector3(0.0f, 0.0f, 1.0f);
			break;
		case uaNX:
			nX = Vector3(0.0f, 0.0f, -1.0f);
			nY = Vector3(0.0f, 1.0f, 0.0f);
			nZ = Vector3(1.0f, 0.0f, 0.0f);
			break;
		case uaNY:
			nX = Vector3(1.0f, 0.0f, 0.0f);
			nY = Vector3(0.0f, 0.0f, -1.0f);
			nZ = Vector3(0.0f, 1.0f, 0.0f);
			break;
		case uaNZ:
			nX = Vector3(-1.0f, 0.0f, 0.0f);
			nY = Vector3(0.0f, 1.0f, 0.0f);
			nZ = Vector3(0.0f, 0.0f, -1.0f);
			break;
	}
	vX = nX * options.mScale;
	vY = nY * options.mScale;
	vZ = nZ * options.mScale;

//	std::cout << Time::Now() << "Processing... " << std::flush;
//	auto start_time = Time::NotifyTime();

	// Update all vertex coordinates
	for (CTMuint i = 0; i < mesh.mVertices.size(); ++i)
		mesh.mVertices[i] = vX * mesh.mVertices[i].x +
							 vY * mesh.mVertices[i].y +
							 vZ * mesh.mVertices[i].z;

	// Update all normals
	if (mesh.HasNormals() && !options.mNoNormals) {
		for (CTMuint i = 0; i < mesh.mNormals.size(); ++i)
			mesh.mNormals[i] = nX * mesh.mNormals[i].x +
								nY * mesh.mNormals[i].y +
								nZ * mesh.mNormals[i].z;
	}

	// Flip trianlges?
	if (options.mFlipTriangles) {
		CTMuint triCount = mesh.mIndices.size() / 3;
		for (CTMuint i = 0; i < triCount; ++i) {
			CTMuint tmp = mesh.mIndices[i * 3];
			mesh.mIndices[i * 3] = mesh.mIndices[i * 3 + 1];
			mesh.mIndices[i * 3 + 1] = tmp;
		}
	}

	// Calculate normals?
	if ((!options.mNoNormals) && options.mCalcNormals &&
		(!mesh.HasNormals()))
		mesh.CalculateNormals();

//	std::cout << Time::DurationFrom(start_time) << " ms" << std::endl;
}