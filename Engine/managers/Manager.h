#pragma once
#include <string>

namespace ve
{
	/// <summary>
	/// A base class for managing in the game engine.
	/// </summary> 
	class Manager
	{
	private:
		std::string type = "undefined";
		bool is_started = false;
		bool is_shutdown = false;

	protected:

		/// <summary>
		/// Set type identifier of this manager
		/// </summary>
		void setType(const std::string& type);

	public:
		Manager();

		/// <summary>
		/// Destructs dependencies, and automatically calls shutdown if hasn't been shutdown yet.
		/// </summary>
		virtual ~Manager();

		
		/// <summary>
		/// Get type identifier of manager
		/// </summary>
		const std::string& getType() const;
		
		/// <summary>
		/// Startup manager.
		/// Returns 0 if ok, else negative number.
		virtual int startUp();

		/// <summary>
		/// Shutdown manager
		/// </summary>
		virtual void shutDown();

		/// <summary>
		/// Is the manager started? Has startUp been called successfully.
		/// </summary>
		/// <returns>True if the manager is strated.</returns>
		bool isStarted() const;
	};
}