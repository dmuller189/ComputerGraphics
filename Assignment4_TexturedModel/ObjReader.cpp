#include "ObjReader.h"
#include "qstring.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

ObjReader::ObjReader() {}

ObjReader::ObjReader(std::string fileName) {
	readFile(fileName);
}

QVector<QVector3D> ObjReader::getVertices() {
	return vertices;
}

QVector<unsigned int> ObjReader::getFaces() {
	return vertexIndices;
}


ObjReader::~ObjReader() {

}


void ObjReader::readFile(std::string fileName) {

	std::ifstream inFile;
	inFile.open(fileName.c_str());

	if (inFile.is_open()) {
		while (!inFile.eof()) {

			std::string line;
			getline(inFile, line);

			if (line.length() > 3) {

				if (line.at(0) == 'v') {
					if (line.at(1) == 'n') {
						readNormal(line);
					}
					else if (line.at(1) == 't') {
						readTexture(line);
					}
					else if (line.at(1) == ' ') {
						readVertex(line);
					}
					continue;
				}

				if (line.at(0) == 'f' && line.at(1) == ' ') {
					readFace(line);
				}
			}

		}
		inFile.close();
	}
}

void ObjReader::readVertex(std::string line) {
	float v1;
	float v2;
	float v3;

	sscanf(line.c_str(), "v %f %f %f", &v1, &v2, &v3);

	vertices.push_back(QVector3D(v1, v2, v3));
}

void ObjReader::readNormal(std::string line) {
	float v1;
	float v2;
	float v3;

	sscanf(line.c_str(), "vn %f %f %f", &v1, &v2, &v3);

	normals.push_back(QVector3D(v1, v2, v3));
}

void ObjReader::readTexture(std::string line) {
	float t1;
	float t2;

	sscanf(line.c_str(), "vt %f %f", &t1, &t2);

	textures.push_back(QVector2D(t1, t2));
}

void ObjReader::readFace(std::string line) {
	unsigned int v1;
	unsigned int v2;
	unsigned int v3;

	unsigned int n1;
	unsigned int n2;
	unsigned int n3;

	unsigned int t1;
	unsigned int t2;
	unsigned int t3;

	sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3);

	vertexIndices.push_back(v1 - 1);
	vertexIndices.push_back(v2 - 1);
	vertexIndices.push_back(v3 - 1);

	textureIndices.push_back(t1 - 1);
	textureIndices.push_back(t2 - 1);
	textureIndices.push_back(t3 - 1);
}