#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Estrutura que representa um usuário
typedef struct {
    char* nome;
    int idade;
    char* cpf;
} User;

// Declarações de funções
User ** criaUsuarios(int numUsuarios);
User * criaUsuario(char* buffNome, int idade, char* buffCpf);

void liberaUsuario(User** users, int numUsuarios);
void imprimeUsuario(User* user);

void leUsuario(char* buffNome, int* idade, char* buffCpf);
User * procuraUsuario(char* buffNome, User** users, int numUsuarios);

int main() {
    char buffNome[100];
    int numUsuarios, idade;
    char buffCpf[20];
    User** users = NULL;
    User* userAchado = NULL;

    // Lê quantidade de usuários que serão cadastrados
    printf("Quantos usuários serão cadastrados? ");
    scanf("%d", &numUsuarios);
    printf("\n");
    getchar(); // limpa o buffer

    // Cria o vetor de ponteiros para usuários
    users = criaUsuarios(numUsuarios);
    
    // Loop para cadastrar cada usuário
    for (int i = 0; i < numUsuarios; i++) {
        printf("Cadastro usuario %d:\n", i+1);
        leUsuario(buffNome, &idade, buffCpf); // lê dados do usuário
        users[i] = criaUsuario(buffNome, idade, buffCpf); // cria e armazena o usuário
    }

    printf("\nCadastro concluído!\n");

    // Loop para buscar um usuário pelo nome
    while(1) {
        printf("\nQual o nome do usuário que você quer ler? ");
        scanf("%[^\n]", buffNome);
        getchar();

        userAchado = procuraUsuario(buffNome, users, numUsuarios); // busca o usuário

        if(userAchado){
            printf("\nO usuário '%s' foi encontrado, seus dados são: \n", buffNome);
            imprimeUsuario(userAchado); // imprime dados do usuário encontrado
            break;
        }

        printf("Não foi possível encontrar o usuário '%s', tente novamente.\n", buffNome);
    }

    // Libera toda a memória alocada
    liberaUsuario(users, numUsuarios);
}//end main()

// Cria um array de ponteiros para usuários
User** criaUsuarios(int numUsuarios) {    
    User** users = (User**) malloc(numUsuarios * sizeof(User*));
    
    if (!users) {
        printf("Erro na alocação de memória para o Array\n");
        exit(1);    
    }

    // Inicializa os ponteiros com NULL
    for(int i = 0; i < numUsuarios; i++){
        users[i] = NULL;
    }

    return users;
}

// Cria um novo usuário com nome, idade e cpf
User* criaUsuario(char* buffNome, int idade, char* buffCpf){
    User* user = (User*) malloc(sizeof(User));
    
    if(!user) {
        printf("Erro na alocação de memória para o usuário\n");
        exit(1);
    }

    // Aloca memória para o nome
    user->nome = (char*) malloc((strlen(buffNome)+1) * sizeof(char)); 
    if(!user->nome) {
        printf("Erro na alocação de memória para o nome\n");
        free(user);
        exit(1);
    }

    // Aloca memória para o CPF (11 dígitos + '\0')
    user->cpf = (char*) malloc((11+1) * sizeof(char));

    if(!user->cpf) {
        printf("Erro na alocação de memória para o cpf");
        free(user->nome);
        free(user);
        exit(1);
    }

    // Copia os valores recebidos para o novo usuário
    strcpy(user->nome, buffNome);
    strcpy(user->cpf, buffCpf);
    (*user).idade = idade;

    return user;
}

// Lê dados do usuário a partir do teclado
void leUsuario(char* buffNome, int* idade, char* buffCpf){ 
    printf("Insira seu nome: ");
    scanf("%[^\n]", buffNome);

    printf("Insira sua idade: ");
    scanf("%d", idade);
    getchar(); // limpa o buffer

    // Validação simples do CPF (deve ter 11 dígitos)
    while(1) {
        printf("Insira seu cpf: ");
        scanf("%[^\n]", buffCpf);
        getchar();
    
        if(strlen(buffCpf) == 11) {
            printf("\n");
            break;
        }
        else printf("CPF inválido, digite novamente.\n");
    }
}

// Busca um usuário pelo nome no vetor
User * procuraUsuario(char* buffNome, User** users, int numUsuarios){ 
    for (int j = 0; j < numUsuarios; j++) {
        if (users[j] && strcmp(buffNome, users[j]->nome) == 0) {
            return users[j];
        }
    }
    return NULL; // retorna NULL se não encontrar
}

// Imprime os dados de um usuário
void imprimeUsuario(User* user) {
    printf("O nome é: %s\n", user->nome);
    printf("A idade é: %d\n", (*user).idade);
    printf("O cpf é: %s\n", user->cpf);
}

// Libera toda a memória alocada para os usuários
void liberaUsuario(User** users, int numUsuarios) {
    for (int i = 0; i < numUsuarios; i++) {
        free(users[i]->nome);
        free(users[i]->cpf);
        free(users[i]);
    }
    free(users);
}

