#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define RED   "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW   "\x1B[33m"
#define WHITE "\x1B[0m"


struct essencial//Estrutura de Dados Base
{
    char name[99];
    int amount;
    float price;
    int validateMonth;
    int validateYear;
};

int searchContent(struct essencial *p){//Função para pesquisar produto

    FILE *arc;
    arc = fopen("products.txt", "r");

    char productName[99];
    int j, i = 0;
    int confirm;

    printf("Digite o nome do produto: ");
    scanf("%s", &productName);

    for(;;i++){
        confirm = fread(&(*p), sizeof(struct essencial), 1, arc);

        if(confirm == 0){
            break;
        }

        for(j = 0; p -> name[j] != '\0'; j++){
            if(productName[j] != p -> name[j]){
                break;
            }
        }

        if(productName[j] == '\0' && p -> name[j] == '\0'){
            printf("\nProduto: %s\n", p -> name);
            printf("Quantidade: %d\n", p -> amount);
            printf("Preco: R$%.2f\n", p -> price);
            if(p -> validateMonth < 9){
                printf("Validade: 0%d/%d\n\n", p -> validateMonth, p -> validateYear);
            }
            else{
                printf("Validade: %d/%d\n\n", p -> validateMonth, p -> validateYear);
            }
            fclose(arc);
            return i;
        }
    }
    fclose(arc);
    return -1;
}

int menu() //Menu de Funcionalidades.
{
    int choice;
    printf("1 - Entrada de dados dos produtos\n");
    printf("2 - Listar produtos\n");
    printf("3 - Listar produtos pelo preco\n");
    printf("4 - Pesquisar produto pelo nome\n");
    printf("5 - Pesquisar produto pela data de validade\n");
    printf("6 - Alterar produto pelo nome\n");
    printf("7 - Alterar quantidade em estoque do produto\n");
    printf("8 - Alterar preco do produto\n");
    printf("9 - Excluir produto pelo nome\n");
    printf("10 - Sair\n\n");
    printf("Digite a opcao referente a sua escolha: ");
    scanf("%d", &choice);

    return choice;
}
void dataSubmit(struct essencial *p)//Entrada de Dados
{

    system("cls");
    FILE *arc;
    arc = fopen("products.txt", "a");

    if(arc == NULL){
        printf(RED"Erro ao encontrar arquivo!!!"WHITE);
        menu();
    }
    else{

        printf(GREEN"*** <ENTRADA DE DADOS> *** \n\n"WHITE);

        printf("Digite o nome do produto: ");
        scanf("%s", &p -> name);

        printf("Digite a quantidade do produto: ");
        scanf("%d",&p -> amount);

        printf("Digite o preco do produto: ");
        scanf("%f",&p -> price);

        printf("Digite o mes de validade do produto: ");
        scanf("%d",&p -> validateMonth);

        printf("Digite o ano de validade do produto: ");
        scanf("%d", &p -> validateYear);

        fwrite(&(*p), sizeof(struct essencial), 1, arc);

        system("cls");
    }

    fclose(arc);
}

void showData(struct essencial *p){//Mostrar Conteudo Completo
    system("cls");
    FILE *arc;
    arc = fopen("products.txt", "r");

    if(arc == NULL){
        system("cls");
        printf(RED"Nenhum produto encontrado em estoque!!"WHITE);
        sleep(1500);
        menu();
    }
    else{

        int confirm;

        printf(GREEN"*** LISTA DE DADOS ***\n\n"WHITE);

        while(1){
            confirm = fread(&(*p), sizeof(struct essencial), 1, arc);
            if(confirm == 0 ){
                break;
            }
            printf("Produto: %s\n", p -> name);
            printf("Quantidade: %d\n", p -> amount);
            printf("Preco: R$%.2f\n", p -> price);
            if(p -> validateMonth < 9){
                printf("Validade: 0%d/%d\n\n", p -> validateMonth, p -> validateYear);
            }
            else{
                printf("Validade: %d/%d\n\n", p -> validateMonth, p -> validateYear);
            }
        }
    }
    fclose(arc);
}

