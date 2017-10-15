// crt_rot.c  
/* This program shifts values to rotate an integer.  
 */  

#include <stdlib.h>  
#include <stdio.h>  

uint32_t _rotl(uint32_t value, int shift) {
    if ((shift &= 31) == 0)
        return value;
    return (value << shift) | (value >> (32 - shift));
}

uint32_t _rotr(uint32_t value, int shift) {
    if ((shift &= 31) == 0)
        return value;
    return (value >> shift) | (value << (32 - shift));
}


#if 0
uint64_t _rotl64(uint64_t value, int shift) {
    if ((shift &= 63) == 0)
        return value;
    return (value << shift) | (value >> (64 - shift));
}

uint64_t _rotr64(uint64_t value, int shift) {
    if ((shift &= 63) == 0)
        return value;
    return (value >> shift) | (value << (64 - shift));
}

#else
inline  uint32_t _rotr(uint32_t x, uint8_t r) {
    asm("rorl %1,%0" : "+r" (x) : "c" (r));
    return x;
}

inline  uint32_t _rotl(uint32_t x, uint8_t r) {
    asm("roll %1,%0" : "+r" (x) : "c" (r));
    return x;
}

inline uint64_t _rotr64 (uint64_t x , uint8_t r)
{
    asm("rorq %1,%0" : "+r" (x) : "c" (r));
    return x;
}

inline uint64_t _rotl64 (uint64_t x , uint8_t r)
{
    asm("rolq %1,%0" : "+r" (x) : "c" (r));
    return x;
}
#endif

int main( void )  
{  
    unsigned val = 0x0fd93;  
    int64_t val2 = 0x0101010101010101;  

    printf( "0x%4.4x rotated left three times is 0x%4.4x\n",   
            val, _rotl( val, 3 ) );  
    printf( "0x%4.4x rotated right four times is 0x%4.4x\n",   
            val, _rotr( val, 4 ) );  
#if 1
    printf( "%llx rotated left three times is %llx\n",  
            val2, _rotl64( val2, 3 ) );  
    printf( "%llx rotated right four times is %llx\n",   
            val2, _rotr64( val2, 4 ) );  
#endif
}  
