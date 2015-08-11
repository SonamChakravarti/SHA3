/* 
 * File:   main.cpp
 * Author: Sona
 *
 * Created on October 8, 2013, 6:35 PM
 */

#include<iostream>
#include<string.h>
#include<strings.h>
#include<string>
#include<fstream>
#include<cstdlib>
#include<bitset>
#include<vector>
//#include<vector.h>


using namespace std;

/*
 * 
 */
class File2String{
public:
    string text1,input,data1;
    ifstream infile,infile2;
	ofstream infile3;
    int count;
    string* data;
    
    int GetLineNumber(string filename) {   
        count=0;
        infile.open(filename.c_str());
        while(!infile.eof())
        {
        
        getline(infile,input);
        count++;
        
        } 
        infile.close();
        
        return count;
    }    
    void CreateStringArray(string filename,int max) {
        
        data=new string[max];
        infile2.open(filename.c_str());
        for(int j=0;j<max;j++)
        {
            getline(infile2,data[j]);    
          //  cout<<j<<endl;
            
        }
        infile2.close();
        
    }
    string OneString() {
       for(int j=0;j<count;j++)
        {
           data1=data1+data[j];
        } 
		return data1;
       
    } 
	void WriteOut(string outputfile,string hash,string text){
        infile3.open(outputfile.c_str());
		infile3<<"Input String\n";
		infile3<<text;
        infile3<<"Message digest \n";
        infile3<<hash;
        infile3.close();
    }	
};
class String2Binary{
public:
    int text1;
    string bin;
    std::vector<std::bitset<8> > v;//temp bitset vector 
    std::vector<std::bitset<1088> > x;//message block bitset vector
    /*********Converts the string given as input to bit set vector of 8 bits each*********/
    void BinaryConverter(string& p){
    int str_len = p.length();
    int i;
    for(i = 0; i < str_len; i++){
        std::bitset<8>  bits(p[i]);
        v.push_back(bits);
        bin=bin+bits.to_string<char,std::string::traits_type,std::string::allocator_type>();// creates one big string on all lines in input file
        }
      }//binary converter
    /******************Pad the message string to 1088*k bits using 10*1 Padding rule*****/
    void Padding(std::vector<std::bitset<8> > b){
        int calc,check;
        int flag;
        flag=1;
        if(((b.size()*8)%1088)!=0)//check if already a multiple of 1088
        {
            calc=1088-((b.size()*8)%1088);//no.of bits to be padded
            check=calc/8;
            while(check>0)
            {
                if(flag){
                    std::bitset<8>  bits(128);
                    v.push_back(bits);
                    flag=0;
                    check--;
                }
                else if(check>1 and flag==0)
                {
                   std::bitset<8>  bits(0);
                    v.push_back(bits);
                    flag=0;
                    check--; 
                }
                else 
                {
                   std::bitset<8>  bits(1);
                    v.push_back(bits);
                    flag=0;
                    check--;  
                    
                }
            }   
        }//if
        else // if message blocks already a multiple of 8
        {
            check=1088/8;
            while(check>0)
            {
                if(flag){
                    std::bitset<8>  bits(128);
                    v.push_back(bits);
                    flag=0;
                    check--;
                }
                else if(check>1 and flag==0)
                {
                   std::bitset<8>  bits(0);
                    v.push_back(bits);
                    flag=0;
                    check--; 
                }
                else 
                {
                   std::bitset<8>  bits(1);
                    v.push_back(bits);
                    flag=0;
                    check--;  
                    
                }
        }
    }//else
    }//Padding
    /*******************Divide the block as per bit rate i.e. 1088 bits each*************/
    void DivideBlocks(std::vector<std::bitset<8> > a)    {
        string temp;
        int amt,point;
        amt=(a.size()*8)/1088;//number of blocks to be generated
        point=0;
        for(int i=0;i<amt;i++)
        {
            temp.clear();
            for(int j=point;j<=point+135;j++)
            {
                temp=temp+a.at(j).to_string<char,std::string::traits_type,std::string::allocator_type>();
            }
            point=point+135;
            std::bitset<1088>  bits(temp);
            x.push_back(bits);//each message block of 1088 pushed to a vector
        }
     //   cout<<"Size of 1088 vector:"<<x.size()<<endl;
    }//divide in blocks of 1088 bits
    
};
class SpongeFunction{
public:
    std::bitset<64> conv(string& h)
    {
        int size=h.size();
        string temp;
        temp.clear();
        for(int i=0;i<size;i++)
        {
        std::bitset<4> bit(h[i]);
        temp=temp+bit.to_string<char,std::string::traits_type,std::string::allocator_type>();
        }
        std::bitset<64> bit(temp);
        return bit;
        
    }//converts string to 64 bit bitset
    string buff,t1,t2;
    int k1,x;
    int arr[2][2];
    string* RC;
    std::bitset<256> L;
    string message_digest,hexout;
    std::bitset<1600>  sponge;
    std::vector<std::bitset<64> > RoundConstant;
    
