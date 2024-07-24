#include "ResourceFile.h"

#include <fstream>
#include <sstream>

ResourceFile::ResourceFile()
{
}

ResourceFile::~ResourceFile()
{
}

const std::string ResourceFile::FileToString(const std::string path)
{
	if (path.empty())
	{
		std::cout << "\nERROR::RESOURCE_FILE::PATH_IS_EMPTY\n";
		return "";
	}

	std::ifstream pathFile;
	pathFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	std::string result;

	try
	{
		pathFile.open(path);
		std::stringstream fileStream;

		fileStream << pathFile.rdbuf();

		pathFile.close();

		result = fileStream.str();
	}
	catch (const std::ifstream::failure error)
	{
		std::cout << "\nERROR::RESOURCE_FILE::FAILED_TO_OPEN_THE_FILE::" << path << "\n";
		std::cout << "\n" << error.what() << "\n";
	}

	return result;
}