void showByPrice(struct essencial *p){//Mostrar Conteudo pelo Preço
    system("cls");
    FILE *arc;
    arc = fopen("products.txt", "r");

    int confirm;
    float minRange = 0;
    float maxRange = 0;

    printf("Digite a faixa minima de preco: ");
    scanf("%f", &minRange);
    printf("Digite a faixa maxima de preco: ");
    scanf("%f", &maxRange);
    system("cls");

    printf(GREEN"*** LISTA DE PRODUTOS ***(Entre - %.2f e %.2f)\n\n"WHITE, minRange, maxRange);

    while(1){
        confirm = fread(&(*p), sizeof(struct essencial), 1, arc);

        if(confirm == 0){
            break;
        }

        if(p -> price > minRange && p -> price < maxRange){
            printf("Produto: %s\n", p -> name);
            printf("Quantidade: %d\n", p -> amount);
            printf("Preco: R$%.2f\n", p -> price);
            if(p -> validateMonth < 9){
                printf("Validade: 0%d/%d\n\n", p -> validateMonth, p -> validateYear);
            }
            else{
                printf("Validade: %d/%d\n\n", p -> validateMonth, p -> validateYear);
            }
        }
    }

    fclose(arc);
}

void showByName(struct essencial *p){//Mostrar Conteudo pelo Nome

    system("cls");
    FILE *arc;
    arc = fopen("products.txt", "r");
    int checkStock;

    printf(GREEN"*** PESQUISAR PRODUTO PELO NOME ***\n\n"WHITE);

    checkStock = searchContent(p);

    if(checkStock == -1){
        printf(RED"Produto nao encontrado em estoque !!\n\n"WHITE);
        menu();
    }

    fclose(arc);
}

void showByValidate(struct essencial *p){//Mostrar Conteudo pela Validade
    system("cls");
    FILE *arc;
    arc = fopen("products.txt", "r");

    int searchMonth;
    int searchYear;
    int confirm;

    printf(YELLOW"Digite a data de validade do produto!!!\n"WHITE);
    printf("MES: ");
    scanf("%d", &searchMonth);
    printf("ANO: ");
    scanf("%d", &searchYear);
    system("cls");

    printf(GREEN"*** LISTA DE PRODUTOS PELA VALIDADE ***\n\n"WHITE);

    while(1){
        confirm = fread(&(*p), sizeof(struct essencial), 1, arc);

        if(confirm == 0){
            break;
        }
        if(searchMonth == p -> validateMonth && searchYear == p -> validateYear){
            printf("Produto: %s\n", p -> name);
            printf("Quantidade: %d\n", p -> amount);
            printf("Preco: R$%.2f\n", p -> price);
            if(p -> validateMonth < 9){
                printf("Validade: 0%d/%d\n\n", p -> validateMonth, p -> validateYear);
            }
            else{
                printf("Validade: %d/%d\n\n", p -> validateMonth, p -> validateYear);
            }
        }
    }
    fclose(arc);
}

void changeProduct(struct essencial *p){//Alterar Produto
    system("cls");
    FILE *arc;
    arc = fopen("products.txt", "r+");
    int checkStock;
    int confirm;

    checkStock = searchContent(p);

    if(checkStock == -1){
        printf(RED"Produto nao encontrado em estoque !!\n\n"WHITE);
        menu();
    }

    for(;;) {
        fseek(arc, checkStock * sizeof(struct essencial), 0);

        confirm = fread(&(*p), sizeof(struct essencial), 1, arc);

        if(confirm == 1) {
            break;
        }
    }

    printf("Alterar nome: ");
    scanf("%s", &p -> name);

    printf("Alterar quantidade: ");
    scanf("%d", &p -> amount);

    printf("Alterar preco: ");
    scanf("%f", &p -> price);

    printf("Alterar mes: ");
    scanf("%d", &p -> validateMonth);

    printf("Alterar ano: ");
    scanf("%d", &p -> validateYear);

    fseek(arc , checkStock * sizeof(struct essencial), 0);
    fwrite(&(*p), sizeof(struct essencial), 1, arc);

    fclose(arc);

}

