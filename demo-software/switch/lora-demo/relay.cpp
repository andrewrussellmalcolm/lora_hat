#include "SX1272.h"
#include <stdio.h>
#include <string.h>

void setRelay(int i)
{
	if(i>0)
	{
		bcm2835_gpio_set(RPI_V2_GPIO_P1_18);
	}
	else
	{
		bcm2835_gpio_clr(RPI_V2_GPIO_P1_18);
	}
}

int main ()
{
	sx1272.ON();
    sx1272.setMode(1);
  	sx1272.setHeaderON();
 	sx1272.setChannel(CH_17_868);
 	sx1272.setCRC_ON();
  	sx1272.setPower('M');
  	sx1272.setNodeAddress(8);

	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_18,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_16,BCM2835_GPIO_FSEL_OUTP);	

	while(1)
	{
    	if (sx1272.receivePacketTimeoutACK(10000) == 0)
        {
            setRelay((strcmp("ON", (char *)sx1272.packet_received.data) == 0));

            printf("%s\n", (char *)sx1272.packet_received.data);

			bcm2835_gpio_set(RPI_V2_GPIO_P1_16);
			bcm2835_delay(500);
			bcm2835_gpio_clr(RPI_V2_GPIO_P1_16);
		}
	}
}
