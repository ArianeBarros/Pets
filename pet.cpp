#include <iostream>
#include <stdlib.h>
#include <locale.h>
#include <ctime>
#include <string.h>
#include <windows.h>
// Coisas a serem mudadas: 
// Ver o v�deo do Nakamiti para adicionar a leitura de arquivos baseada em struct
// Mudar os dados linha 61 para uma cria��o de struct e chamar cada valor fazendo struct.valor

using namespace std;

enum Gender {Female, Male};
enum Behavior {Calm, Docile, Lonely, Aggressive};

struct pet {
    int cod;
    char name[21];
    char type[11];
    char breed[21];
    Gender gender;
    int age;
    float weight;
    struct pet* next;
};

//INICIALIZANDO AS FUN��ES
void insertEnd(pet **list, int cod, char name[], char type[], char breed[], Gender gender, int age, float weight);
void createPet(pet **list);
void printPetRec(pet *list);
void removePet (pet **list);
void removePetByCode( pet **list, int cod, char name[]);
void changePet(pet **list);
int getCount(pet *list);
int getCountType(pet *list);
pet* searchByName(pet *list, char name[]);
void searchByType(pet *list);
void searchByTypeAndBreed(pet *list);
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

/* INSERIR NO INICIO - NAO USAMOS MAIS
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


void insertEnd(pet **list, int code, char name[], char type[], char breed[], Gender gender, int age, float weight) {
    pet *head = new pet;
    //head = (pet *)malloc(sizeof(pet));
    try {
        head->cod = code;
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
        SetConsoleTextAttribute(hConsole, 9); cout << "\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="<< endl;
        SetConsoleTextAttribute(hConsole, 11); cout << "    Informa��es do"; 
        SetConsoleTextAttribute(hConsole, 10); cout << " Pet"; 
        SetConsoleTextAttribute(hConsole, 11); cout << " a ser adicionado" << endl;
        SetConsoleTextAttribute(hConsole, 9); cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="<< endl << endl;
        SetConsoleTextAttribute(hConsole, 14); cout << "Nome"; 
        SetConsoleTextAttribute(hConsole, 15); cout << ": "; cin >> data.name; //name = input();
        SetConsoleTextAttribute(hConsole, 14); cout << "Esp�cie";
        SetConsoleTextAttribute(hConsole, 15); cout << ": "; cin >> data.type;
        SetConsoleTextAttribute(hConsole, 14); cout << "Ra�a"; 
        SetConsoleTextAttribute(hConsole, 15); cout << ": "; cin >> data.breed;
        do {
            cin.ignore();
			if (cin.fail())
        	{
            cin.clear();
            cin.ignore(1200, '\n');
            SetConsoleTextAttribute(hConsole, 12); cout << "Utilize somente n�meros.\n";
        	}while(cin.fail());
            SetConsoleTextAttribute(hConsole, 14); cout << "G�nero ";
            SetConsoleTextAttribute(hConsole, 15); cout << "(";
            SetConsoleTextAttribute(hConsole, 13); cout << "F�mea = 1";
            SetConsoleTextAttribute(hConsole, 15); cout << "/";
            SetConsoleTextAttribute(hConsole, 11); cout << "Macho = 2";
            SetConsoleTextAttribute(hConsole, 15); cout << "): "; 
            SetConsoleTextAttribute(hConsole, 15); cin >> tempGender;
        }while(tempGender != 1 && tempGender != 2);
        data.gender = selectGender(tempGender - 1);
        do {
			if (cin.fail())
        	{
            cin.clear();
            cin.ignore(1200, '\n');
            SetConsoleTextAttribute(hConsole, 12); cout << "Utilize somente n�meros.\n";
        	}while(cin.fail());
            SetConsoleTextAttribute(hConsole, 14); cout << "Idade";
            SetConsoleTextAttribute(hConsole, 15); cout << ": "; cin >> data.age;
        }while(cin.fail() || data.age < 0 || data.age > 500);
        do {
			if (cin.fail())
        	{
            cin.clear();
            cin.ignore(1200, '\n');
            SetConsoleTextAttribute(hConsole, 12); cout << "Utilize somente n�meros.\n";
        	}while(cin.fail());
            SetConsoleTextAttribute(hConsole, 14); cout << "Peso";
            SetConsoleTextAttribute(hConsole, 15); cout << ": "; cin >> data.weight;
        }while(cin.fail() || data.weight < 0 || data.weight > 500);
        int cod = getCount(*list) + 1;
        insertEnd(list, cod, data.name, data.type, data.breed, data.gender, data.age, data.weight);
    } catch (const char *err) {
        SetConsoleTextAttribute(hConsole, 12); cout<<"\nErro: " << err << endl;
    }
}


void printPetRec(pet *list) {
    if (getCount(list) != 0)
    { 
        if(list) {
            SetConsoleTextAttribute(hConsole, 10); cout << "Codigo";
            SetConsoleTextAttribute(hConsole, 15); cout << ":" << list->cod << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Nome";
            SetConsoleTextAttribute(hConsole, 15); cout << ":" << list->name << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Esp�cie";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->type << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Ra�a";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->breed << endl;
            if(list->gender == Female)
            {
                SetConsoleTextAttribute(hConsole, 10); cout << "G�nero";
                SetConsoleTextAttribute(hConsole, 15); cout << ": ";
                SetConsoleTextAttribute(hConsole, 13); cout <<"? F�mea"<< endl;
            }
            else
            { 
                SetConsoleTextAttribute(hConsole, 10); cout << "G�nero: ";
                SetConsoleTextAttribute(hConsole, 11); cout <<"? Macho" << endl;
            }
            SetConsoleTextAttribute(hConsole, 10); cout << "Idade";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->age << " anos" << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Peso";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->weight << "kg" << endl << endl;
            printPetRec(list->next);
        }
    }
}


void removePet (pet **list) {
    char name[21];

    SetConsoleTextAttribute(hConsole, 15); cout << "Digite o nome do pet a ser";
    SetConsoleTextAttribute(hConsole, 12); cout <<" removido";
    SetConsoleTextAttribute(hConsole, 15); cout << ": "; cin >> name;
    cin.ignore();

    //pet *target = *list;

    // Target anda at� que ele encontre o nome ou seja NULL
    //while(target && strcmp(target->name, name) != 0) target = target->next;
    pet* listPetsWithName = searchByName(*list, name);
    int count = getCount(listPetsWithName);
    if (count == 0) {
        SetConsoleTextAttribute(hConsole, 12); cout << "Pet " << name << " n�o encontrado!" << endl;
        return;
    }
    else {
        if (count == 1) {
            SetConsoleTextAttribute(hConsole, 10); cout << "Pet " << name << " removido com sucesso!" << endl;
            // Se target � o primeiro da lista 
            if(listPetsWithName == *list) {
                *list = listPetsWithName->next;
                delete listPetsWithName;
                return;
            }
            // Se target est� no meio da lista
            pet *temp = *list;
            while(temp->next != listPetsWithName) temp = temp->next;
            temp->next = listPetsWithName->next;
            delete listPetsWithName;
        } else {
            int codDesejado;
            cout<<"Há mais de 1 pet com o nome "<<name<<endl;
            cout<<"Digite o codigo do pet a ser removido: "; cin>>codDesejado;
            removePetByCode(list, codDesejado, name);
        }
    }
}

void removePetByCode ( pet** list, int code, char name[] ) {
    pet *target = *list;

    // Target anda at� que ele encontre o nome ou seja NULL
    while(target && target->cod == code) target = target->next;

    // Se target ï¿½ NULL, não encontrou o nome
    if(target == NULL) {
        SetConsoleTextAttribute(hConsole, 12); cout << "Pet de codigo " << code << " não encontrado!" << endl;
        return;
    }
    else {
        if (strcmp(target->name, name) != 0)  {
            SetConsoleTextAttribute(hConsole, 12); cout << "Pet de codigo " << code << "e nome " << name <<" não encontrado!" << endl;  
        }      
        else {
            SetConsoleTextAttribute(hConsole, 10); cout << "Pet de codigo " << code << "e nome " << name << " removido com sucesso!" << endl;
            // Se target ï¿½ o primeiro da lista 
            if(target == *list) {
                *list = target->next;
                delete target;
                return;
            }
            // Se target estï¿½ no meio da lista
            pet *temp = *list;
            while(temp->next != target) temp = temp->next;
            temp->next = target->next;
            delete target;
        }
    }
}


void changePet(pet **list) {
    char name[21];

    SetConsoleTextAttribute(hConsole, 15); cout << "Digite o nome do pet a ser ";
    SetConsoleTextAttribute(hConsole, 13); cout << "alterado";
    SetConsoleTextAttribute(hConsole, 15); cout << ": "; cin >> name;
    cin.ignore();

    pet *target = *list;

    // Target anda at� que ele encontre o nome ou seja NULL
    while(target && strcmp(target->name, name) != 0) target = target->next;

    // Se target � NULL, n�o encontrou o nome
    if(target == NULL) {
        SetConsoleTextAttribute(hConsole, 12); cout << "Pet "; 
        SetConsoleTextAttribute(hConsole, 15); cout << name;
        SetConsoleTextAttribute(hConsole, 12); cout << " n�o encontrado!" << endl;
        //return;
    }
    else {
        int tempGender;
        try {
            SetConsoleTextAttribute(hConsole, 1); cout << "\n=-=-=-=-=-=- ";
            SetConsoleTextAttribute(hConsole, 11); cout << "Informa��es do Pet a ser adicionado";
            SetConsoleTextAttribute(hConsole, 1); cout << " -=-=-=-=-=-=\n" << endl;
            SetConsoleTextAttribute(hConsole, 14); cout << "Novo Nome"; 
            SetConsoleTextAttribute(hConsole, 15); cout << ": ";cin >> target->name;
            SetConsoleTextAttribute(hConsole, 14); cout << "Nova Esp�cie"; +
            
            SetConsoleTextAttribute(hConsole, 15); cout << ": "; cin >> target->type;
            SetConsoleTextAttribute(hConsole, 14); cout << "Nova Ra�a "; 
            SetConsoleTextAttribute(hConsole, 15); cout<< ": "; cin >> target->breed;
            do{
                cin.ignore();
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1200, '\n');
                    SetConsoleTextAttribute(hConsole, 12); cout << "Utilize somente n�meros.\n";
                }while(cin.fail());
                SetConsoleTextAttribute(hConsole, 15); cout << "Novo G�nero ";
                SetConsoleTextAttribute(hConsole, 15); cout <<"(";
                SetConsoleTextAttribute(hConsole, 13); cout <<"F�mea = 1"; 
                SetConsoleTextAttribute(hConsole, 15); cout <<"/"; 
                SetConsoleTextAttribute(hConsole, 11); cout << "Macho = 2";
                SetConsoleTextAttribute(hConsole, 15); cout <<"): "; cin >> tempGender;
                }while(tempGender != 1 && tempGender != 2);
            target->gender = selectGender(tempGender - 1);
            do{
			    if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1200, '\n');
                    SetConsoleTextAttribute(hConsole, 12); cout << "Utilize somente n�meros.\n";
                }while(cin.fail());
                SetConsoleTextAttribute(hConsole, 14); cout << "Nova Idade: "; 
                SetConsoleTextAttribute(hConsole, 15); cin >> target->age;
                }while(cin.fail() || target->age < 0 || target->age > 500);
            do{
			    if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1200, '\n');
                    SetConsoleTextAttribute(hConsole, 12); cout << "Utilize somente n�meros.\n";
                }while(cin.fail());
                SetConsoleTextAttribute(hConsole, 14); cout << "Novo Peso: "; 
                SetConsoleTextAttribute(hConsole, 15); cin >> target->weight;
            }while(cin.fail() || target->weight < 0 || target->weight > 500);
        } catch (const char *err) {
            SetConsoleTextAttribute(hConsole, 12); cout<<"\nErro: " << err << endl;
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

int getCountType(pet *list, char type[]) {
    if (list == NULL) return 0;

    int count = 0;

    while(list) {
        if(strcmp(list->type, type) == 0) {
            count++;
        }
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

pet* searchByName(pet *list, char name[]) {
    //char name[21];
    int count = 0;
    /*
    SetConsoleTextAttribute(hConsole, 15); cout << "Digite o ";
    SetConsoleTextAttribute(hConsole, 13); cout << "nome " ; 
    SetConsoleTextAttribute(hConsole, 15); cout << "do pet a ser buscado: ";
    cin >> name;
    cin.ignore();*/
    pet* foundByName = (pet*) malloc(sizeof(pet));
    while(list) {
        if(strcmp(list->name, name) == 0) {
            insertEnd(&foundByName, list->cod, list->name, list->type, list->breed, list->gender, list->age, list->weight);

            /*SetConsoleTextAttribute(hConsole, 10); cout << "Nome";
            SetConsoleTextAttribute(hConsole, 15); cout << ":" << list->name << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Esp�cie";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->type << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Ra�a";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->breed << endl;
            if(list->gender == Female)
            {
                SetConsoleTextAttribute(hConsole, 10); cout << "G�nero";
                SetConsoleTextAttribute(hConsole, 15); cout << ": ";
                SetConsoleTextAttribute(hConsole, 13); cout <<"? F�mea"<< endl;
            }
            else
            { 
                SetConsoleTextAttribute(hConsole, 10); cout << "G�nero: ";
                SetConsoleTextAttribute(hConsole, 11); cout <<"? Macho" << endl;
            }
            SetConsoleTextAttribute(hConsole, 10); cout << "Idade";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->age << " anos" << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Peso";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->weight << "kg" << endl << endl;*/
            count++;
        }
        list = list->next;
    }
    if (count == 0){
        SetConsoleTextAttribute(hConsole, 15); cout << "N�o foi encontrado nenhum pet chamado "; 
        cout << name << endl;
        return NULL;
        }
    SetConsoleTextAttribute(hConsole, 15); cout << "Encontrado "; 
    SetConsoleTextAttribute(hConsole, 10); cout << count;
    if (count > 1){
        SetConsoleTextAttribute(hConsole, 15); cout << " pets chamados ";}
    else if (count == 1){
        SetConsoleTextAttribute(hConsole, 15); cout << " pet chamado ";
        SetConsoleTextAttribute(hConsole, 15); cout<< name << endl;
    }

    return foundByName;
}


