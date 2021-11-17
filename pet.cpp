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
    char breed[21];
    Gender gender;
    int age;
    float weight;
    struct pet* next;
};


/*
void insertStart(pet **list, char name[], char type[], char breed[], Gender gender, int age, float weight) {
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
*/


void insertEnd(pet **list, char name[], char type[], char breed[], Gender gender, int age, float weight) {
    pet *head = new pet;
    //head = (pet *)malloc(sizeof(pet));
    try {
        strcpy(head->name, name);
        strcpy(head->type, type);
        strcpy(head->breed, breed);
        head->gender = gender;
        head->age = age;
        head->weight = weight;
        head->next = NULL;
        if((*list) == NULL) (*list) = head;
        else {
            pet *temp = (*list);
            while(temp->next) temp = temp->next;
            temp->next = head;
        }
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

        insertEnd(list, data.name, data.type, data.breed, data.gender, data.age, data.weight);
    } catch (const char *err) {
        cout<<"\nErro: " << err << endl;
    }
}


void printPetRec(pet *list) {
    if(list) {
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
        printPetRec(list->next);
    }
}


void removePet (pet **list) {
    char name[21];

    cout << "Digite o nome do pet a ser removido: ";
    cin >> name;
    cin.ignore();

    pet *target = *list;

    // Target anda at� que ele encontre o nome ou seja NULL
    while(target && strcmp(target->name, name) != 0) target = target->next;

    // Se target � NULL, n�o encontrou o nome
    if(target == NULL) {
        cout << "Pet " << name << " n�o encontrado!" << endl;
        return;
    }
    else {
        cout << "Pet " << name << " removido com sucesso!" << endl;
        // Se target � o primeiro da lista 
        if(target == *list) {
            *list = target->next;
            delete target;
            return;
        }
        // Se target est� no meio da lista
        pet *temp = *list;
        while(temp->next != target) temp = temp->next;
        temp->next = target->next;
        delete target;
    }
}


void changePet(pet **list) {
    char name[21];

    cout << "Digite o nome do pet a ser alterado: ";
    cin >> name;
    cin.ignore();

    pet *target = *list;

    // Target anda at� que ele encontre o nome ou seja NULL
    while(target && strcmp(target->name, name) != 0) target = target->next;

    // Se target � NULL, n�o encontrou o nome
    if(target == NULL) {
        cout << "Pet " << name << " n�o encontrado!" << endl;
        return;
    }
    else {
        pet data;

        int tempGender;
        try {
            cout << "\n=-=-=-=-=-=- Informa��es do Pet a ser adicionado -=-=-=-=-=-=\n" << endl;
            cout << "Novo nome: "; cin >> target->name;
            cout << "Nova esp�cie: "; cin >> target->type;
            cout << "Nova ra�a: "; cin >> target->breed;
            do {
                cin.ignore();
                cout << "Novo g�nero (F�mea = 1 / Macho = 2): "; cin >> tempGender;
            } while(tempGender != 1 && tempGender != 2);
            target->gender = selectGender(tempGender - 1);
            cout << "Nova idade: "; cin >> target->age;
            cout << "Novo peso: "; cin >> target->weight;

            
        } catch (const char *err) {
            cout<<"\nErro: " << err << endl;
        }
    }

}


int getCount(pet *list) {
    if (list == NULL) return 0;

    int count = 0;

    while (list) {
        count++;
        list = list->next;
    }
    

    return count;
}


int getCountType(pet *list) {
    if (list == NULL) return 0;

    char type[11];
    int count = 0;

    cout << "Digite a esp�cie do pet a ser buscado: ";
    cin >> type;
    cin.ignore();

    while(list && strcmp(list->type, type) == 0) {
        count++;
        list = list->next;
    }

    return count;
}

/*
pet* searchByType(pet *list, char type[11]) {
    pet* found = NULL;

    if (!list) { cout << "\nNenhum pet cadastrado!"; return NULL; }
    
    while (list) {
        if (strcmp(list->type, type) == 0) {
            pet* aux = list;
            aux->next = found;
            found = aux;
        }
        list = list->next;
    }
    
    if ( found ) {
        cout << "\n[" << getCount( found ) << "] pets da esp�cie [" << type << "] foram encontrados\n";
        printPetRec (found);
    }
    else { cout << "\nNenhum pet da esp�cie [" << type << "] foi cadastrado."; return NULL;}
    
    return found;
}
*/

void searchByName(pet *list) {
    char name[21];

    cout << "Digite o nome do pet a ser buscado: ";
    cin >> name;
    cin.ignore();

    pet *target = list;

    // Target anda at� que ele encontre o nome ou seja NULL
    while(target && strcmp(target->name, name) != 0) target = target->next;

    // Se target � NULL, n�o encontrou o nome
    if(target == NULL) {
        cout << "Pet " << name << " n�o encontrado!" << endl;
        return;
    }
    else {
        pet*aux = list;
        aux->next = NULL;
        printPetRec(aux);
        free(aux);
    }
}


