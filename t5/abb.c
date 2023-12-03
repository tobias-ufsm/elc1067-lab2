#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "abb.h"

bool codIndisponivel(Arv* a, int cod){
    bool esq, dir;
    if (a != NULL) {
        if(a->cod == cod){
            return true;
        }
        esq = codIndisponivel(a->esq, cod);
        dir = codIndisponivel(a->dir, cod);
    }
    if(esq == true || dir == true){
        return true;
    }else{
        return false;
    }
    
}


void abb_imprime(Arv* a){
    if (a != NULL) {
        abb_imprime(a->esq);
        printf("Cod: %d ",a->cod);
        printf("Curso: %s\n",a->curso->nome);
        abb_imprime(a->dir);
    }
}


Arv* abb_insere (Arv* a, int v){
    if (a==NULL) {
        a = (Arv*)malloc(sizeof(Arv));
        a->curso = (Curso*)malloc(sizeof(Curso));
        printf("Qual o nome do curso?");
        scanf(" %30[^\n]", a->curso->nome);
        a->cod = v;
        a->esq = a->dir = NULL;
        a->curso->alunos = (Lista*)malloc(sizeof(Lista));
        a->curso->alunos = NULL;
        printf("Arvore locada com sucesos");
    }
    else if (v < a->cod){
        a->esq = abb_insere(a->esq,v);
    }else{
        a->dir = abb_insere(a->dir, v);
    }
    return a;
}

Arv* achaCod(Arv* arvore, int codCurso){
    Arv* dir = NULL; Arv* esq = NULL;
    if(arvore!=NULL){
        if(arvore->cod==codCurso){
            return arvore;
        }else{
            dir = achaCod(arvore->dir, codCurso);
            esq = achaCod(arvore->esq, codCurso);
        }
    }
    if(esq != NULL){
        return esq;
    }else if(dir != NULL){
        return dir;
    }
    return NULL;
}

Lista* insereListaAluno(Arv* arvore, int codCurso, char nomeAluno[], int matricula, int anoIngresso){
    Lista* l = (Lista*)malloc(sizeof(Lista));
    for(int i=0;i<25;i++){
        l->nome[i] = nomeAluno[i];
    }
    l->matricula = matricula;
    l->ano = anoIngresso;
    Lista* p=arvore->curso->alunos;
    if(arvore->curso->alunos == NULL){
        return l;
    }else if(arvore->curso->alunos->matricula > matricula){
        l->prox=p;
        return l;
    }    
    Lista* ant=arvore->curso->alunos;
    while (p!=NULL && p->matricula < l->matricula)
    {
        ant=p;
        p=p->prox;
    }
    if(p==NULL){
        ant->prox=l;
    }else{
        ant->prox = l;
        l->prox = p;
    }
    return arvore->curso->alunos;
}

Arv* abb_retira (Arv* r, int v){
    if (r == NULL){
        printf("Ainda nao tem curso cadastrado\n");
        return NULL;
    }else if (r->cod > v)
        r->esq = abb_retira(r->esq, v);
    else if (r->cod < v)
        r->dir = abb_retira(r->dir, v);
    else { /* achou o nó a remover */
    /* nó sem filhos */
    if (r->esq == NULL && r->dir == NULL) {
        free (r);
        r = NULL;
        printf("Curso removido\n");
    }
    /* nó só tem filho à direita */
    else if (r->esq == NULL) {
        Arv* t = r;
        r = r->dir;
        free (t);
        printf("Curso removido\n");
    }
    /* só tem filho à esquerda */
    else if (r->dir == NULL) {
        Arv* t = r;
        r = r->esq;
        free (t);
        printf("Curso removido\n");
    }
    /* nó tem os dois filhos */
    else {
        Arv* f = r->esq;
        while (f->dir != NULL) {
        f = f->dir;
        }
        r->cod = f->cod; /* troca as informações */
        f->cod = v;
        r->esq = abb_retira(r->esq,v);
        }
    }
    return r;
}

Lista* excluiAlunoLista(Arv* arvore, int mat){
    Lista* ant = NULL;
    Lista* p = arvore->curso->alunos;
    while (p!=NULL && p->matricula!=mat)
    {
        ant=p;
        p=p->prox;
    }
    if(p==NULL){
        printf("Nao tem aluno com essa matricula\n");
        return arvore->curso->alunos;
    }
    if(ant==NULL){
        arvore->curso->alunos=p->prox;
    }else{
        ant->prox=p->prox;
    }
    free(p);
    return arvore->curso->alunos;
    
}