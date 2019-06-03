int i = 1;
int j = 12;
int k;
int y = j;

void setup() {
  Serial.begin(9600);
  
  for (int z = 0; z < 13; z++){
  for (int x = 0; x < i; x++){
    Serial.print(x);                //setColorOne(x, defaultIntensity, a[y], c[y], l[y]);
    Serial.print(", ");
    Serial.println(y);
    y += 1;
  }

  int k = i;
  Serial.print(k);
  Serial.println(" - 47");
  i++;
  j--;
  y = j;
//  delay(1000);
  }

}

void loop() {
  
}
