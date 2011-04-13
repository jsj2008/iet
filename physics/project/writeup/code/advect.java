void advect(int n,
            int b,
            float[] d,
            float[] d0,
            float[] u,
            float[] v,
            float dt)
{
    int i, j, i0, j0, i1, j1;
    float x, y, s0, t0, s1, t1, dt0;

    dt0 = dt*n;
    for(i=1 ; i<=n ; i++)
    {
        for(j=1 ; j<=n ; j++)
        {
            x = i - dt0 * u[IX(i,j)];
            y = j - dt0 * v[IX(i,j)];

            if(x < 0.5f)
            {
                x = 0.5f;
            }
            if(x > (n+0.5f))
            {
                x = n + 0.5f;
            }
            i0 = (int)x;
            i1 = i0 + 1;

            if(y < 0.5f)
            {
                y = 0.5f;
            }
            if(y > (n+0.5f))
            {
                y = n + 0.5f;
            }
            j0 = (int)y;
            j1 = j0 + 1;

            s1 = x - i0;
            s0 = 1 - s1;

            t1 = y - j0;
            t0 = 1 - t1;

            d[IX(i,j)] = s0 * 
				(t0 * d0[IX(i0,j0)] + 
				 t1 * d0[IX(i0,j1)]) +
                s1 * (t0 * d0[IX(i1,j0)] 
						+ t1 * d0[IX(i1,j1)]);
        }
    }
    setBnd(n, b, d);
}

