/*El siguiente código resuelve el problema criptoartmetico
		    T W O
		  + T W O
		  ----------
		  F O U R

	Donde se consideran las restriccones
		O + O = R + 10A
		A + W + W = U + 10B
		B + T + T = O + 10C
		C = F
		F != 0
		
		Con O,R,W,U,T,F numeros enteros de 0-9 todos diferentes y A,B,C constantes de0-9
*/
#include <iostream>
#include <string.h>

using namespace std;


/*Funcion que verifica la restriccion de que los elementos sean distintos
	Compara que los elementos de un arreglo int sean distintos
	true: Son distintos
	false: No son distintos*/
bool sonDiferentes(int valores[], int tamanio){	
	int valAux=-1;
	for(int i=0; i<tamanio;i++){
		valAux=valores[i];
		for(int j=i+1; j<tamanio;j++){
			if(valores[j]!=-1){
				if(valAux==valores[j]){
					return false;			
				}
			}
		}
	}
	return true;							
};

/*Funcion que verifica la restriccion general: (C1 + V1 + V1 = V2 + 10C2) 
	true: Se cumple
	false: No se cumple*/
bool cumpRestr(int c1, int val1, int val2, int c2){		
    return ((c1+val1+val1)==(val2+10*c2));				
};

/*Funcion principal:
Irá asignando valores a las constantes y variables verificando se cumplen las restricciones, en caso de cumplir
llamará nuevamente a esta funcion para buscar el valor para las variables restantes. En caso contrario regresará 
a las variables anteriores y buscará nuevos valores que satisfagan las restricciones para poder avanzar.Es un metodo repetitivo.
	Tomando la siguiente nomenclatura:  (C1 + V1 + V1 = V2 + 10C2) 
	cn1: Guarda el valor C1;
	var: Arreglo que contiene el valor de las variables
	varAux: Arreglo que contiene el valor de las constantes
	tamanioVar: Tamaño del arreglo de variables
	tamanioVarAux: Tamaño del arreglo de constantes
	posVar: Guarda la posicion actual del arreglo de variables (permite avanzar, retroceder, asignar y reasiganar un valor en dicha posicion) 
	posVarAux: Guarda la posicion actual del arreglo de constantes (permite avanzar, retroceder, asignar y reasiganar un valor en dicha posicion) 
	v1anterior: Guarda el valor V1 asignado en el anterior movimiento
	v2anterior: Guarda el valor V2 asignado en el anterior movimiento
	c2anterior: Guarda el valor C2 asignado en el anterior movimiento
	*/
bool backTraking(int cn1, int var[], int varAux[], int tamanioVar, int tamanioVarAux, int posVar, int posVarAux, int v1anterior, int v2anterior, int c2anterior){
	
	int c1=cn1, v1=-1, v2=-1, c2=-1;	//Variables usadas para representar: (C1 + V1 + V1 = V2 + 10C2) , inicializadas en -1 porque no tienen valor asignado
	
    for(int i=v1anterior;i>-1;i--){ 	//Iteracion para asignar un valor a V1 que inicia en el ultimo caso intentado. Al inicio irá: V1=9, luego V1=8, luego V1=7 ...
		v1=i;
        for(int j=v2anterior; j>-1; j--){	//Iteracion para asignar un valor a V2 que inicia en el ultimo caso intentado.  Al inicio irá: V2=9, luego V2=8, luego V2=7 ...
           v2=j;
            for(int k=9; k>-1; k--){			//Iteracion para asignar un valor a C2 que omite en el ultimo caso intentado. Al inicio irá: C2=9, luego C2=8, luego C2=7 ...
            	if(k==c2anterior &&v1==v1anterior&&v2==v2anterior){		//Si está en un caso ya verificado lo omite
				}else{													//Caso contrario asigna un nuevo valor a C2 
	            	c2=k;
	            	bool rest=false;									//Almacena el valor de verdad de la funcion cumpRestr();
	            	if(posVar==4){
	            		rest=((cumpRestr(c1,v1, var[0],c2))&&(c2!=0)); //Verifica la ultima restriccion de: B+T+T=O+10C  y como F=C implica que C != 0
					}else{
						rest=cumpRestr(c1,v1, v2,c2);
					}
	            	if(rest){											//Recordando el contexto:  (C1 + V1 + V1 = V2 + 10C2)
	            		if(posVar==4){									//Cuando B+T+T=O+10C se cumple, F toma el valor de C
	            			v2=c2; 		//F=C
						}
						var[posVar]=v1;									//Guarda los posibles valores en el arreglo de valores para las variables
						var[posVar+1]=v2;
	                    varAux[posVarAux]=c2;							//Guarda los posibles valores en el arreglo de valores para las constantes
	                    //printValor(var,tamanioVar);
	            		if(sonDiferentes(var, tamanioVar)){				//Verifica que los valores hasta el momento son distintos.
							var[posVar++]=v1;	//Dado que son valores respuesta los almacena e incrementa la posicion (que permitirá trabajar sobre el arreglo de valores de las variables)
							var[posVar++]=v2;
	                    	varAux[posVarAux++]=c2; //Dado que son valores respuesta los almacena e incrementa la posicion (que permitirá trabajar sobre el arreglo de valores de las constantes)
	                    	if(posVar>5){		//Significa que cada variable ya tiene un valor distinto que solucionan el problema y cumple que F!=0
	                    		return true;	
							}else{		//Signfica que aun falta hallar el valor de las variables siguintes, por lo que vuelve a llamar a la funcion
	                    		return backTraking(c2,var, varAux, tamanioVar, tamanioVarAux, posVar, posVarAux,9,9,9);	//La constante C2 hallada será la C1 para el nuevo caso  (C1 + V1 + V1 = V2 + 10C2)
	           				}	//Al tratarse de un nuevo caso, se inicializa las v1anterior=v2anterior=c2anterior=9 para que pruebe con todos los casos posibles
	                    }
	                }   
	            }
        	}
        }
    }
    //En caso de recorrer todos los casos posibles se tiene:
    if(v1==0 && posVar==0){	//Si V1=0 y posVar==0 significa que se han buscado todas las alternativas existentes y no se han logrado asignar valores a las variables
       	return false; //Por lo que se interpreta que el problema no tiene solucion
	}else{					//Se regresa al nivel anterior en busca de otro posible solucion
		var[posVar]=-1;		//Se borra el valor asignado en este nivel al arreglo de valores de las variables
		var[posVar+1]=-1;
		varAux[posVarAux]=-1;	//Se borra el valor asignado en este nivel al arreglo de valores de las constantes
		v1anterior=var[posVar-2];	//V1anterior toma el valor asigando en el arreglo de valores dos posiciones atrás (toma el valor que tenia V1 en el nivel anterior)
        v2anterior=var[posVar-1];	//V2anterior toma el valor asigando en el arreglo de valores una posicion atrás (toma el valor que tenia V2 en el nivel anterior)
    	c2anterior=varAux[posVarAux-1];	//C2anterior toma el valor asigando en el arreglo de valores de constantes (toma el valor que tenia C2 en el nivel anterior)
    	posVar=posVar-2;			//Regreso las posiciones que se avanzó en el arreglo de valores de las variables
		posVarAux--;				//Regreso las posiciones que se avanzó en el arreglo de valores de las variables
		if(posVar==0){
			c1=0;				//Significa que se encuentra en el primer caso, O + O = R + 10A lo que equivale a (C1 + V1 + V1 = V2 + 10C2) con C1=0
		}
    	backTraking(c1,var, varAux, tamanioVar, tamanioVarAux, posVar, posVarAux,v1anterior,v2anterior,c2anterior);	//Regreso al nivel anteriro y sigo buscando soluciones						
	}
};

