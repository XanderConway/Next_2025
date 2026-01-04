#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include <unordered_map>
#include <windows.h> 

#include "../Game/Utils/ReadObj.h"

// A triplet of v, uv and n indicies in the obj file
struct FaceVert {
	uint32_t p_i, uv_i, n_i;

	bool operator==(const FaceVert& other) const {

		return p_i == other.p_i && n_i == other.n_i && uv_i == other.uv_i;
	}

};

struct FaceVertHash {
	std::size_t operator()(const FaceVert& data) const {
		return data.p_i ^ (data.n_i << 1) ^ (data.uv_i << 2);
	}
};

// Read an obj file, expects the .obj format Blender outputs
Model readFromFile(std::string filename) {
	std::ifstream file(filename);
	std::string line;
	
	// Avoid duplicating verticies by making one vert for identical (v/uv/n) triplets
	std::unordered_map<FaceVert, int, FaceVertHash> vertMap;

	std::vector<Vert> verticies;
	std::vector<Face> faces;

	if (file.is_open()) {

		std::vector<Vec3<float>> positions;
		std::vector<Vec3<float>> normals;
		std::vector<UV<float>> uvs;

		while (std::getline(file, line)) {

			// TODO: use \.
			std::regex vertRegex(R"(^v (-?\d+.\d+) (-?\d+.\d+) (-?\d+.\d+))");
			std::regex normalRegex(R"(^vn (-?\d+.\d+) (-?\d+.\d+) (-?\d+.\d+))");
			std::regex uvRegex(R"(^vt (-?\d+.\d+) (-?\d+.\d+))");
			std::regex faceRegex(R"(^f (\d+)/(\d+)/(\d+) (\d+)/(\d+)/(\d+) (\d+)/(\d+)/(\d+))"); // assume only triangle faces

			std::smatch smatch;
			
			// Read vertex, normal or uv lines
			if (std::regex_match(line, smatch, vertRegex)) {
				float x = std::stof(smatch[1]);
				float y = std::stof(smatch[2]);
				float z = std::stof(smatch[3]);

				positions.push_back(Vec3(x, y, z));
			}
			else if (std::regex_match(line, smatch, uvRegex)) {
				float u = std::stof(smatch[1]);
				float v = std::stof(smatch[2]);

				uvs.push_back(UV(u, v));
			} 
			else if (std::regex_match(line, smatch, normalRegex)) {
				float x = std::stof(smatch[1]);
				float y = std::stof(smatch[2]);
				float z = std::stof(smatch[3]);

				normals.push_back(Vec3(x, y, z));
			}
			else if (std::regex_match(line, smatch, faceRegex)) {

				Face f;

				// Check if any verts in the face are duplicates, then add the updated 
				for (int i = 0; i < 3; i++) {
					uint32_t vp_i = std::stoi(smatch[i * 3 + 1]) - 1;
					uint32_t uv_i = std::stoi(smatch[i * 3 + 2]) - 1;
					uint32_t vn_i = std::stoi(smatch[i * 3 + 3]) - 1;

					FaceVert faceVert = { vp_i, uv_i, vn_i };

					int vertIndex = 0;
					if (vertMap.find(faceVert) == vertMap.end()) {
						verticies.push_back({ positions[vp_i], uvs[uv_i], normals[vn_i] });
						vertMap[faceVert] = verticies.size() - 1;
					}
					vertIndex = vertMap[faceVert];
					(&f.v1)[i] = vertIndex;
				}

				faces.push_back(f);
			}
		}
	}
	Model m{ verticies, faces };
	return m;
}