void searchByType(pet *list) {
    char type[11];
    int count = 0;

    //SetConsoleTextAttribute(hConsole, 15); cout << "Digite a ";
    //SetConsoleTextAttribute(hConsole, 13); cout << "esp�cie ";
    //SetConsoleTextAttribute(hConsole, 15); cout << "do pet a ser buscada: ";
    //cin >> type;
    //cin.ignore();

    while(list) {
        if(strcmp(list->type, type) == 0) {
            SetConsoleTextAttribute(hConsole, 10); cout << "Nome";
            SetConsoleTextAttribute(hConsole, 15); cout << ":" << list->name << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Esp�cie";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->type << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Ra�a";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->breed << endl;
            if(list->gender == Female)
            {
                SetConsoleTextAttribute(hConsole, 10); cout << "G�nero";
                SetConsoleTextAttribute(hConsole, 15); cout << ": ";
                SetConsoleTextAttribute(hConsole, 13); cout <<"? F�mea"<< endl;
            }
            else
            { 
                SetConsoleTextAttribute(hConsole, 10); cout << "G�nero: ";
                SetConsoleTextAttribute(hConsole, 11); cout <<"? Macho" << endl;
            }
            SetConsoleTextAttribute(hConsole, 10); cout << "Idade";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->age << " anos" << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Peso";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->weight << "kg" << endl << endl;
            count++;
        }
        list = list->next;
    }
    SetConsoleTextAttribute(hConsole, 15); cout << "Encontrado "; 
    SetConsoleTextAttribute(hConsole, 10); cout << count << " "; 
    SetConsoleTextAttribute(hConsole, 15); cout << type << endl;
}


