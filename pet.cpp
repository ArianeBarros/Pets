#include <iostream>
#include <stdlib.h>
#include <locale.h>
#include <ctime>
#include <string.h>

// Coisas a serem mudadas: 
// Ver o v�deo do Nakamiti para adicionar a leitura de arquivos baseada em struct
// Mudar os dados linha 61 para uma cria��o de struct e chamar cada valor fazendo struct.valor

using namespace std;

enum Gender {Female, Male};
enum Behavior {Calm, Docile, Lonely, Aggressive};

struct pet {
    char name[21];
    char type[11];
    char breed[26];
    Gender gender;
    int age;
    float weight;
    struct pet* next;
};


void insert(pet **list, char name[], char type[], char breed[], Gender gender, int age, float weight) {
    pet *head = new pet;
    //head = (pet *)malloc(sizeof(pet));
    try {
        strcpy(head->name, name);
        strcpy(head->type, type);
        strcpy(head->breed, breed);
        head->gender = gender;
        head->age = age;
        head->weight = weight;
        head->next = (* list);
        (*list) = head;
    } catch (const char * err) {
        cout<<"\nErro: " << err << "\n";
        throw;
    }
    
}


Gender selectGender(int option) {
    return static_cast<Gender>(option);
}


void createPet(pet **list) {
    pet data;

    int tempGender;
    try {
        cout << "\n=-=-=-=-=-=- Informa��es do Pet a ser adicionado -=-=-=-=-=-=\n" << endl;
        cout << "Nome: "; cin >> data.name; //name = input();
        cout << "Esp�cie: "; cin >> data.type;
        cout << "Ra�a: "; cin >> data.breed;
        do {
            cin.ignore();
            cout << "G�nero (F�mea = 1 / Macho = 2): "; cin >> tempGender;
        } while(tempGender != 1 && tempGender != 2);
        data.gender = selectGender(tempGender - 1);
        cout << "Idade: "; cin >> data.age;
        cout << "Peso: "; cin >> data.weight;

        insert(list, data.name, data.type, data.breed, data.gender, data.age, data.weight);
    } catch (const char *err) {
        cout<<"\nErro: " << err << endl;
    }
}


void printPetRec(pet *list) {
    if(list != NULL) {
        printPetRec(list->next);
        cout
            << "Nome: " << list->name << endl
            << "Esp�cie: " << list->type << endl
            << "Ra�a: " << list->breed << endl;
        if(list->gender == Female) cout << "G�nero: F�mea" << endl;
        else cout << "G�nero: Macho" << endl;
        cout    
            << "Idade: " << list->age << " anos" << endl
            << "Peso: " << list->weight << " kg" << endl
            << endl;
    }
}

int removePet (int n, pet** l) {
    

    return 0;
}


int getCount(pet *list) {
    
    if (!list) return 0;

    int qtd = 0;

    while (list) {
        qtd++;
        list = list->next;
    }
    

    return qtd;
}

pet* searchByType(pet *list, char type[11]) {
    pet* found;

    if (!list) { cout << "\nNenhum pet cadastrado!"; return NULL; }
    
    while (list) {
        if (list->type == type) {
            pet* aux = found;
            found = list;
            found->next = aux;
        }
        list = list->next;
    }
    
    if ( found ) {
        cout << "\n[" << getCount( found ) << "] pets da especie [" << type << "] foram encontrados";
        printPetRec (found);
    }
    else { cout << "\nNenhum pet da especie [" << type << "] foi cadastrado."; }

    return found;
}

pet* searchByTypeAndBreed(pet *list) {
    pet* found;

    

    return found;
}

pet* searchByTypeBreedAndGender(pet *list) {
    pet* found;

    

    return found;
}


int main() {
    setlocale(LC_ALL, "Portuguese");

    /*FILE *petData;
    if((petData = fopen("pet_data.txt", "r+")) == NULL) {
        cout << "Arquivo n�o existente, criando um novo" << endl;
        petData = fopen("pet_data.txt", "w+");
    }*/

    int option;
    pet *list = NULL;

    cout << "Bem-vindo � lista de Pets!\n";
    do {
        cout << "\n\nMenu de Op��es\n";
        cout << "\n1 - Inserir na lista de pets" << endl;
        cout << "\n2 - Imprimir a lista de pets" << endl;
        cout << "\n3 - Buscar por especie" << endl;
        cout << "\n4 - Quantidade de pets cadastrados" << endl;
        cout << "\n0 - Sair do Programa" << endl;
        cout << "\nDigite a opcao desejada: ";
        cin >> option;
        switch (option) {
        case 1: createPet(&list);
            break;
        case 2:printPetRec(list);
            break;

        case 3:
            char t[11];
            cout << "\nDigite a especie a ser buscada: "; cin >> t;
            searchByType(list, t);
            break;

        case 4: cout << "\nTemos [" << getCount(list) << "] pets cadastrados" << endl;
            break;
        }
    } while(option != 0);

    //fclose(petData);

    return 0;
}