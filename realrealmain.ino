//https://m.blog.naver.com/dokkosam/221750933418
#include <StandardCplusplus.h>
#include <Keypad.h>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;


int waterpump1In = 30;
int waterpump1Out = 31;
int waterpump2In = 32;
int waterpump2Out = 33;
int waterpump3In = 34;
int waterpump3Out = 35;
int waterpump4In = 36;
int waterpump4Out = 37;
int waterpump5In = 38;
int waterpump5Out = 39;

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '7', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {11, 10, 9, 8};
byte colPins[COLS] = {7, 6, 5, 4};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String choice[5] = { "Fanta", "Sprite", "CocaCola", "Powerade", "Soju" };
int waterpumpin[5] = { 30,32, 34, 36,38};
int waterpumpout[5] = {31,33,35,37,39}; 
vector<pair<String, int>> mix;

char tmp;

char main_menu() {
  Serial.println("**************************************");
  Serial.println("1 : Customize your Drink!");
  Serial.println("2 : Best Customization");
  Serial.println("3 : Get some Recommendation!");
  Serial.println("4 : Exit");
  Serial.println("**************************************");
  Serial.print("Choose the menu : ");
  
  char ret;  
  while(1){
    ret = keypad.getKey();
    if(ret)
    {
       Serial.println(ret);
       break;
    }
  }
  
  Serial.println("**************************************");

  return ret;
}

int recomm_rate() {
  Serial.println("**************************************\n");
  Serial.println("Give a score for your customized drink!\n");
  Serial.println("Score range : (0~9)\n");

  int score;
  Serial.print("Your Score : ");
  while(1){
    tmp = keypad.getKey();
    if(tmp){
      score = int(tmp) - '0';
      break;
    }
  }
  Serial.println(score);
  Serial.println("\nScore Uploaded.");
  Serial.println("**************************************\n");

  return score;
}

void first_menu() {
  String recipe_now = "";
  char input;
  int bev;
  char ml;


  while (1) {
    Serial.println("**************************************");
    Serial.println("Choose the Beverage!");
    Serial.println("1. Fanta 2. Sprite 3. Coke 4. Powerade 5. Soju");
    Serial.println("Press '*' to finish!");
    Serial.println("**************************************");
    Serial.print("Your Choice : ");

    while(1){
      input = keypad.getKey();
      if(input)
        break;
    }

    Serial.println(input);

    if (input == '*') {
      Serial.println("Finish Customizing.");
      break;
    }

    bev = int(input) - '0'; // char to int

    if (bev < 1 || bev > 5) {
      Serial.println("Error!\n");
      continue;
    }

    recipe_now += (String)choice[bev-1] + " ";

    Serial.println(choice[bev - 1]); 
    Serial.print("Enter the amount of beverage for your Customization! (per 10mL) : ");
      
    while(1){
      ml = keypad.getKey();
      if(ml)
        break;
    }
    
    String tmpR = (String)ml + (String)"0 ";
    Serial.println(tmpR);
    
    Serial.println("\n**************************************\n");
    recipe_now += tmpR;
  }

  Serial.println("------------Your Recipe-------------\n");
  Serial.println(recipe_now);
  Serial.println("\n----------------------------------\n");

  pour_juice(recipe_now); //여기서부터 붓기 시작함

  int rate = recomm_rate();
  mix.push_back(make_pair(recipe_now, rate));
}

bool cmp(pair<String, int> a, pair<String, int> b) {
  return a.second > b.second;
}

void second_menu() {
  Serial.println("**************************************");

  sort(mix.begin(), mix.end(), cmp);

  Serial.println("Recommended Mix based on users' reviews.\n\n");

  for (int i = 0; i < mix.size(); i++)
    Serial.println(i+1 + (String)"  |  " + mix[i].first + "\n");

  Serial.print("Your Choice : ");

  int input;

  while(1){
    tmp = keypad.getKey();
    if(tmp){
      input = int(tmp) - '0';
      Serial.println(tmp);
      break;
    }
  }
  
  Serial.println(input);

  Serial.println("\n" + mix[input-1].first + (String)" was your input.\n");

  //여기서부터 이제 붓기 시작함
  pour_juice(mix[input-1].first);

  int score = recomm_rate();
  mix[input-1].second += score;
}

void third_menu() {
  Serial.println("**************************************\n");
  Serial.println("How about these?\n");

  String good_mix[3] = { "Sprite 20 Powerade 20 Soju 40", "CocaCola 30 Soju 50", "Sprite 70 Soju 10" };

  for (int i = 0; i < 3; i++) { // 절대치긴 한데... good_mix의 배열 크기
    Serial.println(i+1 + (String)"  |  "+ good_mix[i] + "\n");//std::cout << i + 1 << "  |  " << good_mix[i] << endl << endl;
  }

  Serial.print("Your Choice : ");
  int input;
  
  while(1){
    tmp = keypad.getKey();
    if(tmp){
      input = int(tmp)-'0';
      break;
    }
  }
  
  Serial.println(input);

  //여기서부터 이제 붓기 시작함
  pour_juice(good_mix[input-1]);

  Serial.println("**************************************\n");
}

void pour_juice(String str) {
  Serial.println("**************************************\n");
  Serial.println(str + (String)" is in progress.....\n"); 
  String temp;
  bool check_type = 1;  // 1이면 음료수, 0이면 ml로 하자
  
  for (int i = 0; i < str.length(); i++) {
    int bev_type; // 음료수 종류
    
    if (str[i] == ' ') {
      
                      if (check_type == 1) {
                        // 음료수 선택하기
                        for(int i=0;i<5;i++){
                          if(temp == choice[i])
                            bev_type = i;
                        }
                      }
                      
                      else {
                        // 그 ml만큼 부어
                        int ml = 0;
                        
                        int unit = temp.length();
                        for (int i = 0; i < temp.length(); i++) {
                          ml += (pow(10, unit-1) * temp[i]);
                          unit--;
                        }
                        
                        digitalWrite(waterpumpin[bev_type], HIGH);
                        digitalWrite(waterpumpout[bev_type], LOW);
                        delay(ml*10);

                        Serial.println(ml);

                        digitalWrite(waterpumpin[bev_type], LOW);
                        digitalWrite(waterpumpout[bev_type], LOW);
                      }
                      check_type = !check_type; // type 변환
                      temp = "";

    }
    
    else {
      temp += str[i];
    }
  }

  Serial.println("Done!\n");
}


void setup() {
  // put your setup code here, to run once:
  pinMode(waterpump1In,OUTPUT);
  pinMode(waterpump1Out,OUTPUT);
  pinMode(waterpump2In,OUTPUT);
  pinMode(waterpump2Out,OUTPUT);
  pinMode(waterpump3In,OUTPUT);
  pinMode(waterpump3Out,OUTPUT);
  pinMode(waterpump4In,OUTPUT);
  pinMode(waterpump4Out,OUTPUT);
  pinMode(waterpump5In,OUTPUT);
  pinMode(waterpump5Out,OUTPUT);

 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  int checkFinish = 0;  // 종료 조건
  
 if(keypad.getKey())
 {
  char menu = main_menu();
  if(menu)
  {
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
        Serial.println("Program Ended.");
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
}
