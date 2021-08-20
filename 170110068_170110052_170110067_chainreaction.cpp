#include<simplecpp>
void print(int q[9][6]){
    for(int i=0;i<9;i++){
        for(int j=0;j<6;j++){
            if(q[i][j]/10==8){cout<<q[i][j]%10<<" ";}
            else if(q[i][j]/10==9){cout<<-1*q[i][j]%10<<" ";}
            else{cout<<q[i][j]<<" ";}
        }
        cout<<endl;
    }
    cout<<endl;
}
bool incheck(int q[9][6],int m,int n){
    if((m<9)and(n<6)and(m>=0)and(n>=0)){return true;}
    else{return false;}
}
int check(int q[9][6],int &r,int &t,int z){
    cin>>r;if(r==-1){return 0;};
    cin>>t;
    if((incheck(q,r,t))and((q[r][t]==0)or(q[r][t]/10==z))){
        return 1;
    }
    else{
        cout<<"Illegal move"<<endl;
        return check(q,r,t,z);
    }
}
void explode(int q[9][6],int x,int y,int z,int c[2]){
    if(incheck(q,x,y)){
        int cap;
        if(((x==0)or(x==8))and((y==0)or(y==5))){cap=1;    }
        else if((x==0)or(x==8)or(y==0)or(y==5)){cap=2; }
        else{cap=3; }

        if(q[x][y]/10!=z){
            q[x][y]=(q[x][y]%10)+z*10;
            c[!(z%2)]-=q[x][y]%10;c[(z%2)]+=q[x][y]%10;
        }

        if(c[!(z%2)]==0){return;}   //for instantaneous matrix returning

        if(q[x][y]%10<cap){
            q[x][y]+=1;return; }
        else{
            q[x][y]=0;
            explode(q,x,y+1,z,c);
            explode(q,x,y-1,z,c);
            explode(q,x+1,y,z,c);
            explode(q,x-1,y,z,c);
        }
    }
    return;
}
int main(){
    int q[9][6],c[2]={0,0},x,y,z=8;
    for(int i=0;i<9;i++){
        for(int j=0;j<6;j++){
            q[i][j]=0;
        }
    }
    if(!check(q,x,y,8)){return 0;}
        q[x][y]+=81;c[0]+=1;print(q);
    if(!check(q,x,y,9)){return 0;}
        q[x][y]+=91;c[1]+=1;print(q);

    while((c[0]!=0) and (c[1]!=0)){
        z=(z%2==0)?(8):9;
        if(!check(q,x,y,z)){return 0;};
        c[z-8]+=1;
        explode(q,x,y,z,c);
        z++;
        print(q);
    }
}
