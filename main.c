#include <stdio.h>  //para utilizar gets(),printf(), scanf()
#include <stdlib.h> //para utilizar system(), exit()
#include <locale.h> //para utilizar setlocale()
#include <string.h>
#include <conio.h>  //para utilizar getch()

//Criando um objeto Usuário utilizando struct
typedef struct Usuario {
    char login[50];
    char senha[10];
}Usuario;

//Criando um objeto Data utilizando struct. A data será utilizada para calcular a idade do paciente
typedef struct Data {
    int dia;
    int mes;
    int ano;
}Data;

typedef struct Paciente {
    char nome[100];
    int cpf;
    int telefone;
    char rua[100];
    int numero;
    char bairro[50];
    char cidade[50];
    char estado[3];
    int cep;
    Data dataNascimento;
    char email[100];
    Data dataDiagnostico;
    char comorbidade[150];
}Paciente;

//Criando um tipo booleano
typedef enum boolean bool;

enum boolean {
    true = 1, false = 0
};

//Criando os métodos que serão utilizados
void cabecalho();
void cadastrarUsuario();
void login();
void cadastrarPaciente();
bool validaGrupoRisco();
void menuTelaCadastroPaciente();

int main()
{
    setlocale(LC_ALL, "Portuguese"); //para formatação de caracteres especiais

    int opcao;

    do {
        cabecalho();
        printf("=======================================================================================\n");
        printf("                                  SEJA BEM VINDO!!!                                    \n");
        printf("=======================================================================================\n");
        printf("\n 1 - Login\n");
        printf("\n 2 - Não é usuário? Cadastre-se\n");
        printf("\n 3 - Sair\n");
        printf("\n Escolha uma opção:");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                login();
                break;
            case 2:
                cadastrarUsuario();
                break;
            case 3:
                printf("\nSe deseja sair do sistema clique em Enter para sair\n");
                exit(1);
                break;
            default:
                printf("\nOpção inválida, clique em Enter para voltar ao menu\n");
                menuTelaCadastroPaciente();
                getch(); //interrompe a execução até o usuário cliclar em alguma tecla do teclado
            break;
            }
        }while(opcao != 3 );

    return 0;
}

void cabecalho() {
    system("cls");
    printf("=======================================================================================\n");
    printf("           SISTEMA DE CADASTRO PARA PACIENTES DIAGNOSTICADOS COM COVID-19              \n");
    printf("=======================================================================================\n");
}

void menuTelaCadastroPaciente() {
    int opcaoCadastroPaciente;

    do {
        system("cls");
        cabecalho();
        printf("=======================================================================================\n");
        printf("                                   CADASTRO DO PACIENTE                                \n");
        printf("=======================================================================================\n");
        printf("\n 1 - Cadastrar novo Paciente\n");
        printf("\n 2 - Voltar para a tela principal\n\n");
        printf("\n Escolha uma opção:");
        scanf("%d", &opcaoCadastroPaciente);

        switch(opcaoCadastroPaciente) {
            case 1:
                cadastrarPaciente();
                break;
            case 2:
                printf("\n Voltando para a tela principal\n");
                main();
                break;
            default:
                printf("\n Opção inválida\n");
                getch(); //interrompe a execução até o usuário cliclar em alguma tecla do teclado
            break;
            }
        }while(opcaoCadastroPaciente != 2 );
}

//metodo para cadastrar os dados de login e senha do usuário
void cadastrarUsuario() {
    FILE *arquivousuario;

    Usuario usuario;

    arquivousuario = fopen("usuarios.txt","ab");

    if(arquivousuario == NULL) {
        printf("\nErro ao criar o arquivo");
        arquivousuario = fopen("usuarios.txt","ab");
        system("pause");
    }
    else {
        do{
            system("cls");
            cabecalho();
            printf("=======================================================================================\n");
            printf("                                CADASTRO DE USUÁRIO                                    \n");
            printf("=======================================================================================\n");

            printf("\n Digite o seu e-mail:");
            scanf("%s", usuario.login); //Utilizando scanf para pegar os dados digitados pelo usuário

            printf("\n Digite a sua senha:");
            scanf("%s", usuario.senha);

            //gravando as informações de login e senha do usuário no arquivo usuarios.txt
            fwrite(&usuario, sizeof(Usuario),1,arquivousuario);
            printf("\n Dados cadastrados com Sucesso!\n");
            system("pause");

            printf(" Se deseja voltar para o menu digite (n)\n");
            printf(" Se deseja cadastrar um novo usuário digite (s)\n");


        }while(getche() == 's');

    }
    fclose(arquivousuario);
}

