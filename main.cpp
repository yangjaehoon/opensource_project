#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

string choice[5] = { "환타", "사이다", "콜라", "파워에이드", "소주" };
vector<pair<string, int>> mix;

int main_menu() {
	std::cout << "**************************************" << endl << endl;
	std::cout << "1 : 직접 만드는 조합\n";
	std::cout << "2 : 인기 순위\n";
	std::cout << "3 : 이런 조합은 어떠세요?\n";
	std::cout << "4 : 종료하기\n";
	std::cout << "\n";

	int ret;
	std::cout << "당신의 선택은 : ";
	cin >> ret;

	std::cout << endl << "**************************************" << endl << endl;

	return ret;
}

int recomm_rate() {
	std::cout << "**************************************" << endl << endl;
	std::cout << "맛있게 드셨나요?" << endl;
	std::cout << "체험해본 조합에 대해 이야기해주세요." << endl << endl;

	std::cout << "점수는 0점부터 9점까지 줄 수 있습니다!" << endl << endl;

	int score;
	std::cout << "당신의 점수는 : ";
	std::cin >> score;
	std::cout << endl << "점수 반영되었습니다." << endl << endl;

	std::cout << "**************************************" << endl << endl;

	return score;
}

void first_menu() {
	string recipe_now = "";
	char input;
	int bev;
	int ml;

	std::cout << "**************************************" << endl;

	while (1) {
		std::cout << "어떤 음료를 드시겠습니까?" << endl << endl;
		std::cout << "1. 환타 2. 사이다 3. 콜라 4. 파워에이드 5. 소주" << endl;
		std::cout << "(*)을 누르면 종료됩니다." << endl << endl;
		std::cout << "당신의 선택은 : ";
		std::cin >> input;

		std::cout << endl;

		if (input == '*') {
			std::cout << "음료선택을 종료하겠습니다" << endl << endl;
			break;
		}

		bev = int(input) - '0';	// char to int

		if (bev < 1 || bev > 5) {
			std::cout << "잘못된 입력입니다." << endl << endl;
			continue;
		}

		recipe_now += choice[bev-1] + " ";

		std::cout << choice[bev-1] << "를 얼만큼 따르시겠습니까?" << endl << endl;
		std::cout << "원하는 만큼 mL 단위로 입력해주세요! : ";
		cin >> ml;
		std::cout << endl << "**************************************" << endl << endl;
		recipe_now += to_string(ml) + " ";
	}

	std::cout << "------------최종레시피-------------" << endl << endl;
	cout << recipe_now << endl << endl;
	std::cout << "-----------------------------------" << endl << endl;

	//pour_juice(recipe_now); 여기서부터 붓기 시작함

	int rate = recomm_rate();
	mix.push_back(make_pair(recipe_now, rate));
}

bool cmp(pair<string, int> a, pair<string, int> b) {
	return a.second > b.second;
}

void second_menu() {
	std::cout << "**************************************" << endl << endl;

	sort(mix.begin(), mix.end(), cmp);

	std::cout << "이런 조합이 있어요\n\n";

	for (int i = 0; i < mix.size(); i++)
		std::cout << i+1 << "  |  " << mix[i].first << "\n\n";

	std::cout << "원하는 조합을 선택해주세요\n\n";

	int choice;
	std::cout << "당신의 조합은? : ";
	std::cin >> choice;

	std::cout << "\n" << mix[choice-1].first << " 조합을 선택하였습니다.\n";
	std::cout << "제조 시작합니다...\n\n";

	//여기서부터 이제 붓기 시작함
	//pour_juice(mix[choice-1].first);

	int score = recomm_rate();
	mix[choice-1].second += score;
}

void third_menu() {
	std::cout << "**************************************" << endl << endl;
	std::cout << "이런 <증명된> 조합도 있어요" << endl << endl;

	string good_mix[3] = { "사이다 20 파워에이드 20 소주 40", "콜라 30 소주 50", "사이다 70 소주 10" };

	for (int i = 0; i < 3; i++) {	// 절대치긴 한데... good_mix의 배열 크기
		std::cout << i + 1 << "  |  " << good_mix[i] << endl << endl;
	}

	std::cout << "당신의 선택은? : ";
	int choice;
	std::cin >> choice;

	//여기서부터 이제 붓기 시작함
	//pour_juice(good_mix[choice-1]);

	std::cout << "**************************************" << endl << endl;
}

void pour_juice(string str) {
	std::cout << "**************************************" << endl << endl;
	std::cout << str << "의 조합을 만들고 있습니다......" << endl << endl;
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

	std::cout << "완성되었습니다." << endl << endl;
}

int main() {

	int checkFinish = 0;	// 종료 조건

	while (1) {
		int menu = main_menu();

		switch (menu) {
		case 1:
			first_menu();	// 첫 번째 메뉴 진입
			break;
		case 2:
			second_menu();	// 두 번째 메뉴 진입
			break;
		case 3:
			third_menu();	// 세 번째 메뉴 진입
			break;
		case 4:
			std::cout << "**************************************" << endl << endl;
			std::cout << "프로그램 종료합니다." << endl << endl;
			std::cout << "이용해주셔서 감사합니다." << endl << endl;
			std::cout << "**************************************" << endl << endl;
			checkFinish = 1;
			break;
		}
		
		if (checkFinish == 1)
			break;
	}


	return 0;
}
