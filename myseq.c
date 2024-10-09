#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum {
	MaxArgsNumber = 3,
};

int
flagW(char *argv)
{
	return strcmp(argv, "-w") == 0;
}

int
isHex(char *argv)
{
	return argv[1] == 'x' || argv[1] == 'X';
}

int
getBase(char *argv)
{
	if (isHex(argv)) {
		return 16;
	}

	return 10;
}

int
endptrIsNotZero(char *endptr)
{
	return *endptr != '\0';
}

void
convertToLong(long *number, char *argv, int *fail)
{
	char *endptr;
	int base;

	base = getBase(argv);
	*number = strtol(argv, &endptr, base);

	if (endptrIsNotZero(endptr)) {
		*fail = -1;
	}
}

void
parseArguments(int argc, char **argv, long *first, long *increment, long *last,
	       int *fail)
{

	switch (argc) {
	case 1:
		convertToLong(last, argv[0], fail);
		break;
	case 2:
		convertToLong(first, argv[0], fail);
		convertToLong(last, argv[1], fail);
		break;
	case 3:
		convertToLong(first, argv[0], fail);
		convertToLong(increment, argv[1], fail);
		convertToLong(last, argv[2], fail);
		break;

	default:
		break;
	}

}

int
existsWidth(int width)
{
	return width;
}

int
lastIsNegative(long last)
{
	return last < 0;
}

int
lastIsNotZero(long last)
{
	return last != 0;
}

void
calculateWidth(long last, int *width)
{
	int count = 0;

	if (lastIsNegative(last)) {
		count++;
		last = -last;
	}
	while (lastIsNotZero(last)) {
		last /= 10;
		count++;
	}
	*width = count;
}

int
positiveIncrement(long increment)
{
	return increment > 0;

}

void
printNumber(long number, int width)
{
	if (existsWidth(width)) {
		printf("%0*ld\n", width, number);
	} else {
		printf("%ld\n", number);
	}
}

void
myseq(long first, long increment, long last, int width)
{
	long i;

	if (positiveIncrement(increment)) {
		for (i = first; i <= last; i += increment) {
			printNumber(i, width);
		}
	} else {
		for (i = first; i >= last; i += increment) {
			printNumber(i, width);
		}
	}
}

int
main(int argc, char **argv)
{
	long last = 1;
	long first = 1;
	long increment = 1;
	int fail = 0;
	int width = 0;

	argc--;
	argv++;

	if (argc < 1) {
		fprintf(stderr, "myseq: missing operand\n");
		exit(EXIT_FAILURE);
	}

	if (flagW(argv[0])) {
		width = 1;
		argc--;
		argv++;

		if (argc < 1) {
			fprintf(stderr, "myseq: missing operand\n");
			exit(EXIT_FAILURE);
		}

	}

	if (argc > MaxArgsNumber) {
		fprintf(stderr, "myseq: extra operand %s\n",
			argv[MaxArgsNumber]);
		exit(EXIT_FAILURE);
	}

	parseArguments(argc, argv, &first, &increment, &last, &fail);

	if (fail == -1) {
		fprintf(stderr, "myseq: invalid floating point argument\n");
		exit(EXIT_FAILURE);
	}

	if (increment == 0) {
		fprintf(stderr, "myseq: invalid Zero increment value: «0»\n");
		exit(EXIT_FAILURE);
	}

	if (existsWidth(width)) {
		calculateWidth(last, &width);
	}

	myseq(first, increment, last, width);

	exit(EXIT_SUCCESS);
}
