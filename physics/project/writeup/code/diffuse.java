void diffuse(int n, int b,  float[] x, 
		float[] x0, float diff, float dt)
{
    int i, j, k;
    float a = dt * diff*n*n;

	for(k=0 ; k<20; k++)
	{
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=n;j++)
			{
				x[IX(i,j)] = (x0[IX(i,j)] +
						a * (x[IX(i - 1, j)] + 
							x[IX(i + 1,j)] + 
							x[IX(i, j - 1)] + 
							x[IX(i,j + 1)])) 
					/ (1 + (4 * a));
			}
		}
		setBnd(n,b,x);
	}
}
