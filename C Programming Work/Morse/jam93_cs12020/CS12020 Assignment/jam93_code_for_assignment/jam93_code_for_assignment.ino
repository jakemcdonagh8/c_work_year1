//Below is a list of chars that dictate what the ASCII character values look like in MACE code.
//NOTE: MACE code only cosists of the following characters; ^, = or $.
//NOTE: After each sequence of MACE, the separator between two characters forming the same word is a '/' character. This is identical to the separator found in morse.

//The Alphabet:
char mace_a[] = "=";
char mace_b[] = "^^=";
char mace_c[] = "^=$";
char mace_d[] = "=^";
char mace_e[] = "^";
char mace_f[] = "^=^";
char mace_g[] = "==";
char mace_h[] = "^==";
char mace_i[] = "^^";
char mace_j[] = "=^^";
char mace_k[] = "^$";
char mace_l[] = "^^$";
char mace_m[] = "^=";
char mace_n[] = "=$";
char mace_o[] = "$=";
char mace_p[] = "$^";
char mace_q[] = "=^$";
char mace_r[] = "^$=";
char mace_s[] = "^$^";
char mace_t[] = "$";
char mace_u[] = "$$";
char mace_v[] = "==^";
char mace_w[] = "==$";
char mace_x[] = "=$^";
char mace_y[] = "^$$";
char mace_z[] = "===";

//Numerical Values:
char mace_1[] = "$^^=";
char mace_2[] = "$^^$";
char mace_3[] = "$^=^";
char mace_4[] = "$^==";
char mace_5[] = "$^=$";
char mace_6[] = "$^$^";
char mace_7[] = "$^$=";
char mace_8[] = "$^$$";
char mace_9[] = "$=^^";
char mace_0[] = "$^^^";

//Punctuation:
char mace_fullstop[] = "$^^";
char mace_comma[] = "$^=";
char mace_apostrophe[] = "$=^";
char mace_question_mark[] = "$==";
char mace_exclamation_mark[] = "$=$";
char mace_space[] = " ";

//Mathematical Operators:
char mace_plus[] = "$$^";
char mace_minus[] = "$$=";
char mace_multiply[] = "$$$";
char mace_divide[] = "$^$";
char mace_equals[] = "$===$";

//Declaring the LED pins on the Arduino Uno. This is needed in order to properly transmit the MACE code to the user.
/*NOTE: BLUELED is strictly used to transmit any unmodified MACE back to the user. The other 4 colours can be used for the decoded MACE code.
 *The varying  brightness of the outputted message can be changed via typing in LP 000 000 000 000 (Where 0 is the PWM instensity of each LED)
  */
int REDLED = 5;
int ORANGELED = 6;
int YELLOWLED = 9;
int GREENLED = 10;
int BLUELED = 11;


//Declaraing the Potentiometer pin for the Arduino. This is used in order to change the transmit frequency of the MACE code.
//NOTE: The potentiometer is the blue switch towards the USB connector on the red shield. The frequency can be changed via rotating the switch clockwise or anti-clockwise
//before the code is transmitted. The frequency cannot be changed during transmission.
int POTENTIOMETER = A0;


//Declaring the Infrared LED pin for the Arduino. This will be used if the user inputs a certain data message (In this case, +-IR). In this particular case, this will turn the infrared
//LED on for 1000 milliseconds before turning itself off once again.
int INFRARED = A1;

//Declaring the types of inputs that are used throughout the program. The maceIp variable saves the input of the MACE code whilst the asciiIP variable saves
//The input of the ASCII string message. The input variables used within both the userinput() and void loop() functions.
String maceIp;
String asciiIp;
String input;

int pwmarray[11] = {0};

void setup() {
  //The beginning of the program. At this point, the pins being used are cuurently being set to either behave as an input or an output.
  //For this program, the LED's being used will be the output pins and the Potentiometer is the input pin.
  Serial.begin(9600);

  pinMode(REDLED, OUTPUT);
  pinMode(ORANGELED, OUTPUT);
  pinMode(YELLOWLED, OUTPUT);
  pinMode(GREENLED, OUTPUT);
  pinMode(BLUELED, OUTPUT);
  pinMode(INFRARED, OUTPUT);

  pinMode(POTENTIOMETER, INPUT);
}

