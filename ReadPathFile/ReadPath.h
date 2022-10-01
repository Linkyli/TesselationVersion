#pragma once
#include<vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>    
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

using namespace std;

class ReadPath {
public:
	int CricleNum;
	int PosNum;
	vector<glm::vec3> CutterPath;
	void ReadPathfile(const char* cfilename);
	bool ReadASCII(const char* buffer);

};
