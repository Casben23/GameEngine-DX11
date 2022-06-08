#pragma once
#include "Vector4.hpp"
#include <array>
#include "DX11.h"
namespace CommonUtilities
{
	template<class T>
	class Matrix4x4
	{
	public:
		Matrix4x4<T>();
		Matrix4x4<T>(const Matrix4x4<T>& aMatrix);
		T& operator()(const int aRow, const int aColumn);
		const T& operator()(const int aRow, const int aColumn) const;
		Matrix4x4<T> operator=(const Matrix4x4& aMatrix4x4);
		static Matrix4x4<T> CreateRotationAroundX(T aAngleInRadians);
		static Matrix4x4<T> CreateRotationAroundY(T aAngleInRadians);
		static Matrix4x4<T> CreateRotationAroundZ(T aAngleInRadians);
		static Matrix4x4<T> Transpose(const Matrix4x4<T>& aMatrixToTranspose);
		static Matrix4x4<T> GetFastInverse(const Matrix4x4<T>& aTransform);
	private:
		std::array<std::array<T, 4>, 4> myMatrix;
		// :)
	};

	template <class T>
	Matrix4x4<T>::Matrix4x4()
	{
		myMatrix[0][0] = 1;
		myMatrix[0][1] = 0;
		myMatrix[0][2] = 0;
		myMatrix[0][3] = 0;

		myMatrix[1][0] = 0;
		myMatrix[1][1] = 1;
		myMatrix[1][2] = 0;
		myMatrix[1][3] = 0;

		myMatrix[2][0] = 0;
		myMatrix[2][1] = 0;
		myMatrix[2][2] = 1;
		myMatrix[2][3] = 0;

		myMatrix[3][0] = 0;
		myMatrix[3][1] = 0;
		myMatrix[3][2] = 0;
		myMatrix[3][3] = 1;
	}

	template <class T>
	Matrix4x4<T>::Matrix4x4(const Matrix4x4<T>& aMatrix)
	{
		myMatrix[0][0] = aMatrix(1, 1);
		myMatrix[0][1] = aMatrix(1, 2);
		myMatrix[0][2] = aMatrix(1, 3);
		myMatrix[0][3] = aMatrix(1, 4);

		myMatrix[1][0] = aMatrix(2, 1);
		myMatrix[1][1] = aMatrix(2, 2);
		myMatrix[1][2] = aMatrix(2, 3);
		myMatrix[1][3] = aMatrix(2, 4);

		myMatrix[2][0] = aMatrix(3, 1);
		myMatrix[2][1] = aMatrix(3, 2);
		myMatrix[2][2] = aMatrix(3, 3);
		myMatrix[2][3] = aMatrix(3, 4);

		myMatrix[3][0] = aMatrix(4, 1);
		myMatrix[3][1] = aMatrix(4, 2);
		myMatrix[3][2] = aMatrix(4, 3);
		myMatrix[3][3] = aMatrix(4, 4);
	}

	template <class T>
	T& Matrix4x4<T>::operator()(const int aRow, const int aColumn)
	{
		assert(aRow <= 4 && aColumn <= 4 && aRow > 0 && aColumn > 0);
		return myMatrix[aRow - 1][aColumn - 1];
	}

	template <class T>
	const T& Matrix4x4<T>::operator()(const int aRow, const int aColumn) const
	{
		assert(aRow <= 4 && aColumn <= 4 && aRow > 0 && aColumn > 0);
		return myMatrix[aRow - 1][aColumn - 1];
	}

