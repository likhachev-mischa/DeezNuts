#pragma once
#include <string>
#include <vector>

#include <glm/vec3.hpp>

std::string readShaderFile(const std::string& filePath);

void readModelInfoFile(const char* filename, std::vector<glm::vec3>& vertices, std::vector<int>& indices);
