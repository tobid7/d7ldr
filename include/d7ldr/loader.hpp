#pragma once

#include <d7ldr/common.hpp>

namespace D7LDR {
// Template class implementing a Default
// null Loader if Rosaline was not found
class Loader {
 public:
  Loader() = default;
  virtual ~Loader() = default;
  PD_SMART_CTOR(Loader)

  void SetExitCallback(void (*exit_func)()) { exit_fun = exit_func; }
  void Exit() {
    if (exit_fun) {
      exit_fun();
    }
  }
  virtual bool Init() { return false; }
  virtual void Deinit() {}
  virtual void LoadFile(
      const std::string& path,
      const std::vector<std::string>& args = std::vector<std::string>()) {}
  virtual std::string GetName() { return "null"; }

 protected:
  void ArgBufferInit() {
    auto ref = &arg_data;
    ref->buf[0] = 0;
    ref->pos = reinterpret_cast<char*>(&ref->buf[1]);
  }

  void ArgBufferAdd(const std::string& arg) {
    auto ref = &arg_data;
    size_t len = arg.length() + 1;
    if (ref->pos + len >= (char*)(ref + 1)) {
      // Overflow
      return;
    }
    ref->buf[0]++;
    strcpy(ref->pos, arg.c_str());
    ref->pos += len;
  }

  unsigned int* ArgBufferGetAddress() { return arg_data.buf; }
  size_t ArgBufferGetSize() { return sizeof(arg_data.buf); }

 private:
  struct arg_buffer {
    unsigned int buf[1024 / sizeof(unsigned int)];
    char* pos;
  };
  arg_buffer arg_data;
  void (*exit_fun)();
};
}  // namespace D7LDR