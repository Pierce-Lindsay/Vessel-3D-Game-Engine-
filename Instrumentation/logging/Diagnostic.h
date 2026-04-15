#pragma once
#include <string>
#include <source_location>
#include <chrono>

/// <summary>
/// Create a Diagnostic for an item at this location with the given severity and message.
/// </summary>
#define VE_DIAGNOSTIC(severity, message)  Diagnostic(std::source_location::current(), severity, message)
/// <summary>
/// Create a Diagnostic for an info item at this location with the given message.
/// </summary>
#define VE_INFO_DIAGNOSTIC(message)  Diagnostic(std::source_location::current(), Severity::INFO, message)
/// <summary>
/// Create a Diagnostic for a warning item at this location with the given message.
/// </summary>
#define VE_WARNING_DIAGNOSTIC(message)  Diagnostic(std::source_location::current(), Severity::WARNING, message)
/// <summary>
/// Create a Diagnostic for an error item at this location with the given message.
/// </summary>
#define VE_ERROR_DIAGNOSTIC(message)  Diagnostic(std::source_location::current(), Severity::ERROR, message)

namespace ve
{
	/// <summary>
	/// An enum for represneting the severity of a diagnostic.
	/// </summary>
	enum class Severity
	{
		INFO,
		WARNING,
		ERROR
	};

	/// <summary>
	/// Get the string representtaion of the severity enum.
	/// </summary>
	std::string SeverityToString(Severity severity);

	/// <summary>
	/// A class for storing info about a error/warning/info log.
	/// </summary>
	class Diagnostic
	{
	private:
		Severity severity;
		std::string fileName;
		std::string function;
		size_t line;
		std::string message;
		std::chrono::system_clock::time_point time;		
		//offers the ability to add additional diagnostics to this one that get
		//printed to string with it
		std::vector<Diagnostic> subDiagnostics;
	public:
		/// <summary>
		/// Create a Diagnostic for an item at the given location with the given severity and message.
		/// </summary>
		Diagnostic(const std::source_location& location, Severity severity, const std::string& message);

		/// <summary>
		/// Add an additional diagnostics to this one that gets
		/// printed to string with the main diagnostic.
		/// </summary>
		void AddAdditionalDiagnostic(const Diagnostic& diag);

		/// <summary>
		/// Get all the sub Diagnostics of this Diagnostic.
		/// </summary>
		/// <returns></returns>
		const std::vector<Diagnostic>& GetSubDiagnostics() const;

		/// <summary>
		/// Get a string representtaion of the stored info in the Diagnostic.
		/// </summary>
		std::string ToString() const;

		/// <summary>
		/// Get the severity of the Diagnostic.
		/// </summary>
		Severity GetSeverity() const;

		/// <summary>
		/// Get the file name of the Diagnostic.
		/// </summary>
		const std::string& GetFileName() const;

		/// <summary>
		/// Get the function name of the Diagnostic.
		/// </summary>
		const std::string& GetFunctionName() const;

		/// <summary>
		/// Get the message attached to the Diagnostic.
		/// </summary>
		const std::string& GetMessage() const;

		/// <summary>
		/// Get the line number the diagnostic was created on.
		/// </summary>
		size_t GetLineNumber() const;
	};
}