#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

int main_menu() {
	cout << "안녕하세요\n";
	cout << "1 : 직접 만드는 조합\n";
	cout << "2 : 인기 순위\n";
	cout << "3 : 이런 조합은 어떠세요?\n";
	cout << "4 : 종료하기\n";
	cout << "\n";

	int ret;
	cin >> ret;

	return ret;
}

bool cmp(pair<int, int> a, pair<int, int> b) {
	return a.second > b.second;
}

void pour_juice(string str) {
	string temp;
	bool check_type = 1;	// 1이면 음료수, 0이면 ml로 하자
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == ' ') {
			if (check_type == 1) {
				// 음료수 선택하기
			}
			else {
				// 그 ml만큼 부어
				int ml = 0;
				
				int unit = temp.length();
				for (int i = 0; i < temp.length(); i++) {
					ml += (pow(10, unit - 1) * temp[i]);
					unit--;
				}
			}
			check_type = !check_type;	// type 변환
		}
		else {
			temp += str[i];
		}
	}
}

int main() {

	int menu = main_menu();

	vector<string> mix;	// 여기에 조합 저장해둘거임

	vector<pair<int, int>> v;	// <조합의 index, 주문 횟수>
	for (int i = 0; i < 10; i++) {
		v.push_back(make_pair(i, i % 5));
	}

	for (int i = 0; i < 10; i++) {
		string tmp;
		if (i <= 5)
			tmp = "안녕하세요";
		else
			tmp = "잘가삼ㅋ";

		mix.push_back(tmp);
	}

	/*

	for (int i = 0; i < mix.size(); i++)
		cout << mix[i] << endl;

	*/

	cout << endl;

	if (menu == 2) {
		sort(v.begin(), v.end(), cmp);

		cout << "이런 조합이 있어요\n\n";

		for (int i = 0; i < v.size(); i++)
			cout << i << "  ||  " << mix[v[i].first] << "\n";

		cout << "원하는 조합을 선택해주세요\n";

		int choice;
		cin >> choice;

		cout << "\n" << mix[choice] << " 조합을 선택하였습니다.\n";
		cout << "제조 시작합니다...\n";

		//여기서부터 이제 붓기 시작함
	}



	return 0;
}