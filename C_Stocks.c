/*
Alonzo, John Leomarc M.
Version: 10:30 AM 4/15/21
 Make a C program that allows the user to perform the following options from a main menu:
1. Add a stockholder - adds the name of a person
2. Add a stock - adds the name of a stock, the price of the stock and how much of that stock is currently available
3. Record a stock purchase - record how much and which stock was purchased by a person
4. Change stock price - change price of a stock
5. Increase stock - adds to the amount of stock currently available for a specific stock
6. Display all stocks - displays all stock
7. Display all stockholders - displays all stockholders, along with all the stocks each stockholder owns, 
how much of each, and how much profit or loss that stockholder has made for that stock since the stockholder bought it, 
as well as the total profit or loss the stockholder has made for all of that person's stocks.

III. Add the ability to sell a stock to the problem above, and remember how much profit or loss the stockholder made on the sales and display 
this whenever you display info about the stockholder (in #7).
8. Record a stock sold - record how much and which stock was sold by a person.

To-do list:
1. Buying stock  still doesnt decrease quantity -ok
2. the number 8 thingy - ok
3. find more bugs if may time pa xd - not ok
*/
#include <stdio.h>
#include <string.h>

struct stocktype{
	char name[30];
	int price, quantity;
};
struct personalstocktype{
	char name[30];
	int profit, quantity;
};
struct holdertype{
	char name[30];
	struct personalstocktype stocks[100];
	int nMax,Sales;
};

