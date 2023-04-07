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
// CRC check
//

//************************************************************************
unsigned int CRC_CREATE(unsigned char *data, unsigned char lenth)
{
	unsigned char j;
	unsigned int reg_crc=0,temp=0xFFFF;
	while(lenth--)
	{
		temp ^= *data++;
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

unsigned char CRC_CHECK(unsigned char *data, unsigned char lenth ,unsigned int crc_data)
{
	unsigned int crc_check=0;
	crc_check=CRC_CREATE(data,lenth);
	if(crc_check==crc_data)
		return 1; //crc check ok
	else
		return 0; //crc check fail
}

