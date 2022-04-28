int num1;
int num2;
int num3;
int num4;
int num5;
int num6;
int num7;
int num8;

int x;
int y;

int tester;
printString("Hello there!\n");

num1 = 10 + 2;
num2 = 20 * 3 + num1;
num3 = num2 - num1;
num4 = num3 / 20;
num5 = num3 % 21;
num6 = num5 + -num4;
num7 = -2 ^ 9;

print(num1);
print(num2);
print(num3);
print(num4);

printLines(num4);
printSpaces(num1);

print(num5);
print(-num5);
print(num6);
print(num7);

if(num7 == -512){
    print(num7 * 2);
}

num7 = 2 * 5 ^ 2;
print(num7);

num7 = (2 + 5) * 6;
print(num7);

printString("\nGoodbye!\n\n");

num8 = 10;
if((num8 == 10)){
    printString("10 == 10, Good Job!\n");
}

if(num8 < 11){
    printString("10 < 11, Good Job!\n");
}

if(num8 <= 10){
    printString("10 <= 10, Good Job!\n");
}

if(num8 >= 10){
    printString("10 >= 10, Good Job!\n");
}

if(num8 > 9){
    printString("10 > 9, Good Job!\n");
}

if(num8 != 11){
    printString("10 != 11, Good Job!\n");
}

x = 10;
y = 11;

if ((x == 10) || (y != 11)) {
    printString("True1\n");
}

if ((x < 11) && (y >= 10)) {
    printString("True2\n");
}

if (!(x == 10 && (y > 11 && x >= 10))) {
    printString("True3\n");
}

if (!(!((x > 10) || (x < y)))) {
    printString("True4\n");
}

if(!(x > 10)){
    printString("True5\n");
}

printLines(1);
print(x+y, num1^2, num3);
printLines(2);

tester = 0;

while(tester < 5) {
    printString("TESTER!\n");
    tester = tester + 1;
}

printLines(1);

for(tester = 0; tester < 10; tester = tester + 1) {
    printString("FOR LOOP!\n");
}