
#include <stdio.h>

int main(int argc, char **argv)
{
	int n1, n2, risultato = 0;
	
	printf("Inserisci un numero: ");
	scanf("%d", &n1);
	
	printf("\nInserisci un altro numero: ");
	scanf("%d", &n2);
	
	risultato = n1 + n2;
	
	printf("\nIl risultato è %d", risultato);
	return 0;
}

