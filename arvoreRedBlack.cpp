#include <iostream>
using namespace std;

class Node{
    public:
        int valor;
        char cor;
        Node* esq;
        Node* dir;
        Node* pai;
        int altura;

        Node(int v){
            altura = 1;
            cor = 'R'; 
            valor = v;
            esq = dir = pai = nullptr;
        }
};

class ArvoreRedBlack{
    public:
        Node* raiz;

        ArvoreRedBlack(){
            raiz = nullptr;
        }

        // rotaciona para a direita
        void rotacionaDireita(Node*& raiz, Node* no){
            Node* filhoEsq = no->esq;
            no->esq = filhoEsq->dir;

            if(no->esq != nullptr){
                no->esq->pai = no;
            }

            filhoEsq->pai = no->pai;

            if(no->pai == nullptr){
                raiz = filhoEsq;
            }else if(no == no->pai->esq){
                no->pai->esq = filhoEsq;
            }else{
                no->pai->dir = filhoEsq;
            }

            filhoEsq->dir = no;
            no->pai = filhoEsq;
        }

        // rotaciona para a esquerda
        void rotacionaEsquerda(Node*& raiz, Node* no){
            Node* filhoDir = no->dir;
            no->dir = filhoDir->esq;

            if(no->dir != nullptr){
                no->dir->pai = no;
            }

            filhoDir->pai = no->pai;

            if(no->pai == nullptr){
                raiz = filhoDir;
            }else if(no == no->pai->esq){
                no->pai->esq = filhoDir;
            }else{
                no->pai->dir = filhoDir;
            }

            filhoDir->esq = no;
            no->pai = filhoDir;
        }

        //corrige a arvore apos uma inserção
        void corrigirArvore(Node*& raiz, Node* no){
            Node* pai_no = nullptr;
            Node* avo_no = nullptr;

            while((no != raiz) && (no->cor != 'P') && (no->pai->cor == 'R')){
                pai_no = no->pai;
                avo_no = no->pai->pai;

                if(pai_no == avo_no->esq){
                    Node* tio_no = avo_no->dir;

                    if(tio_no && tio_no->cor == 'R'){
                        avo_no->cor = 'R';
                        pai_no->cor = 'P';
                        tio_no->cor = 'P';
                        no = avo_no;
                    }else{
                        if(no == pai_no->dir){
                            rotacionaEsquerda(raiz, pai_no);
                            no = pai_no;
                            pai_no = no->pai;
                        }
                        rotacionaDireita(raiz, avo_no);
                        swap(pai_no->cor, avo_no->cor);
                        no = pai_no;
                    }
                }else{
                    Node* tio_no = avo_no->esq;

                    if(tio_no && tio_no->cor == 'R'){
                        avo_no->cor = 'R';
                        pai_no->cor = 'P';
                        tio_no->cor = 'P';
                        no = avo_no;
                    }else{
                        if(no == pai_no->esq){
                            rotacionaDireita(raiz, pai_no);
                            no = pai_no;
                            pai_no = no->pai;
                        }
                        rotacionaEsquerda(raiz, avo_no);
                        swap(pai_no->cor, avo_no->cor);
                        no = pai_no;
                    }
                }
            }

            raiz->cor = 'P';
        }

        //metodo de inserção
        Node* inserir(Node* raiz, Node* no){
            if(raiz == nullptr) return no;

            if(no->valor < raiz->valor){
                raiz->esq = inserir(raiz->esq, no);
                raiz->esq->pai = raiz;
            }else if(no->valor > raiz->valor){
                raiz->dir = inserir(raiz->dir, no);
                raiz->dir->pai = raiz;
            }
            return raiz;
        }
};