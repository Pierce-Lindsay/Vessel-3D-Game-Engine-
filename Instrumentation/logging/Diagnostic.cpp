#include "Diagnostic.h"

namespace ve
{

	std::string SeverityToString(Severity severity)
	{
		switch (severity)
		{
		case Severity::INFO:
			return "INFO";
		case Severity::WARNING:
			return "WARNING";
		default:
			return "ERROR";
		}
	}
	Diagnostic::Diagnostic(const std::source_location& location, Severity severity, const std::string& message)
		:severity{ severity }, message{ message },
		fileName{ location.file_name() }, function{ location.function_name() }, line{ location.line() },
		time{ std::chrono::system_clock::now() }
	{}

	std::string Diagnostic::ToString() const
	{
		std::string mainDiagnostic = std::format("Diagnostic at time: {} - Serverity: {}\n{}\n Location: {}::Line: {} in {}\n",
			time, SeverityToString(severity), message, function, line, fileName);

		for (auto& diag : subDiagnostics)
		{
			mainDiagnostic += diag.ToString();
		}		
		return mainDiagnostic;
	}

	void Diagnostic::AddAdditionalDiagnostic(const Diagnostic& diag)
	{
		subDiagnostics.push_back(diag);
	}

	const std::vector<Diagnostic>& Diagnostic::GetSubDiagnostics() const
	{
		return subDiagnostics;
	}
	
	Severity Diagnostic::GetSeverity() const
	{
		return severity;
	}
	
	const std::string& Diagnostic::GetFileName() const
	{
		return fileName;
	}

	const std::string& Diagnostic::GetFunctionName() const
	{
		return function;
	}

	const std::string& Diagnostic::GetMessage() const
	{
		return message;
	}

	size_t Diagnostic::GetLineNumber() const
	{
		return line;
	}
}