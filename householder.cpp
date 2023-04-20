#include<bits/stdc++.h>
using namespace std;

#define int float

//Defining few functions for elementary matrix operations
//Filter the values of the matrix for the floating point operations
vector<vector<int>> filter(vector<vector<int>> v,int eps){
    
    vector<vector<int>> mat(v.size(),vector<int>(v[0].size()));

    for(int i=0;i<v.size();i++){
        for(int j=0;j<v[0].size();j++){
            if(abs(v[i][j]) < eps) mat[i][j] = 0;
            else mat[i][j] = v[i][j];
        }
    }
    return mat;
}

//get the matrix A from the cin input stream
void getMatrix(vector<vector<int>> &v){
    const int m = v.size();
    const int n = v[0].size();

    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++)cin>>v[i][j];
    }

}

//display any matrix that is passed to the function
void displayMatrix(vector<vector<int>> v){
    const int m = v.size();
    const int n = v[0].size();

    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++)cout<<setprecision(5)<<v[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

//get the identity matrix of any dimension passed as argument
vector<vector<int>> getIdentity(int n){
    vector<vector<int>> I(n,vector<int>(n));

    for(int i=0;i<n;i++){
        I[i][i] = 1;
    }

    return I;
}

//get the dimensions of any matrix
pair<int,int> getdim(vector<vector<int>> v){
pair<int,int> p = {v.size(),v[0].size()};
return p;
}

//get the transpose of a matrix
vector<vector<int>> gettranspose(vector<vector<int>> v){
    pair<int,int> p = getdim(v);

    vector<vector<int>> A_dash(p.second, vector<int>(p.first));

    for(int i=0;i<p.second;i++){
        for(int j=0;j<p.first;j++){
            A_dash[i][j] = v[j][i];
        }
    }

    return A_dash;
}

//function to add two given matrices in the arguments
vector<vector<int>> getAdd(vector<vector<int>> v1,vector<vector<int>> v2){
    pair<int,int> p1 = getdim(v1);
    pair<int,int> p2 = getdim(v2);

    if(p1.first == p2.first && p2.second == p1.second){
        vector<vector<int>> v(p1.first,vector<int> (p1.second));
        for(int i=0;i<p1.first;i++){
            for(int j=0;j<p1.second;j++){
                v[i][j]=v1[i][j]+v2[i][j];
            }
        }
        return v;
    }
    else{
        cout<<"Error with dimensionality while adding the two given matrices";
        vector<vector<int>> v;
        return v;
    }
}

//function to scale all the values of a given matrix with a given non zero real number
vector<vector<int>> getScaledMatrix(vector<vector<int>> v,int scale){
    vector<vector<int>> m = v;
    for(int i=0;i<v.size();i++){
    for(int j=0;j<v[0].size();j++) m[i][j]*=scale;
    }
    return m;
}

//multiplication of the two given matrices
vector<vector<int>> getMul(vector<vector<int>> v1,vector<vector<int>> v2)
{
    pair<int,int> p1 = getdim(v1);
    pair<int,int> p2 = getdim(v2);

    if(p1.second == p2.first){
        vector<vector<int>> v(p1.first,vector<int> (p2.second));

        for(int i=0;i<p1.first;i++){
            for(int j=0;j<p2.second;j++){
                for(int k=0;k<p1.second;k++){
                    v[i][j]+=v1[i][k]*v2[k][j];
                }
            }
        }

        return v;
    }
    else{
        cout<<"Error, the multiplication is not possible";
        vector<vector<int>> v;
        return v;
    }

}

//Now definining the main Householder method functions
vector<vector<int>> col(vector<vector<int>> A,int i,int j){
    pair<int,int> p = getdim(A);

    vector<vector<int>> c(p.first-i,vector<int>(1));
    for(int k=0;k<p.first-i;k++){
        c[k][0]=A[k+i][j];
    }

    return c;

}

//get second norm of a 1-D matrix or a vector
int signum(int x){
    return x>=0?1:-1;
}

int secondnorm(vector<vector<int>> v){
pair<int,int> p= getdim(v);
int norm = 0;
for(int i=0;i<p.first;i++){
    for(int j=0;j<p.second;j++){
        norm+=v[i][j]*v[i][j];
    }
}

return sqrt(norm);
}

//get the u-vector to find out subsequent Householder matrices
vector<vector<int>> getu(vector<vector<int>> v){
    vector<vector<int>> u = v;
    u[0][0]-=signum(v[0][0])*secondnorm(v);
    return u;
}

//construct the Householder matrix from the column
vector<vector<int>> Householder(vector<vector<int>> u){
    pair<int,int> p=getdim(u);

    vector<vector<int>> H(p.first,vector<int>(p.first));
    vector<vector<int>> I = getIdentity(p.first);

    vector<vector<int>> sub = getMul(u,gettranspose(u));
    vector<vector<int>> s = getMul(gettranspose(u),u);
    int sc = s[0][0];
    sub = getScaledMatrix(sub,-2/sc);
    H = getAdd(I,sub);
    return H;
}

//Construct the modified matrix for multiplication with matrix A 
vector<vector<int>> constructModifiedMatrix(vector<vector<int>> H,int m){
    vector<vector<int>> _H(m,vector<int> (m));
    pair<int,int> p = getdim(H);

    int diff = m-p.first;

    for(int i=0;i<diff;i++){
        _H[i][i]=1;
    }
    for(int i=diff;i<m;i++){
        for(int j=diff;j<m;j++){
            _H[i][j] = H[i-diff][j-diff];
        }
    }

    return _H;
}

//Defining the function to get the QR decomposition matrices from the Householder method given the matrix A to be decomposed
void mainHouseHolder(vector<vector<int>> A){
    pair<int,int> dim = getdim(A);
    const int times = dim.first - 1;

    vector<vector<int>> Q;
    vector<vector<int>> R = A;

    for(int i=0;i<times;i++){
        vector<vector<int>> f = col(R,i,i);
        vector<vector<int>> u = getu(f);

        vector<vector<int>> H = Householder(u);
        vector<vector<int>> _H = constructModifiedMatrix(H,dim.first);

        R = getMul(_H,R);
        if(i==0){
            Q = gettranspose(_H);
        }
        else{
            Q = getMul(Q,gettranspose(_H));
        }

    }

    vector<vector<int>> _Q = filter(Q,1e-6);
    vector<vector<int>> _R = filter(R,1e-6);
    displayMatrix(_Q);
    displayMatrix(_R);
}


int32_t main(){

    int m,n;
    cin>>m>>n;

    vector<vector<int>> A(m,vector<int>(n));
    getMatrix(A);
    displayMatrix(A);

    mainHouseHolder(A);

    return 0;
}