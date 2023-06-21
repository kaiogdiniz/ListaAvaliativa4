#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_FABRICANTES 5
#define MAX_PRODUTOS 50
#define MAX_UF 27
#define PESO_MINIMO 0.05 
#define PESO_MAXIMO 50.0 
#define VALOR_COMPRA_MINIMO 0.50
#define VALOR_COMPRA_MAXIMO 8000.0
#define VALOR_VENDA_MINIMO 1.00
#define VALOR_VENDA_MAXIMO 10000.0

typedef struct {
    char marca[50];
    char site[100];
    char telefone[20];
    char uf[3];
} Fabricante;

typedef struct {
    char descricao[100];
    float peso;
    float valorCompra;
    float valorVenda;
    float valorLucro;
    float percentualLucro;
    Fabricante fabricante;
} Produto;

Fabricante cadastrarFabricante();
Produto cadastrarProduto(Fabricante fabricantes[], int numFabricantes);
void listarMarcas(Fabricante fabricantes[], int numFabricantes);
void listarProdutos(Produto produtos[], int numProdutos);
void listarProdutosEstado(Produto produtos[], int numProdutos);
void listarProdutosMarca(Produto produtos[], int numProdutos, Fabricante fabricantes[], int numFabricantes);
void listarEstadoProdutoMaisCaro(Produto produtos[], int numProdutos, Fabricante fabricantes[], int numFabricantes);
void listarEstadoProdutoMaisBarato(Produto produtos[], int numProdutos, Fabricante fabricantes[], int numFabricantes);
void ordenarPorValor(Produto produtos[], int numProdutos);
void ordenarPorLucro(Produto produtos[], int numProdutos);
void ordenarPorPercentualLucro(Produto produtos[], int numProdutos);
void ordenarProdutosCrescente(Produto produtos[], int numProdutos);
void ordenarMarcasDecrescente(Fabricante fabricantes[], int numFabricantes);

int main() {
    setlocale(LC_ALL, "");
    Fabricante* fabricantes = calloc(MAX_FABRICANTES, sizeof(Fabricante));
    Produto* produtos = calloc(MAX_PRODUTOS, sizeof(Produto));
    int numFabricantes = 0;
    int numProdutos = 0;
    int opcao;

    do {
        printf("===================================================================================\n");
        printf("                       MENU PRINCIPAL\n");
        printf("===================================================================================\n");
        printf("[1] Cadastrar fabricante\n");
        printf("[2] Cadastrar produto\n");
        printf("[3] Listar todas as marcas\n");
        printf("[4] Listar todos os produtos\n");
        printf("[5] Listar os produtos de um determinado estado\n");
        printf("[6] Listar os produtos de uma determinada marca\n");
        printf("[7] Apresentar o(s) estado(s) onde está registrado o produto mais caro\n");
        printf("[8] Apresentar o(s) estado(s) onde está registrado o produto mais barato\n");
        printf("[9] Listar todos os produtos em ordem crescente de valor\n");
        printf("[10] Listar todos os produtos em ordem crescente de maior 'valor do lucro'\n");
        printf("[11] Listar todos os produtos em ordem crescente de maior 'percentual de lucro'\n");
        printf("[12] Listar todos os produtos em ordem alfabética crescente\n");
        printf("[13] Listar todas as marcas em ordem alfabética decrescente\n");
        printf("[0] Sair do programa\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (numFabricantes < MAX_FABRICANTES) {
                    fabricantes[numFabricantes] = cadastrarFabricante();
                    numFabricantes++;
                    printf("Fabricante cadastrado com sucesso!\n");
                } else {
                    printf("Limite máximo de fabricantes atingido!\n");
                }
                break;
            case 2:
                if (numProdutos < MAX_PRODUTOS) {
                    produtos[numProdutos] = cadastrarProduto(fabricantes, numFabricantes);
                    numProdutos++;
                    printf("Produto cadastrado com sucesso!\n");
                } else {
                    printf("Limite máximo de produtos atingido!\n");
                }
                break;
            case 3:
                listarMarcas(fabricantes, numFabricantes);
                break;
            case 4:
                listarProdutos(produtos, numProdutos);
                break;
            case 5:
                listarProdutosEstado(produtos, numProdutos);
                break;
            case 6:
                listarProdutosMarca(produtos, numProdutos, fabricantes, numFabricantes);
                break;
            case 7:
                listarEstadoProdutoMaisCaro(produtos, numProdutos, fabricantes, numFabricantes);
                break;
            case 8:
                listarEstadoProdutoMaisBarato(produtos, numProdutos, fabricantes, numFabricantes);
                break;
            case 9:
                ordenarPorValor(produtos, numProdutos);
                listarProdutos(produtos, numProdutos);
                break;
            case 10:
                ordenarPorLucro(produtos, numProdutos);
                listarProdutos(produtos, numProdutos);
                break;
            case 11:
                ordenarPorPercentualLucro(produtos, numProdutos);
                listarProdutos(produtos, numProdutos);
                break;
            case 12:
                ordenarProdutosCrescente(produtos, numProdutos);
                listarProdutos(produtos, numProdutos);
                break;
            case 13:
   				ordenarMarcasDecrescente(fabricantes, numFabricantes);
   				listarMarcas(fabricantes, numFabricantes);
   				break;
    
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

        printf("==============================================================================\n");
        printf("\n");
    } while (opcao != 0);

    free(fabricantes);
    free(produtos);

    return 0;
}