	template <class T>
	Matrix4x4<T> Matrix4x4<T>::operator=(const Matrix4x4& aMatrix4x4)
	{
		myMatrix[0][0] = aMatrix4x4(1, 1);
		myMatrix[0][1] = aMatrix4x4(1, 2);
		myMatrix[0][2] = aMatrix4x4(1, 3);
		myMatrix[0][3] = aMatrix4x4(1, 4);
		myMatrix[1][0] = aMatrix4x4(2, 1);
		myMatrix[1][1] = aMatrix4x4(2, 2);
		myMatrix[1][2] = aMatrix4x4(2, 3);
		myMatrix[1][3] = aMatrix4x4(2, 4);
		myMatrix[2][0] = aMatrix4x4(3, 1);
		myMatrix[2][1] = aMatrix4x4(3, 2);
		myMatrix[2][2] = aMatrix4x4(3, 3);
		myMatrix[2][3] = aMatrix4x4(3, 4);
		myMatrix[3][0] = aMatrix4x4(4, 1);
		myMatrix[3][1] = aMatrix4x4(4, 2);
		myMatrix[3][2] = aMatrix4x4(4, 3);
		myMatrix[3][3] = aMatrix4x4(4, 4);

		return *this;
	}

	template <class T>
	bool operator==(const Matrix4x4<T>& aMatrix4x4Zero, const Matrix4x4<T>& aMatrix4x4One)
	{
		for(int i = 1; i < 5; i++)
		{
			for (int j = 1; j < 5; j++)
			{
				if (aMatrix4x4Zero(i, j) != aMatrix4x4One(i, j))
				{
					return false;
				}
			}
		}

		return true;
	}

	template <class T>
	Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundX(T aAngleInRadians)
	{
		Matrix4x4<T> tempMatrix4x4;

		tempMatrix4x4(1, 1) = 1;
		tempMatrix4x4(1, 2) = 0;
		tempMatrix4x4(1, 3) = 0;
		tempMatrix4x4(1, 4) = 0;				  
		tempMatrix4x4(2, 1) = 0;
		tempMatrix4x4(2, 2) = cos(aAngleInRadians);
		tempMatrix4x4(2, 3) = sin(aAngleInRadians);
		tempMatrix4x4(2, 4) = 0;			  
		tempMatrix4x4(3, 1) = 0;
		tempMatrix4x4(3, 2) = -sin(aAngleInRadians);
		tempMatrix4x4(3, 3) = cos(aAngleInRadians);
		tempMatrix4x4(3, 4) = 0;
		tempMatrix4x4(4, 1) = 0;
		tempMatrix4x4(4, 2) = 0;
		tempMatrix4x4(4, 3) = 0;
		tempMatrix4x4(4, 4) = 1;

		return tempMatrix4x4;
	}

	template <class T>
	Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundY(T aAngleInRadians)
	{
		Matrix4x4<T> tempMatrix4x4;

		tempMatrix4x4(1, 1) = cos(aAngleInRadians);;
		tempMatrix4x4(1, 2) = 0;
		tempMatrix4x4(1, 3) = -sin(aAngleInRadians);
		tempMatrix4x4(1, 4) = 0;
		tempMatrix4x4(2, 1) = 0;
		tempMatrix4x4(2, 2) = 1;
		tempMatrix4x4(2, 3) = 0;
		tempMatrix4x4(2, 4) = 0;
		tempMatrix4x4(3, 1) = sin(aAngleInRadians);
		tempMatrix4x4(3, 2) = 0;
		tempMatrix4x4(3, 3) = cos(aAngleInRadians);
		tempMatrix4x4(3, 4) = 0;
		tempMatrix4x4(4, 1) = 0;
		tempMatrix4x4(4, 2) = 0;
		tempMatrix4x4(4, 3) = 0;
		tempMatrix4x4(4, 4) = 1;

		return tempMatrix4x4;
	}

	template <class T>
	Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundZ(T aAngleInRadians)
	{
		Matrix4x4<T> tempMatrix4x4;

		tempMatrix4x4(1, 1) = cos(aAngleInRadians);
		tempMatrix4x4(1, 2) = sin(aAngleInRadians);
		tempMatrix4x4(1, 3) = 0;
		tempMatrix4x4(1, 4) = 0;
		tempMatrix4x4(2, 1) = -sin(aAngleInRadians);
		tempMatrix4x4(2, 2) = cos(aAngleInRadians);
		tempMatrix4x4(2, 3) = 0;
		tempMatrix4x4(2, 4) = 0;
		tempMatrix4x4(3, 1) = 0;
		tempMatrix4x4(3, 2) = 0;
		tempMatrix4x4(3, 3) = 1;
		tempMatrix4x4(3, 4) = 0;
		tempMatrix4x4(4, 1) = 0;
		tempMatrix4x4(4, 2) = 0;
		tempMatrix4x4(4, 3) = 0;
		tempMatrix4x4(4, 4) = 1;

		return tempMatrix4x4;
	}

