//Declaring all the variables to be used.....

int fl,l,c,r,fr;
int flm,lm,cm,rm,frm;
int bfl,bl,bc,br,bfr;
int wfl,wl,wc,wr,wfr;

char path[100];
int pathLength;

/*fl = far left sensor reading
        l = left sensor reading
        c = center sensor reading
        r = right sensor reading
        fr = far right sensor reading

        Prefix w indicates sensor reading when placed over a white surface
        For Example, wc = reading of center sensor when placed over a white surface

        Prefix b indicates sensor reading when placed over a black surface
        For Example, bc = reading of center sensor when placed over a black surface

        Suffix m indicates that the variable stores average value of black and white reading
        For Example, variable cm stores average value of center sensor readings when placed
        over a black and then a white surface (order of placing doesn't matter, cm will
        store the average value and will be used as a threshold to determine whether the
        sensor is over a white or black background)

        Please NOTE -   The bot follows a BLACK LINE on a WHITE BACKGROUND.....
                        The line-following code is written with the assumption that sensors are
                        calibrated (physically) in such a manner that they read a high when they detect black
                        and a low when they detect white.
                        If the sensors are calibrated differently or are uncalibrated (meaning they read when
                        a high when kept over a white surface and a low when kept over a black surface), then
                        all the > s in the line-following part of the code must be changed to < s and vice versa.
 */


//Assigning pins to the sensor input variables - The variable names are self explanatory.....
#define far_left_sensor A3
#define left_sensor A6
#define center_sensor A5
#define right_sensor A1
#define far_right_sensor A0


//Assigning pins to the motor output variables - The variable names are self explanatory.....
#define left_enable 10
#define left_dir 4
#define left_speed 5
#define right_enable 9
#define right_dir 2
#define right_speed 3


#define LED 13


//Setup starts here.....
void setup() {
        //Setting all sensor pins to input....
        pinMode (far_left_sensor,INPUT);    //farleft sensor
        pinMode (left_sensor,INPUT);    //left sensor
        pinMode (center_sensor,INPUT);    //center sensor
        pinMode (right_sensor,INPUT);    //right sensor
        pinMode (far_right_sensor,INPUT);    //farright sensor

        //Setting all motor driver pins to output....
        pinMode (left_enable,OUTPUT);    //left motor enable - 10
        pinMode (left_dir,OUTPUT);    //left motor direction - 4
        pinMode (left_speed,OUTPUT);    //left motor speed - 5
        pinMode (right_enable,OUTPUT);    //right motor enable - 9
        pinMode (right_dir,OUTPUT);    //right motor direction - 2
        pinMode (right_speed,OUTPUT);    //right motor speed - 3
        pinMode (LED,OUTPUT);    //Led


        //Calibration starts here.....
        digitalWrite(LED,LOW);
        delay(1000);
        digitalWrite(LED,HIGH);
        //Once LED turns on, place sensors over a black surface.....
        delay(2000);
        bl = analogRead (A1);
        bc = analogRead (A5);
        br = analogRead (A6);
        bfl = analogRead (A0);
        bfr = analogRead (A3);
        delay(2000);
        digitalWrite(LED,LOW);
        //Once LED turns off, remove sensors from black surface and wait for LED to turn.....
        delay(2000);
        digitalWrite(LED,HIGH);
        //Once LED turns on, place sensors over a white surface.....
        delay(2000);
        wl = analogRead (A1);
        wc = analogRead (A5);
        wr = analogRead (A6);
        wfl = analogRead (A0);
        wfr = analogRead (A3);
        delay(2000);
        digitalWrite(LED,LOW);
        //Once LED turns off, place the bot at the starting of the maze and wait for 3+ seconds.....
        delay(3000);
        //Actual Calibration calculation is done here.....
        flm  = (bfl+wfl)/2;
        lm = (bl+wl)/2;
        cm = (wc+bc)/2;
        rm = (wr+br)/2;
        frm = (bfr+wfr)/2;
        //End of Calibration.....

        //Setting the enable pins of the motor driver to high.....
        digitalWrite(9,HIGH);
        digitalWrite(10,HIGH);

        //Now, the bot can begin its motion...
        Serial.begin(9600);
}


