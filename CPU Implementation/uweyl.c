//This code is extracted from the TestU01 embedded code
//The algorithms goes as follows:
//x_n = n*Alpha (mod 1)
//This generator takes advantage of irregular floating point numbers 
//I believe that this specific algorithm can compliment other 
//Types of RNGs by applying this onto another.
//A very interesting generator!
//More information can be found on page 74 of the PDF

typedef struct {
	unsigned long n;
} Weyl_state;

typedef struct {
	double Alpha;
} Weyl_param;

static double Weyl_U01(void *vpar, void *vsta)
{
	Weyl_param *param = vpar;
	Weyl_state *state = vsta;
	double X;

	state->n++;
	X = state->n * param->Alpha;
	return (X - (long)X);
}