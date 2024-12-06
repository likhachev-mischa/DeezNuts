#include "File.hpp"

#include <fstream>
#include <sstream>

std::string readShaderFile(const std::string& filePath)
{
	std::string shaderCode;
	std::ifstream shaderFile(filePath, std::ios::in);

	while (shaderFile.good())
	{
		std::string line;
		std::getline(shaderFile, line);
		shaderCode.append(line + "\n");
	}
	return shaderCode;
}

void readModelInfoFile(const char* filename, std::vector<glm::vec3>& vertices, std::vector<int>& indices)
{
	vertices.clear();
	indices.clear();

	std::ifstream file(filename, std::ios::in);

	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open file!");
	}
	std::string str;

	while (std::getline(file, str))
	{
		char key = str[0];
		str.erase(0, 1);
		if (key == 'v')
		{
			glm::vec3 vertex;
			std::istringstream iss(str);
			for (int i = 0; i < 3; ++i)
			{
				iss >> vertex[i];
			}
			vertices.push_back(vertex);
		}
		else if (key == 'f')
		{
			std::istringstream iss(str);
			int index;
			while (iss >> index)
			{
				indices.push_back(index);
			}
		}
	}
}