Fabricante cadastrarFabricante() {
    Fabricante fabricante;

    printf("===================================================================================\n");
    printf("                     CADASTRO DE FABRICANTE\n");
    printf("===================================================================================\n");
    printf("Marca: ");
    getchar();
    fgets(fabricante.marca, sizeof(fabricante.marca), stdin);
    fabricante.marca[strcspn(fabricante.marca, "\n")] = '\0';
    printf("Site: ");
    fgets(fabricante.site, sizeof(fabricante.site), stdin);
    fabricante.site[strcspn(fabricante.site, "\n")] = '\0';
    printf("Telefone: ");
    fgets(fabricante.telefone, sizeof(fabricante.telefone), stdin);
    fabricante.telefone[strcspn(fabricante.telefone, "\n")] = '\0';
    printf("UF: ");
    fgets(fabricante.uf, sizeof(fabricante.uf), stdin);
    fabricante.uf[strcspn(fabricante.uf, "\n")] = '\0';

    return fabricante;
}

Produto cadastrarProduto(Fabricante fabricantes[], int numFabricantes) {
    Produto produto;

    printf("===============================================================================\n");
    printf("                       CADASTRO DE PRODUTO\n");
    printf("===============================================================================\n");
    printf("Descrição: ");
    getchar();
    fgets(produto.descricao, sizeof(produto.descricao), stdin);
    produto.descricao[strcspn(produto.descricao, "\n")] = '\0';

    
    do {
        printf("Peso (em kg, entre %.2f e %.2f): ", PESO_MINIMO, PESO_MAXIMO);
        scanf("%f", &produto.peso);
    } while (produto.peso < PESO_MINIMO || produto.peso > PESO_MAXIMO);

    
    do {
        printf("Valor de compra (entre R$ %.2f e R$ %.2f): ", VALOR_COMPRA_MINIMO, VALOR_COMPRA_MAXIMO);
        scanf("%f", &produto.valorCompra);
    } while (produto.valorCompra < VALOR_COMPRA_MINIMO || produto.valorCompra > VALOR_COMPRA_MAXIMO);

    
    do {
        printf("Valor de venda (entre R$ %.2f e R$ %.2f): ", VALOR_VENDA_MINIMO, VALOR_VENDA_MAXIMO);
        scanf("%f", &produto.valorVenda);
    } while (produto.valorVenda < VALOR_VENDA_MINIMO || produto.valorVenda > VALOR_VENDA_MAXIMO);

    float valorLucro = produto.valorVenda - produto.valorCompra;
    produto.valorLucro = valorLucro;
    produto.percentualLucro = (valorLucro / produto.valorCompra) * 100;

    int fabricanteIndex;
    do {
        printf("Índice do fabricante (0 a %d): ", numFabricantes - 1);
        scanf("%d", &fabricanteIndex);
    } while (fabricanteIndex < 0 || fabricanteIndex >= numFabricantes);

    produto.fabricante = fabricantes[fabricanteIndex];

    return produto;
}

