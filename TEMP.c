#include<lpc21xx.h>
#define bit(x) (1<<x)
#define DELAY_VALUE 5000000
#define GPIO_PIN_A (1 << 16)  // Assuming pin 16 is being used

void DELAY(unsigned long VALUE);

void ext_interrupt(void) __irq
{
    EXTINT = bit(1);  // Using bit() macro for better readability
    DELAY(DELAY_VALUE);
    VICVectAddr = 0x00000000;
}

void init_ext(void)
{
    PINSEL0 |= bit(29);  // Assuming bit 29 is being used
    EXTMODE = bit(1);
    EXTPOLAR = bit(1);
    VICVectAddr0 = (unsigned int)ext_interrupt;
    VICVectCntl0 = 0x0000002F;
    VICIntEnable = bit(15);
}

int main(void)
{
    unsigned int temp = GPIO_PIN_A;  // Move declaration to the beginning
    IO0DIR = 0x00FF0000;
    init_ext();
    
    while(1)
    {
        IO0SET |= temp;
        DELAY(1000000);
        IO0CLR |= temp;
        temp <<= 1;
        if(temp == bit(24))
            temp = GPIO_PIN_A;
        DELAY(1000000);
    }
}

void DELAY(unsigned long VALUE)
{
    while(VALUE > 0)
    {
        VALUE--;
    }
}