int mainMenu(){
	int nChoice=0;
	while(nChoice<1||nChoice>9){
		printf("1. Add a stockholder\n");
		printf("2. Add a stock\n");
		printf("3. Record a stock purchase\n");
		printf("4. Change stock price\n");
		printf("5. Increase stock\n");
		printf("6. Display all stocks\n");
		printf("7. Display all stockholders\n");
		printf("8. Record a stock sold\n");
		printf("9. Exit\n");
		printf("Enter your choice: ");
		scanf(" %d", &nChoice);
	}
	return nChoice;
}
int holderAdd(struct holdertype Stockholders[], int nHolderMax){
	if(nHolderMax<100){
		printf("What is the stockholder's name?: ");
		scanf("%s", Stockholders[nHolderMax].name);
		nHolderMax++;
	}
	else {
		printf("\nSorry, your list of stockholders are already full, please delete some");
	}
	return nHolderMax;
}
int stockAdd(struct stocktype Stocks[], int nStockMax){
	if(nStockMax<100){
		printf("What is the stock's name?: ");
		scanf("%s",Stocks[nStockMax].name);
		printf("What is the price of the stock?: ");
		scanf("%d",&Stocks[nStockMax].price);
		printf("What is the quantity of the stock?: ");
		scanf("%d",&Stocks[nStockMax].quantity);
		nStockMax++;
	}
	else {
		printf("\nSorry, your list of stocks are already full, please delete some");
	}
	return nStockMax;
}
int stockPurchase(struct holdertype Stockholders[], struct stocktype Stocks[],int nHolderMax,int nStockMax){
	int x,y,nAmount,nTag,nBought=0;
	char cSearch[30],cSearch2[30];
	printf("Who purchased the stock?: ");
	scanf(" %s", cSearch);
	for(x=0;x<nHolderMax;x++){
		if(!strcmp(cSearch,Stockholders[x].name)){
			printf("Which stock is it?: ");
			scanf(" %s", cSearch2);
			for(y=0;y<nStockMax;y++){
				if(!strcmp(cSearch2,Stocks[y].name)){
					
					while(nBought==0){	
						printf("How many of this stock was purchased?: ");
						scanf("%d", &nAmount);
						if((Stocks[y].quantity-nAmount)>=0){
							Stocks[y].quantity=Stocks[y].quantity-nAmount;
							nBought=1;
						}
						else{
							nBought=0;
						}
					}
					
					
					if(Stockholders[x].nMax>0){
					}
					else{
						Stockholders[x].nMax=0;
					}
					nTag=Stockholders[x].nMax;
					
					strcpy(Stockholders[x].stocks[nTag].name, Stocks[y].name);
					Stockholders[x].stocks[nTag].profit= (nAmount*Stocks[y].price);
					Stockholders[x].stocks[nTag].quantity=nAmount;
					
					Stockholders[x].nMax++;
					
				}
			}
		}
	}
}
int stockPrice(struct stocktype Stocks[],int nStockMax){
	int x, nPrice,nFound=0;
	char cSearch[30];
	printf("What is the name of the stock you want to change the price of?: ");
	scanf(" %s", cSearch);
	
	for(x=0;x<nStockMax;x++){
		if(!strcmp(cSearch,Stocks[x].name)){
			printf("Enter its new price: ");
			scanf("%d", &nPrice);
			Stocks[x].price=nPrice;
			nFound=1;
		}
	}
	if(nFound==1){
		printf("Price succesfully changed!\n");
	}
	else{
		printf("Invalid stock name\n");
	}
}
int stockIncrease(struct stocktype Stocks[],int nStockMax){
	int x, nQuantity,nFound=0;
	char cSearch[30];
	printf("What is the name of the stock you want to increase the quantity of?: ");
	scanf(" %s", cSearch);
	
	for(x=0;x<nStockMax;x++){
		if(!strcmp(cSearch,Stocks[x].name)){
			printf("Enter how much you would like to add to its quantity: ");
			scanf("%d", &nQuantity);
			Stocks[x].quantity+=nQuantity;
			nFound=1;
		}
	}
	if(nFound==1){
		printf("Quantity succesfully increased!\n");
	}
	else{
		printf("Invalid stock name\n");
	}
}
int stockDisplay(struct stocktype Stocks[], int nStockMax){
	int x;
	printf("\n");
	printf("Stocks: \n");
	for(x=0;x<nStockMax;x++){
		printf("\nName: %s\nPrice: %d\nQuantity: %d\n\n",Stocks[x].name,Stocks[x].price,Stocks[x].quantity);
	}
}
int holderDisplay(struct holdertype Stockholders[],struct stocktype Stocks[], int nHolderMax, int nStockMax){
	int x,y,z,nTotal,nProfit;
	printf("\n");
	printf("Stockholders: \n");
	for(x=0;x<nHolderMax;x++){
		nTotal=0;
		printf("%s\n",Stockholders[x].name);
		printf("Here are the stocks they own: \n");
		for(y=0;y<Stockholders[x].nMax;y++){
			for(z=0;z<nStockMax;z++){
				if(!strcmp(Stockholders[x].stocks[y].name,Stocks[z].name)){
					nProfit=(Stocks[z].price*Stockholders[x].stocks[y].quantity)-(Stockholders[x].stocks[y].profit);
				}
			}
			printf("Name: %s\n",Stockholders[x].stocks[y].name);
			printf("Profit/Loss: %d\n",nProfit);
			printf("Quantity: %d\n",Stockholders[x].stocks[y].quantity);
			nTotal+=nProfit;
		}
		
		printf("Here is their total profit from stocks: %d\n",nTotal);
		printf("Here is their total sales: %d\n",Stockholders[x].Sales);
		printf("Here is their total profit overall: %d\n",(nTotal+Stockholders[x].Sales));
	}
	printf("\n");
}
int stockSold(struct holdertype Stockholders[], struct stocktype Stocks[],int nHolderMax,int nStockMax){
	int x,y,nAmount,nTag,nSold=0,nSuccess=0;
	char cSearch[30],cSearch2[30];
	printf("Who is the seller?: ");
	scanf(" %s", cSearch);
	for(x=0;x<nHolderMax;x++){
		if(!strcmp(cSearch,Stockholders[x].name)){
			printf("Which stock are they selling?: ");
			scanf(" %s", cSearch2);
			for(y=0;y<Stockholders[x].nMax;y++){
				if(!strcmp(cSearch2,Stockholders[x].stocks[y].name)){
					while(nSold==0){	
					printf("How many of this stock are they selling?: ");
					scanf("%d", &nAmount);
					if((Stockholders[x].stocks[y].quantity-nAmount)>=0){
						Stockholders[x].stocks[y].quantity=Stockholders[x].stocks[y].quantity-nAmount;
						nSold=1;
						}
					else{
						printf("Please input a number not greater than their stock quantity\n");
						nSold=0;
						}
					}
					if(Stockholders[x].Sales>0){
					}
					else{
						Stockholders[x].Sales=0;
					}
					Stocks[y].quantity=Stocks[y].quantity+nAmount;
					Stockholders[x].Sales=(Stocks[y].price*nAmount);
					nSuccess=1;
				}
			}
		}
	}
	if (nSuccess==0){
		printf("Invalid inputs\n");
	}
}
main () {
	struct stocktype Stocks[100];
	struct holdertype Stockholders[100];
	int nChoice=0, nHolderMax=0, nStockMax=0;
	
	while (nChoice!=9){
		nChoice=mainMenu();
		switch(nChoice) {
			case 1: nHolderMax=holderAdd(Stockholders, nHolderMax);
				break;
			case 2: nStockMax=stockAdd(Stocks,nStockMax);
				break;
			case 3: stockPurchase(Stockholders, Stocks, nHolderMax, nStockMax);
				break;
			case 4: stockPrice(Stocks,nStockMax);
				break;
			case 5: stockIncrease(Stocks,nStockMax);
				break;
			case 6: stockDisplay(Stocks, nStockMax);
				break;
			case 7: holderDisplay(Stockholders,Stocks, nHolderMax,nStockMax);
				break;
			case 8: stockSold(Stockholders, Stocks, nHolderMax, nStockMax);
				break;
		}
	}
}
