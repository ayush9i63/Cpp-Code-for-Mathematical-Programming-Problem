#include<iostream>
#include<iomanip>
#include<climits>
using namespace std;

int main(){
    int var,cons,problem,les,eq,great;
    cout.precision(3);

 l1:cout<<"\nEnter total numbers of variables,constraints,<= constraints,= constraints,>= constraints: \n";

    cin>>var>>cons>>les>>eq>>great;
    
    if((les+eq+great)!=cons){
        cout<<"\nWrong inputs..."<<"\nRe-enter :";
        goto l1;
    }

    double C[var+cons+eq];
    double A[cons+eq][var+cons+eq];
    double B[cons+eq];

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
    for(int i=0;i<cons+eq;i++){
        if(i<(les+eq)) for(int j=0;j<var;j++) cin>>A[i][j];
        else for(int j=0;j<var;j++){
            cin>>A[i][j];
            A[i][j]= -A[i][j];
        }
        for(int j=0;j<cons+eq;j++){
            if (i==j) A[i][var+j]=1;
            else A[i][var+j]=0;
        }
    }

    cout<<"\nEnter the solution column: ";
    for(int i=0;i<cons;i++){
        if(i<(les+eq)) cin>>B[i];
        else{
            cin>>B[i];
            B[i]= -B[i];
        }
    } 
    
    cout<<"\n--------------------------------------------------------------------SIMPLEX METHOD--------------------------------------------------------------------";

    cout<<"\n\nThus the given LPP is: ";
    if(problem==1) cout<<"\n\n\tmax: ";
    else cout<<"\n\n\tmin: ";
    for(int i=0;i<var;i++){
        if(problem==0) cout<<-C[i]<<"x"<<i+1;
        else cout<<C[i]<<"x"<<i+1;
        if(i<var-1) cout<<" + ";
    }

    cout<<"\n\nsubject tO:\n\n";
    for(int i=0;i<cons+eq;i++){
        for(int j=0;j<var;j++){
            if(i<les+eq) cout<<"\t"<<A[i][j]<<"x"<<j+1;
            else if(i>=(cons-great)) cout<<"\t"<<-A[i][j]<<"x"<<j+1;
            if(j<var-1) cout<<" + ";
        }
        if(i<les) cout<<" <= ";
        else if(i>=les && i<les+eq) cout<<" =  ";
        else if(i>=(cons-great)) cout<<" >= ";
        if(i<les+eq) cout<<B[i];
        else if(i>=(cons-great)) cout<<-B[i];
        cout<<endl;
    }
    cout<<"\n\t\tall xj >= 0\n\n";
    
    cout<<"\n\nPhase 1:\n\n";

    // Simplex

    double z_c[var+cons+eq];
    double cb[cons+eq];
    double variable[cons+eq];
    double sol[cons+eq];
    double min_ratio[var+cons+eq];
    double min,min2,max;
    double alternate[var+great];
    int enter,ext,flag,count=cons;
    double pivot,ratio,res;

    for(int i=0;i<cons;i++){
        cb[i]=C[var+i];
        sol[i]=B[i];
        variable[i]=var+i;
    }

    while (true){
        
        min=INT_MAX;
        for(int j=0;j<var+cons+eq;j++)
        {
            z_c[j]=0;
            for(int i=0;i<cons;i++) z_c[j] += A[i][j]*cb[i];
            z_c[j] -= C[j];
            if(min>z_c[j]){
                min=z_c[j];
            }
        }

        
        //printint simplex table-----------------------------------------------------------------------------------
        cout<<setw(10)<<"  "<<setw(10)<<"  "<<setw(3)<<"|"<<setw(10)<<"Cj"<<setw(3)<<"|";
        for(int j=0;j<cons+var+eq;j++){
            cout<<setw(10)<<C[j];
        }
        cout<<setw(3)<<"|"<<setw(10)<<"  "<<endl;
        
        cout<<setw(10)<<"CB"<<setw(10)<<"XB"<<setw(3)<<"|"<<setw(10)<<"Sol"<<setw(3)<<"|";
        for(int i=0;i<cons+var+eq;i++) cout<<setw(9)<<"x"<<i+1;
        cout<<setw(3)<<"|"<<endl;
        
        for(int i=0;i<(10*(var+cons+eq)+55);i++) cout<<"-";
        cout<<endl;

        for(int i=0;i<cons+eq;i++){
            cout<<setw(10)<<cb[i]<<setw(9)<<"x"<<variable[i]+1<<setw(3)<<"|"<<setw(10)<<sol[i]<<setw(3)<<"|";
            for(int j=0;j<cons+var+eq;j++){
                cout<<setw(10)<<A[i][j];
            }
            cout<<setw(3)<<"|"<<endl;
        }
        
        for(int i=0;i<(10*(var+cons+eq)+55);i++) cout<<"-";
        cout<<endl;
        
        cout<<setw(10)<<"  "<<setw(10)<<"  "<<setw(3)<<"|"<<setw(10)<<"z_c"<<setw(3)<<"|";
        for(int j=0;j<cons+var+eq;j++){
            cout<<setw(10)<<z_c[j];
        }
        cout<<endl;
        cout<<setw(10)<<"  "<<setw(10)<<"  "<<setw(3)<<"|"<<setw(10)<<"Min ratio"<<setw(3)<<"|";
        for(int j=0;j<cons+var+eq;j++){
            if(min_ratio[j]>0){
                cout<<setw(10)<<min_ratio[j];
            }
            else cout<<setw(10)<<"--";
        }
        


        cout<<setw(3)<<"|"<<setw(10)<<"  "<<endl;
        cout<<endl<<endl;
        //printing complete-----------------------------------------------------------------------------------------
        
        if(min<0){
            cout<<"\nDual simplex method is inapplicable....";
            goto l5;
        }

        min2=INT_MAX;
        for(int i=0;i<cons+eq;i++){
            if(min2>sol[i]){
                min2=sol[i];
                ext=i;
            }
        }
        max=INT_MIN;
        for(int i=0;i<var+cons+eq;i++){
            if(A[ext][i]<0){
                min_ratio[i]=z_c[i]/A[ext][i];
                if(max<min_ratio[i]){
                    max=min_ratio[i];
                    enter=i;
                }
            }
            else min_ratio[i]=1;
        }
        if(max==INT_MIN){
            cout<<"\nSolution is infeasible...";
            goto l5;
        }

        if(min2<0){
           
            cb[ext]=C[enter];
            variable[ext]=enter;
            
            pivot=A[ext][enter];

            //using ert

            for(int i=0;i<cons+var+eq;i++) A[ext][i]/=pivot;
            sol[ext]/=pivot;

            for(int i=0;i<cons+eq;i++){
                if(i!=ext){
                    ratio=A[i][enter];
                    for(int j=0;j<var+cons+eq;j++){
                        A[i][j] -= ratio*A[ext][j];
                    }
                    sol[i] -= ratio*sol[ext];
                }
            }
        }
        else break;
    }
           
    //checking degeneracy
        
        for(int i=0;i<cons;i++){ 
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

l5: cout<<"\n\n--------------------------------------------------------------------DUAL SIMPLEX ENDS--------------------------------------------------------------------";

}
