
void i2c_init();
void i2c_start();
void i2c_stop();
void i2c_wait();
void i2c_write();
void i2c_read();
void i2c_ack();
void i2c_nack();
void i2c_repeated_start();

void i2c_init()
{
    
    
    //////////////
    // Fosc = 8MHz
    //
    //////////////
    SSPADD = 0x28; //set baud rate to 100khZ
    
    SSPEN = 1; //SSP enabled
    
    //SSPM = 8; 
    SSPM3 = 1;
    SSPM2 = 0;
    SSPM1 = 0;
    SSPM0 = 0;
    
    
    ////////////Pin Configurations///////////
    //SDA = 
    //SCL = OUTPUT
    ////////////////////////////////////////
    
    TRISCbits.TRISC3 = 1; // SCL
    TRISCbits.TRISC4 = 1; // SDA
    
    
    /////////Interrupt Settings //////////////////
    //
    //
    //
    /////////////////////////////////////////////
    GIE = 1; //enable global interrupt or  //asm("ie");
    PEIE = 1; //enable peripheral interrupt
    SSPIF = 0; //clear SSPIF
    SSPIE = 1; // enable SSP interrupt
   
    
}


void i2c_wait()
{
    while(SSPIF);
    SSPIF = 0;
}


void start()
{
    i2c_wait();
    SEN = 1; //start enable
}

void stop()
{
    i2c_wait();
    PEN = 1; //stop enabled
}

void ack()
{
    i2c_wait();
    ACKEN = 1; //enable ack or nack
    ACKDT = 0; //ACK enable
}

void nack()
{
    i2c_wait();
    ACKEN = 1;
    ACKDT = 1;
}

void i2c_write(unsigned char data)
{
    i2c_wait();
    SSPBUF = data;
}

unsigned char i2c_read()
{
    i2c_wait();
    return SSPBUF;
}

void i2c_repeated_start()
{
    i2c_wait();
    RCEN = 1;//repeated start enabled
}