void searchByTypeAndBreed(pet *list) {
    char type[11];
    char breed[21];
    int count = 0;

    SetConsoleTextAttribute(hConsole, 15); cout << "Digite a ";
    SetConsoleTextAttribute(hConsole, 13); cout << "esp�cie ";
    SetConsoleTextAttribute(hConsole, 15); cout << "do pet a ser buscada: ";
    cin >> type;
    cin.ignore();
    //tolower(*type); tinha um warning falando que esse 'statement' n diferença, n altera nada, tem ctz q é esse msm leo? sera q tem outro jeito? 

    SetConsoleTextAttribute(hConsole, 15); cout << "Digite a ";
    SetConsoleTextAttribute(hConsole, 13); cout << "ra�a ";
    SetConsoleTextAttribute(hConsole, 15); cout << "do pet a ser buscada: ";
    cin >> breed;
    cin.ignore();
    //tolower(*breed); tinha um warning falando que esse 'statement' n diferença, n altera nada, tem ctz q é esse msm leo? sera q tem outro jeito? 

    while(list) {
        if(strcmp(list->type, type) == 0 && strcmp(list->breed, breed) == 0) {
            SetConsoleTextAttribute(hConsole, 10); cout << "Nome";
            SetConsoleTextAttribute(hConsole, 15); cout << ":" << list->name << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Esp�cie";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->type << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Ra�a";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->breed << endl;
            if(list->gender == Female)
            {
                SetConsoleTextAttribute(hConsole, 10); cout << "G�nero";
                SetConsoleTextAttribute(hConsole, 15); cout << ": ";
                SetConsoleTextAttribute(hConsole, 13); cout <<"? F�mea"<< endl;
            }
            else
            { 
                SetConsoleTextAttribute(hConsole, 10); cout << "G�nero: ";
                SetConsoleTextAttribute(hConsole, 11); cout <<"? Macho" << endl;
            }
            SetConsoleTextAttribute(hConsole, 10); cout << "Idade";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->age << " anos" << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Peso";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->weight << "kg" << endl << endl;
            count++;
        }
        list = list->next;
    }
    SetConsoleTextAttribute(hConsole, 15); cout << "Encontrado "; 
    SetConsoleTextAttribute(hConsole, 10); cout << count << " "; 
    SetConsoleTextAttribute(hConsole, 15); cout << type << " ";
    SetConsoleTextAttribute(hConsole, 15); cout<< breed;
}

