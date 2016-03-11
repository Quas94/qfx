/**
 * Entry point for the qfx trading application.
 *
 * Author: Michael
 */

#include <cstdio>
#include <cstdlib>

#include "ta_libc.h"

int main(int argc, char** argv) {
	printf("Starting...\n");

	double inputs[50];
	for (int i = 0; i < 50; i++) {
		inputs[i] = i;
	}

	int outStart;
	int outEnd;

	TA_RetCode code = TA_MA(0, 50, &inputs[0], TA_INTEGER_DEFAULT, TA_MAType_SMA, &outStart, &outEnd, &inputs[0]);

	printf("outStart = %d, outEnd = %d\n", outStart, outEnd);

	for (int i = 0; i < 50; i++) {
		if (i > 0) {
			printf(" ");
		}
		printf("%lf", inputs[i]);
		if (i < 49) {
			printf(",");
		}
	}

	return EXIT_SUCCESS;
}
