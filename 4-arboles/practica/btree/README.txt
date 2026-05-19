Compilamos primero la implementación:
-----------------
$ gcc -c btree.c
-----------------

Si todo anduvo bien, generó un btree.o en el directorio.

Luego, podemos compilar el archivo test.c, dándole
nombre "test" al binario (en lugar de "a.out"), y
diciendole que tiene que tomar algunas funciones
de btree.o:
----------------------------
$ gcc -o test test.c btree.o
----------------------------

Ejecutamos "test" para verificar que haga lo esperado:
---------
$ ./test
1 2 3 4
---------
