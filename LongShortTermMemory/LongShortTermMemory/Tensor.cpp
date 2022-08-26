#include "Tensor.h"

template class Tensor<int>;
template class Tensor<float>;
template class Tensor<double>;
template class Tensor<size_t>;
template class unique_ptr<Tensor<double>>;
template class unique_ptr<Tensor<int>>;

template<typename T>
Tensor<T>::Tensor(int numDims, int const* m_Dims)
{
	assert(numDims > 0 && numDims <= 4);
	int size = 1;
	for (int i = 0; i < numDims; i++)
	{
		size *= m_Dims[i];
		this->m_Dims[i] = m_Dims[i];
	}
	m_Size = size;
	m_Data = new T[m_Size];
	this->numDims = numDims;
}

template<typename T>
Tensor<T>::Tensor(vector<int> m_Dims)
{
	numDims = m_Dims.size();
	assert(numDims > 0 && numDims <= 4);
	int size = 1;
	for (int i = 0; i < numDims; i++)
	{
		size *= m_Dims[i];
		this->m_Dims[i] = m_Dims[i];
	}
	m_Size = size;
	m_Data = new T[m_Size];
	this->numDims = numDims;
}

template<typename T>
Tensor<T>::Tensor(const Tensor<T>& other) : m_Size(other.m_Size), numDims(other.numDims), m_Data(new T[other.m_Size])
{
	std::copy(other.m_Data, other.m_Data + m_Size, m_Data);
	std::copy(other.m_Dims, other.m_Dims + 4, m_Dims);
}

template<typename T>
Tensor<T>::Tensor(const unique_ptr<Tensor<T>>& other) : m_Size(other->m_Size), numDims(other->numDims), m_Data(new T[other->m_Size])
{
	std::copy(other->m_Data, other->m_Data + m_Size, m_Data);
	std::copy(other->m_Dims, other->m_Dims + 4, m_Dims);
}

template<typename T>
Tensor<T>::~Tensor() {
	delete[] m_Data;
}

template<typename T>
void Tensor<T>::zero()
{
	memset(m_Data, 0, sizeof(T) * m_Size);
}

template<typename T>
int Tensor<T>::GetSize()
{
	return m_Size;
}

template<typename T>
T Tensor<T>::GetListIndex(int i)
{
	return m_Data[i];
}


template<typename T>
T Tensor<T>::get(int i)
{
	assert(numDims == 1);
	return m_Data[i];
}

template<typename T>
T Tensor<T>::get(int i, int j)
{
	assert(numDims == 2);
	return m_Data[(i * m_Dims[1]) + j];
}

template<typename T>
T Tensor<T>::get(int i, int j, int k)
{
	assert(numDims == 3);
	return m_Data[(i * m_Dims[1] * m_Dims[2]) + (j * m_Dims[2]) + k];
}

template<typename T>
T Tensor<T>::get(int i, int j, int k, int l)
{
	assert(numDims == 4);
	return m_Data[(i * m_Dims[1] * m_Dims[2] * m_Dims[3]) + (j * m_Dims[2] * m_Dims[3]) + (k * m_Dims[3]) + l];
}

//template<typename T>
//Tensor<T> Tensor<T>::GetTensor3D(int i)
//{
//	assert(numDims == 4);
//	int newDims[] = { m_Dims[1], m_Dims[2], m_Dims[3] };
//	Tensor<T> result(3, newDims);
//	for (size_t j = 0; j < m_Dims[1]; j++)	
//		for (size_t k = 0; k < m_Dims[2]; k++)		
//			for (size_t l = 0; l < m_Dims[3]; l++)			
//				result.set(m_Data[(i * m_Dims[1] * m_Dims[2] * m_Dims[3]) + (j * m_Dims[2] * m_Dims[3]) + (k * m_Dims[3]) + l], j, k, l);					
//
//	return result;
//}
//
//template<typename T>
//Tensor<T> Tensor<T>::GetTensor2D(int i)
//{
//	assert(numDims == 3);
//	int newDims[] = { m_Dims[1], m_Dims[2] };
//	Tensor<T> result(2, newDims);
//	for (size_t j = 0; j < m_Dims[1]; j++)
//		for (size_t k = 0; k < m_Dims[2]; k++)
//			result.set(m_Data[(i * m_Dims[1] * m_Dims[2]) + (j * m_Dims[2]) + k], j, k);
//
//	return result;
//}
//
//template<typename T>
//Tensor<T> Tensor<T>::GetTensor1D(int i)
//{
//	assert(numDims == 2);
//	int newDims[] = { m_Dims[1] };
//	Tensor<T> result(1, newDims);
//	for (size_t j = 0; j < m_Dims[1]; j++)
//		result.set(m_Data[(i * m_Dims[1]) + j], j);
//
//	return result;
//}

