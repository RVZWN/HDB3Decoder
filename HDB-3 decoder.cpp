#include <iostream>

using namespace std;

int main ()
{
    int v[32], n, i, k;
    int min=0, max=0; //counters for +1 & -1 voltage levels
    int kmin=0, kmax=0; //bits for voltage level
    int hdberr=0; //34404 info display
    cout<<"Code length (!must be >4!) : ";
    cin>>n;
    while(n<5)
    {
      cout<<"The value must be greater than *4* ! Please retry!!"<<endl;
      cin>>n;
    }
	cout<<"Type HDB-3 code : ";
    
    for(i=0; i<n; i++){
        cin>>v[i];
        if(v[i]>=-1 && v[i]<2){
            
            if(i>=3 && v[i-3]==v[i-2] && v[i-2]==v[i-1] && v[i-1]==v[i] && v[i]==0)
                {
                    v[i-3]=34404; v[i-2]=34404; v[i-1]=34404; v[i]=34404; hdberr=1;
                cout<<"!HDB-3 ERROR! HDB-3 found errors in the code (a 4 consecutive 0 sequence)"<<endl<<endl;
                }
        }
        
        else{
          
          cout<<"!ERROR! Incorrect HDB-3 code! (-1, 0, +1)";
          return 0;
        }
	}
	
	for(i=0; i<n; i++){
	    
	    if(v[i]==-1) {
            if(kmin==1) {
                if((max+min+1)%2==0){
                    //following condition to pass the even exception at -V level
                    if(v[i]==-1 && v[i-1]==0 && v[i-1]==v[i-2] && v[i-3]==-1){
                        v[i]=0; v[i-1]=0; v[i-2]=0; v[i-3]=0;
                        max=0;min=0;kmax=0;kmin=0;
                    }
                }
                
                else{
                    cout<<"!ERROR! Decoder encountered an error for -V (voltage levels should alternate)";
                    return 0;
                        
                }
            }
            else {min+=1; kmin=1; kmax=0;}
        }
        
        if(v[i]==1) {
            if(kmax==1) {
                if((max+1+min)%2==0){
                    //following condition to pass the even exception at +V level
                    if(v[i]==1 && v[i-1]==0 && v[i-1]==v[i-2] && v[i-3]==1){
                        v[i]=0; v[i-1]=0; v[i-2]=0; v[i-3]=0;
                        max=0;min=0;kmax=0;kmin=0;
                    }
                }
                
                else{
                    cout<<"!ERROR! Decoder encountered an error for +V (voltage levels should alternate)";
                    return 0;
                        
                }
            }
            else {max+=1; kmax=1; kmin=0;}
        }
	    
        if(i+3<n){
            
            if ((max+min)%2!=0){ //odd case
                
                if(v[i]==0 && v[i]==v[i+1] && v[i+1]==v[i+2] && v[i+3]==-1 && kmin==1){
                    v[i]=0; v[i+1]=0; v[i+2]=0; v[i+3]=0;
                    max=0;min=0;kmax=0;kmin=0;
                }
                
                if(v[i]==0 && v[i]==v[i+1] && v[i+1]==v[i+2] && v[i+3]==1 && kmax==1){
                    v[i]=0; v[i+1]=0; v[i+2]=0; v[i+3]=0;
                    max=0;min=0;kmax=0;kmin=0;
                }
            }
        }
	}
	
	for(i=0; i<n; i++) //for for the rest -1 values.
	    if(v[i]==-1) v[i]=1;
	
	cout<<"Decoded HDB-3 code :"<<endl;
	for(i=0; i<n; i++)
    {
      cout<<v[i]<<" ";
    }
    if(hdberr)
        cout<<endl<<"34404 - represents the error bits";
  return 0;
}