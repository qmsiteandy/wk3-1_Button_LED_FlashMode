#define Button_Pin 12
#define LED_Pin 14

//用二微陣列儲存閃爍模式
int flashMode[3][2] = {{100, 100}, //模式一：亮100ms 暗100ms
                       {1500, 250}, //模式二：亮1500ms 暗250ms
                       {500, 1000}};//模式三：亮500ms  暗1000ms
//紀錄現在是第幾個模式
int modeIndex = 0;
//紀錄按鈕是否持續按下
bool btnPressed = false;  

void setup() {
  Serial.begin(115200);
  pinMode(Button_Pin, INPUT);
  pinMode(LED_Pin, OUTPUT);
}


void loop() {
  //偵測當按鈕按下(HIGH),並且按鈕還沒按下，將模式設定為下一個
  if(digitalRead(Button_Pin) == HIGH && btnPressed == false){
    btnPressed = true;
    modeIndex += 1;
    if(modeIndex >= 3) modeIndex = 0; //如果模式超出設定組數，回歸為第0組
  }
  //偵測當按鈕放開(LOW),設定btnPressed為否
  else if(digitalRead(Button_Pin) == LOW && btnPressed == true){
    btnPressed = false;
  }

  //控制LED亮滅
  digitalWrite(LED_Pin, HIGH);
  delay(flashMode[modeIndex][0]);  //從flashMode陣列抓取目前模式亮的時間
  digitalWrite(LED_Pin, LOW);
  delay(flashMode[modeIndex][1]);  //從flashMode陣列抓取目前模式暗的時間
}
