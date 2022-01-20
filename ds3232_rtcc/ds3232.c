
#include <xc.h>
#include "i2c.h"


//
void rtcc_write(unsigned char slave_addr,unsigned char word_adrr, unsigned char data);
unsigned char rtcc_read(unsigned addr);

//
void set_time(int seconds, int minutes, int hours);
void set_alarm1_time(int seconds, int minutes, int hours);
int get_seconds(unsigned char , unsigned char);
int get_minutes(unsigned char, unsigned char);
int get_hours(unsigned char, unsigned char);
void rtcc_config();

void main(void)
{
    
    
    
    return;
}

void rtcc_write(unsigned char slave_addr,unsigned char word_addr, unsigned char data)
{
    i2c_start();
    
    i2c_write(slave_addr);
    i2c_wait();
    //confirm if slave ack or nack
    if(ACKSTAT) return -1; //if slave does not acknowledge terminate
    
    i2c_write(word_addr); //send data
    i2c_wait();
    
    if(ACKSTAT) return -1;
    
    i2c_write(data);
    
    if(ACKSTAT) return -1;
    
    i2c_stop();
    
}

unsigned char rtcc_read(unsigned slave_addr, unsigned word_addr)
{
    unsigned char data;
    i2c_start();
    
    i2c_write(slave_addr|0x00); //slave addr+W
    i2c_wait();
    if(ACKSTAT) return -1;
       
    i2c_write(word_addr);
    i2c_wait();
    if(ACKSTAT) return -1;
    
    i2c_repeated_start();
    
    i2c_write(slave_addr|0x00); //slave addr+R
    i2c_wait();
    if(ACKSTAT) return -1;
    
    data = i2c_read();
    i2c_nack(); //nack to terminate
    
}

void rtcc_config()
{
   ///////////////////////////////
    //  Control registers(0x0E)
    //  
    //
    //
    //
    ////////////////////////////
    
    rtcc_write(0xD0, 0x0E, 0x1F);
    
    ///////////////////////////
    //  Control and Status Reg
    //  
    //
    //////////////////////////
    rtcc_write(0xD0, 0xF, 0x00);
    
}

void set_time(int seconds, int minutes, int hours)
{
    
    rtcc_write(0xD0, 0x00, int_to_bcd(seconds));
    
    rtcc_write(0xD0, 0x01, int_to_bcd(minutes));
    
    rtcc_write(0xD0, 0x02, int_to_bcd(hours)); //12hour mode bit<6> = HIGH; 24 hour bit<6> = LOW
    
}

void set_alarm1_time(int minutes, int hours)
{
    //rtcc_write(0xD0, 0x07, int_to_bcd(seconds));
    
    rtcc_write(0xD0, 0x08, int_to_bcd(minutes));
    
    rtcc_write(0xD0, 0x09, int_to_bcd(hours)); //12hour mode bit<6> = HIGH; 24 hour bit<6> = LOW
}



void set_alarm2_time(int minutes, int hours)
{
    //rtcc_write(0xD0, 0x07, int_to_bcd(seconds));
    
    rtcc_write(0xD0, 0x0B, int_to_bcd(minutes));
    
    rtcc_write(0xD0, 0x0C, int_to_bcd(hours)); //12hour mode bit<6> = HIGH; 24 hour bit<6> = LOW
}



int get_seconds(unsigned char slave_addr, unsigned char word_addr)
{
    int seconds = bcd_to_int(rtcc_read(slave_addr, word_addr));
    
    return seconds;
}

int get_minute(unsigned char addr, unsigned char word_addr)
{
    int minute = bcd_to_int(r)
}
unsigned char int_to_bcd(int int_val)
{
    return((int_val/10)<<4 |int_val%10);
}

int bcd_to_int(unsigned char bcd_val)
{
    return(((bcd_val&0xF0)>>4)*10 + bcd_val&0x0F);
}


