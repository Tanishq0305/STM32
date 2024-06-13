/*
For SPI1 pins are:
PA4 -> SS (Select Line – General Output)
PA5 -> SCLK (CLK – Alternate Output)
PA6 -> MISO (Alternate Input)
PA7 -> MOIS (Alternate Output)
SPI1 is bit 12th bit in APB1
For SPI2 pins are:
PB12 -> SS
PB13 -> SCLK
PB14 -> MISO
PB15 -> MOSI
SPI4 is bit 14 in APB2.
*/

void spi_init(unsigned short spi);
void spi_Tx(unsigned short spi, char tx_char);
void spi_msg(unsigned short spi, char str[]);