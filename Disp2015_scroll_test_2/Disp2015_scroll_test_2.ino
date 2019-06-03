int i = 4;
int j = 46;
int k;
int y = j;
int lightCount = 48;

void setup() {
  Serial.begin(9600);
  
  for (int z = 0; z < 27; z++){
      Serial.print("20 - ");
      Serial.print(j);
      Serial.println(" = black");
    for (int y = j; y < lightCount; y++){
      Serial.print(y);
      Serial.print(", a[");
      Serial.print(i);
      Serial.println("]");
      i++;
    }
    j--;
    i = 4;
  }
}

void loop() {
  
}