void listarMarcas(Fabricante fabricantes[], int numFabricantes) {
    printf("==============================================================================\n");
    printf("                          LISTA DE MARCAS\n");
    printf("==============================================================================\n");
    for (int i = 0; i < numFabricantes; i++) {
        printf("Fabricante #%d\n", i + 1);
        printf("Marca: %s\n", fabricantes[i].marca);
        printf("Site: %s\n", fabricantes[i].site);
        printf("Telefone: %s\n", fabricantes[i].telefone);
        printf("UF: %s\n", fabricantes[i].uf);
        printf("\n");
    }
}

void listarProdutos(Produto produtos[], int numProdutos) {
    printf("==============================================================================\n");
    printf("                       LISTA DE PRODUTOS\n");
    printf("==============================================================================\n");
    for (int i = 0; i < numProdutos; i++) {
        printf("Produto #%d\n", i + 1);
        printf("Descrição: %s\n", produtos[i].descricao);
        printf("Peso: %.2f\n", produtos[i].peso);
        printf("Valor de compra: R$ %.2f\n", produtos[i].valorCompra);
        printf("Valor de venda: R$ %.2f\n", produtos[i].valorVenda);
        printf("Valor do lucro: R$ %.2f\n", produtos[i].valorLucro);
        printf("Percentual de lucro: %.2f%%\n", produtos[i].percentualLucro);
        printf("Fabricante: %s\n", produtos[i].fabricante.marca);
        printf("\n");
    }
}

void listarProdutosEstado(Produto produtos[], int numProdutos) {
    char estado[3];

    printf("==============================================================================\n");
    printf("               LISTA DE PRODUTOS DE UM DETERMINADO ESTADO\n");
    printf("==============================================================================\n");
    printf("Digite a UF do estado: ");
    scanf("%s", estado);

    printf("Produtos do estado %s:\n", estado);
    int encontrado = 0;
    for (int i = 0; i < numProdutos; i++) {
        if (strcmp(produtos[i].fabricante.uf, estado) == 0) {
            printf("Produto #%d\n", i + 1);
            printf("Descrição: %s\n", produtos[i].descricao);
            printf("Peso: %.2f\n", produtos[i].peso);
            printf("Valor de compra: R$ %.2f\n", produtos[i].valorCompra);
            printf("Valor de venda: R$ %.2f\n", produtos[i].valorVenda);
            printf("Valor do lucro: R$ %.2f\n", produtos[i].valorLucro);
            printf("Percentual de lucro: %.2f%%\n", produtos[i].percentualLucro);
            printf("Fabricante: %s\n", produtos[i].fabricante.marca);
            printf("\n");
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("Nenhum produto encontrado para o estado %s\n", estado);
    }
}

void ordenarMarcasDecrescente(Fabricante fabricantes[], int numFabricantes) {
    int i, j;
    Fabricante temp;

    for (i = 0; i < numFabricantes - 1; i++) {
        for (j = i + 1; j < numFabricantes; j++) {
            if (strcmp(fabricantes[i].marca, fabricantes[j].marca) < 0) {
                temp = fabricantes[i];
                fabricantes[i] = fabricantes[j];
                fabricantes[j] = temp;
            }
        }
    }
}


void ordenarProdutosCrescente(Produto produtos[], int numProdutos) {
    int i, j;
    Produto temp;

    for (i = 0; i < numProdutos - 1; i++) {
        for (j = i + 1; j < numProdutos; j++) {
            if (strcmp(produtos[i].descricao, produtos[j].descricao) > 0) {
                temp = produtos[i];
                produtos[i] = produtos[j];
                produtos[j] = temp;
            }
        }
    }
}

void listarProdutosMarca(Produto produtos[], int numProdutos, Fabricante fabricantes[], int numFabricantes) {
    char marca[50];

    printf("============================================================================\n");
    printf("               LISTA DE PRODUTOS DE UMA DETERMINADA MARCA\n");
    printf("============================================================================\n");
    printf("Digite a marca do produto: ");
    getchar();
    fgets(marca, sizeof(marca), stdin);
    marca[strcspn(marca, "\n")] = '\0';

    printf("Produtos da marca %s:\n", marca);
    int encontrado = 0;
    for (int i = 0; i < numProdutos; i++) {
        if (strcmp(produtos[i].fabricante.marca, marca) == 0) {
            printf("Produto #%d\n", i + 1);
            printf("Descrição: %s\n", produtos[i].descricao);
            printf("Peso: %.2f\n", produtos[i].peso);
            printf("Valor de compra: R$ %.2f\n", produtos[i].valorCompra);
            printf("Valor de venda: R$ %.2f\n", produtos[i].valorVenda);
            printf("Valor do lucro: R$ %.2f\n", produtos[i].valorLucro);
            printf("Percentual de lucro: %.2f%%\n", produtos[i].percentualLucro);
            printf("Fabricante: %s\n", produtos[i].fabricante.marca);
            printf("\n");
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("Nenhum produto encontrado para a marca %s\n", marca);
    }
}

void listarEstadoProdutoMaisCaro(Produto produtos[], int numProdutos, Fabricante fabricantes[], int numFabricantes) {
    float maxValor = 0;
    int encontrado = 0;

    printf("===================================================================================\n");
    printf("         ESTADO(S) ONDE ESTÁ REGISTRADO O PRODUTO MAIS CARO\n");
    printf("===================================================================================\n");

    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].valorVenda > maxValor) {
            maxValor = produtos[i].valorVenda;
        }
    }

    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].valorVenda == maxValor) {
            printf("Produto #%d\n", i + 1);
            printf("Descrição: %s\n", produtos[i].descricao);
            printf("Peso: %.2f\n", produtos[i].peso);
            printf("Valor de compra: R$ %.2f\n", produtos[i].valorCompra);
            printf("Valor de venda: R$ %.2f\n", produtos[i].valorVenda);
            printf("Valor do lucro: R$ %.2f\n", produtos[i].valorLucro);
            printf("Percentual de lucro: %.2f%%\n", produtos[i].percentualLucro);
            printf("Fabricante: %s\n", produtos[i].fabricante.marca);
            printf("\n");
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Nenhum produto encontrado!\n");
    }
}

