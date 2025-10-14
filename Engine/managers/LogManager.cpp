#include "LogManager.h"
#include <iostream>
#include <stdio.h>
#include <exception>
#include <ctime>
#include <cstdio>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstdarg>
#include <format>

//for cross-platform
#ifdef _WIN32
#include <direct.h> // For Windows _mkdir
#define MAKE_DIRECTORY(path) _mkdir(path)
#else
#include <sys/stat.h>
#include <sys/types.h>
#define MAKE_DIRECTORY(path) mkdir(path, 0777) // 0777 for full permissions
#endif


using namespace ve;

std::exception FILE_POINTER_NULL = std::exception("Log manager error, The file pointer as null.");
std::exception FILE_RENAME_ERROR = std::exception("Log manager error, failed to rename file.");
LogManager::LogManager()
{
	setType("LogManager");
}

LogManager::~LogManager()
{
}

LogManager& LogManager::GetInstance()
{
	static LogManager lm;
	return lm;
}

int LogManager::startUp()
{
	//create directory if doesn't exist
	createDirectory();

	std::string full_path = (file_path + file_name);
	stream = std::ofstream(full_path);
	if(!stream.is_open())
	{ //failed to open file
		return -1;
	}
	
	//writeLog(std::format("{}::{}: Log Manager successfully started!", getType(), __func__));
	//writeLog("LogManager::startUp: LogManager successfully started!");
	LOG("Log Manager successfully started!");
	return Manager::startUp();
}

void LogManager::shutDown()
{
	//writeLog("LogManager::shutDown: LogManager successfully shutdown!");
	LOG("LogManager successfully shutdown!");
	stream.close();
	Manager::shutDown();
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


void LogManager::setOutputPath(const std::string& path)
{
	std::string old_name = getFullFilePath();
	file_path = path;
	resetFilePath(old_name.c_str());
}

void LogManager::setOutputFileName(const std::string& name)
{
	std::string old_name = getFullFilePath();
	file_name = name;
	resetFilePath(old_name.c_str());
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
	return (file_path + file_name);
}

void LogManager::resetFilePath(const std::string& old_name)
{
	if (!stream.is_open()) //rename/move file
	{
		createDirectory(); //make sure new dir exists
		auto new_name = getFullFilePath();
		if (rename(old_name.c_str(), new_name.c_str()) != 0)
			throw FILE_RENAME_ERROR;
	}
}

void LogManager::createDirectory()
{
	MAKE_DIRECTORY(file_path.c_str());
}