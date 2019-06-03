//LiquidCrystsl(RS, enable, D4, D5, D6, D7
LiquidCrystal lcd(6, 8, 9, 10, 11, 12);

int numChars = 0;

int katakana(int (*syllable)()){
  numChars = 0;
  numChars += syllable();
  Serial.print(", katakana characters: ");
  Serial.println(numChars);
  return numChars;
}

int katakana(int (*syllable)(), int (*syllable2)()){
  numChars = 0;
  numChars += syllable();
  numChars += syllable2();
  Serial.print(", katakana characters: ");
  Serial.println(numChars);
  return numChars;
}

int katakana(int (*syllable)(), int (*syllable2)(), int (*syllable3)()){
  numChars = 0;
  numChars += syllable();
  numChars += syllable2();
  numChars += syllable3();
  Serial.print(", katakana characters: ");
  Serial.println(numChars);
  return numChars;
}

int katakana(int (*syllable)(), int (*syllable2)(), int (*syllable3)(), int (*syllable4)()){
  numChars = 0;
  numChars += syllable();
  numChars += syllable2();
  numChars += syllable3();
  numChars += syllable4();
  Serial.print(", katakana characters: ");
  Serial.println(numChars);
  return numChars;
}

int katakana(int (*syllable)(), int (*syllable2)(), int (*syllable3)(), int (*syllable4)(), int (*syllable5)()){
  numChars = 0;
  numChars += syllable();
  numChars += syllable2();
  numChars += syllable3();
  numChars += syllable4();
  numChars += syllable5();
  Serial.print(", katakana characters: ");
  Serial.println(numChars);
  return numChars;
}

int katakana(int (*syllable)(), int (*syllable2)(), int (*syllable3)(), int (*syllable4)(), int (*syllable5)(), int (*syllable6)()){
  numChars = 0;
  numChars += syllable();
  numChars += syllable2();
  numChars += syllable3();
  numChars += syllable4();
  numChars += syllable5();
  numChars += syllable6();
  Serial.print(", katakana characters: ");
  Serial.println(numChars);
  return numChars;
}

int katakana(int (*syllable)(), int (*syllable2)(), int (*syllable3)(), int (*syllable4)(), int (*syllable5)(), int (*syllable6)(), int (*syllable7)()){
  numChars = 0;
  numChars += syllable();
  numChars += syllable2();
  numChars += syllable3();
  numChars += syllable4();
  numChars += syllable5();
  numChars += syllable6();
  numChars += syllable7();
  Serial.print(", katakana characters: ");
  Serial.println(numChars);
  return numChars;
}

int katakana(int (*syllable)(), int (*syllable2)(), int (*syllable3)(), int (*syllable4)(), int (*syllable5)(), int (*syllable6)(), int (*syllable7)(), int (*syllable8)()){
  numChars = 0;
  numChars += syllable();
  numChars += syllable2();
  numChars += syllable3();
  numChars += syllable4();
  numChars += syllable5();
  numChars += syllable6();
  numChars += syllable7();
  numChars += syllable8();
  Serial.print(", katakana characters: ");
  Serial.println(numChars);
  return numChars;
}


int wo(){
  lcd.write(166);
  Serial.print("wo");
  return 1; // number of katakana characters needed to print to the lcd
}

int a(){
  lcd.write(177);
  Serial.print("a");
  return 1; // number of katakana characters needed to print to the lcd
}

int i(){
  lcd.write(178);
  Serial.print("i");
  return 1; // number of katakana characters needed to print to the lcd
}

int u(){
  lcd.write(179);
  Serial.print("u");
  return 1; // number of katakana characters needed to print to the lcd
}

int e(){
  lcd.write(180);
  Serial.print("e");
  return 1; // number of katakana characters needed to print to the lcd
}

int o(){
  lcd.write(181);
  Serial.print("o");
  return 1; // number of katakana characters needed to print to the lcd
}

int ka(){
  lcd.write(182);
  Serial.print("ka");
  return 1; // number of katakana characters needed to print to the lcd
}

int ki(){
  lcd.write(183);
  Serial.print("ki");
  return 1; // number of katakana characters needed to print to the lcd
}

