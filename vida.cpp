// Juego de la vida by JoniJnm.es

#include <iostream>
#include <conio2.h>

using namespace std;

#define T_ESC 27
#define T_ARRIBA 72
#define T_ABAJO 80
#define T_IZQUIERDA 75
#define T_DERECHA 77
#define T_INTRO 13
#define T_ESPACIO 32


typedef struct Smundo {
	bool **celda; //el array de posiciones, TRUE viva, FALSE muerta
	unsigned int ancho; //ancho del mundo
	unsigned int alto; //alto del mundo
} Tmundo;


bool avance(Tmundo &mundo, unsigned int i, unsigned int j) {
	// Calcular si una celda vivirá o no en el próximo tiempo de vida

	//posiciones alrededor de la cécula:
	int contador = 0;
	unsigned int a,b,c,d; //arriba, derecha, abajo, izquierda
	unsigned int w=mundo.ancho, h=mundo.alto;

	a = (i == 0) ? h : i-1; //arriba
	b = (j == w-1) ? w : j+1; //derecha
	c = (i == h-1) ? h : i+1; //abajo
	d = (j == 0) ? w : j-1; //izquierda

	if (a<h&&mundo.celda[a][j]) contador++; //arriba
	if (b<w&&mundo.celda[i][b]) contador++; //derecha
	if (c<h&&mundo.celda[c][j]) contador++; //abajo
	if (d<w&&mundo.celda[i][d]) contador++; //izquierda
	if (a<h&&b<w&&mundo.celda[a][b]) contador++; //arriba derecha
	if (c<h&&b<w&&mundo.celda[c][b]) contador++; //abajo derecha
	if (c<h&&d<w&&mundo.celda[c][d]) contador++; //abajo izquierda
	if (a<h&&d<w&&mundo.celda[a][d]) contador++; //arriba izquierda

	//CONDICIÓN 23/3
	return ((!mundo.celda[i][j] && contador == 3) || (mundo.celda[i][j] && (contador == 2 || contador == 3)));
	//(celda muerta y 3 habitantes) o (celda vida y (2 o 3 habitantes))
}

void iniciarMundo(Tmundo &mundo, unsigned int ancho, unsigned int alto) {
	unsigned int i, j;

    if (mundo.celda != NULL) {
		for (unsigned short i=0;i<mundo.alto;i++){
			delete[] mundo.celda[i];
		}
		delete[] mundo.celda;
	}

	mundo.ancho = ancho;
	mundo.alto = alto;

	mundo.celda = new bool *[mundo.alto];
	for (i=0; i<mundo.alto; i++) {
		mundo.celda[i] = new bool[mundo.ancho];
		for (j=0; j<mundo.ancho; j++) {
			mundo.celda[i][j] = 0; //Iniciar celdas a "muertos"
		}
	}
}

void copiarMundo(Tmundo a, Tmundo &b) {
    unsigned int i, j;

    for (i=0;i<a.alto;i<i++) {
        for (j=0;j<a.ancho;j++) {
            b.celda[i][j] = a.celda[i][j];
        }
    }
}

void cargarEjemplo(Tmundo &mundo) {
    iniciarMundo(mundo, 36, 20);

    mundo.celda[4][0] = 1;
    mundo.celda[4][1] = 1;
    mundo.celda[5][0] = 1;
    mundo.celda[5][1] = 1;
    mundo.celda[4][10] = 1;
    mundo.celda[5][10] = 1;
    mundo.celda[6][10] = 1;
    mundo.celda[7][11] = 1;
    mundo.celda[8][12] = 1;
    mundo.celda[8][13] = 1;
    mundo.celda[3][11] = 1;
    mundo.celda[2][12] = 1;
    mundo.celda[2][13] = 1;
    mundo.celda[3][15] = 1;
    mundo.celda[4][16] = 1;
    mundo.celda[5][16] = 1;
    mundo.celda[6][16] = 1;
    mundo.celda[5][17] = 1;
    mundo.celda[7][15] = 1;
    mundo.celda[4][20] = 1;
    mundo.celda[3][20] = 1;
    mundo.celda[2][20] = 1;
    mundo.celda[2][21] = 1;
    mundo.celda[3][21] = 1;
    mundo.celda[4][21] = 1;
    mundo.celda[5][22] = 1;
    mundo.celda[1][22] = 1;
    mundo.celda[0][24] = 1;
    mundo.celda[1][24] = 1;
    mundo.celda[5][24] = 1;
    mundo.celda[6][24] = 1;
    mundo.celda[2][34] = 1;
    mundo.celda[3][34] = 1;
    mundo.celda[2][35] = 1;
    mundo.celda[3][35] = 1;
    mundo.celda[5][14] = 1;
}



