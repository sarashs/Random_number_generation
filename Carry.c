//This code is extracted from the TestU01 embedded code
//The algorithms goes as follows:
//x_n = (x_(n-r) + x_(n-s) + c_(n-1)) mod m in which 
//c_n = (x_(n-r) + x_(n-s) + c_(n-1)) div m in which 
//The output is x_n/m
//More information can be found on page 31 of the PDF


/*=============================== Types =================================*/

typedef struct {
	unsigned long M;                /* Modulus */
	double Norm;                    /* 1 / M */                 /* = TRUE if r >= s, FALSE if r < s */
	int skip;                       /* For luxury: skip = Lux - S numbers */
} AWC_param;

typedef struct {
	unsigned long *X;               /* State */
	unsigned int C;                 /* Carry */
	unsigned int R, S;              /* Lags */
	unsigned int n;                 /* how many since last skip */
	unsigned int Order;             /* Order */
} AWC_state;

static double AWC_U01(void *vpar, void *vsta)
{
	AWC_param *param = vpar;
	AWC_state *state = vsta;

	unsigned long x, temp;

	x = state->X[state->R] + state->C;
	temp = param->M - state->X[state->S];
	if (x < temp) {
		x += state->X[state->S];
		state->C = 0;
	}
	else {
		x -= temp;
		state->C = 1;
	}
	state->X[state->R] = x;
	state->R = (state->R + 1) % state->Order;
	state->S = (state->S + 1) % state->Order;
	return (x * param->Norm);
}