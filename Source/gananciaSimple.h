//
// gananciaSimple.h
//
// Code generation for function 'gananciaSimple'
//

#ifndef GANANCIASIMPLE_H
#define GANANCIASIMPLE_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
struct gananciaSimpleStackData;

// Type Definitions
class derivedAudioPlugin {
public:
  derivedAudioPlugin();
  ~derivedAudioPlugin();
  int PrivateLatency;
  double ganancia;
};

// Function Declarations
extern void createPluginInstance(gananciaSimpleStackData *SD,
                                 unsigned long long thisPtr);

extern void gananciaSimple_initialize(gananciaSimpleStackData *SD);

extern void gananciaSimple_terminate();

extern int getLatencyInSamplesCImpl(gananciaSimpleStackData *SD);

extern void onParamChangeCImpl(gananciaSimpleStackData *SD, int paramIdx,
                               double value);

extern void processEntryPoint(gananciaSimpleStackData *SD,
                              double samplesPerFrame, const double i1_data[],
                              const int i1_size[1], const double i2_data[],
                              const int i2_size[1], double o1_data[],
                              int o1_size[1], double o2_data[], int o2_size[1]);

extern void resetCImpl(gananciaSimpleStackData *SD, double rate);

#endif
// End of code generation (gananciaSimple.h)
