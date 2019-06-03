#define redPin 3
#define greenPin 5
#define bluePin 10

int delayTime = 50;
int delayTime2 = 10000;

void setup(){
  
  delay(1000);
  for (int i = 0; i < 14; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }

  
  analogWrite(redPin, 255);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);
  
  delay(delayTime2);
  
}

void loop(){
  digitalWrite(greenPin, HIGH);
  for (int i = 255; i >= 0; i--){      //transition to green
    analogWrite(redPin, i);
    analogWrite(bluePin, i);
    delay(delayTime);
  }
  
//  digitalWrite(3, LOW);
//  digitalWrite(6, LOW);
  delay(delayTime2);
  
  for (int i = 0; i <= 255; i++){      //transition to blue
    analogWrite(bluePin, i);
    analogWrite(greenPin, 255 - i);
    delay(delayTime);
  }
  
//  digitalWrite(3, LOW);
//  digitalWrite(5, LOW);
  delay(delayTime2);
  
  for (int i = 0; i <= 255; i++){      //transition to white
    analogWrite(redPin, i);
    analogWrite(greenPin, i);
    delay(delayTime);
  }
  
//  digitalWrite(3, HIGH);
//  digitalWrite(5, HIGH);
//  digitalWrite(6, HIGH);
  delay(delayTime2);
  
  /*
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
  delay(1000);
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
  delay(1000);
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
  delay(1000);
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
  delay(1000);
  
  
  digitalWrite(redPin, HIGH);
  //digitalWrite(greenPin, HIGH);
  //digitalWrite(bluePin, HIGH);
  delay(1000);
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
  delay(1000);
  //digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  //digitalWrite(bluePin, HIGH);
  delay(1000);
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
  delay(1000);
  //digitalWrite(redPin, HIGH);
  //digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
  delay(1000);
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
  delay(1000);
  */
  
}