void changeAmount(struct essencial *p) { // Alterar quantidade do produto
  FILE *arc;
  arc = fopen("products.txt", "r+");

  int confirm;
  int supAmount;
  int checkStock;
  checkStock = searchContent(p);

  if(checkStock == -1){
    printf(RED"Nenhum produto encontrado em estoque\n\n"WHITE);
    menu();
  }

  for(;;) {
    fseek(arc, checkStock * sizeof(struct essencial), 0);
    confirm = fread(&(*p), sizeof(struct essencial), 1, arc);
    if(confirm == 1) {
      break;
    }
  }

  printf("Alterar quantidade do produto: ");
  scanf("%d", &supAmount);

  p -> amount = p -> amount + supAmount;

 fseek(arc , checkStock * sizeof(struct essencial), 0);
 fwrite(&(*p), sizeof(struct essencial), 1, arc);

  fclose(arc);

}

void changePrice(struct essencial *p){//Alterar Preço
    FILE *arc;
    arc = fopen("products.txt", "r+");

    int confirm;
    int supPrice;
    int checkStock;

    checkStock = searchContent(p);
    if(checkStock == -1){
        printf(RED"Nenhum produto encontrado em estoque\n\n"WHITE);
        menu();
    }

    for(;;) {
        fseek(arc, checkStock * sizeof(struct essencial), 0);
        confirm = fread(&(*p), sizeof(struct essencial), 1, arc);

        if(confirm == 1) {
            break;
        }
    }

    printf("Alterar preco: ");
    scanf("%f", &p->price);


    fseek(arc , checkStock * sizeof(struct essencial), 0);
    fwrite(&(*p), sizeof(struct essencial), 1, arc);
    fclose(arc);


}

void removeProduct(struct essencial *p){//Remover Produto
    FILE *arc;
    arc = fopen("products.txt", "r+");

    int checkStock;
    int confirm;
    int supAmount;
    int supPrice;

    checkStock = searchContent(p);
    system("cls");
    if(checkStock == -1){
        printf(RED"Nenhum produto encontrado em estoque\n\n"WHITE);
        menu();
    }

    fseek(arc,checkStock * sizeof(struct essencial), 0);
    confirm = fread(&(*p), sizeof(struct essencial), 1, arc);

    p -> name[0] = '*';
    supAmount = p -> amount;
    supPrice= p -> price;
    supAmount = NULL;
    supPrice = NULL;

    p -> amount = supAmount;
    p -> price = supPrice;
    p -> validateMonth = NULL;
    p -> validateYear = NULL;

    fseek(arc, checkStock * sizeof(struct essencial), 0);
    fwrite(&(*p), sizeof(struct essencial), 1, arc);
    fclose(arc);

}

void userExit(){//Saida Pelo Usuario
    system("cls");
    exit(0);
}

int main(void){//Função principal
    setlocale(LC_ALL, "portuguese");

    struct essencial essencial;
    struct essencial *p;
    p = &essencial;

    int choice;
    do{
        choice = menu();
        switch (choice){
            case 1:
                dataSubmit(p);
                break;
            case 2:
                showData(p);
                break;
            case 3:
                showByPrice(p);
                break;
            case 4:
                showByName(p);
                break;
            case 5:
                showByValidate(p);
                break;
            case 6:
                changeProduct(p);
                break;
            case 7:
                changeAmount(p);
                break;
            case 8:
                changePrice(p);
                break;
            case 9:
                removeProduct(p);
                break;
            case 10:
                userExit();
                break;
        }
    }while(choice > 0 && choice < 11);
}
