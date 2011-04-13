void addSource(int n, float[] x, float[] s, float dt)
{
    int i;
    int sz = (n+2)*(n+2);

    for(i=0;i<sz;i++)
    {
        x[i] += dt*s[i];
    }
}
