/*
 * Polynom.cpp
 * Authors : Justin Rohr, Alex Zurek, & Alex Banker
 * Version : 1.1
 */
#include "Polynom.h"
//#include <limits>//#include <cmath>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <initializer_list>
#include <string>
namespace gvsu {
using namespace std;

Polynom::Polynom() {
	num_terms = 0;
}

Polynom::Polynom(initializer_list<float> coef_list,
		initializer_list<int> expo_list) {
	if (coef_list.size() != expo_list.size())
		throw invalid_argument("Inputs of different length");
	num_terms = 0;
	auto ex = expo_list.begin();
	for (auto iter = coef_list.begin(); iter != coef_list.end(); ++iter) {
		num_terms++; //Increase Number of Terms
		coeff_expon.push_back(std::make_pair(*iter, *ex)); // Inserting into vector
		//cout << "Coefficient: " << *iter << " & Exponent: " << *ex << endl;
		ex++;
	}
}

ostream& operator<<(ostream& out, const Polynom& p) {
	string outputBuilder = "";

	for (int i = p.number_of_terms() - 1; i >= 0; i--) { // Access things in reverse
		string sign;
		(p[i].first < 0) ? sign = " - " : sign = " + ";

		if (p[i].second <= 1) { // Exponent of 1 or 0
			outputBuilder.append(sign);
			//outputBuilder.append(std::to_string(p[i].first));
			outputBuilder += (char) p[i].first;
			outputBuilder.append("X^");
			outputBuilder += (char) p[i].second;
//			} else {      On second though, it should still probably accurately represent
//				if (){     any given input.  However, the equations will need to account for
//					       the rules for exponents of 1 and 0.
//				} else {
//
//				}
//				output = output + sign +
		} //TODO:Actually get this working properly...

	}
	out << outputBuilder;
	return out;
}

int Polynom::number_of_terms() const {
	return num_terms;
}

/*
 * A Polynom method that returns a call to its vector<pair> variable.
 */
pair<float, int> Polynom::operator[](int index) const {
	return coeff_expon.at(index);
}

Polynom& Polynom::operator*=(float m) {
	for (int x = 0; x < num_terms; x++) {
		coeff_expon.at(x) = make_pair(coeff_expon.at(x).first * m,
				coeff_expon.at(x).second);
	}
	return *this;
}

Polynom Polynom::operator*(float m) const {
	if (m == 0)
		return Polynom();
	Polynom temp;
	for (int x = 0; x < this->num_terms; x++) {
		temp.coeff_expon.push_back(
				make_pair(coeff_expon.at(x).first * m,
						coeff_expon.at(x).second));
		temp.num_terms++;
	}
	return temp;
}

Polynom operator*(float val, const Polynom& p) {
	return p * val;
}

/* basic polynomial arithmetic between two polynomials: "*this" and "other" */
Polynom Polynom::operator+(const Polynom& other) const {
	Polynom temp;
	if (other.num_terms == 0)
		return *this;

	//If the exponents are equal add the coeff.
	for (int a = 0; a < this->num_terms; a++) {
		for (int x = 0; x < other.num_terms; x++) {
			if (other[x].second == coeff_expon.at(a).second) {
				temp.coeff_expon.push_back(
						make_pair(coeff_expon.at(a).first + other[x].first,
								coeff_expon.at(a).second));
				temp.num_terms++;
				break;
			} else if (other[x].second < coeff_expon.at(a).second) {
				temp.coeff_expon.push_back(
						make_pair(coeff_expon.at(a).first,
								coeff_expon.at(a).second));
				temp.num_terms++;
				break;
			} /*else if (other[x].second > coeff_expon.at(a).second) {
			 temp.coeff_expon.push_back(
			 make_pair(other[x].first, other[x].second));
			 break;
			 }*/
		}

	}
	/*
	 int x = 0;
	 for (int a = 0; a < this->num_terms; a++) {
	 if (other[x].second == coeff_expon.at(a).second) {
	 temp.coeff_expon.push_back(
	 make_pair(other[x].first + coeff_expon.at(a).first,
	 coeff_expon.at(a).second));
	 temp.num_terms++;
	 if (x < other.num_terms)
	 x++;
	 } else if (other[x].second < coeff_expon.at(a).second) {
	 temp.coeff_expon.push_back(
	 make_pair(coeff_expon.at(a).first,
	 coeff_expon.at(a).second));
	 temp.num_terms++;
	 } else if (other[x].second > coeff_expon.at(a).second) {
	 if (x < other.num_terms) {
	 x++;
	 temp.coeff_expon.push_back(
	 make_pair(other[x].first, other[x].second));
	 a--;
	 temp.num_terms++;
	 }
	 }
	 }
	 */
	return temp;
}

Polynom Polynom::operator-(const Polynom& other) const {
	Polynom temp;
	if (other.number_of_terms() == 0) {
		return *this;
	}
	if (this->coeff_expon == other.coeff_expon)
		return Polynom();
//If the exponents are equal minus the coeff.
	for (int a = 0; a < this->num_terms; a++) {
		for (int x = 0; x < other.num_terms; x++) {
			if (other[x].second == coeff_expon.at(a).second) {
				temp.coeff_expon.push_back(
						make_pair(coeff_expon.at(a).first - other[x].first,
								coeff_expon.at(a).second));
				temp.num_terms++;
				break;
			} else if (other[x].second < coeff_expon.at(a).second) {
				temp.coeff_expon.push_back(coeff_expon[a]);
				temp.num_terms++;
				break;
			} else if (other[x].second > coeff_expon.at(a).second) {
				temp.coeff_expon.push_back(
						make_pair(0.0 - other[x].first, other[x].second));
				temp.num_terms++;
			} else {
				temp.coeff_expon.push_back(coeff_expon[a]);
				temp.num_terms++;
			}
		}

	}
	return temp;
}

Polynom Polynom::operator*(const Polynom& other) const {
	Polynom temp;
	Polynom final;
	for (auto a : this->coeff_expon) {
		for (auto b : other.coeff_expon) {
			temp.coeff_expon.push_back(
					make_pair(a.first * b.first, a.second + b.second));
			temp.num_terms++;
		}	//TODO: Need to add each a(1)*b + a(2)*b + a(3) *b  together
		final = final + temp;
		temp.coeff_expon.clear();
		temp.num_terms = 0;
	}
	//TODO: Use a for loop like this: for (vector<float,int>& z : other.coeff_expon){continue;}
	return final;
}

double Polynom::operator()(double val) const {
	double result = 0.0;
	for (auto it : this->coeff_expon)
		if (it.second > 0)
			result += it.first * std::pow(val, it.second);
		else
			result += it.first;

	return result;
}

}