int ku(){
  lcd.write(184);
  Serial.print("ku");
  return 1; // number of katakana characters needed to print to the lcd
}

int ke(){
  lcd.write(185);
  Serial.print("ke");
  return 1; // number of katakana characters needed to print to the lcd
}

int ko(){
  lcd.write(186);
  Serial.print("ko");
  return 1; // number of katakana characters needed to print to the lcd
}

int sa(){
  lcd.write(187);
  Serial.print("sa");
  return 1; // number of katakana characters needed to print to the lcd
}

int si(){
  lcd.write(188);
  Serial.print("si");
  return 1; // number of katakana characters needed to print to the lcd
}

int shi(){
  lcd.write(188);
  Serial.print("shi");
  return 1; // number of katakana characters needed to print to the lcd
}

int su(){
  lcd.write(189);
  Serial.print("su");
  return 1; // number of katakana characters needed to print to the lcd
}

int se(){
  lcd.write(190);
  Serial.print("se");
  return 1; // number of katakana characters needed to print to the lcd
}

int so(){
  lcd.write(191);
  Serial.print("so");
  return 1; // number of katakana characters needed to print to the lcd
}

int ta(){
  lcd.write(192);
  Serial.print("ta");
  return 1; // number of katakana characters needed to print to the lcd
}

int ti(){
  lcd.write(193);
  Serial.print("ti");
  return 1; // number of katakana characters needed to print to the lcd
}

int chi(){
  lcd.write(193);
  Serial.print("chi");
  return 1; // number of katakana characters needed to print to the lcd
}

int tu(){
  lcd.write(194);
  Serial.print("tu");
  return 1; // number of katakana characters needed to print to the lcd
}

int tsu(){
  lcd.write(194);
  Serial.print("tsu");
  return 1; // number of katakana characters needed to print to the lcd
}

int te(){
  lcd.write(195);
  Serial.print("te");
  return 1; // number of katakana characters needed to print to the lcd
}

int to(){
  lcd.write(196);
  Serial.print("to");
  return 1; // number of katakana characters needed to print to the lcd
}

int na(){
  lcd.write(197);
  Serial.print("na");
  return 1; // number of katakana characters needed to print to the lcd
}

int ni(){
  lcd.write(198);
  Serial.print("ni");
  return 1; // number of katakana characters needed to print to the lcd
}

int nu(){
  lcd.write(199);
  Serial.print("nu");
  return 1; // number of katakana characters needed to print to the lcd
}

int ne(){
  lcd.write(200);
  Serial.print("ne");
  return 1; // number of katakana characters needed to print to the lcd
}

int no(){
  lcd.write(201);
  Serial.print("no");
  return 1; // number of katakana characters needed to print to the lcd
}

int ha(){
  lcd.write(202);
  Serial.print("ha");
  return 1; // number of katakana characters needed to print to the lcd
}

int hi(){
  lcd.write(203);
  Serial.print("hi");
  return 1; // number of katakana characters needed to print to the lcd
}

int hu(){
  lcd.write(204);
  Serial.print("hu");
  return 1; // number of katakana characters needed to print to the lcd
}

int fu(){
  lcd.write(204);
  Serial.print("fu");
  return 1; // number of katakana characters needed to print to the lcd
}

int he(){
  lcd.write(205);
  Serial.print("he");
  return 1; // number of katakana characters needed to print to the lcd
}

int ho(){
  lcd.write(206);
  Serial.print("ho");
  return 1; // number of katakana characters needed to print to the lcd
}

int ma(){
  lcd.write(207);
  Serial.print("ma");
  return 1; // number of katakana characters needed to print to the lcd
}

int mi(){
  lcd.write(208);
  Serial.print("mi");
  return 1; // number of katakana characters needed to print to the lcd
}

int mu(){
  lcd.write(209);
  Serial.print("mu");
  return 1; // number of katakana characters needed to print to the lcd
}

int me(){
  lcd.write(210);
  Serial.print("me");
  return 1; // number of katakana characters needed to print to the lcd
}

int mo(){
  lcd.write(211);
  Serial.print("mo");
  return 1; // number of katakana characters needed to print to the lcd
}

int ya(){
  lcd.write(212);
  Serial.print("ya");
  return 1; // number of katakana characters needed to print to the lcd
}