void vida(Tmundo &mundo) {
    Tmundo mundoNuevo;
    mundoNuevo.celda=NULL;
    iniciarMundo(mundoNuevo, mundo.ancho, mundo.alto);
    copiarMundo(mundo, mundoNuevo);

    unsigned int i, j;
    for (i=0; i<mundo.alto; i++) {
        cout<<endl;
        if (i == 0) {
            textbackground(WHITE);
            for (j=0; j<mundo.ancho; j++) cout<<" ";
            cout<<"  \n";
        }
        for (j=0; j<mundo.ancho; j++) {
            if (j == 0) {
                textbackground(WHITE);
                cout<<" ";
            }
            mundo.celda[i][j] = avance(mundoNuevo, i, j);
            if (mundo.celda[i][j])
                textbackground(BLUE);
            else
                textbackground(BLACK);
            cout<<" ";
            if (j == mundo.ancho-1) {
                textbackground(WHITE);
                cout<<" ";
            }
        }
        if (i == mundo.alto-1) {
            textbackground(WHITE);
            cout<<"\n  ";
            for (j=0; j<mundo.ancho; j++) cout<<" ";
        }
    }
    textbackground(BLACK);
}

void cambiarDim(Tmundo &mundo) {
    clrscr();
    unsigned int ancho, alto;
	cout<<"Ancho del mundo: ";
	cin>>ancho;
	cout<<"Alto del mundo: ";
	cin>>alto;
	iniciarMundo(mundo, ancho, alto);
}

void mBoton(char *text, bool activado) {
    textbackground(BLACK);
    cout<<"   ";
    if (activado)
        textbackground(RED);
    else
        textbackground(WHITE);
    textcolor(BLUE);
    cout<<text;
    textcolor(WHITE);
    textbackground(BLACK);
}

int guardar_cargar(Tmundo &mundo) {
    char ch;
    char tmp[255];
    unsigned int i, j;

    do {
        clrscr();
        cout<<"Escribe C para cargar y G para guardar: ";
        ch=getch();
    }
    while(ch != 67 && ch != 99 && ch != 71 && ch != 103);

    cout<<ch<<"\nNombre del fichero: ";
    cin>>tmp;
    FILE *f;

    if (ch == 67 || ch == 99) { //cargar
        f = fopen(tmp, "rt");
        if (!f) {
            cout<<"No se ha podido abrir el archivo "<<tmp<<endl;
            system("PAUSE");
            return 1;
        }
        fscanf(f, "Ancho=%d\nAlto=%d\n", &i, &j);
        iniciarMundo(mundo, i, j);
        for (i=0;i<mundo.alto;i++) {
            fscanf(f, "\n");
            for (j=0;j<mundo.ancho;j++) {
                fscanf(f, "%c", &ch);
                mundo.celda[i][j] = (ch == 49);
            }
        }
        fclose(f);
        cout<<"Fichero "<<tmp<<" cargado\n\n";
    }
    else if (ch == 71 || ch == 103) { //guardar
        f = fopen(tmp, "wt");
        if (!f) {
            cout<<"No se ha podido crear el archivo "<<tmp<<endl;
            system("PAUSE");
            return 1;
        }
        fprintf(f, "Ancho=%d\nAlto=%d\n", mundo.ancho, mundo.alto);
        for (i=0;i<mundo.alto;i++) {
            fprintf(f, "\n");
            for (j=0;j<mundo.ancho;j++) {
                fprintf(f, "%d", (int)mundo.celda[i][j]);
            }
        }
        fclose(f);
        cout<<"Fichero "<<tmp<<" guardado\n\n";
    }

    system("PAUSE");
    return 0;
}

