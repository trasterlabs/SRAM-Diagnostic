/**
 * listado de pruebas para asegurar el funcionamiento de un mempool
 * ¿Qué es un mempool? Es un bufer estático de memoria donde hay un tipo asignado y cada vez que alguien trate de borrar o crear un objeto, sustituya el comportamiento de new y delete para evitar usar memoria dinámica.
 */

/**
 * +---+---+---+---+---+---+---+---+---+----+
 * | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | <- Tipo de objeto que irá sustituyendo a new y delete
 * +===+===+===+===+===+===+===+===+===+====+
 * | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |  0 | <- Cuántos objetos hay seguidos
 * +---+---+---+---+---+---+---+---+---+----+
 */
