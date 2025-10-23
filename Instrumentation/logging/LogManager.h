#pragma once
#include <fstream>
#include <format>

#define LM ve::LogManager::GetInstance()

//ensure this is only used in a game engine object/event object class as getType() must be defined
//this will automatically add class and function to output
#define LOG(message) LM.writeLog(std::format("{}::{}", __FUNCSIG__, message))

namespace ve
{
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
		const std::string DEFAULT_FILE_NAME = "vessle_log.txt";
		const std::string DEFAULT_FILE_PATH = "logs/";
		std::string file_path = DEFAULT_FILE_PATH;
		std::string file_name = DEFAULT_FILE_NAME;


		/// <summary>
		/// Gets the full relative file path of the log files.
		/// </summary>
		std::string getFullFilePath();
		
		/// <summary>
		/// Rename/moves log file based on the current file name/directory and the old.
		/// </summary>
		void resetFilePath(const std::string& old_name);

		/// <summary>
		/// Creates the required directory according to the manager's directory path
		/// </summary>
		void createDirectory();

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
		/// Set whether the log file is flushed to every time it is updated (slower if true).
		/// </summary>
		void setFlush(bool do_flush = true);

		/// <summary>
		/// Set whether the log file prints to the console aswell.
		/// </summary>
		void setConsolePrint(bool print = true);

		/// <summary>
		/// Set whether the log file prints to the console aswell.
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