#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/*
la biblioteca ctype.h incluye una función que permite determinar si un caracter
es un dígito o no.
Una cadena para la cuál todos sus caracteres son dígitos es Número.
 */
int esNumero(const char *nro) {    
	int i=0;
	while (nro[i])
	{
		if (isdigit(nro[i]) == 0)
		{
			return 0;
		};
		i++;
	};
	return 1;
}
int main(int argc, char **argv) {
	char prueba[6] = "12345h";
	esNumero(prueba);
	if (argc != 3) {
		puts("uso: suma Nro1 Nro2");
		exit(0);
	}
	if (!esNumero(argv[1]) || !esNumero(argv[2])) {
		puts("nro1 y nro2 deben ser constantes numéricas");
		exit(-1);
	} 
	int sum1 = atoi(argv[1]);
	int sum2 = atoi(argv[2]);
	printf("la suma de %d y %d es %d", sum1, sum2, sum1+sum2);
	return 0;
}