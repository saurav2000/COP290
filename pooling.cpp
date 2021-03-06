#include "defs.h"
#include "library.h"

void maxPool(vector<vf> &v, vector<vf>& m_pool)
{
    int n=v.size();
    int i,j,k;

    if(n&1)
    {
        vf v1;
        v1.pb(0);
        for(i=0;i<n;i++)
        {
            v[i].pb(0);
            v1.pb(0);
        }
        v.pb(v1);
        n++;
    }
	
    for(i=0;i<n;i+=2)
    {
        vf temp;
        for(j=0;j<n;j+=2)
        {
            float maxi=0;
            maxi=max(v[i][j],max(v[i][j+1],max(v[i+1][j],v[i+1][j+1])));
            temp.pb(maxi);
        }
        m_pool.pb(temp);
    }
}

void averagePool(vector<vf> &v, vector<vf>& av_pool)
{
    int n=v.size();
    int i,j,k;
    
    
    for(i=0;i<n;i+=2)
    {
        vf temp;
        for(j=0;j<n;j+=2)
        {
            float ans=0;
            if(i==n-1 && j==n-1)
                ans=v[i][j];
            else if(i==n-1)
                ans=(v[i][j]+v[i][j+1])/2;
            else if(j==n-1)
                ans=(v[i][j]+v[i+1][j])/2;
            else
                ans=(v[i][j]+v[i][j+1]+v[i+1][j]+v[i+1][j+1])/4;
            temp.pb(ans);
        }
        av_pool.pb(temp);
    }
        
}
