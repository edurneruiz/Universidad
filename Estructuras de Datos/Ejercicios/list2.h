#include <iostream> 
#include <stdexcept>  // std::domain_error
#include <cmath>
#include "list_eda.h"
#include "stack_eda.h"
using namespace std;

template <class T, class Predicate>
class list_viajeros: public list<T> {
	using iterator = typename list<T>::iterator;
public:

	void remove_if(Predicate pred) {
		stack<iterator> dlt;
		iterator it = this->begin();

		while (it != this->end()) {
			if (!pred(*it)) { //no cumple la condición para pertenecer a la lista
				dlt.push(it);
			}
			++it;
		}

		while (!dlt.empty()) {
			this->erase(dlt.top());
			dlt.pop();
		}
	}
};

