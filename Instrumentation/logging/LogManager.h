#pragma once
#include <fstream>
#include <format>
#include <filesystem>
#include <iostream>

#define LM ve::LogManager::GetInstance()

/// Macros for logging messages to the log file. Uses the LogManager singleton instance to write the log message.
#define VE_LOG(message) if (!LM.isStarted()) {LM.startUp();} LM.writeLog(std::format("LOG::{} in {}\n{}\n{}::{}\n", std::chrono::system_clock::now(), __FUNCSIG__, message, __FILE__, __LINE__)); 
#define VE_WARN(message) if (!LM.isStarted()) {LM.startUp();} LM.writeLog(std::format("WARNING::{} in {}\n{}\n{}::{}\n", std::chrono::system_clock::now(), __FUNCSIG__, message, __FILE__, __LINE__)); 
#define VE_ERROR(message) if (!LM.isStarted()) {LM.startUp();} LM.writeLog(std::format("ERROR::{} in {}\n{}\n{}::{}\n", std::chrono::system_clock::now(), __FUNCSIG__, message, __FILE__, __LINE__)); 
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
		std::string getFullFilePath();
		
		/// <summary>
		/// Rename/moves log file based on the current file name/directory and the old.
		/// </summary>
		void resetFile();

		/// <summary>
		/// Creates the required directory according to the manager's directory path
		/// </summary>
		void createDirectory();

		/// <summary>
		/// Opens the file stream for the logging file.
		/// </summary>
		void openStream();

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

		/// <summary>
		/// Open/create log file and setup LogManager.
		/// </summary>
		/// <returns>0 if succesfful, negative else.</returns>
		int startUp();

		/// <summary>
		/// Get whether the log manager is started. 
		/// This indicates whether the log file is open and ready to be written to.
		/// </summary>
		/// <returns></returns>
		bool isStarted() const;

		/// <summary>
		/// Set whether the log file is flushed to every time it is updated (slower if true).
		/// </summary>
		void setFlush(bool do_flush = true);

		/// <summary>
		/// Set whether the log file prints to the console aswell.
		/// </summary>
		void setConsolePrint(bool print = true);

		/// <summary>
		/// Get whether the log file prints to the console aswell.
		/// </summary>
		bool getConsolePrint() const;

		/// <summary>
		/// Write a line to the log file from the given string. Returns 1 if successful.
		/// Adds newline at the end of line. 
		/// </summary>
		/// <param name="line">A string input that is sent to the log.</param>
		int writeLog(const std::string& line);

		/// <summary>
		/// Sets the outpath path (directory) log file are placed in.
		/// </summary>
		void setOutputPath(const std::string& path);

		/// <summary>
		/// Sets the current relative output path to be based on the location of a marker file
		/// with the given name upstream.
		/// </summary>
		/// <param name="rootFile"></param>
		void setOutputPathByRoot(const std::string& rootFile);

		/// <summary>
		/// Sets the file name for the output log file.
		/// </summary>
		void setOutputFileName(const std::string& name);

		/// <summary>
		/// Gets the current set output path (directory) log files are placed in.
		/// </summary>
		const std::string& getOutputPath() const;

		/// <summary>
		/// Gets the current set output filename of log files.
		/// </summary>
		const std::string& getOutputFileName() const;
	};
}