/* FluxamasynthPlayAllVoices
* Plays all voices with a random algorithmic tune
* on the Modern Device Fluxamasynth Shield
* ModernDevice.com
*/
#include <Fluxamasynth.h>
#include <PgmChange.h>


    Fluxamasynth synth = Fluxamasynth();
    

    void setup() {
      for(int x = 30; x < 50; x++){
        pinMode(x, OUTPUT);
      }
      synth.midiReset();
      synth.programChange(127, 0, 0);        //bank 127 piano
      synth.programChange(127, 1, 112);        //bank 127 timpani
      synth.programChange(127, 2, 48);        //bank 127 string ensemble
      synth.programChange(127, 3, 88);        //bank 127 trumpet
      synth.programChange(127, 4, 64);        //bank 127 acoustic bass
      synth.programChange(127, 5, 49);        //bank 127 tremolo strings
      synth.programChange(127, 6, 102);        //bank 127 tubular bells
      synth.programChange(0, 7, 66);        //bank 127 tenor sax
      synth.programChange(0, 8, 58);        //bank 0 trombone, really tuba
      synth.programChange(0, 9, 40);        //jazz kit
      for (int y = 0; y < 16; y++){
      synth.setReverb(y, 5, 80, 50);
      synth.setChannelVolume(9, 90);
      }
    }

    void loop()
{
  for (int a = 0; a < 2; a++){
    synth.noteOn(5, 48, 60);        //intro 1-1
    synth.noteOn(5, 60, 60);
    synth.noteOn(5, 55, 60);
    synth.noteOn(2, 84, 100);
    synth.noteOn(6, 72, 127);  
    delay(100);
      synth.noteOff(2, 84);        //1-1-ee
      synth.noteOn(2, 83, 95);
      delay(100);
        synth.noteOff(2, 83);        //1-1-and
        synth.noteOn(2, 81, 90);
        delay(100);
          synth.noteOff(2, 81);        //1-1-a
          synth.noteOn(2, 79, 85);
          delay(100);
            synth.noteOff(2, 79);        //1-2
            synth.noteOn(2, 81, 80);
            delay(100);
              synth.noteOff(2, 81);        //1-2-ee
              synth.noteOn(2, 79, 76);
              delay(100);
                synth.noteOff(2, 79);        //1-2-and
                synth.noteOn(2, 77, 74);
                delay(100);
                  synth.noteOff(2, 77);        //1-2-a
                  synth.noteOn(2, 76, 72);
                  delay(100);
    synth.noteOff(2, 76);        //1-3
    synth.noteOff(6, 72);
    synth.noteOn(6, 67, 127);
    synth.noteOn(2, 74, 72);
    delay(100);
      synth.noteOff(2, 74);        //1-3-ee
      synth.noteOn(2, 76, 74);
      delay(100);
        synth.noteOff(2, 76);        //1-3-and
        synth.noteOn(2, 77, 76);
        delay(100);
          synth.noteOff(2, 77);        //1-3-a
          synth.noteOn(2, 79, 80);
          delay(100);
            synth.noteOff(2, 79);        //1-4
            synth.noteOn(2, 81, 85);
            delay(100);
              synth.noteOff(2, 81);        //1-4-ee
              synth.noteOn(2, 79, 90);
              delay(100);
                synth.noteOff(2, 79);        //1-4-and
                synth.noteOn(2, 81, 95);
                delay(100);
                  synth.noteOff(2, 81);        //1-4-a
                  synth.noteOn(2, 83, 100);
                  delay(100);
    synth.noteOff(2, 83);        //2-1
    synth.noteOff(6, 67);
    synth.noteOn(6, 69, 127);
    synth.noteOn(2, 84, 100);
    delay(100);
      synth.noteOff(2, 84);        //2-1-ee
      synth.noteOn(2, 83, 95);
      delay(100);
        synth.noteOff(2, 83);        //2-1-and
        synth.noteOn(2, 81, 90);
        delay(100);
          synth.noteOff(2, 81);        //2-1-a
          synth.noteOn(2, 79, 85);
          delay(100);
            synth.noteOff(2, 79);        //2-2
            synth.noteOn(2, 81, 80);
            delay(100);
              synth.noteOff(2, 81);        //2-2-ee
              synth.noteOn(2, 79, 76);
              delay(100);
                synth.noteOff(2, 79);        //2-2-and
                synth.noteOn(2, 77, 74);
                delay(100);
                  synth.noteOff(2, 77);        //2-2-a
                  synth.noteOn(2, 76, 72);
                  delay(100);
    synth.noteOff(2, 76);        //2-3
    synth.noteOff(6, 69);
    synth.noteOn(6, 64, 127);
    synth.noteOn(2, 74, 72);
    delay(100);
      synth.noteOff(2, 74);        //2-3-ee
      synth.noteOn(2, 76, 74);
      delay(100);
        synth.noteOff(2, 76);        //2-3-and
        synth.noteOn(2, 77, 76);
        delay(100);
          synth.noteOff(2, 77);        //2-3-a
          synth.noteOn(2, 79, 80);
          delay(100);
            synth.noteOff(2, 79);        //2-4
            synth.noteOn(2, 81, 85);
            delay(100);
              synth.noteOff(2, 81);        //2-4-ee
              synth.noteOn(2, 79, 90);
              delay(100);
                synth.noteOff(2, 79);        //2-4-and
                synth.noteOn(2, 81, 95);
                delay(100);
                  synth.noteOff(2, 81);        //2-4-a
                  synth.noteOn(2, 83, 100);
                  delay(100);
    synth.noteOff(2, 83);        
    synth.noteOff(6, 64);
    synth.allNotesOff(5);
  }
    synth.noteOn(2, 83, 100);        //8-1
    synth.noteOn(2, 43, 100);
    synth.noteOn(2, 55, 100);
    synth.noteOn(2, 74, 100);
    synth.noteOn(2, 77, 100);
    synth.noteOn(2, 79, 100);
    delay(100);
    synth.allNotesOff(6);
    synth.allNotesOff(2);
    synth.allNotesOff(5);
    delay(120);
      synth.noteOn(4, 43, 70);        //8-1-and
      delay(180);
        synth.noteOff(4, 43);        //8-2
        synth.noteOn(4, 41, 70);
        delay(400);
          synth.noteOff(4, 41);        //8-3
          synth.noteOn(4, 40, 70);
          delay(400);
            synth.noteOff(4, 40);        //8-4        Ha-
            synth.noteOn(4, 38, 70);
            synth.noteOn(3, 67, 80);
            synth.noteOn(7, 67, 80);
            synth.noteOn(3, 62, 80);
            synth.noteOn(7, 62, 80);
            synth.noteOn(3, 59, 80);
            synth.noteOn(7, 59, 80);
            synth.noteOn(3, 65, 80);
            synth.noteOn(7, 65, 80);
            delay(200);
            synth.allNotesOff(3);
            synth.allNotesOff(7);
            delay(50);
              synth.allNotesOff(3);        //8-4-and        ppy
              synth.allNotesOff(7);
              synth.noteOn(3, 67, 80);
              synth.noteOn(7, 67, 80);
              synth.noteOn(3, 62, 80);
              synth.noteOn(7, 62, 80);
              synth.noteOn(3, 59, 80);
              synth.noteOn(7, 59, 80);
              synth.noteOn(3, 65, 80);
              synth.noteOn(7, 65, 80);
              delay(100);
              synth.allNotesOff(3);
              synth.allNotesOff(7);
              delay(50);
    synth.noteOff(4, 38);        //9-1        Ho-
    synth.noteOn(7, 69, 80);
    synth.noteOn(3, 69, 80);
    synth.noteOn(7, 67, 80);
    synth.noteOn(3, 67, 80);
    synth.noteOn(7, 64, 80);
    synth.noteOn(3, 64, 80);
    synth.noteOn(7, 60, 80);
    synth.noteOn(3, 60, 80);
    synth.noteOn(4, 36, 80);
    synth.noteOn(9, 36, 50);
    synth.noteOn(9, 40, 80);
    delay(200);
    delay(50);
      synth.allNotesOff(7);        //9-1-and        li-
      synth.allNotesOff(3);
      synth.noteOff(9, 36);
      synth.noteOff(4, 36);      
      synth.noteOn(4, 36, 70);
      synth.noteOn(7, 69, 80);
      synth.noteOn(3, 69, 80);
      synth.noteOn(7, 67, 80);
      synth.noteOn(3, 67, 80);
      synth.noteOn(7, 64, 80);
      synth.noteOn(3, 64, 80);
      synth.noteOn(7, 60, 80);
      synth.noteOn(3, 60, 80);
      delay(100);
      synth.allNotesOff(7);
      synth.allNotesOff(3);
      delay(50);
        synth.noteOff(4, 36);        //9-2        day
        synth.noteOff(9, 40);
        synth.noteOn(4, 40, 70);
        synth.noteOn(9, 39, 80);
        synth.noteOn(7, 69, 80);
        synth.noteOn(3, 69, 80);
        synth.noteOn(7, 67, 80);
        synth.noteOn(3, 67, 80);
        synth.noteOn(7, 64, 80);
        synth.noteOn(3, 64, 80);
        synth.noteOn(7, 60, 80);
        synth.noteOn(3, 60, 80);
        delay(400);
          synth.noteOff(9, 39);        //9-3
          synth.noteOff(4, 40);
          synth.noteOn(4, 43, 70);
          synth.noteOn(9, 36, 50);
          synth.noteOn(9, 40, 80);
          delay(400);
            synth.noteOff(9, 36);        //9-4
            synth.noteOff(9, 40);
            synth.noteOff(4, 43);
            synth.noteOn(4, 45, 70);
            synth.noteOn(9, 39, 80);
            synth.noteOn(7, 69, 80);
            synth.noteOn(3, 69, 80);
            synth.noteOn(7, 67, 80);
            synth.noteOn(3, 67, 80);
            synth.noteOn(7, 64, 80);
            synth.noteOn(3, 64, 80);
            synth.noteOn(7, 60, 80);
            synth.noteOn(3, 60, 80);
            delay(100);
            synth.allNotesOff(7);
            synth.allNotesOff(3);
            delay(300);
    synth.noteOff(9, 39);        //10-1
    synth.noteOff(4, 45);
    synth.allNotesOff(7);
    synth.allNotesOff(3);
    synth.noteOn(4, 48, 70);
    synth.noteOn(9, 36, 50);
    synth.noteOn(9, 40, 80);
    synth.noteOn(7, 69, 80);
    synth.noteOn(3, 69, 80);
    synth.noteOn(7, 66, 80);
    synth.noteOn(3, 66, 80);
    synth.noteOn(7, 64, 80);
    synth.noteOn(3, 64, 80);
    synth.noteOn(7, 60, 80);
    synth.noteOn(3, 60, 80);
    delay(250);
      synth.allNotesOff(7);        //10-1-and
      synth.allNotesOff(3);
      synth.noteOn(7, 69, 80);
      synth.noteOn(3, 69, 80);
      synth.noteOn(7, 67, 80);
      synth.noteOn(3, 67, 80);
      synth.noteOn(7, 64, 80);
      synth.noteOn(3, 64, 80);
      synth.noteOn(7, 60, 80);
      synth.noteOn(3, 60, 80);
      delay(100);
        synth.allNotesOff(7);
        synth.allNotesOff(3);
        delay(50);
        synth.noteOff(4, 48);        //10-2
        synth.noteOff(9, 36);
        synth.noteOff(9, 40);
        synth.noteOn(4, 45, 70);
        synth.noteOn(9, 39, 80);
        delay(250);
          synth.noteOn(7, 69, 80);        //10-2-and
          synth.noteOn(3, 69, 80);
          synth.noteOn(7, 67, 80);
          synth.noteOn(3, 67, 80);
          synth.noteOn(7, 64, 80);
          synth.noteOn(3, 64, 80);
          synth.noteOn(7, 60, 80);
          synth.noteOn(3, 60, 80);
          synth.noteOn(9, 57, 120);
          delay(100);
          synth.allNotesOff(7);
          synth.allNotesOff(3);
          delay(50);
            synth.noteOff(9, 39);        //10-3
            synth.noteOff(4, 45);
            synth.noteOn(9, 36, 50);
            synth.noteOn(9, 40, 80);
            synth.noteOn(4, 43, 80);
            synth.noteOn(9, 36, 50);
            synth.noteOn(9, 40, 80);
            delay(400);
              synth.noteOff(9, 36);        //10-4        Ha-
              synth.noteOff(9, 40);
              synth.noteOff(9, 57);
              synth.noteOff(4, 43);
              synth.noteOn(9, 39, 80);
              synth.noteOn(4, 40, 80);
              synth.noteOn(7, 60, 80);
              synth.noteOn(3, 60, 80);
              synth.noteOn(7, 64, 80);
              synth.noteOn(3, 64, 80);
              synth.noteOn(7, 67, 80);
              synth.noteOn(3, 67, 80);
              delay(200);
              synth.allNotesOff(7);
              synth.allNotesOff(3);
              delay(50);
                synth.noteOn(7, 60, 80);        //10-4-and        ppy
                synth.noteOn(3, 60, 80);
                synth.noteOn(7, 64, 80);
                synth.noteOn(3, 64, 80);
                synth.noteOn(7, 67, 80);
                synth.noteOn(3, 67, 80);
                delay(100);
                synth.allNotesOff(7);
                synth.allNotesOff(3);
                delay(50);
    synth.allNotesOff(9);        //11-1        Hol-
    synth.noteOff(4, 40);
    synth.noteOn(4, 38, 80);
    synth.noteOn(7, 60, 80);
    synth.noteOn(3, 60, 80);
    synth.noteOn(7, 62, 80);
    synth.noteOn(3, 62, 80);  
    synth.noteOn(7, 65, 80);
    synth.noteOn(3, 65, 80);  
    synth.noteOn(7, 69, 80);
    synth.noteOn(3, 69, 80);
    synth.noteOn(9, 36, 50);
    synth.noteOn(9, 40, 80);
    delay(200);
    synth.noteOff(4, 38);
    synth.allNotesOff(7);
    synth.allNotesOff(3);
    delay(50);
      synth.noteOn(4, 38, 80);        //11-1-and        li-
      synth.noteOn(7, 60, 80);
      synth.noteOn(3, 60, 80);
      synth.noteOn(7, 62, 80);
      synth.noteOn(3, 62, 80);  
      synth.noteOn(7, 65, 80);
      synth.noteOn(3, 65, 80);  
      synth.noteOn(7, 69, 80);
      synth.noteOn(3, 69, 80);
      delay(100);
      delay(50);
        synth.allNotesOff(7);
        synth.allNotesOff(3);
        synth.noteOff(9, 36);        //11-2        day
        synth.noteOff(9, 40);
        synth.noteOn(9, 39, 80);
        synth.noteOff(4, 38);
        synth.noteOn(4, 41, 80);
        synth.noteOn(7, 60, 80);
        synth.noteOn(3, 60, 80);
        synth.noteOn(7, 62, 80);
        synth.noteOn(3, 62, 80);  
        synth.noteOn(7, 65, 80);
        synth.noteOn(3, 65, 80);  
        synth.noteOn(7, 69, 80);
        synth.noteOn(3, 69, 80);
        delay(350);
        delay(50);
          synth.allNotesOff(7);
          synth.allNotesOff(3);
          synth.noteOff(4, 41);        //11-3
          synth.noteOff(9, 39);
          synth.noteOn(4, 45, 80);
          synth.noteOn(9, 36, 50);
          synth.noteOn(9, 40, 80);
          synth.noteOn(7, 60, 80);
          synth.noteOn(3, 60, 80);
          synth.noteOn(7, 62, 80);
          synth.noteOn(3, 62, 80);  
          synth.noteOn(7, 65, 80);
          synth.noteOn(3, 65, 80);  
          synth.noteOn(7, 69, 80);
          synth.noteOn(3, 69, 80);
          delay(75);
          synth.allNotesOff(7);
          synth.allNotesOff(3);
          delay(325);
            synth.noteOff(4, 45);        //11-4
            synth.noteOff(9, 36);
            synth.noteOff(9, 40);
            synth.noteOn(9, 39, 80);
            synth.noteOn(4, 48, 80);
            delay(250);
              synth.noteOn(7, 60, 80);        //11-4-and
              synth.noteOn(3, 60, 80);
              synth.noteOn(7, 62, 80);
              synth.noteOn(3, 62, 80);  
              synth.noteOn(7, 65, 80);
              synth.noteOn(3, 65, 80);  
              synth.noteOn(7, 69, 80);
              synth.noteOn(3, 69, 80);
              delay(75);
              synth.allNotesOff(7);
              synth.allNotesOff(3);
              delay(75);
    synth.noteOff(4, 48);        //12-1
    synth.noteOff(9, 39);
    synth.noteOn(4, 50, 80);
    synth.noteOn(9, 36, 50);
    synth.noteOn(9, 40, 80);
    delay(250);
      synth.noteOn(7, 60, 80);        //12-1-and
      synth.noteOn(3, 60, 80);
      synth.noteOn(7, 62, 80);
      synth.noteOn(3, 62, 80);  
      synth.noteOn(7, 65, 80);
      synth.noteOn(3, 65, 80);  
      synth.noteOn(7, 69, 80);
      synth.noteOn(3, 69, 80);
      delay(100);
      synth.allNotesOff(7);
      synth.allNotesOff(3);
      delay(50);
        synth.noteOff(4, 50);        //12-2
        synth.noteOff(9, 36);
        synth.noteOff(9, 40);
        synth.noteOn(9, 39, 80);
        synth.noteOn(4, 48, 80);
        synth.noteOn(7, 60, 80);
        synth.noteOn(3, 60, 80);
        synth.noteOn(7, 62, 80);
        synth.noteOn(3, 62, 80);  
        synth.noteOn(7, 64, 80);
        synth.noteOn(3, 64, 80);  
        synth.noteOn(7, 69, 80);
        synth.noteOn(3, 69, 80);
        delay(250);
          synth.allNotesOff(7);
          synth.allNotesOff(3);
          synth.noteOn(7, 60, 80);
          synth.noteOn(3, 60, 80);
          synth.noteOn(7, 62, 80);
          synth.noteOn(3, 62, 80);  
          synth.noteOn(7, 65, 80);
          synth.noteOn(3, 65, 80);  
          synth.noteOn(7, 69, 80);
          synth.noteOn(3, 69, 80);
          synth.noteOn(9, 49, 120);
          delay(75);
          synth.allNotesOff(7);
          synth.allNotesOff(3);
          delay(75);
            synth.noteOff(4, 48);        //12-3
            synth.noteOff(9, 39);
            synth.noteOn(9, 36, 50);
            synth.noteOn(9, 40, 80);
            synth.noteOn(4, 45, 80);
            delay(400);
              synth.noteOff(4, 45);        //12-4        While
              synth.noteOff(9, 36);
              synth.noteOff(9, 40);
              synth.noteOff(9, 49);
              synth.noteOn(4, 41, 80);
              synth.noteOn(9, 39, 80);
              synth.noteOn(7, 60, 80);
              synth.noteOn(3, 60, 80);
              synth.noteOn(7, 62, 80);
              synth.noteOn(3, 62, 80);  
              synth.noteOn(7, 65, 80);
              synth.noteOn(3, 65, 80);  
              synth.noteOn(7, 67, 80);
              synth.noteOn(3, 67, 80);
              delay(200);
              synth.allNotesOff(7);
              synth.allNotesOff(3);
              delay(50);
                synth.noteOn(7, 60, 80);        //12-4-and        the
                synth.noteOn(3, 60, 80);
                synth.noteOn(7, 62, 80);
                synth.noteOn(3, 62, 80);  
                synth.noteOn(7, 65, 80);
                synth.noteOn(3, 65, 80);  
                synth.noteOn(7, 67, 80);
                synth.noteOn(3, 67, 80);
                delay(100);
                synth.allNotesOff(7);
                synth.allNotesOff(3);
                delay(50);
    synth.noteOff(4, 41);        //13-1        merr-
    synth.noteOff(9, 39);
    synth.noteOn(4, 43, 80);
    synth.noteOn(9, 36, 50);
    synth.noteOn(9, 40, 80);
    synth.noteOn(7, 62, 80);
    synth.noteOn(3, 62, 80);
    synth.noteOn(7, 65, 80);
    synth.noteOn(3, 65, 80);  
    synth.noteOn(7, 67, 80);
    synth.noteOn(3, 67, 80);  
    synth.noteOn(7, 71, 80);
    synth.noteOn(3, 71, 80);
    delay(200);
      //insert light blinking off here
    delay(50);
      synth.noteOff(4, 43);
      synth.allNotesOff(7);
      synth.allNotesOff(3);
      synth.noteOn(4, 43, 80);        //13-1-and        ry
      synth.noteOn(7, 62, 80);
      synth.noteOn(3, 62, 80);
      synth.noteOn(7, 65, 80);
      synth.noteOn(3, 65, 80);  
      synth.noteOn(7, 67, 80);
      synth.noteOn(3, 67, 80);  
      synth.noteOn(7, 71, 80);
      synth.noteOn(3, 71, 80);
      delay(100);
      synth.allNotesOff(7);
      synth.allNotesOff(3);
      delay(50);
        synth.allNotesOff(9);        //13-2        bells
        synth.noteOff(4, 43);
        synth.noteOn(4, 47, 80);
        synth.noteOn(9, 39, 80);
        synth.noteOn(7, 59, 80);
        synth.noteOn(3, 59, 80);
        synth.noteOn(7, 62, 80);
        synth.noteOn(3, 62, 80);  
        synth.noteOn(7, 65, 80);
        synth.noteOn(3, 65, 80);  
        synth.noteOn(7, 69, 80);
        synth.noteOn(3, 69, 80);
        delay(400);
          synth.noteOff(4, 47);        //13-3        bells, 2nd beat of half note
          synth.noteOff(9, 39);
          synth.noteOn(4, 50, 80);
          synth.noteOn(9, 36, 50);
          synth.noteOn(9, 40, 80);
          delay(400);
            synth.allNotesOff(9);        //13-4        keep
            synth.noteOff(4, 50);
            synth.allNotesOff(7);
            synth.allNotesOff(3);
            synth.noteOn(4, 47, 80);
            synth.noteOn(9, 39, 80);
            synth.noteOn(7, 62, 80);
            synth.noteOn(3, 62, 80);
            synth.noteOn(7, 65, 80);
            synth.noteOn(3, 65, 80);  
            synth.noteOn(7, 67, 80);
            synth.noteOn(3, 67, 80);  
            synth.noteOn(7, 71, 80);
            synth.noteOn(3, 71, 80);
            delay(300);
            synth.allNotesOff(7);
            synth.allNotesOff(3);
            delay(100);
    synth.noteOff(4, 47);        //14-1        ring-
    synth.noteOff(9, 39);
    synth.allNotesOff(7);
    synth.allNotesOff(3);
    synth.noteOn(4, 48, 80);
    synth.noteOn(9, 36, 50);
    synth.noteOn(9, 40, 80);
    synth.noteOn(7, 64, 80);
    synth.noteOn(3, 64, 80);
    synth.noteOn(7, 67, 80);
    synth.noteOn(3, 67, 80);
    synth.noteOn(7, 69, 80);
    synth.noteOn(3, 69, 80);
    synth.noteOn(7, 72, 80);
    synth.noteOn(3, 72, 80);
    delay(200);
    synth.allNotesOff(7);
    synth.allNotesOff(3);
    //insert light off
    delay(50);
      synth.noteOn(7, 57, 80);        //14-1-and        ing
      synth.noteOn(3, 57, 80);
      synth.noteOn(7, 60, 80);
      synth.noteOn(3, 60, 80);
      synth.noteOn(7, 64, 80);
      synth.noteOn(3, 64, 80);
      synth.noteOn(7, 67, 80);
      synth.noteOn(3, 67, 80);
      delay(75);
      synth.allNotesOff(7);
      synth.allNotesOff(3);
      delay(75);
        synth.noteOff(4, 48);        //14-2
        synth.allNotesOff(9);
        synth.noteOn(4, 45, 80);
        synth.noteOn(9, 39, 80);
        delay(250);
          synth.noteOn(7, 55, 80);        //14-2-and
          synth.noteOn(3, 55, 80);
          synth.noteOn(7, 57, 80);
          synth.noteOn(3, 57, 80);
          synth.noteOn(7, 60, 80);
          synth.noteOn(3, 60, 80);
          synth.noteOn(7, 64, 80);
          synth.noteOn(3, 64, 80);
          synth.noteOn(9, 57, 100);
          delay(75);
          synth.allNotesOff(7);
          synth.allNotesOff(3);
          delay(75);
            synth.noteOff(4, 45);        //14-3
            synth.noteOff(9, 39);
            synth.noteOn(4, 43, 80);
            synth.noteOn(9, 36, 50);
            synth.noteOn(9, 40, 80);
            delay(400);
              synth.noteOff(4, 43);        //14-4        May
              synth.allNotesOff(9);
              synth.noteOn(4, 40, 80);
              synth.noteOn(9, 39, 80);
              synth.noteOn(7, 55, 80);
              synth.noteOn(3, 55, 80);
              synth.noteOn(7, 57, 80);
              synth.noteOn(3, 57, 80);
              synth.noteOn(7, 60, 80);
              synth.noteOn(3, 60, 80);
              synth.noteOn(7, 64, 80);
              synth.noteOn(3, 64, 80);
              delay(200);
              synth.allNotesOff(7);
              synth.allNotesOff(3);
              //lights
              delay(50);
                synth.noteOn(7, 55, 80);        //14-4-and        your
                synth.noteOn(3, 55, 80);
                synth.noteOn(7, 57, 80);
                synth.noteOn(3, 57, 80);
                synth.noteOn(7, 60, 80);
                synth.noteOn(3, 60, 80);
                synth.noteOn(7, 64, 80);
                synth.noteOn(3, 64, 80);
                delay(75);
                synth.allNotesOff(7);
                synth.allNotesOff(3);
                delay(75);
  synth.noteOff(4, 40);        //15-1        ev'-
  synth.noteOff(9, 39);
  synth.noteOn(4, 38, 80);
  synth.noteOn(9, 36, 50);
  synth.noteOn(9, 40, 80);
  synth.noteOn(7, 57, 80);
  synth.noteOn(3, 57, 80);
  synth.noteOn(7, 60, 80);
  synth.noteOn(3, 60, 80);
  synth.noteOn(7, 62, 80);
  synth.noteOn(3, 62, 80);
  synth.noteOn(7, 67, 80);
  synth.noteOn(3, 67, 80);
  delay(200);
  delay(50);
    synth.allNotesOff(7);        //15-1-and        ry
    synth.allNotesOff(3);
    synth.noteOff(4, 38);
    synth.noteOn(4, 38, 80);
    synth.noteOn(7, 57, 80);
    synth.noteOn(3, 57, 80);
    synth.noteOn(7, 60, 80);
    synth.noteOn(3, 60, 80);
    synth.noteOn(7, 62, 80);
    synth.noteOn(3, 62, 80);
    synth.noteOn(7, 67, 80);
    synth.noteOn(3, 67, 80);
    delay(75);
    synth.allNotesOff(7);
    synth.allNotesOff(3);
    delay(75);
      synth.noteOff(4, 38);        //15-2        wish
      synth.allNotesOff(9);
      synth.noteOn(4, 41, 80);
      synth.noteOn(9, 39, 80);
      synth.noteOn(7, 57, 80);
      synth.noteOn(3, 57, 80);
      synth.noteOn(7, 60, 80);
      synth.noteOn(3, 60, 80);
      synth.noteOn(7, 62, 80);
      synth.noteOn(3, 62, 80);
      synth.noteOn(7, 65, 80);
      synth.noteOn(3, 65, 80);
      delay(400);
        synth.noteOff(4, 41);        //15-3
        synth.noteOff(9, 39);
        synth.noteOn(4, 45, 80);
        synth.noteOn(9, 36, 50);
        synth.noteOn(9, 40, 80);
        delay(350);
        synth.allNotesOff(7);
        synth.allNotesOff(3);
        delay(50);
          synth.noteOff(4, 45);        //15-4        come
          synth.allNotesOff(9);
          synth.noteOn(4, 38, 80);
          synth.noteOn(9,39, 80);
          synth.noteOn(7, 53, 80);
          synth.noteOn(3, 53, 80);
          synth.noteOn(7, 57, 80);
          synth.noteOn(3, 57, 80);
          synth.noteOn(7, 60, 80);
          synth.noteOn(3, 60, 80);
          synth.noteOn(7, 62, 80);
          synth.noteOn(3, 62, 80);
          delay(350);
          synth.allNotesOff(7);
          synth.allNotesOff(3);
          delay(50);
  synth.noteOff(4, 38);        //16-1        true
  synth.noteOff(9, 39);
  synth.noteOn(4, 43, 80);
  synth.noteOn(9, 36, 50);
  synth.noteOn(9, 40, 80);
  synth.noteOn(7, 59, 80);
  synth.noteOn(3, 59, 80);
  synth.noteOn(7, 62, 80);
  synth.noteOn(3, 62, 80);
  synth.noteOn(7, 64, 80);
  synth.noteOn(3, 64, 80);
  synth.noteOn(7, 67, 80);
  synth.noteOn(3, 67, 80);
  delay(250);
    synth.noteOff(7, 64);        //16-1-and
    synth.noteOff(3, 64);
    synth.noteOff(4, 43);
    synth.noteOn(4, 43, 80);
    synth.noteOn(7, 62, 80);
    synth.noteOn(3, 62, 80);
    delay(150);
      synth.noteOff(4, 43);        //16-2
      synth.allNotesOff(9);
      synth.noteOff(7, 62);
      synth.noteOff(3, 62);
      synth.noteOn(4, 41, 80);
      synth.noteOn(9, 39, 80);
      synth.noteOn(7, 62, 80);
      synth.noteOn(3, 62, 80);
      synth.noteOn(7, 64, 80);
      synth.noteOn(3, 64, 80);
      delay(250);
        synth.noteOff(7, 64);        //16-2-and
        synth.noteOff(3, 64);
        synth.noteOn(7, 65, 80);
        synth.noteOn(3, 65, 80);
        delay(150);
          synth.noteOff(4, 41);        //16-3
          synth.noteOff(9, 39);
          synth.noteOn(4, 40, 80);
          synth.noteOn(9, 36, 50);
          synth.noteOn(9, 40, 80);
            delay(400);
            synth.noteOff(4, 40);        //16-4        Ha-
            synth.allNotesOff(9);
            synth.allNotesOff(7);
            synth.allNotesOff(3);
            synth.noteOn(4, 38, 80);
            synth.noteOn(8, 59, 90);
            synth.noteOn(8, 62, 90);
            synth.noteOn(8, 65, 90);
            synth.noteOn(8, 67, 90);
            delay(200);
            delay(50);
              synth.allNotesOff(8);
              synth.noteOn(8, 59, 80);        //16-4-and        ppy
              synth.noteOn(8, 62, 80);
              synth.noteOn(8, 65, 80);
              synth.noteOn(8, 67, 80);
              delay(100);
              synth.allNotesOff(8);
              delay(50);
    synth.noteOff(4, 38);        //17-1        Ho-
    synth.allNotesOff(8);
    synth.noteOn(8, 60, 90);
    synth.noteOn(8, 64, 90);
    synth.noteOn(8, 67, 90);
    synth.noteOn(8, 69, 90);
    synth.noteOn(4, 36, 80);
    synth.noteOn(9, 36, 50);
    synth.noteOn(9, 40, 80);
    delay(200);
    delay(50);
      synth.allNotesOff(8);        //17-1-and        li-
      synth.noteOff(9, 36);
      synth.noteOff(4, 36);      
      synth.noteOn(4, 36, 80);
      synth.noteOn(8, 60, 80);
      synth.noteOn(8, 64, 80);
      synth.noteOn(8, 67, 80);
      synth.noteOn(8, 69, 80);
      delay(100);
      delay(50);
        synth.allNotesOff(8);        //17-2        day
        synth.noteOff(4, 36);
        synth.noteOff(9, 40);
        synth.noteOn(4, 40, 80);
        synth.noteOn(9, 39, 80);
        synth.noteOn(8, 60, 90);
        synth.noteOn(8, 64, 90);
        synth.noteOn(8, 67, 90);
        synth.noteOn(8, 69, 90);
        delay(400);
          synth.noteOff(9, 39);        //17-3
          synth.noteOff(4, 40);
          synth.noteOn(4, 43, 80);
          synth.noteOn(9, 36, 50);
          synth.noteOn(9, 40, 80);
          delay(400);
            synth.noteOff(4, 43);        //17-4        trip-
            synth.allNoteOff(9);
            synth.allNotesOff(8);
            synth.noteOn(4, 48, 80);
            synth.noteOn(9, 45, 50);
            synth.noteOn(9, 40, 80);
            synth.noteOn(7, 64);
            synth.noteOn(3, 64);
            delay(133);
              synth.noteOff(7, 64);        //17-4        -a-
              synth.noteOff(3, 64);
              synth.noteOn(7, 67, 80);
              synth.noteOn(3, 67, 80);
              delay(133);
                synth.noteOff(7, 67);        //17-4        let
                synth.noteOff(3, 67);
                synth.noteOn(7, 70, 80);
                synth.noteOn(3, 70, 80);
                delay(133);
  synth.noteOff(7, 70);        //18-1
  synth.noteOff(3, 70);
  synth.noteOff(4, 45);
  synth.noteOff(9, 39);
  synth.noteOn(4, 48, 80);
  synth.noteOn(7, 69, 80);
  synth.noteOn(3, 69, 80);
  synth.noteOn(9, 36, 50);
  synth.noteOn(9, 57, 120);
  synth.noteOn(8, 60, 90);
  synth.noteOn(8, 64, 90);
  synth.noteOn(8, 67, 90);
  synth.noteOn(8, 69, 90);
  delay(75);
  synth.allNotesOff(8);
  synth.noteOff(7, 69);
  synth.noteOff(3, 69);
  delay(325);
    synth.allNotesOff(9);        //18-2
    synth.noteOff(4, 48);
    synth.noteOn(4, 45, 80);
    synth.noteOn(9, 39, 80);
    delay(250);
      synth.noteOn(7, 70, 80);        //18-2-and
      synth.noteOn(3, 70, 80);
      synth.noteOn(8, 61, 90);
      synth.noteOn(8, 64, 90);
      synth.noteOn(8, 67, 90);
      synth.noteOn(8, 70, 90);
      synth.noteOn(9, 49, 120);
      delay(75);
      synth.allNotesOff(8);
      synth.noteOff(7, 70);
      synth.noteOff(3, 70);
      delay(75);
        synth.noteOff(4, 45);        //18-3
        synth.allNotesOff(9);
        synth.noteOn(4, 43, 80);
        synth.noteOn(9, 36, 50);
        synth.noteOn(9, 40, 80);
        delay(400);
          synth.noteOff(4, 43);        //18-4        Ha-
          synth.allNotesOff(9);
          synth.noteOn(4, 40, 80);
          synth.noteOn(9, 39, 80);
          synth.noteOn(8, 57, 90);
          synth.noteOn(8, 60, 90);
          synth.noteOn(8, 64, 90);
          synth.noteOn(8, 67, 90);
          delay(200);
          delay(50);
            synth.allNotesOff(8);        //18-4-and        ppy
            synth.noteOn(8, 57, 80);
            synth.noteOn(8, 60, 80);
            synth.noteOn(8, 64, 80);
            synth.noteOn(8, 67, 80);
            delay(100);
            synth.allNotesOff(8);
            delay(50);
  synth.noteOff(4, 40);        //19-1        Hol-
  synth.noteOff(9, 39);
  synth.noteOn(4, 38, 80);
  synth.noteOn(9, 36, 50);
  synth.noteOn(9, 40, 80);
  synth.noteOn(8, 60, 90);
  synth.noteOn(8, 62, 90);
  synth.noteOn(8, 65, 90);
  synth.noteOn(8, 69, 90);
  delay(200);
  delay(50);
    synth.allNotesOff(8);        //19-1-and        -li-
    synth.noteOn(8, 60, 80);
    synth.noteOn(8, 62, 80);
    synth.noteOn(8, 65, 80);
    synth.noteOn(8, 69, 80);
    delay(100);
    synth.allNotesOff(8);
    delay(50);
      synth.noteOff(4, 38);        //19-2        -day
      synth.noteallNotesOff(9);
      synth.noteOn(4, 41, 80);
      synth.noteOn(9, 39, 80);
      synth.noteOn(8, 60, 90);
      synth.noteOn(8, 62, 90);
      synth.noteOn(8, 65, 90);
      synth.noteOn(8, 69, 90);
      delay(400);
        synth.noteOff(4, 41);        //19-3
        synth.noteOff(9, 39);
        synth.noteOn(4, 45, 80);
        synth.noteOn(9, 36, 50);
        synth.noteOn(9, 40, 80);
        delay(400);
          synth.noteOff(4, 45);        //19-4        trip
          synth.allNotesOff(9);
          synth.allNotesOff(8);
          synth.noteOn(4, 48, 80);
          synth.noteOn(9, 39, 80);
          synth.noteOn(7, 64, 80);
          synth.noteOn(3, 64, 80);
          delay(133);
            synth.noteOff(7, 64);        //19-4        -a-
            synth.noteOff(3, 64);
            synth.noteOn(7, 67, 80);
            synth.noteOn(3, 67, 80);
            delay(133);
              synth.noteOff(7, 67);        //19-4        -let
              synth.noteOff(3, 67);
              synth.noteOn(7, 70);
              synth.noteOn(3, 70);
              delay(133);
  synth.noteOff(4, 48);        //20-1
  synth.noteOff(9, 39);
  synth.noteOff(7, 70);
  synth.noteOff(3, 70);
  synth.noteOn(4, 50, 80);
  synth.noteOn(9, 36, 50);
  synth.noteOn(9, 49, 120);
  synth.noteOn(8, 60, 90);
  synth.noteOn(8, 62, 90);
  synth.noteOn(8, 65, 90);
  synth.noteOn(8, 69, 90);
  synth.noteOn(7, 69, 80);
  synth.noteOn(3, 69, 80);
  delay(75);
  synth.allNotesOff(8);
  synth.noteOff(7, 69);
  synth.noteOff(3, 69);
  delay(325);
    synth.noteOff(4, 50);        //20-2
    synth.allNotesOff(9);
    synth.noteOn(4, 48);
    synth.noteOn(9, 39);
    delay(250);
      synth.noteOn(8, 60, 90);        //20-2-and
      synth.noteOn(8, 62, 90);
      synth.noteOn(8, 66, 90);
      synth.noteOn(8, 70, 90);
      synth.noteOn(7, 70, 80);
      synth.noteOn(3, 70, 80);
      synth.noteOm(9, 57, 120);
      delay(75);
      synth.allNotesOff(8);
      synth.noteOff(7, 70);
      synth.noteOff(3, 70);
      delay(75);
        synth.noteOff(4, 48);        //20-3
        synth.allNotesOff(9);
        synth.noteOn(4, 45, 80);
        synth.noteOn(9, 36, 50);
        synth.noteOn(9, 40, 80);
        delay(400);
          synth.noteOff(4, 45);        //20-4        While
          synth.allNotesOff(9);
          synth.noteOn(4, 41, 80);
          synth.noteOn(9, 39, 80);
          synth.noteOn(8, 60, 90);
          synth.noteOn(8, 62, 90);
          synth.noteOn(8, 65, 90);
          synth.noteOn(8, 67, 90);
          delay(200);
          delay(50);
            synth.allNotesOff(8);        //20-4-and        the
            synth.noteOn(8, 60, 80);
            synth.noteOn(8, 62, 80);
            synth.noteOn(8, 65, 80);
            synth.noteOn(8, 67, 80);
            delay(100);
            synth.allNotesOff(8);
            delay(50);
  synth.noteOff(4, 41);        //21-1        merr-
  synth.noteOff(9, 39);
  synth.noteOn(4, 43, 80);
  synth.noteOn(9, 36, 50);
  synth.noteOn(9, 40, 80);
  synth.noteOn(8, 62, 90);
  synth.noteOn(8, 65, 90);
  synth.noteOn(8, 67, 90);
  synth.noteOn(8, 71, 90);
  delay(200);
  delay(50);
    synth.allNotesOff(8);        //21-1-and        -ry
    synth.noteOn(8, 62, 80);
    synth.noteOn(8, 65, 80);
    synth.noteOn(8, 67, 80);
    synth.noteOn(8, 71, 80);
    delay(100);
    synth.allNotesOff(8);
    delay(50);
      synth.noteOff(4, 43);        //21-2        bells
      synth.allNotesOff(9);
      synth.noteOn(4, 41, 80);
      synth.noteOn(9, 39, 80);
      synth.noteOn(8, 59, 90);
      synth.noteOn(8, 62, 90);
      synth.noteOn(8, 65, 90);
      synth.noteOn(8, 69, 90);
      delay(400);
        synth.noteOff(4, 41);        //21-3
        synth.noteOff(9, 39);
        synth.noteOn(4, 40);
        synth.noteOn(9, 36, 50);
        synth.noteOn(9, 40, 80);
        delay(400);
          
}

