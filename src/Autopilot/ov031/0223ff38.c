#include <m2c.h>


void **ov38_02221C60(void ***arg0) {
    void **temp_r3;
    void *temp_r2;

    temp_r3 = *arg0;
    if (temp_r3 != NULL) {
        temp_r2 = M2C_FIELD(temp_r3, void **, 0);
        if (temp_r3 == temp_r2) {
            *arg0 = NULL;
        } else {
            M2C_FIELD(temp_r2, void ***, 4) = (void **) M2C_FIELD(temp_r3, void ***, 4);
            *M2C_FIELD(temp_r3, void ***, 4) = M2C_FIELD(temp_r3, void **, 0);
            *arg0 = M2C_FIELD(temp_r3, void ***, 4);
        }
    }
    return temp_r3;
}
