#ifndef __COUNT_WORD_H
#define __COUNT_WORD_H

/*
 * An approach to make the code generic
 * In some compilers length of the data
 * type differs, In such cases this should
 * be configured.
 *
 * Ex: int data type in Windows-xp 2bytes
 *			Linux 	   4bytes.
 */
typedef unsigned char		u8;
typedef unsigned short		u16;
typedef unsigned int		u32;
typedef unsigned long long	u64;
typedef signed char		s8;
typedef short			s16;
typedef int			s32;
typedef long long		s64;

/*
 * maximum letter count per type.
 */
#define MAX_LETTER_CNT 26

/*
 * range checker, used for testing
 * the given letter falls within range.
 */
#define SMALL_LETTER_START 'a'
#define SMALL_LETTER_END 'z'
#define CAPITAL_LETTER_START 'A'
#define CAPITAL_LETTER_END 'Z'

/*
 * @enum letter_type_t
 *
 * Enum used for identifying the type
 * of letter, easing the stat array
 * index calculation. 
 */
typedef enum {
	TYPE_CAPITAL = 0, /* Capital letter */
	TYPE_SMALL,	  /* Small letter*/
	TYPE_INVALID	  /* Invlaid or not of our interest*/
} letter_type_t;

/*
 * Percentage calculator.
 *
 * @L : specific letter count (Numerator)
 * @C : Total letters count (Denominator)
 */
#define LETTER_PER(L, C) (((L) * 100)/(C))

#endif
