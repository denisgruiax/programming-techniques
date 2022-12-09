/*
    Aplicația 4.6: Un fișier conține pe fiecare linie un produs dat prin numele său
    (un cuvânt) și preț (număr real), separate prin spațiu. Să se încarce fișierul în memorie și să se implementeze într-o
    buclă infinită un meniu cu următoarele opțiuni:
    Caută un produs după nume și, dacă e găsit, îi afișează prețul
    Afișează toate produsele
    Adaugă un nou produs
    Șterge un produs, după numele său
    Salvează în fișierul originar baza de date din memorie
    Ieșire din program
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[30];
    double price;
} Product;

double searchProductByName(Product *products, char *name, unsigned length);
void displayAllProducts(Product *products, unsigned length);
Product *addProduct(Product *products, Product product, unsigned *length);
int deleteProductByName(Product *products, char *name, unsigned *length);
int saveDataBase(Product *products, unsigned length);

int main()
{
    Product *products = NULL, product = {0};
    unsigned length = 1;
    char option = 0, name[30] = " ";
    FILE *file;

    if (!(file = fopen("app6.txt", "rt")))
    {
        fprintf(stderr, "Error at opening the file.");

        exit(EXIT_FAILURE);
    }

    products = (Product *)malloc(sizeof(Product) * length);

    while (fscanf(file, "%s %lf", (products + (length - 1))->name, &((products + (length - 1))->price)) == 2)
    {
        length++;
        products = (Product *)realloc(products, sizeof(Product) * length);
    }

    puts("MENU");
    puts("1 - Search product and display his price. (if the price is -1 the product does not exist)");
    puts("2 - Display all the products.");
    puts("3 - Add product.");
    puts("4 - Delete product by name.");
    puts("5 - Save the data base.");

    do
    {
        printf("Insert at this line the option: ");
        scanf(" %c", &option);

        switch (option)
        {
        case '1':
            printf("Insert name of the product: ");
            scanf("%s", name);

            printf("price = %lf\n", searchProductByName(products, name, length));

            break;

        case '2':
            displayAllProducts(products, length);

            break;

        case '3':
            puts("Insert the name and after that the price.");
            scanf("%s", product.name);
            scanf("%lf", &product.price);

            products = addProduct(products, product, &length);

            break;

        case '4':

            puts("Insert the name of product to delete.");
            scanf("%s", name);

            deleteProductByName(products, name, &length);

            break;

        case '5':

            puts("Save data base.");
            saveDataBase(products, length);

            break;

        case '6':

            printf("Closing program\n");

            break;

        default:

            break;
        }

        puts("");

    } while (option != 0);

    fclose(file);

    return 0;
}

double searchProductByName(Product *products, char *name, unsigned length)
{
    for (size_t i = 0; i < (length - 1); i++)
        if (!strcmp(name, (products + i)->name))
            return (products + i)->price;

    return -1;
}

void displayAllProducts(Product *products, unsigned length)
{
    for (size_t i = 0; i < (length - 1); i++)
        printf("%s %lf\n", (products + i)->name, (products + i)->price);
}

Product *addProduct(Product *products, Product product, unsigned *length)
{
    products = (Product *)realloc(products, sizeof(Product) * *length);

    strcpy((products + (*length - 1))->name, product.name);
    (products + (*length - 1))->price = product.price;

    (*length)++;

    return products;
}

int deleteProductByName(Product *products, char *name, unsigned *length)
{
    for (size_t i = 0; i < *length - 1; i++)
    {
        if (!strcmp(((products + i)->name), name))
        {
            (*length)--;

            for (size_t j = i; j < *length - 1; j++)
                *(products + j) = *(products + j + 1);

            if (products)
                return 1;
        }
    }

    return 0;
}

int saveDataBase(Product *products, unsigned length)
{
    FILE *file;

    if (!(file = fopen("app6_out.txt", "w")))
    {
        fprintf(stderr, "Error on opening file \"app6_out.txt\" ");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < length - 1; i++)
    {
        printf("%s %lf\n", (products + i)->name, (products + i)->price);
        fprintf(file, "%s %lf\n", (products + i)->name, (products + i)->price);
    }  

    fclose(file);

    return 1;
}