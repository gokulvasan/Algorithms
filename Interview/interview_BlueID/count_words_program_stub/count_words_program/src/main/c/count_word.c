#include <stdio.h>
#include <stdlib.h>
#include <count_word.h>

/*
 * array that holds the stat of each letter
 */
static u32 lettr_cnt_arr[MAX_LETTER_CNT];
 
/*
 * array directly associates with
 * letter_type_t for easy calculation
 * of the letter index.
 */
static const u8 subtractor[] = {
		CAPITAL_LETTER_START,
		SMALL_LETTER_START,
};

/*
 * Converts from letter type (capital or small)
 * to corresponding index of the stat array.
 *
 * @L : Letter
 * @T : letter_type_t
 */
#define TYPE_TO_IDX(L, T) ((L) - (subtractor[T]))

/*
 * Converts from index of the stat array
 * to corresponding letter.
 *
 * @I : Index of the array
 * @T : letter_type_t
 */
#define IDX_TO_LETTER(I, T) ((I) + (subtractor[T]))

/* 
 * @fn test_range
 * @brief: inline function used for testing
 *	the given letter is within the range of
 *	alphabets.
 *
 * @param letter whose range needs to be tested
 * @return: type of the letter.
 *
 */
static inline u32 test_range(u8 letter)
{
	if((CAPITAL_LETTER_START <= letter) && 
		(CAPITAL_LETTER_END >= letter)) {
		return TYPE_CAPITAL;
	}
	else if((SMALL_LETTER_START <= letter) &&
	 	(SMALL_LETTER_END >= letter)) {
		return TYPE_SMALL;
	}
	return TYPE_INVALID;
}

/* 
 * @fn test_incr_arr
 * @brief: function that tests and increments 
 *	the corresponding array value if needed
 *
 * @param letter whose range needs to be tested
 * @return: none.
 *
 */
static void test_incr_arr(u8 letter)
{
	letter_type_t type = test_range(letter);
	
	if(TYPE_INVALID == type)
		return;
	
	lettr_cnt_arr[TYPE_TO_IDX(letter, type)]++;

	return;
}

/* 
 * @fn print_arr_cnt
 * @brief: function that prints the stat array in
 *	the format :
 *	letter	number	percent.
 *
 * @param total characters in all files
 *	used for percentage calculation
 * @return: none.
 */
static void print_arr_cnt(u32 total_cnt)
{
	u32 i = 0;

	printf("letter \t number \t percent\n");
	while(i < MAX_LETTER_CNT) {
		printf("%c/%c \t %d \t\t %d%%\n", 
			IDX_TO_LETTER(i, TYPE_CAPITAL),
			IDX_TO_LETTER(i, TYPE_SMALL),
			lettr_cnt_arr[i],
			LETTER_PER(lettr_cnt_arr[i], total_cnt));
		i++;
	}
	return;
}

/* 
 * @fn cnt_lttrs_per_file
 * @brief: traverses the given file and update stat array.
 * @param path of the file that needs to be traversed.
 * @return: total count of characters in the file.
 *
 * P.S. This assumes stdlib is available for file access
 *	If not, A wrapper needs to be designed that imitates
 *	fopen, fgetc.
 */
static u32 cnt_lttrs_per_file(u8 *file)
{
	FILE *fp;
   	u8 c;
   	u32 n = 0;
  
	fp = fopen(file,"r");
	if(NULL == fp) {
		perror("Error in opening file");
		return n;
	}
 
	do {
		c = fgetc(fp);
		if(feof(fp)) {
			break ;
		}
		test_incr_arr(c);
		n++;
	} while(1);

	fclose(fp);

	return n;
}

/* 
 * @fn main
 * @brief: entry function that iterates per file and displays.
 * @param argument count.
 * @param list of args
 * @return: 0 on success, -1 on failure.
 *
 * P.S. If this functionality needs to be made lib
 * 	Then main needs to be replaced by a non main
 *	function.
 */
u32 main(int argc, char *argv[])
{
	u32 i = 1;
	u32 total_cnt = 0;

	if(argc <= 1) {
		fprintf(stderr, "Error: No file input\n");
		exit(-1);
	}

	while(i < argc) {
		total_cnt += cnt_lttrs_per_file(argv[i]);	
		i++;
	}
	print_arr_cnt(total_cnt);

	return 0;
}

