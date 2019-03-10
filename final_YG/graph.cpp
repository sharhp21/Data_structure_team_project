#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>

using namespace std;
#define MAX_intersection 239
#define MAX_class 436
#define MAX_elevator 122
#define MAX_stair 48

int population[10][4][6][57]; //[��][section][����][�ð�] �����α� ������ marix
string day[] = { "��", "ȭ", "��", "��", "��", "��" };

//csv���� �޾ƿ� data ������ matrix
string intersection_tmp[MAX_intersection][7];
string class_tmp[MAX_class][7];
string elevator_tmp[MAX_elevator][7];
string stair_tmp[MAX_stair][7];

//3���� ���������� Ȥ�� 3���� ����� �̿��� path, dist ���� ���� -> result���� ���� ���� ��� �����Ұ���
vector<pair<float, float>> path, path2, path3, path4, path5, path6, path7, path8, path9, path_tmp1, path_tmp2, result_path;
float dist, dist2, dist3, dist4, dist5, dist6, dist7, dist8, dist9, result_dist;
//�� �̵� ����
vector<int> floor_st;

//�� ���� ������ ��� ��ȣ ����, ��ǥ ���� ���� ����
vector<string> intersection_node_B6;
vector<pair<float, float>> intersection_coordinate_B6;
vector<string> intersection_node_B5;
vector<pair<float, float>> intersection_coordinate_B5;
vector<string> intersection_node_B4;
vector<pair<float, float>> intersection_coordinate_B4;
vector<string> intersection_node_B3;
vector<pair<float, float>> intersection_coordinate_B3;
vector<string> intersection_node_B2;
vector<pair<float, float>> intersection_coordinate_B2;
vector<string> intersection_node_B1;
vector<pair<float, float>> intersection_coordinate_B1;
vector<string> intersection_node_1F;
vector<pair<float, float>> intersection_coordinate_1F;
vector<string> intersection_node_2F;
vector<pair<float, float>> intersection_coordinate_2F;
vector<string> intersection_node_3F;
vector<pair<float, float>> intersection_coordinate_3F;
vector<string> intersection_node_4F;
vector<pair<float, float>> intersection_coordinate_4F;
vector<string> intersection_node_5F;
vector<pair<float, float>> intersection_coordinate_5F;
vector<string> intersection_node_6F;
vector<pair<float, float>> intersection_coordinate_6F;
vector<string> intersection_node_7F;
vector<pair<float, float>> intersection_coordinate_7F;
vector<string> intersection_node_8F;
vector<pair<float, float>> intersection_coordinate_8F;
vector<string> intersection_node_9F;
vector<pair<float, float>> intersection_coordinate_9F;
vector<string> intersection_node_10F;
vector<pair<float, float>> intersection_coordinate_10F;
vector<string> intersection_node_11F;
vector<pair<float, float>> intersection_coordinate_11F;
vector<string> intersection_node_12F;
vector<pair<float, float>> intersection_coordinate_12F;
//������ �� ���� ����
vector<vector<string>> intersection_node_all(9);
vector<vector<pair<float, float>>> intersection_coordinate_all(9);

