//This code is extracted from the TestU01 embedded code
//This is a cubic regression generator, in which 
//x_(n+1) = (ax^3+bx^2+cx+d) mod m
//The output is a double in the form of x_n/m
//More information can be found on the PDF on page 46


typedef struct {
	unsigned long m, a, b, c, d;
	double Norm;
} Cubic_param;

typedef struct {
	unsigned long X;
} Cubic_state;

static double Cubic_U01(void *vpar, void *vsta)
/*
 * Implementation used when all intermediary results hold in an int of 32
 * bits. This is the case when  m < 2^{16} since a, b, c, d are all < m.
 */
{
	Cubic_param *param = vpar;
	Cubic_state *state = vsta;

	state->X = (param->d + state->X * ((param->c + state->X * ((param->b +
		state->X * param->a) % param->m)) % param->m)) % param->m;
	return (state->X * param->Norm);
}
