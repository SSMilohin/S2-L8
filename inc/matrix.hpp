#pragma once
#include <iostream>

namespace sm::math
{
	template<typename T, int N, int M>
	struct MasWrapper
	{
		T mas[N][M];
	};

	template<typename T, int N, int M>
	class Matrix
	{
	public:
		Matrix()
		{
			m_n = N;
			m_m = M;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = 0;
		}

		Matrix(const T mas[N][M])
		{
			m_n = N;
			m_m = M;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mas[i][j];
		}

		Matrix(const MasWrapper<T, N, M>& mas)
		{
			m_n = N;
			m_m = M;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mas.mas[i][j];
		}

		Matrix(const Matrix<T, N, M>& mat)
		{
			m_n = mat.m_n;
			m_m = mat.m_m;

			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mat.m_mat[i][j];
		}

		int getN() const { return m_n; }
		int getM() const { return m_m; }
		T get(int i, int j) const { return m_mat[i][j]; }
		void set(int i, int j, T data) { m_mat[i][j] = data; }

		Matrix<T, N, M>& operator=(const Matrix<T, N, M>& mat)
		{
			m_n = mat.m_n;
			m_m = mat.m_m;

			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mat.m_mat[i][j];

			return *this;
		}

		Matrix<T, N, M> operator+(const Matrix<T, N, M>& mat)
		{
			Matrix<T, N, M> tmp;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					tmp.m_mat[i][j] = m_mat[i][j] + mat.m_mat[i][j];
			return tmp;
		}

		Matrix<T, N, M> operator+=(const Matrix<T, N, M>& mat) {
			m_n = mat.m_n;
			m_m = mat.m_m;

			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] += mat.m_mat[i][j];

			return *this;
		}

		Matrix<T, N, M> operator-(const Matrix<T, N, M>& mat)
		{
			Matrix<T, N, M> tmp;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					tmp.m_mat[i][j] = m_mat[i][j] - mat.m_mat[i][j];
			return tmp;
		}

		template<int L>
		Matrix<T, N, L> operator*(const Matrix<T, M, L>& mat)
		{
			Matrix<T, N, L> tmp;
			for (int i = 0; i < m_n; i++) {
				for (int j = 0; j < mat.getM(); j++) {
					T sum = 0;
					for (int k = 0; k < m_m; k++)
						sum += m_mat[i][k] * mat.get(k,j);
					tmp.set(i, j, sum);
				}
			}
			return tmp;
		}

		double determinant() {
			if (m_n != m_m || m_n > 3) throw std::exception("The operation is not supported!");
			if (m_n == 2) return m_mat[0][0] * m_mat[1][1] - m_mat[0][1] * m_mat[1][0];
			if (m_n == 3) return m_mat[0][0] * m_mat[1][1] * m_mat[2][2]
				+ m_mat[0][1] * m_mat[1][2] * m_mat[2][0]
				+ m_mat[1][0] * m_mat[2][1] * m_mat[0][2]
				- m_mat[2][0] * m_mat[1][1] * m_mat[0][2]
				- m_mat[2][1] * m_mat[1][2] * m_mat[0][0]
				- m_mat[1][0] * m_mat[0][1] * m_mat[2][2];
		}
		
		Matrix<T, M, N> transpose() {
			Matrix<T, M, N> tr_mat;
			for (int i = 0; i < m_n; i++) {
				for (int j = 0; j < m_m; j++) {
					tr_mat.m_mat[i][j] = m_mat[j][i];
				}
			}
			return tr_mat;
		}

		Matrix<T, M, N> inversion() {
			if (m_n != m_m) throw std::exception("This operation is only available for square matrixes.");
			if (m_n > 3) throw std::exception("The operation is not supported.");

			int det = determinant();
			if (det == 0) throw std::exception("Matrix has no inverse.");

			Matrix<T, M, N> tmp;
			if (m_n == 2)
			{
				tmp.m_mat[0][0] = m_mat[1][1] / det;
				tmp.m_mat[0][1] = -m_mat[0][1] / det;
				tmp.m_mat[1][0] = -m_mat[1][0] / det;
				tmp.m_mat[1][1] = m_mat[0][0] / det;
				return tmp;
			}
			if (m_n == 3) {
				tmp.m_mat[0][0] = (m_mat[1][1] * m_mat[2][2] - m_mat[2][1] * m_mat[1][2]) / det;
				tmp.m_mat[1][0] = -(m_mat[1][0] * m_mat[2][2] - m_mat[2][0] * m_mat[1][2]) / det;
				tmp.m_mat[2][0] = (m_mat[1][0] * m_mat[2][1] - m_mat[2][0] * m_mat[1][1]) / det;
				tmp.m_mat[0][1] = -(m_mat[0][1] * m_mat[2][2] - m_mat[2][1] * m_mat[0][2]) / det;
				tmp.m_mat[1][1] = (m_mat[0][0] * m_mat[2][2] - m_mat[2][0] * m_mat[0][2]) / det;
				tmp.m_mat[2][1] = -(m_mat[0][0] * m_mat[2][1] - m_mat[2][0] * m_mat[0][1]) / det;
				tmp.m_mat[0][2] = (m_mat[0][1] * m_mat[1][2] - m_mat[1][1] * m_mat[0][2]) / det;
				tmp.m_mat[1][2] = -(m_mat[0][0] * m_mat[1][2] - m_mat[1][0] * m_mat[0][2]) / det;
				tmp.m_mat[2][2] = (m_mat[0][0] * m_mat[1][1] - m_mat[1][0] * m_mat[0][1]) / det;
				return tmp;
			}
		}

		~Matrix() {}

		template<typename T, int N, int M>
		friend std::istream& operator>>(std::istream& os, Matrix<T, N, M>& mat);
		template<typename T, int N, int M>
		friend std::ostream& operator<<(std::ostream& os, const Matrix<T, N, M>& mat);

	private:
		int m_n, m_m;
		T m_mat[N][M];
	};

	template<typename T, int N, int M>
	std::istream& operator>>(std::istream& in, Matrix<T, N, M>& mat)
	{
		for (int i = 0; i < mat.m_n; i++)
			for (int j = 0; j < mat.m_m; j++)
				in >> mat.m_mat[i][j];
		return in;
	}

	template<typename T, int N, int M>
	std::ostream& operator<<(std::ostream& out, const Matrix<T, N, M>& mat)
	{
		out << "Matrix " << mat.m_n << "x" << mat.m_m << std::endl;
		for (int i = 0; i < mat.m_n; i++) {
			for (int j = 0; j < mat.m_m; j++)
				out << mat.m_mat[i][j] << " ";
			out << std::endl;
		}
		return out;
	}
}
