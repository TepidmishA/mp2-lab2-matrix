// ННГУ, ВМК, Курс "Методы программирования2", С++, ООП
//
// utmatrix.h  Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица  реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class T>
class TVector
{
protected:
  T *pVector;
  int size;       // размер вектора
  int startIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();
  int GetSize()      { return size;       } // размер вектора
  int GetStartIndex(){ return startIndex; } // индекс первого элемента
  
  T& operator[](int pos);             // доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const T &val);   // прибавить скаляр
  TVector  operator-(const T &val);   // вычесть скаляр
  TVector  operator*(const T &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  T  operator*(const TVector &v);			// скалярное произведение

  // вводвывод
  friend istream& operator>>(istream &in, TVector &v) {
    for (int i = 0; i < v.size; i++)
      in >> v.pVector[i];
    return in;
  }

  friend ostream& operator<<(ostream &out, const TVector &v) {
    for (int i = 0; i < v.size; i++)
      out << v.pVector[i] << ' ';
    return out;
  }
};

template <class T>
TVector<T>::TVector(int s, int si) {
	
	if (s <= 0  || s > MAX_VECTOR_SIZE || si < 0)
		throw out_of_range("invalid vector size or start index");

	size = s;
	startIndex = si;
	pVector = new T[size];
} 

template <class T> //конструктор копирования
TVector<T>::TVector(const TVector<T> &v) {
	size = v.size;
	startIndex = v.startIndex;

	pVector = new T[size];
	for (int i = 0; i < size; i++) {
		pVector[i] = v.pVector[i];
	}
}

template <class T>
TVector<T>::~TVector() {
	delete[] pVector;
} 

template <class T> // доступ
T& TVector<T>::operator[](int ind) {
	if (ind - startIndex < 0 || ind - startIndex >= size)
		throw out_of_range("Invalid index");

	return pVector[ind - startIndex];
}

template <class T> // сравнение
bool TVector<T>::operator==(const TVector &v) const
{
	if (size != v.size || startIndex != v.startIndex)
		return false;

	for (int i = 0; i < size; i++) {
		if (pVector[i] != v.pVector[i])
			return false;
	}
	return true;
} 

template <class T> // сравнение
bool TVector<T>::operator!=(const TVector &v) const
{
	return !(*this == v);
} 

template <class T> // присваивание
TVector<T>& TVector<T>::operator=(const TVector &v)
{
	if (this == &v) return *this;

	if (size != v.size) {
		T* tmp = new T[v.size];
		delete[] pVector;

		pVector = tmp;
		size = v.size;
	}

	startIndex = v.startIndex;
	for (int i = 0; i < size; i++) {
		pVector[i] = v.pVector[i];
	}

	return *this;
} 

template <class T> // прибавить скаляр
TVector<T> TVector<T>::operator+(const T &val)
{
	TVector tmp = TVector(size);

	for (int i = 0; i < size; i++) {
		tmp.pVector[i] = pVector[i] + val;
	}

	return tmp;
} 

template <class T> // вычесть скаляр
TVector<T> TVector<T>::operator-(const T &val)
{
	TVector tmp = TVector(size);

	for (int i = 0; i < size; i++) {
		tmp.pVector[i] = pVector[i] - val;
	}

	return tmp;
} 

template <class T> // умножить на скаляр
TVector<T> TVector<T>::operator*(const T &val)
{
	TVector tmp = TVector(size);

	for (int i = 0; i < size; i++) {
		tmp.pVector[i] = pVector[i] * val;
	}

	return tmp;
} 

template <class T> // сложение
TVector<T> TVector<T>::operator+(const TVector<T> &v)
{
	if (size != v.size) throw - 1;

	TVector tmp = TVector(size, this->startIndex);

	for (int i = 0; i < size; i++) {
		tmp.pVector[i] = pVector[i] + v.pVector[i];
	}

	return tmp;
} 

template <class T> // вычитание
TVector<T> TVector<T>::operator-(const TVector<T> &v)
{
	if (size != v.size) throw - 1;

	TVector tmp = TVector(size);

	for (int i = 0; i < size; i++) {
		tmp.pVector[i] = pVector[i] - v.pVector[i];
	}

	return tmp;
} 

template <class T> // скалярное произведение
T TVector<T>::operator*(const TVector<T> &v)
{
	if (size != v.size) throw - 1;

	T tmp = 0;

	for (int i = 0; i < size; i++) {
		tmp += pVector[i] * v.pVector[i];
	}

	return tmp;
} 

/*----------------------------------------------------------------------*/

// Верхнетреугольная матрица
// Реализация через агрегацию
template <class T>
class ATMatrix {
	int size;
	TVector<T>* pMatrix;
	// матрица - массив векторов

public:
	ATMatrix(int s = 10);

