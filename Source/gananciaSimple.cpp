//
// gananciaSimple.cpp
//
// Code generation for function 'gananciaSimple'
//

// Include files
#include "gananciaSimple.h"
#include "gananciaSimple_types.h"
#include "coder_array.h"

// Function Declarations
static derivedAudioPlugin *getPluginInstance(gananciaSimpleStackData *SD);

static void getPluginInstance_init(gananciaSimpleStackData *SD);

// Function Definitions
static derivedAudioPlugin *getPluginInstance(gananciaSimpleStackData *SD)
{
  if (!SD->pd->plugin_not_empty) {
    //  Pass constructor args to plugin.
    SD->pd->plugin.ganancia = 0.5;
    SD->pd->plugin.PrivateLatency = 0;
    if (!SD->pd->thisPtr_not_empty) {
      SD->pd->thisPtr = 0ULL;
      SD->pd->thisPtr_not_empty = true;
    }
    SD->pd->plugin_not_empty = true;
  }
  return &SD->pd->plugin;
}

static void getPluginInstance_init(gananciaSimpleStackData *SD)
{
  SD->pd->plugin_not_empty = false;
}

derivedAudioPlugin::derivedAudioPlugin()
{
}

derivedAudioPlugin::~derivedAudioPlugin()
{
}

void createPluginInstance(gananciaSimpleStackData *SD,
                          unsigned long long thisPtr)
{
  if (!SD->pd->thisPtr_not_empty) {
    SD->pd->thisPtr = thisPtr;
    SD->pd->thisPtr_not_empty = true;
  }
  getPluginInstance(SD);
}

void gananciaSimple_initialize(gananciaSimpleStackData *SD)
{
  SD->pd->thisPtr_not_empty = false;
  getPluginInstance_init(SD);
}

void gananciaSimple_terminate()
{
  // (no terminate code required)
}

int getLatencyInSamplesCImpl(gananciaSimpleStackData *SD)
{
  derivedAudioPlugin *plugin;
  plugin = getPluginInstance(SD);
  return plugin->PrivateLatency;
}

void onParamChangeCImpl(gananciaSimpleStackData *SD, int paramIdx, double value)
{
  derivedAudioPlugin *plugin;
  plugin = getPluginInstance(SD);
  switch (paramIdx) {
  case 0:
    plugin->ganancia = value;
    break;
  }
}

void processEntryPoint(gananciaSimpleStackData *SD, double samplesPerFrame,
                       const double i1_data[], const int i1_size[1],
                       const double i2_data[], const int i2_size[1],
                       double o1_data[], int o1_size[1], double o2_data[],
                       int o2_size[1])
{
  derivedAudioPlugin *plugin;
  coder::array<double, 2U> t1;
  double b;
  int i;
  int loop_ub;
  plugin = getPluginInstance(SD);
  b = plugin->ganancia;
  t1.set_size(i1_size[0], 2);
  loop_ub = i1_size[0];
  for (i = 0; i < loop_ub; i++) {
    t1[i] = i1_data[i] * b;
  }
  loop_ub = i2_size[0];
  for (i = 0; i < loop_ub; i++) {
    t1[i + t1.size(0)] = i2_data[i] * b;
  }
  if (1.0 > samplesPerFrame) {
    loop_ub = 0;
  } else {
    loop_ub = static_cast<int>(samplesPerFrame);
  }
  o1_size[0] = loop_ub;
  for (i = 0; i < loop_ub; i++) {
    o1_data[i] = t1[i];
  }
  if (1.0 > samplesPerFrame) {
    loop_ub = 0;
  } else {
    loop_ub = static_cast<int>(samplesPerFrame);
  }
  o2_size[0] = loop_ub;
  for (i = 0; i < loop_ub; i++) {
    o2_data[i] = t1[i + t1.size(0)];
  }
}

void resetCImpl(gananciaSimpleStackData *SD, double)
{
  getPluginInstance(SD);
}

// End of code generation (gananciaSimple.cpp)
