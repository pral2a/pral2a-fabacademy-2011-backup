//
//
// hello.ftdi.44.serial.rgb.c
//
// 115200 baud FTDI character echo, with flash string
//
// set lfuse to 0x7E for 20 MHz xtal
//
//
// Based on Neil Gershenfeld hello.ftdi.serial.echo.c
//
//
// Guillem Camprodon FAB ACADEMY 2011
//
// (c) Massachusetts Institute of Technology 2010
// Permission granted for experimental and personal use;
// license for commercial sale available from MIT.
//


#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

// Some macros that make the code more readable
#define output(directions,pin) (directions |= pin) // set port direction for output
#define set(port,pin) (port |= pin) // set port pin
#define clear(port,pin) (port &= (~pin)) // clear port pin
#define pin_test(pins,pin) (pins & pin) // test for port pin
#define bit_test(byte,bit) (byte & (1 << bit)) // test for bit set
#define output_low(port,pin) port &= ~(1<<pin)
#define output_high(port,pin) port |= (1<<pin)
#define set_input(portdir,pin) portdir &= ~(1<<pin)
#define set_output(portdir,pin) portdir |= (1<<pin)

#define bit_delay_time 8.5 // bit delay for 115200 with overhead
#define bit_delay() _delay_us(bit_delay_time) // RS232 bit delay
#define half_bit_delay() _delay_us(bit_delay_time/2) // RS232 half bit delay
#define char_delay() _delay_ms(10) // char delay

#define serial_port PORTA // set serial
#define serial_direction DDRA // set serial
#define serial_pins PINA // set serial
#define serial_pin_in (1 << PA0) // set input Port
#define serial_pin_out (1 << PA1) // set output Port

// define what pins the LEDs are connected to.
#define RED PA7 // set red led Port
#define GREEN PA6 // set green led Port
#define BLUE PA5 // set blue led Port

void make_color(unsigned char red_glow, unsigned char green_glow, unsigned char blue_glow, unsigned char rate_glow) {
	
   unsigned char i;
   while (rate_glow != 0) {
   	
     output_high(PORTA, RED);
     output_high(PORTA, GREEN);
     output_high(PORTA, BLUE);
     
     for (i=0; i < 255; i++) {
       if (i == red_glow)
         output_low(PORTA, RED);
       if (i == green_glow)
         output_low(PORTA, GREEN);
       if (i == blue_glow)
         output_low(PORTA, BLUE);
     }
     
     rate_glow--;
   }
 }


void get_char(volatile unsigned char *pins, unsigned char pin, char *rxbyte) {
   //
   // read character into rxbyte on pins pin
   //    assumes line driver (inverts bits)
   //
   *rxbyte = 0;
   while (pin_test(*pins,pin))
      //
      // wait for start bit
      //
      ;
   //
   // delay to middle of first data bit
   //
   half_bit_delay();
   bit_delay();
   //
   // unrolled loop to read data bits
   //
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 0);
   else
      *rxbyte |= (0 << 0);
   bit_delay();
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 1);
   else
      *rxbyte |= (0 << 1);
   bit_delay();
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 2);
   else
      *rxbyte |= (0 << 2);
   bit_delay();
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 3);
   else
      *rxbyte |= (0 << 3);
   bit_delay();
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 4);
   else
      *rxbyte |= (0 << 4);
   bit_delay();
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 5);
   else
      *rxbyte |= (0 << 5);
   bit_delay();
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 6);
   else
      *rxbyte |= (0 << 6);
   bit_delay();
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 7);
   else
      *rxbyte |= (0 << 7);
   //
   // wait for stop bit
   //
   bit_delay();
   half_bit_delay();
   }

void put_char(volatile unsigned char *port, unsigned char pin, char txchar) {
   //
   // send character in txchar on port pin
   //    assumes line driver (inverts bits)
   //
   // start bit
   //
   clear(*port,pin);
   bit_delay();
   //
   // unrolled loop to write data bits
   //
   if bit_test(txchar,0)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,1)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,2)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,3)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,4)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,5)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,6)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,7)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   //
   // stop bit
   //
   set(*port,pin);
   bit_delay();
   //
   // char delay
   //
   bit_delay();
   }

void put_flash_string(volatile unsigned char *port, unsigned char pin, PGM_P str) {
   //
   // print a null-terminated string from flash
   //
   static char chr;
   static int index;
   index = 0;
   do {
      chr = pgm_read_byte(&(str[index]));
      put_char(port, pin, chr);
      ++index;
      } while (chr != 0);
   }

void put_ram_string(volatile unsigned char *port, unsigned char pin, char *str) {
   //
   // print a null-terminated string from SRAM
   //
   static int index;
   index = 0;
   do {
      put_char(port, pin, str[index]);
      ++index;
      } while (str[index] != 0);
   }

int main(void) {
   //
   // main
   //
   //
   // set RGB LED
   //
   set_output(DDRA, RED);  
   set_output(DDRA, GREEN);
   set_output(DDRA, BLUE);
   //
   static char chr;
   //
   // set clock divider to /1
   //
   CLKPR = (1 << CLKPCE);
   CLKPR = (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);
   //
   // initialize output pins
   //
   set(serial_port, serial_pin_out);
   output(serial_direction, serial_pin_out);
   //
   // main loop
   //
   while (1) {
   	chr = 0;
      get_char(&serial_pins, serial_pin_in, &chr);
      static char message[] PROGMEM = "make color >> ";
      put_flash_string(&serial_port, serial_pin_out, (PGM_P) message);
      switch(chr){
			case 87: // W
       			make_color(0, 0, 0, 200);
			break;
			case 82: // R
       			make_color(0, 255, 255, 200);
			break;
			case 71: // G
       			make_color(255, 0, 255, 200);
			break;
			case 66: // B
       			make_color(255, 255, 0, 200);
			break;
			case 67: // C
       			make_color(255, 0, 0, 200);
			break;
			case 77: // M
       			make_color(0, 255, 0, 200);
			break;
			case 89: // Y
       			make_color(0, 0, 255, 200);
			break;
			case 75: // K
       			make_color(255, 255, 255, 200);
			break;
			default: 
		 		make_color(255, 255, 255, 200);
		}
		put_char(&serial_port, serial_pin_out, chr); // new line
      	put_char(&serial_port, serial_pin_out, 10); // new line
      }
   }
