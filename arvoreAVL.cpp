#include <iostream>
using namespace std;

class Node{
    public:
        int valor;
        Node* esq;
        Node* dir;
        Node* pai;
        int altura;

        Node(int v){
            altura = 1;
            valor = v;
            esq = dir = pai = nullptr;
        }
};

class ArvoreAVL{
    public:
        Node* raiz;

        ArvoreAVL(){
            raiz = nullptr;
        }

        int getAltura(Node* no){
            if(no == nullptr) return 0;
            return no->altura;
        }

        int getMax(int a, int b){
            if(a > b) return a;
            else return b;
        }

        //rotaciona para a direita
        Node* rotacionaDireita(Node* raiz){
            Node* x = raiz->esq;
            Node* T2 = x->dir;

            x->dir = raiz;
            raiz->esq = T2;

            raiz->altura = getMax(getAltura(raiz->esq), getAltura(raiz->dir)) + 1;
            x->altura = getMax(getAltura(x->esq), getAltura(x->dir)) + 1;

            return x;
        }

        //rotaciona para a esquerda
        Node* rotacionaEsquerda(Node* raiz){
            Node* y = raiz->dir;
            Node* T2 = y->esq;

            y->esq = raiz;
            raiz->dir = T2;

            raiz->altura = getMax(getAltura(raiz->esq), getAltura(raiz->dir)) + 1;
            y->altura = getMax(getAltura(y->esq), getAltura(y->dir)) + 1;

            return y;
        }

        //obter balanceamento de um nó
        int getBalanceamento(Node* node){
            if (node == nullptr) return 0;
            return getAltura(node->esq) - getAltura(node->dir);
        }

        Node* inserir(Node* node, int valor){
            if(node == nullptr) return new Node(valor);

            if(valor < node->valor){
                node->esq = inserir(node->esq, valor);
            } else{
                node->dir = inserir(node->dir, valor);
            }

            node->altura = getMax(getAltura(node->esq), getAltura(node->dir)) + 1;

            int fatorBal = getBalanceamento(node);

            //caso esquerda-esquerda
            if(fatorBal > 1 && valor < node->esq->valor)
                return rotacionaDireita(node);

            //caso direita-direita
            if(fatorBal < -1 && valor > node->dir->valor)
                return rotacionaEsquerda(node);

            //caso esquerda-direita
            if(fatorBal > 1 && valor > node->esq->valor) {
                node->esq = rotacionaEsquerda(node->esq);
                return rotacionaDireita(node);
            }

            //caso direita-esquerda
            if(fatorBal < -1 && valor < node->dir->valor) {
                node->dir = rotacionaDireita(node->dir);
                return rotacionaEsquerda(node);
            }

            return node;
        }

        void inserir(int valor){
            raiz = inserir(raiz, valor);
        }

        //percorre a árvore em ordem
        void percorrerEmOrdem(Node* node){
            if(node != nullptr){
                percorrerEmOrdem(node->esq);
                cout<<node->valor<<" ";
                percorrerEmOrdem(node->dir);
            }
        }

        void percorrer() {
            percorrerEmOrdem(raiz);
            cout<<endl;
        }

        Node* getMin(Node* node) {        
            while(node->esq != nullptr){
                node = node->esq;
            }
            return node;
        }

        Node* removerNode(Node* raiz, int valor){
            if(raiz == nullptr) return raiz;

            if(valor < raiz->valor){
                raiz->esq = removerNode(raiz->esq, valor);
            }
            else if(valor > raiz->valor){
                raiz->dir = removerNode(raiz->dir, valor);
            }else{
                //no com 1 ou 0 filhos
                if(raiz->esq == nullptr || raiz->dir == nullptr){
                    Node* temp;

                    if(raiz->esq != nullptr){
                        temp = raiz->esq; 
                    }else{
                        temp = raiz->dir;
                    }

                    //nenhum filho
                    if (temp == nullptr) {
                        temp = raiz;
                        raiz = nullptr;

                    }else{ //1 filho
                        *raiz = *temp; 
                    }
                    delete temp;

                }else{ //node com 2 filhos
                    Node* temp = getMin(raiz->dir);

                    raiz->valor = temp->valor;
                    raiz->dir = removerNode(raiz->dir, temp->valor);
                }
            }

            //se tinha apenas 1 node
            if(raiz == nullptr){
                return raiz;
            }
            raiz->altura = 1 + getMax(getAltura(raiz->esq), getAltura(raiz->dir));

            int balance = getBalanceamento(raiz);

            
            //caso esquerda-esquerda
            if (balance > 1 && getBalanceamento(raiz->esq) >= 0) {
                return rotacionaDireita(raiz);
            }

            //caso esquerda-direita
            if (balance > 1 && getBalanceamento(raiz->esq) < 0) {
                raiz->esq = rotacionaEsquerda(raiz->esq);
                return rotacionaDireita(raiz);
            }

            //caso direita-direita
            if (balance < -1 && getBalanceamento(raiz->dir) <= 0) {
                return rotacionaEsquerda(raiz);
            }

            //caso direita-esquerda
            if (balance < -1 && getBalanceamento(raiz->dir) > 0) {
                raiz->dir = rotacionaDireita(raiz->dir);
                return rotacionaEsquerda(raiz);
            }

            return raiz;
        }

        void remover(int valor) {
            raiz = removerNode(raiz, valor);
        }
};

//funcao principal que testa os metodos inserir e remover em uma arvore avl qualquer
int main() {
    ArvoreAVL arvore;

    arvore.inserir(25);
    arvore.inserir(20);
    arvore.inserir(30);
    arvore.inserir(50);
    arvore.inserir(40);
    arvore.inserir(10);

    cout<<"Arvore AVL em ordem: ";
    arvore.percorrer();

    arvore.remover(40);
    arvore.remover(25);
    arvore.remover(50);

    cout<<"Arvore AVL depois de remover alguns nodes: ";
    arvore.percorrer();

    return 0;
}