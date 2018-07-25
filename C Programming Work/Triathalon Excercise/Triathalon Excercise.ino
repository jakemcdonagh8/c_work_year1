void setup() {
  // put your setup code here, to run once:
#define DEBUG 1

  const int hourstoseconds = 3600;
  const int minutestoseconds = 60;
  String names[4] = {"Swim", "Bike", "Run", "Total"};

  Serial.begin(9600);
  int athleteid = 0;
  //for (int i = 0; i < 4; i++) {
  while (!Serial.available()) {
    long totaltimes[4] = {0};
    Serial.println();

    Serial.print("Please enter a value for the swim time in hours ");
    totaltimes[0] += readportsfunction() * hourstoseconds ;
    Serial.println();

    Serial.print("Please enter a value for the swim time in minutes ");
    totaltimes[0] += readportsfunction() * minutestoseconds;
    Serial.println();

    Serial.print("Please enter a value for the swim time in seconds ");
    totaltimes[0] += readportsfunction();
    Serial.println();
    /* The following code calculates the total time of the swimming event
     * in seconds, converting it from the hours and minute into seconds.
     */



    Serial.print("Please enter a value for the bike cycling time in hours ");
    totaltimes[1] += readportsfunction() * hourstoseconds;
    Serial.println();


    Serial.print("Please enter a value for the bike cycling time in minutes ");
    totaltimes[1] += readportsfunction() * minutestoseconds;
    Serial.println();

    Serial.print("Please enter a value for the bike cycling time in seconds ");
    totaltimes[1] += readportsfunction();
    Serial.println();
    /* The following code calculates the total time of the bike event
      * in seconds, converting it from the hours and minute into seconds.
      */



    Serial.print("Please enter a value for the run time in hours ");
    totaltimes[2] += readportsfunction() * hourstoseconds;
    Serial.println();

    Serial.print("Please enter a value for the run time in minutes ");
    totaltimes[2] += readportsfunction() * minutestoseconds;
    Serial.println();

    Serial.print("Please enter a value for the run time in seconds ");
    totaltimes[2] += readportsfunction();
    Serial.println();
    /* The following code calculates the total time of the running event
        * in seconds, converting it from the hours and minute into seconds.
        */

    totaltimes[3] = totaltimes[0] + totaltimes[1] + totaltimes[2];

    long athletetime = totaltimes[3];

    athleteid = athleteid + 1;

#ifdef DEBUG
    Serial.print("Athlete ID:");
    Serial.println(athleteid);
    Serial.print("Athlete's time:");
    Serial.println(athletetime);
#endif


    int hours;
    int minutes;
    int seconds;

    for (int n = 0; n < 4; n++) {

      hours = totaltimes[n] / hourstoseconds;
      minutes = (totaltimes[n] / minutestoseconds) % minutestoseconds;
      seconds = totaltimes[n] % minutestoseconds;

      Serial.print(names[n]);
      Serial.print(" ");
      Serial.print("time= ");
      Serial.print(hours);
      Serial.print(" hours ");
      Serial.print(minutes);
      Serial.print(" minutes ");
      Serial.print(seconds);
      Serial.println(" seconds ");
    }
long comparetime;
    
    if (comparetime < totaltimes[3]) {
     
    Serial.println();
    Serial.print("The fastest athlete was No ");
    Serial.print(athleteid);
    Serial.print(" ");
    Serial.print("with a time of ");
    Serial.print(hours);
    Serial.print(" hours ");
    Serial.print(minutes);
    Serial.print(" minutes ");
    Serial.print(seconds);
    Serial.println(" seconds ");
    
    comparetime = totaltimes[3];
    }
  }
}

long readportsfunction() {
  long result;

  while (!Serial.available()) {
    // wait for the user to enter a value
    ;
  }
  result = Serial.parseInt();
#ifdef DEBUG
  Serial.print(" ");
  Serial.print(result);
#endif
  return result;
}


void loop() {
  // put your main code here, to run repeatedly:
}
