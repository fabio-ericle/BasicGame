#pragma once
#ifndef RESOURCE_FILE_H
#define RESOURCE_FILE_H

#include <iostream>
#include <string>

class ResourceFile
{
public:
	static const std::string FileToString(const std::string path);
private:
	ResourceFile();
	~ResourceFile();
};

#endif // !RESOURCE_FILE_H