void cuadricula(Tmundo &mundo, unsigned int &x, unsigned int &y, int ch) {
    int boton=0;

    if (x > mundo.ancho) {
        if (x == mundo.ancho+1) { //boton ejemplo
            if (ch == T_INTRO) { //Intro: cargarEjemplo y ponerlo en el boton comenzar
                cargarEjemplo(mundo);
                x = mundo.ancho+4;
                y = mundo.alto-1;
                boton = 4;
            }
            else if (ch == T_IZQUIERDA) //Izquierda: ponerlo en la cuadrícula
                x = mundo.ancho-1;
            else if (ch == T_ABAJO) { //Abajo: ponerlo en el boton guardar
                x = mundo.ancho+2;
                y = 2;
                boton = 2;
            }
            else if (ch == T_ARRIBA) { //Arriba: ponerlo en el boton comenzar
                x = mundo.ancho+4;
                y = mundo.alto-1;
                boton = 4;
            }
            else
                boton = 1;
        }
        else if (x == mundo.ancho+2) { //boton guardar/cargar
            if (ch == T_INTRO) { //Intro: mostrar guardar_cargar, ponerlo en el boton comenzar
                guardar_cargar(mundo);
                x=mundo.ancho+4;
                y=mundo.alto-1;
                boton=4;
            }
            else if (ch == T_IZQUIERDA) //Izquierda, ponerlo en la cuadricula
                x = mundo.ancho-1;
            else if (ch == T_ARRIBA) { //Arriba: ponerlo en el boton ejemplo
                x = mundo.ancho+1;
                y = 0;
                boton = 1;
            }
            else if (ch == T_ABAJO) { //Abajo: ponerlo en el boton cambiarDim
                x = mundo.ancho+3;
                y = 3;
                boton = 3;
            }
            else
                boton = 2;
        }
        else if (x == mundo.ancho+3) { //boton cambiarDim
            if (ch == T_INTRO) { //INTRO: mostrar pantalla cambiar dim y dejar el boton en el boton cambiarDim
                cambiarDim(mundo);
                x=mundo.ancho+3;
                y=4;
                boton=3;
            }
            else if (ch == T_IZQUIERDA) //Izquierda: Moverlo a la cuadrícula
                x = mundo.ancho-1;
            else if (ch == T_ARRIBA) { //Arriba: Poner boton en el boton guardar
                x = mundo.ancho+2;
                y = 2;
                boton = 2;
            }
            else if (ch == T_ABAJO) { //Abajo: Ponerlo en el boton comenzar
                x = mundo.ancho+4;
                y = mundo.alto-1;
                boton = 4;
            }
            else
                boton = 3;
        }
        else if (x == mundo.ancho+4) { //boton comenzar
            if (ch == T_INTRO) //Intro: Comenzar! (mundo.alto+1)
                y = mundo.alto+1;
            else if (ch == T_IZQUIERDA) //Izquierda: moverlo a la cuadrícula
                x = mundo.ancho-1;
            else if (ch == T_ABAJO) { //ABAJO: Moverlo al botón ejemplo
                x = mundo.ancho+1;
                y = 0;
                boton=1;
            }
            else if (ch == T_ARRIBA) { //Arriba: Moverlo al botón cambiarDim
                x = mundo.ancho+3;
                y = 4;
                boton = 3;
            }
            else
                boton = 4;
        }
    }
    else {
        if(x==mundo.ancho-1 && y == 0 && ch == T_DERECHA) {
            boton=1;
            x=mundo.ancho+1;
        }
        else if(x==mundo.ancho-1 && y == 2 && ch == T_DERECHA) {
            boton=2;
            x=mundo.ancho+2;
        }
        else if(x==mundo.ancho-1 && y == 4 && ch == T_DERECHA) {
            boton=3;
            x=mundo.ancho+3;
        }
        else if (x == mundo.ancho-1 && y == mundo.alto-1 && ch == T_DERECHA) {
            boton=4;
            x=mundo.ancho+4;
        }

        else if (ch == T_ARRIBA)
            y = (y == 0) ? mundo.alto-1 : y-1;
        else if (ch == T_DERECHA)
            x = (x == mundo.ancho-1) ? 0 : x+1;
        else if (ch == T_ABAJO)
            y = (y == mundo.alto-1) ? 0 : y+1;
        else if (ch == T_IZQUIERDA)
            x = (x == 0) ? mundo.ancho-1 : x-1;
        else if (ch == T_INTRO)
            mundo.celda[y][x] = !mundo.celda[y][x];
    }

    clrscr();

    unsigned int i, j;
    for (i=0; i<mundo.alto; i++) {
        cout<<endl;
        if (i == 0) {
            textbackground(WHITE);
            for (j=0; j<mundo.ancho; j++) cout<<" ";
            cout<<"  \n";
        }
        for (j=0; j<mundo.ancho; j++) {
            if (j == 0) {
                textbackground(WHITE);
                cout<<" ";
            }
            if (x == j && y == i)
                textbackground(RED);
            else if (mundo.celda[i][j])
                textbackground(BLUE);
            else
                textbackground(BLACK);
            cout<<" ";
            if (j == mundo.ancho-1) {
                textbackground(WHITE);
                cout<<" ";
            }
            if (i == 0 && j == mundo.ancho-1)
                mBoton("Cargar ejemplo", boton==1);
            else if (i == 2 && j == mundo.ancho-1)
                mBoton("Guardar/Cargar", boton==2);
            else if (i == 4 && j == mundo.ancho-1)
                mBoton("Cambiar Dimensiones", boton==3);
        }
        if (i == mundo.alto-1) {
            textbackground(WHITE);
            cout<<"\n  ";
            for (j=0; j<mundo.ancho; j++) cout<<" ";
        }
    }
    mBoton("COMENZAR", boton==4);

    cout<<endl<<endl<<x<<", "<<y;
}

void rellenar(Tmundo &mundo) {
	unsigned int x=0, y=0;
	char ch;

	cuadricula(mundo, x, y, -1);

	do {
		ch=getch();
		cuadricula(mundo, x, y, ch);
	}
	while(y != mundo.alto+1);
}

void comenzar(Tmundo &mundo) {
	char ch;
    unsigned int i=0;

    clrscr();
    do {
		vida(mundo);
		cout<<endl<<endl<<"Paso "<<i<<" | Intro: continuar, ESC: salir, Espacio: editar";
		ch=getch();
		clrscr();
		i++;
		if (ch == T_ESPACIO) {
            rellenar(mundo);
			clrscr();
            i=0;
		}
    }
    while (ch !=  T_ESC);
}

int main () {
	Tmundo mundo;
	mundo.celda=NULL;

	iniciarMundo(mundo, 10, 10);
	rellenar(mundo);
    comenzar(mundo);

	return 0;
}
