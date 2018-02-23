#Andrés Herranz González

#Crea el almacen (un array)
def crearAlmacen():
    return []

#Añade los objetos al almacén
def anadeAalmacen(objeto, almacen):
    almacen.append(objeto)

#Muestra el objeto de una posición dada
def muestraObjeto(objeto):
    print("El material [ ", objeto, " ]")

#Muestra todos los objetos de un almacén
def muestraAlmacen(almacen):
    for obj in almacen:
        muestraObjeto(obj)

#Elimina el objeto de una posicion dada de un almacen
def eliminaDeAlmacen(almacen, pos):
    if(almacen[pos]):
        almacen.pop(pos)

#Busca si existe una posición dada en un almacén, y si es así, devuelve el objeto que contiene
def buscaEnAlmacen(almacen, pos):
    if(len(almacen) > pos):
        return almacen[pos]
    else:
        return "nada"


#inicializamos el almacén
almacen = crearAlmacen()

#Añadimos los objetos al almacén
anadeAalmacen("plancha", almacen)
anadeAalmacen("cafetera", almacen)
anadeAalmacen("mesa", almacen)
anadeAalmacen("silla", almacen)

#Buscamos el objeto de la posición 10, si existe lo mostramos y sino, mostramos mensaje de error
if(buscaEnAlmacen(almacen, 10) != "nada"):
    print(buscaEnAlmacen(almacen, 10))
else:
    print("No existe el objecto con posición 10. \n")

#Eliminamos el objeto de la posición 2
eliminaDeAlmacen(almacen, 2)

#Mostramos el contenido del almacén
muestraAlmacen(almacen)

