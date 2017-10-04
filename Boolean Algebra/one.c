#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>

char *truthTable(char * expr);

// A structure to represent a stack
struct Stack
{
    int top;
    int toptemp;//top of temp stack
    int topops;// top of ops stack
    unsigned capacity;
    char* final; //final array with numbers //changed int to char
    char* temp; //temp, with variables
    char* ops; //operators
};
 
// function to create a stack of given capacity. It initializes size of
// stack as 0
struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->topops = -1;
    stack->toptemp = -1;
    stack->final = (char*) malloc(stack->capacity * sizeof(char)); //changed int to char
    stack->temp = (char*) malloc(stack->capacity * sizeof(char));
    stack->ops = (char*) malloc(stack->capacity * sizeof(char));
    return stack;
}
 
// Stack is full when top is equal to the last index
int isFull(struct Stack* stack)
{   return stack->top == stack->capacity - 1; }
int isFullOps(struct Stack* stack)
{   return stack->topops == stack->capacity - 1; }
 
 int isFullTemp(struct Stack* stack)
{   return stack->toptemp == stack->capacity - 1; }


// Stack is empty when top is equal to -1
int isEmpty(struct Stack* stack)
{   return stack->top == -1;  }

int isEmptyTemp(struct Stack* stack)
{   return stack->toptemp == -1;  }

int isEmptyOps(struct Stack* stack)
{   return stack->topops == -1;  }
 
 //--------------PUSH----------------------------------------------------------
// Function to add an item to stack.  It increases top by 1
void push(struct Stack* stack, int item)
{
    if (isFull(stack))
        return;
    stack->final[++stack->top] = item;
   // printf("%d pushed to stack\n", item);
   // printf("Pushed value of Normal push:%dNONE",stack->final[0]);
}
 void pusho(struct Stack* stack, char item)
{
    if (isFullOps(stack))
        return;
    stack->ops[++stack->topops] = item;
   // printf("%c pushed to ops stack\n", item);
   // printf("Pushed value:%cNONE",stack->ops[0]);
}
void pusht(struct Stack* stack, char item)
{
    if (isFullTemp(stack))
        return;
    stack->temp[++stack->toptemp] = item;
  //  printf("%c pushed to temp stack\n", item);
   // printf("Pushed value of temp stack:%c",stack->temp[0]);
}
//-------------END PUSH----------------------------------------------------------
//-------------POP-----------------------------------------------------------------
char pop(struct Stack* stack)
{
    if (isEmpty(stack))
        return -1;
    return stack->final[stack->top--];
}

char popo(struct Stack* stack)
{
	//printf("About to pop OPS\n");
    if (isEmptyOps(stack))
        return -1;
  //  printf("About to return\n");
    return stack->ops[stack->topops--];
   // printf("After poping Ops stack, top is at: %d",stack->topops);
}

char popt(struct Stack* stack)
{
    if (isEmptyTemp(stack))
        return -1;
    return stack->temp[stack->toptemp--];
}
//-------------END POP---------------------------------------------------------------

//--------------PEAK------------------------------------------------------------------
char peak(struct Stack* stack)
{
    if (isEmpty(stack))
        return -1;
    return stack->final[stack->top];
}

char peako(struct Stack* stack)
{
    if (isEmptyOps(stack))
        return 'N';
    return stack->ops[stack->topops];
}

char peakt(struct Stack* stack)
{
    if (isEmptyTemp(stack))
        return 'N';
    return stack->temp[stack->toptemp];
}

//---------------END PEAK--------------------------------------------------------------

void printTemp(struct Stack* stack)
{
	int i = 0;
	while(stack->temp[i] != '\0'){
		printf("%c",stack->temp[i]);
		i++;
	}
	printf("\n");
}


int main(){
	setbuf(stdout, NULL);//allows buffer to no hold back from printing "enter:"
	printf("Enter: ");
	char expr[256];
	 read(0, expr,256);
	 char *result = truthTable(expr);
	 printf("Output String:%s\n", result);
	// printf("result is: %s\n", result);
	return 0;
}

