#pragma once
#include<string>
#include<vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
using namespace glm;

class Tools {
public:
	static string TailToken(string line) {
		int index = line.find_first_of(" ");
		return line.substr(index+1, line.size()-index+1);
	}

	
	static string FirstToken(string line) {
		int index = line.find_first_of(" ");
		return line.substr(0,index);

	}


	static vec3 getElement(vector<vec3>& arr, string pos) {
		
		int num = atoi(pos.c_str())-1;
	/*	if (num < arr.size())*/
			return arr[num];
		//else
		//	return vec3(0, 0, 0);
	}

	static vec2 getElement(vector<vec2>& arr, string pos) {
		int num = atoi(pos.c_str())-1;
		/*if (num < arr.size())*/
			return arr[num];
		//else
		//	return vec2(0, 0);

	}

	static vector<string> split(string str, vector<string>res, string delim) {

		if ("" == str) 
			return res;
		//�Ƚ�Ҫ�и���ַ�����string����ת��Ϊchar*����
		char* strs = new char[str.length() + 1]; //��Ҫ����
		strcpy(strs, str.c_str());

		char* d = new char[delim.length() + 1];
		strcpy(d, delim.c_str());


		char* p = strtok(strs, d);
		while (p) {
			string s = p; //�ָ�õ����ַ���ת��Ϊstring����
			res.push_back(s); //����������
			p = strtok(NULL, d);
		}

		return res;
	}

};