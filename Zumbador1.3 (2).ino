int red = A2;
int green = A3;
int button1 = 6;
int button2 = 7;

int zumb1 = A4;
int zumb2 = A5;

int cleared = 1;
int lvl = 3;
int counter = 0;

int sequence[10];

int song1[] = {500} ;
int song2[] = {200} ;
int correctSong[] = {400, 400, 600};
int wrongSong[] = {200,200,200};

void setup() {

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);  
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);

  pinMode(zumb1, OUTPUT);
  pinMode(zumb2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < lvl; i++) {
    resetLeds();
    int selectedNumber = random(1, 3);
    ShowLedAndZumb(selectedNumber);
      
    sequence[i] = selectedNumber;
    Serial.println(String(selectedNumber));
    delay(1000);
  }

  resetLeds();

  waitForInput();
}


void waitForInput() {
  int counter = 0;
  while (counter < lvl) {
    int pulsado1 = digitalRead(button1);
    int pulsado2 = digitalRead(button2);
    if (pulsado1 == HIGH) {
      Serial.println(sequence[counter]);
      zumb1Song();
      if (sequence[counter] != 1) {
        wrong();
        break;
      }
      else {
          Serial.println("CORRECT");
        counter++;
      }

    }

    if (pulsado2 == HIGH) {
      Serial.println(sequence[counter]);
      zumb2Song();
      if (sequence[counter] != 2) {
        wrong();
        break;
      }
      else {
          Serial.println("CORRECT");
        counter++;
      }

    }
  }

  if (counter == lvl) {
    lvl++;
    lvlUp();
    Serial.println("LEVEL UP!");
  }
  else {
    Serial.println("LEVEL 3 AGAIN!");
    lvl = 3;
  }

}

void resetLeds() {
  analogWrite(red,LOW);
  analogWrite(green, LOW);
  //delay(1000);
}

void lvlUp() {
   for (int i = 0; i < 10; i++) {
    digitalWrite(green, HIGH);
    delay(100);
    digitalWrite(green, LOW);
  }
  digitalWrite(green, HIGH);
  delay(500);
  digitalWrite(green, LOW);
  playCorrectSong();
}

void wrong(){
  Serial.println("WRONG");
  for (int i = 0; i < 10; i++) {
    digitalWrite(red, HIGH);
    delay(100);
    digitalWrite(red, LOW);
  }
  digitalWrite(red, HIGH);
  delay(500);
  digitalWrite(red, LOW);
  playWrongSong();
}

void ShowLedAndZumb(int selectedNumber){
   if(selectedNumber ==1){
    analogWrite(red, 200); //analogWrite(red, HIGH);
    zumb1Song();
   }
   else{ // 2
    analogWrite(green , 200);
    zumb2Song();
   }
}

void zumb1Song(){
for (int i = 0;i < sizeof(song1)/sizeof(song1[0]); i++){
      tone(zumb1, song1[i]);
      delay(500);
    }
    noTone(zumb1);
}

void zumb2Song(){
for (int i = 0;i < sizeof(song2)/sizeof(song2[0]); i++){
      tone(zumb2, song2[i]);
      delay(500);
    }
    noTone(zumb2);
}

void playCorrectSong(){
int songSize =  sizeof(correctSong)/sizeof(correctSong[0]);
  
for (int i = 0;i < songSize -1; i++){
      tone(zumb1, correctSong[i]);
      delay(500);
    }
    tone(zumb1, correctSong[songSize-1]);
    delay(1000);
    noTone(zumb1);
}

void playWrongSong(){
int songSize =  sizeof(wrongSong)/sizeof(wrongSong[0]);
  
for (int i = 0;i < songSize -1; i++){
      tone(zumb1, wrongSong[i]);
      delay(500);
    }
    tone(zumb1, wrongSong[songSize-1]);
    delay(1000);
    noTone(zumb1);
}

