#include <stdio.h>

unsigned long int exponenciacao_modular_rapida(unsigned long int denominador, unsigned long int potencia, unsigned long int mod)
{
    unsigned long int n = denominador, k = potencia, d = mod;
    unsigned long int resultado, pot;
 
 
    pot = n % d;
    resultado = 1;
 
    for ( ; k > 0; k /= 2) 
    {
        if (k % 2 == 1) 
        {
            resultado = (resultado * pot) % d;
        }
    
        pot = (pot * pot) % d;
     }
      return resultado;
}

unsigned long int mdc(unsigned long int n1, unsigned long int n2)
{
    unsigned long int resto;

    resto = n1 % n2;

    if (n2 == 0)
    {
        return n1;
    }

    else if (resto == 0)
    {
        return n2;
    }

    n1 = n2;

    n2 = resto;

    return mdc(n1, n2);
}

void inverso_modular(unsigned long int a, unsigned long int m, unsigned long int *resultado)
{
    if (mdc(a, m) != 1)
    {
        *resultado = 0;

        return;
    }

    unsigned long int m0 = m;

    long int y = 0, x = 1;

    while (a > 1)
    {
        long int q = a / m;     
        long int t = m; 

        m = a % m;
        a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0)
    {
        x += m0;
    }

    *resultado = x;
}

void desencriptaMensagem(){
    printf("descript\n");
    char cript_name[125];
    FILE *cript = NULL;
    unsigned long int p, q, phi, e, d, n, c, m;
    printf("Digite o valor de p:\n");
    scanf("%lu", &p);
    printf("Digite o valor de q:\n");
    scanf("%lu", &q);
    phi = (p - 1) * (q - 1);
    n = p * q;
    printf("Digite o valor de e:\n");
    scanf("%lu", &e);
    inverso_modular(e, phi, &d);
    if(d == 0){
      printf("e não é coprimo de (p - 1) * (q - 1)\n");
      return ;
    }
    while(cript == NULL){
        printf("Digite o nome do arquivo onde se encontra a mensagem:\n");
        scanf("%s", cript_name);
        cript = fopen(cript_name, "r");
        if(cript == NULL)
            printf("Arquivo não encontrado ou não existe, favor: \n");
    }
    while(fscanf(cript, "%lu", &c) != EOF){
        m = exponenciacao_modular_rapida(c, d, n);
        if(m == 28){
            printf(" ");
        }else if(m > 1 && m < 28){
            printf("%c", (char) ('A' + m - 2));
        }else{
            printf("@");
        }
    }
    printf("\n");
    fclose(cript);
}

void entrada_frase()
{
    unsigned long int p = 0, q = 0, e = 0;
    FILE *keys = fopen("chaves.txt", "r+");
    
    if(keys == NULL)
    {
        printf("Ainda nao existem chaves publicas!\n");
        return;
    }
    else 
    {
        fscanf(keys, "p = %lu q = %lu e = %lu", &p, &q, &e);
        fclose(keys);
        unsigned long int n = p * q;
        char frase[10000];
        printf("Digite sua frase:\n");
        scanf("\n%[^\n]", frase);
        int tamanho_frase;
 		FILE *crip = fopen("grifado.txt", "w");
        for (tamanho_frase = 0; frase[tamanho_frase] != '\0'; tamanho_frase++) 
        {
            unsigned long int m = 0;
            if(frase[tamanho_frase] == ' '){
              m = 28;
            }else if(frase[tamanho_frase] >= 'a' && frase[tamanho_frase] <= 'z'){
              m = (unsigned long int) (frase[tamanho_frase] - 'a') + 2;
            }else if(frase[tamanho_frase] >= 'A' && frase[tamanho_frase] <= 'Z'){
              m = (unsigned long int) (frase[tamanho_frase] - 'A') + 2;
            }
            fprintf(crip, "%lu\n", exponenciacao_modular_rapida(m, e, n));
        }
        printf("Texto criptografado com sucesso!\n"); 
        fclose(crip);
    }
}

void entrada_chave(){
	unsigned long int p, q, e, d, phi;
	printf("Digite o valor de p:\n");
	scanf("%lu", &p);
	printf("Digite o valor de q:\n");
	scanf("%lu", &q);
	phi = (p - 1) * (q - 1);
	printf("Digite o valor de e:\n");
	scanf("%lu", &e);
	inverso_modular(e, phi, &d);
	while(d == 0){
		printf("e não é coprimo de (p - 1) * (q - 1)\nDigite o valor de e:\n");
		scanf("%lu", &e);
		inverso_modular(e, phi, &d);
	}
	FILE *keys = fopen("chaves.txt", "w");
	fprintf(keys, "p = %lu q = %lu e = %lu", p, q, e);
	fclose(keys);
}

int main(){
	entrada_chave();
	entrada_frase();
	desencriptaMensagem();
	return 0;
}