//Loop starts here.....
void loop() {
        //Line following starts here.....
        read_sensors();
        if (fl<flm && c<cm) //BWB (1) straight motion
        {
                digitalWrite(right_dir,LOW);
                analogWrite(right_speed,125);
                digitalWrite(left_dir,LOW);
                analogWrite(left_speed,135);
        }
        else
        if (fl<flm && l<lm && c<cm && r<rm && fr<frm) //BBB (2)
        {
                digitalWrite(right_dir,HIGH);
                analogWrite(right_speed,200);
                digitalWrite(left_dir,HIGH);
                analogWrite(left_speed,190);
        }
        else
        if (l<lm && c<cm && r>rm) //BBW (3) right motion
        {
                digitalWrite(right_dir,LOW);
                analogWrite(right_speed,0);
                digitalWrite(left_dir,LOW);
                analogWrite(left_speed,135);
        }
        else
        if (l<lm && c<cm && fr>frm) //BWW (4) sharp right motion
        {
                digitalWrite(right_dir,HIGH);
                analogWrite(right_speed,200);
                digitalWrite(left_dir,LOW);
                analogWrite(left_speed,135);
        }
        else
        if (l<lm && c>cm && r>rm) //BWW (4) sharp right motion
        {
                digitalWrite(right_dir,HIGH);
                analogWrite(right_speed,200);
                digitalWrite(left_dir,LOW);
                analogWrite(left_speed,135);
        }
        else
        if (fr>frm) //BWW (4) sharp right motion
        {
                digitalWrite(right_dir,HIGH);
                analogWrite(right_speed,200);
                digitalWrite(left_dir,LOW);
                analogWrite(left_speed,135);
                delay(250);
        }
        else
        if (fr>frm && c>cm && l>lm) //BWW (4) sharp right motion
        {
                digitalWrite(right_dir,HIGH);
                analogWrite(right_speed,200);
                digitalWrite(left_dir,LOW);
                analogWrite(left_speed,135);
                delay(250);
        }
        else
        if (fr>frm && c>cm) //BWW (4) sharp right motion
        {
                digitalWrite(right_dir,HIGH);
                analogWrite(right_speed,200);
                digitalWrite(left_dir,LOW);
                analogWrite(left_speed,135);
                delay(250);
        }
        else
        if (fl>flm && r<rm) //WWB (5) sharp left motion
        {
                digitalWrite(right_dir,LOW);
                analogWrite(right_speed,125);
                digitalWrite(left_dir,HIGH);
                analogWrite(left_speed,190);
        }
        else
        if (l>lm && c>cm) //WWB (5) sharp left motion
        {
                digitalWrite(right_dir,LOW);
                analogWrite(right_speed,125);
                digitalWrite(left_dir,HIGH);
                analogWrite(left_speed,190);
        }
        else
        if (fl>flm) //WWB (5) sharp left motion
        {
                digitalWrite(right_dir,LOW);
                analogWrite(right_speed,125);
                digitalWrite(left_dir,HIGH);
                analogWrite(left_speed,190);
                delay(250);
        }
        else
        if (fl>flm && c>cm && r>rm) //WWB (5) sharp left motion
        {
                digitalWrite(right_dir,LOW);
                analogWrite(right_speed,125);
                digitalWrite(left_dir,HIGH);
                analogWrite(left_speed,190);
                delay(250);
        }
        else
        if (fl>flm && c>cm) //WWB (5) sharp left motion
        {
                digitalWrite(right_dir,LOW);
                analogWrite(right_speed,125);
                digitalWrite(left_dir,HIGH);
                analogWrite(left_speed,190);
                delay(250);
        }
        else
        if (lm && r>rm) //WBB (6) left motion  - Condition to be checked
        {
                digitalWrite(right_dir,LOW);
                analogWrite(right_speed,125);
                digitalWrite(left_dir,LOW);
                analogWrite(left_speed,0);
        }

        else
        if (l>lm && c>cm && r>rm) //WBB (6) left motion
        {
                digitalWrite(right_dir,LOW);
                analogWrite(right_speed,20);
                digitalWrite(left_dir,LOW);
                analogWrite(left_speed,20);

                if (fr>frm) //WBB (6) left motion
                {
                        digitalWrite(right_dir,LOW);
                        analogWrite(right_speed,125);
                        digitalWrite(left_dir,LOW);
                        analogWrite(left_speed,0);
                        delay(250);
                }

                else
                if (fl>flm) //WBB (6) left motion
                {
                        digitalWrite(right_dir,LOW);
                        analogWrite(right_speed,0);
                        digitalWrite(left_dir,LOW);
                        analogWrite(left_speed,135);
                        delay(250);
                }
        }
}


