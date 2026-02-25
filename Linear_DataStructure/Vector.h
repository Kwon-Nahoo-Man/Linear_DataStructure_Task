#pragma once
#include <iostream>


template<typename T>
class C_VECTOR
{
public:
	C_VECTOR(int capacity = 2)
	{
		Reallocate(capacity);
	}
	~C_VECTOR()
	{
		if (m_data != nullptr)
		{
			delete[] m_data;
			m_data = nullptr;
		}
	}

	void PushBack(const T& value)
	{
		if (m_size == m_capacity)
		{
			Reallocate(m_capacity * 2);
		}

		m_data[m_size] = value;
		m_size++;
	}

	void PushBack(const T&& value)
	{
		if (m_size == m_capacity)
		{
			Reallocate(m_capacity * 2);
		}

		m_data[m_size] = std::move(value);
		m_size++;
	}

	bool Erase(int index)
	{
		if (index < 0 || index >= m_size)
		{
			return false;
		}

		for (int i = index + 1; i < m_size; i++)
		{
			m_data[i - 1] = m_data[i];
		}
		m_size--;

		m_data[m_size] = T{};

		return true;
	}

	void Clear()
	{
		for (int i = 0; i < m_size; i++)
		{
			m_data[i] = T{};
		}
		m_size = 0;
	}

	void Reserve(int newCapacity)
	{
		Reallocate(newCapacity);
	}

	const T& End() const
	{
		if (m_data != nullptr)
		{
			return m_data[m_size - 1];
		}
		else
		{
			return nullptr;
		}
		
	}

	const T& Begin() const
	{
		if (m_data != nullptr)
		{
			return m_data[0];
		}
		else
		{
			return nullptr;
		}
	}

	const T& operator[](int index) const
	{
		if (index >= m_size)
		{
			__debugbreak();
		}
		return m_data[index];
	}

	T& operator[](int index)
	{
		if (index >= m_size)
		{
			__debugbreak();
		}
		return m_data[index];
	}

public:

	// getter
	const T& At(int index) const
	{
		if (index >= 0 && index < m_size)
		{
			return m_data[index];
		}
		else
		{
			__debugbreak();
		}
		
	}
	
	int Size() const
	{
		return m_size;
	}
	int Capacity() const
	{
		return m_capacity;
	}

	bool Empty() const
	{
		return m_size == 0;
	}

private:
	void Reallocate(int newCapacity)
	{
		// 새로운 공간 할당
		T* newBlock = new T[newCapacity];
		for (int i = 0; i < newCapacity; i++)
		{
			newBlock[i] = T{};
		}

		// 새로 할당할 공간이 현재 데이터 사이즈보다 작을 때
		// 할당할 공간만큼으로 줄여버리기
		if (newCapacity < m_size)
		{
			m_size = newCapacity;
		}

		// 원래 데이터 옮기기
		if (m_data != nullptr)
		{
			for (int i = 0; i < m_size; i++)
			{
				newBlock[i] = m_data[i];
			}
		}

		// 옛날 데이터 삭제 && 새로운 데이터로 교체
		delete[] m_data;
		m_data = newBlock;

		// capacity 설정
		m_capacity = newCapacity;

	}


private:

	T* m_data{ nullptr };
	int m_size{};
	int m_capacity{};


};