int yu(){
  lcd.write(213);
  Serial.print("yu");
  return 1; // number of katakana characters needed to print to the lcd
}

int yo(){
  lcd.write(214);
  Serial.print("yo");
  return 1; // number of katakana characters needed to print to the lcd
}

int ra(){
  lcd.write(215);
  Serial.print("ra");
  return 1; // number of katakana characters needed to print to the lcd
}

int ri(){
  lcd.write(216);
  Serial.print("ri");
  return 1; // number of katakana characters needed to print to the lcd
}

int ru(){
  lcd.write(217);
  Serial.print("ru");
  return 1; // number of katakana characters needed to print to the lcd
}

int re(){
  lcd.write(218);
  Serial.print("re");
  return 1; // number of katakana characters needed to print to the lcd
}

int ro(){
  lcd.write(219);
  Serial.print("ro");
  return 1; // number of katakana characters needed to print to the lcd
}

int wa(){
  lcd.write(220);
  Serial.print("wa");
  return 1; // number of katakana characters needed to print to the lcd
}

int n(){
  lcd.write(221);
  Serial.print("n");
  return 1; // number of katakana characters needed to print to the lcd
}

int ga(){
  lcd.write(182); // ka
  lcd.write(222);
  Serial.print("ka");
  return 2; // number of katakana characters needed to print to the lcd
}

int gi(){
  lcd.write(183); // ki
  lcd.write(222);
  Serial.print("gi");
  return 2; // number of katakana characters needed to print to the lcd
}

int gu(){
  lcd.write(184); // ku
  lcd.write(222);
  Serial.print("gu");
  return 2; // number of katakana characters needed to print to the lcd
}

int ge(){
  lcd.write(185); // ke
  lcd.write(222);
  Serial.print("ge");
  return 2; // number of katakana characters needed to print to the lcd
}

int go(){
  lcd.write(186); // ko
  lcd.write(222);
  Serial.print("go");
  return 2; // number of katakana characters needed to print to the lcd
}

int za(){
  lcd.write(187); // sa
  lcd.write(222);
  Serial.print("za");
  return 2; // number of katakana characters needed to print to the lcd
}

int zi(){
  lcd.write(188); // si
  lcd.write(222);
  Serial.print("zi");
  return 2; // number of katakana characters needed to print to the lcd
}

int zu(){
  lcd.write(189); // su
  lcd.write(222);
  Serial.print("zu");
  return 2; // number of katakana characters needed to print to the lcd
}

int ze(){
  lcd.write(190); // se
  lcd.write(222);
  Serial.print("ze");
  return 2; // number of katakana characters needed to print to the lcd
}

int zo(){
  lcd.write(191); // so
  lcd.write(222);
  Serial.print("zo");
  return 2; // number of katakana characters needed to print to the lcd
}

int da(){
  lcd.write(192); // ta
  lcd.write(222);
  Serial.print("da");
  return 2; // number of katakana characters needed to print to the lcd
}

int di(){
  lcd.write(193); // ti
  lcd.write(222);
  Serial.print("di");
  return 2; // number of katakana characters needed to print to the lcd
}

int du(){
  lcd.write(194); // tu
  lcd.write(222);
  Serial.print("du");
  return 2; // number of katakana characters needed to print to the lcd
}

int de(){
  lcd.write(195); // te
  lcd.write(222);
  Serial.print("de");
  return 2; // number of katakana characters needed to print to the lcd
}

int doh(){
  lcd.write(196); // to
  lcd.write(222);
  Serial.print("doh");
  return 2; // number of katakana characters needed to print to the lcd
}

int ba(){
  lcd.write(202); // ha
  lcd.write(222);
  Serial.print("ba");
  return 2; // number of katakana characters needed to print to the lcd
}

int bi(){
  lcd.write(203); // hi
  lcd.write(222);
  Serial.print("bi");
  return 2; // number of katakana characters needed to print to the lcd
}

int bu(){
  lcd.write(204); // hu
  lcd.write(222);
  Serial.print("bu");
  return 2; // number of katakana characters needed to print to the lcd
}

int be(){
  lcd.write(205); // he
  lcd.write(222);
  Serial.print("be");
  return 2; // number of katakana characters needed to print to the lcd
}

