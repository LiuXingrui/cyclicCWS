// cyclicCWS.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<cstring>
#include<string>
#include<vector>
#include <fstream>

using namespace std;

ofstream Circuit("circuit.txt");
void qreg(int n,string q="q") {
	Circuit << "qreg "<<q<<"[" << n << "];" << endl;

}
void creg(int n,string c="c") {
	Circuit << "creg "<<c<<"[" << n << "];" << endl;

}

void X(int n, string q = "q") {
	Circuit << "x " << q << "[" << n << "];" << endl;

}

void Z(int n, string q = "q") {
	Circuit << "z " << q << "[" << n << "];" << endl;

}

void CNOT(int n1, int n2, string q1 = "q",string q2="a") {
	Circuit << "cx " << q1 << "[" << n1 << "],"<<q2<<"["<<n2<<"];" << endl;

}

void CZ(int n1, int n2, string q1 = "q", string q2 = "a") {
	Circuit << "cz " << q1 << "[" << n1 << "]," << q2 << "[" << n2 << "];" << endl;

}

void H(int n, string q = "q") {
	Circuit << "h " << q << "[" << n << "];" << endl;

}
void Measure( string a = "a", string c = "c",int n1=-1, int n2=-1) {
	if (n1 == -1 && n2 == -1) {
		Circuit << "measure " << a << "->"<<c << ";" << endl;
	}
	else if (n1 >= 0 && n2 >= 0) {
		Circuit << "measure " << a <<"["<<n1<< "]->" << c <<"["<<n2<< "];" << endl;

	}


}

int main(int argc, char* argv[])

{
	int const t = atoi(argv[1]);
	int const n = t * t + (t + 1) * (t + 1);
	vector<char> S1;


	//Construct S1=ZXII...IIXZ
	for (int i = 0; i < n; i++) {
		if (S1.size() == 0 || S1.size() == n - 1) {
			S1.push_back('Z');
		}
		else if (S1.size() == 1 || S1.size() == n - 2) {
			S1.push_back('X');
		}
		else {
			S1.push_back('I');

		}
	}

	//Construct other stabalizers;
	vector<vector<char>> stabilizers;
	vector<char> temp1,temp2;
	temp1 = S1;
	temp2 = S1;
	stabilizers.push_back(S1);
	for (int i = 1; i < n - 1; i++) {
		temp1[0] = temp2[n - 1];
		for (int j = 1; j < n; j++) {
			temp1[j] = temp2[j - 1];
		}
		temp2 = temp1;
		stabilizers.push_back(temp1);

	}

	//input circuit by openQASM

	
	
	Circuit << "OPENQASM 2.0;\ninclude \"qelib1.inc\";" << endl;
	qreg(n,"q");
	qreg(n - 1, "a");
	creg(n, "c");

	Circuit << "\n";


	for (int j = 0; j < n-1; j++) {
		for (int i = 0; i < n; i++) {
			if (stabilizers[j][i] == 'X') {
				H(i, "q");
				CNOT(i,j, "q","a");
				H(i,"q");
				Circuit << "\n";
			}
			else if (stabilizers[j][i] == 'Z') {
				CNOT(i, j, "q", "a");
				Circuit << "\n";
			}

			
		}
		
	}
	Measure("a", "c");

	Circuit.close();
	return 0;
}

