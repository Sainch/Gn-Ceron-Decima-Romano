/*MODULO ASISTENTE

3. Identificación de asistente (Usuario y Contraseña) Recibe Usuarios.dat
4. Registra mascota (Apellido y Nombre, Domicilio, DNI del dueño, Localidad, Fecha de Nacimiento, 
   Edad, Peso, Teléfono) Crea Mascotas.dat
5. Registra turno (Fecha, dd/mm/aaaa) Crea Turnos.dat
9. Obtiene informe de atenciones por veterinario y fecha.

Cada vez que un usuario cree un registro de mascota el mismo se guardará dentro del archivo Mascotas.dat y 
los turnos correspondientes dentro del archivo Turnos.dat.*/

#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<windows.h>
#include"funciones_y_estructuras.h"

struct Fecha
{
	int dia;
	int mes;
	int anio;
};
struct Mascota
{
	char ApellidoyNombre[60];
	char Domicilio[60];
	int DNI_Dueno;
	char Localidad[60];
	Fecha FechadeNacimiento;
	float Peso;
	char Telefono[25];
};
struct Turno
{
	int MatriculaVeterinario;
	Fecha fecha;
	int DNI_Duenio;
	char DetalleAtencion[380];
};

int MenuPrincipalAsistente();
void registrarMascotas(FILE *Mascotas);
void mensaje(char const *cadena);
void registrarTurnos(FILE *Turnos);

main()
{
	setlocale(LC_CTYPE,"spanish");
	system("color 2");
	
	int bandera=0;
	
	FILE *ArchMascotas; //Se abre de lectura para conservar
	ArchMascotas = fopen("Mascotas.dat","w+b"); //los anteriores registros.
	
	if(ArchMascotas == NULL) // Evalua, Si hubo error, muestra mensaje y termina.
	{
		system("CLS");
		printf("Ocurrio un error en la apertura del Archivo....");
		exit(1);
	}

	do
	{
		int Opcion = MenuPrincipalAsistente(); //Llama la función que muestra el menú.
		switch(Opcion)
		{
			case 1:
				
				break;
			case 2:
				LimpiarPantalla();
				registrarMascotas(ArchMascotas);
				break;
			case 3:
				
				break;
			case 4:
				
				break;
			case 5:
				LimpiarPantalla();
				fclose(ArchMascotas);
				printf("Fin del Programa");
				bandera=1;
				break;
			default:
				LimpiarPantalla();
				printf("Ha ingresado una opcion no valida");
		}
	}while(bandera == 0);
}
int MenuPrincipalAsistente()
{
	int Opcion;
	
	gotoxy(45,2);
	printf("Modulo del Asistente");
	gotoxy(45,3);
	printf("========================="); 
	gotoxy(45,4);
	printf("1.- Iniciar Sesión");
	gotoxy(45,5);
	printf("2.- Registrar Mascota");
	gotoxy(45,6);
	printf("3.- Registrar Turno");
	gotoxy(45,7);
	printf("4.- Listado de Atenciones por Veterinario y Fecha");
	gotoxy(45,9);
	printf("5.- Cerrar la aplicación");
	gotoxy(45,11);
	printf("Ingrese una opción: ");
	_flushall();
	scanf("%d",&Opcion);
	return Opcion;
}

void mensaje(char const *cadena)
{
	printf("\n %50s ", cadena);
	system("PAUSE");
} //Fin de la función mensaje()

void registrarMascotas(FILE *Mascotas)
{
	Mascota reg; //crea la variable "reg" de tipo Mascota.
	int nroReg=0; //Variable contador del nro de registros almacenado.
	char continua='N';

	do
	{
		printf("\t** Registro Nro %3.0d **\n", ++nroReg);
		printf("\t****************************\n\n");
		_flushall();
		printf("\n\t Apellido y Nombre: ");
		gets(reg.ApellidoyNombre);
		strupr(reg.ApellidoyNombre);
		printf("\n\t Domicilio: ");
		gets(reg.Domicilio);
		strupr(reg.Domicilio);
		printf("\n\t DNI del Dueño: ");
		scanf("%d",&reg.DNI_Dueno);
		_flushall();
		printf("\n\t Localidad: ");
		gets(reg.Localidad);
		strupr(reg.Localidad);
		printf("\n\t Fecha de Nacimiento: \n");
		printf("\n\t Dia: ");
		scanf("%d",&reg.FechadeNacimiento.dia);
		printf("\n\t Mes: ");
		scanf("%d",&reg.FechadeNacimiento.mes);
		printf("\n\t Anio: ");
		scanf("%d",&reg.FechadeNacimiento.anio);
		printf("\n\t Peso(kg): ");
		scanf("%f",&reg.Peso);
		_flushall();
		printf("\n\t Telefono: ");
		gets(reg.Telefono);
		fwrite(&reg, sizeof(Mascota), 1, Mascotas); //Graba el registro lógico.
		_flushall();
		printf("\n\nContinuar Registrando Mascotas (S/N): ");
		scanf("%c", &continua);
	}while(continua == 'S' || continua == 's');
	system("CLS");
	mensaje("Fin de la carga");
}

