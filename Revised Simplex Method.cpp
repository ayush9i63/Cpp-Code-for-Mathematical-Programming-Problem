#include<iostream>
#include<iomanip>
#include<climits>
using namespace std;

int main(){
    int var,cons,problem,les,eq,great;
    cout.precision(3);

    cout<<"\nEnter total numbers of variables,constraints\n";
    cin>>var>>cons;
 
    double C[var+cons];
    double A[cons][var+cons];
    double B[cons];

    cout<<"\nEnter '1' for maximisation problem and '0' for minimisation problem: ";
    cin>>problem;

    cout<<"\nEnter the coefficient of objective function: ";
    for(int i=0;i<var;i++){
        cin>>C[i];
       if(problem==0) C[i]=-C[i];
    }
    for(int i=0;i<cons+eq;i++){
        C[var+i]=0;
    }

    cout<<"\nEnter the coefficient of contraints: ";
    for(int i=0;i<cons;i++){
        for(int j=0;j<var;j++) cin>>A[i][j]; 
        for(int j=0;j<cons;j++){
            if (i==j) A[i][var+j]=1;
            else A[i][var+j]=0;
        }
    }

    cout<<"\nEnter the solution column: ";
    for(int i=0;i<cons;i++) cin>>B[i];
    
    cout<<"\n--------------------------------------------------------------------SIMPLEX METHOD--------------------------------------------------------------------";

    cout<<"\n\nThus the given LPP is: ";
    if(problem==1) cout<<"\n\n\tmax: ";
    else cout<<"\n\n\tmin: ";
    for(int i=0;i<var;i++){
        if(problem==0) cout<<-C[i]<<"x"<<i+1;
        else cout<<C[i]<<"x"<<i+1;
        if(i<var-1) cout<<" + ";
    }

    cout<<"\n\nsubject to:\n\n";
    for(int i=0;i<cons+eq;i++){
        for(int j=0;j<var;j++){
            cout<<"\t"<<A[i][j]<<"x"<<j+1;
            if(j<var-1) cout<<" + ";
        }
        cout<<" <= ";
        cout<<B[i];
        cout<<endl;
    }
    cout<<"\n\t\tall xj >= 0\n\n";
    

    // Simplex
    double Bi[cons][cons];
    double pvc[cons];
    double W[cons];
    double z_c[var+cons];
    double cb[cons];
    double variable[cons];
    double sol[cons];
    double min_ratio[var+cons];
    double min,min2;
    int enter,leave;
    double pivot,ratio,res,temp;

    for(int i=0;i<cons;i++){
        cb[i]=C[var+i];
        sol[i]=B[i];
        variable[i]=var+i;
        for(int j=0;j<cons;j++){
            Bi[i][j]=A[i][var+j];
        }
    }

    while(true){
    	//calculating W
    	for(int i=0;i<cons;i++){
    		W[i]=0;
    		for(int j=0;j<cons;j++){
    			W[i]+=cb[j]*Bi[j][i];
			}
		}
        min=INT_MAX;
        for(int j=0;j<var+cons+eq;j++)
        {
            z_c[j]=0;
            for(int i=0;i<cons;i++) z_c[j] += A[i][j]*W[i];
            z_c[j] -= C[j];
            if(min>z_c[j]){
                min=z_c[j];
                enter=j;
            }
        }

        for(int i=0;i<cons;i++){
            pvc[i]=A[i][enter];
        }
        for(int i=0;i<cons;i++){
        	temp=0;
            for(int j=0;j<cons;j++){
                temp+=pvc[j]*Bi[i][j];
            }
            pvc[i]=temp;
        }
        
        min2=INT_MAX;
        for(int i=0;i<cons;i++){
        	
            if(pvc[i]>0){
                min_ratio[i]=sol[i]/pvc[i];
                if(min2>min_ratio[i]){
                    min2=min_ratio[i];
                    leave=i;
                }
            }
            else min_ratio[i]=1;
            
        }
        
        if(min2==INT_MAX){
            cout<<"\nSolution is Unbounded...";
            goto l5;
        }
        
        //print in progress...
        cout<<setw(3)<<"--"<<setw(cons*10)<<"Basis Inverse"<<setw(10)<<"Sol"<<setw(10)<<"Pivot"<<endl;
        cout<<setw(3)<<"W";
		for(int i=0;i<cons;i++){
            cout<<setw(10)<<W[i];
        }
        cout<<setw(10)<<"--"<<setw(10)<<C[enter]<<setw(3)<<"C"<<endl; 
        for(int i=0;i<cons;i++){
        	cout<<setw(3)<<"--";
            for(int j=0;j<cons;j++){
                cout<<setw(10)<<Bi[i][j];
            }
            cout<<setw(10)<<sol[i]<<setw(10)<<pvc[i]<<endl;
        }
        cout<<endl;

        
        //print finish...
        if(min<0){
           
            cb[leave]=C[enter];
            variable[leave]=enter;
            
            pivot=pvc[leave];

            //using ert

            for(int i=0;i<cons;i++) Bi[leave][i]/=pivot;
            sol[leave]/=pivot;

            for(int i=0;i<cons;i++){
                if(i!=leave){
                    ratio=pvc[i];
                    for(int j=0;j<cons;j++){
                        Bi[i][j] -= ratio*Bi[leave][j];
                    }
                    sol[i] -= ratio*sol[leave];
                }
            }
        }
        else break;
    }
    
    //checking degeneracy
        
        for(int i=0;i<cons+eq;i++){
            if(sol[i]==0){
                cout<<"\nThe solution is degenerate.\n";
            }
        }
    
    cout<<"\nThe required optimal solution is given at: \n";
    cout.precision(10);
    res=0;
    for(int i=0;i<cons;i++){
        cout<<"x"<<variable[i]+1<<" = "<<sol[i]<<endl;
        if(problem==0) res+=(-cb[i])*sol[i];
        else res+=(cb[i])*sol[i];
    }
    cout<<"all remaining xi = 0"<<endl;
    cout<<"The optimal value is: "<<res;

l5: cout<<"\n\n--------------------------------------------------------------------REVISED SIMPLEX ENDS--------------------------------------------------------------------";

}
