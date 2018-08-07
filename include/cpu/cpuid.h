#ifndef	__CPUID_H_
#define	__CPUID_H_
#ifdef	__cplusplus
extern	"C"{
#endif
enum cpuid_requests {
	CPUID_VENDORSTRING,
	CPUID_FEATURES,
	CPUID_TLB,

	CPUID_INTELEXTENDED=0x80000000,
	CPUID_INTELFEATURES,
	CPUID_INTELBRANDSTRING,
	CPUID_INTELBRANDSTRINGMORE,
	CPUID_INTELBRANDSTRINGEND
};

/* Single request to CPUID */
static inline void cpuid(int code,size_t *a,size_t *d)
{
	asm volatile("cpuid":"=a"(*a),"=d"(*d):"a"(code):"ecx","ebx");
}
/* Issue a complete request, storing general registers output as a string */
static inline int cpuid_string(int code,size_t where[4])
{
	int ret;
	asm volatile("cpuid":"=a"(where[0]),"=b"(where[1]),"=c"(where[2]),"=d"(where[3]):"a"(code));
	return ret;
}
#ifdef	__cplusplus
}
#endif
#endif