	TVector<T>& ATMatrix<T>::operator[](int ind);
};

template <class T>
ATMatrix<T>::ATMatrix(int _size) {
	size = _size;
	pMatrix = new TVector<T>[size];

	for (int i = 0; i < size; i++) {
		pMatrix[i] = TVector<T>(size - i, i);
	}
}

template<class T>
TVector<T>& ATMatrix<T>::operator[](int ind)
{
	if (ind < 0 || ind >= size) 
		throw out_of_range("invalid matrix index");;

	return pMatrix[ind];
}

/*----------------------------------------------------------------------*/

// Верхнетреугольная матрица
// Реализация через наследование
template <class T>
class TMatrix : public TVector<TVector<T> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<T> > &mt); // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание

  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt) {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }

  friend ostream & operator<<( ostream &out, const TMatrix &mt) {
    for (int i = 0; i < mt.size; i++)
      out << mt.pVector[i] << endl;
    return out;
  }
};

template <class T>
TMatrix<T>::TMatrix(int s): TVector<TVector<T> >(s) {
	if (s > MAX_MATRIX_SIZE || s < 0) throw - 1;

	for (int i = 0; i < size; i++) {				// ??? size
		pVector[i] = TVector<T>(size - i, i);
	}
} 

template <class T> // конструктор копирования
TMatrix<T>::TMatrix(const TMatrix<T> &mt):
  TVector<TVector<T> >(mt) {}	// будет рабоать копирование родительского класса

template <class T> // конструктор преобразования типа
TMatrix<T>::TMatrix(const TVector<TVector<T> > &mt):
  TVector<TVector<T> >(mt) {}

template <class T> // сравнение
bool TMatrix<T>::operator==(const TMatrix<T> &mt) const
{
	if (this->size != mt.size) return false;
	
	for (int i = 0; i < this->size; i++) {
		//if (*this[i] != mt[i]) return false;
		if (this->pVector[i] != mt.pVector[i]) {
			return false;
		}
	}
	return true;
}

template <class T> // сравнение
bool TMatrix<T>::operator!=(const TMatrix<T> &mt) const {
	return !(*this == mt);
} 

template <class T> // присваивание
TMatrix<T>& TMatrix<T>::operator=(const TMatrix<T> &mt) {
	if (this == &mt) return *this;

	if (this->size != mt.size) {
		this->size = mt.size;
		delete[] this->pVector;
		this->pVector = new TVector<T>[this->size];			// ???
	}

	for (int i = 0; i < this->size; i++) {
		this->pVector[i] = mt.pVector[i];
	}

	return *this;
} 

template <class T> // сложение
TMatrix<T> TMatrix<T>::operator+(const TMatrix<T> &mt)
{
	return TVector<TVector<T>>::operator+(mt);
} 

template <class T> // вычитание
TMatrix<T> TMatrix<T>::operator-(const TMatrix<T> &mt) {
	return TVector<TVector<T>>::operator-(mt);
} 

// написать умножение матриц

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