//�����α� matrix����� �Լ�
void pop_mat(string inputString[2000], int a) {
	for (int i = 0; i < a - 1; i++) {
		//cout << inputString[i].substr(inputString[i].rfind(' ') + 1, inputString[i].rfind(',') - inputString[i].rfind(' ') - 1) << endl;
		population[1][1][find(day, day + 6, inputString[i].substr(8, 2)) - day][stoi(inputString[i].substr(inputString[i].find(' ') + 1, inputString[i].rfind(' ') - inputString[i].find(' ') - 1))] += stoi(inputString[i].substr(inputString[i].rfind(',') + 1)) * 0.2;
		population[1][2][find(day, day + 6, inputString[i].substr(8, 2)) - day][stoi(inputString[i].substr(inputString[i].find(' ') + 1, inputString[i].rfind(' ') - inputString[i].find(' ') - 1))] += stoi(inputString[i].substr(inputString[i].rfind(',') + 1)) * 0.4;
		population[1][3][find(day, day + 6, inputString[i].substr(8, 2)) - day][stoi(inputString[i].substr(inputString[i].find(' ') + 1, inputString[i].rfind(' ') - inputString[i].find(' ') - 1))] += stoi(inputString[i].substr(inputString[i].rfind(',') + 1)) * 0.4;
		population[stoi(inputString[i].substr(4, 1))][stoi(inputString[i].substr(6, 1))][find(day, day + 6, inputString[i].substr(8, 2)) - day][stoi(inputString[i].substr(inputString[i].rfind(' ') + 1, inputString[i].rfind(',') - inputString[i].rfind(' ') - 1))] += stoi(inputString[i].substr(inputString[i].rfind(',') + 1));
	}
}
void print_mat() {
	for (int i = 1; i < 10; i++) {
		cout << i << "��" << endl;
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
//��¥ �ð� �Է� �޾Ƽ� return���ִ� �Լ�
int convert_day(string day) {
	if (day == "������") return 0;
	else if (day == "ȭ����") return 1;
	else if (day == "������") return 2;
	else if (day == "�����") return 3;
	else if (day == "�ݿ���") return 4;
	else if (day == "�����") return 5;
	else {
		cout << "error" << endl;
		exit(1);
	}
}
int convert_time(string time) {
	int time_tmp;
	time.erase(time.find(':'), 1);
	time_tmp = stoi(time);
	time_tmp = (((time_tmp / 100 * 60) + (time_tmp % 100)) - 526) / 15;
	if (time_tmp < 0 || time_tmp >= 57)
		time_tmp = 1;
	return time_tmp;
}
//csv data �������� �Լ�
void tmp_storage(string *inputString_a, string *inputString_b, string *inputString_c, string *inputString_d) {
	for (int i = 1; i < MAX_intersection + 1; i++) {
		for (int j = 0; j < 7; j++) {
			inputString_a[i].erase(0, inputString_a[i].find(',') + 1);
			intersection_tmp[i - 1][j] = inputString_a[i].substr(0, inputString_a[i].find(','));
			//cout << intersection_tmp[i - 1][j] << ' ';
		}
		//cout << endl;
	}
	for (int i = 1; i < MAX_class + 1; i++) {
		for (int j = 0; j < 7; j++) {
			inputString_b[i].erase(0, inputString_b[i].find(',') + 1);
			class_tmp[i - 1][j] = inputString_b[i].substr(0, inputString_b[i].find(','));
			//cout << class_tmp[i - 1][j] << ' ';
		}
		//cout << endl;
	}
	for (int i = 1; i < MAX_elevator + 1; i++) {
		for (int j = 0; j < 7; j++) {
			inputString_c[i].erase(0, inputString_c[i].find(',') + 1);
			elevator_tmp[i - 1][j] = inputString_c[i].substr(0, inputString_c[i].find(','));
			//cout << elevator_tmp[i - 1][j] << ' ';
		}
		//cout << endl;
	}
	for (int i = 1; i < MAX_stair + 1; i++) {
		for (int j = 0; j < 7; j++) {
			inputString_d[i].erase(0, inputString_d[i].find(',') + 1);
			stair_tmp[i - 1][j] = inputString_d[i].substr(0, inputString_d[i].find(','));
			//cout << stair_tmp[i - 1][j] << ' ';
		}
		//cout << endl;
	}
}
//������ ��� ������ �� �Լ�
void intersection_node_storage() {
	for (int i = 0; i < MAX_intersection; i++) {
		if (intersection_tmp[i][0].length() == 3) {
			if (intersection_tmp[i][0].substr(0, 1) == "1") {
				intersection_node_1F.push_back(intersection_tmp[i][0]);
				intersection_coordinate_1F.push_back(make_pair(stof(intersection_tmp[i][5]), stof(intersection_tmp[i][6])));
			}
			else if (intersection_tmp[i][0].substr(0, 1) == "2") {
				intersection_node_2F.push_back(intersection_tmp[i][0]);
				intersection_coordinate_2F.push_back(make_pair(stof(intersection_tmp[i][5]), stof(intersection_tmp[i][6])));
			}
			else if (intersection_tmp[i][0].substr(0, 1) == "3") {
				intersection_node_3F.push_back(intersection_tmp[i][0]);
				intersection_coordinate_3F.push_back(make_pair(stof(intersection_tmp[i][5]), stof(intersection_tmp[i][6])));
			}
			else if (intersection_tmp[i][0].substr(0, 1) == "4") {
				intersection_node_4F.push_back(intersection_tmp[i][0]);
				intersection_coordinate_4F.push_back(make_pair(stof(intersection_tmp[i][5]), stof(intersection_tmp[i][6])));
			}
			else if (intersection_tmp[i][0].substr(0, 1) == "5") {
				intersection_node_5F.push_back(intersection_tmp[i][0]);
				intersection_coordinate_5F.push_back(make_pair(stof(intersection_tmp[i][5]), stof(intersection_tmp[i][6])));
			}
			else if (intersection_tmp[i][0].substr(0, 1) == "6") {
				intersection_node_6F.push_back(intersection_tmp[i][0]);
				intersection_coordinate_6F.push_back(make_pair(stof(intersection_tmp[i][5]), stof(intersection_tmp[i][6])));
			}
			else if (intersection_tmp[i][0].substr(0, 1) == "7") {
				intersection_node_7F.push_back(intersection_tmp[i][0]);
				intersection_coordinate_7F.push_back(make_pair(stof(intersection_tmp[i][5]), stof(intersection_tmp[i][6])));
			}
			else if (intersection_tmp[i][0].substr(0, 1) == "8") {
				intersection_node_8F.push_back(intersection_tmp[i][0]);
				intersection_coordinate_8F.push_back(make_pair(stof(intersection_tmp[i][5]), stof(intersection_tmp[i][6])));
			}
			else if (intersection_tmp[i][0].substr(0, 1) == "9") {
				intersection_node_9F.push_back(intersection_tmp[i][0]);
				intersection_coordinate_9F.push_back(make_pair(stof(intersection_tmp[i][5]), stof(intersection_tmp[i][6])));
			}
		}
		else if (intersection_tmp[i][0].length() == 4) {
			if (intersection_tmp[i][0].substr(0, 2) == "B6") {
				intersection_node_B6.push_back(intersection_tmp[i][0]);
				intersection_coordinate_B6.push_back(make_pair(stof(intersection_tmp[i][5]), stof(intersection_tmp[i][6])));
			}
			else if (intersection_tmp[i][0].substr(0, 2) == "B5") {
				intersection_node_B5.push_back(intersection_tmp[i][0]);
				intersection_coordinate_B5.push_back(make_pair(stof(intersection_tmp[i][5]), stof(intersection_tmp[i][6])));
			}
			else if (intersection_tmp[i][0].substr(0, 2) == "B4") {
				intersection_node_B4.push_back(intersection_tmp[i][0]);
				intersection_coordinate_B4.push_back(make_pair(stof(intersection_tmp[i][5]), stof(intersection_tmp[i][6])));
			}
			else if (intersection_tmp[i][0].substr(0, 2) == "B3") {
				intersection_node_B3.push_back(intersection_tmp[i][0]);
				intersection_coordinate_B3.push_back(make_pair(stof(intersection_tmp[i][5]), stof(intersection_tmp[i][6])));
			}
			else if (intersection_tmp[i][0].substr(0, 2) == "B2") {
				intersection_node_B2.push_back(intersection_tmp[i][0]);
				intersection_coordinate_B2.push_back(make_pair(stof(intersection_tmp[i][5]), stof(intersection_tmp[i][6])));
			}
			else if (intersection_tmp[i][0].substr(0, 2) == "B1") {
				intersection_node_B1.push_back(intersection_tmp[i][0]);
				intersection_coordinate_B1.push_back(make_pair(stof(intersection_tmp[i][5]), stof(intersection_tmp[i][6])));
			}
			else if (intersection_tmp[i][0].substr(0, 2) == "10") {
				intersection_node_10F.push_back(intersection_tmp[i][0]);
				intersection_coordinate_10F.push_back(make_pair(stof(intersection_tmp[i][5]), stof(intersection_tmp[i][6])));
			}
			else if (intersection_tmp[i][0].substr(0, 2) == "11") {
				intersection_node_11F.push_back(intersection_tmp[i][0]);
				intersection_coordinate_11F.push_back(make_pair(stof(intersection_tmp[i][5]), stof(intersection_tmp[i][6])));
			}
			else if (intersection_tmp[i][0].substr(0, 2) == "12") {
				intersection_node_12F.push_back(intersection_tmp[i][0]);
				intersection_coordinate_12F.push_back(make_pair(stof(intersection_tmp[i][5]), stof(intersection_tmp[i][6])));
			}
		}
	}
	intersection_node_all[0] = intersection_node_1F;
	intersection_coordinate_all[0] = intersection_coordinate_1F;
	intersection_node_all[1] = intersection_node_2F;
	intersection_coordinate_all[1] = intersection_coordinate_2F;
	intersection_node_all[2] = intersection_node_3F;
	intersection_coordinate_all[2] = intersection_coordinate_3F;
	intersection_node_all[3] = intersection_node_4F;
	intersection_coordinate_all[3] = intersection_coordinate_4F;
	intersection_node_all[4] = intersection_node_5F;
	intersection_coordinate_all[4] = intersection_coordinate_5F;
	intersection_node_all[5] = intersection_node_6F;
	intersection_coordinate_all[5] = intersection_coordinate_6F;
	intersection_node_all[6] = intersection_node_7F;
	intersection_coordinate_all[6] = intersection_coordinate_7F;
	intersection_node_all[7] = intersection_node_8F;
	intersection_coordinate_all[7] = intersection_coordinate_8F;
	intersection_node_all[8] = intersection_node_9F;
	intersection_coordinate_all[8] = intersection_coordinate_9F;
}
//��� ������ ���� ���� �� ������ ��� vecctor�� �� ���ǽ� �߰��ϴ� �Լ�
float **intersection_dist_storage(string start, string finish, vector<string> node, vector<pair<float, float>> coordinate) {
	float **dist = new float *[node.size() + 2];
	for (int i = 0; i < node.size() + 2; i++) {
		dist[i] = new float[node.size() + 2];
	}

	bool check = false;
	if (start.size() == 3)
		if (start.at(0) == finish.at(0)) check = true;
	else
		if (start.substr(0, 2) == finish.substr(0, 2)) check = true;

	int tmp_start = 0;
	int tmp_finish = 0;
	int tmp = 0;

	for (int i = 0; i < MAX_class; i++) {
		if (start == class_tmp[i][0]) {
			tmp_start = i;
			break;
		}
	}
	
	for (int i = 0; i < MAX_class; i++) {
		if (finish == class_tmp[i][0]) {
			tmp_finish = i;
			break;
		}
	}

	for (int i = 0; i < MAX_intersection; i++) {
		if (start.size() == 3) {
			if (start.at(0) == intersection_tmp[i][0].at(0)) {
				tmp = i;
				break;
			}
		}
		else if(start.size() == 4) {
			if (start.substr(0, 2) == intersection_tmp[i][0].substr(0, 2) && intersection_tmp[i][0].size() == 4) {
				tmp = i;
				//cout << start.substr(0, 2) << ' ' << intersection_tmp[i][0] << ' ' << tmp << endl;
				break;
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int k = 1; k < 5; k++) {
			if (class_tmp[tmp_start][k] == node[i - 1]) {
				dist[0][i] = sqrt(pow(abs(stof(class_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(class_tmp[tmp_start][6]) - coordinate[i].second), 2));
				dist[i][0] = sqrt(pow(abs(stof(class_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(class_tmp[tmp_start][6]) - coordinate[i].second), 2));
			}
		}
		for (int m = 1; m < 5; m++) {
			if (class_tmp[tmp_finish][m] == node[i - 1]) {
				dist[node.size() + 1][i] = sqrt(pow(abs(stof(class_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(class_tmp[tmp_finish][6]) - coordinate[i].second), 2));
				dist[i][node.size() + 1] = sqrt(pow(abs(stof(class_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(class_tmp[tmp_finish][6]) - coordinate[i].second), 2));
			}
		}
	}

 	for (int i = 1; i < node.size() + 1; i++) {
		for (int j = 1; j < node.size() + 1; j++) {
			for (int k = 1; k < 5; k++) {
				if (intersection_tmp[tmp + i - 1][k] == node[j - 1])
					dist[i][j] = sqrt(pow(abs(coordinate[i].first - coordinate[j].first), 2) + pow(abs(coordinate[i].second - coordinate[j].second), 2));
			}
		}
	}

	for (int i = 0; i < node.size() + 2; i++) {
		for (int j = 0; j < node.size() + 2; j++) {
			if (dist[i][j] < 0) dist[i][j] = 0;
			//cout << dist[i][j] << ' ';
		}
		//cout << endl;
	}

	return dist;
}
//��� ������ �ٸ� ���� �� ������ ��� vector�� ���ǽǰ� 1���� ���������� �߰��ϴ� �Լ�
float **intersection_dist_storage_2(string start, string finish, vector<string> node, vector<pair<float, float>> coordinate) {
	float **dist = new float *[node.size() + 2];
	for (int i = 0; i < node.size() + 2; i++) {
		dist[i] = new float[node.size() + 2];
	}

	bool check = false;
	if (start.size() == 3)
		if (start.at(0) == finish.at(0)) check = true;
		else
			if (start.substr(0, 2) == finish.substr(0, 2)) check = true;

	int tmp_start = 0;
	int tmp_finish = 0;
	int tmp = 0;

	for (int i = 0; i < MAX_class; i++) {
		if (start == class_tmp[i][0]) {
			tmp_start = i;
			break;
		}
	}

	for (int i = 0; i < MAX_elevator; i++) {
		if (elevator_tmp[i][0].substr(2, 1) == "1" && elevator_tmp[i][0].substr(0, 1) == finish.substr(0, 1) && elevator_tmp[i][0].size() == 3) {
			tmp_finish = i;
			break;
		}
	}

	for (int i = 0; i < MAX_intersection; i++) {
		if (start.size() == 3) {
			if (start.at(0) == intersection_tmp[i][0].at(0)) {
				tmp = i;
				break;
			}
		}
		else if (start.size() == 4) {
			if (start.substr(0, 2) == intersection_tmp[i][0].substr(0, 2) && intersection_tmp[i][0].size() == 4) {
				tmp = i;
				//cout << start.substr(0, 2) << ' ' << intersection_tmp[i][0] << ' ' << tmp << endl;
				break;
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int k = 1; k < 5; k++) {
			if (class_tmp[tmp_start][k] == node[i - 1]) {
				dist[0][i] = sqrt(pow(abs(stof(class_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(class_tmp[tmp_start][6]) - coordinate[i].second), 2));
				dist[i][0] = sqrt(pow(abs(stof(class_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(class_tmp[tmp_start][6]) - coordinate[i].second), 2));
			}
		}
		for (int m = 1; m < 5; m++) {
			if (elevator_tmp[tmp_finish][m] == node[i - 1]) {
				dist[node.size() + 1][i] = sqrt(pow(abs(stof(elevator_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(elevator_tmp[tmp_finish][6]) - coordinate[i].second), 2));
				dist[i][node.size() + 1] = sqrt(pow(abs(stof(elevator_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(elevator_tmp[tmp_finish][6]) - coordinate[i].second), 2));
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int j = 1; j < node.size() + 1; j++) {
			for (int k = 1; k < 5; k++) {
				if (intersection_tmp[tmp + i - 1][k] == node[j - 1])
					dist[i][j] = sqrt(pow(abs(coordinate[i].first - coordinate[j].first), 2) + pow(abs(coordinate[i].second - coordinate[j].second), 2));
			}
		}
	}

	for (int i = 0; i < node.size() + 2; i++) {
		for (int j = 0; j < node.size() + 2; j++) {
			if (dist[i][j] < 0) dist[i][j] = 0;
			//cout << dist[i][j] << ' ';
		}
		//cout << endl;
	}

	return dist;
}
//��� ������ �ٸ� ���� �� ������ ��� vector�� ���ǽǰ� 2���� ���������� �߰��ϴ� �Լ�
float **intersection_dist_storage_3(string start, string finish, vector<string> node, vector<pair<float, float>> coordinate) {
	float **dist = new float *[node.size() + 2];
	for (int i = 0; i < node.size() + 2; i++) {
		dist[i] = new float[node.size() + 2];
	}

	bool check = false;
	if (start.size() == 3)
		if (start.at(0) == finish.at(0)) check = true;
		else
			if (start.substr(0, 2) == finish.substr(0, 2)) check = true;

	int tmp_start = 0;
	int tmp_finish = 0;
	int tmp = 0;

	for (int i = 0; i < MAX_class; i++) {
		if (start == class_tmp[i][0]) {
			tmp_start = i;
			break;
		}
	}


	for (int i = 0; i < MAX_elevator; i++) {
		if (elevator_tmp[i][0].substr(2, 1) == "3" && elevator_tmp[i][0].substr(0, 1) == finish.substr(0, 1) && elevator_tmp[i][0].size() == 3) {
			tmp_finish = i;
			break;
		}
	}

	for (int i = 0; i < MAX_intersection; i++) {
		if (start.size() == 3) {
			if (start.at(0) == intersection_tmp[i][0].at(0)) {
				tmp = i;
				break;
			}
		}
		else if (start.size() == 4) {
			if (start.substr(0, 2) == intersection_tmp[i][0].substr(0, 2) && intersection_tmp[i][0].size() == 4) {
				tmp = i;
				//cout << start.substr(0, 2) << ' ' << intersection_tmp[i][0] << ' ' << tmp << endl;
				break;
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int k = 1; k < 5; k++) {
			if (class_tmp[tmp_start][k] == node[i - 1]) {
				dist[0][i] = sqrt(pow(abs(stof(class_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(class_tmp[tmp_start][6]) - coordinate[i].second), 2));
				dist[i][0] = sqrt(pow(abs(stof(class_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(class_tmp[tmp_start][6]) - coordinate[i].second), 2));
			}
		}
		for (int m = 1; m < 5; m++) {
			if (elevator_tmp[tmp_finish][m] == node[i - 1]) {
				dist[node.size() + 1][i] = sqrt(pow(abs(stof(elevator_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(elevator_tmp[tmp_finish][6]) - coordinate[i].second), 2));
				dist[i][node.size() + 1] = sqrt(pow(abs(stof(elevator_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(elevator_tmp[tmp_finish][6]) - coordinate[i].second), 2));
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int j = 1; j < node.size() + 1; j++) {
			for (int k = 1; k < 5; k++) {
				if (intersection_tmp[tmp + i - 1][k] == node[j - 1])
					dist[i][j] = sqrt(pow(abs(coordinate[i].first - coordinate[j].first), 2) + pow(abs(coordinate[i].second - coordinate[j].second), 2));
			}
		}
	}

	for (int i = 0; i < node.size() + 2; i++) {
		for (int j = 0; j < node.size() + 2; j++) {
			if (dist[i][j] < 0) dist[i][j] = 0;
			//cout << dist[i][j] << ' ';
		}
		//cout << endl;
	}

	return dist;
}
//��� ������ �ٸ� ���� �� ������ ��� vector�� ���ǽǰ� 3���� ���������� �߰��ϴ� �Լ�
float **intersection_dist_storage_4(string start, string finish, vector<string> node, vector<pair<float, float>> coordinate) {
	float **dist = new float *[node.size() + 2];
	for (int i = 0; i < node.size() + 2; i++) {
		dist[i] = new float[node.size() + 2];
	}

	bool check = false;
	if (start.size() == 3)
		if (start.at(0) == finish.at(0)) check = true;
		else
			if (start.substr(0, 2) == finish.substr(0, 2)) check = true;

	int tmp_start = 0;
	int tmp_finish = 0;
	int tmp = 0;

	for (int i = 0; i < MAX_class; i++) {
		if (start == class_tmp[i][0]) {
			tmp_start = i;
			break;
		}
	}


	for (int i = 0; i < MAX_elevator; i++) {
		if (elevator_tmp[i][0].substr(2, 1) == "7" && elevator_tmp[i][0].substr(0, 1) == finish.substr(0, 1) && elevator_tmp[i][0].size() == 3) {
			tmp_finish = i;
			break;
		}
	}

	for (int i = 0; i < MAX_intersection; i++) {
		if (start.size() == 3) {
			if (start.at(0) == intersection_tmp[i][0].at(0)) {
				tmp = i;
				break;
			}
		}
		else if (start.size() == 4) {
			if (start.substr(0, 2) == intersection_tmp[i][0].substr(0, 2) && intersection_tmp[i][0].size() == 4) {
				tmp = i;
				//cout << start.substr(0, 2) << ' ' << intersection_tmp[i][0] << ' ' << tmp << endl;
				break;
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int k = 1; k < 5; k++) {
			if (class_tmp[tmp_start][k] == node[i - 1]) {
				dist[0][i] = sqrt(pow(abs(stof(class_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(class_tmp[tmp_start][6]) - coordinate[i].second), 2));
				dist[i][0] = sqrt(pow(abs(stof(class_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(class_tmp[tmp_start][6]) - coordinate[i].second), 2));
			}
		}
		for (int m = 1; m < 5; m++) {
			if (elevator_tmp[tmp_finish][m] == node[i - 1]) {
				dist[node.size() + 1][i] = sqrt(pow(abs(stof(elevator_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(elevator_tmp[tmp_finish][6]) - coordinate[i].second), 2));
				dist[i][node.size() + 1] = sqrt(pow(abs(stof(elevator_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(elevator_tmp[tmp_finish][6]) - coordinate[i].second), 2));
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int j = 1; j < node.size() + 1; j++) {
			for (int k = 1; k < 5; k++) {
				if (intersection_tmp[tmp + i - 1][k] == node[j - 1])
					dist[i][j] = sqrt(pow(abs(coordinate[i].first - coordinate[j].first), 2) + pow(abs(coordinate[i].second - coordinate[j].second), 2));
			}
		}
	}

	for (int i = 0; i < node.size() + 2; i++) {
		for (int j = 0; j < node.size() + 2; j++) {
			if (dist[i][j] < 0) dist[i][j] = 0;
			//cout << dist[i][j] << ' ';
		}
		//cout << endl;
	}

	return dist;
}
//��� ������ �ٸ� ���� �� ������ ��� vector�� ���ǽǰ� 1���� ��� �߰��ϴ� �Լ�
float **intersection_dist_storage_5(string start, string finish, vector<string> node, vector<pair<float, float>> coordinate) {
	float **dist = new float *[node.size() + 2];
	for (int i = 0; i < node.size() + 2; i++) {
		dist[i] = new float[node.size() + 2];
	}

	bool check = false;
	if (start.size() == 3)
		if (start.at(0) == finish.at(0)) check = true;
		else
			if (start.substr(0, 2) == finish.substr(0, 2)) check = true;

	int tmp_start = 0;
	int tmp_finish = 0;
	int tmp = 0;

	for (int i = 0; i < MAX_class; i++) {
		if (start == class_tmp[i][0]) {
			tmp_start = i;
			break;
		}
	}


	for (int i = 0; i < MAX_stair; i++) {
		if (stair_tmp[i][0].substr(2, 1) == "1" && stair_tmp[i][0].substr(0, 1) == finish.substr(0, 1) && stair_tmp[i][0].size() == 3) {
			tmp_finish = i;
			break;
		}
	}

	for (int i = 0; i < MAX_intersection; i++) {
		if (start.size() == 3) {
			if (start.at(0) == intersection_tmp[i][0].at(0)) {
				tmp = i;
				break;
			}
		}
		else if (start.size() == 4) {
			if (start.substr(0, 2) == intersection_tmp[i][0].substr(0, 2) && intersection_tmp[i][0].size() == 4) {
				tmp = i;
				//cout << start.substr(0, 2) << ' ' << intersection_tmp[i][0] << ' ' << tmp << endl;
				break;
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int k = 1; k < 5; k++) {
			if (class_tmp[tmp_start][k] == node[i - 1]) {
				dist[0][i] = sqrt(pow(abs(stof(class_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(class_tmp[tmp_start][6]) - coordinate[i].second), 2));
				dist[i][0] = sqrt(pow(abs(stof(class_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(class_tmp[tmp_start][6]) - coordinate[i].second), 2));
			}
		}
		for (int m = 1; m < 5; m++) {
			if (stair_tmp[tmp_finish][m] == node[i - 1]) {
				dist[node.size() + 1][i] = sqrt(pow(abs(stof(stair_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(stair_tmp[tmp_finish][6]) - coordinate[i].second), 2));
				dist[i][node.size() + 1] = sqrt(pow(abs(stof(stair_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(stair_tmp[tmp_finish][6]) - coordinate[i].second), 2));
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int j = 1; j < node.size() + 1; j++) {
			for (int k = 1; k < 5; k++) {
				if (intersection_tmp[tmp + i - 1][k] == node[j - 1])
					dist[i][j] = sqrt(pow(abs(coordinate[i].first - coordinate[j].first), 2) + pow(abs(coordinate[i].second - coordinate[j].second), 2));
			}
		}
	}

	for (int i = 0; i < node.size() + 2; i++) {
		for (int j = 0; j < node.size() + 2; j++) {
			if (dist[i][j] < 0) dist[i][j] = 0;
			//cout << dist[i][j] << ' ';
		}
		//cout << endl;
	}

	return dist;
}
//��� ������ �ٸ� ���� �� ������ ��� vector�� ���ǽǰ� 2���� ��� �߰��ϴ� �Լ�
float **intersection_dist_storage_6(string start, string finish, vector<string> node, vector<pair<float, float>> coordinate) {
	float **dist = new float *[node.size() + 2];
	for (int i = 0; i < node.size() + 2; i++) {
		dist[i] = new float[node.size() + 2];
	}

	bool check = false;
	if (start.size() == 3)
		if (start.at(0) == finish.at(0)) check = true;
		else
			if (start.substr(0, 2) == finish.substr(0, 2)) check = true;

	int tmp_start = 0;
	int tmp_finish = 0;
	int tmp = 0;

	for (int i = 0; i < MAX_class; i++) {
		if (start == class_tmp[i][0]) {
			tmp_start = i;
			break;
		}
	}


	for (int i = 0; i < MAX_stair; i++) {
		if (stair_tmp[i][0].substr(2, 1) == "2" && stair_tmp[i][0].substr(0, 1) == finish.substr(0, 1) && stair_tmp[i][0].size() == 3) {
			tmp_finish = i;
			break;
		}
	}

	for (int i = 0; i < MAX_intersection; i++) {
		if (start.size() == 3) {
			if (start.at(0) == intersection_tmp[i][0].at(0)) {
				tmp = i;
				break;
			}
		}
		else if (start.size() == 4) {
			if (start.substr(0, 2) == intersection_tmp[i][0].substr(0, 2) && intersection_tmp[i][0].size() == 4) {
				tmp = i;
				//cout << start.substr(0, 2) << ' ' << intersection_tmp[i][0] << ' ' << tmp << endl;
				break;
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int k = 1; k < 5; k++) {
			if (class_tmp[tmp_start][k] == node[i - 1]) {
				dist[0][i] = sqrt(pow(abs(stof(class_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(class_tmp[tmp_start][6]) - coordinate[i].second), 2));
				dist[i][0] = sqrt(pow(abs(stof(class_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(class_tmp[tmp_start][6]) - coordinate[i].second), 2));
			}
		}
		for (int m = 1; m < 5; m++) {
			if (stair_tmp[tmp_finish][m] == node[i - 1]) {
				dist[node.size() + 1][i] = sqrt(pow(abs(stof(stair_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(stair_tmp[tmp_finish][6]) - coordinate[i].second), 2));
				dist[i][node.size() + 1] = sqrt(pow(abs(stof(stair_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(stair_tmp[tmp_finish][6]) - coordinate[i].second), 2));
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int j = 1; j < node.size() + 1; j++) {
			for (int k = 1; k < 5; k++) {
				if (intersection_tmp[tmp + i - 1][k] == node[j - 1])
					dist[i][j] = sqrt(pow(abs(coordinate[i].first - coordinate[j].first), 2) + pow(abs(coordinate[i].second - coordinate[j].second), 2));
			}
		}
	}

	for (int i = 0; i < node.size() + 2; i++) {
		for (int j = 0; j < node.size() + 2; j++) {
			if (dist[i][j] < 0) dist[i][j] = 0;
			//cout << dist[i][j] << ' ';
		}
		//cout << endl;
	}

	return dist;
}
//��� ������ �ٸ� ���� �� ������ ��� vector�� ���ǽǰ� 3���� ���������� �߰��ϴ� �Լ�
float **intersection_dist_storage_7(string start, string finish, vector<string> node, vector<pair<float, float>> coordinate) {
	float **dist = new float *[node.size() + 2];
	for (int i = 0; i < node.size() + 2; i++) {
		dist[i] = new float[node.size() + 2];
	}

	bool check = false;
	if (start.size() == 3)
		if (start.at(0) == finish.at(0)) check = true;
		else
			if (start.substr(0, 2) == finish.substr(0, 2)) check = true;

	int tmp_start = 0;
	int tmp_finish = 0;
	int tmp = 0;

	for (int i = 0; i < MAX_class; i++) {
		if (start == class_tmp[i][0]) {
			tmp_start = i;
			break;
		}
	}


	for (int i = 0; i < MAX_stair; i++) {
		if (stair_tmp[i][0].substr(2, 1) == "5" && stair_tmp[i][0].substr(0, 1) == finish.substr(0, 1) && stair_tmp[i][0].size() == 3) {
			tmp_finish = i;
			break;
		}
	}

	for (int i = 0; i < MAX_intersection; i++) {
		if (start.size() == 3) {
			if (start.at(0) == intersection_tmp[i][0].at(0)) {
				tmp = i;
				break;
			}
		}
		else if (start.size() == 4) {
			if (start.substr(0, 2) == intersection_tmp[i][0].substr(0, 2) && intersection_tmp[i][0].size() == 4) {
				tmp = i;
				//cout << start.substr(0, 2) << ' ' << intersection_tmp[i][0] << ' ' << tmp << endl;
				break;
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int k = 1; k < 5; k++) {
			if (class_tmp[tmp_start][k] == node[i - 1]) {
				dist[0][i] = sqrt(pow(abs(stof(class_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(class_tmp[tmp_start][6]) - coordinate[i].second), 2));
				dist[i][0] = sqrt(pow(abs(stof(class_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(class_tmp[tmp_start][6]) - coordinate[i].second), 2));
			}
		}
		for (int m = 1; m < 5; m++) {
			if (stair_tmp[tmp_finish][m] == node[i - 1]) {
				dist[node.size() + 1][i] = sqrt(pow(abs(stof(stair_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(stair_tmp[tmp_finish][6]) - coordinate[i].second), 2));
				dist[i][node.size() + 1] = sqrt(pow(abs(stof(stair_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(stair_tmp[tmp_finish][6]) - coordinate[i].second), 2));
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int j = 1; j < node.size() + 1; j++) {
			for (int k = 1; k < 5; k++) {
				if (intersection_tmp[tmp + i - 1][k] == node[j - 1])
					dist[i][j] = sqrt(pow(abs(coordinate[i].first - coordinate[j].first), 2) + pow(abs(coordinate[i].second - coordinate[j].second), 2));
			}
		}
	}

	for (int i = 0; i < node.size() + 2; i++) {
		for (int j = 0; j < node.size() + 2; j++) {
			if (dist[i][j] < 0) dist[i][j] = 0;
			//cout << dist[i][j] << ' ';
		}
		//cout << endl;
	}

	return dist;
}
//������ ��� vector�� 1���� ���������� -> 1���� ��� �߰��ϴ� �Լ�
float **intersection_dist_storage_8(string start, string finish, vector<string> node, vector<pair<float, float>> coordinate) {
	float **dist = new float *[node.size() + 2];
	for (int i = 0; i < node.size() + 2; i++) {
		dist[i] = new float[node.size() + 2];
	}
	string str;

	bool check = false;
	if (start.size() == 3)
		if (start.at(0) == finish.at(0)) check = true;
		else
			if (start.substr(0, 2) == finish.substr(0, 2)) check = true;

	int tmp_start = 0;
	int tmp_finish = 0;
	int tmp = 0;

	for (int i = 0; i < MAX_elevator; i++) {
		if (elevator_tmp[i][0].substr(2, 1) == "1" && elevator_tmp[i][0].substr(0, 1) == finish.substr(0, 1) && elevator_tmp[i][0].size() == 3) {
			tmp_start = i;
			break;
		}
	}

	for (int i = 0; i < MAX_stair; i++) {
		if (stair_tmp[i][0].substr(2, 1) == "1" && stair_tmp[i][0].substr(0, 1) == finish.substr(0, 1) && stair_tmp[i][0].size() == 3) {
			tmp_finish = i;
			break;
		}
	}

	for (int i = 0; i < MAX_intersection; i++) {
		if (start.size() == 3) {
			if (start.at(0) == intersection_tmp[i][0].at(0)) {
				tmp = i;
				break;
			}
		}
		else if (start.size() == 4) {
			if (start.substr(0, 2) == intersection_tmp[i][0].substr(0, 2) && intersection_tmp[i][0].size() == 4) {
				tmp = i;
				//cout << start.substr(0, 2) << ' ' << intersection_tmp[i][0] << ' ' << tmp << endl;
				break;
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int k = 1; k < 5; k++) {
			if (elevator_tmp[tmp_start][k] == node[i - 1]) {
				dist[0][i] = sqrt(pow(abs(stof(elevator_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(elevator_tmp[tmp_start][6]) - coordinate[i].second), 2));
				dist[i][0] = sqrt(pow(abs(stof(elevator_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(elevator_tmp[tmp_start][6]) - coordinate[i].second), 2));
			}
		}
		for (int m = 1; m < 5; m++) {
			if (stair_tmp[tmp_finish][m] == node[i - 1]) {
				dist[node.size() + 1][i] = sqrt(pow(abs(stof(stair_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(stair_tmp[tmp_finish][6]) - coordinate[i].second), 2));
				dist[i][node.size() + 1] = sqrt(pow(abs(stof(stair_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(stair_tmp[tmp_finish][6]) - coordinate[i].second), 2));
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int j = 1; j < node.size() + 1; j++) {
			for (int k = 1; k < 5; k++) {
				if (intersection_tmp[tmp + i - 1][k] == node[j - 1])
					dist[i][j] = sqrt(pow(abs(coordinate[i].first - coordinate[j].first), 2) + pow(abs(coordinate[i].second - coordinate[j].second), 2));
			}
		}
	}

	for (int i = 0; i < node.size() + 2; i++) {
		for (int j = 0; j < node.size() + 2; j++) {
			if (dist[i][j] < 0) dist[i][j] = 0;
			//cout << dist[i][j] << ' ';
		}
		//cout << endl;
	}

	return dist;
}
float **intersection_dist_storage_9(string start, string finish, vector<string> node, vector<pair<float, float>> coordinate) {
	float **dist = new float *[node.size() + 2];
	for (int i = 0; i < node.size() + 2; i++) {
		dist[i] = new float[node.size() + 2];
	}
	string str;

	bool check = false;
	if (start.size() == 3)
		if (start.at(0) == finish.at(0)) check = true;
		else
			if (start.substr(0, 2) == finish.substr(0, 2)) check = true;

	int tmp_start = 0;
	int tmp_finish = 0;
	int tmp = 0;

	for (int i = 0; i < MAX_elevator; i++) {
		if (elevator_tmp[i][0].substr(2, 1) == "1" && elevator_tmp[i][0].substr(0, 1) == finish.substr(0, 1) && elevator_tmp[i][0].size() == 3) {
			tmp_start = i;
			break;
		}
	}

	for (int i = 0; i < MAX_stair; i++) {
		if (stair_tmp[i][0].substr(2, 1) == "2" && stair_tmp[i][0].substr(0, 1) == finish.substr(0, 1) && stair_tmp[i][0].size() == 3) {
			tmp_finish = i;
			break;
		}
	}

	for (int i = 0; i < MAX_intersection; i++) {
		if (start.size() == 3) {
			if (start.at(0) == intersection_tmp[i][0].at(0)) {
				tmp = i;
				break;
			}
		}
		else if (start.size() == 4) {
			if (start.substr(0, 2) == intersection_tmp[i][0].substr(0, 2) && intersection_tmp[i][0].size() == 4) {
				tmp = i;
				//cout << start.substr(0, 2) << ' ' << intersection_tmp[i][0] << ' ' << tmp << endl;
				break;
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int k = 1; k < 5; k++) {
			if (elevator_tmp[tmp_start][k] == node[i - 1]) {
				dist[0][i] = sqrt(pow(abs(stof(elevator_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(elevator_tmp[tmp_start][6]) - coordinate[i].second), 2));
				dist[i][0] = sqrt(pow(abs(stof(elevator_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(elevator_tmp[tmp_start][6]) - coordinate[i].second), 2));
			}
		}
		for (int m = 1; m < 5; m++) {
			if (stair_tmp[tmp_finish][m] == node[i - 1]) {
				dist[node.size() + 1][i] = sqrt(pow(abs(stof(stair_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(stair_tmp[tmp_finish][6]) - coordinate[i].second), 2));
				dist[i][node.size() + 1] = sqrt(pow(abs(stof(stair_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(stair_tmp[tmp_finish][6]) - coordinate[i].second), 2));
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int j = 1; j < node.size() + 1; j++) {
			for (int k = 1; k < 5; k++) {
				if (intersection_tmp[tmp + i - 1][k] == node[j - 1])
					dist[i][j] = sqrt(pow(abs(coordinate[i].first - coordinate[j].first), 2) + pow(abs(coordinate[i].second - coordinate[j].second), 2));
			}
		}
	}

	for (int i = 0; i < node.size() + 2; i++) {
		for (int j = 0; j < node.size() + 2; j++) {
			if (dist[i][j] < 0) dist[i][j] = 0;
			//cout << dist[i][j] << ' ';
		}
		//cout << endl;
	}

	return dist;
}
float **intersection_dist_storage_10(string start, string finish, vector<string> node, vector<pair<float, float>> coordinate) {
	float **dist = new float *[node.size() + 2];
	for (int i = 0; i < node.size() + 2; i++) {
		dist[i] = new float[node.size() + 2];
	}
	string str;

	bool check = false;
	if (start.size() == 3)
		if (start.at(0) == finish.at(0)) check = true;
		else
			if (start.substr(0, 2) == finish.substr(0, 2)) check = true;

	int tmp_start = 0;
	int tmp_finish = 0;
	int tmp = 0;

	for (int i = 0; i < MAX_elevator; i++) {
		if (elevator_tmp[i][0].substr(2, 1) == "1" && elevator_tmp[i][0].substr(0, 1) == finish.substr(0, 1) && elevator_tmp[i][0].size() == 3) {
			tmp_start = i;
			break;
		}
	}

	for (int i = 0; i < MAX_stair; i++) {
		if (stair_tmp[i][0].substr(2, 1) == "5" && stair_tmp[i][0].substr(0, 1) == finish.substr(0, 1) && stair_tmp[i][0].size() == 3) {
			tmp_finish = i;
			break;
		}
	}

	for (int i = 0; i < MAX_intersection; i++) {
		if (start.size() == 3) {
			if (start.at(0) == intersection_tmp[i][0].at(0)) {
				tmp = i;
				break;
			}
		}
		else if (start.size() == 4) {
			if (start.substr(0, 2) == intersection_tmp[i][0].substr(0, 2) && intersection_tmp[i][0].size() == 4) {
				tmp = i;
				//cout << start.substr(0, 2) << ' ' << intersection_tmp[i][0] << ' ' << tmp << endl;
				break;
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int k = 1; k < 5; k++) {
			if (elevator_tmp[tmp_start][k] == node[i - 1]) {
				dist[0][i] = sqrt(pow(abs(stof(elevator_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(elevator_tmp[tmp_start][6]) - coordinate[i].second), 2));
				dist[i][0] = sqrt(pow(abs(stof(elevator_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(elevator_tmp[tmp_start][6]) - coordinate[i].second), 2));
			}
		}
		for (int m = 1; m < 5; m++) {
			if (stair_tmp[tmp_finish][m] == node[i - 1]) {
				dist[node.size() + 1][i] = sqrt(pow(abs(stof(stair_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(stair_tmp[tmp_finish][6]) - coordinate[i].second), 2));
				dist[i][node.size() + 1] = sqrt(pow(abs(stof(stair_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(stair_tmp[tmp_finish][6]) - coordinate[i].second), 2));
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int j = 1; j < node.size() + 1; j++) {
			for (int k = 1; k < 5; k++) {
				if (intersection_tmp[tmp + i - 1][k] == node[j - 1])
					dist[i][j] = sqrt(pow(abs(coordinate[i].first - coordinate[j].first), 2) + pow(abs(coordinate[i].second - coordinate[j].second), 2));
			}
		}
	}

	for (int i = 0; i < node.size() + 2; i++) {
		for (int j = 0; j < node.size() + 2; j++) {
			if (dist[i][j] < 0) dist[i][j] = 0;
			//cout << dist[i][j] << ' ';
		}
		//cout << endl;
	}

	return dist;
}
float **intersection_dist_storage_11(string start, string finish, vector<string> node, vector<pair<float, float>> coordinate) {
	float **dist = new float *[node.size() + 2];
	for (int i = 0; i < node.size() + 2; i++) {
		dist[i] = new float[node.size() + 2];
	}
	string str;

	bool check = false;
	if (start.size() == 3)
		if (start.at(0) == finish.at(0)) check = true;
		else
			if (start.substr(0, 2) == finish.substr(0, 2)) check = true;

	int tmp_start = 0;
	int tmp_finish = 0;
	int tmp = 0;

	for (int i = 0; i < MAX_elevator; i++) {
		if (elevator_tmp[i][0].substr(2, 1) == "3" && elevator_tmp[i][0].substr(0, 1) == finish.substr(0, 1) && elevator_tmp[i][0].size() == 3) {
			tmp_start = i;
			break;
		}
	}

	for (int i = 0; i < MAX_stair; i++) {
		if (stair_tmp[i][0].substr(2, 1) == "1" && stair_tmp[i][0].substr(0, 1) == finish.substr(0, 1) && stair_tmp[i][0].size() == 3) {
			tmp_finish = i;
			break;
		}
	}

	for (int i = 0; i < MAX_intersection; i++) {
		if (start.size() == 3) {
			if (start.at(0) == intersection_tmp[i][0].at(0)) {
				tmp = i;
				break;
			}
		}
		else if (start.size() == 4) {
			if (start.substr(0, 2) == intersection_tmp[i][0].substr(0, 2) && intersection_tmp[i][0].size() == 4) {
				tmp = i;
				//cout << start.substr(0, 2) << ' ' << intersection_tmp[i][0] << ' ' << tmp << endl;
				break;
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int k = 1; k < 5; k++) {
			if (elevator_tmp[tmp_start][k] == node[i - 1]) {
				dist[0][i] = sqrt(pow(abs(stof(elevator_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(elevator_tmp[tmp_start][6]) - coordinate[i].second), 2));
				dist[i][0] = sqrt(pow(abs(stof(elevator_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(elevator_tmp[tmp_start][6]) - coordinate[i].second), 2));
			}
		}
		for (int m = 1; m < 5; m++) {
			if (stair_tmp[tmp_finish][m] == node[i - 1]) {
				dist[node.size() + 1][i] = sqrt(pow(abs(stof(stair_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(stair_tmp[tmp_finish][6]) - coordinate[i].second), 2));
				dist[i][node.size() + 1] = sqrt(pow(abs(stof(stair_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(stair_tmp[tmp_finish][6]) - coordinate[i].second), 2));
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int j = 1; j < node.size() + 1; j++) {
			for (int k = 1; k < 5; k++) {
				if (intersection_tmp[tmp + i - 1][k] == node[j - 1])
					dist[i][j] = sqrt(pow(abs(coordinate[i].first - coordinate[j].first), 2) + pow(abs(coordinate[i].second - coordinate[j].second), 2));
			}
		}
	}

	for (int i = 0; i < node.size() + 2; i++) {
		for (int j = 0; j < node.size() + 2; j++) {
			if (dist[i][j] < 0) dist[i][j] = 0;
			//cout << dist[i][j] << ' ';
		}
		//cout << endl;
	}

	return dist;
}
float **intersection_dist_storage_12(string start, string finish, vector<string> node, vector<pair<float, float>> coordinate) {
	float **dist = new float *[node.size() + 2];
	for (int i = 0; i < node.size() + 2; i++) {
		dist[i] = new float[node.size() + 2];
	}
	string str;

	bool check = false;
	if (start.size() == 3)
		if (start.at(0) == finish.at(0)) check = true;
		else
			if (start.substr(0, 2) == finish.substr(0, 2)) check = true;

	int tmp_start = 0;
	int tmp_finish = 0;
	int tmp = 0;

	for (int i = 0; i < MAX_elevator; i++) {
		if (elevator_tmp[i][0].substr(2, 1) == "3" && elevator_tmp[i][0].substr(0, 1) == finish.substr(0, 1) && elevator_tmp[i][0].size() == 3) {
			tmp_start = i;
			break;
		}
	}

	for (int i = 0; i < MAX_stair; i++) {
		if (stair_tmp[i][0].substr(2, 1) == "2" && stair_tmp[i][0].substr(0, 1) == finish.substr(0, 1) && stair_tmp[i][0].size() == 3) {
			tmp_finish = i;
			break;
		}
	}

	for (int i = 0; i < MAX_intersection; i++) {
		if (start.size() == 3) {
			if (start.at(0) == intersection_tmp[i][0].at(0)) {
				tmp = i;
				break;
			}
		}
		else if (start.size() == 4) {
			if (start.substr(0, 2) == intersection_tmp[i][0].substr(0, 2) && intersection_tmp[i][0].size() == 4) {
				tmp = i;
				//cout << start.substr(0, 2) << ' ' << intersection_tmp[i][0] << ' ' << tmp << endl;
				break;
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int k = 1; k < 5; k++) {
			if (elevator_tmp[tmp_start][k] == node[i - 1]) {
				dist[0][i] = sqrt(pow(abs(stof(elevator_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(elevator_tmp[tmp_start][6]) - coordinate[i].second), 2));
				dist[i][0] = sqrt(pow(abs(stof(elevator_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(elevator_tmp[tmp_start][6]) - coordinate[i].second), 2));
			}
		}
		for (int m = 1; m < 5; m++) {
			if (stair_tmp[tmp_finish][m] == node[i - 1]) {
				dist[node.size() + 1][i] = sqrt(pow(abs(stof(stair_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(stair_tmp[tmp_finish][6]) - coordinate[i].second), 2));
				dist[i][node.size() + 1] = sqrt(pow(abs(stof(stair_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(stair_tmp[tmp_finish][6]) - coordinate[i].second), 2));
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int j = 1; j < node.size() + 1; j++) {
			for (int k = 1; k < 5; k++) {
				if (intersection_tmp[tmp + i - 1][k] == node[j - 1])
					dist[i][j] = sqrt(pow(abs(coordinate[i].first - coordinate[j].first), 2) + pow(abs(coordinate[i].second - coordinate[j].second), 2));
			}
		}
	}

	for (int i = 0; i < node.size() + 2; i++) {
		for (int j = 0; j < node.size() + 2; j++) {
			if (dist[i][j] < 0) dist[i][j] = 0;
			//cout << dist[i][j] << ' ';
		}
		//cout << endl;
	}

	return dist;
}
float **intersection_dist_storage_13(string start, string finish, vector<string> node, vector<pair<float, float>> coordinate) {
	float **dist = new float *[node.size() + 2];
	for (int i = 0; i < node.size() + 2; i++) {
		dist[i] = new float[node.size() + 2];
	}
	string str;

	bool check = false;
	if (start.size() == 3)
		if (start.at(0) == finish.at(0)) check = true;
		else
			if (start.substr(0, 2) == finish.substr(0, 2)) check = true;

	int tmp_start = 0;
	int tmp_finish = 0;
	int tmp = 0;

	for (int i = 0; i < MAX_elevator; i++) {
		if (elevator_tmp[i][0].substr(2, 1) == "3" && elevator_tmp[i][0].substr(0, 1) == finish.substr(0, 1) && elevator_tmp[i][0].size() == 3) {
			tmp_start = i;
			break;
		}
	}

	for (int i = 0; i < MAX_stair; i++) {
		if (stair_tmp[i][0].substr(2, 1) == "5" && stair_tmp[i][0].substr(0, 1) == finish.substr(0, 1) && stair_tmp[i][0].size() == 3) {
			tmp_finish = i;
			break;
		}
	}

	for (int i = 0; i < MAX_intersection; i++) {
		if (start.size() == 3) {
			if (start.at(0) == intersection_tmp[i][0].at(0)) {
				tmp = i;
				break;
			}
		}
		else if (start.size() == 4) {
			if (start.substr(0, 2) == intersection_tmp[i][0].substr(0, 2) && intersection_tmp[i][0].size() == 4) {
				tmp = i;
				//cout << start.substr(0, 2) << ' ' << intersection_tmp[i][0] << ' ' << tmp << endl;
				break;
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int k = 1; k < 5; k++) {
			if (elevator_tmp[tmp_start][k] == node[i - 1]) {
				dist[0][i] = sqrt(pow(abs(stof(elevator_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(elevator_tmp[tmp_start][6]) - coordinate[i].second), 2));
				dist[i][0] = sqrt(pow(abs(stof(elevator_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(elevator_tmp[tmp_start][6]) - coordinate[i].second), 2));
			}
		}
		for (int m = 1; m < 5; m++) {
			if (stair_tmp[tmp_finish][m] == node[i - 1]) {
				dist[node.size() + 1][i] = sqrt(pow(abs(stof(stair_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(stair_tmp[tmp_finish][6]) - coordinate[i].second), 2));
				dist[i][node.size() + 1] = sqrt(pow(abs(stof(stair_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(stair_tmp[tmp_finish][6]) - coordinate[i].second), 2));
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int j = 1; j < node.size() + 1; j++) {
			for (int k = 1; k < 5; k++) {
				if (intersection_tmp[tmp + i - 1][k] == node[j - 1])
					dist[i][j] = sqrt(pow(abs(coordinate[i].first - coordinate[j].first), 2) + pow(abs(coordinate[i].second - coordinate[j].second), 2));
			}
		}
	}

	for (int i = 0; i < node.size() + 2; i++) {
		for (int j = 0; j < node.size() + 2; j++) {
			if (dist[i][j] < 0) dist[i][j] = 0;
			//cout << dist[i][j] << ' ';
		}
		//cout << endl;
	}

	return dist;
}
float **intersection_dist_storage_14(string start, string finish, vector<string> node, vector<pair<float, float>> coordinate) {
	float **dist = new float *[node.size() + 2];
	for (int i = 0; i < node.size() + 2; i++) {
		dist[i] = new float[node.size() + 2];
	}
	string str;

	bool check = false;
	if (start.size() == 3)
		if (start.at(0) == finish.at(0)) check = true;
		else
			if (start.substr(0, 2) == finish.substr(0, 2)) check = true;

	int tmp_start = 0;
	int tmp_finish = 0;
	int tmp = 0;

	for (int i = 0; i < MAX_elevator; i++) {
		if (elevator_tmp[i][0].substr(2, 1) == "7" && elevator_tmp[i][0].substr(0, 1) == finish.substr(0, 1) && elevator_tmp[i][0].size() == 3) {
			tmp_start = i;
			break;
		}
	}

	for (int i = 0; i < MAX_stair; i++) {
		if (stair_tmp[i][0].substr(2, 1) == "1" && stair_tmp[i][0].substr(0, 1) == finish.substr(0, 1) && stair_tmp[i][0].size() == 3) {
			tmp_finish = i;
			break;
		}
	}

	for (int i = 0; i < MAX_intersection; i++) {
		if (start.size() == 3) {
			if (start.at(0) == intersection_tmp[i][0].at(0)) {
				tmp = i;
				break;
			}
		}
		else if (start.size() == 4) {
			if (start.substr(0, 2) == intersection_tmp[i][0].substr(0, 2) && intersection_tmp[i][0].size() == 4) {
				tmp = i;
				//cout << start.substr(0, 2) << ' ' << intersection_tmp[i][0] << ' ' << tmp << endl;
				break;
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int k = 1; k < 5; k++) {
			if (elevator_tmp[tmp_start][k] == node[i - 1]) {
				dist[0][i] = sqrt(pow(abs(stof(elevator_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(elevator_tmp[tmp_start][6]) - coordinate[i].second), 2));
				dist[i][0] = sqrt(pow(abs(stof(elevator_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(elevator_tmp[tmp_start][6]) - coordinate[i].second), 2));
			}
		}
		for (int m = 1; m < 5; m++) {
			if (stair_tmp[tmp_finish][m] == node[i - 1]) {
				dist[node.size() + 1][i] = sqrt(pow(abs(stof(stair_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(stair_tmp[tmp_finish][6]) - coordinate[i].second), 2));
				dist[i][node.size() + 1] = sqrt(pow(abs(stof(stair_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(stair_tmp[tmp_finish][6]) - coordinate[i].second), 2));
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int j = 1; j < node.size() + 1; j++) {
			for (int k = 1; k < 5; k++) {
				if (intersection_tmp[tmp + i - 1][k] == node[j - 1])
					dist[i][j] = sqrt(pow(abs(coordinate[i].first - coordinate[j].first), 2) + pow(abs(coordinate[i].second - coordinate[j].second), 2));
			}
		}
	}

	for (int i = 0; i < node.size() + 2; i++) {
		for (int j = 0; j < node.size() + 2; j++) {
			if (dist[i][j] < 0) dist[i][j] = 0;
			//cout << dist[i][j] << ' ';
		}
		//cout << endl;
	}

	return dist;
}
float **intersection_dist_storage_15(string start, string finish, vector<string> node, vector<pair<float, float>> coordinate) {
	float **dist = new float *[node.size() + 2];
	for (int i = 0; i < node.size() + 2; i++) {
		dist[i] = new float[node.size() + 2];
	}
	string str;

	bool check = false;
	if (start.size() == 3)
		if (start.at(0) == finish.at(0)) check = true;
		else
			if (start.substr(0, 2) == finish.substr(0, 2)) check = true;

	int tmp_start = 0;
	int tmp_finish = 0;
	int tmp = 0;

	for (int i = 0; i < MAX_elevator; i++) {
		if (elevator_tmp[i][0].substr(2, 1) == "7" && elevator_tmp[i][0].substr(0, 1) == finish.substr(0, 1) && elevator_tmp[i][0].size() == 3) {
			tmp_start = i;
			break;
		}
	}

	for (int i = 0; i < MAX_stair; i++) {
		if (stair_tmp[i][0].substr(2, 1) == "2" && stair_tmp[i][0].substr(0, 1) == finish.substr(0, 1) && stair_tmp[i][0].size() == 3) {
			tmp_finish = i;
			break;
		}
	}

	for (int i = 0; i < MAX_intersection; i++) {
		if (start.size() == 3) {
			if (start.at(0) == intersection_tmp[i][0].at(0)) {
				tmp = i;
				break;
			}
		}
		else if (start.size() == 4) {
			if (start.substr(0, 2) == intersection_tmp[i][0].substr(0, 2) && intersection_tmp[i][0].size() == 4) {
				tmp = i;
				//cout << start.substr(0, 2) << ' ' << intersection_tmp[i][0] << ' ' << tmp << endl;
				break;
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int k = 1; k < 5; k++) {
			if (elevator_tmp[tmp_start][k] == node[i - 1]) {
				dist[0][i] = sqrt(pow(abs(stof(elevator_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(elevator_tmp[tmp_start][6]) - coordinate[i].second), 2));
				dist[i][0] = sqrt(pow(abs(stof(elevator_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(elevator_tmp[tmp_start][6]) - coordinate[i].second), 2));
			}
		}
		for (int m = 1; m < 5; m++) {
			if (stair_tmp[tmp_finish][m] == node[i - 1]) {
				dist[node.size() + 1][i] = sqrt(pow(abs(stof(stair_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(stair_tmp[tmp_finish][6]) - coordinate[i].second), 2));
				dist[i][node.size() + 1] = sqrt(pow(abs(stof(stair_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(stair_tmp[tmp_finish][6]) - coordinate[i].second), 2));
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int j = 1; j < node.size() + 1; j++) {
			for (int k = 1; k < 5; k++) {
				if (intersection_tmp[tmp + i - 1][k] == node[j - 1])
					dist[i][j] = sqrt(pow(abs(coordinate[i].first - coordinate[j].first), 2) + pow(abs(coordinate[i].second - coordinate[j].second), 2));
			}
		}
	}

	for (int i = 0; i < node.size() + 2; i++) {
		for (int j = 0; j < node.size() + 2; j++) {
			if (dist[i][j] < 0) dist[i][j] = 0;
			//cout << dist[i][j] << ' ';
		}
		//cout << endl;
	}

	return dist;
}
float **intersection_dist_storage_16(string start, string finish, vector<string> node, vector<pair<float, float>> coordinate) {
	float **dist = new float *[node.size() + 2];
	for (int i = 0; i < node.size() + 2; i++) {
		dist[i] = new float[node.size() + 2];
	}
	string str;

	bool check = false;
	if (start.size() == 3)
		if (start.at(0) == finish.at(0)) check = true;
		else
			if (start.substr(0, 2) == finish.substr(0, 2)) check = true;

	int tmp_start = 0;
	int tmp_finish = 0;
	int tmp = 0;

	for (int i = 0; i < MAX_elevator; i++) {
		if (elevator_tmp[i][0].substr(2, 1) == "7" && elevator_tmp[i][0].substr(0, 1) == finish.substr(0, 1) && elevator_tmp[i][0].size() == 3) {
			tmp_start = i;
			break;
		}
	}

	for (int i = 0; i < MAX_stair; i++) {
		if (stair_tmp[i][0].substr(2, 1) == "5" && stair_tmp[i][0].substr(0, 1) == finish.substr(0, 1) && stair_tmp[i][0].size() == 3) {
			tmp_finish = i;
			break;
		}
	}

	for (int i = 0; i < MAX_intersection; i++) {
		if (start.size() == 3) {
			if (start.at(0) == intersection_tmp[i][0].at(0)) {
				tmp = i;
				break;
			}
		}
		else if (start.size() == 4) {
			if (start.substr(0, 2) == intersection_tmp[i][0].substr(0, 2) && intersection_tmp[i][0].size() == 4) {
				tmp = i;
				//cout << start.substr(0, 2) << ' ' << intersection_tmp[i][0] << ' ' << tmp << endl;
				break;
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int k = 1; k < 5; k++) {
			if (elevator_tmp[tmp_start][k] == node[i - 1]) {
				dist[0][i] = sqrt(pow(abs(stof(elevator_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(elevator_tmp[tmp_start][6]) - coordinate[i].second), 2));
				dist[i][0] = sqrt(pow(abs(stof(elevator_tmp[tmp_start][5]) - coordinate[i].first), 2) + pow(abs(stof(elevator_tmp[tmp_start][6]) - coordinate[i].second), 2));
			}
		}
		for (int m = 1; m < 5; m++) {
			if (stair_tmp[tmp_finish][m] == node[i - 1]) {
				dist[node.size() + 1][i] = sqrt(pow(abs(stof(stair_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(stair_tmp[tmp_finish][6]) - coordinate[i].second), 2));
				dist[i][node.size() + 1] = sqrt(pow(abs(stof(stair_tmp[tmp_finish][5]) - coordinate[i].first), 2) + pow(abs(stof(stair_tmp[tmp_finish][6]) - coordinate[i].second), 2));
			}
		}
	}

	for (int i = 1; i < node.size() + 1; i++) {
		for (int j = 1; j < node.size() + 1; j++) {
			for (int k = 1; k < 5; k++) {
				if (intersection_tmp[tmp + i - 1][k] == node[j - 1])
					dist[i][j] = sqrt(pow(abs(coordinate[i].first - coordinate[j].first), 2) + pow(abs(coordinate[i].second - coordinate[j].second), 2));
			}
		}
	}

	for (int i = 0; i < node.size() + 2; i++) {
		for (int j = 0; j < node.size() + 2; j++) {
			if (dist[i][j] < 0) dist[i][j] = 0;
			//cout << dist[i][j] << ' ';
		}
		//cout << endl;
	}

	return dist;
}



//���ͽ�Ʈ�� ���̴� �Լ�
int minDistance(float *dist, bool *sptSet) {
	float min = INFINITY, min_index;

	for (int i = 0; i < _msize(dist)/sizeof(*dist); i++) {
		if (!sptSet[i] && min > dist[i]) {
			min_index = i;
			min = dist[i];
		}
	}
	return min_index;
}
void printSolution(float *dist, vector<vector<int>> path, int n, int finish)
{
	/*cout << "Vertex   Distance from Source" << "       " << "path" << endl;
	for (int i = 0; i < n; i++) {
		cout << i << "           " << dist[i] << "           ";
		for (int j = 0; j < path[i].size(); j++) {
			cout << path[i].at(j) << " -> ";
		}
		cout << endl;
	}*/
	cout << dist[finish] << endl;
	for (int j = 0; j < path[finish].size(); j++)
		cout << path[finish].at(j) << ' ';
	cout << endl;
}
//���ͽ�Ʈ��� �ִܰ���� ��ǥ���� ��ȯ�ϴ� �Լ�
vector<pair<float, float>> dijkstra_path(float **graph, vector<pair<float, float>> list, int src, int finish) {
	int n = _msize(graph) / sizeof(**graph);
	float *dist = new float[n];
	bool *sptSet = new bool[n];
	vector<vector<int>> path(n);

	for (int i = 0; i < n; i++) {
		dist[i] = INFINITY, sptSet[i] = false;
	}

	dist[src] = 0;
	path[src].push_back(src);

	for (int count = 0; count < n - 1; count++) {
		int j = minDistance(dist, sptSet);
		for (int i = 0; i < n; i++) {
			if (!sptSet[i] && graph[j][i] && dist[j] != INFINITY && dist[i] > dist[j] + graph[j][i]) {
				if (dist[i] == INFINITY) {
					for (int k = 0; k < path[j].size(); k++) {
						path[i].push_back(path[j][k]);
					}
				}
				else {
					path[i].clear();
					for (int k = 0; k < path[j].size(); k++) {
						path[i].push_back(path[j][k]);
					}
				}
				dist[i] = dist[j] + graph[j][i];
				//path[i].push_back(j);
				path[i].push_back(i);
			}
		}
		sptSet[j] = true;
	}

	//printSolution(dist, path, n, finish);
	vector<pair<float, float>> real_path;
	for (int i = 0; i < path[finish].size(); i++) {
		real_path.push_back(make_pair(list[path[finish].at(i)].first, list[path[finish].at(i)].second));
	}

	return real_path;
}
//���ͽ�Ʈ��� �ִܰ���� �Ÿ��� ��ȯ�ϴ� �Լ�
float dijkstra_dist(float **graph, vector<pair<float, float>> list, int src, int finish) {
	int n = _msize(graph) / sizeof(**graph);
	float *dist = new float[n];
	bool *sptSet = new bool[n];
	vector<vector<int>> path(n);

	for (int i = 0; i < n; i++) {
		dist[i] = INFINITY, sptSet[i] = false;
	}

	dist[src] = 0;
	path[src].push_back(src);

	for (int count = 0; count < n - 1; count ++) {
		int j = minDistance(dist, sptSet);
		for (int i = 0; i < n; i++) {
			if (!sptSet[i] && graph[j][i] && dist[j] != INFINITY && dist[i] > dist[j] + graph[j][i]) {
				if (dist[i] == INFINITY) {
					for (int k = 0; k < path[j].size(); k++) {
						path[i].push_back(path[j][k]);
					}
				}
				else {
					path[i].clear();
					for (int k = 0; k < path[j].size(); k++) {
						path[i].push_back(path[j][k]);
					}
				}
				dist[i] = dist[j] + graph[j][i];
				//path[i].push_back(j);
				path[i].push_back(i);
			}
		}
		sptSet[j] = true;
	}
	//printSolution(dist, path, n, finish);
	return (dist[finish] / 12 * 5);
}
//��� ������ ���� ���� �� �ִܰ�� ��ǥ��, �Ÿ� ���
void same_floor(string start, string finish, vector<pair<float, float>> list, float input_start_coord[1][2], float input_finish_coord[1][2], vector<string> intersection_node) {
	list.insert(list.begin(), make_pair(input_start_coord[0][0], input_start_coord[0][1]));
	list.insert(list.end(), make_pair(input_finish_coord[0][0], input_finish_coord[0][1]));

	//intersection_dist_storage(start, finish, intersection_node, list);

	vector<pair<float, float>> path;
	result_path = dijkstra_path(intersection_dist_storage(start, finish, intersection_node, list), list, 0, intersection_node.size() + 1);
	float dist;
	result_dist = dijkstra_dist(intersection_dist_storage(start, finish, intersection_node, list), list, 0, intersection_node.size() + 1);
	
	/*for (int i = 0; i < path.size(); i++) {
		cout << path[i].first << ' ' << path[i].second << "->";
	}
	cout << endl;
	cout << dist << "��" << endl;*/
}
//��� ������ �ٸ� ���� �� 1������ �̵������� ��ġ�� ��ǥ��, �Ÿ� ���
void not_same_floor(int tmp, string start, string middle, string middle2, string finish, vector<pair<float, float>> list, vector<pair<float, float>> list2, float input_start_coord[1][2], float input_middle1_coord[1][2], float input_middle2_coord[1][2], float input_finish_coord[1][2], vector<string> intersection_node, vector<string> intersection_node_2) {
	if (tmp == 1) {
		list.insert(list.begin(), make_pair(input_start_coord[0][0], input_start_coord[0][1]));
		list.insert(list.end(), make_pair(input_middle1_coord[0][0], input_middle1_coord[0][1]));
		list2.insert(list2.end(), make_pair(input_middle2_coord[0][0], input_middle2_coord[0][1]));
		list2.insert(list2.begin(), make_pair(input_finish_coord[0][0], input_finish_coord[0][1]));
		//intersection_dist_storage(start, finish, intersection_node, list);

		path = dijkstra_path(intersection_dist_storage_2(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
		path2 = dijkstra_path(intersection_dist_storage_2(finish, middle2, intersection_node_2, list2), list2, intersection_node_2.size() + 1, 0);
		path.push_back(make_pair(-1000, -1000));
		path.insert(path.end(), path2.begin(), path2.end());
		dist = dijkstra_dist(intersection_dist_storage_2(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
		dist2 = dijkstra_dist(intersection_dist_storage_2(finish, middle2, intersection_node_2, list2), list2, intersection_node_2.size() + 1, 0);
		dist += dist2;

		for (int i = 0; i < path.size(); i++) {
			//cout << path[i].first << ' ' << path[i].second << "->";
		}
		//cout << endl;

		//cout << dist << "��" << endl;
	}
	else {
		list.insert(list.begin(), make_pair(input_start_coord[0][0], input_start_coord[0][1]));
		list.insert(list.end(), make_pair(input_middle1_coord[0][0], input_middle1_coord[0][1]));
		list2.insert(list2.end(), make_pair(input_middle2_coord[0][0], input_middle2_coord[0][1]));
		list2.insert(list2.begin(), make_pair(input_finish_coord[0][0], input_finish_coord[0][1]));
		//intersection_dist_storage(start, finish, intersection_node, list);

		path = dijkstra_path(intersection_dist_storage_5(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
		path2 = dijkstra_path(intersection_dist_storage_5(finish, middle2, intersection_node_2, list2), list2, intersection_node_2.size() + 1, 0);
		path.push_back(make_pair(-1000, -1000));
		path.insert(path.end(), path2.begin(), path2.end());
		dist = dijkstra_dist(intersection_dist_storage_5(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
		dist2 = dijkstra_dist(intersection_dist_storage_5(finish, middle2, intersection_node_2, list2), list2, intersection_node_2.size() + 1, 0);
		dist += dist2;
	}
}
//��� ������ �ٸ� ���� �� 2������ �̵������� ��ġ�� ��ǥ��, �Ÿ� ���
void not_same_floor2(int tmp, string start, string middle, string middle2, string finish, vector<pair<float, float>> list, vector<pair<float, float>> list2, float input_start_coord[1][2], float input_middle1_coord[1][2], float input_middle2_coord[1][2], float input_finish_coord[1][2], vector<string> intersection_node, vector<string> intersection_node_2) {
	if (tmp == 1) {
		list.insert(list.begin(), make_pair(input_start_coord[0][0], input_start_coord[0][1]));
		list.insert(list.end(), make_pair(input_middle1_coord[0][0], input_middle1_coord[0][1]));
		list2.insert(list2.end(), make_pair(input_middle2_coord[0][0], input_middle2_coord[0][1]));
		list2.insert(list2.begin(), make_pair(input_finish_coord[0][0], input_finish_coord[0][1]));
		//intersection_dist_storage(start, finish, intersection_node, list);

		path3 = dijkstra_path(intersection_dist_storage_3(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
		path4 = dijkstra_path(intersection_dist_storage_3(finish, middle2, intersection_node_2, list2), list2, intersection_node_2.size() + 1, 0);
		path3.push_back(make_pair(-1000, -1000));
		path3.insert(path3.end(), path4.begin(), path4.end());
		dist3 = dijkstra_dist(intersection_dist_storage_3(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
		dist4 = dijkstra_dist(intersection_dist_storage_3(finish, middle2, intersection_node_2, list2), list2, intersection_node_2.size() + 1, 0);
		dist3 += dist4;

		for (int i = 0; i < path.size(); i++) {
			//cout << path3[i].first << ' ' << path3[i].second << "->";
		}

		//cout << endl;
		//cout << dist3 << "��" << endl;
	}
	else {
		list.insert(list.begin(), make_pair(input_start_coord[0][0], input_start_coord[0][1]));
		list.insert(list.end(), make_pair(input_middle1_coord[0][0], input_middle1_coord[0][1]));
		list2.insert(list2.end(), make_pair(input_middle2_coord[0][0], input_middle2_coord[0][1]));
		list2.insert(list2.begin(), make_pair(input_finish_coord[0][0], input_finish_coord[0][1]));
		//intersection_dist_storage(start, finish, intersection_node, list);

		path3 = dijkstra_path(intersection_dist_storage_6(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
		path4 = dijkstra_path(intersection_dist_storage_6(finish, middle2, intersection_node_2, list2), list2, intersection_node_2.size() + 1, 0);
		path3.push_back(make_pair(-1000, -1000));
		path3.insert(path3.end(), path4.begin(), path4.end());
		dist3 = dijkstra_dist(intersection_dist_storage_6(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
		dist4 = dijkstra_dist(intersection_dist_storage_6(finish, middle2, intersection_node_2, list2), list2, intersection_node_2.size() + 1, 0);
		dist3 += dist4;
	}
}
//��� ������ �ٸ� ���� �� 3������ �̵������� ��ġ�� ��ǥ��, �Ÿ� ���
void not_same_floor3(int tmp, string start, string middle, string middle2, string finish, vector<pair<float, float>> list, vector<pair<float, float>> list2, float input_start_coord[1][2], float input_middle1_coord[1][2], float input_middle2_coord[1][2], float input_finish_coord[1][2], vector<string> intersection_node, vector<string> intersection_node_2) {
	if (tmp == 1) {
		list.insert(list.begin(), make_pair(input_start_coord[0][0], input_start_coord[0][1]));
		list.insert(list.end(), make_pair(input_middle1_coord[0][0], input_middle1_coord[0][1]));
		list2.insert(list2.end(), make_pair(input_middle2_coord[0][0], input_middle2_coord[0][1]));
		list2.insert(list2.begin(), make_pair(input_finish_coord[0][0], input_finish_coord[0][1]));
		//intersection_dist_storage(start, finish, intersection_node, list);

		path5 = dijkstra_path(intersection_dist_storage_4(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
		path6 = dijkstra_path(intersection_dist_storage_4(finish, middle2, intersection_node_2, list2), list2, intersection_node_2.size() + 1, 0);
		path5.push_back(make_pair(-1000, -1000));
		path5.insert(path5.end(), path6.begin(), path6.end());
		dist5 = dijkstra_dist(intersection_dist_storage_4(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
		dist6 = dijkstra_dist(intersection_dist_storage_4(finish, middle2, intersection_node_2, list2), list2, intersection_node_2.size() + 1, 0);
		dist5 += dist6;

		for (int i = 0; i < path.size(); i++) {
			//cout << path5[i].first << ' ' << path5[i].second << "->";
		}

		//cout << endl;
		//cout << dist5 << "��" << endl;
	}
	else {
		list.insert(list.begin(), make_pair(input_start_coord[0][0], input_start_coord[0][1]));
		list.insert(list.end(), make_pair(input_middle1_coord[0][0], input_middle1_coord[0][1]));
		list2.insert(list2.end(), make_pair(input_middle2_coord[0][0], input_middle2_coord[0][1]));
		list2.insert(list2.begin(), make_pair(input_finish_coord[0][0], input_finish_coord[0][1]));
		//intersection_dist_storage(start, finish, intersection_node, list);

		path5 = dijkstra_path(intersection_dist_storage_7(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
		path6 = dijkstra_path(intersection_dist_storage_7(finish, middle2, intersection_node_2, list2), list2, intersection_node_2.size() + 1, 0);
		path5.push_back(make_pair(-1000, -1000));
		path5.insert(path5.end(), path6.begin(), path6.end());
		dist5 = dijkstra_dist(intersection_dist_storage_7(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
		dist6 = dijkstra_dist(intersection_dist_storage_7(finish, middle2, intersection_node_2, list2), list2, intersection_node_2.size() + 1, 0);
		dist5 += dist6;
	}
}
void not_same_floor4(string start, string middle, string middle2, string middle3, string middle4, string finish, vector<pair<float, float>> list, vector<pair<float, float>> list2, vector<pair<float, float>> list3, float input_start_coord[1][2], float input_middle1_coord[1][2], float input_middle2_coord[1][2], float input_middle3_coord[1][2], float input_middle4_coord[1][2], float input_finish_coord[1][2], vector<string> intersection_node, vector<string> intersection_node_2, vector<string> intersection_node_3) {
	list.insert(list.begin(), make_pair(input_start_coord[0][0], input_start_coord[0][1]));
	list.insert(list.end(), make_pair(input_middle1_coord[0][0], input_middle1_coord[0][1]));
	list2.insert(list2.begin(), make_pair(input_middle2_coord[0][0], input_middle2_coord[0][1]));
	list2.insert(list2.end(), make_pair(input_middle3_coord[0][0], input_middle3_coord[0][1]));
	list3.insert(list3.end(), make_pair(input_middle4_coord[0][0], input_middle4_coord[0][1]));
	list3.insert(list3.begin(), make_pair(input_finish_coord[0][0], input_finish_coord[0][1]));
	//intersection_dist_storage(start, finish, intersection_node, list);

	path = dijkstra_path(intersection_dist_storage_2(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
	path_tmp1 = dijkstra_path(intersection_dist_storage_8(middle2, middle3, intersection_node_2, list2), list2, 0, intersection_node_2.size() + 1);
	path_tmp2 = dijkstra_path(intersection_dist_storage_5(finish, middle4, intersection_node_3, list3), list3, intersection_node_3.size() + 1, 0);
	path.push_back(make_pair(-1000, -1000));
	path.insert(path.end(), path_tmp1.begin(), path_tmp1.end());
	path.push_back(make_pair(-1000, -1000));
	path.insert(path.end(), path_tmp2.begin(), path_tmp2.end());

	dist = dijkstra_dist(intersection_dist_storage_2(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
	dist += dijkstra_dist(intersection_dist_storage_8(middle2, middle3, intersection_node_2, list2), list2, 0, intersection_node_2.size() + 1);
	dist += dijkstra_dist(intersection_dist_storage_5(finish, middle4, intersection_node_3, list3), list3, intersection_node_3.size() + 1, 0);
}
void not_same_floor5(string start, string middle, string middle2, string middle3, string middle4, string finish, vector<pair<float, float>> list, vector<pair<float, float>> list2, vector<pair<float, float>> list3, float input_start_coord[1][2], float input_middle1_coord[1][2], float input_middle2_coord[1][2], float input_middle3_coord[1][2], float input_middle4_coord[1][2], float input_finish_coord[1][2], vector<string> intersection_node, vector<string> intersection_node_2, vector<string> intersection_node_3) {
	list.insert(list.begin(), make_pair(input_start_coord[0][0], input_start_coord[0][1]));
	list.insert(list.end(), make_pair(input_middle1_coord[0][0], input_middle1_coord[0][1]));
	list2.insert(list2.begin(), make_pair(input_middle2_coord[0][0], input_middle2_coord[0][1]));
	list2.insert(list2.end(), make_pair(input_middle3_coord[0][0], input_middle3_coord[0][1]));
	list3.insert(list3.end(), make_pair(input_middle4_coord[0][0], input_middle4_coord[0][1]));
	list3.insert(list3.begin(), make_pair(input_finish_coord[0][0], input_finish_coord[0][1]));
	//intersection_dist_storage(start, finish, intersection_node, list);

	path_tmp1.clear();
	path_tmp2.clear();

	path2 = dijkstra_path(intersection_dist_storage_2(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
	path_tmp1 = dijkstra_path(intersection_dist_storage_9(middle2, middle3, intersection_node_2, list2), list2, 0, intersection_node_2.size() + 1);
	path_tmp2 = dijkstra_path(intersection_dist_storage_6(finish, middle4, intersection_node_3, list3), list3, intersection_node_3.size() + 1, 0);
	path2.push_back(make_pair(-1000, -1000));
	path2.insert(path2.end(), path_tmp1.begin(), path_tmp1.end());
	path2.push_back(make_pair(-1000, -1000));
	path2.insert(path2.end(), path_tmp2.begin(), path_tmp2.end());

	dist2 = dijkstra_dist(intersection_dist_storage_2(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
	dist2 += dijkstra_dist(intersection_dist_storage_9(middle2, middle3, intersection_node_2, list2), list2, 0, intersection_node_2.size() + 1);
	dist2 += dijkstra_dist(intersection_dist_storage_6(finish, middle4, intersection_node_3, list3), list3, intersection_node_3.size() + 1, 0);
}
void not_same_floor6(string start, string middle, string middle2, string middle3, string middle4, string finish, vector<pair<float, float>> list, vector<pair<float, float>> list2, vector<pair<float, float>> list3, float input_start_coord[1][2], float input_middle1_coord[1][2], float input_middle2_coord[1][2], float input_middle3_coord[1][2], float input_middle4_coord[1][2], float input_finish_coord[1][2], vector<string> intersection_node, vector<string> intersection_node_2, vector<string> intersection_node_3) {
	list.insert(list.begin(), make_pair(input_start_coord[0][0], input_start_coord[0][1]));
	list.insert(list.end(), make_pair(input_middle1_coord[0][0], input_middle1_coord[0][1]));
	list2.insert(list2.begin(), make_pair(input_middle2_coord[0][0], input_middle2_coord[0][1]));
	list2.insert(list2.end(), make_pair(input_middle3_coord[0][0], input_middle3_coord[0][1]));
	list3.insert(list3.end(), make_pair(input_middle4_coord[0][0], input_middle4_coord[0][1]));
	list3.insert(list3.begin(), make_pair(input_finish_coord[0][0], input_finish_coord[0][1]));
	//intersection_dist_storage(start, finish, intersection_node, list);
	path_tmp1.clear();
	path_tmp2.clear();

	path3 = dijkstra_path(intersection_dist_storage_2(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
	path_tmp1 = dijkstra_path(intersection_dist_storage_10(middle2, middle3, intersection_node_2, list2), list2, 0, intersection_node_2.size() + 1);
	path_tmp2 = dijkstra_path(intersection_dist_storage_7(finish, middle4, intersection_node_3, list3), list3, intersection_node_3.size() + 1, 0);
	path3.push_back(make_pair(-1000, -1000));
	path3.insert(path3.end(), path_tmp1.begin(), path_tmp1.end());
	path3.push_back(make_pair(-1000, -1000));
	path3.insert(path3.end(), path_tmp2.begin(), path_tmp2.end());

	dist3 = dijkstra_dist(intersection_dist_storage_2(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
	dist3 += dijkstra_dist(intersection_dist_storage_10(middle2, middle3, intersection_node_2, list2), list2, 0, intersection_node_2.size() + 1);
	dist3 += dijkstra_dist(intersection_dist_storage_7(finish, middle4, intersection_node_3, list3), list3, intersection_node_3.size() + 1, 0);
}
void not_same_floor7(string start, string middle, string middle2, string middle3, string middle4, string finish, vector<pair<float, float>> list, vector<pair<float, float>> list2, vector<pair<float, float>> list3, float input_start_coord[1][2], float input_middle1_coord[1][2], float input_middle2_coord[1][2], float input_middle3_coord[1][2], float input_middle4_coord[1][2], float input_finish_coord[1][2], vector<string> intersection_node, vector<string> intersection_node_2, vector<string> intersection_node_3) {
	list.insert(list.begin(), make_pair(input_start_coord[0][0], input_start_coord[0][1]));
	list.insert(list.end(), make_pair(input_middle1_coord[0][0], input_middle1_coord[0][1]));
	list2.insert(list2.begin(), make_pair(input_middle2_coord[0][0], input_middle2_coord[0][1]));
	list2.insert(list2.end(), make_pair(input_middle3_coord[0][0], input_middle3_coord[0][1]));
	list3.insert(list3.end(), make_pair(input_middle4_coord[0][0], input_middle4_coord[0][1]));
	list3.insert(list3.begin(), make_pair(input_finish_coord[0][0], input_finish_coord[0][1]));
	//intersection_dist_storage(start, finish, intersection_node, list);
	path_tmp1.clear();
	path_tmp2.clear();

	path4 = dijkstra_path(intersection_dist_storage_3(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
	path_tmp1 = dijkstra_path(intersection_dist_storage_11(middle2, middle3, intersection_node_2, list2), list2, 0, intersection_node_2.size() + 1);
	path_tmp2 = dijkstra_path(intersection_dist_storage_5(finish, middle4, intersection_node_3, list3), list3, intersection_node_3.size() + 1, 0);
	path4.push_back(make_pair(-1000, -1000));
	path4.insert(path4.end(), path_tmp1.begin(), path_tmp1.end());
	path4.push_back(make_pair(-1000, -1000));
	path4.insert(path4.end(), path_tmp2.begin(), path_tmp2.end());

	dist4 = dijkstra_dist(intersection_dist_storage_3(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
	dist4 += dijkstra_dist(intersection_dist_storage_11(middle2, middle3, intersection_node_2, list2), list2, 0, intersection_node_2.size() + 1);
	dist4 += dijkstra_dist(intersection_dist_storage_5(finish, middle4, intersection_node_3, list3), list3, intersection_node_3.size() + 1, 0);
}
void not_same_floor8(string start, string middle, string middle2, string middle3, string middle4, string finish, vector<pair<float, float>> list, vector<pair<float, float>> list2, vector<pair<float, float>> list3, float input_start_coord[1][2], float input_middle1_coord[1][2], float input_middle2_coord[1][2], float input_middle3_coord[1][2], float input_middle4_coord[1][2], float input_finish_coord[1][2], vector<string> intersection_node, vector<string> intersection_node_2, vector<string> intersection_node_3) {
	list.insert(list.begin(), make_pair(input_start_coord[0][0], input_start_coord[0][1]));
	list.insert(list.end(), make_pair(input_middle1_coord[0][0], input_middle1_coord[0][1]));
	list2.insert(list2.begin(), make_pair(input_middle2_coord[0][0], input_middle2_coord[0][1]));
	list2.insert(list2.end(), make_pair(input_middle3_coord[0][0], input_middle3_coord[0][1]));
	list3.insert(list3.end(), make_pair(input_middle4_coord[0][0], input_middle4_coord[0][1]));
	list3.insert(list3.begin(), make_pair(input_finish_coord[0][0], input_finish_coord[0][1]));
	//intersection_dist_storage(start, finish, intersection_node, list);
	path_tmp1.clear();
	path_tmp2.clear();

	path5 = dijkstra_path(intersection_dist_storage_3(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
	path_tmp1 = dijkstra_path(intersection_dist_storage_12(middle2, middle3, intersection_node_2, list2), list2, 0, intersection_node_2.size() + 1);
	path_tmp2 = dijkstra_path(intersection_dist_storage_6(finish, middle4, intersection_node_3, list3), list3, intersection_node_3.size() + 1, 0);
	path5.push_back(make_pair(-1000, -1000));
	path5.insert(path5.end(), path_tmp1.begin(), path_tmp1.end());
	path5.push_back(make_pair(-1000, -1000));
	path5.insert(path5.end(), path_tmp2.begin(), path_tmp2.end());

	dist5 = dijkstra_dist(intersection_dist_storage_3(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
	dist5 += dijkstra_dist(intersection_dist_storage_12(middle2, middle3, intersection_node_2, list2), list2, 0, intersection_node_2.size() + 1);
	dist5 += dijkstra_dist(intersection_dist_storage_6(finish, middle4, intersection_node_3, list3), list3, intersection_node_3.size() + 1, 0);
}
void not_same_floor9(string start, string middle, string middle2, string middle3, string middle4, string finish, vector<pair<float, float>> list, vector<pair<float, float>> list2, vector<pair<float, float>> list3, float input_start_coord[1][2], float input_middle1_coord[1][2], float input_middle2_coord[1][2], float input_middle3_coord[1][2], float input_middle4_coord[1][2], float input_finish_coord[1][2], vector<string> intersection_node, vector<string> intersection_node_2, vector<string> intersection_node_3) {
	list.insert(list.begin(), make_pair(input_start_coord[0][0], input_start_coord[0][1]));
	list.insert(list.end(), make_pair(input_middle1_coord[0][0], input_middle1_coord[0][1]));
	list2.insert(list2.begin(), make_pair(input_middle2_coord[0][0], input_middle2_coord[0][1]));
	list2.insert(list2.end(), make_pair(input_middle3_coord[0][0], input_middle3_coord[0][1]));
	list3.insert(list3.end(), make_pair(input_middle4_coord[0][0], input_middle4_coord[0][1]));
	list3.insert(list3.begin(), make_pair(input_finish_coord[0][0], input_finish_coord[0][1]));
	//intersection_dist_storage(start, finish, intersection_node, list);
	path_tmp1.clear();
	path_tmp2.clear();

	path6 = dijkstra_path(intersection_dist_storage_3(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
	path_tmp1 = dijkstra_path(intersection_dist_storage_13(middle2, middle3, intersection_node_2, list2), list2, 0, intersection_node_2.size() + 1);
	path_tmp2 = dijkstra_path(intersection_dist_storage_7(finish, middle4, intersection_node_3, list3), list3, intersection_node_3.size() + 1, 0);
	path6.push_back(make_pair(-1000, -1000));
	path6.insert(path6.end(), path_tmp1.begin(), path_tmp1.end());
	path6.push_back(make_pair(-1000, -1000));
	path6.insert(path6.end(), path_tmp2.begin(), path_tmp2.end());

	dist6 = dijkstra_dist(intersection_dist_storage_3(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
	dist6 += dijkstra_dist(intersection_dist_storage_13(middle2, middle3, intersection_node_2, list2), list2, 0, intersection_node_2.size() + 1);
	dist6 += dijkstra_dist(intersection_dist_storage_7(finish, middle4, intersection_node_3, list3), list3, intersection_node_3.size() + 1, 0);
}
void not_same_floor10(string start, string middle, string middle2, string middle3, string middle4, string finish, vector<pair<float, float>> list, vector<pair<float, float>> list2, vector<pair<float, float>> list3, float input_start_coord[1][2], float input_middle1_coord[1][2], float input_middle2_coord[1][2], float input_middle3_coord[1][2], float input_middle4_coord[1][2], float input_finish_coord[1][2], vector<string> intersection_node, vector<string> intersection_node_2, vector<string> intersection_node_3) {
	list.insert(list.begin(), make_pair(input_start_coord[0][0], input_start_coord[0][1]));
	list.insert(list.end(), make_pair(input_middle1_coord[0][0], input_middle1_coord[0][1]));
	list2.insert(list2.begin(), make_pair(input_middle2_coord[0][0], input_middle2_coord[0][1]));
	list2.insert(list2.end(), make_pair(input_middle3_coord[0][0], input_middle3_coord[0][1]));
	list3.insert(list3.end(), make_pair(input_middle4_coord[0][0], input_middle4_coord[0][1]));
	list3.insert(list3.begin(), make_pair(input_finish_coord[0][0], input_finish_coord[0][1]));
	//intersection_dist_storage(start, finish, intersection_node, list);
	path_tmp1.clear();
	path_tmp2.clear();

	path7 = dijkstra_path(intersection_dist_storage_4(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
	path_tmp1 = dijkstra_path(intersection_dist_storage_14(middle2, middle3, intersection_node_2, list2), list2, 0, intersection_node_2.size() + 1);
	path_tmp2 = dijkstra_path(intersection_dist_storage_5(finish, middle4, intersection_node_3, list3), list3, intersection_node_3.size() + 1, 0);
	path7.push_back(make_pair(-1000, -1000));
	path7.insert(path7.end(), path_tmp1.begin(), path_tmp1.end());
	path7.push_back(make_pair(-1000, -1000));
	path7.insert(path7.end(), path_tmp2.begin(), path_tmp2.end());

	dist7 = dijkstra_dist(intersection_dist_storage_4(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
	dist7 += dijkstra_dist(intersection_dist_storage_14(middle2, middle3, intersection_node_2, list2), list2, 0, intersection_node_2.size() + 1);
	dist7 += dijkstra_dist(intersection_dist_storage_5(finish, middle4, intersection_node_3, list3), list3, intersection_node_3.size() + 1, 0);
}
void not_same_floor11(string start, string middle, string middle2, string middle3, string middle4, string finish, vector<pair<float, float>> list, vector<pair<float, float>> list2, vector<pair<float, float>> list3, float input_start_coord[1][2], float input_middle1_coord[1][2], float input_middle2_coord[1][2], float input_middle3_coord[1][2], float input_middle4_coord[1][2], float input_finish_coord[1][2], vector<string> intersection_node, vector<string> intersection_node_2, vector<string> intersection_node_3) {
	list.insert(list.begin(), make_pair(input_start_coord[0][0], input_start_coord[0][1]));
	list.insert(list.end(), make_pair(input_middle1_coord[0][0], input_middle1_coord[0][1]));
	list2.insert(list2.begin(), make_pair(input_middle2_coord[0][0], input_middle2_coord[0][1]));
	list2.insert(list2.end(), make_pair(input_middle3_coord[0][0], input_middle3_coord[0][1]));
	list3.insert(list3.end(), make_pair(input_middle4_coord[0][0], input_middle4_coord[0][1]));
	list3.insert(list3.begin(), make_pair(input_finish_coord[0][0], input_finish_coord[0][1]));
	//intersection_dist_storage(start, finish, intersection_node, list);
	path_tmp1.clear();
	path_tmp2.clear();

	path8 = dijkstra_path(intersection_dist_storage_4(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
	path_tmp1 = dijkstra_path(intersection_dist_storage_15(middle2, middle3, intersection_node_2, list2), list2, 0, intersection_node_2.size() + 1);
	path_tmp2 = dijkstra_path(intersection_dist_storage_6(finish, middle4, intersection_node_3, list3), list3, intersection_node_3.size() + 1, 0);
	path8.push_back(make_pair(-1000, -1000));
	path8.insert(path8.end(), path_tmp1.begin(), path_tmp1.end());
	path8.push_back(make_pair(-1000, -1000));
	path8.insert(path8.end(), path_tmp2.begin(), path_tmp2.end());

	dist8 = dijkstra_dist(intersection_dist_storage_4(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
	dist8 += dijkstra_dist(intersection_dist_storage_15(middle2, middle3, intersection_node_2, list2), list2, 0, intersection_node_2.size() + 1);
	dist8 += dijkstra_dist(intersection_dist_storage_6(finish, middle4, intersection_node_3, list3), list3, intersection_node_3.size() + 1, 0);
}
void not_same_floor12(string start, string middle, string middle2, string middle3, string middle4, string finish, vector<pair<float, float>> list, vector<pair<float, float>> list2, vector<pair<float, float>> list3, float input_start_coord[1][2], float input_middle1_coord[1][2], float input_middle2_coord[1][2], float input_middle3_coord[1][2], float input_middle4_coord[1][2], float input_finish_coord[1][2], vector<string> intersection_node, vector<string> intersection_node_2, vector<string> intersection_node_3) {
	list.insert(list.begin(), make_pair(input_start_coord[0][0], input_start_coord[0][1]));
	list.insert(list.end(), make_pair(input_middle1_coord[0][0], input_middle1_coord[0][1]));
	list2.insert(list2.begin(), make_pair(input_middle2_coord[0][0], input_middle2_coord[0][1]));
	list2.insert(list2.end(), make_pair(input_middle3_coord[0][0], input_middle3_coord[0][1]));
	list3.insert(list3.end(), make_pair(input_middle4_coord[0][0], input_middle4_coord[0][1]));
	list3.insert(list3.begin(), make_pair(input_finish_coord[0][0], input_finish_coord[0][1]));
	//intersection_dist_storage(start, finish, intersection_node, list);
	path_tmp1.clear();
	path_tmp2.clear();

	path9 = dijkstra_path(intersection_dist_storage_4(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
	path_tmp1 = dijkstra_path(intersection_dist_storage_16(middle2, middle3, intersection_node_2, list2), list2, 0, intersection_node_2.size() + 1);
	path_tmp2 = dijkstra_path(intersection_dist_storage_7(finish, middle4, intersection_node_3, list3), list3, intersection_node_3.size() + 1, 0);
	path9.push_back(make_pair(-1000, -1000));
	path9.insert(path9.end(), path_tmp1.begin(), path_tmp1.end());
	path9.push_back(make_pair(-1000, -1000));
	path9.insert(path9.end(), path_tmp2.begin(), path_tmp2.end());

	dist9 = dijkstra_dist(intersection_dist_storage_4(start, middle, intersection_node, list), list, 0, intersection_node.size() + 1);
	dist9 += dijkstra_dist(intersection_dist_storage_16(middle2, middle3, intersection_node_2, list2), list2, 0, intersection_node_2.size() + 1);
	dist9 += dijkstra_dist(intersection_dist_storage_7(finish, middle4, intersection_node_3, list3), list3, intersection_node_3.size() + 1, 0);
}

//���� ��� ��� ��ǥ ���� �Լ�
vector<pair<float, float>> r_path(vector<pair<float, float>> path, vector<pair<float, float>> path3, vector<pair<float, float>> path5, float dist, float dist3, float dist5) {
	if (dist > dist3) {
		if (dist3 > dist5) return path5;
		else return path3;
	}
	else {
		if (dist3 < dist5) return path;
		else if (dist < dist5) return path;
		else return path5;
	}
}
//���� ��� ��� �Ÿ� ���� �Լ�
float r_dist(float dist, float dist3, float dist5) {
	if (dist > dist3) {
		if (dist3 > dist5) return dist5;
		else return dist3;
	}
	else {
		if (dist3 < dist5) return dist;
		else if (dist < dist5) return dist;
		else return dist5;
	}
}

int main() {
	int q = 0;
	string inputString[2000];

	ifstream inFile("temp_.csv");

	//���� �޾ƿ�
	while (!inFile.eof()) {
		getline(inFile, inputString[q]);
		q++;
	}
	
	pop_mat(inputString, q);//�����α� ����
	print_mat();

	inFile.close();

	//���� �Է�
	string input_start, input_finish, day, time;
	int day_int, time_int;
	cout << "���� �Է�(ex ������) : ";
	cin >> day;
	day_int = convert_day(day);
	cout << "�ð� �Է�(ex 9:00) : ";
	cin >> time;
	time_int = convert_time(time);
	cout << "��� ���ǽ� �Է�(������ 101) : ";
	cin >> input_start;
	cout << "���� ���ǽ� �Է� : ";
	cin >> input_finish;

	//�� ���� �� ��� ���Ϳ� �����ϴ� ����
	int a = 0, b = 0, c = 0, d = 0;
	string inputString_a[2000];
	string inputString_b[2000];
	string inputString_c[2000];
	string inputString_d[2000];

	ifstream intersection("intersection.csv");
	ifstream classes("class.csv");
	ifstream elevator("elevator.csv");
	ifstream stair("stair.csv");

	while (!intersection.eof()) {
		getline(intersection, inputString_a[a]);
		a++;
	}
	while (!classes.eof()) {
		getline(classes, inputString_b[b]);
		b++;
	}
	while (!elevator.eof()) {
		getline(elevator, inputString_c[c]);
		c++;
	}
	while (!stair.eof()) {
		getline(stair, inputString_d[d]);
		d++;
	}

	intersection.close();
	tmp_storage(inputString_a, inputString_b, inputString_c, inputString_d);
	intersection_node_storage();

	//����, ����, ��ġ�� �̵����� ��� ��ǥ �����ϴ� ����
	float input_start_coordinate[1][2] = { 0, 0 };
	float input_finish_coordinate[1][2] = { 0, 0 };
	float input_middle1_coordinate[1][2] = { 0 ,0 };
	float input_middle2_coordinate[1][2] = { 0 ,0 };
	float input_middle3_coordinate[1][2] = { 0 ,0 };
	float input_middle4_coordinate[1][2] = { 0 ,0 };
	float input_middle5_coordinate[1][2] = { 0 ,0 };
	float input_middle6_coordinate[1][2] = { 0 ,0 };

	//����, ���� ��� ��ǥ ����
	for (int i = 0; i < MAX_class; i++) {
		if (class_tmp[i][0] == input_start) {
			input_start_coordinate[0][0] = stof(class_tmp[i][5]);
			input_start_coordinate[0][1] = stof(class_tmp[i][6]);
		}
		if (class_tmp[i][0] == input_finish) {
			input_finish_coordinate[0][0] = stof(class_tmp[i][5]);
			input_finish_coordinate[0][1] = stof(class_tmp[i][6]);
		}
	}

	//���� ���϶� ���
	if (input_start.at(0) == input_finish.at(0)) {
		if (input_start.size() == 3) {
			if (input_start.at(0) == '1')
				same_floor(input_start, input_finish, intersection_coordinate_1F, input_start_coordinate, input_finish_coordinate, intersection_node_1F);
			else if (input_start.at(0) == '2')
				same_floor(input_start, input_finish, intersection_coordinate_2F, input_start_coordinate, input_finish_coordinate, intersection_node_2F);
			else if (input_start.at(0) == '3')
				same_floor(input_start, input_finish, intersection_coordinate_3F, input_start_coordinate, input_finish_coordinate, intersection_node_3F);
			else if (input_start.at(0) == '4')
				same_floor(input_start, input_finish, intersection_coordinate_4F, input_start_coordinate, input_finish_coordinate, intersection_node_4F);
			else if (input_start.at(0) == '5')
				same_floor(input_start, input_finish, intersection_coordinate_5F, input_start_coordinate, input_finish_coordinate, intersection_node_5F);
			else if (input_start.at(0) == '6')
				same_floor(input_start, input_finish, intersection_coordinate_6F, input_start_coordinate, input_finish_coordinate, intersection_node_6F);
			else if (input_start.at(0) == '7')
				same_floor(input_start, input_finish, intersection_coordinate_7F, input_start_coordinate, input_finish_coordinate, intersection_node_7F);
			else if (input_start.at(0) == '8')
				same_floor(input_start, input_finish, intersection_coordinate_8F, input_start_coordinate, input_finish_coordinate, intersection_node_8F);
			else if (input_start.at(0) == '9')
				same_floor(input_start, input_finish, intersection_coordinate_9F, input_start_coordinate, input_finish_coordinate, intersection_node_9F);
		}
		else {
			if (input_start.substr(0, 2) == "B1")
				same_floor(input_start, input_finish, intersection_coordinate_B1, input_start_coordinate, input_finish_coordinate, intersection_node_B1);
			else if (input_start.substr(0, 2) == "B2")
				same_floor(input_start, input_finish, intersection_coordinate_B2, input_start_coordinate, input_finish_coordinate, intersection_node_B2);
			else if (input_start.substr(0, 2) == "B3")
				same_floor(input_start, input_finish, intersection_coordinate_B3, input_start_coordinate, input_finish_coordinate, intersection_node_B3);
			else if (input_start.substr(0, 2) == "B4")
				same_floor(input_start, input_finish, intersection_coordinate_B4, input_start_coordinate, input_finish_coordinate, intersection_node_B4);
			else if (input_start.substr(0, 2) == "B5")
				same_floor(input_start, input_finish, intersection_coordinate_B5, input_start_coordinate, input_finish_coordinate, intersection_node_B5);
			else if (input_start.substr(0, 2) == "B6")
				same_floor(input_start, input_finish, intersection_coordinate_B6, input_start_coordinate, input_finish_coordinate, intersection_node_B6);
			else if (input_start.substr(0, 2) == "10")
				same_floor(input_start, input_finish, intersection_coordinate_10F, input_start_coordinate, input_finish_coordinate, intersection_node_10F);
			else if (input_start.substr(0, 2) == "11")
				same_floor(input_start, input_finish, intersection_coordinate_11F, input_start_coordinate, input_finish_coordinate, intersection_node_11F);
			else if (input_start.substr(0, 2) == "12")
				same_floor(input_start, input_finish, intersection_coordinate_12F, input_start_coordinate, input_finish_coordinate, intersection_node_12F);
		}
		floor_st.push_back(stoi(input_start.substr(0, 1)));
	}
	//�ٸ� ���� �� ���
	else {
		int tmp, tmp2, tmp3;
		string middle1, middle2, middle3, middle4, middle5, middle6, middle7, middle8, middle9, middle10, middle11, middle12;
		//�����α� �� �����ֱ� ���� ������ ����
		tmp = population[stoi(input_start.substr(0, 1))][1][day_int][time_int];
		tmp2 = population[stoi(input_start.substr(0, 1))][2][day_int][time_int] / 2;
		tmp3 = population[stoi(input_start.substr(0, 1))][3][day_int][time_int] / 2;

		//�� ���� 3�� ���Ϸ� ���� ���� & �� ���� ��� ��� ��ǥ�� �̸� ���� -> ���߿� ����ϱ� ����
		if (abs(stoi(input_start.substr(0, 1)) - stoi(input_finish.substr(0, 1))) <= 3) {
			floor_st.push_back(stoi(input_start.substr(0, 1)));
			floor_st.push_back(stoi(input_finish.substr(0, 1)));
			for (int i = 0; i < MAX_stair; i++) {
				if (stair_tmp[i][0].substr(2, 1) == "1" && stair_tmp[i][0].substr(0, 1) == input_start.substr(0, 1)) {
					middle1 = stair_tmp[i][0];
					input_middle1_coordinate[0][0] = stof(stair_tmp[i][5]);
					input_middle1_coordinate[0][1] = stof(stair_tmp[i][6]);
					break;
				}
			}
			for (int i = 0; i < MAX_stair; i++) {
				if (stair_tmp[i][0].substr(2, 1) == "1" && stair_tmp[i][0].substr(0, 1) == input_finish.substr(0, 1)) {
					middle2 = stair_tmp[i][0];
					input_middle2_coordinate[0][0] = stof(stair_tmp[i][5]);
					input_middle2_coordinate[0][1] = stof(stair_tmp[i][6]);
					break;
				}
			}
			for (int i = 0; i < MAX_stair; i++) {
				if (stair_tmp[i][0].substr(2, 1) == "2" && stair_tmp[i][0].substr(0, 1) == input_start.substr(0, 1)) {
					middle3 = stair_tmp[i][0];
					input_middle3_coordinate[0][0] = stof(stair_tmp[i][5]);
					input_middle3_coordinate[0][1] = stof(stair_tmp[i][6]);
					break;
				}
			}
			for (int i = 0; i < MAX_stair; i++) {
				if (stair_tmp[i][0].substr(2, 1) == "2" && stair_tmp[i][0].substr(0, 1) == input_finish.substr(0, 1)) {
					middle4 = stair_tmp[i][0];
					input_middle4_coordinate[0][0] = stof(stair_tmp[i][5]);
					input_middle4_coordinate[0][1] = stof(stair_tmp[i][6]);
					break;
				}
			}
			for (int i = 0; i < MAX_stair; i++) {
				if (stair_tmp[i][0].substr(2, 1) == "5" && stair_tmp[i][0].substr(0, 1) == input_start.substr(0, 1)) {
					middle5 = stair_tmp[i][0];
					input_middle5_coordinate[0][0] = stof(stair_tmp[i][5]);
					input_middle5_coordinate[0][1] = stof(stair_tmp[i][6]);
					break;
				}
			}
			for (int i = 0; i < MAX_stair; i++) {
				if (stair_tmp[i][0].substr(2, 1) == "5" && stair_tmp[i][0].substr(0, 1) == input_finish.substr(0, 1)) {
					middle6 = stair_tmp[i][0];
					input_middle6_coordinate[0][0] = stof(stair_tmp[i][5]);
					input_middle6_coordinate[0][1] = stof(stair_tmp[i][6]);
					break;
				}
			}
			//�� ����� �̿����� ���� ���, �Ÿ� ���
			not_same_floor(2, input_start, middle1, middle2, input_finish, intersection_coordinate_all[stoi(input_start.substr(0, 1)) - 1], intersection_coordinate_all[stoi(input_finish.substr(0, 1)) - 1], input_start_coordinate, input_middle1_coordinate, input_middle2_coordinate, input_finish_coordinate, intersection_node_all[stoi(input_start.substr(0, 1)) - 1], intersection_node_all[stoi(input_finish.substr(0, 1)) - 1]);
			not_same_floor2(2, input_start, middle3, middle4, input_finish, intersection_coordinate_all[stoi(input_start.substr(0, 1)) - 1], intersection_coordinate_all[stoi(input_finish.substr(0, 1)) - 1], input_start_coordinate, input_middle3_coordinate, input_middle4_coordinate, input_finish_coordinate, intersection_node_all[stoi(input_start.substr(0, 1)) - 1], intersection_node_all[stoi(input_finish.substr(0, 1)) - 1]);
			not_same_floor3(2, input_start, middle5, middle6, input_finish, intersection_coordinate_all[stoi(input_start.substr(0, 1)) - 1], intersection_coordinate_all[stoi(input_finish.substr(0, 1)) - 1], input_start_coordinate, input_middle5_coordinate, input_middle6_coordinate, input_finish_coordinate, intersection_node_all[stoi(input_start.substr(0, 1)) - 1], intersection_node_all[stoi(input_finish.substr(0, 1)) - 1]);

			//���� ª�� ���� ����� ��
			result_path = r_path(path, path3, path5, dist, dist3, dist5);
			result_dist = r_dist(dist, dist3, dist5);
		}

		//��� -> ���������� -> ��� -> ����
		else if (abs(stoi(input_start.substr(0, 1)) - stoi(input_finish.substr(0, 1))) % 2 == 1 && input_start.substr(0, 1) != "1") {
			floor_st.push_back(stoi(input_start.substr(0, 1)));
			if (stoi(input_start.substr(0, 1)) - stoi(input_finish.substr(0, 1)) < 0) {
				floor_st.push_back(stoi(input_finish.substr(0, 1)) - 1);
			}
			else floor_st.push_back(stoi(input_finish.substr(0, 1)) + 1);
			floor_st.push_back(stoi(input_finish.substr(0, 1)));
			float input_middle7_coordinate[1][2] = { 0 ,0 };
			float input_middle8_coordinate[1][2] = { 0 ,0 };
			float input_middle9_coordinate[1][2] = { 0 ,0 };
			float input_middle10_coordinate[1][2] = { 0 ,0 };
			float input_middle11_coordinate[1][2] = { 0 ,0 };
			float input_middle12_coordinate[1][2] = { 0 ,0 };

			string strr;
			if (stoi(input_start.substr(0, 1)) - stoi(input_finish.substr(0, 1)) < 0) {
				strr = to_string(stoi(input_finish.substr(0, 1)) - 1);
			}
			else strr = to_string(stoi(input_finish.substr(0, 1)) + 1);

			for (int i = 0; i < MAX_elevator; i++) {
				if (elevator_tmp[i][0].substr(2, 1) == "1" && elevator_tmp[i][0].substr(0, 1) == input_start.substr(0, 1)) {
					middle1 = elevator_tmp[i][0];
					input_middle1_coordinate[0][0] = stof(elevator_tmp[i][5]);
					input_middle1_coordinate[0][1] = stof(elevator_tmp[i][6]);
					break;
				}
			}
			for (int i = 0; i < MAX_elevator; i++) {
				if (elevator_tmp[i][0].substr(2, 1) == "1" && elevator_tmp[i][0].substr(0, 1) == strr) {
					middle2 = elevator_tmp[i][0];
					input_middle2_coordinate[0][0] = stof(elevator_tmp[i][5]);
					input_middle2_coordinate[0][1] = stof(elevator_tmp[i][6]);
					break;
				}
			}
			for (int i = 0; i < MAX_elevator; i++) {
				if (elevator_tmp[i][0].substr(2, 1) == "3" && elevator_tmp[i][0].substr(0, 1) == input_start.substr(0, 1)) {
					middle3 = elevator_tmp[i][0];
					input_middle3_coordinate[0][0] = stof(elevator_tmp[i][5]);
					input_middle3_coordinate[0][1] = stof(elevator_tmp[i][6]);
					break;
				}
			}
			for (int i = 0; i < MAX_elevator; i++) {
				if (elevator_tmp[i][0].substr(2, 1) == "3" && elevator_tmp[i][0].substr(0, 1) == strr) {
					middle4 = elevator_tmp[i][0];
					input_middle4_coordinate[0][0] = stof(elevator_tmp[i][5]);
					input_middle4_coordinate[0][1] = stof(elevator_tmp[i][6]);
					break;
				}
			}
			for (int i = 0; i < MAX_elevator; i++) {
				if (elevator_tmp[i][0].substr(2, 1) == "7" && elevator_tmp[i][0].substr(0, 1) == input_start.substr(0, 1)) {
					middle5 = elevator_tmp[i][0];
					input_middle5_coordinate[0][0] = stof(elevator_tmp[i][5]);
					input_middle5_coordinate[0][1] = stof(elevator_tmp[i][6]);
					break;
				}
			}
			for (int i = 0; i < MAX_elevator; i++) {
				if (elevator_tmp[i][0].substr(2, 1) == "7" && elevator_tmp[i][0].substr(0, 1) == strr) {
					middle6 = elevator_tmp[i][0];
					input_middle6_coordinate[0][0] = stof(elevator_tmp[i][5]);
					input_middle6_coordinate[0][1] = stof(elevator_tmp[i][6]);
					break;
				}
			}
			for (int i = 0; i < MAX_stair; i++) {
				if (stair_tmp[i][0].substr(2, 1) == "1" && stair_tmp[i][0].substr(0, 1) == strr) {
					middle7 = stair_tmp[i][0];
					input_middle7_coordinate[0][0] = stof(stair_tmp[i][5]);
					input_middle7_coordinate[0][1] = stof(stair_tmp[i][6]);
					break;
				}
			}
			for (int i = 0; i < MAX_stair; i++) {
				if (stair_tmp[i][0].substr(2, 1) == "1" && stair_tmp[i][0].substr(0, 1) == input_finish.substr(0, 1)) {
					middle8 = stair_tmp[i][0];
					input_middle8_coordinate[0][0] = stof(stair_tmp[i][5]);
					input_middle8_coordinate[0][1] = stof(stair_tmp[i][6]);
					break;
				}
			}
			for (int i = 0; i < MAX_stair; i++) {
				if (stair_tmp[i][0].substr(2, 1) == "2" && stair_tmp[i][0].substr(0, 1) == strr) {
					middle9 = stair_tmp[i][0];
					input_middle9_coordinate[0][0] = stof(stair_tmp[i][5]);
					input_middle9_coordinate[0][1] = stof(stair_tmp[i][6]);
					break;
				}
			}
			for (int i = 0; i < MAX_stair; i++) {
				if (stair_tmp[i][0].substr(2, 1) == "2" && stair_tmp[i][0].substr(0, 1) == input_finish.substr(0, 1)) {
					middle10 = stair_tmp[i][0];
					input_middle10_coordinate[0][0] = stof(stair_tmp[i][5]);
					input_middle10_coordinate[0][1] = stof(stair_tmp[i][6]);
					break;
				}
			}
			for (int i = 0; i < MAX_stair; i++) {
				if (stair_tmp[i][0].substr(2, 1) == "5" && stair_tmp[i][0].substr(0, 1) == strr) {
					middle11 = stair_tmp[i][0];
					input_middle11_coordinate[0][0] = stof(stair_tmp[i][5]);
					input_middle11_coordinate[0][1] = stof(stair_tmp[i][6]);
					break;
				}
			}
			for (int i = 0; i < MAX_stair; i++) {
				if (stair_tmp[i][0].substr(2, 1) == "5" && stair_tmp[i][0].substr(0, 1) == input_finish.substr(0, 1)) {
					middle12 = stair_tmp[i][0];
					input_middle12_coordinate[0][0] = stof(stair_tmp[i][5]);
					input_middle12_coordinate[0][1] = stof(stair_tmp[i][6]);
					break;
				}
			}

			not_same_floor4(input_start, middle1, middle2, middle7, middle8, input_finish, intersection_coordinate_all[stoi(input_start.substr(0, 1)) - 1], intersection_coordinate_all[stoi(strr) - 1], intersection_coordinate_all[stoi(input_finish.substr(0, 1)) - 1], input_start_coordinate, input_middle1_coordinate, input_middle2_coordinate, input_middle7_coordinate, input_middle8_coordinate, input_finish_coordinate, intersection_node_all[stoi(input_start.substr(0, 1)) - 1], intersection_node_all[stoi(strr) - 1], intersection_node_all[stoi(input_finish.substr(0, 1)) - 1]);
			not_same_floor5(input_start, middle1, middle2, middle9, middle10, input_finish, intersection_coordinate_all[stoi(input_start.substr(0, 1)) - 1], intersection_coordinate_all[stoi(strr) - 1], intersection_coordinate_all[stoi(input_finish.substr(0, 1)) - 1], input_start_coordinate, input_middle1_coordinate, input_middle2_coordinate, input_middle9_coordinate, input_middle10_coordinate, input_finish_coordinate, intersection_node_all[stoi(input_start.substr(0, 1)) - 1], intersection_node_all[stoi(strr) - 1], intersection_node_all[stoi(input_finish.substr(0, 1)) - 1]);
			not_same_floor6(input_start, middle1, middle2, middle11, middle12, input_finish, intersection_coordinate_all[stoi(input_start.substr(0, 1)) - 1], intersection_coordinate_all[stoi(strr) - 1], intersection_coordinate_all[stoi(input_finish.substr(0, 1)) - 1], input_start_coordinate, input_middle1_coordinate, input_middle2_coordinate, input_middle11_coordinate, input_middle12_coordinate, input_finish_coordinate, intersection_node_all[stoi(input_start.substr(0, 1)) - 1], intersection_node_all[stoi(strr) - 1], intersection_node_all[stoi(input_finish.substr(0, 1)) - 1]);
			not_same_floor7(input_start, middle3, middle4, middle7, middle8, input_finish, intersection_coordinate_all[stoi(input_start.substr(0, 1)) - 1], intersection_coordinate_all[stoi(strr) - 1], intersection_coordinate_all[stoi(input_finish.substr(0, 1)) - 1], input_start_coordinate, input_middle3_coordinate, input_middle4_coordinate, input_middle7_coordinate, input_middle8_coordinate, input_finish_coordinate, intersection_node_all[stoi(input_start.substr(0, 1)) - 1], intersection_node_all[stoi(strr) - 1], intersection_node_all[stoi(input_finish.substr(0, 1)) - 1]);
			not_same_floor8(input_start, middle3, middle4, middle9, middle10, input_finish, intersection_coordinate_all[stoi(input_start.substr(0, 1)) - 1], intersection_coordinate_all[stoi(strr) - 1], intersection_coordinate_all[stoi(input_finish.substr(0, 1)) - 1], input_start_coordinate, input_middle3_coordinate, input_middle4_coordinate, input_middle9_coordinate, input_middle10_coordinate, input_finish_coordinate, intersection_node_all[stoi(input_start.substr(0, 1)) - 1], intersection_node_all[stoi(strr) - 1], intersection_node_all[stoi(input_finish.substr(0, 1)) - 1]);
			not_same_floor9(input_start, middle3, middle4, middle11, middle12, input_finish, intersection_coordinate_all[stoi(input_start.substr(0, 1)) - 1], intersection_coordinate_all[stoi(strr) - 1], intersection_coordinate_all[stoi(input_finish.substr(0, 1)) - 1], input_start_coordinate, input_middle3_coordinate, input_middle4_coordinate, input_middle11_coordinate, input_middle12_coordinate, input_finish_coordinate, intersection_node_all[stoi(input_start.substr(0, 1)) - 1], intersection_node_all[stoi(strr) - 1], intersection_node_all[stoi(input_finish.substr(0, 1)) - 1]);
			not_same_floor10(input_start, middle5, middle6, middle7, middle8, input_finish, intersection_coordinate_all[stoi(input_start.substr(0, 1)) - 1], intersection_coordinate_all[stoi(strr) - 1], intersection_coordinate_all[stoi(input_finish.substr(0, 1)) - 1], input_start_coordinate, input_middle5_coordinate, input_middle6_coordinate, input_middle7_coordinate, input_middle8_coordinate, input_finish_coordinate, intersection_node_all[stoi(input_start.substr(0, 1)) - 1], intersection_node_all[stoi(strr) - 1], intersection_node_all[stoi(input_finish.substr(0, 1)) - 1]);
			not_same_floor11(input_start, middle5, middle6, middle9, middle10, input_finish, intersection_coordinate_all[stoi(input_start.substr(0, 1)) - 1], intersection_coordinate_all[stoi(strr) - 1], intersection_coordinate_all[stoi(input_finish.substr(0, 1)) - 1], input_start_coordinate, input_middle5_coordinate, input_middle6_coordinate, input_middle9_coordinate, input_middle10_coordinate, input_finish_coordinate, intersection_node_all[stoi(input_start.substr(0, 1)) - 1], intersection_node_all[stoi(strr) - 1], intersection_node_all[stoi(input_finish.substr(0, 1)) - 1]);
			not_same_floor12(input_start, middle5, middle6, middle11, middle12, input_finish, intersection_coordinate_all[stoi(input_start.substr(0, 1)) - 1], intersection_coordinate_all[stoi(strr) - 1], intersection_coordinate_all[stoi(input_finish.substr(0, 1)) - 1], input_start_coordinate, input_middle5_coordinate, input_middle6_coordinate, input_middle11_coordinate, input_middle12_coordinate, input_finish_coordinate, intersection_node_all[stoi(input_start.substr(0, 1)) - 1], intersection_node_all[stoi(strr) - 1], intersection_node_all[stoi(input_finish.substr(0, 1)) - 1]);

			result_path = r_path(r_path(path, path2, path3, dist + tmp, dist2 + tmp, dist3 + tmp), r_path(path4, path5, path6, dist4 + tmp2, dist5 + tmp2, dist6 + tmp2), r_path(path7, path8, path9, dist7 + tmp3, dist8 + tmp3, dist9 + tmp3), r_dist(dist + tmp, dist2 + tmp, dist3 + tmp), r_dist(dist4 + tmp2, dist5 + tmp2, dist6 + tmp2), r_dist(dist7 + tmp3, dist8 + tmp3, dist9 + tmp3));
			result_dist = r_dist(r_dist(dist + tmp, dist2 + tmp, dist3 + tmp), r_dist(dist4 + tmp2, dist5 + tmp2, dist6 + tmp2), r_dist(dist7 + tmp3, dist8 + tmp3, dist9 + tmp3));
		}

		//���� ���������͸� �̿��� �� & �� ���� ���������� ��ǥ�� �̸� ���� -> ���߿� ���
		else {
			floor_st.push_back(stoi(input_start.substr(0, 1)));
			floor_st.push_back(stoi(input_finish.substr(0, 1)));
			for (int i = 0; i < MAX_elevator; i++) {
				if (elevator_tmp[i][0].substr(2, 1) == "1" && elevator_tmp[i][0].substr(0, 1) == input_start.substr(0, 1)) {
					middle1 = elevator_tmp[i][0];
					input_middle1_coordinate[0][0] = stof(elevator_tmp[i][5]);
					input_middle1_coordinate[0][1] = stof(elevator_tmp[i][6]);
					break;
				}
			}
			for (int i = 0; i < MAX_elevator; i++) {
				if (elevator_tmp[i][0].substr(2, 1) == "1" && elevator_tmp[i][0].substr(0, 1) == input_finish.substr(0, 1)) {
					middle2 = elevator_tmp[i][0];
					input_middle2_coordinate[0][0] = stof(elevator_tmp[i][5]);
					input_middle2_coordinate[0][1] = stof(elevator_tmp[i][6]);
					break;
				}
			}
			for (int i = 0; i < MAX_elevator; i++) {
				if (elevator_tmp[i][0].substr(2, 1) == "3" && elevator_tmp[i][0].substr(0, 1) == input_start.substr(0, 1)) {
					middle3 = elevator_tmp[i][0];
					input_middle3_coordinate[0][0] = stof(elevator_tmp[i][5]);
					input_middle3_coordinate[0][1] = stof(elevator_tmp[i][6]);
					break;
				}
			}
			for (int i = 0; i < MAX_elevator; i++) {
				if (elevator_tmp[i][0].substr(2, 1) == "3" && elevator_tmp[i][0].substr(0, 1) == input_finish.substr(0, 1)) {
					middle4 = elevator_tmp[i][0];
					input_middle4_coordinate[0][0] = stof(elevator_tmp[i][5]);
					input_middle4_coordinate[0][1] = stof(elevator_tmp[i][6]);
					break;
				}
			}
			for (int i = 0; i < MAX_elevator; i++) {
				if (elevator_tmp[i][0].substr(2, 1) == "7" && elevator_tmp[i][0].substr(0, 1) == input_start.substr(0, 1)) {
					middle5 = elevator_tmp[i][0];
					input_middle5_coordinate[0][0] = stof(elevator_tmp[i][5]);
					input_middle5_coordinate[0][1] = stof(elevator_tmp[i][6]);
					break;
				}
			}
			for (int i = 0; i < MAX_elevator; i++) {
				if (elevator_tmp[i][0].substr(2, 1) == "7" && elevator_tmp[i][0].substr(0, 1) == input_finish.substr(0, 1)) {
					middle6 = elevator_tmp[i][0];
					input_middle6_coordinate[0][0] = stof(elevator_tmp[i][5]);
					input_middle6_coordinate[0][1] = stof(elevator_tmp[i][6]);
					break;
				}
			}

			//�� ���������͸� ������� ���� ���, �Ÿ� ���
			not_same_floor(1, input_start, middle1, middle2, input_finish, intersection_coordinate_all[stoi(input_start.substr(0, 1)) - 1], intersection_coordinate_all[stoi(input_finish.substr(0, 1)) - 1], input_start_coordinate, input_middle1_coordinate, input_middle2_coordinate, input_finish_coordinate, intersection_node_all[stoi(input_start.substr(0, 1)) - 1], intersection_node_all[stoi(input_finish.substr(0, 1)) - 1]);
			not_same_floor2(1, input_start, middle3, middle4, input_finish, intersection_coordinate_all[stoi(input_start.substr(0, 1)) - 1], intersection_coordinate_all[stoi(input_finish.substr(0, 1)) - 1], input_start_coordinate, input_middle3_coordinate, input_middle4_coordinate, input_finish_coordinate, intersection_node_all[stoi(input_start.substr(0, 1)) - 1], intersection_node_all[stoi(input_finish.substr(0, 1)) - 1]);
			not_same_floor3(1, input_start, middle5, middle6, input_finish, intersection_coordinate_all[stoi(input_start.substr(0, 1)) - 1], intersection_coordinate_all[stoi(input_finish.substr(0, 1)) - 1], input_start_coordinate, input_middle5_coordinate, input_middle6_coordinate, input_finish_coordinate, intersection_node_all[stoi(input_start.substr(0, 1)) - 1], intersection_node_all[stoi(input_finish.substr(0, 1)) - 1]);

			//�� �Ÿ��� �����α��� �ݿ� -> ���� ª�� ��� ��� ������ ����
			result_path = r_path(path, path3, path5, dist + tmp, dist3 + tmp2, dist5 + tmp3);
			result_dist = r_dist(dist + tmp, dist3 + tmp2, dist5 + tmp3);
		}
	}
	//���
	for (int i = 0; i < floor_st.size(); i++) {
		cout << floor_st[i] << "�� -> ";//�̵� �� ����
	}
	cout << endl;
	for (int i = 0; i < result_path.size(); i++) {
		cout << result_path[i].first << ", " << result_path[i].second << " -> ";//�̵� ��� ��ǥ ����
	}
	cout << endl;
	cout << result_dist << "��" << endl;//�Ÿ� ����

	return 0;
}
//���� ���϶��� �ش� ���� ������ ��� ���� �յڿ� ���ǽ� ��带 �߰��ϰ� ���ͽ�Ʈ�� ������ �ִܰ�θ� ���ѰŰ��
//�ٸ� ���϶��� ��� ���� ������ ��� ���� �տ��� ��߰��ǽ� ���, �ڿ��� �̵����ܳ�带 �߰��ϰ�, ���� ���� ������ ��� ���� �տ��� �̵����� ���, �ڿ��� �������ǽ� ��带 �߰��ؼ�
//�׷��� �������� �ٸ� ��ΰ� �����ٵ� �� ������ �� ���� ª�� �Ÿ��� ������ ����ϴ�.
//�̶� �����α��� �Ÿ��� �����ִµ� �⺻������ ���������Ͱ� 4���� ������ �����α�/2�� ���ᱸ��
//�׳� �ܼ��� �Ÿ��� �����α��� �����༭ �ð�+�����α��� ���� ���� ������ ��ζ�� �����߽��ϴ�. �ٵ� ���� �ð� ����Ѱ� �̵����� �̿��� �� �ɸ��� �ð��� �߰� ������ �̴ϴ�! ��� ������� ���� �ָ��ؼ�
//*�߰�*
//Ȧ������ -> ¦�� �� , ¦������ -> Ȧ�� �� �̵��� ������ ���� ���(��� ��, �߰� ��, ���� ��) ex) 3�� -> 8���϶� 7���� �߰� ��, 8�� -> 3�� �϶� 4���� �߰� ��
//�߰����� ���ʹ� ������ ���������� -> ������ -> ��� �̷������� ����(���������Ϳ��� ������ ������� 1���̵�)
//3�� -> 8�� �̵� ��츦 ���캸�� 3�� ��� ���ǽ� -> 3���� �ϳ��� ���������� ���� -> 7������ �̵� -> 7������ 3���� �ϳ��� ��� ���� -> ���������� �̵� -> 8�� ���� ���ǽ� ---> 9���� ����� ��