	template <class T>
	Matrix4x4<T> Matrix4x4<T>::Transpose(const Matrix4x4<T>& aMatrixToTranspose)
	{
		Matrix4x4<T> tempMatrix4x4;

		tempMatrix4x4(1, 1) = aMatrixToTranspose(1, 1);
		tempMatrix4x4(1, 2) = aMatrixToTranspose(2, 1);
		tempMatrix4x4(1, 3) = aMatrixToTranspose(3, 1);
		tempMatrix4x4(1, 4) = aMatrixToTranspose(4, 1);

		tempMatrix4x4(2, 1) = aMatrixToTranspose(1, 2);
		tempMatrix4x4(2, 2) = aMatrixToTranspose(2, 2);
		tempMatrix4x4(2, 3) = aMatrixToTranspose(3, 2);
		tempMatrix4x4(2, 4) = aMatrixToTranspose(4, 2);

		tempMatrix4x4(3, 1) = aMatrixToTranspose(1, 3);
		tempMatrix4x4(3, 2) = aMatrixToTranspose(2, 3);
		tempMatrix4x4(3, 3) = aMatrixToTranspose(3, 3);
		tempMatrix4x4(3, 4) = aMatrixToTranspose(4, 3);

		tempMatrix4x4(4, 1) = aMatrixToTranspose(1, 4);
		tempMatrix4x4(4, 2) = aMatrixToTranspose(2, 4);
		tempMatrix4x4(4, 3) = aMatrixToTranspose(3, 4);
		tempMatrix4x4(4, 4) = aMatrixToTranspose(4, 4);

		return tempMatrix4x4;
	}

	template<class T>
	inline Matrix4x4<T> Matrix4x4<T>::GetFastInverse(const Matrix4x4<T>& aTransform)
	{
		Matrix4x4<T> rotationMatrix;
		for (short i = 1; i <= 3; i++)
		{
			for (short j = 1; j <= 3; j++)
			{
				rotationMatrix(i, j) = aTransform(i, j);
			}
		}

		rotationMatrix = rotationMatrix.Transpose(rotationMatrix);

		Matrix4x4<T> tempMatrix;

		tempMatrix(4, 1) = aTransform(4, 1) * -1;
		tempMatrix(4, 2) = aTransform(4, 2) * -1;
		tempMatrix(4, 3) = aTransform(4, 3) * -1;

		return tempMatrix * rotationMatrix;
	}

	template <class T>
	Matrix4x4<T> operator+(Matrix4x4<T>& aMatrix4x4Zero, const Matrix4x4<T>& aMatrix4x4One)
	{
		Matrix4x4<T> tempMatrix;
		tempMatrix(1, 1) = aMatrix4x4Zero(1, 1) + aMatrix4x4One(1, 1);
		tempMatrix(1, 2) = aMatrix4x4Zero(1, 2) + aMatrix4x4One(1, 2);
		tempMatrix(1, 3) = aMatrix4x4Zero(1, 3) + aMatrix4x4One(1, 3);
		tempMatrix(1, 4) = aMatrix4x4Zero(1, 4) + aMatrix4x4One(1, 4);

		tempMatrix(2, 1) = aMatrix4x4Zero(2, 1) + aMatrix4x4One(2, 1);
		tempMatrix(2, 2) = aMatrix4x4Zero(2, 2) + aMatrix4x4One(2, 2);
		tempMatrix(2, 3) = aMatrix4x4Zero(2, 3) + aMatrix4x4One(2, 3);
		tempMatrix(2, 4) = aMatrix4x4Zero(2, 4) + aMatrix4x4One(2, 4);

		tempMatrix(3, 1) = aMatrix4x4Zero(3, 1) + aMatrix4x4One(3, 1);
		tempMatrix(3, 2) = aMatrix4x4Zero(3, 2) + aMatrix4x4One(3, 2);
		tempMatrix(3, 3) = aMatrix4x4Zero(3, 3) + aMatrix4x4One(3, 3);
		tempMatrix(3, 4) = aMatrix4x4Zero(3, 4) + aMatrix4x4One(3, 4);

		tempMatrix(4, 1) = aMatrix4x4Zero(4, 1) + aMatrix4x4One(4, 1);
		tempMatrix(4, 2) = aMatrix4x4Zero(4, 2) + aMatrix4x4One(4, 2);
		tempMatrix(4, 3) = aMatrix4x4Zero(4, 3) + aMatrix4x4One(4, 3);
		tempMatrix(4, 4) = aMatrix4x4Zero(4, 4) + aMatrix4x4One(4, 4);

		return tempMatrix;
	}

