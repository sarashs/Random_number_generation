//This code is extracted from the TestU01 embedded code
//The algorithms goes as follows and is super similar to ugfsr:
//x_n = x_(n-r1) ^ x_(n-r2) ^ x_(n-r3) ^ x_(n-k)
//More information can be found on page 38 of the PDF

typedef struct {
	unsigned long Shift;
} GFSR5_param;

typedef struct {
	unsigned long *X;
	unsigned int r1, r2, r3, s, K;
} GFSR5_state;

static unsigned long GFSR5_Bits(void *vpar, void *vsta)
{
	GFSR5_param *param = vpar;
	GFSR5_state *state = vsta;

	if (++state->s == state->K)
		state->s = 0;
	if (++state->r1 == state->K)
		state->r1 = 0;
	if (++state->r2 == state->K)
		state->r2 = 0;
	if (++state->r3 == state->K)
		state->r3 = 0;
	state->X[state->s] ^= state->X[state->r1] ^ state->X[state->r2] ^
		state->X[state->r3];
	return state->X[state->s] << param->Shift;
}