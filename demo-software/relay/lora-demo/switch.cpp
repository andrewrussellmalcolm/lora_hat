#include "SX1272.h"
#include <stdio.h>

int main ()
{
	sx1272.ON();
    sx1272.setMode(1);
  	sx1272.setHeaderON();
 	sx1272.setChannel(CH_17_868);
 	sx1272.setCRC_ON();
  	sx1272.setPower('M');
  	sx1272.setNodeAddress(3);

	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_18,BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_set_pud(RPI_V2_GPIO_P1_18,BCM2835_GPIO_PUD_UP);
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_16,BCM2835_GPIO_FSEL_OUTP);	

	uint8_t oldLev=bcm2835_gpio_lev(RPI_V2_GPIO_P1_18); 
	while(1)
	{
		uint8_t lev=bcm2835_gpio_lev(RPI_V2_GPIO_P1_18);

		if(lev != oldLev)
		{
			char *msg = (char*)(!lev?"ON":"OFF");
			printf("%s\n",msg);
	    	uint8_t e = sx1272.sendPacketTimeoutACKRetries(8, msg);
printf("e=%d\n",e);

			bcm2835_gpio_set(RPI_V2_GPIO_P1_16);
			bcm2835_delay(500);
			bcm2835_gpio_clr(RPI_V2_GPIO_P1_16);
			oldLev=lev;
		}

		bcm2835_delay(500);
	}
}
