#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;
int population[10][4][6][57]; //[층][section][요일][시간]
string day[] = { "월", "화", "수", "목", "금", "토" };

void pop_mat(string inputString[2000], int a) {
	for (int i = 0; i < a - 1; i++) {
		//cout << inputString[i].substr(inputString[i].rfind(' ') + 1, inputString[i].rfind(',') - inputString[i].rfind(' ') - 1) << endl;
		population[1][1][find(day, day + 6, inputString[i].substr(8, 2)) - day][stoi(inputString[i].substr(inputString[i].find(' ') + 1, inputString[i].rfind(' ') - inputString[i].find(' ') - 1))] += stoi(inputString[i].substr(inputString[i].rfind(',') + 1));
		population[stoi(inputString[i].substr(4, 1))][stoi(inputString[i].substr(6, 1))][find(day, day + 6, inputString[i].substr(8, 2)) - day][stoi(inputString[i].substr(inputString[i].rfind(' ') + 1, inputString[i].rfind(',') - inputString[i].rfind(' ') - 1))] += stoi(inputString[i].substr(inputString[i].rfind(',') + 1));
	}
}

void print_mat() {
	for (int i = 1; i < 10; i++) {
		cout << i << "층" << endl;
		for (int j = 1; j < 4; j++) {
			cout << j << "section" << endl;
			for (int k = 0; k < 6; k++) {
				cout << day[k] << endl;
				for (int l = 0; l < 57; l++) {
					cout << population[i][j][k][l] << ' ';
				}
				cout << endl;
			}
			cout << endl;
		}
		cout << endl;
		cout << endl;
	}
}

struct Class {
	float x;
	float y;
};

struct Cross {
	float x;
	float y;
};

struct Elv {
	float x;
	float y;
	int population[6][57];
};

struct Stair {
	float x;
	float y;
};

int main() {
	int a = 0;
	string inputString[2000];
	string b;

	ifstream inFile("temp_.csv");

	while (!inFile.eof()) {
		getline(inFile, inputString[a]);
		a++;
	}

	pop_mat(inputString, a);
	//print_mat();
	
	inFile.close();

	ifstream inFile_2("data.csv");

	while(!inFile_2.eof()){
		getline(inFile_2, b);
		cout << b << endl;
	}
	Class C401 = { 168.00, 125.00};

	return 0;
}