/*
* Лабораторная работа №8 (2 семестр)
*  
* Возьмите за основу репозиторий mathutils.
* Методы должны быть шаблонными.
* На каждый метод или оператор напишите по одному тесту(пример теста есть в main.cpp в репозитории mathutils).
*/

#include <iostream>
#include <cassert>
#include "inc/matrix.hpp"

using namespace sm::math;

int main()
{
	std::cout << "=== Test (operator=) ===" << std::endl;
	{
		Matrix<int, 2, 2> A({{
			{1,2},
			{3,4}
		}});
		auto B = A;
		assert(B.get(0, 0) == 1);
		assert(B.get(0, 1) == 2);
		assert(B.get(1, 0) == 3);
		assert(B.get(1, 1) == 4);
	}
	std::cout << "Done!" << std::endl;

	std::cout << "=== Test (operator+) ===" << std::endl;
	{
		Matrix<int, 2, 2> A({{
			{1,2},
			{3,4}
		}});
		Matrix<int, 2, 2> B({{
			{3,3},
			{3,3}
		}});
		auto C = A + B;
		assert(C.get(0, 0) == 4);
		assert(C.get(0, 1) == 5);
		assert(C.get(1, 0) == 6);
		assert(C.get(1, 1) == 7);
	}
	std::cout << "Done!" << std::endl;

	std::cout << "=== Test (operator+=) ===" << std::endl;
	{
		Matrix<int, 2, 2> A({{
			{1,2},
			{3,4}
		}});
		Matrix<int, 2, 2> B({{
			{3,3},
			{3,3}
		}});
		B += A;
		assert(B.get(0, 0) == 4);
		assert(B.get(0, 1) == 5);
		assert(B.get(1, 0) == 6);
		assert(B.get(1, 1) == 7);
	}
	std::cout << "Done!" << std::endl;

	std::cout << "=== Test (operator-) ===" << std::endl;
	{
		Matrix<int, 2, 2> A({ {
			{1,2},
			{3,4}
		} });
		Matrix<int, 2, 2> B({ {
			{3,3},
			{3,3}
		} });
		auto C = B - A; 
		assert(C.get(0, 0) == 2);
		assert(C.get(0, 1) == 1);
		assert(C.get(1, 0) == 0);
		assert(C.get(1, 1) == -1);
	}
	std::cout << "Done!" << std::endl;

	std::cout << "=== Test (operator*) ===" << std::endl;
	{
		Matrix<double, 2, 4> A({{
			{1,2,3,5},
			{3,4,4,3}
		}});
		Matrix<double, 4, 1> B({{
			{2},
			{1},
			{1},
			{4}
		}});
		auto C = A * B;
		assert(C.get(0, 0) == 27);
		assert(C.get(1, 0) == 26);
	}
	std::cout << "Done!" << std::endl;

	std::cout << "=== Test (determinant) ===" << std::endl;
	{
		Matrix<double, 3, 3> A({{
			{1,2,3},
			{3,4,4},
			{4,2,1}
		}});
		assert(A.determinant() == -8);
	}
	std::cout << "Done!" << std::endl;

	std::cout << "=== Test (transpose) ===" << std::endl;
	{
		Matrix<double, 3, 3> A({{
			{1,2,3},
			{3,4,4},
			{4,2,1}
		}});
		auto B = A.transpose();
		assert(B.get(2,1) == 4);
		assert(B.get(0, 1) == 3);
	}
	std::cout << "Done!" << std::endl;

	std::cout << "=== Test (inversion) ===" << std::endl;
	{
		Matrix<double, 3, 3> A({{
			{1,2,3},
			{3,4,4},
			{4,2,1}
		}});
		auto B = A.inversion();
		assert(B.get(0, 0) == 0.5);
		assert(B.get(0, 1) == -0.5);
	}
	std::cout << "Done!" << std::endl;

	return 0;
}