int bo(){
  lcd.write(206); // ho
  lcd.write(222);
  Serial.print("bo");
  return 2; // number of katakana characters needed to print to the lcd
}

int pa(){
  lcd.write(202); // ha
  lcd.write(223);
  Serial.print("pa");
  return 2; // number of katakana characters needed to print to the lcd
}

int pi(){
  lcd.write(203); // 203
  lcd.write(223);
  Serial.print("pi");
  return 2; // number of katakana characters needed to print to the lcd
}

int pu(){
  lcd.write(204); // hu
  lcd.write(223);
  Serial.print("pu");
  return 2; // number of katakana characters needed to print to the lcd
}

int pe(){
  lcd.write(205); // he
  lcd.write(223);
  Serial.print("pe");
  return 2; // number of katakana characters needed to print to the lcd
}

int po(){
  lcd.write(206); // ho
  lcd.write(223);
  Serial.print("po");
  return 2; // number of katakana characters needed to print to the lcd
}

int kya(){
  lcd.write(183); // ki
  lcd.write(172);
  Serial.print("kya");
  return 2; // number of katakana characters needed to print to the lcd
}

int kyu(){
  lcd.write(183); // ki
  lcd.write(173);
  Serial.print("kyu");
  return 2; // number of katakana characters needed to print to the lcd
}

int kyo(){
  lcd.write(183); // ki
  lcd.write(174);
  Serial.print("kyo");
  return 2; // number of katakana characters needed to print to the lcd
}

int sha(){
  lcd.write(188); // si
  lcd.write(172);
  Serial.print("sha");
  return 2; // number of katakana characters needed to print to the lcd
}

int shu(){
  lcd.write(188); // si
  lcd.write(173);
  Serial.print("shu");
  return 2; // number of katakana characters needed to print to the lcd
}

int she(){
  lcd.write(188); // si
  lcd.write(170);
  Serial.print("she");
  return 2; // number of katakana characters needed to print to the lcd
}

int sho(){
  lcd.write(188); // si
  lcd.write(174);
  Serial.print("sho");
  return 2; // number of katakana characters needed to print to the lcd
}

int cha(){
  lcd.write(193); // chi
  lcd.write(172);
  Serial.print("cha");
  return 2; // number of katakana characters needed to print to the lcd
}

int chu(){
  lcd.write(193); // chi
  lcd.write(173);
  Serial.print("chu");
  return 2; // number of katakana characters needed to print to the lcd
}

int che(){
  lcd.write(193); // chi
  lcd.write(170);
  Serial.print("che");
  return 2; // number of katakana characters needed to print to the lcd
}

int cho(){
  lcd.write(193); // chi
  lcd.write(174);
  Serial.print("cho");
  return 2; // number of katakana characters needed to print to the lcd
}

int nya(){
  lcd.write(198); // ni
  lcd.write(172);
  Serial.print("nya");
  return 2; // number of katakana characters needed to print to the lcd
}

int nyu(){
  lcd.write(198); // ni
  lcd.write(173);
  Serial.print("nyu");
  return 2; // number of katakana characters needed to print to the lcd
}

int nyo(){
  lcd.write(198); // ni
  lcd.write(174);
  Serial.print("nyo");
  return 2; // number of katakana characters needed to print to the lcd
}

int hya(){
  lcd.write(203); // hi
  lcd.write(172);
  Serial.print("hya");
  return 2; // number of katakana characters needed to print to the lcd
}

int hyu(){
  lcd.write(203); // hi
  lcd.write(173);
  Serial.print("hyu");
  return 2; // number of katakana characters needed to print to the lcd
}

int hyo(){
  lcd.write(203); // hi
  lcd.write(174);
  Serial.print("hyo");
  return 2; // number of katakana characters needed to print to the lcd
}

int mya(){
  lcd.write(208); // mi
  lcd.write(172);
  Serial.print("mya");
  return 2; // number of katakana characters needed to print to the lcd
}

int myu(){
  lcd.write(208); // mi
  lcd.write(173);
  Serial.print("myu");
  return 2; // number of katakana characters needed to print to the lcd
}

