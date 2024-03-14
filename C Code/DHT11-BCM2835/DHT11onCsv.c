#include <bcm2835.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>

#define DEBUG

#define DHT_PIN RPI_BPLUS_GPIO_J8_07   // GPIO pin for DHT11

#define DHT11_OK              0
#define DHT11_ERROR_ARG       -1
#define DHT11_ERROR_CHECKSUM  -2
#define DHT11_ERROR_TIMEOUT   -3

/** 
 * How long to spin, waiting for input.
 */
#define DHT11_MAXCOUNT 32000

/**
 * Number of bit pulses to expect from the DHT.  Note that this is 41 because
 * the first pulse is a constant 50 microsecond pulse, with 40 pulses to
 * represent the data afterwards.
 */
#define DHT11_PULSES	41

int dht11_read(int pin, float *humidity, float *temperature)
{
	/* Make sure output pointers are probably ok */
  if (humidity == NULL || temperature == NULL ) {
    return DHT11_ERROR_ARG;
  }

  *humidity = 0.0f;
  *temperature = 0.0f;

  /* Array to store length of low and high pulses from the sensor */
  int pulseWidths[DHT11_PULSES*2] = {0};

  /* Signal sensor to output it's data. High for ~500ms then low for ~20ms */
  bcm2835_gpio_fsel(DHT_PIN, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_write(DHT_PIN, HIGH);

	bcm2835_delay(500);
  bcm2835_gpio_write(DHT_PIN, LOW);
  bcm2835_delay(20);

  /* Time the pulses coming in */
  bcm2835_gpio_fsel(DHT_PIN, BCM2835_GPIO_FSEL_INPT);
  /* Tiny delay to let pin stabilise as input pin and let voltage come up */
  for(volatile int i=0; i<50; i++);

  /* Wait for HIGH->LOW edge */
  uint32_t count = 0;
  while (bcm2835_gpio_lev(DHT_PIN)) {
    if (++count > DHT11_MAXCOUNT) {
      return DHT11_ERROR_TIMEOUT;
    }
  }
  
  /* Record pulse widths */
  int pulse=0;
  
  while (pulse < DHT11_PULSES*2) {
    /* Time low */
    while (!bcm2835_gpio_lev(DHT_PIN)) {
      if (++pulseWidths[pulse] > DHT11_MAXCOUNT) {
        return DHT11_ERROR_TIMEOUT;
      }
    }
    ++pulse;
    /* Time high */
    while (bcm2835_gpio_lev(DHT_PIN)) {
      if (++pulseWidths[pulse] > DHT11_MAXCOUNT) {
        return DHT11_ERROR_TIMEOUT;
      }
    }
    ++pulse;
  }

  /* Convert pulse widths to bits and bytes */
  uint8_t bytes[5] = {0};
  uint8_t bit = 0;
  pulse = 2; /* Skip over initial bit */
  while (pulse < DHT11_PULSES*2) {
#ifdef DEBUG
    printf( 
      "Bit: %2d Byte: %2d Low: %3d High: %3d -> %1d  = 0x%2x\n", 
      bit,
      bit>>3,
      pulseWidths[pulse],
      pulseWidths[pulse+1],
      pulseWidths[pulse] <
      pulseWidths[pulse+1],
      bytes[bit>>3]
    );
    if (pulse % 16 == 0)
      puts("");
#endif

    bytes[bit>>3] <<= 1;
	 if(pulseWidths[pulse] < pulseWidths[++pulse]){
      /* High part is longer than the preceding low, so this bit is a 1. */ 
      bytes[bit>>3] |= 1;
    }
    /* Otherwise high part is shorter, this bit is a 0 */

    ++bit;
    ++pulse;
  }

#ifdef DEBUG
  printf( "Data: %02x %02x %02x %02x Checksum: %02x : %02x\n",
    bytes[0],
    bytes[1],
    bytes[2],
    bytes[3],
    bytes[4],
    ((bytes[0] + bytes[1] + bytes[2] + bytes[3]) & 0xff)
    );

  /* If debugging, set outputs regardless of checksum validity */
  *humidity = (float)bytes[0];
  *temperature = (float)bytes[2];
#endif

  /* Check the checksum */
  if (bytes[4] != ((bytes[0] + bytes[1] + bytes[2] + bytes[3]) & 0xff)) {
    return DHT11_ERROR_CHECKSUM;
  }

  /* All good, put the data in the vars :-) */
  *humidity = (float)bytes[0];
  *temperature = (float)bytes[2];

  return DHT11_OK;
}

int main(){
	
	FILE *file;
   char *filename = "data.csv";
	float humidity=0, temperature=0;   
	
	while(1){
    if (!bcm2835_init()) {
      printf("bcm2835_init failed. Are you running as root?\n");
      return 1;
    }

    int tries;

    for (tries = 3; tries > 0; --tries) {
      int ret = dht11_read(DHT_PIN, &humidity, &temperature);
      if (ret == DHT11_OK ) {
        printf("Humidity: %2.0f%% RH, Temperature: %2.0f C\n", humidity, temperature);
        break;
      }
      else if (ret == DHT11_ERROR_CHECKSUM) {
        puts("Checksum error.");
      }
      else {
        puts("Timeout.");
      }
    }
    if (tries == 0) {
      puts("Ran out of tries.");
    }
  
    //SCRITTURA FILE
    // Open the file in "a" mode (append content to existing file)
    file = fopen(filename, "a");
        
    if (file == NULL) {
      printf("Error opening file\n");
      exit(1);
    } 
    else {
      printf("File opened correctly\n");
      fprintf(file, "%0.f,%0.f\n", temperature, humidity);
      fflush(file);
    }
    fclose(file);
    printf("File closed\n");  

    bcm2835_delay(1000);
    bcm2835_close();
  }
  return 0;
}