//metodo para validação de login e senha para acesso ao cadastro do paciente
void login() {

    FILE *arquivousuario;

    Usuario usuario;

    arquivousuario = fopen("usuarios.txt","rb");

    if(arquivousuario == NULL) {
        printf("\nO arquivo não pôde ser aberto");
        //cadastrarUsuario();
        exit(1);
    }else {
        char loginTemp[50];
        char senhaTemp[10];

        cabecalho();
        printf("=======================================================================================\n");
        printf("                          ENTRE COM LOGIN E SENHA CADASTRADOS                          \n");
        printf("=======================================================================================\n");

        printf("\n Digite o seu login(e-mail):");
        scanf("%s", loginTemp);

        printf("\n Digite sua senha:");
        scanf("%s", senhaTemp);

        //Compara se o login e senha digitados na tela de login são iguais ao login e senha cadastrados
        while(fread(&usuario,sizeof(struct Usuario),1,arquivousuario)) {
            if(strcmp(loginTemp,usuario.login) == 0 && strcmp(senhaTemp,usuario.senha) == 0) {
                printf("Login realizado com sucesso");
                menuTelaCadastroPaciente();
                exit(1);
            }else {
                printf("\nNão foi possível logar, verifique seu login e senha\n");
                system("pause");
                login();
            }
        }
        fclose(arquivousuario);
    }
}

int idade;
bool possuiComorbidade;

