#include <3ds.h>
#include <d7ldr.h>
#include <stdio.h>

static bool main_loop = true;

void ExitCallback() { main_loop = false; }

int main(int argc, char* argv[]) {
  gfxInitDefault();
  consoleInit(GFX_TOP, NULL);
  printf("D7LDR C Example\n");
  printf("Press Start to Exit\n");
  printf("Press A to Run Universal Updater\n");
  printf("IF YOU DON'T HAVE UNIVERSAL UPDATER AS 3DSX\n");
  printf("YOU WILL SEE A CRASH DUMP SCREEN\n\n");

  D7LDR_Loader loader;
  D7LDR_Init(&loader);
  D7LDR_SetExitCallback(loader, ExitCallback);
  printf("Loader: %s\n", D7LDR_GetLoaderName(loader));
  while (aptMainLoop() && main_loop) {
    hidScanInput();
    if (hidKeysUp() & KEY_A) {
      printf("Launching Universal-Updater...\n");
      D7LDR_LoadFile(loader, "sdmc:/3ds/Universal-Updater.3dsx", NULL);
    }
    if (hidKeysUp() & KEY_START) {
      main_loop = false;
    }
  }
  D7LDR_Deinit(loader);
  return 0;
}