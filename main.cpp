#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

string choice[5] = { "환타", "사이다", "콜라", "파워에이드", "소주" };
vector<pair<string, int>> mix;

int main_menu() {
	Serial.println("**************************************");
	Serial.println("1 : 직접 만드는 조합");
	Serial.println("2 : 인기 순위");
	Serial.println("3 : 이런 조합은 어떠세요?");
	Serial.println("4 : 종료하기");
	Serial.println("");

	int ret;
	Serial.println("당신의 선택은 : ");
	ret = (int)keypad.getKey();

	Serial.println("**************************************\n");

	return ret;
}

int recomm_rate() {
	Serial.println("**************************************\n");
	Serial.println("맛있게 드셨나요?");
	Serial.println("체험해본 조합에 대해 이야기해주세요.\n");

	Serial.println("점수는 0점부터 9점까지 줄 수 있습니다!\n");

	int score;
	Serial.println("당신의 점수는 : ");
	score = (int)keypad.getKey();
	Serial.println("점수 반영되었습니다.");

	Serial.println("**************************************\n");

	return score;
}

void first_menu() {
	string recipe_now = "";
	char input;
	int bev;
	int ml;

	Serial.println("**************************************\n");

	while (1) {
		Serial.println( "어떤 음료를 드시겠습니까?\n");
		Serial.println("1. 환타 2. 사이다 3. 콜라 4. 파워에이드 5. 소주\n");
		Serial.println("(*)을 누르면 종료됩니다.\n");
		Serial.println("당신의 선택은 : ");
		input = keypad.getKey();

		Serial.println("");

		if (input == '*') {
			Serial.println("음료선택을 종료하겠습니다");
			break;
		}

		bev = int(input) - '0';	// char to int

		if (bev < 1 || bev > 5) {
			Serial.println("잘못된 입력입니다.\n");
			continue;
		}

		recipe_now += choice[bev-1] + " ";

		std::cout << choice[bev-1] << "를 얼만큼 따르시겠습니까?" << endl << endl;
		Serial.println("원하는 만큼 mL 단위로 입력해주세요! : ");
		ml = (int)keypad.getKey();
		Serial.println("\n**************************************\n");
		recipe_now += to_string(ml) + " ";
	}

	Serial.println("------------최종레시피-------------\n");
	cout << recipe_now << endl << endl;
	Serial.println("-----------------------------------\n");

	//pour_juice(recipe_now); 여기서부터 붓기 시작함

	int rate = recomm_rate();
	mix.push_back(make_pair(recipe_now, rate));
}

bool cmp(pair<string, int> a, pair<string, int> b) {
	return a.second > b.second;
}

void second_menu() {
	Serial.println("**************************************");

	sort(mix.begin(), mix.end(), cmp);

	Serial.println("이런 조합이 있어요\n\n");

	for (int i = 0; i < mix.size(); i++)
		std::cout << i+1 << "  |  " << mix[i].first << "\n\n";

	Serial.println("원하는 조합을 선택해주세요\n\n");

	int choice;
	Serial.println("당신의 조합은? : ");
	choice = (int)keypad.getKey();

	std::cout << "\n" << mix[choice-1].first << " 조합을 선택하였습니다.\n";
	Serial.println("제조 시작합니다...\n\n");

	//여기서부터 이제 붓기 시작함
	//pour_juice(mix[choice-1].first);

	int score = recomm_rate();
	mix[choice-1].second += score;
}

void third_menu() {
	Serial.println("**************************************\n");
	std::cout << "이런 <증명된> 조합도 있어요" << endl << endl;

	string good_mix[3] = { "사이다 20 파워에이드 20 소주 40", "콜라 30 소주 50", "사이다 70 소주 10" };

	for (int i = 0; i < 3; i++) {	// 절대치긴 한데... good_mix의 배열 크기
		std::cout << i + 1 << "  |  " << good_mix[i] << endl << endl;
	}

	Serial.println("당신의 선택은? : ");
	int choice;
	choice = (int)keypad.getKey();

	//여기서부터 이제 붓기 시작함
	//pour_juice(good_mix[choice-1]);

	Serial.println("**************************************\n");
}

void pour_juice(string str) {
	Serial.println("**************************************\n");
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

	Serial.println("완성되었습니다.\n");
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
			Serial.println("**************************************\n");
			Serial.println("프로그램 종료합니다.\n");
			Serial.println("이용해주셔서 감사합니다.\n");
			Serial.println("**************************************\n");
			checkFinish = 1;
			break;
		default:
			Serial.println("다시 입력해주세요.\n\n");
		}
		
		
		if (checkFinish == 1)
			break;
	}


	return 0;
}
