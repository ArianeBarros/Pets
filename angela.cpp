// Grupo:
// Ariane Paula Barros - RA: 21011817
// Guilherme Zanoni Guidetti - RA: 21001718
// Henrique Vergili de Freitas Dias - RA: 21005466
// Leonardo Hana Bersello - RA: 

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
using namespace std;

struct no {
    int codigo;
    struct no* prox;
    struct no* ant;
};

void input(int n, no **lista){
    no *aux;
    aux= (no *) malloc(sizeof (no));
    aux->codigo = n;
    aux->prox= (*lista);
    (*lista)=aux;
}

void print(no* lista){
    if (lista != NULL){
        cout << "\nLista imprimida: ";
        cout << "\n[ ";
        while (lista!=NULL){
            cout << " ("<< lista->codigo << ") ";
            lista=lista->prox;
        }
        cout << " ]"; 
    }
    else cout << "\nLista vazia!";
    cout <<"\n";
}

void printinverso(no* lista)
{
    no* lista_invertida = NULL;
    no* aux;
    int i;
    while (lista != NULL)
    {
        aux = lista;
        lista = lista->prox;
        aux->ant = lista_invertida;
        lista_invertida = aux;
    }
    lista = lista_invertida;
    if (lista_invertida!=NULL){
        cout << "\nLista imprimida: ";
        cout << "\n[ ";
        while (lista_invertida!=NULL){
            cout << " ("<< lista_invertida->codigo << ") ";
            lista_invertida=lista_invertida->ant;
        }
        cout << " ]"; 
    }
    else cout << "\nLista vazia!";
    cout <<"\n";
}

int search(int n, no *lista){
    if (lista == NULL)
        return 0;
    while (lista!=NULL)
    {
        if (lista->codigo == n)
            return 1;
        lista = lista->prox;
    }
}

int remove_elem_n (no **lista, int n) {
    /* 
    CODIGO DO STACKOVERFLOW
    if(!(*l)) // encerra se não houver item na lista
        return 0;

    ldisp *aux = (*l);
    if((*l)->idAviao == id){ // verifica se posição == 0
        (*l) = (*l)->prox; // coloca a lista no próximo item
        free(aux); // limpa a memória

        return 1; // finaliza com verdadeiro
    }

    ldisp *prev;
    while(aux){ // verifica se aux não chegou ao fim e percorre a posição
        prev = aux; // prev guarda valor da remoção
        aux = aux->prox;
        if(aux && aux->idAviao == id){ // verifica o id do avião
            prev->prox = aux->prox;
            free(aux);
            return 1;
        }
    }
    return 0;
    }
    */
    /* 
    CODIGO DO STACKOVERFLOW MODIFICADO PRA RODAR AQUI
    if((*lista == NULL))
        return 0;

    no *aux = (*lista);
    no *ant;

    if((*lista)->codigo == n){
        (*lista) = (*lista)->prox;
        free(aux);
        return 1;
    }
    while(aux){
        ant = aux;
        aux = aux->prox;
        if(aux->codigo == n){
            ant->prox = aux->prox;
            free(aux);
            return 1;
        }
    }
    return 0;
    }*/



    if (lista == NULL) return 0;
    no* aux = (no*) malloc(sizeof(no));
    no* anterior = (no*) malloc(sizeof(no));
    int removed = 0;
    while (aux && !removed) {
        anterior = aux;
        if (aux->prox->codigo == n) {
            aux->prox = aux->prox->prox;
            removed = 1;
        }
        aux = aux->prox;
    }
    cout<<"\nchegou aqui\n";
    if (removed) {
        //alterar lista
        while (*lista) {
            if ((*lista)->codigo == anterior->codigo) {
                *lista = aux;
                return 1;
            }
            *lista = (*lista)->prox;
        }
        return 1;
    }

    return 0;
}

int remove_first(no **lista){
    if (*lista){
        no* aux;
        int n;
        aux = (*lista);
        n = aux->codigo;
        (*lista) = aux->prox;
        free(aux);
        return n;

    }
}
int main(){
    SetConsoleOutputCP(65001); // mostrar acentos
    int opcao, n;
    no *lista=NULL;   // lista vazia

    do{
        cout << "\n\n=-=-=-=-=-=-= MENU =-=-=-=-=-=-=\n";
        cout << "1- Inserir novo nó\n";
        cout << "2- Imprimir nós presentes\n";
        cout << "3- Imprimir nós em ordem inversa\n";
        cout << "4- Procurar valor na lista\n";
        cout << "5- Remover primeiro valor\n";
        cout << "6- Remover valor especifico\n";
        cout << "0- Sair do programa\n";
        cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
        cout << "Escolha: ";
        do{
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1200, '\n');
                cout << "Utilize somente números.\nEscolha: ";

            }
            cin>>opcao;
            if (!cin.fail() && opcao != 0 && opcao != 1 && opcao != 2 && opcao != 3 && opcao != 4&& opcao != 5 && opcao != 6)
                cout << "Valores entre 0 e 6.\nEscolha: ";
        }while(cin.fail() || (opcao != 0 && opcao != 1 && opcao != 2 && opcao != 3 && opcao != 4 && opcao != 5 && opcao != 6));
        switch (opcao) {
            case 1:
                cout << "Digite o valor a ser inserido: ";
                do{
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(1200, '\n');
                        cout << "Utilize somente números.\n";
                        cout << "Digite o valor a ser buscado: ";
                    }
                    cin>>n;
                }while(cin.fail());
                input(n, &lista);
                break;
                
            case 2: 
                print(lista);
                break;
                
            case 3: 
                printinverso(lista);
                break;
                
            case 4:
                cout << "Digite o valor a ser buscado: ";
                do{
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(1200, '\n');
                        cout << "Utilize somente números.\n";
                        cout << "Digite o valor a ser buscado: ";
                    }
                    cin>>n;
                }while(cin.fail());
                cout << "\nO valor ";
                if (search(n , lista) == 1)
                    cout << "está ";
                else 
                    cout << "não está ";
                cout << "presente na lista.\n";
                break;

            case 5:
                cout << "Valor removido: " << remove_first(&lista);
                break;

            case 6:
                cout << "Digite o valor a ser removido: ";
                do{
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(1200, '\n');
                        cout << "Utilize somente números.\n";
                        cout << "Digite o valor a ser removido: ";
                    }
                    cin>>n;
                }while(cin.fail());
                cout << "\nO valor ";
                if (remove_elem_n(&lista, n) == 1)
                    cout << "está ";
                else 
                    cout << "não está ";
                cout << "presente na lista.\n";
                break;
        }
    } while (opcao!=0);
    return 0;
}