	template <class T>
	void operator+=(Matrix4x4<T>& aMatrix4x4Zero, const Matrix4x4<T>& aMatrix4x4One)
	{
		aMatrix4x4Zero(1, 1) += aMatrix4x4One(1, 1);
		aMatrix4x4Zero(1, 2) += aMatrix4x4One(1, 2);
		aMatrix4x4Zero(1, 3) += aMatrix4x4One(1, 3);
		aMatrix4x4Zero(1, 4) += aMatrix4x4One(1, 4);
							  
		aMatrix4x4Zero(2, 1) += aMatrix4x4One(2, 1);
		aMatrix4x4Zero(2, 2) += aMatrix4x4One(2, 2);
		aMatrix4x4Zero(2, 3) += aMatrix4x4One(2, 3);
		aMatrix4x4Zero(2, 4) += aMatrix4x4One(2, 4);
							  
		aMatrix4x4Zero(3, 1) += aMatrix4x4One(3, 1);
		aMatrix4x4Zero(3, 2) += aMatrix4x4One(3, 2);
		aMatrix4x4Zero(3, 3) += aMatrix4x4One(3, 3);
		aMatrix4x4Zero(3, 4) += aMatrix4x4One(3, 4);
							  
		aMatrix4x4Zero(4, 1) += aMatrix4x4One(4, 1);
		aMatrix4x4Zero(4, 2) += aMatrix4x4One(4, 2);
		aMatrix4x4Zero(4, 3) += aMatrix4x4One(4, 3);
		aMatrix4x4Zero(4, 4) += aMatrix4x4One(4, 4);
	}

	template <class T>
	Matrix4x4<T> operator-(Matrix4x4<T>& aMatrix4x4Zero, const Matrix4x4<T>& aMatrix4x4One)
	{
		Matrix4x4<T> tempMatrix;
		tempMatrix(1, 1) = aMatrix4x4Zero(1, 1) - aMatrix4x4One(1, 1);
		tempMatrix(1, 2) = aMatrix4x4Zero(1, 2) - aMatrix4x4One(1, 2);
		tempMatrix(1, 3) = aMatrix4x4Zero(1, 3) - aMatrix4x4One(1, 3);
		tempMatrix(1, 4) = aMatrix4x4Zero(1, 4) - aMatrix4x4One(1, 4);
											    
		tempMatrix(2, 1) = aMatrix4x4Zero(2, 1) - aMatrix4x4One(2, 1);
		tempMatrix(2, 2) = aMatrix4x4Zero(2, 2) - aMatrix4x4One(2, 2);
		tempMatrix(2, 3) = aMatrix4x4Zero(2, 3) - aMatrix4x4One(2, 3);
		tempMatrix(2, 4) = aMatrix4x4Zero(2, 4) - aMatrix4x4One(2, 4);
											    
		tempMatrix(3, 1) = aMatrix4x4Zero(3, 1) - aMatrix4x4One(3, 1);
		tempMatrix(3, 2) = aMatrix4x4Zero(3, 2) - aMatrix4x4One(3, 2);
		tempMatrix(3, 3) = aMatrix4x4Zero(3, 3) - aMatrix4x4One(3, 3);
		tempMatrix(3, 4) = aMatrix4x4Zero(3, 4) - aMatrix4x4One(3, 4);
											    
		tempMatrix(4, 1) = aMatrix4x4Zero(4, 1) - aMatrix4x4One(4, 1);
		tempMatrix(4, 2) = aMatrix4x4Zero(4, 2) - aMatrix4x4One(4, 2);
		tempMatrix(4, 3) = aMatrix4x4Zero(4, 3) - aMatrix4x4One(4, 3);
		tempMatrix(4, 4) = aMatrix4x4Zero(4, 4) - aMatrix4x4One(4, 4);

		return tempMatrix;
	}

