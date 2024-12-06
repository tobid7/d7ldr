#include <d7ldr.h>

#include <d7ldr.hpp>

#ifndef D7LDR_GIT_COMMIT
#define D7LDR_GIT_COMMIT "unknown"
#endif

#ifndef D7LDR_VERSION
#define D7LDR_VERSION "unknown"
#endif

// C Wrapper setup
static D7LDR::Loader* d7ldr_loader = nullptr;

namespace D7LDR {
Loader::Ref GetLoader() {
  Loader::Ref res;
  res = RosalinaLdr::New();
  if (res->Init()) {
    return res;
  }
  res = Loader::New();
  return res;
}

std::string GetVersion() { return D7LDR_VERSION; }
std::string GetGitCommit() { return D7LDR_GIT_COMMIT; }
}  // namespace D7LDR

// C Wrapper Functions
void D7LDR_Init(D7LDR_Loader* ldr) {
  // Generate a New Laoder
  d7ldr_loader = new D7LDR::RosalinaLdr();
  if (!d7ldr_loader->Init()) {
    delete d7ldr_loader;
    d7ldr_loader = new D7LDR::Loader();
  }
  ldr[0] = reinterpret_cast<D7LDR_Loader>(d7ldr_loader);
}

void D7LDR_Deinit(D7LDR_Loader ldr) {
  auto rldr = reinterpret_cast<D7LDR::Loader*>(ldr);
  // Dont do anything if addres is null
  if (!rldr) {
    return;
  }
  // Run deinit
  rldr->Deinit();
  // Cleanup
  delete d7ldr_loader;
  d7ldr_loader = nullptr;
  ldr = nullptr;
}
void D7LDR_SetExitCallback(D7LDR_Loader ldr, void (*exit_func)()) {
  auto rldr = reinterpret_cast<D7LDR::Loader*>(ldr);
  // Dont do anything if addres is null
  if (!rldr) {
    return;
  }
  rldr->SetExitCallback(exit_func);
}
void D7LDR_LoadFile(D7LDR_Loader ldr, const char* path, const char* args[]) {
  auto rldr = reinterpret_cast<D7LDR::Loader*>(ldr);
  // Dont do anything if addres is null
  if (!rldr) {
    return;
  }
  std::vector<std::string> res_args;
  if (args != nullptr) {
    int an = 0;
    const char* arg = args[an++];
    while (arg != nullptr) {
      res_args.push_back(arg);
      arg = args[an++];
    }
  }
  rldr->LoadFile(path, res_args);
}

const char* D7LDR_GetLoaderName(D7LDR_Loader ldr) {
  auto rldr = reinterpret_cast<D7LDR::Loader*>(ldr);
  // Dont do anything if addres is null
  if (!rldr) {
    return "null-address";
  }
  // Create a Copy into a dynamic allocated buffer
  // As the .c_str() looks buggy in c
  static char buf[256];
  strcpy(buf, rldr->GetName().c_str());
  buf[sizeof(buf) - 1] = '\0';
  return buf;
}

const char* D7LDR_GetVersion() { return D7LDR_VERSION; }
const char* D7LDR_GetGitCommit() { return D7LDR_GIT_COMMIT; }