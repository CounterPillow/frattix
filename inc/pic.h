#ifndef PIC_H
#define PIC_H

#include "stdint.h"

#define PIC_MCOMMAND	0x20
#define PIC_MDATA	0x21
#define PIC_MIMR	0x21
#define PIC_SCOMMAND	0xA0
#define PIC_SDATA	0xA1
#define PIC_SIMR	0xA1

void pic_init(void);

void pic_mask_irqs(uint16_t mask);
void pic_send_eoi(int irq);
#endif