	template <class T>
	void operator-=(Matrix4x4<T>& aMatrix4x4Zero, const Matrix4x4<T>& aMatrix4x4One)
	{
		aMatrix4x4Zero(1, 1) -= aMatrix4x4One(1, 1);
		aMatrix4x4Zero(1, 2) -= aMatrix4x4One(1, 2);
		aMatrix4x4Zero(1, 3) -= aMatrix4x4One(1, 3);
		aMatrix4x4Zero(1, 4) -= aMatrix4x4One(1, 4);
							 
		aMatrix4x4Zero(2, 1) -= aMatrix4x4One(2, 1);
		aMatrix4x4Zero(2, 2) -= aMatrix4x4One(2, 2);
		aMatrix4x4Zero(2, 3) -= aMatrix4x4One(2, 3);
		aMatrix4x4Zero(2, 4) -= aMatrix4x4One(2, 4);
							 
		aMatrix4x4Zero(3, 1) -= aMatrix4x4One(3, 1);
		aMatrix4x4Zero(3, 2) -= aMatrix4x4One(3, 2);
		aMatrix4x4Zero(3, 3) -= aMatrix4x4One(3, 3);
		aMatrix4x4Zero(3, 4) -= aMatrix4x4One(3, 4);
							 
		aMatrix4x4Zero(4, 1) -= aMatrix4x4One(4, 1);
		aMatrix4x4Zero(4, 2) -= aMatrix4x4One(4, 2);
		aMatrix4x4Zero(4, 3) -= aMatrix4x4One(4, 3);
		aMatrix4x4Zero(4, 4) -= aMatrix4x4One(4, 4);
	}

