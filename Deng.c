//This code is extracted from the TestU01 embedded code
//This code is for one of the generator created by Lih-Yuan Deng.
//Algorithm: x_(n) = b(x_(n-1+)x_(n-k)) mod m
//The function returns a double, the value of x_n/m
//More information can be found on page 73 of the PDF

#define MASK1 127


typedef struct {
	double b, m;
} DX02_param;

typedef struct {
	double *X;
	unsigned int s, K;
} DX02_state;

static double DX02a_U01(void *vpar, void *vsta)
{
	/* Generate 3 numbers; discard the next 100 numbers; and so on ... */
	DX02_state *state = vsta;
	DX02_param *param = vpar;
	double Z;
	int i;
	static int co = 2;
	++state->s;

	if (co % 3 == 0) {
		for (i = 0; i < 100; i++) {
			state->X[state->s & MASK1] = num_MultModD(param->b,
				state->X[(state->s - 1) & MASK1] + state->X[(state->s - state->K) &
				MASK1], 0.0, param->m);
			++state->s;
		}
		co = 0;
	}
	co++;
	Z = state->X[state->s & MASK1] = num_MultModD(param->b,
		state->X[(state->s - 1) & MASK1] + state->X[(state->s - state->K) &
		MASK1], 0.0, param->m);
	return  Z / param->m;
