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
	
	if (s <= 0  || s > MAX_VECTOR_SIZE || si < 0 || si >= s)
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
	if (ind < 0 || ind >= size)
		throw out_of_range("Invalid index");

	return pVector[ind];	// учесть startIndex
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
	return !(this == &v);
} 

template <class T> // присваивание
TVector<T>& TVector<T>::operator=(const TVector &v)
{
	if (this == &v) return *this;

	if (size != v.size) {
		T* tmp = new T[v.size];
		delete[] pVector;

		pVector = tmp
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

	TVector tmp = TVector(size);

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


// Верхнетреугольная матрица
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
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << endl;
    return out;
  }
};

template <class T>
TMatrix<T>::TMatrix(int s): TVector<TVector<T> >(s)
{
} /**/

template <class T> // конструктор копирования
TMatrix<T>::TMatrix(const TMatrix<T> &mt):
  TVector<TVector<T> >(mt) {}

template <class T> // конструктор преобразования типа
TMatrix<T>::TMatrix(const TVector<TVector<T> > &mt):
  TVector<TVector<T> >(mt) {}

template <class T> // сравнение
bool TMatrix<T>::operator==(const TMatrix<T> &mt) const
{
	return true;
} /**/

template <class T> // сравнение
bool TMatrix<T>::operator!=(const TMatrix<T> &mt) const
{
	return true;
} /**/

template <class T> // присваивание
TMatrix<T>& TMatrix<T>::operator=(const TMatrix<T> &mt)
{
	return *this;
} /**/

template <class T> // сложение
TMatrix<T> TMatrix<T>::operator+(const TMatrix<T> &mt)
{
	return *this;
} /**/

template <class T> // вычитание
TMatrix<T> TMatrix<T>::operator-(const TMatrix<T> &mt)
{
	return *this;

} /**/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
