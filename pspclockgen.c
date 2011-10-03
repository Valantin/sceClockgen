#include <pspsdk.h>
#include <pspsysevent.h>

PSP_MODULE_INFO("sceClockgen_Driver", 1007, 1, 8);

/*
 * Imports from library: sceI2c_driver
 */
extern int sceI2c_driver_8ABA796F (int arg1, int arg2, int arg3);
extern void sceI2c_driver_9F3CBEA3 (int arg1, int arg2);
extern int sceI2c_driver_C7DF1502 (int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);

SceUID mtid = -1; //0x000008E0
int g0x000008E4; //0x000008E4
int g0x000008E8[3]; //0x000008E8
PspSysEventHandler sysevent; //0x000008F0

int module_start(SceSize args, void *argp) {
    sceClockgenInit();
    sceClockgen_driver_D37944FB();
    g0x000008E4 = 1;
    return 0;
}

int sub_00000678 (int arg1, int arg2) {
    int ret = 0x80000102;
    int var1[2];
    if(arg1 < 3) {
        var1[0] = arg1 -128;
        var1[1] = arg2;
        int i2c = sceI2c_driver_8ABA796F(0xD2, var1, 2);
        ret = (i2c < 0) ? i2c : 0;
    }
    return ret;
}

int module_reboot_before (SceSize args, void *argp) {
    int var1 = g0x000008EA;
    int var2 = g0x000008ED;
    asm("ins %0, $zr, 0, 3" : "=r" (var1));
    if((g0x000008EA & 7) == (g0x000008ED & 7)) {
        sub_00000678(2, t0 | var2);
    }
    sceClockgenEnd();
    return 0;
}

int sceClockgenInit() {
    sceI2c_driver_9F3CBEA3(4, 4);
    SceUID temp = sceKernelCreateMutex("SceClockgen", 1, 0, NULL);
    if(temp >= 0) {
        sceKernelRegisterSysEventHandler(&sysevent);
        mtid = temp;
    }
    return 0;
}

int sceClockgenEnd() {
    if(mtid >= 0) {
        sceKernelDeleteMutex(mtid);
        mtid = -1;
    }
    sceKernelUnregisterSysEventHandler(&sysevent);
    return 0;
}

int sceClockgen_driver_35A667A6(int arg1) { //SET
    g0x000008E4 = arg1;
    return 0;
}

char* sceClockgen_driver_4498E7E1() {
    return g0x000008E8;
}

int sceClockgen_driver_18512E9D(int arg1) {
    int ret = 0x80000102;
    if(arg1 < 3) {
        ret = g0x000008E8[arg1];
    }
    return ret;
}

int sceClockgenAudioClkSetFreq(unsigned int cmd) {
    int ret = 0x800001FE;
    if(cmd = 0xAC44) {
        ret = sub_000005D4(1, 0);
    } else if(cmd == 0xBB80) {
        ret = sub_000005D4(1, 1);
    }
    return ret;
}

int sceClockgenAudioClkEnable() { 
    return sub_000005D4 (0x10, 0);
}

int sceClockgenAudioClkDisable() {
    return sub_000005D4 (0x10, 0);
}

int sceClockgenLeptonClkEnable() {
    return sub_000005D4 (8, 1);
}

int sceClockgenLeptonClkDisable() {
    return sub_000005D4 (8, 0);
}
