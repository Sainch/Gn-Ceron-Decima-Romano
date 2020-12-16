void gotoxy(int x,int y)
{  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
}

void LimpiarPantalla()
{
	//printf("\n\n\t\t");
	system("pause>0");
	system("cls");
}

typedef char palabra[50];

struct Datos_Veterinarios
{
	char ApellidoNombre[60],Usuario[11],Contrasena[33],telefono[25];
	int DNI,matricula;
};

struct Datos_Usuarios_Asistentes
{
	char Usuario[11],Contrasena[32],ApellidoNombre[60];
};

