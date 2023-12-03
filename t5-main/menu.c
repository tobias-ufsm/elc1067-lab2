#include <stdio.h>
#include <stdlib.h>
#include "abb.h"



Arv* insereCurso(Arv* arvore){
    int cod;
    printf("Qual o codigo do curso? \n");
    scanf("%d", &cod);
    if(codIndisponivel(arvore, cod)){
        printf("Esse cod ja esta em uso");
    }else{
        arvore = abb_insere(arvore, cod);
    }
    return arvore;
}

void insereAluno(Arv* arvore){
    int codCurso;
    char nomeAluno[25];
    int anoIngresso, matricula;
    printf("Qual o codigo do curso que deseja inserir? \n");
    scanf("%d",&codCurso);
    arvore = achaCod(arvore, codCurso);
    if(arvore!=NULL){
        printf("Qual nome do aluno? ");
        scanf(" %25[^\n]", nomeAluno);
        printf("\nQual a matricula? \n");
        scanf("%d",&matricula);
        printf("\nQual o ano de ingresso? \n");
        scanf("%d", &anoIngresso);
        arvore->curso->alunos = insereListaAluno(arvore, codCurso, nomeAluno, matricula, anoIngresso);
    }else{
        printf("Nao achou curso com esse cod");
    }
}

void printaAlunos(Arv* arvore){
    int cod;
    printf("\nDeseja imprimir alunos de qual cod curso? ");
    scanf("%d",&cod);
    arvore = achaCod(arvore, cod);
    if(arvore != NULL){
        printf("-- %s --\n",arvore->curso);
        if(arvore->curso->alunos != NULL){
        for(Lista* l=arvore->curso->alunos;l!=NULL;l=l->prox){
            printf("------------------\n");
            printf("Nome: %s\n",l->nome);
            printf("Matricula: %d\n",l->matricula);
            printf("Ano: %d\n",l->ano);
            printf("------------------\n");
        }   
        }else{
            printf("Nao existem alunos nesse curso\n");
        }
    }else{
        printf("Esse curso nao existe");
    }
}
    
void excluiAluno(Arv* arvore){
    int codCurso, mat;
    printf("Qual curso deseja remover aluno? ");
    scanf("%d",&codCurso);
    arvore = achaCod(arvore, codCurso);
    if(arvore==NULL){
        printf("Nao tem curso com esse codigo\n");
        return;
    }
    printf("Qual a matricula do aluno que deseja excluir? ");
    scanf("%d", &mat);
    excluiAlunoLista(arvore, mat);
}

Arv* excluiCurso(Arv* arvore){
    int cod;
    printf("Qual o codigo do curso que deseja remover? ");
    scanf("%d",&cod);
    arvore = abb_retira(arvore,cod);
}

void openUniversity(){
    Arv* arvore = (Arv*)malloc(sizeof(Arv));
    arvore = NULL;
    int aberto = 1;
    int ctrl;
    while (aberto)
    {
        printf("\n----MENU----\n1- Insere Curso\n2- Imprime Cursos\n3- Insere Aluno\n4- Printa Alunos\n5- Exclui Aluno\n6- Exclui Curso\n");
        scanf("%d", &ctrl);
        switch (ctrl)
        {
        case 1:
            arvore = insereCurso(arvore);
            break;
        case 2:
            abb_imprime(arvore);
            break;
        case 3:
            insereAluno(arvore);
            break;
        case 4:
            printaAlunos(arvore);
            break;
        case 5:
            excluiAluno(arvore);
            break;
        case 6:
            arvore = excluiCurso(arvore);
            break;
        case 7:
            aberto = 0;
            break;
        default:
            break;
        }
    }
    
}