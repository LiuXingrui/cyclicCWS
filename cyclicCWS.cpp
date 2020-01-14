// cyclicCWS.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<cstring>
#include<string>
#include<vector>
#include <fstream>

using namespace std;


int main(int argc, char* argv[])

{
	int t = atoi(argv[1]);
	int n = t * t + (t + 1) * (t + 1);
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
	ofstream Circuit("circuit.txt");
	
	
	Circuit << "qreg q[" << n << "];" << endl;
	Circuit << "creg c[" << n-1 << "];\n" << endl;


	for (int j = 0; j < n-1; j++) {
		for (int i = 0; i < n; i++) {
			if (stabilizers[j][i] == 'X') {
				Circuit << "h q[" << i << "];" << endl;
				Circuit << "cx q[" << i << "],c[" << j << "];" << endl;
				Circuit << "h q[" << i << "];\n\n" ;
			}
			else if (stabilizers[j][i] == 'Z') {
				Circuit << "cx q[" << i << "],c[" << j << "];\n\n" ;
			}

			
		}
		Circuit << "barrier q\n\n" ;
	}
	Circuit.close();
	return 0;
}

