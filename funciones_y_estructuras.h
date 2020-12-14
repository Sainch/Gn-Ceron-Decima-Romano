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

struct Datos_Veterianrios
{
	char ApellidoNombre[60],Usuario[10],Contrasena[32],telefono[25];
	int DNI,matricula;
};

struct Datos_Usuarios_Asistentes
{
	char Usuario[10],Contrasena[32],ApellidoNombre[60];
};

