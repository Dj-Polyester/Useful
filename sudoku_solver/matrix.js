class Matrix
{
    constructor(m,n)
    {
        this = [];
        for(var i=0; i<m; i++) 
        {
            this[i] = new Array(n);
        }
    }

    element(i,j)
    {
        return this[i][j];
    }
}