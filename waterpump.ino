const int bvg1 = 6; // 수중모터 펌프 핀번호 
 
void setup(){
    pinMode(pwmPin, OUTPUT);
}
 
void loop(){

        analogWrite(pwmPin, 0);// 속도 조절 0
        delay(5000); // 
        analogWrite(pwmPin, 255);
        delay(5000); // 
  /*
    for(int i = 0; i <= 255 ; i++)
    {
        analogWrite(pwmPin, i);
        delay(40); // 속도 천천히
    }
    for(int i = 255; i >= 0 ; i--)
    {
        analogWrite(pwmPin, i);
        delay(40); // 속도 천천히
    }

    */
}