char *truthTable(char *expr){
	//printf("First char is: %s\n", expr);
	struct Stack* stack = createStack(256); //makes a stack
	int i = 0;
	while(expr[i] != '\0'){
		if(expr[i] == 'A' || expr[i] == 'B' || expr[i] == 'C' ||expr[i] =='D'){
			pusht(stack, expr[i]);
		}
		else if(expr[i] == '&'){// Taking care of order of operations

			//If the next char is a letter place the char before the not so RPN executes correctly
			if(expr[i+1] == 'A' || expr[i+1] == 'B' || expr[i+1] =='C' || expr[i+1] == 'D'){
				pusht(stack, expr[i+1]);//push letter
				pusht(stack, expr[i]); //push not
				i++;// increment an additional time since we took care of 2 chars
			}
			//if the next char is a NOT, and the one after is not an open parenthesis:
			// put 
			else if(expr[i+1] == '~' && expr[i+2] != '('){
				pusho(stack,expr[i+1]); //puts not on Operator stack
				pusht(stack, expr[i+2]); //puts variable being notted on temp stack
				pusht(stack,popo(stack)); //puts not in temp stack
				pusht(stack, expr[i]); // puts & on stack
				i = i+2; //we took care of the next 2 chars
			}
			else{ //if no case fits, put on operator stack
				pusho(stack,expr[i]);
			}
		}
		else if(expr[i] == '('){ //always push ( on operation stack
			pusho(stack,expr[i]);
		}
		else if(expr[i] == '+' || expr[i] == '~' ){ //taking care of other operators
			char temp = peako(stack); //view the top of the operator stack to check for a negative
			//We don't want double plus on ops stack, it should go on temp stack
			if(temp == expr[i] && expr[i] != '~'){ //take care of double ~ later
				pusht(stack,popo(stack));
			}
			//if sign is already at top of operations stack, we have a double negative
			else if(temp == expr[i] && expr[i] == '~'){ //double not, remove the not
			//this removes the existing not without putting the "new" not on the stack
				popo(stack);
			}
				else{
					pusho(stack,expr[i]);
				}

		}
		//When we have a closing parenthesis, pop everything on ops stack 
		//and place the poped operator on the temp stack
		//until we meet the matching open parenthesis (we are working backwards)
		else if (expr[i] == ')'){
			while(peako(stack) != '('){
				pusht(stack,popo(stack));
			}
			popo(stack); //pop ( from operating stack
		}
		i++; //go to next char of user input

	} //end while loop through user input string
//---------END OF FORMATING STRING FOR RPN--------------------------------------

	//put remaining operators on t stack
	while(!isEmptyOps(stack)){
		pusht(stack,popo(stack));
	}
	printf("\n\nOriginal String is: %s\n", expr);
	printf("Final result is: ");
	printTemp(stack);
	printf("Stack at top: %c\n",stack->temp[stack->toptemp]);
//-------- Generating the Truth Table begins -----------
	//when looking at a truth table in order: D C B A
	//where A is the least significant bit in terms of counting,
	//variables b and c  alternate from 1 to 0 every 2 and 4 numbers
	// d only changes from 0 to 1 at 8
	//a alternates every time
	int bCounter=2; int cCounter=4; //keeping track of a and b 
	char a='1';char b='0'; char c='0'; char d='0';
	printf("Binary form: D C B A       Result\n");
	printf("----------------------------------\n");
	for(int x = 0;x<16;x++){ //itterate through 16 numbers generated by 4 bits
		//no matter what, alternate a
		if(a=='0'){ 
			a='1';
		}else if(a == '1'){ 
			a='0';
		}
		//only change d from 0 to 1 when at 9th itteration of loop
		if(x==8){
			d = '1';
		}
		//alternate b every 2 itterations
		if(x == bCounter){
			if(b == '0'){
				b='1';
			}else{
				b='0';
			}
			bCounter = bCounter+2;
		}
		//alternate c every 4 itteratoins
		if(x == cCounter){
			if(c == '0'){
				c='1';
			}else{
				c='0';
			}
			cCounter = cCounter+4;
		}
		printf("Binary form: %c %c %c %c       ",d,c,b,a);
//--------Done Generating Truth Table------------------------
//--------Now place values of a, b, c, and d on the final stack----------
		int t = 0; //iterator
		char topFinal;
		while(stack->temp[t] != '\0'){ //itterator through temp stack we made
			//printf("TEMP:%c\n",stack->temp[t]);
			if(stack->temp[t] == 'A'){
				push(stack,a);
			}else if(stack->temp[t] == 'B'){
				push(stack,b);
			}else if(stack->temp[t] == 'C'){
				push(stack,c);
			}else if(stack->temp[t] =='D'){
				push(stack,d);
			}
			//Invert right off the bat
			else if(stack->temp[t] == '~'){
				topFinal = pop(stack);
				if(topFinal == '1'){
					push(stack, '0');
				}else{
					push(stack, '1');
				}
			}
			//And Case
			else if(stack->temp[t]=='&'){
				char z = pop(stack);
				char y = pop(stack);
				//AND only results in 1 if z and y are 1
				if(z == '1' && y == '1') 
					push(stack, '1');
				else
					push(stack,'0');
			}
			//OR Case
			else if(stack->temp[t] == '+'){
				char m = pop(stack);
				char r = pop(stack);
				//AND only results in 1 if z and y are 1
				if(r == '0' && m == '0') 
					push(stack, '0');
				else
					push(stack,'1');
			}
			t++;
		} //end while loop
		printf("       %c\n", peak(stack));
	} //end for loop (4 bit counter)
	return stack->final;
}