void loop() {
  //This section of the program repeats indefinitely until the program itself closes. During this section, the program
  //waits for the user to input in either a ASCII or MACE value. Depending on the string entered, one of the two following functions
  //will be called.
  userinput();

  //If the first character presented is a MACE character then call the MACEStringtoASCII function, which converts the MACE to ASCII.
  //Otherwise, the value must be in ASCII and hence, convert the string into MACE code.
  if (input[0] == '$' || input[0] == '^' || input[0] == '=') {
    maceIp = input;
    asciiIp = MACEStringtoASCII(input);
  }
  else {
    asciiIp = input;
    maceIp = ASCIIStringtoMACE(input);
  }

  //If the first character presented was a MACE character then the function will use a Blue LED. Otherwise it will use a Red LED by default.
  if (input[0] == '$' || input[0] == '^' || input[0] == '=') {
    Serial.println(asciiIp);
    OutputLED(BLUELED, maceIp);
  }
  else {
    Serial.println(maceIp);
    OutputLED(REDLED, maceIp);
  }

  //If the first two characters are "LP" then run the following code below. The program will read each of the 3 blocks of digits and concatenates them together to form a number between
  //0 and 255, where 255 means the LED is at it's brightest and 0 is when the LED is turned off.
  //NOTE: Simply typing in "LP" will result in all of the LEDs turning off.
  if (input[0] == 'L' && input[1] == 'P') {
    for (int j = 2; j < 14; j++) {
      pwmarray[j - 2] = input[j] - 48;
    }
    int concatenateRED = (pwmarray[0] * 100) + (pwmarray[1] * 10) + (pwmarray[2]);
    int concatenateORANGE = (pwmarray[3] * 100) + (pwmarray[4] * 10) + (pwmarray[5]);
    int concatenateYELLOW = (pwmarray[6] * 100) + (pwmarray[7] * 10) + (pwmarray[8]);
    int concatenateGREEN = (pwmarray[9] * 100) + (pwmarray[10] * 10) + (pwmarray[11]);


    //The following statements ensure that the value of each block stay between 0 and 255, in order to prevent any errors that may occur.
    if (concatenateRED > 255) {
      concatenateRED = 255;
    }
    else if (concatenateRED < 0) {
      concatenateRED = 0;
    }

    if (concatenateORANGE > 255) {
      concatenateORANGE = 255;
    }
    else if (concatenateORANGE < 0) {
      concatenateORANGE = 0;
    }

    if (concatenateYELLOW > 255) {
      concatenateYELLOW = 255;
    }
    else if (concatenateYELLOW < 0) {
      concatenateYELLOW = 0;
    }

    if (concatenateGREEN > 255) {
      concatenateGREEN = 255;
    }
    else if (concatenateGREEN < 0) {
      concatenateGREEN = 0;
    }
    analogWrite(REDLED, concatenateRED);
    analogWrite(ORANGELED, concatenateORANGE);
    analogWrite(YELLOWLED, concatenateYELLOW);
    analogWrite(GREENLED, concatenateGREEN);
  }

  //If the following data message "+-IR" was entered, then the IR LED will turn on for 1000 milliseconds and then turn back off.
  if (input[0] == '+' && input[1] == '-' && input[2] == 'I' && input[3] == 'R') {
    unsigned long duration = 1000;
    unsigned int frequency = 38000;

    tone(INFRARED, frequency, duration);
    noTone(INFRARED);
  }

  //If the following data message entered was "XVIR" then send an output message will be sent to the user diplaying if the state is either equal to "HIGH" or "LOW".
  if (input[0] == 'R' && input[1] == 'X' && input[2] == 'I' && input[3] == 'R') {
    if (INFRARED = HIGH) {
      Serial.println("HIGH");
    }
    else if (INFRARED = LOW) {
      Serial.println("LOW");
    }
  }

  //If the following data message entered was "VRV" then the program will read the integer value of the potentiometer and be converted into a 4 decimal digit code by an encoding algorithm.
  //Once the 4 decimal code has been calculated, the encoded code will become converted into MACE.
  if (input[0] == 'V' && input[1] ==  'R' && input[2] == 'V') {
    //This part of the code ensures that the transmission speed of the potentiometer is between 20 and 500ms.
    int VRV = analogRead(POTENTIOMETER);

    if (VRV < 20) {
      VRV = 20;
    }
    else {
      VRV = VRV / 2.046;
      //This is needed as anything slightly above 20 would result in the unit length becoming equal to less than 20.
      if (VRV < 20) {
        VRV = 20;
      }
    }

    //The encoding algorithm used in order to turn the analog reading into an encoded 4 decimal digits.
    do {
      VRV = VRV * 18;
    }
    while (VRV < 1000);

    if (VRV > 10000) {
      VRV = VRV / 2;
    }

    //Once the encoding is done, the program calls a the ASCIIStringtoMACE function in order to convert the newly encoded reading into a MACE sequece.
    String VRVString = String(VRV);

    input = ASCIIStringtoMACE(VRVString);
    Serial.println(input);
  }
}

