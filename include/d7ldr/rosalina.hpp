#pragma once

#include <d7ldr/loader.hpp>

namespace D7LDR {
class RosalinaLdr : public Loader {
 public:
  RosalinaLdr() = default;
  PD_SMART_CTOR(RosalinaLdr)

  bool Init() override;
  void Deinit() override;
  void LoadFile(const std::string& path,
                const std::vector<std::string>& args =
                    std::vector<std::string>()) override;
  std::string GetName() override { return "Rosalina"; }

 private:
  Handle hbldr;
  Result InitHbldr();
  void DeinitHbldr();
  Result SetExec(const std::string& path);
  Result SetArgs(const void* argdata, unsigned int len);
};
}  // namespace D7LDR