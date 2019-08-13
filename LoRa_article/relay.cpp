#include "SX1272.h"
#include <stdio.h>
#include <string.h>

int main ()
{
	// set up the LoRa modem
	sx1272.ON();
    sx1272.setMode(4);
  	sx1272.setHeaderON();
 	sx1272.setChannel(CH_17_868);
 	sx1272.setCRC_ON();
  	sx1272.setPower('M');
  	sx1272.setNodeAddress(8);

	// set up GPIO: 3 outputs
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_26,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_18,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_16,BCM2835_GPIO_FSEL_OUTP);	

	// turn both relays off
	bcm2835_gpio_clr(RPI_V2_GPIO_P1_18);
	bcm2835_gpio_clr(RPI_V2_GPIO_P1_26);
    
	while(1)
	{
		// wait for an incoming message and sens an ACK
    	if (sx1272.receivePacketTimeoutACK(10000) == 0)
        {
			// get the packet data and act on it
            char *msg = (char *)sx1272.packet_received.data;
            printf("%s\n", msg);
            sx1272.getRSSI();

            if(strcmp("ON0", msg)==0)
            {
        		bcm2835_gpio_set(RPI_V2_GPIO_P1_18);
            }            

            if(strcmp("OFF0", msg)==0)
            {
        		bcm2835_gpio_clr(RPI_V2_GPIO_P1_18);
            }

            if(strcmp("ON1", msg)==0)
            {
        		bcm2835_gpio_set(RPI_V2_GPIO_P1_26);
            }            

            if(strcmp("OFF1", msg)==0)
            {
        		bcm2835_gpio_clr(RPI_V2_GPIO_P1_26);
            }
 
			// flash the LED       
			bcm2835_gpio_set(RPI_V2_GPIO_P1_16);
			bcm2835_delay(500);
			bcm2835_gpio_clr(RPI_V2_GPIO_P1_16);
		}
	}
}
