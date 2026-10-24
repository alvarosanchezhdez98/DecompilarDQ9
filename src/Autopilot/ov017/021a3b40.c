#include <m2c.h>

M2C_UNK func_020dae68(void *);
M2C_UNK func_ov003_0217e580(void *);
M2C_UNK func_ov003_0217eec4(void *);
M2C_UNK func_ov003_0217f218(void *);
M2C_UNK func_ov017_021a1880(void *);
M2C_UNK func_ov017_021a5934(void *);
M2C_UNK func_ov017_021a7998(void *);
M2C_UNK func_ov017_021a9248(void *);
M2C_UNK func_ov017_021a9998(void *);
M2C_UNK func_ov017_021aad8c(void *);
M2C_UNK func_ov017_021accfc(void *);
M2C_UNK func_ov017_021adc30(void *);
M2C_UNK func_ov017_021afa70(void *);
M2C_UNK func_ov017_021b1cc4(void *);
M2C_UNK func_ov017_021b1fa0(void *);
M2C_UNK func_ov017_021b2348(void *);
M2C_UNK func_ov017_021b2f0c(void *);
M2C_UNK func_ov017_021b6b5c(void *);
M2C_UNK func_ov017_021b8438(void *);
M2C_UNK func_ov017_021b9904(void *);
M2C_UNK func_ov017_021babc8(void *);
M2C_UNK func_ov017_021bae80(void *);
M2C_UNK func_ov017_021bb930(void *);
M2C_UNK func_ov017_021bef48(void *);
M2C_UNK func_ov017_021c0538(void *);
M2C_UNK func_ov017_021c11f0(void *);
M2C_UNK func_ov017_021c162c(void *);
M2C_UNK func_ov017_021c19f8(void *);

void func_ov017_021a3b40(s32 arg0, void *arg1) {
    s8 temp_r0;

    if (arg1 == NULL) {
        return;
    }
    if (M2C_FIELD(arg1, u8 *, 1) != 0) {
        return;
    }
    temp_r0 = M2C_FIELD(arg1, s8 *, 0);
    switch ((s32) temp_r0) {                        /* irregular */
    case 0x1:
        func_ov017_021adc30(arg1);
        return;
    case 0x2:
        func_ov017_021a1880(arg1);
        return;
    case 0x5:
        func_ov017_021b9904(arg1);
        return;
    case 0xA:
        func_ov017_021b8438(arg1);
        return;
    case 0xC:
        func_ov017_021a5934(arg1);
        return;
    case 0xF:
        func_ov017_021bae80(arg1);
        return;
    case 0x10:
        func_ov017_021babc8(arg1);
        return;
    case 0x11:
        func_ov003_0217e580(arg1);
        return;
    case 0x4:
        func_ov017_021bb930(arg1);
        return;
    case 0x12:
        func_ov017_021b2f0c(arg1);
        return;
    case 0x17:
        func_ov017_021b6b5c(arg1);
        return;
    case 0x18:
        func_ov003_0217eec4(arg1);
        return;
    case 0x1A:
        func_ov017_021aad8c(arg1);
        return;
    case 0x1F:
        func_ov017_021accfc(arg1);
        return;
    case 0x26:
        func_ov017_021afa70(arg1);
        return;
    case 0x28:
        func_ov017_021c0538(arg1);
        return;
    case 0x29:
        func_ov017_021c11f0(arg1);
        return;
    case 0x2A:
        func_ov003_0217f218(arg1);
        return;
    case 0x2B:
        func_ov017_021b1cc4(arg1);
        return;
    case 0x2C:
        func_ov017_021b1fa0(arg1);
        return;
    case 0x2D:
        func_ov017_021b2348(arg1);
        return;
    case 0x2E:
        func_ov017_021c162c(arg1);
        return;
    case 0x2F:
        func_ov017_021c19f8(arg1);
        return;
    case 0x34:
        func_ov017_021bef48(arg1);
        return;
    case 0x38:
        func_ov017_021a9248(arg1);
        return;
    case 0x3A:
        func_ov017_021a9998(arg1);
        return;
    case 0x3F:
        func_ov017_021a7998(arg1);
        return;
    case 0x4B:
        func_020dae68(arg1);
        return;
        return;
    }
}