String userinput() {
  //The following function is repeated indefinitely within the program. It states to the user to enter a value. The program stops running entirely until
  //This is done.
  input = "";

  while (!Serial.available()) {
    ;
  }
  input = Serial.readString();
  return input;
}

void OutputLED(int LED, String message) {
  //The following function transmits the output MACE to the LED. Depending on if the string entered orginally was either ASCII or MACE,
  //then the LED used will be either Red or Blue correspondently. The frequency of the transmission can be altered using the potentiometer.
  int unit = analogRead(POTENTIOMETER);


  //This part of the code ensures that the transmission speed of the potentiometer is between 20 and 500ms.
  if (unit < 20) {
    unit = 20;
  }
  else {
    unit = unit / 2.046;
    //This is needed as anything slightly above 20 would result in the unit length becoming equal to less than 20.
    if (unit < 20) {
      unit = 20;
    }
  }

  for (int k = 0; k < message.length(); k++) {
    if (message[k] == '^') {
      digitalWrite(LED, HIGH);
      delay(unit);
      digitalWrite(LED, LOW);
      delay(unit);
    }
    else if (message[k] == '=') {
      digitalWrite(LED, HIGH);
      delay(unit * 2);
      digitalWrite(LED, LOW);
      delay(unit);
    }
    else if (message[k] == '$') {
      digitalWrite(LED, HIGH);
      delay(unit * 4);
      digitalWrite(LED, LOW);
      delay(unit);
    }
    else if (message[k] == '/') {
      digitalWrite(LED, LOW);
      delay(unit * 3);
    }
    else {
      digitalWrite(LED, LOW);
      delay(unit * 5);
    }
  }
  maceIp = "";
}

String MACEStringtoASCII(String m) {
  //The following function translates the MACE code inputted in by the user in ASCII. It does this by looping through the input and adding each character that
  //is not a /, space or the end of the string to a variable called block. At this point, another function is called to convert the block string into its ASCII value
  //and insert it into the output variable. Finally, the output variable is looped through again in order to remove all of the /'s that the string contains.
  String output = "";
  String outputrefresh = "";
  String block = "";


  //Looping through the inital string to convert the MACE code into ASCII.
  for (int t = 0; t <= m.length(); t++) {
    if (m[t] != '/' && m[t] != ' ' && m[t] != '\0') {
      block += m[t];
    }
    else
    {
      String temp = "";
      temp += MACE2char(block);

      output += temp;
      if (m[t] == (' ')) {
        output += ' ';
      }
      block = "";
    }
  }

  //Looping through the now converted ASCII string to remove all of the /'s within the string.
  for (int j = 0; j < output.length(); j++) {
    if (output[j] == '/') {
      ;
    }
    else {

      outputrefresh += output[j];
    }
  }
  return outputrefresh;
}

String ASCIIStringtoMACE(String s) {
  //The following function takes a string value of ascii characters and converts it into MACE. It does this by looping through the string
  //and calling another function in order to convert each individual character in a sequence of MACE. it then appends this sequence to the end
  //of a variable called value. A / value will also be appended to the variable as long as it reaches the following criteria:

  /*
  1. The current character in question isn't the last character of the string.
  2. The current character in question ia not a space.
  3. The character ahead of the currently selected character is also not a space
  */
  String value = "";
  String temp;

  s.toLowerCase();

  for (int i = 0; i < s.length(); i++) {

    temp = char2MACE(s[i]);

    if (i == s.length() - 1 || s[i] == ' ' || s[i + 1] == ' ') {
      ; // do nothing
    }
    else
    {
      temp += "/";
    }
    value += temp;
  }
  return value;
}

