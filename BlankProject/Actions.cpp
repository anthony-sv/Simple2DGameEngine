#include "Actions.hpp"


SGE2D::Actions::Actions(std::string const& name, std::string const& type)
	: m_name{ name }, m_type{ type }
{
}

std::string const& SGE2D::Actions::getName() const
{
	return m_name;
}

std::string const& SGE2D::Actions::getType() const
{
	return m_type;
}