void searchByTypeBreedAndGender(pet *list) {
    char type[11];
    char breed[21];
    int gender;
    int count = 0;

    SetConsoleTextAttribute(hConsole, 15); cout << "Digite a ";
    SetConsoleTextAttribute(hConsole, 13); cout << "esp�cie ";
    SetConsoleTextAttribute(hConsole, 15); cout << "do pet a ser buscada: ";
    cin >> type;
    cin.ignore();

    SetConsoleTextAttribute(hConsole, 15); cout << "Digite a ";
    SetConsoleTextAttribute(hConsole, 13); cout << "ra�a ";
    SetConsoleTextAttribute(hConsole, 15); cout << "do pet a ser buscada: ";
    cin >> breed;
    cin.ignore();

    do {
        SetConsoleTextAttribute(hConsole, 14); cout << "G�nero ";
        SetConsoleTextAttribute(hConsole, 15); cout << "(";
        SetConsoleTextAttribute(hConsole, 13); cout << "F�mea = 1";
        SetConsoleTextAttribute(hConsole, 15); cout << "/";
        SetConsoleTextAttribute(hConsole, 11); cout << "Macho = 2";
        SetConsoleTextAttribute(hConsole, 15); cout << "): "; 
        cin >> gender;
    } while(gender != 1 && gender != 2);

    while(list) {
        if(strcmp(list->type, type) == 0 && strcmp(list->breed, breed) == 0 && list->gender == selectGender(gender - 1)) {
            SetConsoleTextAttribute(hConsole, 10); cout << "Nome";
            SetConsoleTextAttribute(hConsole, 15); cout << ":" << list->name << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Esp�cie";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->type << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Ra�a";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->breed << endl;
            if(list->gender == Female)
            {
                SetConsoleTextAttribute(hConsole, 10); cout << "G�nero";
                SetConsoleTextAttribute(hConsole, 15); cout << ": ";
                SetConsoleTextAttribute(hConsole, 13); cout <<"? F�mea"<< endl;
            }
            else
            { 
                SetConsoleTextAttribute(hConsole, 10); cout << "G�nero: ";
                SetConsoleTextAttribute(hConsole, 11); cout <<"? Macho" << endl;
            }
            SetConsoleTextAttribute(hConsole, 10); cout << "Idade";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->age << " anos" << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Peso";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->weight << "kg" << endl << endl;
            count++;
        }
        list = list->next;
    }
    SetConsoleTextAttribute(hConsole, 15); cout << "Encontrado "; 
    SetConsoleTextAttribute(hConsole, 10); cout << count << " "; 
    SetConsoleTextAttribute(hConsole, 15); cout << type << " ";
    SetConsoleTextAttribute(hConsole, 15); cout<< breed << " ";
    if(selectGender(gender - 1) == Female) {
		SetConsoleTextAttribute(hConsole, 13); cout << "f�mea"<<endl;}
    else {
		SetConsoleTextAttribute(hConsole, 11); cout << "macho"<<endl;}
}


