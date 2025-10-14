#pragma once
#include <string>
#include <memory>

namespace ve {
	/// <summary>
	/// A component is a class that is meant to be inherited by
	/// objects that provide a behavior/capabilitis to a gameobject.
	/// </summary>
	class Component
	{
	private:
		std::string type = "component";
	public:

		/// <summary>
		/// Destructs the component and calls the shutdown function.
		/// </summary>
		~Component();

		/// <summary>
		/// Returns the type as a string.
		/// </summary>
		/// <returns>A string representing the type.</returns>
		const std::string& getType() const;

		/// <summary>
		/// Sets the type of the object.
		/// </summary>
		/// <param name="type">The type to assign to the object.</param>
		void setType(const std::string& type);

		/// <summary>
		/// Called once before this component expereinces its first update call.
		/// </summary>
		virtual void start();

		/// <summary>
		/// Called once either when destructed/deleted.
		/// </summary>
		virtual void shutdown();

		/// <summary>
		/// Called every frame by engine
		/// </summary>
		virtual void update();
	};
}

