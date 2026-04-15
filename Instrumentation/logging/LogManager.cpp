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

void LogManager::StartUp()
{
	if (auto e = ResetFile(); !e)
	{
		std::cout << (e.error()).ToString() << '\n';
		return;
	}
	is_started = true;
	VE_LOG("Log Manager successfully started!");
}

bool LogManager::IsStarted() const
{
	return is_started;
}

void LogManager::SetFlush(bool shouldFlush)
{
	this->shouldFlush = shouldFlush;
}

void LogManager::WriteLog(const std::string& line)
{
	if (!stream.is_open())
	{
		std::cout << VE_ERROR_DIAGNOSTIC("Faliure to open stream when attempting write log!").ToString() << '\n';
		return;
	}

	stream << line << '\n';

	if(consolePrint)
		std::cout << line << '\n';

	if (shouldFlush)
		stream.flush();
}


void LogManager::SetConsolePrint(bool print)
{
	consolePrint = print;
}


bool LogManager::GetConsolePrint() const
{
	return consolePrint;
}

std::expected<void, Diagnostic> LogManager::SetOutputPathByRoot(const std::string& rootFile)
{
	auto pathToRoot = FileUtils::GetPathToMarker(rootFile);

	if (std::filesystem::exists(pathToRoot / rootFile))
	{
		relativeDir = pathToRoot;
		if (auto e = ResetFile(); !e)
			return std::unexpected(std::move(e.error()));
	}
	else
	{
		return std::unexpected(VE_ERROR_DIAGNOSTIC(std::format("marker file: {} not found!", rootFile)));
	}
	return {};
}

std::expected<void, Diagnostic> LogManager::OpenStream()
{
	std::string full_path = (file_path + "/" + file_name);
	stream = std::ofstream(relativeDir / full_path);
	if (!stream.is_open())
	{ //failed to open file
		return std::unexpected(VE_ERROR_DIAGNOSTIC("Failed to open log: " + std::string(strerror(errno))));
	}
	return {};
}


void LogManager::SetOutputPath(const std::string& path)
{
	file_path = path;
	ResetFile();
}

void LogManager::SetOutputFileName(const std::string& name)
{
	file_name = name;
	ResetFile();
}

const std::string& LogManager::GetOutputPath() const
{
	return file_path;
}

const std::string& LogManager::GetOutputFileName() const
{
	return file_name;
}

std::string LogManager::GetFullFilePath()
{
	return (relativeDir / file_path / file_name).string();
}

std::expected<void, Diagnostic> LogManager::ResetFile()
{
	if (stream.is_open())
	{
		stream.flush();
		stream.close();
	}
	CreateDirectory(); //make sure new dir exists

	if (auto e = OpenStream(); !e)
		return std::unexpected(std::move(e.error()));

	return {};
}

void LogManager::CreateDirectory()
{
	try {
		std::filesystem::create_directories(relativeDir / file_path);
	}
	catch (const std::filesystem::filesystem_error& e) {
		std::cerr << e.what();
	}
}