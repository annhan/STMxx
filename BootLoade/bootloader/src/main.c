int main(void) {
 asm( "ldr   r1, =(0x08001000 + 4)\n\t"
      "ldr   r0, [r1]\n\t"
      "bx    r0" );

 return 0;
}