template<typename T>
int Tensor<T>::GetDimLen(int dimIndex, int start, int end)
{
	int len = dimIndex;
	for (int i = start; i < end; i++)	
		len *= m_Dims[i];	
	return len;
}

//template<typename T>
//T Tensor<T>::get(const unsigned int args, ...)
//{
//	int dimIndex = args;
//	int dataIndex = 0;
//	va_list ap;
//	va_start(ap, args);
//	int startDim = 0;
//	while (startDim < numDims)
//	{
//		dataIndex += GetDimLen(dimIndex, startDim + 1, numDims);
//		dimIndex = va_arg(ap, int);
//		startDim++;
//	}
//	va_end(ap);
//
//	return m_Data[dataIndex];
//}

template<typename T>
void Tensor<T>::set(T value, int i)
{
	assert(numDims == 1);
	m_Data[i] = value;
}

template<typename T>
void Tensor<T>::set(T value, int i, int j)
{
	assert(numDims == 2);
	m_Data[(i * m_Dims[1]) + j] = value;
}

template<typename T>
void Tensor<T>::set(T value, int i, int j, int k)
{
	assert(numDims == 3);
	m_Data[(i * m_Dims[1] * m_Dims[2]) + (j * m_Dims[2] + k)] = value;
}

template<typename T>
void Tensor<T>::set(T value, int i, int j, int k, int l)
{
	assert(numDims == 4);
	m_Data[(i * m_Dims[1] * m_Dims[2] * m_Dims[3]) + (j * m_Dims[2] * m_Dims[3]) + (k * m_Dims[3]) + l] = value;
}

template<typename T>
void Tensor<T>::SetListIndex(T value, int i)
{
	m_Data[i] = value;
}

//template<typename T>
//void Tensor<T>::set(T value, const unsigned int args, ...)
//{
//	int dimIndex = args;
//	int dataIndex = 0;
//	va_list ap;
//	va_start(ap, args);
//	int startDim = 0;
//	while (startDim < numDims)
//	{
//		dataIndex += GetDimLen(dimIndex, startDim + 1, numDims);
//		dimIndex = va_arg(ap, int);
//		startDim++;
//	}
//	va_end(ap);
//
//	m_Data[dataIndex] = value;
//}

template<typename T>
void Tensor<T>::add(T value, int i)
{
	assert(numDims == 1);
	m_Data[i] = value;
}

template<typename T>
void Tensor<T>::add(T value, int i, int j, int k, int l)
{
	assert(numDims == 4);
	m_Data[(i * m_Dims[1] * m_Dims[2] * m_Dims[3]) + (j * m_Dims[2] * m_Dims[3]) + (k * m_Dims[3]) + l] += value;
}

//template<typename T>
//void Tensor<T>::add(T value, const unsigned int args, ...)
//{
//	int dimIndex = args;
//	int dataIndex = 0;
//	va_list ap;
//	va_start(ap, args);
//	int startDim = 0;
//	while (startDim < numDims)
//	{
//		dataIndex += GetDimLen(dimIndex, startDim + 1, numDims);
//		dimIndex = va_arg(ap, int);
//		startDim++;
//	}
//	va_end(ap);
//
//	m_Data[dataIndex] += value;
//}

template<typename T>
void Tensor<T>::view(int newNumDims, int* newDims)
{
	assert(newNumDims > 0 && newNumDims <= 4);
	this->numDims = newNumDims;
	copy(newDims, newDims + 4, this->m_Dims);
}

