/*
MIT License

Copyright (c)2020 Gian Gisin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/






#define dirPin 11          
#define stepPin 12       
#define stepsPerRevolution 200        
#define lengthCM 77      
#define delayBetweenRuns 1000
#define delayMicro 900
#define potentioPin 17
#define potentioPower 10

int currentDirection = HIGH;
boolean timeLapse = false;
int value = 0;
int stepsForLength = 0;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  digitalWrite(potentioPower, HIGH);
  
  Serial.begin(9600);
  delay(3000);
  
  stepsForLength = lengthCM / 3.2 * stepsPerRevolution;
}

void loop() {
  digitalWrite(dirPin, currentDirection);
  
  if(currentDirection == LOW){
    currentDirection = HIGH;
  }else{
    currentDirection = LOW;
  }
  delay(delayBetweenRuns);
  
  for(int i = 0; i <= stepsForLength; i++){
    digitalWrite(stepPin, HIGH);
    
    Serial.println(analogRead(potentioPin) * 2);
    
    if (analogRead(potentioPin)* 2 >= 1000){
        value = analogRead(potentioPin);
        
        if(value >= 1200){
          value = 20;
          timeLapse = true;
          
        }else{
          value = 10;
          timeLapse = true;
        }
        
    }else{
      timeLapse = false;
      value += 700;
    }
    
    if(!timeLapse){
      delayMicroseconds(value);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(value);
      
    }else{
      delay(value);
      digitalWrite(stepPin, LOW);
      delay(value);
    }
  } 
}
