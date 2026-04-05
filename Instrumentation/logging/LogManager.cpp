#include "LogManager.h"
#include <iostream>
#include <stdio.h>
#include <exception>
#include <ctime>
#include <filesystem>
#include "../files/FileUtils.h"

using namespace ve;

LogManager::LogManager()
{
	relativeDir = std::filesystem::current_path();
}

LogManager::~LogManager()
{
	//if we havn't been shutdown, do it now

	VE_LOG("LogManager successfully shutdown!");
	if (stream.is_open())
	{
		stream.flush();
		stream.close();
	}
}

LogManager& LogManager::GetInstance()
{
	static LogManager lm;
	return lm;
}

int LogManager::startUp()
{
	resetFile();
	is_started = true;
	VE_LOG("Log Manager successfully started!");
	return 0;
}

bool LogManager::isStarted() const
{
	return is_started;
}

void LogManager::setFlush(bool shouldFlush)
{
	this->shouldFlush = shouldFlush;
}

int LogManager::writeLog(const std::string& line)
{
	if (!stream.is_open())
		return -1;

	stream << line << '\n';
	if(consolePrint)
		std::cout << line << '\n';

	if (shouldFlush)
		stream.flush();

	return 1;
}


void LogManager::setConsolePrint(bool print)
{
	consolePrint = print;
}


bool LogManager::getConsolePrint() const
{
	return consolePrint;
}

void LogManager::setOutputPathByRoot(const std::string& rootFile)
{
	auto pathToRoot = FileUtils::GetPathToMarker(rootFile);

	if(std::filesystem::exists(pathToRoot/ rootFile))
		relativeDir = pathToRoot;
	else
		std::cout << "marker file not found!" << '\n';
}

void LogManager::openStream()
{
	std::string full_path = (file_path + "/" + file_name);
	stream = std::ofstream(relativeDir / full_path);
	if (!stream.is_open())
	{ //failed to open file
		std::cerr << "Failed to open log: " << strerror(errno) << std::endl;
	}
}


void LogManager::setOutputPath(const std::string& path)
{
	file_path = path;
	resetFile();
}

void LogManager::setOutputFileName(const std::string& name)
{
	file_name = name;
	resetFile();
}

const std::string& LogManager::getOutputPath() const
{
	return file_path;
}

const std::string& LogManager::getOutputFileName() const
{
	return file_name;
}

std::string LogManager::getFullFilePath()
{
	return (relativeDir / file_path / file_name).string();
}

void LogManager::resetFile()
{
	if (stream.is_open())
	{
		stream.flush();
		stream.close();
	}
	createDirectory(); //make sure new dir exists
	openStream();
}

void LogManager::createDirectory()
{
	try {
		std::filesystem::create_directories(relativeDir / file_path);
	}
	catch (const std::filesystem::filesystem_error& e) {
		std::cerr << e.what();
	}
}