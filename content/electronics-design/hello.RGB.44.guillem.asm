;
; hello.RGB.44.asm
;
; RGB LED PWM guillem.hello-world
;
; Based on Neil's hello.RGB.45.asm
;
; Neil Gershenfeld
; CBA MIT 11/6/09
;
; (c) Massachusetts Institute of Technology 2009
; Permission granted for experimental and personal use;
; license for commercial sale available from MIT.
;

.include "tn44def.inc"
;
; definitions
;
.equ red = PA7; red pin
.equ green = PA6; green pin
.equ blue = PA5; blue pin
;
; registers
;
.def temp = R16; temporary storage
.def temp1 = R17; temporary storage
.def count = R17; loop counter
.def pwm = R18; PWM counter
;
; code segment
;
.cseg
.org 0
rjmp reset
;
; main program
;
reset:
   ;
   ; set clock divider to /16   ;
   
   ldi temp, (1 << CLKPCE)
   ldi temp1, (1 << CLKPS3) | (1 << CLKPS2) | (1 << CLKPS1) | (1 << CLKPS0)
   out CLKPR, temp
   out CLKPR, temp1
   ;
   ; set stack pointer to top of RAM
   ;
   ldi temp, high(RAMEND)
   out SPH, temp
   ldi temp, low(RAMEND)
   out SPL, temp
   ;
   ; init LED pins for output
   ;
   sbi PORTA, red
   sbi DDRA, red
   sbi PORTA, green
   sbi DDRA, green
   sbi PORTA, blue
   sbi DDRA, blue
   ;
   ; main loop
   ;
   main_loop:
      ldi count, 255
      off_red_loop:
         mov pwm, count
         sbi PORTA, red
         off_red_loop_off:
            dec pwm
            brne off_red_loop_off
         mov pwm, count
         cbi PORTA, red
         off_red_loop_on:
            inc pwm
            brne off_red_loop_on
         dec count
         brne off_red_loop
      ldi count, 255
      red_green_loop:
         mov pwm, count
         cbi PORTA, red
         sbi PORTA, green
         red_green_loop_off:
            dec pwm
            brne red_green_loop_off
         mov pwm, count
         sbi PORTA, red
         cbi PORTA, green
         red_green_loop_on:
            inc pwm
            brne red_green_loop_on
         dec count
	      brne red_green_loop
      green_blue_loop:
         mov pwm, count
         cbi PORTA, green
         sbi PORTA, blue
         green_blue_loop_off:
            dec pwm
            brne green_blue_loop_off
         mov pwm, count
         sbi PORTA, green
         cbi PORTA, blue
         green_blue_loop_on:
            inc pwm
            brne green_blue_loop_on
         dec count
         brne green_blue_loop
      blue_on_loop:
         mov pwm, count
         sbi PORTA, red
         sbi PORTA, green
         blue_on_loop_off:
            dec pwm
            brne blue_on_loop_off
         mov pwm, count
         cbi PORTA, red
         cbi PORTA, green
         blue_on_loop_on:
            inc pwm
            brne blue_on_loop_on
         dec count
         brne blue_on_loop
      on_off_loop:
         mov pwm, count
         cbi PORTA, red
         cbi PORTA, green
         cbi PORTA, blue
         on_off_loop_off:
            dec pwm
            brne on_off_loop_off
         mov pwm, count
         sbi PORTA, red
         sbi PORTA, green
         sbi PORTA, blue
         on_off_loop_on:
            inc pwm
            brne on_off_loop_on
         dec count
         brne on_off_loop
      rjmp main_loop
