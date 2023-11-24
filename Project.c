#include <LPC17xx.h>
#include <stdio.h>
#include <string.h>
int temp1,temp2,flag1,i,j,k,l,m;
int row,x,col;
void clock_wise(void);
void anti_clock_wise(void);
unsigned long int var1,var2;
int pass_len=0,sense=-1;
int command[] = {0x30,0x30,0x30,0x20,0x28,0x01,0x06,0x0C,0x80};
char pass[32];
long int seven[4][4]={{0,1,2,3},{4,5,6,7},{8,9,0xa,0xb},{0xc,0xd,0xe,0xf}};
char message[]="Welcome";
char yes[]="YES !!";
char no[]="NO !!";
char clear[]="                  ";
char enter_pass[]="Enter Password";

 
void port_write(){
	LPC_GPIO0->FIOPIN = temp2<<23;
	if(flag1==0){
		LPC_GPIO0->FIOCLR=1<<27;
	}
	else{
		LPC_GPIO0->FIOSET=1<<27;
	}
	LPC_GPIO0->FIOSET=1<<28;
	for(j=0;j<50;j++);
	LPC_GPIO0->FIOCLR=1<<28;
	for(j=0;j<30000;j++);
}
void lcd_write(){
	temp2=(temp1>>4)&0xF;
	port_write();
	if( ! (flag1==0 && (temp1==0x20 || temp1 == 0x30) )){
		temp2 = temp1& 0xF;
		port_write();
	}
}
void clock_wise(void) //Stepper motor
{
var1 = 0x00000080; //For Clockwise
for(m=0;m<=3;m++) // for A B C D Stepping
{
//var1 = var1<<1; //For Clockwise
//var2 = ~var1;
//var2 = var2 & 0x000000F0;
	LPC_GPIO0->FIOMASK=0XFFFFFF0F;
LPC_GPIO0->FIOPIN = var1 ;         //~var1;
	LPC_GPIO0->FIOMASK=0X00000000;
//LPC_GPIO0->FIOSET = var1;
//LPC_GPIO0->FIOCLR = var2;
	var1=var1>>1;
for(k=0;k<60000;k++); //for step speed variation
}
}
 
