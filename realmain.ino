#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

string choice[5] = { "Fanta", "Sprite", "CocaCola", "Powerade", "Soju" };
vector<pair<string, int>> mix;

char tmp;

int main_menu() {
  Serial.println("**************************************");
  Serial.println("1 : Customize your Drink!");
  Serial.println("2 : Best Customization");
  Serial.println("3 : Get some Recommendation!");
  Serial.println("4 : Exit");
  Serial.println("");

  char ret;
  Serial.println("What's your choice? : ");
  
  while(1){
    ret = keypad.getKey();
    if(ret)
      break;
  }

  Serial.println("**************************************\n");

  return ret;
}

int recomm_rate() {
  Serial.println("**************************************\n");
  Serial.println("Give a score for your customized drink!\n");
  Serial.println("Score range : (0~9)\n");

  int score;
  Serial.println("Your Score : ");
  while(1){
    tmp = keypad.getKey();
    if(tmp){
      score = int(tmp) - '0';
      break;
    }
  }
  
  Serial.println("Score Uploaded.");
  Serial.println("**************************************\n");

  return score;
}

void first_menu() {
  string recipe_now = "";
  char input;
  int bev;
  char ml;

  Serial.println("**************************************\n");

  while (1) {
    Serial.println("Choose the Beverage!");
    Serial.println("1. Fanta 2. Sprite 3. Coke 4. Powerade 5. Soju\n");
    Serial.println("Press '#' to finish!\n");
    Serial.println("Your Choice : ");

    while(1){
      input = keypad.getKey();
      if(input)
        break;
    }

    Serial.println("");

    if (input == '*') {
      Serial.println("Finish Customizing.");
      break;
    }

    bev = int(input) - '0'; // char to int

    if (bev < 1 || bev > 5) {
      Serial.println("Error!\n");
      continue;
    }

    recipe_now += choice[bev-1] + " ";

    Serial.println((String)"Amount to pour " + choice[bev-1] + (String)"(per 10mL) : "); //std::cout << choice[bev-1] << "를 얼만큼 따르시겠습니까?" << endl << endl;
    
    while(1){
      ml = keypad.getKey();
      if(ml)
        break;
    }
    
    Serial.println("\n**************************************\n");
    recipe_now += ml + 0 + " ";
  }

  Serial.println("------------Your Recipe-------------\n");
  Serial.println(recipe_now)  //cout << recipe_now << endl << endl;
  Serial.println("\n----------------------------------\n");

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

  Serial.println("Recommended Mix\n\n");

  for (int i = 0; i < mix.size(); i++)
    println(i+1 + (String)"  |  " + mix[i].first + "\n"); //std::cout << i+1 << "  |  " << mix[i].first << "\n\n";

  Serial.println("What's your choice? : ");

  int choice;

  while(1){
    tmp = keypad.getKey();
    if(tmp){
      choice = int(tmp) - '0';
      break;
    }
  }

  println("\n" + mix[choice-1].first + (String)" was your choice.\n"); //std::cout << "\n" << mix[choice-1].first << " 조합을 선택하였습니다.\n";
  Serial.println("Start Making...\n\n");

  //여기서부터 이제 붓기 시작함
  //pour_juice(mix[choice-1].first);

  int score = recomm_rate();
  mix[choice-1].second += score;
}

void third_menu() {
  Serial.println("**************************************\n");
  Serial.println("How about these?\n");

  string good_mix[3] = { "Sprite 20 Powerade 20 Soju 40", "CocaCola 30 Soju 50", "Sprite 70 Soju 10" };

  for (int i = 0; i < 3; i++) { // 절대치긴 한데... good_mix의 배열 크기
    Serial.println(i+1 + (String)"  |  "+ good_mix[i] + "\n");//std::cout << i + 1 << "  |  " << good_mix[i] << endl << endl;
  }

  Serial.println("What's your choice? : ");
  int choice;
  
  while(1){
    tmp = keypad.getKey();
    if(tmp){
      choice = int(tmp)-'0';
      break;
    }
  }

  //여기서부터 이제 붓기 시작함
  //pour_juice(good_mix[choice-1]);

  Serial.println("**************************************\n");
}

void pour_juice(string str) {
  Serial.println("**************************************\n");
  Serial.println(str + (String)" is in progress.....\n"); //std::cout << str << "의 조합을 만들고 있습니다......" << endl << endl;
  string temp;
  bool check_type = 1;  // 1이면 음료수, 0이면 ml로 하자
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
      check_type = !check_type; // type 변환
    }
    else {
      temp += str[i];
    }
  }

  Serial.println("Done!\n");
}


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  int checkFinish = 0;  // 종료 조건
  
 if(keypad.getKey())
 {
  char menu = main_menu();
  if(menu)
  {
    Serial.println((String)"if enter  " + menu);
    switch (menu) {
      case '1':
        first_menu(); // 첫 번째 메뉴 진입
        break;
      case '2':
        second_menu();  // 두 번째 메뉴 진입
        break;
      case '3':
        third_menu(); // 세 번째 메뉴 진입
        break;
      case '4':
        Serial.println("**************************************\n");
        Serial.println("Program Ended.\n");
        Serial.println("**************************************\n");
        checkFinish = 1;
        break;
      default:
        Serial.println("rewrite.\n\n");
    }
  
  
    if (checkFinish == 1)
      exit(0);
  }   

}