	template<class T>
	Matrix4x4<T> operator*(const Matrix4x4<T>& aMatrix4x4Zero, const Matrix4x4<T>& aMatrix4x4One)
	{
		Matrix4x4<T> tempMatrix;

		tempMatrix(1, 1) = (aMatrix4x4Zero(1, 1) * aMatrix4x4One(1, 1)) + (aMatrix4x4Zero(1, 2) * aMatrix4x4One(2, 1)) + (aMatrix4x4Zero(1, 3) * aMatrix4x4One(3, 1)) + (aMatrix4x4Zero(1, 4) * aMatrix4x4One(4, 1));
		tempMatrix(1, 2) = (aMatrix4x4Zero(1, 1) * aMatrix4x4One(1, 2)) + (aMatrix4x4Zero(1, 2) * aMatrix4x4One(2, 2)) + (aMatrix4x4Zero(1, 3) * aMatrix4x4One(3, 2)) + (aMatrix4x4Zero(1, 4) * aMatrix4x4One(4, 2));
		tempMatrix(1, 3) = (aMatrix4x4Zero(1, 1) * aMatrix4x4One(1, 3)) + (aMatrix4x4Zero(1, 2) * aMatrix4x4One(2, 3)) + (aMatrix4x4Zero(1, 3) * aMatrix4x4One(3, 3)) + (aMatrix4x4Zero(1, 4) * aMatrix4x4One(4, 3));
		tempMatrix(1, 4) = (aMatrix4x4Zero(1, 1) * aMatrix4x4One(1, 4)) + (aMatrix4x4Zero(1, 2) * aMatrix4x4One(2, 4)) + (aMatrix4x4Zero(1, 3) * aMatrix4x4One(3, 4)) + (aMatrix4x4Zero(1, 4) * aMatrix4x4One(4, 4));

		tempMatrix(2, 1) = aMatrix4x4Zero(2, 1) * aMatrix4x4One(1, 1) + aMatrix4x4Zero(2, 2) * aMatrix4x4One(2, 1) + aMatrix4x4Zero(2, 3) * aMatrix4x4One(3, 1) + aMatrix4x4Zero(2, 4) * aMatrix4x4One(4, 1);
		tempMatrix(2, 2) = aMatrix4x4Zero(2, 1) * aMatrix4x4One(1, 2) + aMatrix4x4Zero(2, 2) * aMatrix4x4One(2, 2) + aMatrix4x4Zero(2, 3) * aMatrix4x4One(3, 2) + aMatrix4x4Zero(2, 4) * aMatrix4x4One(4, 2);
		tempMatrix(2, 3) = aMatrix4x4Zero(2, 1) * aMatrix4x4One(1, 3) + aMatrix4x4Zero(2, 2) * aMatrix4x4One(2, 3) + aMatrix4x4Zero(2, 3) * aMatrix4x4One(3, 3) + aMatrix4x4Zero(2, 4) * aMatrix4x4One(4, 3);
		tempMatrix(2, 4) = aMatrix4x4Zero(2, 1) * aMatrix4x4One(1, 4) + aMatrix4x4Zero(2, 2) * aMatrix4x4One(2, 4) + aMatrix4x4Zero(2, 3) * aMatrix4x4One(3, 4) + aMatrix4x4Zero(2, 4) * aMatrix4x4One(4, 4);

		tempMatrix(3, 1) = aMatrix4x4Zero(3, 1) * aMatrix4x4One(1, 1) + aMatrix4x4Zero(3, 2) * aMatrix4x4One(2, 1) + aMatrix4x4Zero(3, 3) * aMatrix4x4One(3, 1) + aMatrix4x4Zero(3, 4) * aMatrix4x4One(4, 1);
		tempMatrix(3, 2) = aMatrix4x4Zero(3, 1) * aMatrix4x4One(1, 2) + aMatrix4x4Zero(3, 2) * aMatrix4x4One(2, 2) + aMatrix4x4Zero(3, 3) * aMatrix4x4One(3, 2) + aMatrix4x4Zero(3, 4) * aMatrix4x4One(4, 2);
		tempMatrix(3, 3) = aMatrix4x4Zero(3, 1) * aMatrix4x4One(1, 3) + aMatrix4x4Zero(3, 2) * aMatrix4x4One(2, 3) + aMatrix4x4Zero(3, 3) * aMatrix4x4One(3, 3) + aMatrix4x4Zero(3, 4) * aMatrix4x4One(4, 3);
		tempMatrix(3, 4) = aMatrix4x4Zero(3, 1) * aMatrix4x4One(1, 4) + aMatrix4x4Zero(3, 2) * aMatrix4x4One(2, 4) + aMatrix4x4Zero(3, 3) * aMatrix4x4One(3, 4) + aMatrix4x4Zero(3, 4) * aMatrix4x4One(4, 4);

		tempMatrix(4, 1) = aMatrix4x4Zero(4, 1) * aMatrix4x4One(1, 1) + aMatrix4x4Zero(4, 2) * aMatrix4x4One(2, 1) + aMatrix4x4Zero(4, 3) * aMatrix4x4One(3, 1) + aMatrix4x4Zero(4, 4) * aMatrix4x4One(4, 1);
		tempMatrix(4, 2) = aMatrix4x4Zero(4, 1) * aMatrix4x4One(1, 2) + aMatrix4x4Zero(4, 2) * aMatrix4x4One(2, 2) + aMatrix4x4Zero(4, 3) * aMatrix4x4One(3, 2) + aMatrix4x4Zero(4, 4) * aMatrix4x4One(4, 2);
		tempMatrix(4, 3) = aMatrix4x4Zero(4, 1) * aMatrix4x4One(1, 3) + aMatrix4x4Zero(4, 2) * aMatrix4x4One(2, 3) + aMatrix4x4Zero(4, 3) * aMatrix4x4One(3, 3) + aMatrix4x4Zero(4, 4) * aMatrix4x4One(4, 3);
		tempMatrix(4, 4) = aMatrix4x4Zero(4, 1) * aMatrix4x4One(1, 4) + aMatrix4x4Zero(4, 2) * aMatrix4x4One(2, 4) + aMatrix4x4Zero(4, 3) * aMatrix4x4One(3, 4) + aMatrix4x4Zero(4, 4) * aMatrix4x4One(4, 4);

		return tempMatrix;
	}

