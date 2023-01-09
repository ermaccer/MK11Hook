#pragma once
#include <iostream>

template < class T > class TArray {
public:
	T* Data;
	int Count;
	int Max;

	TArray();
	T& Get(int id) { return this->Data[id]; };
	void Add(T data);

};

template<class T>
inline TArray<T>::TArray()
{
	Data = nullptr;
	Count = 0;
	Max = 0;
}

template<class T>
inline void TArray<T>::Add(T InputData)
{
	Data = (T*)realloc(Data, sizeof(T) * (Count + 1));
	Data[Count++] = InputData;
	Max = Count;
}
