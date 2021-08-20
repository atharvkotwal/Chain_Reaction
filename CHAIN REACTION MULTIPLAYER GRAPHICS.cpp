#include<simplecpp>
string cl[]={"Pink","Yellow","Blue","Red","Green","Orange","brown","gray","Voilet"};
int clrs[9][3]={{255,20,150},{255,255,0},{0,0,255},{255,0,0},{0,255,0},{255,180,0},{180,0,0},{140,140,140},{255,0,255}};

void losewin(int c[],int n){
    int v=0;
    for(int e=1;e<=n;e++){
        if(c[e-1]==0){cout<<cl[e-1]<<" loses\t";}
        else{v=v*10+e;}
    }
    cout<<endl;
    if(v/10==0){
    Text t2(600,25,cl[(v%10)-1]+"WINS!!!!");t2.setColor(COLOR(clrs[(v%10)-1][0],clrs[(v%10)-1][1],clrs[(v%10)-1][2]));t2.imprint();wait(10);
    cout<<cl[(v%10)-1]<<" WINS!!";
    }
}

void graphic(int a,int b,int m,int z){
a= 100*a+100;b=100*b+100;

Circle c1(a,b,48);c1.setColor(COLOR(255,255,255));c1.setFill();c1.imprint();
if(m==1){
    Circle c1(a,b,20);c1.setColor(COLOR(clrs[z-1][0],clrs[z-1][1],clrs[z-1][2]));c1.setFill();c1.imprint();}
else if(m==2){
    Circle c1(a-20,b,20);c1.setColor(COLOR(clrs[z-1][0],clrs[z-1][1],clrs[z-1][2]));c1.setFill();c1.imprint();
    c1.move(40,0);c1.imprint();
}
else if(m==3){
    Circle c1(a,b,20);c1.setColor(COLOR(clrs[z-1][0],clrs[z-1][1],clrs[z-1][2]));c1.setFill();
    c1.move(0,-40/sqrt(3));c1.imprint();
    c1.move(-20,60/sqrt(3));c1.imprint();
    c1.move(40,0);c1.imprint();
}
return;}
void grid(int z){
for(int x=50;x<=950;x+=100){
    Line l(x,50,x,650);l.setColor(COLOR(clrs[z-1][0],clrs[z-1][1],clrs[z-1][2]));l.imprint();
}
for(int y=50;y<=650;y+=100){
    Line l(50,y,950,y);l.setColor(COLOR(clrs[z-1][0],clrs[z-1][1],clrs[z-1][2]));l.imprint();
}}
void print(int q[9][6],int c[],int n){
    char clr[]={'P','Y','B','R','G','O','b','g','V'};
    for(int i=0;i<6;i++){
        for(int j=0;j<9;j++){
            if(q[j][i]/10!=0){
            cout<<clr[q[j][i]/10-1]<<q[j][i]%10<<"\t";
            }
            else{cout<<q[j][i]<<"\t";}
        }
        cout<<endl;
    }
    cout<<endl;
    for(int r=0;r<n;r++){
    cout<<cl[r]<<" - "<<c[r]<<" ";
    Text t(50+r*100,675,cl[r]+"-");t.setColor(COLOR(clrs[r][0],clrs[r][1],clrs[r][2]));t.imprint();
    Text t4(90+r*100,675,c[r]);t4.setColor(COLOR(clrs[r][0],clrs[r][1],clrs[r][2]));t4.imprint();
    }
    cout<<endl;
}
void getval(int &x,int &y){
    int g=getClick();
    x= g/65536;y=g%65536;
    x= (x-50)/100;y=(y-50)/100;
}
bool incheck(int q[9][6],int m,int n){
    if((m<9)and(n<6)and(m>=0)and(n>=0)){return true;}
    else{return false;}
}
void check(int q[9][6],int &r,int &t,int m){
    if((incheck(q,r,t))and((q[r][t]==0)or(q[r][t]/10==m))){
        return;
    }
    else{
        cout<<"Invalid input. Enter again \n";
        getval(r,t);
        return check(q,r,t,m);
    }
}
void explode(int q[9][6],int x,int y,int z,int c[]){
    if(incheck(q,x,y)){
        int cap;
        if(((x==0)or(x==8))and((y==0)or(y==5))){cap=1;    }
        else if((x==0)or(x==8)or(y==0)or(y==5)){cap=2; }
        else{cap=3; }
        if(q[x][y]/10!=z){
            c[(q[x][y]/10)-1]-=q[x][y]%10;c[z-1]+=q[x][y]%10;q[x][y]=(q[x][y]%10)+z*10;
        }
        if(q[x][y]%10<cap){
            q[x][y]+=1;graphic(x,y,q[x][y]%10,z);
            return; }
        else{
            q[x][y]=0;graphic(x,y,q[x][y]%10,z);
            explode(q,x,y+1,z,c);
            explode(q,x,y-1,z,c);
            explode(q,x+1,y,z,c);
            explode(q,x-1,y,z,c);
        }
    }
    return;
}
bool func(int c[],int &z,int n){
    int s=z;
    z++;z=(z>n)?(1):z;
    while(c[z-1]==0){
        z++;z=(z>n)?(1):z;
    }
    if(z==s){return false;}
    else{return true;}
}
main_program{
    int n;cout<<"No. of players(<10) - ";cin>>n;while(!((n>0)and (n<10))){cout<<"Invalid Input! Try Again -";cin>>n;}
    initCanvas("window",1000,700);Text t4(500,25,"CHAIN REACTION");t4.scale(5);t4.setColor(COLOR("red"));
    int q[9][6],c[n],x,y,z=0;
    for(int p=0;p<n;p++){c[p]=0;}
    for(int i=0;i<9;i++){
        for(int j=0;j<6;j++){
            q[i][j]=0;
        }
    }
    print(q,c,n);
    for(int w=1;w<=n;w++){
        grid(w);
        cout<<cl[w-1]<<"'s turn - "<<endl;
        getval(x,y);check(q,x,y,w); q[x][y]+=w*10+1;c[w-1]+=1;
        print(q,c,n);
        graphic(x,y,q[x][y]%10,w);
        }
    while(func(c,z,n)){
        grid(z);
        cout<<cl[z-1]<<"'s turn - "<<endl;
        getval(x,y);
        check(q,x,y,z);
        c[z-1]+=1;
        explode(q,x,y,z,c);
        print(q,c,n);losewin(c,n);
    }
}