char MACE2char(String m) {
  //The following function converts a string of MACE into a character from the ASCII table. It does this by checking each statement to see
  //if the string is equal to any of the pre defined values of what the MACE code represents. If for some reason the string does not compare with any of the
  //statements, then an error message will be displayed to the user.
  if (m.equals(mace_a)) {
    return 'a';
  }
  else if (m.equals(mace_b)) {
    return 'b';
  }
  else if (m.equals(mace_c)) {
    return 'c';
  }
  else if (m.equals(mace_d)) {
    return 'd';
  }
  else if (m.equals(mace_e)) {
    return 'e';
  }
  else if (m.equals(mace_f)) {
    return 'f';
  }
  else if (m.equals(mace_g)) {
    return 'g';
  }
  else if (m.equals(mace_h)) {
    return 'h';
  }
  else if (m.equals(mace_i)) {
    return 'i';
  }
  else if (m.equals(mace_j)) {
    return 'j';
  }
  else if (m.equals(mace_k)) {
    return 'k';
  }
  else if (m.equals(mace_l)) {
    return 'l';
  }
  else if (m.equals(mace_m)) {
    return 'm';
  }
  else if (m.equals(mace_n)) {
    return 'n';
  }
  else if (m.equals(mace_o)) {
    return 'o';
  }
  else if (m.equals(mace_p)) {
    return 'p';
  }
  else if (m.equals(mace_q)) {
    return 'q';
  }
  else if (m.equals(mace_r)) {
    return 'r';
  }
  else if (m.equals(mace_s)) {
    return 's';
  }
  else if (m.equals(mace_t)) {
    return 't';
  }
  else if (m.equals(mace_u)) {
    return 'u';
  }
  else if (m.equals(mace_v)) {
    return 'v';
  }
  else if (m.equals(mace_w)) {
    return 'w';
  }
  else if (m.equals(mace_x)) {
    return 'x';
  }
  else if (m.equals(mace_y)) {
    return 'y';
  }
  else if (m.equals(mace_z)) {
    return 'z';
  }
  else if (m.equals(mace_1)) {
    return '1';
  }
  else if (m.equals(mace_2)) {
    return '2';
  }
  else if (m.equals(mace_3)) {
    return '3';
  }
  else if (m.equals(mace_4)) {
    return '4';
  }
  else if (m.equals(mace_5)) {
    return '5';
  }
  else if (m.equals(mace_6)) {
    return '6';
  }
  else if (m.equals(mace_7)) {
    return '7';
  }
  else if (m.equals(mace_8)) {
    return '8';
  }
  else if (m.equals(mace_9)) {
    return '9';
  }
  else if (m.equals(mace_0)) {
    return '0';
  }
  else if (m.equals(mace_fullstop)) {
    return '.';
  }
  else if (m.equals(mace_comma)) {
    return ',';
  }
  else if (m.equals(mace_apostrophe)) {
    return '\'';
  }
  else if (m.equals(mace_question_mark)) {
    return '?';
  }
  else if (m.equals(mace_exclamation_mark)) {
    return '!';
  }
  else if (m.equals(mace_space)) {
    return ' ';
  }
  else if (m.equals(mace_plus)) {
    return '+';
  }
  else if (m.equals(mace_minus)) {
    return '-';
  }
  else if (m.equals(mace_multiply)) {
    return '*';
  }
  else if (m.equals(mace_divide)) {
    return '/';
  }
  else if (m.equals(mace_equals)) {
    return '=';
  }
  else
    Serial.print("ERROR:System has not correctly identified the MACE code for this character");
  delay(100);
}

char * char2MACE(char c) {
  //This function is used to convert a character from the ascii table into a MACE sequence. It does this by using case statements in order
  //to compare the current character from the loop previous to this function being called. Once it has found the same case statement, it will return the
  //MACE value of said character back to the char2MACE function. If it doesen't find any statements which equal the current sequence, then an error message will be displayed.
  switch (c) {
    case 'a':
      return mace_a;
    case 'b':
      return mace_b;
    case 'c':
      return mace_c;
    case 'd':
      return mace_d;
    case 'e':
      return mace_e;
    case 'f':
      return mace_f;
    case 'g':
      return mace_g;
    case 'h':
      return mace_h;
    case 'i':
      return mace_i;
    case 'j':
      return mace_j;
    case 'k':
      return mace_k;
    case 'l':
      return mace_l;
    case 'm':
      return mace_m;
    case 'n':
      return mace_n;
    case 'o':
      return mace_o;
    case 'p':
      return mace_p;
    case 'q':
      return mace_q;
    case 'r':
      return mace_r;
    case 's':
      return mace_s;
    case 't':
      return mace_t;
    case 'u':
      return mace_u;
    case 'v':
      return mace_v;
    case 'w':
      return mace_w;
    case 'x':
      return mace_x;
    case 'y':
      return mace_y;
    case 'z':
      return mace_z;
    case '1':
      return mace_1;
    case '2':
      return mace_2;
    case '3':
      return mace_3;
    case '4':
      return mace_4;
    case '5':
      return mace_5;
    case '6':
      return mace_6;
    case '7':
      return mace_7;
    case '8':
      return mace_8;
    case '9':
      return mace_9;
    case '0':
      return mace_0;
    case '.':
      return mace_fullstop;
    case ',':
      return mace_comma;
    case '\'':
      return mace_apostrophe;
    case '?':
      return mace_question_mark;
    case '!':
      return mace_exclamation_mark;
    case ' ':
      return mace_space;
    case '+':
      return mace_plus;
    case '-':
      return mace_minus;
    case '*':
      return mace_multiply;
    case '/':
      return mace_divide;
    case '=':
      return mace_equals;
    default:
      Serial.println("ERROR:Mace sequence does not equal any sequence that can be found. Please ensure that you typed the MACE sequence in correctly.");
      break;
  }
  delay(100);
}
