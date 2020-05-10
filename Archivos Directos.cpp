/*
    Tiendita de doña chona pide que realice el siguiente programa

1.	Nuevo Articulo
    Debe de solicitar código del artículo el cual será la lleve y de tipo entero, nombre, precio costo, precio venta, garantía, existencia.

2.	Búsqueda de Articulo
    El sistema debe de solicitar el código,  buscar y mostrar los datos del artículo.

3.	Actualización Articulo
    El usuario debe de ingresar el código y poder modificar los atributos del artículo

4.	Borrar Articulo
    debe solicitar el código  del artículo poder borrarlo, pero antes el sistema le preguntara si está seguro de hacerlo

5.	Compra de articulo
    El sistema le pedirá el código del articulo y mostrara los atributos si no existe el sistema debe de informar,
    si existe el sistema le preguntara el precio costo y la cantidad del articulo y hará el cálculo del total,
    al confirmar la compra la existencia sumara por ejemplo el articulo tornillo tenía 5 de existencia y después
    compraron 10 ahora la existencia será de 15; también actualizara el precio costo al cual se está comprando.

*/

/*
    Extra:

    El analista también le pide que desarrolle una clase donde tendrá como función el cálculo del iva mas el 25% 
    de ganancia sobre el precio costo y el resultado será el precio venta, la debe aplicar cada vez que agreguen 
    el precio costo, el precio venta automáticamente se calculara.
*/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#include <limits> // Limpiar el buffer
#include "iva.h"

using namespace std; // Se utiliza en Dev, en borland no es necesario

void limpiar_buffer(); // Para evitar errores al momento de solicitar datos

/* Declaracion de funciones */
void nuevo();
void buscar();
void actualizar();
void borrar();
void comprar();


struct ARTICULO { // Debe tener id, nombre, precio costo, precio venta, garantía, existencia.
    int id;
    char nombre[100];
    double precio_costo;
    double precio_venta;
    char garantia[2]; // 99 años de garantia - 0 años de garantia (no tiene garantia)
    int existencia;
};

struct ARTICULO articulo;
char nombreArchivo[25] = "articulos_almacenito.dir";
FILE *archivo;
long int dirFisica;
IVA iva;

main() {

    int opcion = 0;
    bool salir = false; // variable para salir del programa
    
    do
    {
        cout << "\r\rAlmacenito Runito"<<endl; // \r (tabular) 
        cout << "\rSeleccione una opcion"<<endl;
        cout << "\n 1. Ingresar un nuevo articulo"<<endl; // \n (salto de linea)
        cout << "2. Buscar un articulo en espeficico"<<endl;
        cout << "3. Actualizar la informacion de un articulo"<<endl;
        cout << "4. Eliminar un articulo"<<endl;
        cout << "5. Compra de articulo"<<endl;
        cout << "6. Salir"<<endl;
        cin>>opcion;
        limpiar_buffer();
        
        system("cls");

        switch(opcion) {
            case 1:
                nuevo();
                break;

            case 2:
                buscar();
                break;

            case 3:
                actualizar();
                break;

            case 4:
                borrar();
                break;

            case 5:
                comprar();
                break;

            case 6:
                cout << "Gracias por usar mi programita :3" << endl;
                salir = true;
                break;

            default:
                cout << "Opcion invalida"<<endl;
        }

        system("pause"); // pausar
        system("cls"); // limpiar pantalla
    } while (salir != true);
}

