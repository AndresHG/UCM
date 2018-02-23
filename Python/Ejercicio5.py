#Andrés Herranz González


#Inicializa una lista
def iniciaLista():
    return []

#Pide los nombres de los clientes hasta que se escriba "Fin"
def pedirClientes():

    clientes = iniciaLista()
    cliente = input('Nombre del cliente ("fin" para terminar): ')
    while cliente.lower() != 'fin':
        clientes.append(cliente)
        cliente = input('Nombre del cliente ("fin" para terminar): ')
    return clientes

#Abre el archivo donde se van a guardar los clientes que le llegan por parametro
#Escribe uno en cada fila y cierra el archivo
def guardaLista(clientes):

    fichero = open("fichero.txt", "w")
    for cliente in clientes:
        fichero.write(cliente)
        fichero.write("\n")
    fichero.close()

#Abre el archivo de los clientes para lectura y coge el texto que contenga
#Luego lo divide en los diferentes nombres y los mete en un el array que posteriormente devuelve
def cargalista():

    fichero = open("fichero.txt")
    contenido = fichero.read()
    separaLineas = contenido.split()
    fichero.close()

    clientes = iniciaLista()

    for cliente in separaLineas:
        clientes.append(cliente)

    return clientes

#Muestra la lista entera de clientes en diferentes lineas
def muestraClientes(clientes):

    for cliente in clientes:
        muestraCliente(cliente)
    print("--------------------------")

#Muestar el cliente que le llega por parametros en una linea
def muestraCliente(cliente):

    print("cliente [", cliente, "]")


#Pedimos los clientes y los guardamos
clientes = pedirClientes()
guardaLista(clientes)


#Cargamos los clientes del archivo y los mostramos
clientesCargados = cargalista()
muestraClientes(clientesCargados)
