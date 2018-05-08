#ifndef		__EWINV_DEFINE_
#define		__EWINV_DEFINE_

typedef union
{
	double	dword;			/* double word : 32bit */
	struct
	{
		int word0;		/* 하위 16비트(least siginificant word) */
		int word1;		/* 상위 16비트(most siginificant word) */
	} word;	
	struct
	{
		unsigned byte0	:8;	/* LSB */
		unsigned byte1	:8;
		unsigned byte2	:8;	/* sign + MSB */
		unsigned byte3	:8;	/* exponent */
	} byte;
} union32;

typedef struct {
	int Cmd;
	int Address;
	double Data;
} CMD_MSG;


#endif