template<typename T>
Tensor<T> Tensor<T>::matmul(Tensor<T> other)
{
	assert(numDims == 2 && other.numDims == 2);
	assert(m_Dims[1] == other.m_Dims[0]);

	int newDims[] = { m_Dims[0], other.m_Dims[1] };
	Tensor<T> product(2, newDims);
	for (int i = 0; i < this->m_Dims[0]; i++) // row iter
	{
		for (int j = 0; j < other.m_Dims[1]; j++) // col iter
		{
			T value = 0;
			for (int k = 0; k < other.m_Dims[0]; k++) // sum iter
				value += this->get(i, k) * other.get(k, j);

			product.set(value, i, j);
		}
	}
	return product;
}

//template<typename T>
//Tensor<T> Tensor<T>::multiply(Tensor<T> other)
//{
//	assert(numDims == 2 && other.numDims == 2);
//	assert(m_Dims[0] == other.m_Dims[0] && m_Dims[1] == other.m_Dims[1]);
//
//	int newDims[] = { m_Dims[0], other.m_Dims[1] };
//	Tensor<T> product(2, newDims);
//	for (size_t i = 0; i < m_Dims[0]; i++)	
//		for (size_t j = 0; j < m_Dims[1]; j++)
//			product.set(this->get(i, j) * other.get(i, j), i, j);
//		
//	return product;
//}

template<typename T>
Tensor<T> Tensor<T>::transpose()
{
	assert(numDims == 2);
	int newDims[] = {m_Dims[1], m_Dims[0]};
	Tensor<T> transpose(numDims, newDims);
	for (int i = 0; i < m_Dims[0]; i++)	
		for (int j = 0; j < m_Dims[1]; j++)		
			transpose.set(get(i, j), j, i);
	return transpose;
}

template<typename T>
T Tensor<T>::sum()
{
	T total = 0;
	for (int i = 0; i < m_Size; i++)
		total += m_Data[i];
	return total;
}

template<typename T>
Tensor<T> Tensor<T>::operator+(T val)
{
	Tensor<T> result(numDims, m_Dims);
	for (size_t i = 0; i < m_Size; i++)
		result.m_Data[i] = m_Data[i] + val;
	return result;
}

template<typename T>
Tensor<T> Tensor<T>::operator+(Tensor<T> other)
{
	if (other.numDims == 1 && numDims == 2 && other.m_Size == this->m_Dims[1])
	{
		// if other is a 1D and this is a 2D tensor
		Tensor<T> result(numDims, m_Dims);
		for (int i = 0; i < this->m_Dims[0]; i++)
			for (int j = 0; j < this->m_Dims[1]; j++)
				result.set(get(i, j) + other.get(j), i, j);
		return result;
	}
	else if (other.numDims == numDims && other.m_Size == m_Size)
	{
		Tensor<T> result(numDims, m_Dims);
		for (int i = 0; i < m_Size; i++)		
			result.m_Data[i] = m_Data[i] + other.m_Data[i];
		return result;
	}
	throw logic_error("Undefined Sum operration");
}

template<typename T>
Tensor<T> Tensor<T>::operator+(unique_ptr<Tensor<T>> other)
{
	if (other->numDims == 1 && numDims == 2 && other->m_Size == this->m_Dims[1])
	{
		// if other is a 1D and this is a 2D tensor
		Tensor<T> result(numDims, m_Dims);
		for (int i = 0; i < this->m_Dims[0]; i++)
			for (int j = 0; j < this->m_Dims[1]; j++)
				result.set(get(i, j) + other->get(j), i, j);
		return result;
	}
	else if (other->numDims == numDims && other->m_Size == m_Size)
	{
		Tensor<T> result(numDims, m_Dims);
		for (int i = 0; i < m_Size; i++)
			result.m_Data[i] = m_Data[i] + other->m_Data[i];
		return result;
	}
	throw logic_error("Undefined Sum operration");
}

template<typename T>
Tensor<T> Tensor<T>::operator-(Tensor<T> other)
{
	if (other.numDims == 1 && numDims == 2 && other.m_Size == this->m_Dims[1])
	{
		// if other is a 1D and this is a 2D tensor
		Tensor<T> result(numDims, m_Dims);
		for (int i = 0; i < this->m_Dims[0]; i++)
			for (int j = 0; j < this->m_Dims[1]; j++)
				result.set(get(i, j) - other.get(j), i, j);
		return result;
	}
	else if (other.numDims == numDims && other.m_Size == m_Size)
	{
		Tensor<T> result(numDims, m_Dims);
		for (int i = 0; i < m_Size; i++)
			result.m_Data[i] = m_Data[i] - other.m_Data[i];
		return result;
	}
	throw logic_error("Undefined Sum operration");
}

