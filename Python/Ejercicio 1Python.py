#Ejercicio 1 Curso de introducción a Python

nombre = input("Nombre del alumno: ")
nota1 = float(input("Nota del examen parcial 1: "))
nota2 = float(input("Nota del examen parcial 2: "))
nota3 = float(input("Nota del examen parcial 3: "))

notafin = float(0.2 *  nota1 + 0.3 * nota2 + 0.5 * nota3)

print("La calificación final de ", nombre, " es ", notafin)