
// Título: Reina del súper

// Comentario general de la solución 
/**
 * Vamos a usar una cola de prioridad de elementos que son una estructura conteniendo 
 * el puesto del cajero y los segundos desde t = 0 (comienzo del problema) que han de transcurrir
 * hasta que ese cliente haya sido atendido. De este modos es sencillo observar
 * que el cliente que tiene que salir es aquel con menor tiempo.
 *
 * Para mantener este invariante las inserciones de los elementos se harán primero los N
 * primero clientes sin añadir nada de tiempo y una vez hayan sido insertados estos cambiaremos
 * la forma de insertar. A partir de ahora, como todos los cajeros ya están ocupados pediremos a 
 * la cola que nos devuelva el peusto saliente e insertaremos un nuevo cliente con este puesto
 * y como tiempo la suma de lo que ha tardado el anterior (acumulado) más lo que tardará él.
 * 
 * En caso que no hubiese suficientes clientes como para llenar todas las cajas el resultado es 
 * obvio pues las cajas se van llenando en orden, por lo que a Ismael le tocaría la caja vacía siguiente
 * al último cliente.
 *
 */
#include <fstream>
#include <iostream>

#include <queue>
#include <vector>

using namespace std;

struct tPuesto {
  int puesto;
  int segundos;
};

class ComparaPuestos {
public:
  bool operator()(const tPuesto& p1, const tPuesto& p2) const {
    if (p1.segundos == p2.segundos) return p1.puesto > p2.puesto;
    return p1.segundos > p2.segundos;
  }
};

bool resuelve() {

  int N, C;
  cin >> N >> C;

  if (!N) return false;
  int tiempo;
  if (C < N) {
    cout << C + 1 << '\n';
    for (int i = 0; i < C; ++i) cin >> tiempo; // Consumir la entrada
  }
  
  else {  // Sabemos que hay clientes como para llenar todas las cajas, así que empezamos a 
          // colocarlos y ejecutar el algoritmo

    priority_queue<tPuesto, vector<tPuesto>, ComparaPuestos> cola_unica;
    for (int i = 1; i <= N; ++i) { // Colocamos los N primeros clientes y a partir de aquí ya 
                                   // vamos sacando en orden
      cin >> tiempo;
      cola_unica.push({ i, tiempo });
    }

    tPuesto saliente;
    for (int i = N + 1; i <= C; ++i) { // Procesamiento de los clientes por delante de Ismael
      saliente = cola_unica.top();
      cola_unica.pop();
      cin >> tiempo;
      cola_unica.push({ saliente.puesto, saliente.segundos + tiempo });
    }

    // Determinación del puesto de Ismael
    cout << cola_unica.top().puesto << '\n';
  }
  


  return true;
}

int main() {
  // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
  std::ifstream in("casos.txt");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  while (resuelve());
  
  // para dejar todo como estaba al principio
#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  system("PAUSE");
#endif
  return 0;
}