template<typename T>
Tensor<T> Tensor<T>::operator-(unique_ptr<Tensor<T>> other)
{
	if (other->numDims == 1 && numDims == 2 && other->m_Size == this->m_Dims[1])
	{
		// if other is a 1D and this is a 2D tensor
		Tensor<T> result(numDims, m_Dims);
		for (int i = 0; i < this->m_Dims[0]; i++)
			for (int j = 0; j < this->m_Dims[1]; j++)
				result.set(get(i, j) - other->get(j), i, j);
		return result;
	}
	else if (other->numDims == numDims && other->m_Size == m_Size)
	{
		Tensor<T> result(numDims, m_Dims);
		for (int i = 0; i < m_Size; i++)
			result.m_Data[i] = m_Data[i] - other->m_Data[i];
		return result;
	}
	throw logic_error("Undefined Sum operration");
}

template<typename T>
Tensor<T> Tensor<T> ::operator*(T multiplier)
{
	Tensor<T> product(numDims, m_Dims);
	for (int i = 0; i < m_Size; i++)
		product.m_Data[i] = m_Data[i] * multiplier;
	return product;
}

template<typename T>
Tensor<T> Tensor<T> ::operator*(Tensor<T> other2D)
{
	assert(m_Size == other2D.m_Size);
	Tensor<T> product(numDims, m_Dims);
	for (int i = 0; i < m_Size; i++)	
		product.m_Data[i] = m_Data[i] * other2D.m_Data[i];
	return product;
}

template<typename T>
Tensor<T> Tensor<T>::operator*(unique_ptr<Tensor<T>> other2D)
{
	assert(m_Size == other2D->m_Size);
	Tensor<T> product(numDims, m_Dims);
	for (int i = 0; i < m_Size; i++)
		product.m_Data[i] = m_Data[i] * other2D->m_Data[i];
	return product;
}

template<typename T>
Tensor<T> Tensor<T> ::operator/(T divisor)
{
	Tensor<T> result(numDims, m_Dims);
	for (int i = 0; i < m_Size; i++)
		result.m_Data[i] = m_Data[i] / divisor;
	return result;
}

template<typename T>
Tensor<T> Tensor<T> ::operator/(Tensor<T> divisor)
{
	Tensor<T> result(numDims, m_Dims);
	for (int i = 0; i < m_Size; i++)
		result.m_Data[i] = m_Data[i] / divisor.m_Data[i];
	return result;
}

template<typename T>
Tensor<T>& Tensor<T>::operator=(const Tensor<T>& other)
{
	if (this != &other) 
	{
		T* newData = new T[other.m_Size];
		copy(other.m_Data, other.m_Data + other.m_Size, newData);
		if (m_Size != -1)
			delete[] m_Data;

		m_Size = other.m_Size;
		copy(other.m_Dims, other.m_Dims + 4, m_Dims);
		numDims = other.numDims;
		m_Data = newData;
	}

	return *this;
}

template<typename T>
Tensor<T>& Tensor<T>::operator=(const unique_ptr<Tensor<T>>& other)
{
	T* newData = new T[other->m_Size];
	copy(other->m_Data, other->m_Data + other->m_Size, newData);
	if (m_Size != -1)
		delete[] m_Data;

	m_Size = other->m_Size;
	copy(other->m_Dims, other->m_Dims + 4, m_Dims);
	numDims = other->numDims;
	m_Data = newData;
	return *this;
}

template<typename T>
Tensor<T> Tensor<T>::operator-=(Tensor<T> diffrence)
{
	assert(m_Size == diffrence.m_Size);
	for (int i = 0; i < m_Size; i++)
		m_Data[i] = m_Data[i] - diffrence.m_Data[i];
	return *this;
}