void keyboard(){
	while(1){
		//if((LPC_GPIO0->FIOPIN)& (1<<4)){
			int keypressed=0;
			int br=0;
			flag1=0;
			for( i=0;i<9;i++){ temp1 = command[i]; lcd_write();}
			flag1=1;
			i=0;
			while(enter_pass[i] != '\0'){
					if(i==16){
						flag1=0;
						temp1=0xC0;
						lcd_write();
					}
					flag1=1;
					temp1=enter_pass[i];
					lcd_write();
				for(row=0;row<4;row++)
				{
					LPC_GPIO2->FIOPIN=1<<(10+row);
					for(k=0;k<50;k++);
					x=(LPC_GPIO1->FIOPIN>>23)&0XF;
					if(x)
					{
						if(x==1)
							col=0;
						else if(x==2)
							col=1;
						else if(x==4)
							col=2;
						else if(x==8)
							col=3;
						sprintf(pass, "%ld", seven[row][col]);
						keypressed=1;
						break;
					}
					for(k=0;k<=50;k++);
				}
				if(keypressed){
					br=1;
					break;
				}
				for(k=0;k<500000;k++);
				i++;
			}
			if(br){
				break;
			}
		//}
	}
	flag1=0;
	temp1=0x01;
	lcd_write();
	for(i=0;i<1000;i++);
	i=0;
	while(pass[i] != '\0'){
		if(i==16){
			flag1=0;
			temp1=0xC0;
			lcd_write();
		}
		flag1=1;
		//temp1=pass[i];
		temp1=42;
		lcd_write();
		for(k=0;k<500000;k++);
		i++;
	}
	pass_len=1;
	while(1){
		long int number;
		int keypressed=0;
		for(row=0;row<4;row++)
		{
			LPC_GPIO2->FIOPIN=1<<(10+row);
			for(k=0;k<50;k++);
			x=(LPC_GPIO1->FIOPIN>>23)&0XF;
			if(x)
			{
				if(x==1)
					col=0;
				else if(x==2)
					col=1;
				else if(x==4)
					col=2;
				else if(x==8)
					col=3;
				for(k=0;k<5000;k++);
				number = seven[row][col];
				if(number==0xf){
					keypressed=1;
					break;
				}
				if(number>=0 && number<=9){
					sprintf(pass+pass_len,"%ld",number);
				}
				else if(number>=0xa && number <=0xf){
					char hexChars[]="ABCDEF";
					char hexChar = hexChars[number - 10];
					sprintf(pass+pass_len,"%c",hexChar);
				}
				pass_len++;
				flag1=1;
				//temp1=pass[pass_len-1];
				temp1=42;
				lcd_write();
				if(pass_len==16){
					flag1=0;
					temp1=0xC0;
					lcd_write();
				}
			}
			for(k=0;k<=500000;k++);
		}
		if(keypressed){
			break;
		}
	}
	flag1=0;
	temp1=0x01;
	lcd_write();
	i=0;
	while(pass[i] != '\0'){
		if(i==16){
			flag1=0;
			temp1=0xC0;
			lcd_write();
		}
		flag1=1;
		temp1=pass[i];
		lcd_write();
		for(k=0;k<500000;k++);
		i++;
	}
	if(strcmp(pass,"1234")==0){
		flag1=0;
		temp1=0x01;
		lcd_write();
		i=0;
		while(yes[i] != '\0'){
			if(i==16){
				flag1=0;
				temp1=0xC0;
				lcd_write();
			}
			flag1=1;
			temp1=yes[i];
			lcd_write();
			for(k=0;k<500000;k++);
			i++;
			for(j=0;j<20;j++) // 20 times in Clock wise Rotation
				clock_wise();
			for(k=0;k<65000;k++); 
		}
	}
	else{
		flag1=0;
		temp1=0x01;
		lcd_write();
		i=0;
		while(no[i] != '\0'){
			if(i==16){
				flag1=0;
				temp1=0xC0;
				lcd_write();
			}
			flag1=1;
			temp1=no[i];
			lcd_write();
			for(k=0;k<800000;k++);
			i++;
		}
		for(k=0;k<3;k++){
			LPC_GPIO0->FIOSET=1<<11;
			for(l=0;l<1000000;l++);
			LPC_GPIO0->FIOCLR=1<<11;
			for(l=0;l<900000;l++);
		}
	}
}
int main(){
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL1 = 0;
	LPC_PINCON->PINSEL0=0;
	LPC_PINCON->PINSEL3=0;
	LPC_PINCON->PINSEL4=0;
	LPC_GPIO0->FIODIR=0XFFFF7FFF ; // lcd
	LPC_GPIO2->FIODIR=0XF<<10; // keyboard row
	// ------------- SENSOR -------------
	LPC_PINCON->PINSEL3 = 0; //SENSOR
	LPC_GPIO0->FIODIR |= 0xFF<<4;
	LPC_GPIO1->FIODIR = 0;
	//---------------END-----------------
	flag1=0;
	for( i=0;i<9;i++){ temp1 = command[i]; lcd_write();}
while(1){
redirect:
	flag1=0;
	temp1=0x01;
	lcd_write();
	i=0;
	while(message[i] != '\0'){
		if(i==16){
			flag1=0;
			temp1=0xC0;
			lcd_write();
		}
		flag1=1;
		temp1=message[i]; 
		lcd_write();
		for(k=0;k<500000;k++);
		i++;
	}
	//while(1){
	sense=LPC_GPIO0->FIOPIN&1<<15;
	if(sense){
		for(k=0;k<5000;k++);
		LPC_GPIO0->FIOSET=0xF<<4;
		for(k=0;k<5000;k++);
		keyboard();
		goto redirect;
	}
	else{
		LPC_GPIO0->FIOCLR=0xFF<<4;
	}
	for(k=0;k<10;k++);
}
}
