/*
 * Polynom.cpp
 * Authors : Justin Rohr, Alex Zurek, & Alex Banker
 * Version : 1.1
 */
#include "Polynom.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <initializer_list>
#include <string>
#include <iomanip>

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
	int first = 0;
	for (int i = 0; i < p.number_of_terms(); i++) {
		string sign = "";
		float temp = p[i].first;

		if (p[i].first >= 0 && first != 0)
			sign = " + ";
		else if (p[i].first < 0 && first != 0) {
			sign = " - ";
			temp = abs(p[i].first);
		}
		first++;

		out.precision(2);
		out << sign;
		out << temp;

		if (p[i].second > 1) {
			out << "x^";
			out << p[i].second;
		} else if (p[i].second == 1)
			out << "x";
		else if (p[i].second == 0)
			out << " ";
	}
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
	int l = 0;
	//If the exponents are equal add the coeff.
	for (int a = 0; a < this->num_terms; a++) {
		for (int x = l; x < other.num_terms; x++) {
			if (other[x].second == coeff_expon.at(a).second) {
				if (coeff_expon.at(a).first + other[x].first != 0) {
					temp.coeff_expon.push_back(
							make_pair(coeff_expon.at(a).first + other[x].first,
									coeff_expon.at(a).second));
					temp.num_terms++;
					l++;
					break;
				} else {
					l++;
					break;
				}
			} else if (coeff_expon.at(a).second > other[x].second) {
				temp.coeff_expon.push_back(
						make_pair(coeff_expon.at(a).first,
								coeff_expon.at(a).second));
				temp.num_terms++;
				break;
			} else if (other[x].second > coeff_expon.at(a).second) {
				temp.coeff_expon.push_back(
						make_pair(other[x].first, other[x].second));
				temp.num_terms++;
				l++;
			}
		}
	}
	int last = this->num_terms - 1;
	for (int x = l; x < other.num_terms; x++) {
		if (other[x].second < coeff_expon.at(last).second) {
			temp.coeff_expon.push_back(
					make_pair(other[x].first, other[x].second));
			temp.num_terms++;
		}
	}

	return temp;
}

Polynom Polynom::operator-(const Polynom& other) const {
	Polynom temp;
	if (other.number_of_terms() == 0)
		return *this;

	if (this->coeff_expon == other.coeff_expon)
		return Polynom();
	int l = 0;
	//If the exponents are equal minus the coeff.
	for (int a = 0; a < this->num_terms; a++) {
		for (int x = l; x < other.num_terms; x++) {
			if (other[x].second == coeff_expon.at(a).second) {
				if (coeff_expon.at(a).first - other[x].first != 0) {
					temp.coeff_expon.push_back(
							make_pair(coeff_expon.at(a).first - other[x].first,
									coeff_expon.at(a).second));
					temp.num_terms++;
					l++;
					break;
				} else {
					l++;
					break;
				}
			} else if (coeff_expon.at(a).second > other[x].second) {
				temp.coeff_expon.push_back(
						make_pair(coeff_expon.at(a).first,
								coeff_expon.at(a).second));
				temp.num_terms++;
				break;
			} else if (other[x].second > coeff_expon.at(a).second) {
				temp.coeff_expon.push_back(
						make_pair(0.0 - other[x].first, other[x].second));
				temp.num_terms++;
				l++;
			}
		}

	}
	int last = this->num_terms - 1;
	for (int x = l; x < other.num_terms; x++) {
		if (other[x].second < coeff_expon.at(last).second) {
			temp.coeff_expon.push_back(
					make_pair(0.0 - other[x].first, other[x].second));
			temp.num_terms++;
		}
	}
	return temp;
}

Polynom Polynom::operator*(const Polynom& other) const {
	Polynom temp;
	Polynom final;
	int firstTime = 0;
	for (auto a : this->coeff_expon) {
		for (auto b : other.coeff_expon) {
			temp.coeff_expon.push_back(
					make_pair(a.first * b.first, a.second + b.second));
			temp.num_terms++;
		}
		firstTime == 0 ? final = temp : final = final + temp;
		firstTime++;
		temp.coeff_expon.clear();
		temp.num_terms = 0;
	}
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
