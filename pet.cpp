#include <iostream>
#include <stdlib.h>
#include <locale.h>
#include <ctime>
#include <string.h>

// Coisas a serem mudadas: 
// Ver o vídeo do Nakamiti para adicionar a leitura de arquivos baseada em struct
// Mudar os dados linha 61 para uma criação de struct e chamar cada valor fazendo struct.valor

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
        cout << "Informações do Pet a ser adicionado" << endl;
        cout << "Nome: "; cin >> data.name; //name = input();
        cout << "Espécie: "; cin >> data.type;
        cout << "Raça: "; cin >> data.breed;
        do {
            cout << "Gênero (Fêmea = 1 / Macho = 2): "; cin >> tempGender;
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
            << "Espécie: " << list->type << endl
            << "Raça: " << list->breed << endl;
        if(list->gender == Female) cout << "Gênero: Fêmea" << endl;
        else cout << "Gênero: Macho" << endl;
        cout    
            << "Idade: " << list->age << " anos" << endl
            << "Peso: " << list->weight << " kg" << endl
            << endl;
    }
}

int removePet (int n, pet** l) {
    

    return 0;
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    /*FILE *petData;
    if((petData = fopen("pet_data.txt", "r+")) == NULL) {
        cout << "Arquivo não existente, criando um novo" << endl;
        petData = fopen("pet_data.txt", "w+");
    }*/

    int option;
    pet *list = NULL;

    cout << "Bem-vindo à lista de Pets!\n";
    do {
        cout << "\n\nMenu de Opções\n\n";
        cout << "1 - Inserir na lista de pets" << endl;
        cout << "2 - Imprimir a lista de pets" << endl;
        cout << "0 - Sair do Programa" << endl;
        cin >> option;
        switch (option) {
        case 1: createPet(&list);
            break;
        case 2:printPetRec(list);
            break;
        }
    } while(option != 0);

    //fclose(petData);

    return 0;
}