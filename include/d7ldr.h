#ifndef D7LDR_H
#define D7LDR_H

/**
 * C Wapper for the library
 */

#ifdef __cplusplus
#ifndef BUILD_D7LDR
#pragma message( \
    "WARNING: This is the <d7ldr.h> C Header which is a wrapper. For CXX you probably wanna use d7ldr.hpp instead.")
#endif
extern "C" {
#endif

typedef unsigned int* D7LDR_Loader;

void D7LDR_Init(D7LDR_Loader* ldr);
void D7LDR_Deinit(D7LDR_Loader ldr);
void D7LDR_SetExitCallback(D7LDR_Loader ldr, void (*exit_func)());
void D7LDR_LoadFile(D7LDR_Loader ldr, const char* path, const char* args[]);
const char* D7LDR_GetLoaderName(D7LDR_Loader ldr);
const char* D7LDR_GetVersion();
const char* D7LDR_GetGitCommit();
#ifdef __cplusplus
}
#endif

#endif