void nuevo() {
    int noProducto; // Id del producto
    int cant; // Ingrsar x articulos

    cout<<"Cuantos articulos desea ingresar"<<endl;
    cin>>cant;
 
    archivo = fopen(nombreArchivo, "rb+"); // Abrir archivo

    if (archivo == NULL)
    {
        archivo = fopen(nombreArchivo, "w+"); // En cuyo caso el archivo no exista lo voy a crear
    } 

    for(int i=0; i < cant; i++) {
        system("cls");

        bool valido = false;

        cout << "\n \r \r Ingresar un nuevo articulo " << endl;
        cout << "\r Actualmente ha ingresado " << i << " nuevos articulos"<<endl;
        
        do
        {
            system("cls");
            cout << "\n Ingrese el codigo del nuevo articulo: "; cin >> noProducto;
            limpiar_buffer();

            if (noProducto > 0)
            {
                valido = true;
            } else {
                system("cls");
                cout<<"DATO INVALIDO, debe ser unicamente un dato tipo entero y mayor que cero (0)"<<endl;
                system("pause");
            }
        } while (valido != true);

        dirFisica = noProducto*sizeof(articulo);

        fseek(archivo, dirFisica, SEEK_SET);

        fread(&articulo, sizeof(articulo), 1, archivo);

        if (articulo.id == noProducto)
        {
            system("cls");
            cout << "Articulo duplicado !!!" << endl;
            system("pause"); // getch();
                
        } else {
            articulo.id = noProducto;

            cout << "Ingrese el nombre: "; cin >> articulo.nombre; limpiar_buffer();
            cout << "Ingrese la garantia en años (0 si no tiene y como maximo 99): "; cin >> articulo.garantia; limpiar_buffer();
            cout << "Ingrese la existencia del articulo: "; cin >> articulo.existencia; limpiar_buffer();
            cout << "Ingrese el precio costo: "; cin >> articulo.precio_costo; limpiar_buffer();

            articulo.precio_venta = iva.obtener_precio_venta(articulo.precio_costo);

            fseek(archivo, dirFisica, SEEK_SET);
            fwrite(&articulo, sizeof(articulo), 1, archivo);

            system("cls");
            cout << "Articulo registrado exitosamente" << endl;
            system("pause");    
        }            
    } // Fin del for

    fclose(archivo);
} // Fin de la funcion

void buscar() {
    int noProducto; // Id del producto
 
    archivo = fopen(nombreArchivo, "rb"); // Abrir archivo

    if(archivo == NULL) {
        cout << "El archivo no existe"<<endl;
        system("pause");
        return;
    }

    cout << "Ingrese el codigo del articulo: "; cin >> noProducto; limpiar_buffer();

    dirFisica = noProducto*sizeof(articulo);
    fseek(archivo, dirFisica, SEEK_SET);
    fread(&articulo, sizeof(articulo), 1, archivo);

    if (articulo.id == noProducto)
    {
        system("cls");
        cout << "Codigo: " << articulo.id << endl;
        cout << "Nombre: " << articulo.nombre << endl;
        cout << "Existencia: " << articulo.existencia << endl;

        if (articulo.garantia[0] != '0') {
            cout << "Garantia: " << articulo.garantia << " anio(s) " << endl;

        } else {
            cout << "Garantia: El articulo no posee garantia vigente" << endl;
        }

        cout << "Precio costo: " << articulo.precio_costo << endl;
        cout << "Precio venta: " << articulo.precio_venta << endl;

    } else {
        cout << "El articulo no existe"<<endl;
    }

    fclose(archivo);
}

void actualizar() {
    int noProducto; // Id del producto
 
    archivo = fopen(nombreArchivo, "rb+"); // Abrir archivo

    if(archivo == NULL) {
        cout << "El archivo no existe"<<endl;
        system("pause");
        return;
    }

    cout << "Ingrese el codigo del articulo: "; cin >> noProducto; limpiar_buffer();

    dirFisica = noProducto*sizeof(articulo);
    fseek(archivo, dirFisica, SEEK_SET);
    fread(&articulo, sizeof(articulo), 1, archivo);

    if (articulo.id != noProducto)
    {
        cout << "El articulo no existe"<<endl;
    } else {
            cout << "Ingrese el nombre: "; cin >> articulo.nombre; limpiar_buffer();
            cout << "Ingrese la garantia en anios (0 si no tiene y como maximo 99): "; cin >> articulo.garantia; limpiar_buffer();
            cout << "Ingrese la existencia del articulo: "; cin >> articulo.existencia; limpiar_buffer();
            cout << "Ingrese el precio costo: "; cin >> articulo.precio_costo; limpiar_buffer();

            articulo.precio_venta = iva.obtener_precio_venta(articulo.precio_costo);

            fseek(archivo, dirFisica, SEEK_SET);
            fwrite(&articulo, sizeof(articulo), 1, archivo);

            system("cls");
            cout << "Articulo actualizado exitosamente" << endl;
    }

    fclose(archivo);
}

