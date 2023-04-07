/* 
 * File:   Data_API.h
 * Author: Administrator
 *
 * Created on 2015年1月20日, 下午 7:20
 */

#ifndef DATA_API_H
#define	DATA_API_H

#ifdef	__cplusplus
extern "C" {
#endif


unsigned char data16_strdec(unsigned int data,unsigned char *buf,unsigned char int_set,unsigned char max_value_set);
unsigned char data_strhex(unsigned long data,char *buf,unsigned char symbol);
long strdec_to_data(unsigned char *buf,unsigned char lenth);

unsigned int CRC_CREATE(unsigned char *data, unsigned char lenth);
unsigned char CRC_CHECK(unsigned char *data, unsigned char lenth ,unsigned int crc_data);
#ifdef	__cplusplus
}
#endif

#endif	/* DATA_API_H */