int main() {
    //setlocale(LC_ALL, "Portuguese");  //MOSTRAR ACENTOS NO GERAL
    //SetConsoleOutputCP(65001);  //MOSTRAR ACENTOS NO VSCODE
    //TEM ALGUM BUG COM ISSO AQUI ^^^
    
    /*FILE *petData;
    if((petData = fopen("pet_data.txt", "r+")) == NULL) {
        cout << "Arquivo n�o existente, criando um novo" << endl;
        petData = fopen("pet_data.txt", "w+");
    }*/
    SetConsoleTitle("Pets"); // MUDA O TITULO DA JANELA DO CMD//
    int option;
    char type[11];
    pet *list = NULL;

    do {
        do{
            SetConsoleTextAttribute(hConsole, 14); cout << "=-=-=-=-=-=-=-=--=-=-=-=-=-=";
            SetConsoleTextAttribute(hConsole, 10); cout << " Projeto PETS";
            SetConsoleTextAttribute(hConsole, 14); cout << " =-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
            SetConsoleTextAttribute(hConsole, 15); cout << "\t\t      Bem-vindo � lista de ";
            SetConsoleTextAttribute(hConsole, 11); cout << "Pets";
            SetConsoleTextAttribute(hConsole, 15); cout << "!\n";
            SetConsoleTextAttribute(hConsole, 15); cout << "\t\t   Escolha uma op��o para continuar\n\n";
            SetConsoleTextAttribute(hConsole, 2); cout << "\t\t1 -";
            SetConsoleTextAttribute(hConsole, 15); cout << " Inserir na lista de pets" << endl;
            SetConsoleTextAttribute(hConsole, 2); cout << "\t\t2 -"; 
            SetConsoleTextAttribute(hConsole, 15); cout << " Remover na lista de pets" << endl;
            SetConsoleTextAttribute(hConsole, 2); cout << "\t\t3 -";
            SetConsoleTextAttribute(hConsole, 15); cout << " Alterar informa��o de um pet" << endl;
            SetConsoleTextAttribute(hConsole, 2); cout << "\t\t4 -";
            SetConsoleTextAttribute(hConsole, 15); cout << " Buscar um pet por nome" << endl;
            SetConsoleTextAttribute(hConsole, 2); cout << "\t\t5 -";
            SetConsoleTextAttribute(hConsole, 15); cout << " Filtrar a lista de pets por esp�cie" << endl;
            SetConsoleTextAttribute(hConsole, 2); cout << "\t\t6 -";
            SetConsoleTextAttribute(hConsole, 15); cout << " Filtrar a lista de pets por esp�cie e ra�a" << endl;
            SetConsoleTextAttribute(hConsole, 2); cout << "\t\t7 -";
            SetConsoleTextAttribute(hConsole, 15); cout << " Filtrar a lista de pets por esp�cie, ra�a e sexo" << endl;
            SetConsoleTextAttribute(hConsole, 2); cout << "\t\t8 -";
            SetConsoleTextAttribute(hConsole, 15); cout << " Quantidade de pets na lista" << endl;
            SetConsoleTextAttribute(hConsole, 2); cout << "\t\t9 -";
            SetConsoleTextAttribute(hConsole, 15); cout << " Quantidade de pets de uma esp�cie" << endl;
            SetConsoleTextAttribute(hConsole, 2); cout << "\t\t10 -";
            SetConsoleTextAttribute(hConsole, 15); cout << " Imprimir a lista de pets" << endl;
            SetConsoleTextAttribute(hConsole, 2); cout << "\t\t0 -";
            SetConsoleTextAttribute(hConsole, 15); cout << " Sair do Programa" << endl;
            SetConsoleTextAttribute(hConsole, 14); cout << "=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=";
            SetConsoleTextAttribute(hConsole, 15); cout << "\nDigite a op��o desejada: ";
            SetConsoleTextAttribute(hConsole, 2); cin >> option;
            cin.ignore(10000, '\n');
            if (cin.fail())
            {
                //system("cls");
                SetConsoleTextAttribute(hConsole, 12); cout << "Utilize somente n�meros!\n";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            else if (option < 1 || option > 10){
                //system("cls");
				SetConsoleTextAttribute(hConsole, 12); cout << "Utilize valores entre 0 e 10\n";}
        }while (option != 1 && option != 2 && option != 3 && option != 4 && option != 5 && option != 6 && option != 7 && option != 8 && option != 9 && option != 10);
        switch (option) {
            case 1: 
				createPet(&list);
                break;
            case 2: 
				removePet(&list);
                break;
            case 3: 
				changePet(&list);
                break;
            case 4: 
                char name[21];
                SetConsoleTextAttribute(hConsole, 15); cout << "Digite o ";
                SetConsoleTextAttribute(hConsole, 13); cout << "nome " ; 
                SetConsoleTextAttribute(hConsole, 15); cout << "do pet a ser buscado: ";
                cin >> name;
                cin.ignore();
				printPetRec(searchByName(list, name));
                break;
            case 5: 
				searchByType(list);
                break;
            case 6: 
				searchByTypeAndBreed(list);
                break;
            case 7: 
				searchByTypeBreedAndGender(list);
                break;
            case 8: 
				SetConsoleTextAttribute(hConsole, 15); cout << "\nH� ["; 
                SetConsoleTextAttribute(hConsole, 10); cout << getCount(list); 
                SetConsoleTextAttribute(hConsole, 15); cout << "] pets cadastrados" << endl;
                break;
            case 9: 
                SetConsoleTextAttribute(hConsole, 15); cout << "Digite a ";
                SetConsoleTextAttribute(hConsole, 13); cout << "esp�cie ";
                SetConsoleTextAttribute(hConsole, 15); cout << "do pet a ser buscada: ";
                cin >> type;
                cin.ignore();
				SetConsoleTextAttribute(hConsole, 15); cout << "\nH� ["; 
                SetConsoleTextAttribute(hConsole, 10); searchByType(list); 
                //SetConsoleTextAttribute(hConsole, 15); cout << "] pets cadastrados da esp�cie digitada" << endl;
                break;
            case 10:
            	if(list == NULL)
				{
                    SetConsoleTextAttribute(hConsole, 15); cout << "\nA lista est� ";
                    SetConsoleTextAttribute(hConsole, 12); cout << "vazia.";
				}
				else
					printPetRec(list);
                break;
        }
    }while(option != 0);

    //fclose(petData);

    return 0;
}
