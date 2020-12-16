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

void Inicio_de_Sesion();
int MenuPrincipalAsistente();
void registrarMascotas(FILE *Mascotas); //Se crea el archivo Mascotas.dat
void mensaje(char const *cadena);
void registrarTurnos(FILE *Turnos); //Se crea el archivo Turnos.dat

main()
{
	setlocale(LC_CTYPE,"spanish");
	system("color 4");
	
	int bandera=0;
	
	Inicio_de_Sesion(); //Inicio del módulo de asistente
	LimpiarPantalla();
	
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
void Inicio_de_Sesion()
{
	char usuario[11],contrasena[32];
	int bandera;
	Datos_Usuarios_Asistentes reg;
	
	FILE *Usuario_Asistente;
	Usuario_Asistente=fopen("Usuarios_Asistentes.dat","rb");
	
	printf("Usuario: "); gets(usuario);
	printf("Contraseña: "); gets(contrasena);
	
	do
	{
		bandera=0;
		rewind(Usuario_Asistente);
		fread(&reg,sizeof(Datos_Usuarios_Asistentes),1,Usuario_Asistente);
		
		while(!feof(Usuario_Asistente) && bandera==0) //compara con usuario del archivo
		{
			if (strcmp(usuario,reg.Usuario)==0)
			{
				bandera=1; //si lo encuentra sale
			}
			if (bandera==0)
			{
				fread(&reg,sizeof(Datos_Usuarios_Asistentes),1,Usuario_Asistente);
			}
		}
		if (bandera==1) //si ingresa bien el usuario
		{
			if (strcmp(contrasena,reg.Contrasena)!=0) //si ingresa mal la contraseña
			{
				bandera=0;
			}
		}
		if (bandera==0)
		{
			printf("Usuario y contraseña incorrectos");
			printf("%s",reg.Usuario);
			printf("%s",reg.Contrasena);
			LimpiarPantalla();
			Inicio_de_Sesion();
		}
	}while(bandera==0); //sale si se ingresa usuario y contraeña correctos
	
	fclose(Usuario_Asistente);
}
int MenuPrincipalAsistente()
{
	int Opcion;
	
	gotoxy(45,2);
	printf("Modulo del Asistente");
	gotoxy(45,3);
	printf("========================="); 
	gotoxy(45,4);
	printf("1.- Registrar Mascota");
	gotoxy(45,5);
	printf("2.- Registrar Turno");
	gotoxy(45,6);
	printf("3.- Listado de Atenciones por Veterinario y Fecha");
	gotoxy(45,8);
	printf("4.- Cerrar la aplicación");
	gotoxy(45,10);
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