void borrar() {
    int noProducto; // Id del producto
 
    archivo = fopen(nombreArchivo, "rb+"); // Abrir archivo

    if(archivo == NULL) {
        cout << "El archivo no existe"<<endl;
        system("pause");
        return;
    }

    cout << "Ingrese el codigo del articulo: "; cin >> noProducto; limpiar_buffer();

    dirFisica = noProducto*sizeof(articulo);
    fseek(archivo, dirFisica, SEEK_SET);
    fread(&articulo, sizeof(articulo), 1, archivo);

    if (articulo.id != noProducto)
    {
        cout << "El articulo no existe"<<endl;
    } else {
            char opcion;

            do {
	            cout << "¿Esta seguro de borrar el articulo ("<<articulo.nombre<<")? [S/N] -> "; 
	            opcion=toupper(getche()); 
             }while(opcion!='S' && opcion!='N');

             if (opcion == 'S')
             {
                articulo.id = 0;
                strcpy(articulo.nombre, "");
                strcpy(articulo.garantia, "");
                articulo.existencia = 0;
                articulo.precio_costo = 0; 
                articulo.precio_venta = 0;

                fseek(archivo, ftell(archivo) - sizeof(articulo), SEEK_SET);
                fwrite(&articulo, sizeof(articulo), 1, archivo);

                cout << "\nArticulo eliminado exitosamente" << endl;
            }
    }
    fclose(archivo);
}

void comprar() {
    int noProducto; // Id del producto
 
    archivo = fopen(nombreArchivo, "rb+"); // Abrir archivo

    if(archivo == NULL) {
        cout << "El archivo no existe"<<endl;
        system("pause");
        return;
    }

    cout << "Ingrese el codigo del articulo: "; cin >> noProducto; limpiar_buffer();

    dirFisica = noProducto*sizeof(articulo);
    fseek(archivo, dirFisica, SEEK_SET);
    fread(&articulo, sizeof(articulo), 1, archivo);

    if (articulo.id != noProducto)
    {
        cout << "El articulo no existe"<<endl;
    } else {
            system("cls");
            cout << "-------- Atributos --------" << endl;
            cout << "Codigo: " << articulo.id << endl;
            cout << "Nombre: " << articulo.nombre << endl;
            cout << "Existencia: " << articulo.existencia << endl;
            if (articulo.garantia[0] != '0') {
                cout << "Garantia: " << articulo.garantia << " anio(s) " << endl;
            } else {
                cout << "Garantia: El articulo no posee garantia vigente" << endl;
            }
            cout << "Precio costo: " << articulo.precio_costo << endl;
            cout << "Precio venta: " << articulo.precio_venta << endl;
            cout << "-------- Compra nueva --------" << endl;

            cout << "Ingrese el precio costo: "; cin >> articulo.precio_costo; limpiar_buffer();            
            articulo.precio_venta = iva.obtener_precio_venta(articulo.precio_costo);

            int compra;
            cout << "\nIngrese cuantos aticulos se compraron: "; cin >> compra; limpiar_buffer();

            articulo.existencia += compra;

            fseek(archivo, dirFisica, SEEK_SET);
            fwrite(&articulo, sizeof(articulo), 1, archivo);

            system("cls");
            cout << "Articulo actualizado exitosamente" << endl;
    }

    fclose(archivo);
}

void limpiar_buffer(){
    cin.clear(); 
    cin.ignore(numeric_limits<streamsize>::max(),'\n'); 
}
