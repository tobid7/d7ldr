#include <3ds.h>

#include <d7ldr.hpp>
#include <iostream>
#include <string>

static bool main_loop = true;

void ExitCallback() { main_loop = false; }

int main(int argc, char* argv[]) {
  gfxInitDefault();
  consoleInit(GFX_TOP, nullptr);
  std::cout << "D7LDR C++ Example" << std::endl;
  std::cout << "Press Start to Exit" << std::endl;
  std::cout << "Press A to Run Universal Updater" << std::endl;
  std::cout << "IF YOU DON'T HAVE UNIVERSAL UPDATER AS 3DSX" << std::endl;
  std::cout << "YOU WILL SEE A CRASH DUMP SCREEN\n\n";
  auto loader = D7LDR::GetLoader();
  loader->SetExitCallback(ExitCallback);
  std::cout << "Loader: " << loader->GetName() << std::endl;
  while (aptMainLoop() && main_loop) {
    hidScanInput();
    if (hidKeysUp() & KEY_A) {
      std::cout << "Launching Universal-Updater..." << std::endl;
      loader->LoadFile("sdmc:/3ds/Universal-Updater.3dsx");
    }
    if (hidKeysUp() & KEY_START) {
      main_loop = false;
    }
  }
  loader->Deinit();
  return 0;
}