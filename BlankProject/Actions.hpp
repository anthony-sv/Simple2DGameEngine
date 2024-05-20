#pragma once
#include <string>

namespace SGE2D
{
	class Actions
	{
	public:
		[[nodiscard]] Actions() = default;
		[[nodiscard]] Actions(std::string const& name, std::string const& type);

		std::string const& getName() const;
		std::string const& getType() const;
	private:
		std::string m_name{ "NONE" };
		std::string m_type{ "NONE" };

	};
}