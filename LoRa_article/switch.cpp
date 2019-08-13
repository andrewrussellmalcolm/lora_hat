#include "SX1272.h"
#include <stdio.h>
#include <syslog.h>

int main ()
{
	// set up the LoRa modem
	sx1272.ON();
    sx1272.setMode(4);
  	sx1272.setHeaderON();
 	sx1272.setChannel(CH_17_868);
 	sx1272.setCRC_ON();
  	sx1272.setPower('M');
  	sx1272.setNodeAddress(3);

	// set up GPIO: 2 inputs and one output
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_18,BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_set_pud(RPI_V2_GPIO_P1_18,BCM2835_GPIO_PUD_UP);
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_08,BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_set_pud(RPI_V2_GPIO_P1_08,BCM2835_GPIO_PUD_UP);
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_16,BCM2835_GPIO_FSEL_OUTP);	

	// get the current switch states
	uint8_t oldLev_08=bcm2835_gpio_lev(RPI_V2_GPIO_P1_08); 
	uint8_t oldLev_18=bcm2835_gpio_lev(RPI_V2_GPIO_P1_18); 

	while(1)
	{
		// get the new states
		uint8_t lev_08=bcm2835_gpio_lev(RPI_V2_GPIO_P1_08);
		uint8_t lev_18=bcm2835_gpio_lev(RPI_V2_GPIO_P1_18);

		//if state is different, send message and update
		if(lev_08 != oldLev_08)
		{
			char *msg=(char*)(!lev_08?"ON0":"OFF0");
			syslog(LOG_USER,msg);
	    	uint8_t e = sx1272.sendPacketTimeoutACKRetries(8, msg);

			if(e==0)
			{
				// flash the LED       
				bcm2835_gpio_set(RPI_V2_GPIO_P1_16);
				bcm2835_delay(500);
				bcm2835_gpio_clr(RPI_V2_GPIO_P1_16);
				// update rthe state
				oldLev_08=lev_08;
			}
		}

		//if state is different, send message and update
		if(lev_18 != oldLev_18)
		{
			char *msg = (char*)(!lev_18?"ON1":"OFF1");
			syslog(LOG_USER,msg);
	    	uint8_t e=sx1272.sendPacketTimeoutACKRetries(8, msg);

			if(e==0)
			{
				// flash the LED       
				bcm2835_gpio_set(RPI_V2_GPIO_P1_16);
				bcm2835_delay(500);
				bcm2835_gpio_clr(RPI_V2_GPIO_P1_16);
				// update rthe state
				oldLev_18=lev_18;
			}
		}

		// wait a bit & repeat
		bcm2835_delay(500);
	}
}
