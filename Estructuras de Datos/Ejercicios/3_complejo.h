#pragma once

#ifndef complejo_h
#define complejo_h

#include <iostream>
#include <iomanip>
#include <stdexcept>  // std::domain_error
#include <utility>    // std::move
#include <algorithm>
#include <cmath>

template<class T>
class complejo {
private:
	T p_real;
	T p_im;
public:
	complejo(T r = 0, T im = 0) {
		p_real = r; p_im = im;
	}

	complejo<T> operator+(complejo<T> const& c);
	complejo<T>& operator*(complejo<T> const& c);
	T mod();

	void read(std::istream & input = std::cin) {
		T r, im;
		input >> r >> im;
		p_real = r; p_im = im;
	}

	void print(std::ostream& o = std::cout) const {
		o << std::setfill('0') << std::setw(2) << p_real 
			<< std::setfill('0') << std::setw(2) << p_im;
	}

};

template<class T>
inline std::ostream & operator<<(std::ostream & salida, complejo<T> const& c) {
	c.print(salida);
	return salida;
}

template<class T>
inline std::istream & operator>>(std::istream & entrada, complejo<T> & c) {
	c.read(entrada);
	return entrada;
}

template<class T>
complejo<T> & operator+(complejo<T> const& c) {
	return complejo(p_real + c.p_real, p_im + c.p_im);
}

template<class T>
complejo<T>& operator*(complejo<T> const& c) { //(a+bi) * (c+di) = (a*c-b*d) + (a*d+c*b)i
	return complejo(p_real*c.p_real - p_im * c.p_im, p_real*c.p_im + p_im * c.p_real);
}

template<class T>
T mod() { 
	return sqrt(p_real ^ 2 + p_im ^ 2);
}

#endif

