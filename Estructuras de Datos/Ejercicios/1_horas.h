
// Edurne Ruiz, Marta Gago

#ifndef HORAS_H
#define HORAS_H

#include <iostream>
#include <iomanip>
#include <stdexcept>  // invalid_argument
#include <string>

class horas {
private:
   int HH; // las horas
   int MM; // los minutos
   int SS; // los segundos 
   bool check(int h, int m, int s) {
       return 0 <= h && h <= 23 && 0 <= m && m <= 59 && 0 <= s && s <= 59;
   }
public:
   // constructora
   horas(int h = 0, int m = 0, int s = 0) {
       if (check(h, m, s)) {
           HH = h;
           MM = m;
           SS = s;
       }
       else throw std::domain_error("datos invalidos");
   }
   
   // observadoras
   int hora() const { return HH; }
   int minuto() const { return MM; }
   int segundo() const { return SS; }

   // operador de comparación
   bool operator<(horas const& h) const {
       return HH * 3600 + MM * 60 + SS < h.HH * 3600 + h.MM * 60 + h.SS;
   }

   //operador de suma
   horas operator + (horas const& other) const {
	   int s = SS + other.SS, m = MM + other.MM, h = HH + other.HH;

	   if (s >= 60) {  s -= 60;  m++; }
	   if (m >= 60) {  m -= 60;  h++; }
	   if (h >= 24) throw std::domain_error("mas de medianoche");

	   return horas(h, m, s);
   }

   //operador de igualdad
   bool operator==(horas const& h) const {
	   return HH * 3600 + MM * 60 + SS == h.HH * 3600 + h.MM * 60 + h.SS;
   }

   void read(std::istream & input = std::cin) {
       char c; int h, m, s;
       input >> h >> c >> m >> c >> s;
       if (check(h, m, s)) { HH = h; MM = m; SS = s; }
       else throw std::domain_error("datos invalidos");
   }

   void print(std::ostream& o = std::cout) const {
      o << std::setfill('0') << std::setw(2) << HH << ':'
        << std::setfill('0') << std::setw(2) << MM << ':'
        << std::setfill('0') << std::setw(2) << SS;
   }
};

inline std::ostream & operator<<(std::ostream & salida, horas const& h) {
   h.print(salida);
   return salida;
}

inline std::istream & operator>>(std::istream & entrada, horas & h) {
   h.read(entrada);
   return entrada;
}

#endif