/*Funcion que imprime los valores de cada variable y constante para generar la solucion*/
void printSolucion(char varChar[], char varAuxChar[], int var[], int varAux[],int tamanioVar, int tamanioVarAux){
	cout<<"Se encontro una solucion\nLos valores deben ser: \n\n";
	for(int i=0; i<tamanioVar;i++){
		cout<<varChar[i]<<" = "<<var[i]<<endl;
	}
	for(int i=0; i<tamanioVarAux;i++){
		cout<<varAuxChar[i]<<" = "<<varAux[i]<<endl;
	}
};

/* Busca la solucion y recibe como parametros:
	varChar: Arreglo que contiene las variables
	varAuxChar: Arreglo que contiene las constantes
	var: Arreglo que contiene el valor de las variables
	varAux: Arreglo que contiene el valor de las constantes
	tamanioVar: Tamaño del arreglo de variables
	tamanioVarAux: Tamaño del arreglo de constantes
	posVar: Guarda la posicion actual del arreglo de variables (permite avanzar, retroceder, asignar y reasiganar un valor en dicha posicion) 
	posVarAux: Guarda la posicion actual del arreglo de constantes (permite avanzar, retroceder, asignar y reasiganar un valor en dicha posicion) 
*/
void resolverCriptoaritmetica(char varChar[], char varAuxChar[], int var[], int varAux[], int tamanioVar, int tamanioVarAux, int posVar, int posVarAux){
    bool existeSolucion=backTraking(0, var,varAux,tamanioVar,tamanioVarAux,posVar,posVarAux,9,9,9);
    if(existeSolucion){
        printSolucion(varChar,varAuxChar,var,varAux,tamanioVar, tamanioVarAux);
    }else{
        cout<<"No se ha encontrado una solucion para el problema descrito"<<endl;
    }
};

int main(){
    char var[6]={'O','R','W','U','T','F'}; 	//Arreglo que almacena las variables
    int valVar[6]={-1,-1,-1,-1,-1,-1};		//Arreglo para almacenar el valor de las variables: -1 significa que aun no se le ha asigando valor
    char varAux[3]={'A','B','C'};			//Arreglo que almacena las constantes
    int valVarAux[3]={-1,-1,-1};			//Arreglo que almacena el valor de las cosntantes: -1 significa que aun no se le ha asigando valor
    int posVar=0, posVarAux=0;		//Inicializamos la posicion para recorrer los arreglos
    int tamanioVar=(sizeof var/sizeof var[0]);			//Almacena el tamaño del arreglo de variables
	int tamanioVarAux=(sizeof varAux/sizeof varAux[0]);	//Almacena el tamaño del arreglo de constantes	
	cout<<"Solucion al problema criptoaritmetico\n\n"<<
		"\t    T W O\n"<<
		"\t  + T W O\n"<<
		"\t    -----\n"<<
		"\t  F O U R\n\n"<<
		"Donde se consideran las restriccones:\n"<<
		"O + O = R + 10A\n"<<
		"A + W + W = U + 10B\n"<<
		"B + T + T = O + 10C\n"<<
		"C = F\n"<<
		"F != 0\n\n";			
	resolverCriptoaritmetica(var, varAux,valVar, valVarAux,tamanioVar, tamanioVarAux, posVar, posVarAux);	//Funcion que busca una solucion
    return 0;
};


