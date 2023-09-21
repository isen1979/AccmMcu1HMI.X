//************************************************************************
// 16位元資料轉為10進制字串
// unsigned int data : 待轉換資料
// unsigned char *buf : 轉換後字串放置位址
// unsigned char int_set 有號數或無號數設定  // 0(無號數)    1(有號數)
// unsigned char max_value_set 最大有效位元選擇  8~16(0~7 皆默認為16bit)
// 回傳值 : 轉換後字串長度
//************************************************************************
unsigned char data16_strdec(unsigned int data,unsigned char *buf,unsigned char int_set,unsigned char max_value_set)  //4G  used 4000000000 10 bytes
{
    unsigned int data2=0,data_plus_max;
    unsigned char bufcnt=0;
    data2=data;
    if(int_set==1)
    {
        switch(max_value_set)
        {
            case 8:
                data_plus_max=0x007f;

            break;
            case 14:
                data_plus_max=0x1fff;
                if(data2>data_plus_max)
                {
                    data=~(data+0xc000-1);//~(data-1);
                    *buf++='-';
                }
            break;
            default://16
                data_plus_max=0x7fff;
                if(data2>data_plus_max)
                {
                    data=~(data-1);
                    *buf++='-';
                }
            break;   
        }
    }
    if(data>=10000 || bufcnt>0)  //10^9
    {
        *buf++=data/10000+0x30;
        data=data%10000;
        bufcnt++;
    }
    if(data>=1000 || bufcnt>0)//10^8
    {
        *buf++=data/1000+0x30;
        data=data%1000;
        bufcnt++;
    }
    if(data>=100 || bufcnt>0)//10^7
    {
        *buf++=data/100+0x30;
        data=data%100;
        bufcnt++;
    }
    if(data>=10 || bufcnt>0)//10^6
    {
        *buf++=data/10+0x30;
        data=data%10;
        bufcnt++;
    }
    if(data>=0 || bufcnt>0)//10^0
    {
        *buf++=data+0x30;
        bufcnt++;
    }
    if(data2>0x1fff)
       bufcnt++;
    return bufcnt;
}

long strdec_to_data(unsigned char *buf,unsigned char lenth)
{
    unsigned char cnt=0;
    long valus=0;
    for(cnt=1;cnt<lenth;cnt++)
    {
        valus*=10;
        valus+=*(buf+cnt)-0x30;
    }
    if(*buf==0)//+
    {
        return valus;
    }
    else       //-
    {
        return (0-valus);
    }
}

//************************************************************************
/* CRC_CREATE函數: 
 * 當數據被傳輸或存儲時，可以使用CRC_CREATE生成一個CRC值。
     輸入: 一個字節數組data和它的長度lenth。
     輸出: 該數組的CRC值。
   運作方式:
     初始化兩個變數reg_crc和temp。
     對於data中的每個字節，它都會進行XOR運算與temp，然後對結果進行8次位操作。
     這8次操作會檢查最低位，並根據它是1還是0來更新temp的值。
     最後，交換temp的高8位和低8位來得到最終的CRC值。
 */
//************************************************************************
unsigned int CRC_CREATE(unsigned char *data, unsigned char lenth)
{
	unsigned char j;
	unsigned int reg_crc = 0,temp = 0xFFFF;
	while(lenth--)
	{
		temp ^= *data++; //Isen：^= 是XOR賦值操作。
		for(j=0;j<8;j++)
		{
			if(temp & 0x01) /* LSB(b0)=1 */
				temp=(temp>>1) ^ 0xA001;
			else
				temp=temp >>1;
		}
	}
	reg_crc=((temp&0x00ff)<<8)|((temp&0xff00)>>8);
	return reg_crc;
}

//************************************************************************
/* CRC_CHECK函數: 
 * 當數據被傳輸或存儲時，可以使用CRC_CREATE生成一個CRC值。
     輸入: 一個字節數組data、長度lenth和一個CRC值crc_data。
     輸出: 如果計算出的CRC值與給定的crc_data匹配，則返回1，否則返回0。
  運作方式:
     使用CRC_CREATE函數計算data的CRC值。
     比較計算出的CRC值與給定的crc_data。
     如果它們匹配，返回1，否則返回0。
 */
//************************************************************************
unsigned char CRC_CHECK(unsigned char *data, unsigned char lenth ,unsigned int crc_data)
{
	unsigned int crc_check = 0;
	crc_check = CRC_CREATE(data,lenth);
	if(crc_check == crc_data)
		return 1; //crc check ok
	else
		return 0; //crc check fail
}