template<typename T>
Tensor<T> Tensor<T>::operator-=(unique_ptr<Tensor<T>> difference)
{
	assert(m_Size == difference->m_Size);
	for (int i = 0; i < m_Size; i++)
		m_Data[i] = m_Data[i] - difference->m_Data[i];
	return *this;
}

template<typename T>
Tensor<T> Tensor<T>::operator[](size_t index)
{
	vector<int> vecDims;
	for (size_t i = 1; i < numDims; i++)
	{
		if(m_Dims[i] > 0)
			vecDims.push_back(m_Dims[i]);
	}
	
	int* newDims = &vecDims[0];
	Tensor<T> result(vecDims.size(), newDims);

	for (size_t j = 0; j < newDims[0]; j++)
	{
		if (numDims > 2)
		{
			for (size_t k = 0; k < newDims[1]; k++)
			{
				if (numDims > 3)
				{
					for (size_t l = 0; l < newDims[2]; l++)
					{
						if (numDims > 4)
							throw logic_error("Undefined Axis Operration Excced 4D");
						else
							result.set(get(index, j, k, l), j, k, l);
					}
				}
				else
					result.set(get(index, j, k), j, k);
			}
		}
		else
			result.set(get(index, j), j);
	}
	return result;
}

template<typename T>
Tensor<T> Tensor<T>::endAt(size_t end, int axis)
{
	vector<int> vecDims;
	for (size_t i = 0; i < numDims; i++)
	{
		if(axis==i)
			vecDims.push_back(end);
		else
			vecDims.push_back(m_Dims[i]);
	}

	int* newDims = &vecDims[0];
	Tensor<T> result(numDims, newDims);

	for (size_t i = 0; i < newDims[0]; i++)
	{
		if (numDims >= 2)
		{
			for (size_t j = 0; j < newDims[1]; j++)
			{
				if (result.numDims >= 3)
				{
					for (size_t k = 0; k < newDims[2]; k++)
					{
						if (result.numDims >= 4)
						{
							for (size_t l = 0; l < newDims[3]; l++)
								result.set(get(i, j, k, l), i, j, k, l);
						}
						else
							result.set(get(i, j, k), i, j, k);
					}
				}
				else
					result.set(get(i, j), i, j);
			}
		}
		else
			result.set(get(i), i);
	}
	return result;
}

template<typename T>
Tensor<T> Tensor<T>::pow(int order)
{
	Tensor<T> result(numDims, m_Dims);
	for (size_t i = 0; i < m_Size; i++)
		result.m_Data[i] = std::pow(m_Data[i], order);
	return result;
}

template<typename T>
Tensor<T> Tensor<T> ::ColumnWiseSum()
{
	assert(numDims == 2);
	int rows = m_Dims[0];
	int cols = m_Dims[1];
	int sumDims[] = { cols };
	Tensor<T> sum(1, sumDims);
	for (int i = 0; i < cols; i++)
	{
		T total = 0;
		for (int j = 0; j < rows; j++)		
			total += get(j, i);
		sum.set(total, i);
	}
	return sum;
}

template<typename T>
void Tensor<T>::randn(default_random_engine generator, normal_distribution<double> distribution, double multiplier)
{
	for (int i = 0; i < m_Size; i++)	
		m_Data[i] = distribution(generator) * multiplier;	
}

template<typename T>
Tensor<T> Tensor<T>::ConcatenateAxis0(Tensor<T> other)
{
	assert(numDims == 2 && other.numDims == 2);
	assert(m_Dims[1] == other.m_Dims[1]);

	int newDims[] = { m_Dims[0] + other.m_Dims[0], m_Dims[1] };
	Tensor<T> result(2, newDims);

	for (size_t i = 0; i < m_Dims[0]; i++)
		for (size_t j = 0; j < m_Dims[1]; j++)
			result.set(get(i, j), i, j);

	for (size_t i = 0; i < other.m_Dims[0]; i++)
		for (size_t j = 0; j < other.m_Dims[1]; j++)
			result.set(other.get(i, j), m_Dims[0]+i, j);

	return result;
}

