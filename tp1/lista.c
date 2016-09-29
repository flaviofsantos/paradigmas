/*  A entrada do seu programa é a lista de TODOS os nomes das clientes, enviada pela empresa. 
 *  A saída é a lista em HTML, em ordem alfabética, só com os nomes que iniciam com "R". */

/* Este programa utiliza 3 argumentos:
 * 1. Nome do arquivo que contem a lista de clientes
 * 2. Nome do arquivo html a ser criado com a lista de ganhadores
 * 3. Letra que servira de filtro para escolher os ganhadores */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLEN 200      // tamanho maximo da linha
#define MAXLINES 1000   // quantidade maxima de linhas

/* função de comparação para o qsort */
int cmp(const void* a, const void* b);

int main(int argc, char **argv)
{   
   FILE *fp;   
   char lines[MAXLINES][MAXLEN];
   int qlines;       // quantidade de linhas armazenadas
   int filtro;       // padrão de filtragem dos nomes
   int i;   // contador
   
   
   /* verifica quantidade de argumentos */
   if (argc != 4) {
      printf("Modo de uso: %s arquivo_de_entrada arquivo_de_saida caracter_de_filtro\n", argv[0]);  
      exit(EXIT_FAILURE);
   }
   
   /* verifica se nome do arquivo de entrada é igual ao arquivo de saida */
   if(strcmp(argv[1], argv[2]) == 0) {
      printf("Nomes do arquivo de entrada e de saída devem ser diferentes\n");
      exit(EXIT_FAILURE);
   }
   
   /* armazena filtro */
   filtro = toupper(*argv[3]);
   
   /* abre arquivo de entrada para leitura */
   if ((fp = fopen(argv[1], "r")) == NULL) {
      printf("Erro ao ler %s\n", argv[1]);
      exit(EXIT_FAILURE);
   }
   
   /* armazena nomes que começam com o filtro no array lines */   
   i = 0;
   while (fgets(lines[i], MAXLEN, fp) != NULL) {
      *lines[i] = toupper(*lines[i]); // Colocar inicial em maiúscula
      if (*lines[i] == filtro) i++;
   }
   qlines = i;
               
   /* realiza o sort do array */
   qsort(lines, qlines, MAXLEN, cmp);      
   
   /* abre arquivo de saida para escrita */
   if ((fp = fopen(argv[2], "w")) == NULL) {
      printf("Erro ao criar %s\n", argv[1]);
      exit(EXIT_FAILURE);
   }
   
   /* grava primeira parte do html */
   fprintf(fp,"<html> <head> <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /> </head>\n"
      "<body> <header1> Lista de ganhadores da promoção BOMBOM Demais! </header1> <ul>\n");
   
   /* grava lista de ganhadores */
   for (i = 0; i < qlines; i++)
      fprintf(fp,"<li>%s</li>", lines[i]);
   
   /* grava final do html */
   fprintf(fp,"</ul> </body> </html>\n");
   
   return 0;
}

int cmp(const void *a, const void *b)
{     
   return strcmp((const char*)a,(const char*)b);
}
