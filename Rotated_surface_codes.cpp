
#include <iostream>
#include<cstring>
#include<string>
#include<vector>
#include <fstream>
#include <math.h> 

using namespace std;

bool Qcommute(const string& v1, const string& v2) {
	int parity = 1;
	for (int i = 0; i < v1.size(); i++) {
		if ((v1[i] != 'I') && (v2[i] != v1[i]) && (v2[i] != 'I')) {
			parity = parity * (-1);
		}
	}
	if (parity == -1) {
		return false;
	}
	return true;
}
//this functon is not used in the file.

// the product of 2 Pauli operators:

string product(const string&v1, const string &v2){
	string p;
	
	for (int i=0;i<v1.size();i++){
		if(v1[i]=='I'){
			p.push_back(v2[i]);
		}
		else if(v1[i]==v2[i]){
			p.push_back('I');
		}
		else if(v2[i]=='I'){
			p.push_back(v1[i]);
		}
		else if(v1[i]=='X'){
			if (v2[i]=='Y'){
				p.push_back('Z');
			}
			if (v2[i]=='Z'){
				p.push_back('Y');
			}
		}
		else if(v1[i]=='Y'){
			if (v2[i]=='X'){
				p.push_back('Z');
			}
			if (v2[i]=='Z'){
				p.push_back('X');
			}
		}
		else if(v1[i]=='Z'){
			if (v2[i]=='Y'){
				p.push_back('X');
			}
			if (v2[i]=='X'){
				p.push_back('Y');
			}
		}
		
	}

	return p;
}
//if the certain Pauli is in the set (s).
bool Qin (const vector<string> &s,const string &o){
	for (int i=0;i<s.size();i++){
		if(o==s[i]){
			return true;
		}
	}
	
	return false;
	
}

//use a set of	Paulis (s) to generate the whole group, I hope to know how many elements are in the group, so I know the number of 
//independent generators.
//dimension in fact is the number of qubits.
vector<string> generate (const vector<string> &s,int dimension){
	string temp;
	vector<string> s1;
	s1 = s;
	for (int i=0;i<s1.size();i++){
		for(int j=s1.size()-1;j>=i;j--){
			temp=product(s1[i],s1[j]);
			if(!Qin(s1,temp)){
				s1.push_back(temp);
			}
		}
	}

	return s1;
	
}
//this function is not used in the file:
string Pauli(int n,bool x,bool y,bool z){
	string P;
	
	for(int j=0;j<n;j++)
	{
		if (y) {
			P.push_back('Y');
		}
		else if(x){
		 P.push_back('X');
	     }
	    else if(z){
			P.push_back('Z');
		}
		else{
			P.push_back('I');
		}
	    
	}
	
	return P;
}
//get these gi
string getstabilizers(int i,int n,int a, int b){
	int i1=i%n;
	int i2=(i1+a)%n;
	int i3=(i2+b)%n;
	int i4=(i3+a)%n;
	string gs;
	
	for (int j = 0; j < n; j++) {
		gs.push_back('I');
	}
	gs[i1] = 'X';
	gs[i2] = 'Z';
	gs[i3] = 'Z';
	gs[i4] = 'X';
	return gs;
}

ofstream output("output.txt");
int main()

{	
	
	double r=0;
	vector<string> operaters; 
	//operaters are just these gi
	vector<string> Stabilizers;
	//the whole stabilizer group
	for(int n=5;n<=30;n++){
		for(int a=1;a<n/2;a++){
			for(int b=1;2*a+b<n;b++){
				output<<"n,a,b=  "<<n<<" , "<<a<<" , "<<b<<"  ->  "<<endl;
				for(int i=0;i<n;i++){
					operaters.push_back(getstabilizers(i, n, a, b));
					//get the gi		
				}
				Stabilizers=generate(operaters, n);
				//use gi to generate the whole stabilizer group
				r=log2(Stabilizers.size());
				//r is the number of the indenpedent generators, since N=2^r
				output<<"r="<<r<<"\n"<<endl;
				operaters.clear();
				Stabilizers.clear();
				r = 0;
			
			}
		
			
		
		
	
		}
	}
	output.close();
	return 0;
	
}


//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