template<typename T>
Tensor<T> Tensor<T>::ConcatenateAxis1(Tensor<T> other)
{
	assert(numDims == 2 && other.numDims == 2);
	assert(m_Dims[0] == other.m_Dims[0]);

	int newDims[] = { m_Dims[0], m_Dims[1] + other.m_Dims[1] };
	Tensor<T> result(2, newDims);

	for (size_t i = 0; i < m_Dims[0]; i++)
	{
		for (size_t j = 0; j < m_Dims[1]; j++)
			result.set(get(i, j), i, j);

		for (size_t j = 0; j < other.m_Dims[1]; j++)
			result.set(other.get(i, j), i, m_Dims[1] + j);
	}		

	return result;
}

template<typename T>
Tensor<T> Tensor<T>::mean2D(int axis)
{
	assert(numDims == 2);
	assert(axis <= 1);

	if (axis == 0)
	{
		int newDims[] = { 1, m_Dims[1]};
		Tensor<T> result(2, newDims);

		for (size_t j = 0; j < m_Dims[1]; j++)
		{
			T sum = 0;
			for (size_t i = 0; i < m_Dims[0]; i++)	
				sum += get(i, j);			

			result.set((double)sum / m_Dims[0], 0, j);
		}
		return result;
	}
	else
	{
		int newDims[] = { m_Dims[0], 1 };
		Tensor<T> result(2, newDims);

		for (size_t i = 0; i < m_Dims[0]; i++)
		{
			T sum = 0;
			for (size_t j = 0; j < m_Dims[1]; j++)
				sum += get(i, j);

			result.set((double)sum / m_Dims[1], i, 0);
		}
		return result;
	}
}

template<typename T>
Tensor<size_t> Tensor<T>::argmax(int axis)
{
	assert(numDims == 2);
	assert(axis <= 1);

	if (axis == 0)
	{
		int newDims[] = { 1, m_Dims[1] };
		Tensor<size_t> result(2, newDims);

		double maxValue = -DBL_MAX;
		for (size_t j = 0; j < m_Dims[1]; j++)
		{
			size_t maxIndex = 0;
			for (size_t i = 0; i < m_Dims[0]; i++)
			{
				double val = get(i, j);
				if (val > maxValue)
				{
					maxValue = val;
					maxIndex = i;
				}
			}
			result.set(maxIndex, 0, j);
		}
		return result;
	}
	else
	{
		int newDims[] = { m_Dims[0], 1 };
		Tensor<size_t> result(2, newDims);

		double maxValue = -DBL_MAX;
		for (size_t i = 0; i < m_Dims[0]; i++)
		{
			size_t maxIndex = 0;
			for (size_t j = 0; j < m_Dims[1]; j++)
			{
				double val = get(i, j);
				if (val > maxValue)
				{
					maxValue = val;
					maxIndex = j;
				}
			}
			result.set(maxIndex, i, 0);
		}
		return result;
	}
}

template<typename T>
Tensor<T> Tensor<T>::log()
{
	Tensor<T> result(numDims, m_Dims);
	for (int i = 0; i < m_Size; i++)
		result.m_Data[i] = std::log(m_Data[i]);
	return result;
}

template<typename T>
Tensor<T> Tensor<T>::exp()
{
	Tensor<T> result(numDims, m_Dims);
	for (int i = 0; i < m_Size; i++)
		result.m_Data[i] = std::exp(m_Data[i]);
	return result;
}

template<typename T>
void Tensor<T>::print()
{
	if (numDims == 2)
	{
		int rows = m_Dims[0];
		int cols = m_Dims[1];
		cout << "Tensor2D (" << rows << ", " << cols << ")\n[";
		for (int i = 0; i < rows; i++)
		{
			if (i != 0)
				cout << " ";

			cout << "[";
			for (int j = 0; j < cols; j++)
			{
				if (j == (cols - 1))				
					printf("%.18lf", get(i, j));				
				else
					printf("%.18lf ", get(i, j));
			}
			if(i==(rows-1))
				cout<<"]]\n";
			else
				cout<<"]\n";
		}
	}
	else
	{
		printf("Tensor%dd (", numDims);
		for (int i = 0; i < numDims; i++)
		{
			printf("%d", m_Dims[i]);
			if (i != (numDims - 1))
				printf(",");
		}
		printf(")\n[");
		for (int i = 0; i < m_Size; i++)		
			printf("%lf ", m_Data[i]);

		printf("]\n");
	}
}