	template<class T>
	void operator*=(Matrix4x4<T>& aMatrix4x4Zero, const Matrix4x4<T>& aMatrix4x4One)
	{
		Matrix4x4<T> tempMatrix;

		tempMatrix(1, 1) = (aMatrix4x4Zero(1, 1) * aMatrix4x4One(1, 1)) + (aMatrix4x4Zero(1, 2) * aMatrix4x4One(2, 1)) + (aMatrix4x4Zero(1, 3) * aMatrix4x4One(3, 1)) + (aMatrix4x4Zero(1, 4) * aMatrix4x4One(4, 1));
		tempMatrix(1, 2) = (aMatrix4x4Zero(1, 1) * aMatrix4x4One(1, 2)) + (aMatrix4x4Zero(1, 2) * aMatrix4x4One(2, 2)) + (aMatrix4x4Zero(1, 3) * aMatrix4x4One(3, 2)) + (aMatrix4x4Zero(1, 4) * aMatrix4x4One(4, 2));
		tempMatrix(1, 3) = (aMatrix4x4Zero(1, 1) * aMatrix4x4One(1, 3)) + (aMatrix4x4Zero(1, 2) * aMatrix4x4One(2, 3)) + (aMatrix4x4Zero(1, 3) * aMatrix4x4One(3, 3)) + (aMatrix4x4Zero(1, 4) * aMatrix4x4One(4, 3));
		tempMatrix(1, 4) = (aMatrix4x4Zero(1, 1) * aMatrix4x4One(1, 4)) + (aMatrix4x4Zero(1, 2) * aMatrix4x4One(2, 4)) + (aMatrix4x4Zero(1, 3) * aMatrix4x4One(3, 4)) + (aMatrix4x4Zero(1, 4) * aMatrix4x4One(4, 4));

		tempMatrix(2, 1) = aMatrix4x4Zero(2, 1) * aMatrix4x4One(1, 1) + aMatrix4x4Zero(2, 2) * aMatrix4x4One(2, 1) + aMatrix4x4Zero(2, 3) * aMatrix4x4One(3, 1) + aMatrix4x4Zero(2, 4) * aMatrix4x4One(4, 1);
		tempMatrix(2, 2) = aMatrix4x4Zero(2, 1) * aMatrix4x4One(1, 2) + aMatrix4x4Zero(2, 2) * aMatrix4x4One(2, 2) + aMatrix4x4Zero(2, 3) * aMatrix4x4One(3, 2) + aMatrix4x4Zero(2, 4) * aMatrix4x4One(4, 2);
		tempMatrix(2, 3) = aMatrix4x4Zero(2, 1) * aMatrix4x4One(1, 3) + aMatrix4x4Zero(2, 2) * aMatrix4x4One(2, 3) + aMatrix4x4Zero(2, 3) * aMatrix4x4One(3, 3) + aMatrix4x4Zero(2, 4) * aMatrix4x4One(4, 3);
		tempMatrix(2, 4) = aMatrix4x4Zero(2, 1) * aMatrix4x4One(1, 4) + aMatrix4x4Zero(2, 2) * aMatrix4x4One(2, 4) + aMatrix4x4Zero(2, 3) * aMatrix4x4One(3, 4) + aMatrix4x4Zero(2, 4) * aMatrix4x4One(4, 4);

		tempMatrix(3, 1) = aMatrix4x4Zero(3, 1) * aMatrix4x4One(1, 1) + aMatrix4x4Zero(3, 2) * aMatrix4x4One(2, 1) + aMatrix4x4Zero(3, 3) * aMatrix4x4One(3, 1) + aMatrix4x4Zero(3, 4) * aMatrix4x4One(4, 1);
		tempMatrix(3, 2) = aMatrix4x4Zero(3, 1) * aMatrix4x4One(1, 2) + aMatrix4x4Zero(3, 2) * aMatrix4x4One(2, 2) + aMatrix4x4Zero(3, 3) * aMatrix4x4One(3, 2) + aMatrix4x4Zero(3, 4) * aMatrix4x4One(4, 2);
		tempMatrix(3, 3) = aMatrix4x4Zero(3, 1) * aMatrix4x4One(1, 3) + aMatrix4x4Zero(3, 2) * aMatrix4x4One(2, 3) + aMatrix4x4Zero(3, 3) * aMatrix4x4One(3, 3) + aMatrix4x4Zero(3, 4) * aMatrix4x4One(4, 3);
		tempMatrix(3, 4) = aMatrix4x4Zero(3, 1) * aMatrix4x4One(1, 4) + aMatrix4x4Zero(3, 2) * aMatrix4x4One(2, 4) + aMatrix4x4Zero(3, 3) * aMatrix4x4One(3, 4) + aMatrix4x4Zero(3, 4) * aMatrix4x4One(4, 4);

		tempMatrix(4, 1) = aMatrix4x4Zero(4, 1) * aMatrix4x4One(1, 1) + aMatrix4x4Zero(4, 2) * aMatrix4x4One(2, 1) + aMatrix4x4Zero(4, 3) * aMatrix4x4One(3, 1) + aMatrix4x4Zero(4, 4) * aMatrix4x4One(4, 1);
		tempMatrix(4, 2) = aMatrix4x4Zero(4, 1) * aMatrix4x4One(1, 2) + aMatrix4x4Zero(4, 2) * aMatrix4x4One(2, 2) + aMatrix4x4Zero(4, 3) * aMatrix4x4One(3, 2) + aMatrix4x4Zero(4, 4) * aMatrix4x4One(4, 2);
		tempMatrix(4, 3) = aMatrix4x4Zero(4, 1) * aMatrix4x4One(1, 3) + aMatrix4x4Zero(4, 2) * aMatrix4x4One(2, 3) + aMatrix4x4Zero(4, 3) * aMatrix4x4One(3, 3) + aMatrix4x4Zero(4, 4) * aMatrix4x4One(4, 3);
		tempMatrix(4, 4) = aMatrix4x4Zero(4, 1) * aMatrix4x4One(1, 4) + aMatrix4x4Zero(4, 2) * aMatrix4x4One(2, 4) + aMatrix4x4Zero(4, 3) * aMatrix4x4One(3, 4) + aMatrix4x4Zero(4, 4) * aMatrix4x4One(4, 4);
		aMatrix4x4Zero = tempMatrix;
	}

	template <class T>
	Vector4<T> operator*(const Vector4<T>& aVector4, const Matrix4x4<T>& aMatrix4x4)
	{
		Vector4<T> tempVector;

		tempVector.x = aVector4.x * aMatrix4x4(1, 1) + aVector4.y * aMatrix4x4(2, 1) + aVector4.z * aMatrix4x4(3, 1) + aVector4.w * aMatrix4x4(4, 1);
		tempVector.y = aVector4.x * aMatrix4x4(1, 2) + aVector4.y * aMatrix4x4(2, 2) + aVector4.z * aMatrix4x4(3, 2) + aVector4.w * aMatrix4x4(4, 2);
		tempVector.z = aVector4.x * aMatrix4x4(1, 3) + aVector4.y * aMatrix4x4(2, 3) + aVector4.z * aMatrix4x4(3, 3) + aVector4.w * aMatrix4x4(4, 3);
		tempVector.w = aVector4.x * aMatrix4x4(1, 4) + aVector4.y * aMatrix4x4(2, 4) + aVector4.z * aMatrix4x4(3, 4) + aVector4.w * aMatrix4x4(4, 4);

		return tempVector;
	}
}


typedef CommonUtilities::Matrix4x4<float> Matrix4x4f;