//read_sensors function starts here - Function name is self explanatory.....
void read_sensors(){
        fl = analogRead(far_left_sensor);
        l = analogRead(left_sensor);
        c = analogRead(center_sensor);
        r = analogRead(right_sensor);
        fr = analogRead(far_right_sensor);
}

//Short Path function shortens the path to be taken by the bot during the rerun....
//This function hasn't been integrated to the main code yet, as the unstable motion of the bot makes path scanning inaccurate.....
void shortPath(){
     int shortDone=0;
     if(path[pathLength-3]=='L' && path[pathLength-1]=='R'){
          pathLength-=3;
          path[pathLength]='B';
          //Serial.println("test1");
          shortDone=1;
     }

     if(path[pathLength-3]=='L' && path[pathLength-1]=='S' && shortDone==0){
          pathLength-=3;
          path[pathLength]='R';
          //Serial.println("test2");
          shortDone=1;
     }

     if(path[pathLength-3]=='R' && path[pathLength-1]=='L' && shortDone==0){
          pathLength-=3;
          path[pathLength]='B';
          //Serial.println("test3");
          shortDone=1;
     }


     if(path[pathLength-3]=='S' && path[pathLength-1]=='L' && shortDone==0){
          pathLength-=3;
          path[pathLength]='R';
          //Serial.println("test4");
          shortDone=1;
     }

     if(path[pathLength-3]=='S' && path[pathLength-1]=='S' && shortDone==0){
          pathLength-=3;
          path[pathLength]='B';
          //Serial.println("test5");
          shortDone=1;
     }
     if(path[pathLength-3]=='L' && path[pathLength-1]=='L' && shortDone==0){
          pathLength-=3;
          path[pathLength]='S';
          //Serial.println("test6");
          shortDone=1;
     }
     path[pathLength+1]='D';
     path[pathLength+2]='D';
     pathLength++;
     //Serial.print("Path length: ");
     //Serial.println(pathLength);
     //printPath();
}

//This funnction is for debugging purposes only.....
void printPath(){
     Serial.println("+++++++++++++++++");
     int x;
     while(x<=pathLength){
          Serial.println(path[x]);
          x++;
     }
     Serial.println("+++++++++++++++++");
}

//Replay function is to be called when the trial run of the bot is complete.....
//Note - The utility functions called by this functions such as straight(), turnLeft() and turnRight() are yet to be defined.....
void replay(){
     int readLength = 0;
     read_sensors();
     if(fl<flm && fr<frm){
          //straight();
     }
     else{
          if(path[readLength]=='D'){
               digitalWrite(left_dir, LOW);
               digitalWrite(left_speed, 255);
               digitalWrite(right_dir, LOW);
               digitalWrite(right_speed, 255);
               delay(100);
               digitalWrite(left_dir, LOW);
               digitalWrite(left_speed, 0);
               digitalWrite(right_dir, LOW);
               digitalWrite(right_speed, 0);
          }
          if(path[readLength]=='L'){
               digitalWrite(left_dir, HIGH);
               digitalWrite(left_speed, 50);
               digitalWrite(right_dir, LOW);
               digitalWrite(right_speed, 200);
               delay(300);
               //turnLeft();
          }
          if(path[readLength]=='R'){
               digitalWrite(left_dir, LOW);
               digitalWrite(left_speed, 200);
               digitalWrite(right_dir, HIGH);
               digitalWrite(right_speed, 50);
               delay(300);
               //turnRight();
          }
          if(path[readLength]=='S'){
               digitalWrite(left_dir, LOW);
               digitalWrite(left_speed, 200);
               digitalWrite(right_dir, LOW);
               digitalWrite(right_speed, 200);
               delay(300);
               //straight();
          }
          readLength++;
     }
     replay();
}
