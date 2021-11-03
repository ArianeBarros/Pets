#include <iostream>
#include <stdlib.h>
#include <locale.h>
#include <ctime>
#include <string.h>

using namespace std;

enum Gender {Female, Male};
enum Behavior {Calm, Docile, Lonely, Aggressive};

struct pet {
    string name;
    string type;
    string breed;
    Gender gender;
    int age;
    float weight;
    struct pet* next;
};


void insert(pet **list, string name, string type, string breed, Gender gender, int age, float weight) {
    pet *head = new pet;
    //head = (pet *)malloc(sizeof(pet));
    try {
        head->name = name;
        head->type = type;
        head->breed = breed;
        head->gender = gender;
        head->age = age;
        head->weight = weight;
        head->next = (* list);
        (*list) = head;
    } catch (const char * err) {
        cout<<"\nErro: "<<err<<"\n";
        throw;
    }
    
}


Gender selectGender(int option) {
    return static_cast<Gender>(option);
}


string input() {
    string temp;
    cin.ignore();
    getline(cin, temp);
    return temp;
}


void createPet(pet **list) {
    string name, type, breed;
    Gender gender;
    int age;
    float weight;

    int tempGender;
    try {
        cout << "Informa��es do Pet a ser adicionado" << endl;
        cout << "Nome: "; cin.ignore(); getline(cin, name); //name = input();
        cout << "Esp�cie: "; type = input();
        cout << "Ra�a: "; breed = input();
        do {
            cout << "G�nero (F�mea = 1 / Macho = 2): "; cin >> tempGender;
        } while(tempGender != 1 && tempGender != 2);
        gender = selectGender(tempGender - 1);
        cout << "Idade: "; cin.ignore(); cin >> age;
        cout << "Peso: "; cin.ignore(); cin >> weight;

        insert(list, name, type, breed, gender, age, weight);
    } catch (const char * err) {
        cout<<"\nErro: "<<err<<"\n";
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

int main() {
    setlocale(LC_ALL, "Portuguese");

    int option;
    pet *list = NULL;

    cout << "Bem-vindo � lista de Pets!\n";
    do {
        cout << "\n\nMenu de Op��es\n\n";
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
}
