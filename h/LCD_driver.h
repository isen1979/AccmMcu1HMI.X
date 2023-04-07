/* 
 * File:   LCD_driver.h
 * Author: User
 *
 * Created on 2014年8月6日, 上午 9:34
 */

#ifndef LCD_DRIVER_H
#define	LCD_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif

    
#define LDC_BUSY    1//(UART)
#define LDC_UNBUSY  0//(UART)
#define LDC_STATUS_PIN _RA10   //shutdown pin
#define LDC_RST_PIN    _RA9   //reset pin
#define LCD_PACKET_BUFFER_MAX  20

//COMMAND
#define READRTCTIME 0x10
#define READEEPROM 0x1A
#define WRITEEEPROM 0x1B
    
#define SET_FONT 0x33
    
#define PASTE_PICTURT 0x70
#define PASTE_ICON 0x72
#define ICON_ITEM_MOVE 0xA1
#define ICON_ITEM_ICON 0xA2
    
#define READ_LCD_EEPROM         0x1A
#define READ_LCD_STARTUP        0XE0
#define LCD_RESPONSE_BUTTON         0XE1
#define TOUCH_LCD 0xE2
#define RUN_MACRO 0xFA
    

//PARAMETER
#define TOUCH_PRESS    1 
#define TOUCH_RELEASE  0
    
//Buffer Size
#define PICTURE_NUM 61//50+11

    
    
typedef struct __REALTIME
{
    unsigned char Year;
    unsigned char Month;
    unsigned char Day;
    unsigned char Hour;
    unsigned char Min;
    unsigned char Sec;
    unsigned char WeekDay;
    
} _REALTIME;
    

//extern unsigned char packet_buf[LCD_PACKET_BUFFER_MAX];
extern unsigned char lcd_startup_flag;

//************************************************************************
//void INIT_TOUCH_LCD(void);
//Initial LCD & Controller 115200 8bits data ,1 start bit ,1 end bit
//115200,N,8,1
//************************************************************************
void INIT_TOUCH_LCD(void);
void ParsingLCD_RX(void);


/*
 * Enable to Show the Information of the LCD
 * The information includes RAM size, Flash size, and version or more.
 */
void ShowLCDInformation(void);
/*
Disable to Show the Information of the LCD
 */
void CloseLCDInformation(void);


/*
 * User can use the function to show the debug message when you are coding your code.
 */
void PrintDebugMessage(unsigned char row, unsigned char col, unsigned char *str, unsigned char length);

void Set_LCD_Page(unsigned char page);


/*
 * Fucntions for the RTC Timer
 */
void Read_RTC_DateTime(void);
//year, month, day, hour, min, and sec are the formation of BCD.
void Set_RTC_DateTime(unsigned char year, unsigned char month, unsigned char day, unsigned char hour, unsigned char min, unsigned char sec);

void READ_EEPROM(unsigned char *buf, unsigned int start, unsigned char size);

void WRITE_EEPROM(unsigned char *buf, unsigned int start, unsigned char size);




/*
 * Buzzer Setting, Resolution : 10msec
 */
void Buzzer(unsigned char Ten_msec);

/*
 * Set the brightness of the backlight. Range from 0 to 32.
 */
void ON_OFF_LCD_BACKLIGHT(unsigned char flag);
void SET_LCD_BACKLIGHT(unsigned char level);


/*
 * 
 */
void ScreenFreeze(unsigned char FreezeTime);
void ScreenSynchronize(void);


/*
 * 
 */
void OnOffTouch(unsigned char status);

/*
 * Functions for the TEXT mode
 */
void Set_BackGround_Color(unsigned int color, unsigned char transparent);
void Set_ForGround_Color(unsigned int color, unsigned char transparent);
void FontSize(unsigned char size, unsigned char distX, unsigned char distY);
void SetFont(unsigned char font);
void PutString(unsigned int x, unsigned int y, unsigned char *str, unsigned char length);//length : string length

void Pen1Setting(unsigned int color, unsigned char transparent, unsigned char size);
void Pen2Setting(unsigned int color, unsigned char transparent, unsigned char size);
void Pen1DrawSingleRectangle(unsigned int Xstart, unsigned int Ystart, unsigned int Xend, unsigned int Yend, unsigned mode);

void FillBackGroundWithPen1(void);
void ReginalErase(unsigned int Xstart, unsigned int Ystart, unsigned int Xend, unsigned Yend);
void SingleReginalMove(unsigned int x, unsigned int y, unsigned int wide, unsigned height, unsigned char mode, unsigned char distance);



void ShowLayer1_SeriesPicture(unsigned int x, unsigned int y, unsigned char *picture, unsigned int picturesId, unsigned char num);
void Show_Layer1_ICON(unsigned int x, unsigned int y, unsigned int ICON_Id);


void WriteDataToRAM(unsigned long addr, unsigned char size, unsigned char *data);
void RUN_LCD_CMD_IN_RAM(unsigned long addr, unsigned char cmd_num);

void ShowCursor(unsigned int x, unsigned int y, unsigned char width, unsigned char height);
void Show_Movie_By_Order(unsigned int movie_x, unsigned int movie_y, unsigned char mode,  unsigned char time, unsigned char user_group, unsigned int photo_group, unsigned char qty, unsigned char start);
void Show_Movie_Any_Order(unsigned int movie_x, unsigned int movie_y, unsigned char mode,  unsigned char time, unsigned char user_group, unsigned int photo_group, unsigned char qty, unsigned char *movie);
void Show_Layer2_ICON(unsigned int x, unsigned int y, unsigned char user_group, unsigned int ICON_Id);
    

void EnableMacro(unsigned char user_group, unsigned int MACRO_Id, unsigned char Repeat);
void DisableMACRO(unsigned char user_group);

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_DRIVER_H */




