#pragma once

#include <d7ldr/loader.hpp>
#include <d7ldr/rosalina.hpp>

namespace D7LDR {
Loader::Ref GetLoader();
std::string GetVersion();
std::string GetGitCommit();
}  // namespace D7LDR