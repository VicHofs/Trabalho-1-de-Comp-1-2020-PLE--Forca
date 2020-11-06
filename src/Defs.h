#ifndef _DEFS_H
#define _DEFS_H

  #if defined(_WIN32) || defined(_WIN64)
    #define CLEAR "cls"
  #elif defined(__unix__) || defined(__APPLE__)
    #define CLEAR "clear"
  #endif

#define MAXW 205

#endif