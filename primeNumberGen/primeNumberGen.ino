boolean prime = true;
unsigned int input = 100;
unsigned int inputTemp = 100;
unsigned int num = 2;

void setup() {
  Serial.begin(9600);
}
  

void loop() {
  if (Serial.available() > 0){
    inputTemp = Serial.parseInt();
    if (inputTemp > 0){
      Serial.println();
      input = inputTemp;
      num = 2;
      prime = true;
    }
  }
  if (num < input){
    for (unsigned int d = 2; d <= num/2; d++){
      if (num % d > 0) prime = true;
      else if (num % d == 0){
        prime = false;
        goto bailout;
      }
    }
    bailout:
    if (prime == true) Serial.println(num);
    num++;
  }
}
