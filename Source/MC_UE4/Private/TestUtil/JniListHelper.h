#pragma once
#include <TestUtil/JavaTestUtil.h>

class JniListHelper
{
public:
	/**
	 * Convert an int array from C++ to a java Int[].
	 * 
	 * @param ints List of integers to put into jvm.
	 */
	static jintArray ToIntArray(TArray<int> ints);

	/**
	 * Convert a java int array to a java List<int>.
	 * 
	 * @param ints Existing int array to convert.
	 */
	static jobject ToList(jintArray ints);

	/**
	 * Convert an TArray<int> to a java List<int>.
	 * 
	 * @param ints List of integers to put into a jvm list.
	 * 
	 * @see ToIntArray(TArray<int>)
	 * @see ToList(jintArray)
	 */
	static jobject ToList(TArray<int> ints);
};
