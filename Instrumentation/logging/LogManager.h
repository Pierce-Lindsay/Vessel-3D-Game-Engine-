#pragma once
#include <fstream>
#include <format>
#include <filesystem>
#include <iostream>
#include <expected>
#include "Diagnostic.h"

#define VE_LM ve::LogManager::GetInstance()

/// Macros for logging messages to the log file. Uses the LogManager singleton instance to write the log message.
#define VE_LOG(message)do {if (!VE_LM.IsStarted()) {VE_LM.StartUp();} VE_LM.WriteLog(std::format("LOG::{} in {}\n{}\n{}::{}\n", std::chrono::system_clock::now(), __FUNCSIG__, message, __FILE__, __LINE__));} while(0)
#define VE_WARN(message)do {if (!VE_LM.IsStarted()) {VE_LM.StartUp();} VE_LM.WriteLog(std::format("WARNING::{} in {}\n{}\n{}::{}\n", std::chrono::system_clock::now(), __FUNCSIG__, message, __FILE__, __LINE__));} while(0)
#define VE_ERROR(message)do {if (!VE_LM.IsStarted()) {VE_LM.StartUp();} VE_LM.WriteLog(std::format("ERROR::{} in {}\n{}\n{}::{}\n", std::chrono::system_clock::now(), __FUNCSIG__, message, __FILE__, __LINE__));} while(0)
#define VE_LOG_DIAGNOSTIC(diagnostic) do{if (!VE_LM.IsStarted()) {VE_LM.StartUp();} VE_LM.WriteLog(diagnostic.ToString());} while(0)

//Consumes return value, best when errors are not meant to be propogated, just logged
#define VE_TRY_LOG(exp) do {auto VE_ERROR_ = exp; if(!VE_ERROR_){VE_LOG_DIAGNOSTIC(VE_ERROR_.error()); } else {}} while(0)

namespace ve
{
	/// <summary>
	/// Log Manager class for handling logging operations.
	/// </summary>
	class LogManager
	{
	private:
		LogManager();
		LogManager(LogManager const &copy) = delete;
		void operator=(LogManager const &assign) = delete;

		bool shouldFlush = false;
		bool consolePrint = false;
		bool is_started = false;
		std::ofstream stream;
		const std::string DEFAULT_FILE_NAME = "vessel_log.txt";
		const std::string DEFAULT_FILE_PATH = "logs";
		std::string file_path = DEFAULT_FILE_PATH;
		std::string file_name = DEFAULT_FILE_NAME;
		std::filesystem::path relativeDir = "";


		/// <summary>
		/// Gets the full relative file path of the log files.
		/// </summary>
		std::string GetFullFilePath();
		
		/// <summary>
		/// Rename/moves log file based on the current file name/directory and the old.
		/// </summary>
		std::expected<void, Diagnostic> ResetFile();

		/// <summary>
		/// Creates the required directory according to the manager's directory path
		/// </summary>
		void CreateDirectory();

		/// <summary>
		/// Opens the file stream for the logging file.
		/// </summary>
		std::expected<void, Diagnostic> OpenStream();

	public:

		/// <summary>
		/// Close the file and any other dependencies.
		/// </summary>
		~LogManager();

		/// <summary>
		/// Get instance of the one and only LogManager.
		/// </summary>
		/// <returns></returns>
		static LogManager& GetInstance();

		//LATER-> need better solution, this should be able to return errors but if the log manager
		//isn't working, we have a recursive issue
		/// <summary>
		/// Open/create log file and setup LogManager.
		/// </summary>
		/// <returns>0 if succesfful, negative else.</returns>
		void StartUp();

		/// <summary>
		/// Get whether the log manager is started. 
		/// This indicates whether the log file is open and ready to be written to.
		/// </summary>
		/// <returns></returns>
		bool IsStarted() const;

		/// <summary>
		/// Set whether the log file is flushed to every time it is updated (slower if true).
		/// </summary>
		void SetFlush(bool do_flush = true);

		/// <summary>
		/// Set whether the log file prints to the console aswell.
		/// </summary>
		void SetConsolePrint(bool print = true);

		/// <summary>
		/// Get whether the log file prints to the console aswell.
		/// </summary>
		bool GetConsolePrint() const;

		/// <summary>
		/// Write a line to the log file from the given string.
		/// Adds newline at the end of line. 
		/// </summary>
		/// <param name="line">A string input that is sent to the log.</param>
		void WriteLog(const std::string& line);

		//LATER-> need better solution, this should be able to return errors but if the log manager
		//isn't working, we have a recursive issue
		/// <summary>
		/// Sets the outpath path (directory) log file are placed in.
		/// </summary>
		void SetOutputPath(const std::string& path);

		/// <summary>
		/// Sets the current relative output path to be based on the location of a marker file
		/// with the given name upstream.
		/// </summary>
		/// <param name="rootFile"></param>
		std::expected<void, Diagnostic> SetOutputPathByRoot(const std::string& rootFile);

		/// <summary>
		/// Sets the file name for the output log file.
		/// </summary>
		void SetOutputFileName(const std::string& name);

		/// <summary>
		/// Gets the current set output path (directory) log files are placed in.
		/// </summary>
		const std::string& GetOutputPath() const;

		/// <summary>
		/// Gets the current set output filename of log files.
		/// </summary>
		const std::string& GetOutputFileName() const;
	};
}