void searchByType(pet *list) {
    char type[11];
    int count = 0;

    cout << "Digite a esp�cie do pet a ser buscado: ";
    cin >> type;
    cin.ignore();
    tolower(*type);

    while(list) {
        if(strcmp(list->type, type) == 0) {
            /*cout
                << "Nome: " << list->name << endl
                << "Esp�cie: " << list->type << endl
                << "Ra�a: " << list->breed << endl;
            if(list->gender == Female) cout << "G�nero: F�mea" << endl;
            else cout << "G�nero: Macho" << endl;
            cout    
                << "Idade: " << list->age << " anos" << endl
                << "Peso: " << list->weight << " kg" << endl
                << endl;*/
            pet*aux = list;
            aux->next = NULL;
            printPetRec(aux);
            free(aux);
            count++;
        }
        list = list->next;
    }
    cout << "Encontrado " << count << " pets com a esp�cie " << type << endl;
}


void searchByTypeAndBreed(pet *list) {
    char type[11];
    char breed[21];
    int count = 0;

    cout << "Digite a esp�cie do pet a ser buscado: ";
    cin >> type;
    cin.ignore();
    tolower(*type);

    cout << "Digite a ra�a do pet a ser buscado: ";
    cin >> breed;
    cin.ignore();
    tolower(*breed);

    while(list) {
        if(strcmp(list->type, type) == 0 && strcmp(list->breed, breed) == 0) {
            pet*aux = list;
            aux->next = NULL;
            printPetRec(aux);
            free(aux);
            count++;
        }
        list = list->next;
    }
    cout << "Encontrado " << count << " pets da esp�cie " << type << " e ra�a " << breed << endl;
}

void searchByTypeBreedAndGender(pet *list) {
    char type[11];
    char breed[21];
    int gender;
    int count = 0;

    cout << "Digite a esp�cie do pet a ser buscado: ";
    cin >> type;
    cin.ignore();

    cout << "Digite a ra�a do pet a ser buscado: ";
    cin >> breed;
    cin.ignore();

    do {
        cout << "G�nero (F�mea = 1 / Macho = 2): ";
        cin >> gender;
    } while(gender != 1 && gender != 2);

    while(list) {
        if(strcmp(list->type, type) == 0 && strcmp(list->breed, breed) == 0 && list->gender == selectGender(gender - 1)) {
            pet*aux = list;
            aux->next = NULL;
            printPetRec(aux);
            free(aux);
            count++;
        }
        list = list->next;
    }
    cout << "Encontrado " << count << " pets ";
    if(selectGender(gender - 1) == Female) cout << "f�mea";
    else cout << "macho";
    cout << " da esp�cie " << type << " e ra�a " << breed << endl;
}


int main() {
    setlocale(LC_ALL, "Portuguese");

    /*FILE *petData;
    if((petData = fopen("pet_data.txt", "r+")) == NULL) {
        cout << "Arquivo n�o existente, criando um novo" << endl;
        petData = fopen("pet_data.txt", "w+");
    }*/

    int option;
    char type[11];
    pet *list = NULL;


    cout << "Bem-vindo � lista de Pets!\n";
    do {
        cout << "\n\nMenu de Op��es" << endl;
        cout << "1 - Inserir na lista de pets" << endl;
        cout << "2 - Remover na lista de pets" << endl;
        cout << "3 - Alterar informa��o de um pet" << endl;
        cout << "4 - Buscar um pet por nome" << endl;
        cout << "5 - Filtrar a lista de pets por esp�cie" << endl;
        cout << "6 - Filtrar a lista de pets por esp�cie e ra�a" << endl;
        cout << "7 - Filtrar a lista de pets por esp�cie, ra�a e sexo" << endl;
        cout << "8 - Quantidade de pets na lista" << endl;
        cout << "9 - Quantidade de pets de uma esp�cie" << endl;
        cout << "10 - Imprimir a lista de pets" << endl;
        cout << "0 - Sair do Programa" << endl;
        cout << "\nDigite a op��o desejada: ";
        cin >> option;
        switch (option) {
            case 1: createPet(&list);
                break;
            case 2: removePet(&list);
                break;
            case 3: changePet(&list);
                break;
            case 4: searchByName(list);
                break;
            case 5: searchByType(list);
                break;
            case 6: searchByTypeAndBreed(list);
                break;
            case 7: searchByTypeBreedAndGender(list);
                break;
            case 8: cout << "\nH� [" << getCount(list) << "] pets cadastrados" << endl;
                break;
            case 9:
                cout << "\nH� [" << getCountType(list) << "] pets cadastrados da ra�a digitada" << endl;
                break;
            case 10: printPetRec(list);
                break;
        }
    } while(option != 0);

    //fclose(petData);

    return 0;
}