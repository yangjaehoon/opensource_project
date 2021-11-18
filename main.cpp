#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

string choice[5] = { "환타", "사이다", "콜라", "파워에이드", "소주" };
vector<pair<string, int>> mix;

int main_menu() {
	std::cout << "안녕하세요\n";
	std::cout << "1 : 직접 만드는 조합\n";
	std::cout << "2 : 인기 순위\n";
	std::cout << "3 : 이런 조합은 어떠세요?\n";
	std::cout << "4 : 종료하기\n";
	std::cout << "\n";

	int ret;
	cin >> ret;

	return ret;
}

void first_menu() {
	string recipe_now = "";
	int bev;
	int ml;

	while (1) {
		std::cout << "어떤 음료를 드시겠습니까?" << endl;
		std::cout << "1. 환타 2. 사이다 3. 콜라 4. 파워에이드 5. 소주" << endl;
		std::cout << "(*)을 누르면 종료됩니다." << endl;
		cin >> bev;

		if (bev == int('*')) {
			std::cout << "음료선택을 종료하겠습니다" << endl;
			break;
		}

		recipe_now += choice[bev] + " ";

		std::cout << choice[bev] << "를 얼만큼 따르시겠습니까?" << endl;
		cin >> ml;
		std::cout << "*******" << ml << "만큼 따르고 있습니다!" << "*******" << endl;
		recipe_now += to_string(ml) + " ";
	}

	std::cout << "------------최종레시피-------------" << endl;
	cout << recipe_now << endl;

	int rate = recomm_rate();
	mix.push_back(make_pair(recipe_now, rate));
}

int recomm_rate() {
	std::cout << "맛있게 드셨나요?" << endl;
	std::cout << "체험해본 조합에 대해 이야기해주세요." << endl;

	std::cout << "**************************************" << endl;
	std::cout << "점수는 0점부터 9점까지 줄 수 있습니다!" << endl;

	int score;
	std::cin >> score;

	return score;
}

bool cmp(pair<string, int> a, pair<string, int> b) {
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

	first_menu();	// 첫 번째 메뉴 진입

	cout << endl;

	if (menu == 2) {
		sort(mix.begin(), mix.end(), cmp);

		cout << "이런 조합이 있어요\n\n";

		/*
		for (int i = 0; i < mix.size(); i++)
			cout << i << "  ||  " << mix[v[i].first] << "\n";

		cout << "원하는 조합을 선택해주세요\n";

		int choice;
		cin >> choice;

		cout << "\n" << mix[choice] << " 조합을 선택하였습니다.\n";
		cout << "제조 시작합니다...\n";
		*/

		//여기서부터 이제 붓기 시작함
	}



	return 0;
}
