#include <kernel/cmos.h>
#include <drivers/rtc.h>

#define	BCD_TO_BIN(val)	((val)=((val)&15) + ((val)>>4)*10)

void get_time(struct tm *time)
{
	do{
		time->tm_sec=CMOS_READ(0);
		time->tm_min=CMOS_READ(2);
		time->tm_hour=CMOS_READ(4);
		time->tm_mday=CMOS_READ(7);
		time->tm_mon=CMOS_READ(8);
		time->tm_year=CMOS_READ(9);
	}while(time->tm_sec!=CMOS_READ(0));
	BCD_TO_BIN(time->tm_sec);
	BCD_TO_BIN(time->tm_min);
	BCD_TO_BIN(time->tm_hour);
	BCD_TO_BIN(time->tm_mday);
	BCD_TO_BIN(time->tm_mon);
	BCD_TO_BIN(time->tm_year);
}
