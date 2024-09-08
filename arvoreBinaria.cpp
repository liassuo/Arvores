#include <iostream>
using namespace std;

class Node{
    public:
        int valor;
        Node* esq;
        Node* dir;
        Node* pai;

        Node(int v){
            valor = v;
            esq = dir = pai =nullptr;
        }
};

class ArvoreBinaria{
    public:
        Node* raiz;

        ArvoreBinaria(){
            raiz = nullptr;
        }

        //metodo para inserir na arvore
        Node* inserir(Node* no, int valor){
            if(no == nullptr){
                return new Node(valor);
            }

            if(valor < no->valor){
                no->esq = inserir(no->esq, valor);
            }else{
                no->dir = inserir(no->dir, valor);
            }
            return no;
        }

        //faz uma busca na arvore
        bool busca(Node* no, int valor){
            if(no == nullptr){
                return false;
            }
            if(no->valor == valor){
                return true;
            }else if(valor < no->valor){
                return busca(no->esq, valor);
            }else{
                return busca(no->dir, valor);
            }
        }

        //encontrar o menor no
        Node* encontrarMin(Node* no){
            while(no->esq != nullptr){
                no = no->esq;
            }
            return no;
        }

        //encontrar o maior no
        Node* encontrarMax(Node* no){
            while(no->dir != nullptr){
                no = no->dir;
            }
            return no;
        }

        //imprime a arvore em ordem crescente
        void emOrdem(Node* no){
            emOrdem(no->esq);
            cout<<no->valor<<" ";
            emOrdem(no->dir);
        }

        //imprime a arvore em pre ordem
        void preOrdem(Node* no){
            cout<<no->valor<<" ";
            preOrdem(no->esq);
            preOrdem(no->dir);
        }

        //imprime a arvore em pos ordem
        void posOrdem(Node* no){
            posOrdem(no->esq);
            posOrdem(no->dir);
            cout<<no->valor<<" ";
        }

        //exclui um no da arvore
        Node* excluir(Node* no, int valor){
            if(no == nullptr){
                return no;
            }

            if(valor < no->valor){
                no->esq = excluir(no->esq, valor);
            }else if(valor > no->valor){
                no->dir = excluir(no->dir, valor);
            }else{
                if(no->esq == nullptr){
                    Node* aux = no->dir;
                    delete no;
                    return aux;
                }else if(no->dir == nullptr){
                    Node* aux = no->esq;
                    delete no;
                    return aux;
                }

                Node* aux = encontrarMin(no->dir);
                no->valor = aux->valor;
                no->dir = excluir(no->dir, aux->valor);
            }
            return no;
        }

        //metodo que verifica se a arvore esta vazia
        bool estaVazia(){
            return raiz == nullptr;
        }

        //calcula a altura de um no
        int altura(Node* no) {
            if(no == nullptr) return 0;
            int alturaEsq = altura(no->esq);
            int alturaDir = altura(no->dir);
            return 1 + max(alturaEsq, alturaDir);
        }

        //verifica se a arvore esta balanceada
        bool estaBalanceada(Node* no) {
            if (no == nullptr) return true; //balanceada

            int alturaEsq = altura(no->esq);
            int alturaDir = altura(no->dir);

        
            if (abs(alturaEsq - alturaDir) > 1) return false;

            return estaBalanceada(no->esq) && estaBalanceada(no->dir);
        }

        //verifica se a arvore se as subarvores sao um espelho
        bool eEspelho(Node* nodeEsq, Node* nodeDir){
            if(nodeEsq == nullptr && nodeDir == nullptr) return true;
            if(nodeEsq == nullptr || nodeDir == nullptr) return false;

            return (nodeEsq->valor == nodeDir->valor) && eEspelho(nodeEsq->esq, nodeDir->dir) && eEspelho(nodeEsq->dir, nodeDir->esq);
        }

        //verifica se a arvore e simetrica
        bool eSimetrica(Node* raiz){
            if(raiz == nullptr) return true;
            
            return eEspelho(raiz->esq, raiz->dir);
        }
};

