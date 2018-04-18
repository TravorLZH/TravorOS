#ifndef	__RTC_H_
#define	__RTC_H_
struct tm {
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};
#ifdef	__cplusplus
extern	"C"{
#endif
/* Get time from CMOS */
extern void get_time(struct tm *time);
#ifdef	__cplusplus
}
#endif
#endif
