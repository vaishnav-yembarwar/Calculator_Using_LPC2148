#include <LPC214X.H>
#define rs (1<<8)
#define en (1<<9)
#define c1 (1<<16)
#define c2 (1<<17)
#define c3 (1<<18)
#define c4 (1<<19)
#define r1 (1<<20)
#define r2 (1<<21)
#define r3 (1<<22)
#define r4 (1<<23)



void cmd(char);
void dat(char);
void delay(int);
void lcdinit();
char keypad(void);
void displayresult(int result);
int chartoint(char c);
char c;      //global variable



void delay(int a)
{
int i,j;
for(i=0;i<a;i++)
for(j=0;j<233;j++);
}

int main()
{
char var1,var2,sign;
int result = 0;
IO0DIR=0X000003FF;
IO1DIR=0X00F00000;

lcdinit();
while(1)
{

var1=keypad();
dat(var1);
delay(1000);

sign=keypad();
dat(sign);
delay(1000);

    var2=keypad();
dat(var2);
delay(1000);

switch(sign)
{
case'+':
result=chartoint(var1) + chartoint(var2);
break;

case'-':
result=chartoint(var1) - chartoint(var2);
break;

case'*':
result=chartoint(var1) * chartoint(var2);
break;

case'/':
if (chartoint(var2)!=0)
result=chartoint(var1) / chartoint(var2);
else
result = 0;
break;
case' ':
result=0;
break;
default:
result=0;
}
cmd(0x01);
displayresult(result);
delay(1000);

}
}
void lcdinit()
{
cmd(0x38);  // Set 8-bit interface, 2 lines, 5x7 dots
cmd(0x0F);  // Display ON, cursor ON, blink ON
cmd(0x01);  // Clear display
cmd(0x06);  // Entry mode: move right, no shift
}


void cmd(char cmd)
{
  IO0PIN=cmd;
IO0CLR=rs;
IO0SET=en;
delay(1);
IO0CLR=en;
}

void dat(char dat)
 {
  IO0PIN=dat;
IO0SET=rs;
IO0SET=en;
delay(1);
IO0CLR=en;
}
 

char keypad()
{
while(1)
{
IO1CLR=r1;
IO1SET=r2|r2|r4;

if(!(IO1PIN&c1))
{
while(!(IO1PIN&c1));
return'7';
}
if(!(IO1PIN&c2))
{
while(!(IO1PIN&c2));
return'8';
}
if(!(IO1PIN&c3))
{
while(!(IO1PIN&c3));
return'9';
}
if(!(IO1PIN&c4))
{
while(!(IO1PIN&c4));
return'/';
}
IO1CLR=r2;
IO1SET=r1|r3|r4;

if(!(IO1PIN&c1))
{
while(!(IO1PIN&c1));
return'4';
}
if(!(IO1PIN&c2))
{
while(!(IO1PIN&c2));
return'5';
}
if(!(IO1PIN&c3))
{
while(!(IO1PIN&c3));
return'6';
}
if(!(IO1PIN&c4))
{
while(!(IO1PIN&c4));
return'*';
}
IO1CLR=r3;
IO1SET=r1|r2|r4;

if(!(IO1PIN&c1))
{
while(!(IO1PIN&c1));
return'1';
}
if(!(IO1PIN&c2))
{
while(!(IO1PIN&c2));
return'2';
}
if(!(IO1PIN&c3))
{
while(!(IO1PIN&c3));
return'3';
}
if(!(IO1PIN&c4))
{
while(!(IO1PIN&c4));
return'-';
}
IO1CLR=r4;
IO1SET=r1|r2|r3;

if(!(IO1PIN&c1))
{
while(!(IO1PIN&c1));
return' ';
}
if(!(IO1PIN&c2))
{
while(!(IO1PIN&c2));
return'0';
}
if(!(IO1PIN&c3))
{
while(!(IO1PIN&c3));
return'=';
}
if(!(IO1PIN&c4))
{
while(!(IO1PIN&c4));
return'+';
}
}
}


void displayresult(int result) {
   
if (result > 10) {
	 dat((result / 100) + '0');
   dat((result / 10) + '0');
  dat((result % 10) + '0');
    }
    // Display each digit of the result
    if (result < 10) 
		{
		dat((result / 10) + '0');
    dat((result % 10) + '0');
    }
}

int chartoint(char c) {
    return c - '0'; // Convert char to int
}
