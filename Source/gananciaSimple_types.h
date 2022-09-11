//
// gananciaSimple_types.h
//
// Code generation for function 'onParamChangeCImpl'
//

#ifndef GANANCIASIMPLE_TYPES_H
#define GANANCIASIMPLE_TYPES_H

// Include files
#include "gananciaSimple.h"
#include "rtwtypes.h"

// Type Definitions
struct gananciaSimplePersistentData {
  derivedAudioPlugin plugin;
  boolean_T plugin_not_empty;
  unsigned long long thisPtr;
  boolean_T thisPtr_not_empty;
};

struct gananciaSimpleStackData {
  gananciaSimplePersistentData *pd;
};

#endif
// End of code generation (gananciaSimple_types.h)
