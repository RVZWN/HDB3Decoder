#include <iostream>
#include <cmath>
#include <time.h>
//time.h is only used for compilation info purposes...

using namespace std;

int main()
{
    int start = clock(); //clock used for compilation info [You don't actually need this]
    int v[64], n, i, k;
    int level=0; //voltage level (-V,0,+V)
    bool hdberr=0; //34404 defines error bits which are interpreted as zeros, but SHOULD not be in a HDB3 code stream!!
    cout<<"Code length (!must be >4!) : ";
    cin>>n;
    while(n<5)
    {
      cout<<"The value must be greater than *4* ! Please retry!!\n";
      cin>>n;
    }
    cout<<"Type HDB-3 code : ";
    
    
    for(i=0; i<n; i++)
    {
        cin>>v[i];
        if(v[i]>=-1 && v[i]<2)
        {
            if(i>=3 && v[i-3]==v[i-2] && v[i-2]==v[i-1] && v[i-1]==v[i] && v[i]==0)
                {
                    v[i-3]=34404; v[i-2]=34404; v[i-1]=34404; v[i]=34404; hdberr=1;
                cout<<"!HDB-3 ERROR! HDB-3 found errors in the code (a 4 consecutive 0 sequence)\n\n";
                }
        }
        
        else
        {
          
          cout<<"!ERROR! Incorrect HDB-3 code! (-1, 0, +1)\n";
          return 0;
        }
    }
    
    //0 -1 0 0 0 -1 0 +1 −1 +1 0 0 +1 −1 +1 −1 0 0 −1 0 0 0 +1 0
    for(i=0; i<n; i++)
    {
        if(v[i]!=0)
        {
            if(v[i]==-1) 
            {
                if(level==-1) 
                {
                    //following condition to pass the even and odds exceptions at -V level
                    if(v[i-1]==0 && v[i-1]==v[i-2] && v[i-3]==1)
                    {
                        v[i]=0; v[i-3]=0; level=-1;
                    }
                    
                    else if(v[i-1]==0 && v[i-1]==v[i-2] && v[i-2]==v[i-3])
                    {
                        v[i]=0; level=-1;
                    }
                    
                    else
                    {
                        cout<<"!ERROR! Decoder encountered an error for -V (voltage levels should alternate)\n";
                        cout<<"At positon : "<<i+1;
                        return 0;
                    }
                }
                else {v[i]=1; level=-1;}
            }
            
            else if(v[i]==1) 
            {
                if(level==1)
                {
                    //following condition to pass the even and odds exceptions at +V level
                    if(v[i-1]==0 && v[i-1]==v[i-2] && v[i-3]==1)
                    {
                        v[i]=0; v[i-3]=0; level=1;
                    }
                    
                    else if(v[i-1]==0 && v[i-1]==v[i-2] && v[i-2]==v[i-3])
                    {
                        v[i]=0; level=1;
                    }
                    
                    else
                    {
                        cout<<"!ERROR! Decoder encountered an error for +Vasd (voltage levels should alternate)\n";
                        cout<<"At positon : "<<i+1;
                        return 0;
                    }
                }
                else level=1;
            }
        }
    }
    
    cout<<"\n\nDecoded HDB-3 code :\n";
    for(i=0; i<n; i++)
    {
      cout<<v[i]<<" ";
    }
    if(hdberr)
        cout<<endl<<"34404 - represents the error bits";
    
    //used those clocks just for testing {optimization purposes}
    int end = clock();
    cout<<"\n\nCompiled in : "<<(float(end-start)/CLOCKS_PER_SEC)*1000<<" ms";
  return 0;
}
