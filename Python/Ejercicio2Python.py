#Pedimos el mes por primera vez al usuario
mes = input("Introduzca el nombre del mes: ")

#Utilizamos un bucle while ya que en el ejemplo, se hacen varias peticiones al usuario
#El bucle termina cuando pulsamos 0
while mes != "0":

    #Utilizamos la función lower() que nos pasa un string a todo minúsculas
    #Caso de los meses de 31 días
    if mes.lower() == "enero" or mes.lower() == "marzo" or mes.lower() == "mayo" or mes.lower() == "julio" or mes.lower() == "agosto" or mes.lower() == "octubre" or mes.lower() == "diciembre":
        print(mes, "tiene 31 días")

    #Caso de los meses de 30 días
    elif mes.lower() == "abril" or mes.lower() == "junio" or mes.lower() == "septiembre" or mes.lower() == "noviembre":
        print(mes, "tiene 30 días")

    #Caso de febrero que tiene 28 días
    elif mes.lower() == "febrero":
        print(mes, "tiene 28 días")

    #Caso en el que se intriduzca un nombre incorrecto
    else:
        print("No conozco ese mes")

    #Volvemos a pedir el mes al usuario
    mes = input("Introduzca el nombre del mes: ")