//método para o cadastro dos dados do paciente
void cadastrarPaciente() {

    int dia, mes, ano;
    char resposta;
    bool ehGrupoRisco;

    Paciente paciente; //criando uma variável paciente do Tipo Paciente

    FILE *arquivopaciente;  //criando um ponteiro arquivopaciente do tipo FILE

    arquivopaciente = fopen("cadastropacientes.txt", "ab");   /*abrindo o arquivo txt arquivopacientes onde
                                                                  será armazenada as informações dos pacientes*/

    if(arquivopaciente == NULL) {
        printf("Não foi possível abrir o arquivo");
        arquivopaciente = fopen("cadastropacientes.txt", "ab");
        exit(1);
    }else {
        do{
            system("cls");
            cabecalho();
            printf("=======================================================================================\n");
            printf("                             PRONTUÁRIO DO PACIENTE                                    \n");
            printf("=======================================================================================\n");

            printf("\n Nome do paciente:");
            fflush(stdin);
            scanf("%[^\n]", paciente.nome);

            printf("\n CPF:");
            scanf("%d", &paciente.cpf);

            printf("\n Telefone:");
            scanf("%d", &paciente.telefone);

            printf("\n Logradouro:");
            fflush(stdin);
            scanf("%[^\n]", paciente.rua);

            printf("\n Número:");
            scanf("%d", &paciente.numero);

            printf("\n Bairro:");
            fflush(stdin);
            scanf("%[^\n]", paciente.bairro);

            printf("\n Cidade:");
            fflush(stdin);
            scanf("%[^\n]", paciente.cidade);

            printf("\n Estado(sigla):");
            fflush(stdin);
            scanf("%[^\n]", paciente.estado);

            printf("\n CEP(XXXXX-XXX):");
            scanf("%d", &paciente.cep);

            printf("\n Data de nascimento(dd/mm/aaaa):");
            scanf("%d%*c%d%*c%d", &dia, &mes, &ano);
            paciente.dataNascimento.dia = dia;
            paciente.dataNascimento.mes = mes;
            paciente.dataNascimento.ano = ano;

            printf("\n Email:");
            fflush(stdin);
            scanf("%[^\n]", paciente.email);

            printf("\n Data de diagnóstico(dd/mm/aaaa):");
            scanf("%d%*c%d%*c%d", &dia, &mes, &ano);
            paciente.dataDiagnostico.dia = dia;
            paciente.dataDiagnostico.mes = mes;
            paciente.dataDiagnostico.ano = ano;

            printf("\n O paciente possui alguma comorbidade? (s/n):");
            resposta = getch();
            if((resposta!='n') && (resposta!='N')){
                printf("\n Digite o tipo de comorbidade do paciente:");
                fflush(stdin);
                scanf("%[^\n]", paciente.comorbidade);
                possuiComorbidade = true;           //verificação se o paciente possui comorbidade
            }
            else{
                possuiComorbidade = false;
            }

            fwrite(&paciente, sizeof(Paciente),100,arquivopaciente); //salvando as informações do paciente no arquivopaciente

            fprintf(arquivopaciente,"\nNome: %s", paciente.nome);    //formatação de texto no arquivopaciente
            fprintf(arquivopaciente,"\nCPF: %d", paciente.cpf);
            fprintf(arquivopaciente,"\nTelefone: %d", paciente.telefone);
            fprintf(arquivopaciente,"\nRua: %s", paciente.rua);
            fprintf(arquivopaciente,"\nNúmero: %d", paciente.numero);
            fprintf(arquivopaciente,"\nBairro: %s", paciente.bairro);
            fprintf(arquivopaciente,"\nCidade: %s", paciente.cidade);
            fprintf(arquivopaciente,"\nEstado: %s", paciente.estado);
            fprintf(arquivopaciente,"\nCEP: %d", paciente.cep);
            fprintf(arquivopaciente,"\nAno de nascimento: %d", paciente.dataNascimento.ano);
            fprintf(arquivopaciente,"\nE-mail: %s", paciente.email);
            fprintf(arquivopaciente,"\nAno do diagnóstico: %d", paciente.dataDiagnostico.ano);
            fprintf(arquivopaciente,"\nTipo de comorbidade: %s", paciente.comorbidade);

            printf("\n Paciente salvo com sucesso!!\n");


            ehGrupoRisco = validaGrupoRisco(possuiComorbidade, paciente);

            if(ehGrupoRisco == true) {
                printf("\n O paciente cadastrado faz parte do grupo de risco\n");

            }else {
                printf("\n O paciente cadastrado não faz parte do grupo de risco\n");
            }

            printf("\n Deseja cadastrar um novo paciente(s/n)?\n");
            resposta = getch();
            if(resposta == 's' && resposta == 'S' ) {
                cadastrarPaciente();
            }else {
                printf("\n Clique em Enter para voltar ao menu de cadastro de pacientes\n");
                system("\npause");
                menuTelaCadastroPaciente();
            }

        }while(getche() == 's');
        fclose(arquivopaciente);
        system("pause");
    }
}

//metodo para validar se o paciente cadastrado faz parte do grupo de risco covid
bool validaGrupoRisco(bool possuiComorbidade, Paciente paciente) {

         bool grupoRisco;
         int anoNascimento, anoDiagnostico;

         FILE *arquivogruporisco;

         int idade = 0;
         anoNascimento = paciente.dataNascimento.ano;
         anoDiagnostico = paciente.dataDiagnostico.ano;
         idade = anoDiagnostico-anoNascimento;               //calcula a idade do paciente
         if((idade > 65)  || (possuiComorbidade == true)) {  //verifica se o paciente faz parte do grupo de risco
            grupoRisco = true;
         }else {
            grupoRisco = false;
         }

         if(grupoRisco == true) {                              /*se o paciente for do grupo de risco
                                                               a informação de cep, nome e idade é salva no arquivo gruporisco"                     */
            arquivogruporisco = fopen("gruporisco.txt", "ab");

            fprintf(arquivogruporisco,"\nCEP: %d", paciente.cep);  //formatação de texto no arquivo grupo risco
            fprintf(arquivogruporisco,"\nNome: %s", paciente.nome);
            fprintf(arquivogruporisco,"\nIdade: %d", idade);

            fclose(arquivogruporisco);  //fecha o arquivo grupo risco

            if(arquivogruporisco == NULL) {
                printf("\n Não foi possível abrir o arquivo\n");
                arquivogruporisco = fopen("gruporisco.txt", "ab");
            }else {
                printf("\n Paciente do grupo de risco salvo com sucesso no arquivo da Secretaria de Saúde!!!\n");
            }
         }
         return grupoRisco;
}

