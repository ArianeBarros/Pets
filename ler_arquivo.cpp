#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdlib.h>

using namespace std;

struct no {
  int codigo;
  struct no* prox;
};

void insere_inicio(int n, no **lista) {
  no *aux;
  aux = (no *)malloc(sizeof(no));
  aux->codigo = n;
  aux->prox = (*lista);
  (*lista) = aux;
}

void insere_final(int n, no **lista) {
  no *aux2;

  aux2 = (no *)malloc(sizeof(no));
  aux2->codigo = n;
  aux2->prox = NULL;
  if((*lista) == NULL) (*lista) = aux2;
  else {
    no *aux = (*lista);
    while(aux->prox != NULL) aux = aux->prox; 
    aux->prox = aux2;
  }
}

void restaurar_backup(no **lista, ifstream &arq) {
  no *aux2;
  int n;

  while(!arq.eof()) {
    arq >> n;
    arq.ignore(1);
    cout << "Lendo: " << n << endl;
    aux2 = (no *)malloc(sizeof(no));
    aux2->codigo = n;
    aux2->prox = NULL;
    if((*lista) == NULL) (*lista) = aux2;
    else {
      no *aux = (*lista);
      while(aux->prox != NULL) aux = aux->prox; 
      aux->prox = aux2;
    }
  }
}

/*
void imprime_complex(no *lista) {
  cout << "( ";
  while(lista != NULL) {
    cout << "[" << lista->codigo << ", " << lista->prox << "] ";
    lista = lista->prox;
  }
  cout << ")";
}
*/

int soma(no *lista) {
  int i = 0;

  while(lista != NULL) {
    i += lista->codigo;
    lista = lista->prox;
  }

  return i;
}

int soma_rec(no *lista) {
  if(lista == NULL) return 0;
  return lista->codigo + soma_rec(lista->prox);
}

int qtd_no(no *lista) {
  int i = 0;

  while(lista != NULL) {
    i++;
    lista = lista->prox;
  }

  return i;
}

void imprime(no *lista) {
  cout << "( ";
  while(lista != NULL) {
    cout << "[" << lista->codigo << "] ";
    lista = lista->prox;
  }
  cout << ")";
}

void imprime_rec(no *lista) {
  if(lista != NULL) {
    imprime_rec(lista->prox);
    cout << "[" << lista->codigo << "] ";
  }
}


int remove1(no **lista) {
  if((*lista) != NULL) {
    int n = (*lista)->codigo;

    no *aux = (*lista);
    (*lista) = (*lista)->prox;
    free(aux);

    return n;
  }
  return 0;
}

int removeU(no **lista) {
  if((*lista) != NULL) {
    if((*lista)->prox != NULL) {
      no *aux = (*lista);
      while((aux->prox)->prox != NULL) aux = aux->prox;
      int n = (aux->prox)->codigo;
      free(aux->prox);
      aux->prox = NULL;
      return n;
    }
    int n = (*lista)->codigo;
    no *aux = (*lista);
    (*lista) = (*lista)->prox;
    free(aux);
    return n;
  }
  return 0;
}

int main(){
  ofstream outfile;
  ifstream infile;

  setlocale(LC_ALL, "Portuguese");

  int opcao, n;
  no *lista = NULL;

  infile.open ("example.txt");
  if(!infile.is_open()){
    cout << "Arquivo não existe, um arquivo novo será criado para salvar os dados assim que utilizar 0 para Sair do Programa" << endl;
    infile.close();
  }
  else {
    restaurar_backup(&lista, infile);
    infile.close();
  }

  do {
    cout << "\n\nMenu de Opções\n\n";
    cout << "1 - Inserir no início da lista\n";
    cout << "2 - Inserir no final da lista\n";
    cout << "3 - Imprimir a lista\n";
    cout << "4 - Quantidade de nós da lista\n";
    cout << "5 - Soma dos valores da lista\n";
    cout << "6 - Imprimir a lista (recursiva)\n";
    cout << "7 - Remover o primeiro da lista\n";
    cout << "8 - Remover o último da lista\n";
    cout << "0 - Sair do Programa\n";
    cin >> opcao;
    switch (opcao) {
      case 1:
        cout << "Digite o valor a ser inserido: ";
        cin >> n;
        insere_inicio(n, &lista);
        break;
      case 2:
        cout << "Digite o valor a ser inserido: ";
        cin >> n;
        insere_final(n, &lista);
        break;
      case 3: imprime(lista);
        break;
      case 4: cout << "A lista possui " << qtd_no(lista) << " nós";
        break;
      case 5: cout << "A soma dos valores da lista é " << soma_rec(lista);
        break;
      case 6: cout << "( ";
        imprime_rec(lista);
        cout << ")";
        break;
      case 7: cout << "Removido nó: " << remove1(&lista);
        break;
      case 8: cout << "Removido nó: " << removeU(&lista);
        break;
    }
  } while (opcao != 0);

  outfile.open("example.txt");

  if(lista == NULL) outfile << "";
  else {
    no *aux = lista;
    while(aux != NULL) {
      if(aux->prox != NULL) outfile << aux->codigo << endl;
      else outfile << aux->codigo;
      cout << "Armazenando: " << aux->codigo << endl;
      aux = aux->prox;
    }
  }

  outfile.close();
  return 0;
}