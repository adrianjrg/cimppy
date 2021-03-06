#include <string>

#include "cimppy/cimppy.hpp"

#include <fmt/core.h>

exported_class::exported_class()
    : m_name {fmt::format("{}", "cimppy")}
{
}

auto exported_class::name() const -> const char*
{
  return m_name.c_str();
}
