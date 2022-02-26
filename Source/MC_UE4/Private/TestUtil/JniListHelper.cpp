#include <TestUtil/JniListHelper.h>
#include <TestUtil/JavaTestUtil.h>

jobjectArray JniListHelper::ToIntegerArray(TArray<int> ints)
{
	// getting java info
	jclass jintCls = JNI_ENV->FindClass("java/lang/Integer");
	jmethodID jintCtor = JNI_ENV->GetMethodID(jintCls, "<init>", "(I)V");
	jobject objDefault = JNI_ENV->NewObject(jintCls, jintCtor, (jint)0);

	// allocating the jvm array
	jobjectArray arr = JNI_ENV->NewObjectArray(ints.Num(), jintCls, objDefault);

	// setting list items
	for (int i = 0; i < ints.Num(); ++i)
	{
		jobject index = JNI_ENV->NewObject(jintCls, jintCtor, (jint)ints[i]);
		JNI_ENV->SetObjectArrayElement(arr, i, index);
	}

	return arr;
}

jobject JniListHelper::ToList(jobjectArray ints)
{
	// using Arrays.asList(T ... a) builtin to convert.
	jclass arraysCls = JNI_ENV->FindClass("java/util/Arrays");
	jmethodID asListMethod = JNI_ENV->GetStaticMethodID(
		arraysCls,
		"asList",
		"([Ljava/lang/Object;)Ljava/util/List;"
	);
	jobject list = JNI_ENV->CallStaticObjectMethod(
		arraysCls, 
		asListMethod, 
		ints
	);

	return list;
}

jobject JniListHelper::ToList(TArray<int> ints)
{
	// converting list
	jobjectArray arr = ToIntegerArray(ints);
	jobject list = ToList(arr);

	// cleanup
	JNI_ENV->DeleteLocalRef(arr);

	return list;
}