int myo(){
  lcd.write(208); // mi
  lcd.write(174);
  Serial.print("myo");
  return 2; // number of katakana characters needed to print to the lcd
}

int rya(){
  lcd.write(216); // ri
  lcd.write(172);
  Serial.print("rya");
  return 2; // number of katakana characters needed to print to the lcd
}

int ryu(){
  lcd.write(216); // ri
  lcd.write(173);
  Serial.print("ryu");
  return 2; // number of katakana characters needed to print to the lcd
}

int ryo(){
  lcd.write(216); // ri
  lcd.write(174);
  Serial.print("ryo");
  return 2; // number of katakana characters needed to print to the lcd
}

int gya(){
  lcd.write(183); // ki
  lcd.write(222);
  lcd.write(172);
  Serial.print("gya");
  return 3; // number of katakana characters needed to print to the lcd
}

int gyu(){
  lcd.write(183); // ki
  lcd.write(222);
  lcd.write(173);
  Serial.print("gyu");
  return 3; // number of katakana characters needed to print to the lcd
}

int gyo(){
  lcd.write(183); // ki
  lcd.write(222);
  lcd.write(174);
  Serial.print("gyo");
  return 3; // number of katakana characters needed to print to the lcd
}

int ja(){
  lcd.write(188); // shi
  lcd.write(222);
  lcd.write(172);
  Serial.print("ja");
  return 3; // number of katakana characters needed to print to the lcd
}

int ji(){
  lcd.write(188); // shi
  lcd.write(222);
  Serial.print("ji");
  return 2; // number of katakana characters needed to print to the lcd
}

int ju(){
  lcd.write(188); // shi
  lcd.write(222);
  lcd.write(173);
  Serial.print("ju");
  return 3; // number of katakana characters needed to print to the lcd
}

int jo(){
  lcd.write(188); // shi
  lcd.write(222);
  lcd.write(174);
  Serial.print("jo");
  return 3; // number of katakana characters needed to print to the lcd
}

int bya(){
  lcd.write(203); // hi
  lcd.write(222);
  lcd.write(172);
  Serial.print("bya");
  return 3; // number of katakana characters needed to print to the lcd
}

int byu(){
  lcd.write(203); // hi
  lcd.write(222);
  lcd.write(173);
  Serial.print("byu");
  return 3; // number of katakana characters needed to print to the lcd
}

int byo(){
  lcd.write(203); // hi
  lcd.write(222);
  lcd.write(174);
  Serial.print("byo");
  return 3; // number of katakana characters needed to print to the lcd
}

int pya(){
  lcd.write(203); // hi
  lcd.write(223);
  lcd.write(172);
  Serial.print("pya");
  return 3; // number of katakana characters needed to print to the lcd
}

int pyu(){
  lcd.write(203); // hi
  lcd.write(223);
  lcd.write(173);
  Serial.print("pyu");
  return 3; // number of katakana characters needed to print to the lcd
}

int pyo(){
  lcd.write(203); // hi
  lcd.write(223);
  lcd.write(174);
  Serial.print("pyo");
  return 3; // number of katakana characters needed to print to the lcd
}

int aa(){
  lcd.write(177); // a
  lcd.write(176);
  Serial.print("aa");
  return 2; // number of katakana characters needed to print to the lcd
}

int ii(){
  lcd.write(178); // i
  lcd.write(176);
  Serial.print("ii");
  return 2; // number of katakana characters needed to print to the lcd
}

int uu(){
  lcd.write(179); // u
  lcd.write(176);
  Serial.print("uu");
  return 2; // number of katakana characters needed to print to the lcd
}

int ee(){
  lcd.write(180); // e
  lcd.write(176);
  Serial.print("ee");
  return 2; // number of katakana characters needed to print to the lcd
}

int oo(){
  lcd.write(181); // o
  lcd.write(176);
  Serial.print("oo");
  return 2; // number of katakana characters needed to print to the lcd
}

int wi(){
  lcd.write(179); // u
  lcd.write(168);
  Serial.print("wi");
  return 2; // number of katakana characters needed to print to the lcd
}

int we(){
  lcd.write(179); // u
  lcd.write(170);
  Serial.print("we");
  return 2; // number of katakana characters needed to print to the lcd
}
