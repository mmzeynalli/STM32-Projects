#ifndef QMC5883L_H
#define QMC5883L_H

#include <stdint.h>

#define QMC5883L_WRITE_ADDRESS 0x1AU
#define QMC5883L_READ_ADDRESS 0x1BU

//#define i2c1
#define i2c2

void qmc5883l_init();
uint8_t qmc5883l_is_ready();
void qmc5883l_read_data(uint16_t *x, uint16_t *y, uint16_t *z);


#endif /* QMC5883L_H */