void listarEstadoProdutoMaisBarato(Produto produtos[], int numProdutos, Fabricante fabricantes[], int numFabricantes) {
    float minValor = produtos[0].valorVenda;
    int encontrado = 0;

    printf("===================================================================================\n");
    printf("         ESTADO(S) ONDE ESTÁ REGISTRADO O PRODUTO MAIS BARATO\n");
    printf("===================================================================================\n");

    for (int i = 1; i < numProdutos; i++) {
        if (produtos[i].valorVenda < minValor) {
            minValor = produtos[i].valorVenda;
        }
    }

    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].valorVenda == minValor) {
            printf("Produto #%d\n", i + 1);
            printf("Descrição: %s\n", produtos[i].descricao);
            printf("Peso: %.2f\n", produtos[i].peso);
            printf("Valor de compra: R$ %.2f\n", produtos[i].valorCompra);
            printf("Valor de venda: R$ %.2f\n", produtos[i].valorVenda);
            printf("Valor do lucro: R$ %.2f\n", produtos[i].valorLucro);
            printf("Percentual de lucro: %.2f%%\n", produtos[i].percentualLucro);
            printf("Fabricante: %s\n", produtos[i].fabricante.marca);
            printf("\n");
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Nenhum produto encontrado!\n");
    }
}

void ordenarPorValor(Produto produtos[], int numProdutos) {
    for (int i = 0; i < numProdutos - 1; i++) {
        for (int j = 0; j < numProdutos - i - 1; j++) {
            if (produtos[j].valorVenda > produtos[j + 1].valorVenda) {
                Produto temp = produtos[j];
                produtos[j] = produtos[j + 1];
                produtos[j + 1] = temp;
            }
        }
    }
}

void ordenarPorLucro(Produto produtos[], int numProdutos) {
    for (int i = 0; i < numProdutos - 1; i++) {
        for (int j = 0; j < numProdutos - i - 1; j++) {
            if (produtos[j].valorLucro > produtos[j + 1].valorLucro) {
                Produto temp = produtos[j];
                produtos[j] = produtos[j + 1];
                produtos[j + 1] = temp;
            }
        }
    }
}

void ordenarPorPercentualLucro(Produto produtos[], int numProdutos) {
    for (int i = 0; i < numProdutos - 1; i++) {
        for (int j = 0; j < numProdutos - i - 1; j++) {
            if (produtos[j].percentualLucro > produtos[j + 1].percentualLucro) {
                Produto temp = produtos[j];
                produtos[j] = produtos[j + 1];
                produtos[j + 1] = temp;
            }
        }
    }
}
