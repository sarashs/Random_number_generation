//This code is extracted from the TestU01 embedded code
//The algorithms goes as follows:
//x_n = x_(n-r) ^ x_(n-k)
//More information can be found on page 37 of the PDF


typedef struct {
	unsigned long Shift, Mask, mag01[2];
	double Norm;
} GFSR_param;

typedef struct {
	unsigned long *X;
	unsigned int r, s, K;
} GFSR_state;

static unsigned long GFSR_Bits(void *vpar, void *vsta)
{
	GFSR_param *param = vpar;
	GFSR_state *state = vsta;

	if (++state->s == state->K)
		state->s = 0;                     /* s = (s + 1) % K */
	if (++state->r == state->K)
		state->r = 0;                     /* r = (r + 1) % K */
	state->X[state->s] ^= state->X[state->r];
	return state->X[state->s] << param->Shift;
}