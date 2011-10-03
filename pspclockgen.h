
#ifndef __CLOCKGEN_H__
#define __CLOCKGEN_H__

#ifdef __cplusplus
extern "C" {
#endif

int sceClockgenInit();

int sceClockgenEnd();

int sceClockgen_driver_35A667A6(int arg1);

char* sceClockgen_driver_4498E7E1();

int sceClockgen_driver_18512E9D(int arg1);

int sceClockgenAudioClkSetFreq(unsigned int cmd);

int sceClockgenAudioClkEnable();

int sceClockgenAudioClkDisable();

int sceClockgenLeptonClkEnable();

int sceClockgenLeptonClkDisable();

void sceClockgen_driver_C9AF3102(int arg1);

void sceClockgen_driver_D37944FB();

#ifdef __cplusplus
}
#endif

#endif
