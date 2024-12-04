#include "utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix)
{
  TMatrix<int> m(5);

  ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
	int size = 3;
	TMatrix<int> a(size);
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			a[i][j] = i + j;
		}
	}

	TMatrix<int> a_copy(a);

	EXPECT_EQ(a, a_copy);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	int size = 3;
	TMatrix<int> a(size);
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			a[i][j] = i + j;
		}
	}

	TMatrix<int> a_copy(a);

	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			a[i][j] = (i + j) * 2;
		}
	}

	EXPECT_NE(a, a_copy);
}

TEST(TMatrix, can_get_size)
{
	int size = 3;
	TMatrix<int> a(size);
	
	EXPECT_EQ(size, a.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
	int size = 3;
	TMatrix<int> a(size);

	ASSERT_NO_THROW(a[0][0] = 4);

	EXPECT_EQ(4, a[0][0]);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	int size = 3;
	TMatrix<int> a(size);

	ASSERT_ANY_THROW(a[-1][-1] = 4);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	int size = 3;
	TMatrix<int> a(size);

	ASSERT_ANY_THROW(a[4][4] = 4);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	int size = 3;
	TMatrix<int> a(size);
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			a[i][j] = i + j;
		}
	}

	TMatrix<int> a_copy(a);

	ASSERT_NO_THROW(a = a);
	EXPECT_EQ(a, a_copy);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	int size = 3;
	TMatrix<int> a(size), b(size);
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			a[i][j] = i + j;
		}
	}

	ASSERT_NO_THROW(b = a);
	EXPECT_EQ(a, b);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	int a_size_1 = 3;
	TMatrix<int> a(a_size_1), b(a_size_1 * 2);

	a = b;
	int a_size_2 = a.GetSize();

	EXPECT_NE(a_size_1, a_size_2);
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	int size = 3;
	TMatrix<int> a(size), b(size * 2);
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			a[i][j] = i + j;
		}
	}

	for (int i = 0; i < size * 2; i++) {
		for (int j = i; j < size * 2; j++) {
			b[i][j] = (i + j) * 2;
		}
	}

	ASSERT_NO_THROW(a = b);
	EXPECT_EQ(a, b);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	int size = 3;
	TMatrix<int> a(size);
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			a[i][j] = i + j;
		}
	}

	TMatrix<int> a_copy(a);

	EXPECT_TRUE(a == a_copy);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	int size = 3;
	TMatrix<int> a(size);
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			a[i][j] = i + j;
		}
	}

	EXPECT_TRUE(a == a);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	int size = 3;
	TMatrix<int> a(size), b(size * 2);

	EXPECT_TRUE(a != b);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	int size = 3;
	TMatrix<int> a(size), b(size), res(size);
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			a[i][j] = i + j;
			b[i][j] = (i + j) * 2;
		}
	}

	ASSERT_NO_THROW(res = a + b);

	for (int i = 0; i < size; i++) {
		EXPECT_TRUE(res[i] == a[i] + b[i]);
	}
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	int size = 3;
	TMatrix<int> a(size), b(size * 2), res(size);

	ASSERT_ANY_THROW(res = a + b);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	int size = 3;
	TMatrix<int> a(size), b(size), res(size);
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			a[i][j] = i + j;
			b[i][j] = (i + j) * 2;
		}
	}

	ASSERT_NO_THROW(res = a - b);

	for (int i = 0; i < size; i++) {
		EXPECT_TRUE(res[i] == a[i] - b[i]);
	}
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	int size = 3;
	TMatrix<int> a(size), b(size * 2), res(size);

	ASSERT_ANY_THROW(res = a - b);
}

