#include "utils.h"

// convert host byte order to network byte order (16 bit)
// Low byte masked, shifted to high position: (port & 0xFF) << 8
//     High byte extracted, shifted right, masked: (port >> 8) & 0xFF  
//     OR combines swapped bytes
int16 htons(int16 port) {
    return  ((port & 0xFF) << 8) | ((port >> 8) & 0xFF);
}


//convert host byte order to network byte order (32 bit)
int32 htonl(int32 addr) {
    return ((addr & 0xFF000000) >> 24) | //byte = highest byte (bits 31-24, masked by 0xFF000000)
           
           ((addr & 0x00FF0000) >> 8)  |//byte = next byte (bits 23-16, masked by 0x00FF0000)
           
           ((addr & 0x0000FF00) << 8)  |//byte = middle byte (bits 15-8, masked by 0x0000FF00)
           
           ((addr & 0x000000FF) << 24); //byte = lowest byte (bits 7-0, masked by 0x000000FF)
    }


//convert "192.168.1.1" to 32-bit number by manually parsing 
//a dotted IP string into a 32-bit host-order integer, 
//then converts it to network order via htonl

// Builds host-order first (little-endian on x86), 
// then htonl swaps to network big-endian. 
int32 inet_addr(const char *ip) {
    int32 result = 0;
    int32 octet = 0;
    int shift = 24;

    while(*ip){
        if(*ip >= '0' && *ip <= '9') {

//           BUILD DECIMAL
//          "string to integer" algorithm
//              - Multiply previous result by 10 (shift digits left)
//              - Add new digit
//              - *ip - '0' converts ASCII character to numeric value
            octet = octet * 10 + (*ip - '0'); 
        
        } else if(*ip == '.'){

             //`<< shift` positions each octet in correct byte position
            // `|=` (OR-equals) combines them without overwriting previous bytes
            // Result: 4 separate numbers packed into 1 integer

            result |= (octet << shift); //Octet → position (24→16→8→0)
            shift -= 8;
            octet = 0; 
        }
        ip++;
    }
    result |= octet;//last octet

    return htonl(result); /*reverses the 4 bytes so that when stored in little-endian memory, 
                            they'll be transmitted on the network in big-endian order 
                            (most significant byte first), which is the Internet standard.*/
}

//string length
int my_strlen(const char *str) {
    int len = 0;
    while(str[len] != '\0') len++;
    return len;
}

//string copy
void my_strcopy(char *dest, const char *src){
    while(*src){
        *dest++ = *src++;
    }
    *dest = '\0';
}

//string compare
int my_strcmp(const char *s1, const char *s2) {
    while(*s1 && (*s1 == *s2)){ // Keep going while chars match AND not end-of-string
                                //i.e Advance while equal AND not null
        
        //move to next chars
        s1++;
        s2++;
    }
    
     // s1>s2:+, s1<s2:-, equal:0
    return *(unsigned char *)s1 -*(unsigned char *)s2;
}

void my_sprintf_simple(char *buffer, const char *format, ...) {
    //this is a placeholder
}