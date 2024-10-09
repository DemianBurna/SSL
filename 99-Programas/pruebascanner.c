#include <stdio.h>
#include <ctype.h>

typedef enum {INICIO, FIN, LEER, ESCRIBIR, ID, CONSTANTE, PARENIZQUIERDO,
 PARENDERECHO, PUNTOYCOMA, COMA, ASIGNACION, SUMA, RESTA, FDT} TOKEN;

const char *Buffer(void);

TOKEN EsReservada(void);

TOKEN Scanner(void);


#define TAMANIO_BUFFER 20

typedef int ESTADO;

char _buffer[TAMANIO_BUFFER+1];
int  _pos = 0;

void LimpiarBuffer(void) {
    for (int i = 0; i < TAMANIO_BUFFER + 1 ; i++)
    {
        _buffer[i] = '\0';
    }
    
}

void AgregarCaracter(int caracter) {
    _buffer[_pos++] = caracter;
}

const char *Buffer(void) {
    _buffer[_pos] = '\0';
    return _buffer;
}

TOKEN EsReservada(void) {
    return ID;
}

int ObtenerColumna(int simbolo) {
    if (isalpha(simbolo)) { 
        return 0;
    } else if (isdigit(simbolo)) {
        return 1;
    } else if (simbolo == '+') {
        return 2;
    } else if (simbolo == '-') {
        return 3;
    } else if (simbolo == '(') {
        return 4;
    } else if (simbolo == ')') {
        return 5;
    } else if (simbolo == ',') {
        return 6;
    } else if (simbolo == ';') {
        return 7;
    } else if (simbolo == ':') {
        return 8;
    } else if (simbolo == '=') {
        return 9;
    } else if (simbolo == -1) {
        return 10;
    } else if (isspace(simbolo)) {
        return 11;
    }    
    return 12;
}


ESTADO Transicion(ESTADO estado, int simbolo) {
    static ESTADO TT[15][13] = {  
        
        // cambio el numero de estados a 15 (filas, originalmente estaba en 12) como se menciona en la descripcion de la TT del AFD que compone el scanner en la seccion 3.2.4.1 de Muchnik

        // los -1 simbolizan los espacios en blanco de TT, si no se rellenan con un entero da error
 
                 /* L |  D |  + |  - |  ( |  ) |  , |   ; |   : |   = | fdt | sp | otro */
        /*  0- */{  1 ,  3 ,  5 ,  6 ,  7 ,  8 ,  9 ,  10 ,  11 ,  14 ,  13 ,  0 , 99  },
        /*  1  */{  1 ,  1 ,  2 ,  2 ,  2 ,  2 ,  2 ,   2 ,   2 ,   2 ,   2 ,  2 ,  2  },
        /*  2+ */{ 99 , 99 , 99 , 99 , 99 , 99 , 99 ,  99 ,  99 ,  99 ,  99 ,  2 , 99  },
        /*  3  */{  4 ,  3 ,  4 ,  4 ,  4 ,  4 ,  4 ,   4 ,   4 ,   4 ,   4 ,  4 ,  4  },
        /*  4+ */{ -1 , -1 , -1 , -1 , -1 , -1 , -1 ,  -1 ,  -1 ,  -1 ,  -1 , -1 , -1  },
        /*  5+ */{ -1 , -1 , -1 , -1 , -1 , -1 , -1 ,  -1 ,  -1 ,  -1 ,  -1 , -1 , -1  },
        /*  6+ */{ -1 , -1 , -1 , -1 , -1 , -1 , -1 ,  -1 ,  -1 ,  -1 ,  -1 , -1 , -1  },
        /*  7+ */{ -1 , -1 , -1 , -1 , -1 , -1 , -1 ,  -1 ,  -1 ,  -1 ,  -1 , -1 , -1  },
        /*  8+ */{ -1 , -1 , -1 , -1 , -1 , -1 , -1 ,  -1 ,  -1 ,  -1 ,  -1 , -1 , -1  },
        /*  9+ */{ -1 , -1 , -1 , -1 , -1 , -1 , -1 ,  -1 ,  -1 ,  -1 ,  -1 , -1 , -1  },
        /* 10+ */{ -1 , -1 , -1 , -1 , -1 , -1 , -1 ,  -1 ,  -1 ,  -1 ,  -1 , -1 , -1  },
        /* 11  */{ -1 , -1 , -1 , -1 , -1 , -1 , -1 ,  -1 ,  -1 ,  12 ,  -1 , -1 , -1  },
        /* 12+ */{ -1 , -1 , -1 , -1 , -1 , -1 , -1 ,  -1 ,  -1 ,  -1 ,  -1 , -1 , -1  },
        /* 13+ */{ -1 , -1 , -1 , -1 , -1 , -1 , -1 ,  -1 ,  -1 ,  -1 ,  -1 , -1 , -1  },
        /* 14  */{ -1 , -1 , -1 , -1 , -1 , -1 , -1 ,  -1 ,  -1 ,  -1 ,  -1 , -1 , -1  },


        /* ¿y la tabla? ¿dónde está la tabla? */
    };
    int columna = ObtenerColumna(simbolo);
    return TT[estado][columna];
}

TOKEN Scanner(void) {
    TOKEN token = INICIO;
    int c;
    _pos = 0; // estaba mal declarada la variable, al declararla devuelta dentro de Scanner no afectaba a la variable externa que usaba la funcion Buffer y LimpiarBuffer, por lo que se rompia
    ESTADO estado = 0;
    LimpiarBuffer();
    while (c=getchar()) {
        estado = Transicion(estado, c);
        switch (estado) {
            case 1:
            case 3:
                AgregarCaracter(c);
                break;
            case 2:
                ungetc(c, stdin);
                return ID; 
            case 4:
                ungetc(c, stdin);
                return CONSTANTE; 
            case 5:
                AgregarCaracter(c);
                return SUMA; 
            case 6:
                AgregarCaracter(c);
                return RESTA; 
            case 7:
                AgregarCaracter(c);
                return PARENIZQUIERDO; 
            case 8:
                AgregarCaracter(c);
                return PARENDERECHO;  
            case 9:
                AgregarCaracter(c);
                return COMA;  
            case 10:
                AgregarCaracter(c);
                return PUNTOYCOMA;  
            case 11:
                AgregarCaracter(c);
                break;
            case 12:
                AgregarCaracter(c);
                return ASIGNACION; 
            case 99:
                return INICIO;
                /* situacion rara. ¿cómo la podemos resolver? */
            case 13:
                return FDT; 

        }
    }
};

int main(void) {
    const char *hola[] = {"INICIO", "FIN", "LEER", "ESCRIBIR", "ID", "CONSTANTE", "PARENIZQUIERDO",
 "PARENDERECHO", "PUNTOYCOMA", "COMA", "ASIGNACION", "SUMA", "RESTA", "FDT"};
    
    TOKEN t;
    while ((t = Scanner()) != 13) {
        if (t == 0){
            printf("\nSe detecto un error lexico\n");
        }
        else{
        printf("\t %s -> %s \n", hola[t], Buffer());
        }
    }
}

