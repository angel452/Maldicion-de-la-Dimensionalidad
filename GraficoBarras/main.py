from matplotlib import pyplot
from numpy import loadtxt
from math import log10
    
########### LOAD TXT ##############
lines = loadtxt("../build/prueba.txt")
lines.sort()

print("###### DATOS ADICIONALES ###########")

n = len(lines)
print("El total de datos es: ", len(lines))

minDato = lines[0]
print("El menor dato es: ", minDato)

maxDato = lines[n-1]
print("El mayor dato es: ", maxDato)

rango = maxDato - minDato
print("El rango es: ", rango)

nClases = round(1+3.3*log10(n))
print("El numero de clases es: ", nClases)

anchoClase = rango/nClases;
print("El ancho de clase es: ", anchoClase)

########## Limites inferiores ####################
a = []
a.append(minDato)
for i in range(0,nClases-1):
    aux = a[i]
    a.append(aux + anchoClase)

print("--- a ---")
for i in range(0,nClases):
    print(a[i], " ")

############ Limites Superiores #######################
b = []
b.append(minDato + anchoClase)
for i in range(0, nClases-1):
    aux = b[i]
    b.append(aux + anchoClase)
b[nClases-1] = b[nClases-1]+0.01

print("--- b ---")
for i in range(0,nClases):
    print(b[i], " ")

################ Frecuencias #######################
fi = []
for i in range(0, nClases):
    contador = 0
    for j in range (0, n):
        if( lines[j] >= a[i] and lines[j] < b[i] ):
            contador = contador + 1
    fi.append(contador)  

print("--- Fi ---")
for i in fi:
    print(i)

############## Marca de clase #######################
xi = []
for i in range(0, nClases):
    aux = (a[i] + b[i])/2 #str()?
    #xi.append(aux)
    xi.append(str(round(aux, 2)))

print("--- XI ---")
for i in xi:
    print(i)


############### Grafica #################
#xi es la marca de clase
#fi son las Frecuencias

pyplot.title("Laboratorio 1: n dimensiones")
pyplot.bar(xi, height=fi, width=0.99)
pyplot.ylabel("Frecuencia (fi)")
pyplot.xlabel("Marca de clase (Xi)")

pyplot.show()


#print("---- DATOS ----")
#for i in lines:
#    print(i)
