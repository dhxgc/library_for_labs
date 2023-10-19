// LCD
#ifndef _lcd_H_
#define _lcd_H_
#define I2C_ADDR 0x3f
#define LCD_CHR 1
#define LCD_CMD 0
#define LINE1 0x80
#define LINE2 0xC0
#define LCD_BACKLIGHT 0x08
#define ENABLE 0b0000100

int fd = wiringPiI2CSetup(I2C_ADDR);
void lcd_toggle_enable(int bits) {
		delayMicroseconds(500);
		wiringPiI2CReadReg8(fd, (bits | ENABLE));
		delayMicroseconds(500);
		wiringPiI2CReadReg8(fd, (bits & ~ENABLE));
		delayMicroseconds(500);
}

void lcd_byte(int bits, int mode) {
		int bits_high, bits_low;
		bits_high = mode | (bits & 0xF0) | LCD_BACKLIGHT;
		bits_low = mode | ((bits << 4) & 0xF0) | LCD_BACKLIGHT;
		wiringPiI2CReadReg8(fd, bits_high);
		lcd_toggle_enable(bits_high);
		wiringPiI2CReadReg8(fd, bits_low);
		lcd_toggle_enable(bits_low);
}

void CtrLcd(void){
		lcd_byte(0x01, LCD_CMD);
		lcd_byte(0x02, LCD_CMD);
}

void lcdLoc(int line) {
		lcd_byte(line, LCD_CMD);
}

void typeLn(const char *s) {
		while(*s) lcd_byte(*(s++), LCD_CHR);
}

void typeInt(int i) {
		char array[20];
		sprintf(array, "%d", i);
		typeLn(array);
}

void typeFloat(float i) {
	char array[20];
	sprintf(array, "%f", i);
	//printf("TESTS ARRAY:  %s", array);
	typeLn(array);
}

void init_lcd(void){
		lcd_byte(0x33, LCD_CMD);
		lcd_byte(0x32, LCD_CMD);
		lcd_byte(0x06, LCD_CMD);
		lcd_byte(0x0C, LCD_CMD);
		lcd_byte(0x28, LCD_CMD);
		lcd_byte(0x01, LCD_CMD);
		delayMicroseconds(500);
}

#endif