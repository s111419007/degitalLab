#define ROW1 A5
#define ROW2 A4
#define ROW3 A0
#define ROW4 11
#define ROW5 4
#define ROW6 9
#define ROW7 8
#define ROW8 A2
#define COL1 10
#define COL2 7
#define COL3 12
#define COL4 6
#define COL5 A1
#define COL6 13
#define COL7 A3
#define COL8 5

const int row[8] = {
  ROW1, ROW2, ROW3, ROW4, ROW5, ROW6, ROW7, ROW8
};

const int col[8] = {
  COL1, COL2, COL3, COL4, COL5, COL6, COL7, COL8
};

byte incomingByte;
byte (*current)[8];

byte scan[8][8] = {
    {1,0,0,0,0,0,0,0},
    {0,1,0,0,0,0,0,0},
    {0,0,1,0,0,0,0,0},
    {0,0,0,1,0,0,0,0},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,0,1,0,0},
    {0,0,0,0,0,0,1,0},
    {0,0,0,0,0,0,0,1}
};

byte turnOff[8][8] = {
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1}
};

byte circle[8][8] = {
    {1,1,0,0,0,0,1,1},
    {1,0,1,1,1,1,0,1},
    {0,1,1,1,1,1,1,0},
    {0,1,1,1,1,1,1,0},
    {0,1,1,1,1,1,1,0},
    {0,1,1,1,1,1,1,0},
    {1,0,1,1,1,1,0,1},
    {1,1,0,0,0,0,1,1}
};

byte H[8][8] = {
    {1,0,1,1,1,1,0,1},
    {1,0,1,1,1,1,0,1},
    {1,0,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,0,1},
    {1,0,1,1,1,1,0,1},
    {1,0,1,1,1,1,0,1}
};

byte A[8][8] = {
    {1,1,1,0,0,1,1,1},
    {1,1,0,1,1,0,1,1},
    {1,0,1,1,1,1,0,1},
    {1,0,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,0,1},
    {1,0,1,1,1,1,0,1},
    {1,0,1,1,1,1,0,1}
};

void setup()
{
    Serial.begin(9600);
    for (byte i = 0; i <= sizeof(row); i++) {
        pinMode(row[i], OUTPUT);
    }

    for (byte i = 0; i <= sizeof(col); i++) {
        pinMode(col[i], OUTPUT);
    }
    pinMode(2, INPUT_PULLUP);
}

void loop()
{
    if(Serial.available() > 0){
        incomingByte = Serial.read();
    }
    if(incomingByte == 'c') current = circle;
    else if(incomingByte == 'H') current = H;
    else if(incomingByte == 'A') current = A;
    else if(incomingByte == 's') current = turnOff;

    showPattern(current);
}

void showPattern(byte matrix[8][8]){
    for(byte i = 0; i < 8; i++){
        for(byte j = 0; j < 8; j++){
            digitalWrite(row[j], 1 - scan[i][j]);
            digitalWrite(col[j], 1 - matrix[i][j]);
        }
        for(byte j = 0; j < 8; j++){
            digitalWrite(row[j], HIGH);
            digitalWrite(col[j], LOW);
        }
    }
}