    void Sponge1(std::vector<std::bitset<1088> > c){
        sponge=0;
        RC=new string[24];
        /****************************Round constants used for Iota**************************************/
        RC[ 0]  = " 0000000000000001" ;
        RC[ 1]  = " 0000000000008082" ;
        RC[ 2]  = " 800000000000808A" ;
        RC[ 3]  = " 8000000080008000" ;
        RC[ 4]  = " 000000000000808B" ;
        RC[ 5]  = " 0000000080000001" ;
        RC[ 6]  = " 8000000080008081" ;
        RC[ 7]  = " 8000000000008009" ;
        RC[ 8]  = " 000000000000008A" ;
        RC[ 9]  = " 0000000000000088" ;
        RC[10]  = " 0000000080008009" ;
        RC[11]  = " 000000008000000A" ;
        RC[12]  = " 000000008000808B" ;
        RC[13]  = " 800000000000008B" ;
        RC[14]  = " 8000000000008089" ;
        RC[15]  = " 8000000000008003" ;
        RC[16]  = " 8000000000008002" ;
        RC[17]  = " 8000000000000080" ;
        RC[18]  = " 000000000000800A" ;
        RC[19]  = " 800000008000000A" ;
        RC[20]  = " 8000000080008081" ;
        RC[21]  = " 8000000000008080" ;
        RC[22]  = " 0000000080000001" ;
        RC[23]  = " 8000000080008008" ;
       // ****************************************************************
         std::bitset<512>  temp(0);
        k1=c.size();//number of blocks
        /********XOR each block with sponge, run the functions Theta,Rho,Pi,Chi,Iota for 24 times (24*5 steps total)****/
        for(int i=0;i<k1;i++){ 
            t1=c.at(i).to_string<char,std::string::traits_type,std::string::allocator_type>();
            t2=temp.to_string<char,std::string::traits_type,std::string::allocator_type>();
            buff=t1+t2;//pad message block to make the length 1600 from 1088 by Padding 512 0's
            std::bitset<1600>  bits(buff);
            sponge^=bits;//xor the message block with sponge
            for(x=0;x<24;x++){
                Theta();
                Rho();
                Pi();
                Chi();
                Iota();
            }//no of rounds=24
        }// each block
        for(int i=0;i<256;i++){
            L[i]=sponge[i];
        }// 256 bits message digest
       // cout<<L<<endl;
        message_digest=ConvertToAscii(L); //converts message digest to ascii
       // cout<<message_digest<<endl;
        hexout=Bin2Hex(L.to_string<char,std::string::traits_type,std::string::allocator_type>());
		cout<<"Output Message Digest:"<<endl;
        cout<<hexout<<endl;//convert message digest to hex
    }//sponge
     /*********Theta Function*********************************/
        //steps as below
        //a[i][j][k] ?= parity(a[0..4][j-1][k]) ? parity(a[0..4][j+1][k-1])
        // Let a[i][j][k] be bit (i×5 + j)×w + k
    void Theta(){
         int w;
        w=64;
    
        for(int i=0;i<5;i++){
            for(int j=0;j<5;j++){
                for(int k=0;k<64;k++){
                    for(int l=0;l<5;l++){
                        int s,p,q;
                        if(k==0)
                        {
                            s=64;
                        }
                        else{
                            s=k;
                        }
                        if(j==0)
                        {
                            p=5;
                        }
                        else{
                            p=j;
                        }
                        if(j==4)
                        {
                            q=0;
                        }
                        else
                        {
                            q=j;
                        }
                         sponge[(i*5 + j)*w + k]=sponge[(i*5 + j)*w + k]^(sponge[(l*5 + p-1)*w + k]^sponge[(l*5 + q+1)*w + s-1]);    
                         
                        
                    }//for l                  
                }//for k
            }//for j
        }//for i
     
    }// Theta
     /***************Rho Function*************************/
    void Rho(){
        
        int trr[2][2];
        int brr[2];
        arr[0][0]=3;
        arr[0][1]=2;
        arr[1][0]=1;
        arr[1][1]=0;
        brr[0]=1;
        brr[1]=0;
        int i,h;
        int j;
        int w;
        for(int t=0;t<24;t++){
            w=64;
           for(int k=0;k<64;k++){
               if(t==0){
                   i=0;
                   j=1;
                   arr[0][0]=3;
                   arr[0][1]=2;
                   arr[1][0]=1;
                   arr[1][1]=0;
               }//t==0
               else if (t==1)
               {
                   i=2;
                   j=0;  
               }//t==1
               else
               {
                   MatrixMultiplication();
                   i=arr[0][1];
                   j=arr[1][1];                   
                   
               }//t>1
            
               h=k-(t+1)*(t+2)/2;
               //calculate modulus 64 of h
               if(h<0){
                   h=h%64;
                   h=64+h;
               }
               if (h>63){
                   h=h%64;
               }
               sponge[(i*5 + j)*w + k]=sponge[(i*5 + j)*w + h];
             
        }//for k
            
        }//for t
        
    }//Rho
          /************matrix multiplication***********************/
    void MatrixMultiplication(){
        int trr[2][2];
        int srr[2][2];
        srr[0][0]=3;
        srr[0][1]=2;
        srr[1][0]=1;
        srr[1][1]=0;
         
        trr[0][0]=(arr[0][0]*srr[0][0]+arr[0][1]*srr[1][0])%5;//restrict each element below 5
        trr[0][1]=(arr[0][0]*srr[0][1]+arr[0][1]*srr[1][1])%5;
        trr[1][0]=(arr[1][0]*srr[0][0]+arr[1][1]*srr[1][0])%5;
        trr[1][1]=(arr[1][0]*srr[0][1]+arr[1][1]*srr[1][1])%5;
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                arr[i][j]=trr[i][j];
            }//for j
        }// for i

        }//matrix multiplication
     /***********************Pi Function**************/
     //permutes the bits
    void Pi(){
        int w;
        for(int i=0;i<5;i++)
        {
            w=64;
            for(int j=0;j<5;j++)
            {
                for(int k=0;k<64;k++)
                {
                  sponge[(j*5 + ((2*i+3*j)%5))*w + k]=sponge[(i*5 + j)*w + k];  
                }//for k
            }//for j
            
        }// for i
        
    }
     /**********************Chi function***********************/
    void Chi(){
         int w;
          //a[i][j][k] ?= ¬a[i][j+1][k] & a[i][j+2][k]
         for(int i=0;i<5;i++)
        {
            w=64;
            for(int j=0;j<5;j++)
            {
                for(int k=0;k<64;k++){
                    
                    sponge[(i*5 + j)*w + k]=sponge[(i*5 + j)*w + k]^((!(sponge[(i*5 + (j+1)%5)*w + k]))&sponge[(i*5 + (j+2)%5)*w + k]);
                }//for k
            }//for j
         }//for i
        
    }// Chi
     /**************************Iota Function************/
     //xor first word with round constant corresponding to that round***********/
    void Iota(){
         std::bitset<64> round;
         round=conv(RC[x]);
         for(int i=0;i<64;i++){
             sponge[i]=sponge[i]^round[i];
         }//for i
    }//Iota
    string ConvertToAscii(std::bitset<256> d){
         std::bitset<8> tt;
         int test,x1;
         string temp,m;
         x1=0;
         while(x1<252)
         {
         for(int i=0;i<=6;i++){
             tt[i]=d[x1+i];
             
         }
         x1=x1+7;
         test=tt.to_ulong();
         m=char(test);
         temp=m+temp;
         
         }
         for(int g=0;g<3;g++){
             tt[g]=0;
         }
         tt[3]=d[252];
         tt[4]=d[253];
         tt[5]=d[254];
         tt[6]=d[255];
         test=tt.to_ulong();
         m=char(test);
         temp=m+temp;
         return temp;
             
     }
    string Bin2Hex(string in){
                string temp1,temp2;
                string chr = "0000";
                int len = in.length()%4;
                int k=4-len;
                temp1.clear();
                temp2.clear();
                if (len!=0){
		chr = chr.substr(0,k);
		in = chr+in;
                }
                for (int i=0;i<in.length();i=i+4){
		temp2 = in.substr(i,4);
		if (!temp2.compare("0000"))
		{
                    temp1.append("0");			
		}
		else if (!temp2.compare("0001"))
		{
			temp1.append("1");	
		}
		else if (!temp2.compare("0010"))
		{
			temp1.append("2");	
		}
		else if (!temp2.compare("0011"))
		{
			temp1.append("3");	
		}
		else if (!temp2.compare("0100"))
		{
			temp1.append("4");	
		}
		else if (!temp2.compare("0101"))
		{
			temp1.append("5");	
		}
		else if (!temp2.compare("0110"))
		{
			temp1.append("6");	
		}
		else if (!temp2.compare("0111"))
		{
			temp1.append("7");	
		}
		else if (!temp2.compare("1000"))
		{
			temp1.append("8");	
		}
		else if (!temp2.compare("1001"))
		{
			temp1.append("9");	
		}
		else if (!temp2.compare("1010"))
		{
			temp1.append("a");	
		}
		else if (!temp2.compare("1011"))
		{
			temp1.append("b");	
		}
		else if (!temp2.compare("1100"))
		{
			temp1.append("c");	
		}
		else if (!temp2.compare("1101"))
		{
			temp1.append("d");	
		}
		else if (!temp2.compare("1110"))
		{
			temp1.append("e");	
		}
		else if (!temp2.compare("1111"))
		{
			temp1.append("f");	
		}
                }
                return temp1;
		}//string binary to hex
    
    
};
int main(int argc, const char *argv[]) {
    if(argc<3){
        cout<<"Error in number of Input Arguments. USAGE: ./sha3 input_filename.txt output_filename.txt "<<endl;       
    }
    else
    {
File2String h;
String2Binary b;
SpongeFunction s;
string filename;
string outputfile;
string text;
//cout<<"enter file name:"<<endl;
//cin>>filename;
filename=argv[1];
outputfile=argv[2];
h.GetLineNumber(filename);//gets the number of line in the input file
h.CreateStringArray(filename,h.count);//creates string array
text=h.OneString();// creates one string
cout<<"Input String:"<<endl;
cout<<text<<endl;
b.BinaryConverter(h.data1);//creates bit set vector
b.Padding(b.v);// pads the initial vector to 1088*k form
b.DivideBlocks(b.v);//divides the message blocks
s.Sponge1(b.x);// runs all the functions and stores the message digest and prints the same
h.WriteOut(outputfile,s.hexout,text);//write output to file
return 0;
}//else arguments correct
}
