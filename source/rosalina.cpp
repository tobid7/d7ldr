#include <d7ldr/rosalina.hpp>

namespace D7LDR {
bool RosalinaLdr::Init() {
  if (R_FAILED(this->InitHbldr())) {
    return false;
  }
  return true;
}

void RosalinaLdr::Deinit() { this->DeinitHbldr(); }

void RosalinaLdr::LoadFile(const std::string& path,
                           const std::vector<std::string>& args) {
  std::string res = path;
  if (path.substr(0, 6) == "sdmc:/") {
    res = path.substr(5, path.length() - 5);
  }
  this->ArgBufferInit();
  // Using default path with sdmc here
  this->ArgBufferAdd(path);
  for (const auto& it : args) {
    this->ArgBufferAdd(it);
  }
  // Path without sdmc: cause FSUSER in loader module
  this->SetExec(res);
  this->SetArgs(this->ArgBufferGetAddress(), this->ArgBufferGetSize());
  this->Exit();
}

Result RosalinaLdr::InitHbldr() {
  return svcConnectToPort(&this->hbldr, "hb:ldr");
}

void RosalinaLdr::DeinitHbldr() { svcCloseHandle(this->hbldr); }

Result RosalinaLdr::SetExec(const std::string& path) {
  unsigned int* cmd = reinterpret_cast<unsigned int*>(getThreadCommandBuffer());
  cmd[0] = IPC_MakeHeader(2, 0, 2);
  cmd[1] = IPC_Desc_StaticBuffer(path.length() + 1, 0);
  cmd[2] = (unsigned int)path.c_str();
  Result ret = svcSendSyncRequest(hbldr);
  if (R_FAILED(ret)) {
    ret = cmd[1];
  }
  return ret;
}
Result RosalinaLdr::SetArgs(const void* argdata, unsigned int len) {
  unsigned int* cmd = reinterpret_cast<unsigned int*>(getThreadCommandBuffer());

  cmd[0] = IPC_MakeHeader(3, 0, 2);
  cmd[1] = IPC_Desc_StaticBuffer(len, 1);
  cmd[2] = (unsigned int)argdata;

  Result ret = svcSendSyncRequest(hbldr);
  if (R_SUCCEEDED(ret)) {
    ret = cmd[1];
  }
  return ret;
}
}  // namespace D7LDR