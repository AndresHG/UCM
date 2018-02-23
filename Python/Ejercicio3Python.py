
#Creamos la lista que contendrá los nombres introducidos y pedimos el primer nombre
lista = []
nom = input("Introduzca un nombre: ")

#Bucle que va pidiendo todos los nombres al usuario hasta que escriba "fin"
while nom.lower() != "fin":
    lista.append(nom)
    print(lista)
    nom = input("Introduzca un nombre: ")

#Una vez salimos del bucle nos despedimos para que el usuario sepa que hemos termianado
print("Fin de la ejecución")