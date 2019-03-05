int l,c,r,lm,cm,rm,bl,wl,bc,wc,br,wr,fl,fr,flm,frm,bfl,wfl,bfr,wfr;

/*

l = leftsensor input
r = rightsensor input
c = centersensor input
lm = leftsensor average reading
rm = rightsensor average reading
cm = centersensor average reading
bl = black reading from left sensor
wl = white reading from left sensor
bc = black reading from center sensor
wc = white reading from center sensor
br = black reading from right sensor
wr = white reading from right sensor

*/

void setup() {

        pinMode (A6,INPUT);    //left sensor
        pinMode (A5,INPUT);    //center sensor
        pinMode (A1,INPUT);    //right sensor
        pinMode (A3,INPUT);    //farleft sensor
        pinMode (A0,INPUT);    //farright sensor
        pinMode (2,OUTPUT);    //right motor direction
        pinMode (3,OUTPUT);    //right motor speed
        pinMode (4,OUTPUT);    //left motor direction
        pinMode (5,OUTPUT);    //left motor speed
        pinMode (10,OUTPUT);    //left motor enable
        pinMode (9,OUTPUT);    //right motor enable
        pinMode (13,OUTPUT);    //Led
        /*

        Sensing to calibrate

        */
  digitalWrite(13,LOW);
  delay(1000);
  digitalWrite(13,HIGH);
  delay(2000);

  bl = analogRead (A1);
  bc = analogRead (A5);
  br = analogRead (A6);
  bfl = analogRead (A0);
  bfr = analogRead (A3);
  delay(2000);
  digitalWrite(13,LOW);
  delay(2000);

  digitalWrite(13,HIGH);
  delay(2000); //time to change color to calibrate

  wl = analogRead (A1);
  wc = analogRead (A5);
  wr = analogRead (A6);
  wfl = analogRead (A0);
  wfr = analogRead (A3);
  delay(2000);
  digitalWrite(13,LOW);
  delay(3000);

  flm  = (bfl+wfl)/2;
  lm = (bl+wl)/2;
  cm = (wc+bc)/2;
  rm = (wr+br)/2;
  frm = (bfr+wfr)/2;
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  Serial.begin(9600);

}

void loop() {

        fr = analogRead (A0);
        r = analogRead (A1);
        c = analogRead (A5);
        l = analogRead (A6);
        fl = analogRead (A3);

        if (fl<flm && c<cm) //BWB (1) straight motion
        {
                digitalWrite(2,LOW);
                analogWrite(3,125);
                digitalWrite(4,LOW);
                analogWrite(5,135);
        }
        else
        if (fl<flm && l<lm && c<cm && r<rm && fr<frm) //BBB (2)
        {
                digitalWrite(2,HIGH);
                analogWrite(3,200);
                digitalWrite(4,HIGH);
                analogWrite(5,190);
        }
        else
        if (l<lm && c<cm && r>rm) //BBW (3) right motion
        {
                digitalWrite(2,LOW);
                analogWrite(3,0);
                digitalWrite(4,LOW);
                analogWrite(5,135);
        }
        else
        if (l<lm && c<cm && fr>frm) //BWW (4) sharp right motion
        {
                digitalWrite(2,HIGH);
                analogWrite(3,200);
                digitalWrite(4,LOW);
                analogWrite(5,135);
        }
        else
        if (l<lm && c>cm && r>rm) //BWW (4) sharp right motion
        {
                digitalWrite(2,HIGH);
                analogWrite(3,200);
                digitalWrite(4,LOW);
                analogWrite(5,135);
        }
        else
        if (fr>frm) //BWW (4) sharp right motion
        {
                digitalWrite(2,HIGH);
                analogWrite(3,200);
                digitalWrite(4,LOW);
                analogWrite(5,135);
                delay(250);
        }
        else
        if (fr>frm && c>cm && l>lm) //BWW (4) sharp right motion
        {
                digitalWrite(2,HIGH);
                analogWrite(3,200);
                digitalWrite(4,LOW);
                analogWrite(5,135);
                delay(250);
        }
        else
        if (fr>frm && c>cm) //BWW (4) sharp right motion
        {
                digitalWrite(2,HIGH);
                analogWrite(3,200);
                digitalWrite(4,LOW);
                analogWrite(5,135);
                delay(250);
        }
        else
        if (fl>flm && r<rm) //WWB (5) sharp left motion
        {
                digitalWrite(2,LOW);
                analogWrite(3,125);
                digitalWrite(4,HIGH);
                analogWrite(5,190);
        }
        else
        if (l>lm && c>cm) //WWB (5) sharp left motion
        {
                digitalWrite(2,LOW);
                analogWrite(3,125);
                digitalWrite(4,HIGH);
                analogWrite(5,190);
        }
        else
        if (fl>flm) //WWB (5) sharp left motion
        {
                digitalWrite(2,LOW);
                analogWrite(3,125);
                digitalWrite(4,HIGH);
                analogWrite(5,190);
                delay(250);
        }
        else
        if (fl>flm && c>cm && r>rm) //WWB (5) sharp left motion
        {
                digitalWrite(2,LOW);
                analogWrite(3,125);
                digitalWrite(4,HIGH);
                analogWrite(5,190);
                delay(250);
        }
        else
        if (fl>flm && c>cm) //WWB (5) sharp left motion
        {
                digitalWrite(2,LOW);
                analogWrite(3,125);
                digitalWrite(4,HIGH);
                analogWrite(5,190);
                delay(250);
        }
        else
        if (lm && r>rm) //WBB (6) left motion  - Condition to be checked
        {
                digitalWrite(2,LOW);
                analogWrite(3,125);
                digitalWrite(4,LOW);
                analogWrite(5,0);
        }

        else
        if (l>lm && c>cm && r>rm) //WBB (6) left motion
        {
                digitalWrite(2,LOW);
                analogWrite(3,20);
                digitalWrite(4,LOW);
                analogWrite(5,20);

                if (fr>frm) //WBB (6) left motion
                {
                        digitalWrite(2,LOW);
                        analogWrite(3,125);
                        digitalWrite(4,LOW);
                        analogWrite(5,0);
                        delay(250);
                }

                else
                if (fl>flm) //WBB (6) left motion
                {
                        digitalWrite(2,LOW);
                        analogWrite(3,0);
                        digitalWrite(4,LOW);
                        analogWrite(5,135);
                        delay(250);
                }
        }
}
