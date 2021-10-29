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
    pet *head;
    head = (pet *)malloc(sizeof(pet));
    head->name = name;
    head->type = type;
    head->breed = breed;
    head->gender = gender;
    head->age = age;
    head->weight = weight;
    head->next = (* list);
    (*list) = head;
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

    cout << "Informações do Pet a ser adicionado" << endl;
    cout << "Nome: "; name = input();
    cout << "Espécie: "; type = input();
    cout << "Raça: "; breed = input();
    do {
        cout << "Gênero (Fêmea = 1 / Macho = 2): "; cin >> tempGender;
    } while(tempGender != 1 && tempGender != 2);
    gender = selectGender(tempGender - 1);
    cout << "Idade: "; cin.ignore(); cin >> age;
    cout << "Peso: "; cin.ignore(); cin >> weight;

    insert(list, name, type, breed, gender, age, weight);
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


int main() {
    setlocale(LC_ALL, "Portuguese");

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
}
