#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
#define MAX 1000
string day[] = { "월", "화", "수", "목", "금", "토" };
string clock[] = { "09:00", "09:15", "09:30", "09:45", 
					"10:00", "10:15", "10:30", "10:45", 
					"11:00", "11:15", "11:30", "11:45", 
					"12:00", "12:15", "12:30", "12:45", 
					"13:00", "13:15", "13:30", "13:45", 
					"14:00", "14:15", "14:30", "14:45", 
					"15:00", "15:15", "15:30", "15:45", 
					"16:00", "16:15", "16:30", "16:45", 
					"17:00", "17:15", "17:30", "17:45", 
					"18:00", "18:15", "18:30", "18:45", "19:00" };

int main() {
	int T;
	cin >> T;
	int test_case = T;
	cin.ignore();

	string room_num[MAX];
	string time_table[MAX];
	int people[910];
	int cnt = 0;

	for (test_case = 0; test_case < T; test_case++) {
		string room;
		getline(cin, room);

		room_num[test_case] += room.substr(room.find(' ') + 1, 3);
		if (room.find("B") <= 50) {
			room_num[test_case] += room.substr(room.find("호") - 1, 1);
		}

		if (room.find('/') <= 50) {
			room.erase(0, room.find('/') + 1);
			room_num[test_case] += room.substr(0, 4);
		}

		cout << room_num[test_case] << endl;
	}

	for (test_case = 0; test_case < T; test_case++) {
		string time;
		string time_;
		getline(cin, time);

		if (time.find('(') <= 100) {
			time_table[test_case] += time.substr(0, 2);
			time_table[test_case] += ' ';
			time_table[test_case] += to_string(find(clock, clock + 41, time.substr(time.find('(') + 1, 5)) - clock);
			time_table[test_case] += ' ';
			time_table[test_case] += to_string(find(clock, clock + 41, time.substr(time.find('~') + 1, 5)) - clock);
			if (time.find('/') <= 100) {
				time.erase(0, time.find('/') + 2);
				time_table[test_case] += ' ';
				time_table[test_case] += time.substr(0, 2);
				time_table[test_case] += ' ';
				time_table[test_case] += to_string(find(clock, clock + 41, time.substr(time.find('(') + 1, 5)) - clock);
				time_table[test_case] += ' ';
				time_table[test_case] += to_string(find(clock, clock + 41, time.substr(time.find('~') + 1, 5)) - clock);
			}
		}

		else {
			time_table[test_case] += time.substr(0, 2);
			time_table[test_case] += ' ';
			if (time.find(',') <= 100 && time.find('/') >= 100) {
				time_table[test_case] += to_string((stoi(time.substr(2, time.length() - 2)) - 1) * 4);
				time_table[test_case] += ' ';
				time_table[test_case] += to_string(stoi(time.substr(time.rfind(',') + 1)) * 4);
			}
			else if (time.find(',') >= 100 && time.find('/') >= 100) {
				time_table[test_case] += to_string((stoi(time.substr(2)) - 1) * 4);
				time_table[test_case] += ' ';
				time_table[test_case] += to_string(stoi(time.substr(2)) * 4);
			}
			else if (time.find('/') <= 100) {
				time_ = time.substr(time.find('/') + 2);
				time.erase(time.find('/') - 1, time.length() - 1);
				if (time.find(',') <= 100) {
					time_table[test_case] += to_string((stoi(time.substr(2, time.length() - 2)) - 1) * 4);
					time_table[test_case] += ' ';
					time_table[test_case] += to_string(stoi(time.substr(time.rfind(',') + 1)) * 4);
				}
				else if (time.find(',') >= 100) {
					time_table[test_case] += to_string((stoi(time.substr(2)) - 1) * 4);
					time_table[test_case] += ' ';
					time_table[test_case] += to_string(stoi(time.substr(2)) * 4);
				}
				time_table[test_case] += ' ';
				time_table[test_case] += time_.substr(0, 2);
				time_table[test_case] += ' ';
				if (time_.find(',') <= 100) {
					time_table[test_case] += to_string((stoi(time_.substr(2, time_.length() - 2)) - 1) * 4);
					time_table[test_case] += ' ';
					time_table[test_case] += to_string(stoi(time_.substr(time_.rfind(',') + 1)) * 4);
				}
				else if (time_.find(',') >= 100) {
					time_table[test_case] += to_string((stoi(time_.substr(2)) - 1) * 4);
					time_table[test_case] += ' ';
					time_table[test_case] += to_string(stoi(time_.substr(2)) * 4);
				}
			}
		}
	}

	for (test_case = 0; test_case < T; test_case++) {
		cin >> people[test_case];
	}

	FILE *fp = fopen("temp_.csv", "w+");

	for (int i = 0; i < T; i++) {
		//강의실 두개 시간 두개
		if (room_num[i].find(' ') <= 100 && time_table[i].length() > 10) {
			fprintf(fp, "%s,%s,%d\n", room_num[i].substr(0, room_num[i].find(' ')).c_str(), time_table[i].substr(0, time_table[i].find(' ', 6)).c_str(), people[i]);
			fprintf(fp, "%s,%s,%d\n", room_num[i].substr(room_num[i].find(' '), room_num[i].length() - 1).c_str(), time_table[i].substr(time_table[i].find(' ', 6) + 1, time_table[i].length() - 1).c_str(), people[i]);
		}
		//강의실 한개 시간 두개
		else if (room_num[i].find(' ') >= 100 && time_table[i].length() > 10) {
			fprintf(fp, "%s,%s,%d\n", room_num[i].c_str(), time_table[i].substr(0, time_table[i].find(' ', 6)).c_str(), people[i]);
			fprintf(fp, "%s,%s,%d\n", room_num[i].c_str(), time_table[i].substr(time_table[i].find(' ', 6) + 1, time_table[i].length() - 1).c_str(), people[i]);
		}
		else fprintf(fp, "%s,%s,%d\n", room_num[i].c_str(), time_table[i].c_str(), people[i]);
	}

	fclose(fp);

	return 0;
}