INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src")

ADD_EXECUTABLE(iteratorTinyTest iteratorTinyTest.cc)


ADD_EXECUTABLE(TinySTL_constructTest TinySTL_constructTest.cc)
SET(TinySTL_allocTest_SRC TinySTL_allocTest.cc ../src/TinySTL_alloc.cc)
ADD_EXECUTABLE(TinySTL_allocTest ${TinySTL_allocTest_SRC})


SET(TinySTL_uninitializedTest_SRC TinySTL_uninitializedTest.cc ../src/TinySTL_alloc.cc)
ADD_EXECUTABLE(TinySTL_uninitializedTest ${TinySTL_uninitializedTest_SRC})



SET(TinySTL_algorithmTest_SRC TinySTL_algorithmTest.cc )
ADD_EXECUTABLE(TinySTL_algorithmTest ${TinySTL_algorithmTest_SRC})



SET(TinySTL_vectorTest_SRC TinySTL_vectorTest.cc ../src/TinySTL_alloc.cc)
ADD_EXECUTABLE(TinySTL_vectorTest ${TinySTL_vectorTest_SRC})



SET(TinySTL_listTest_SRC TinySTL_listTest.cc ../src/TinySTL_alloc.cc)
ADD_EXECUTABLE(TinySTL_listTest ${TinySTL_listTest_SRC})


SET(TinySTL_rbtreeTest_SRC TinySTL_rbtreeTest.cc ../src/TinySTL_alloc.cc)
ADD_EXECUTABLE(TinySTL_rbtreeTest ${TinySTL_rbtreeTest_SRC})

SET(TinySTL_setTest_SRC TinySTL_setTest.cc ../src/TinySTL_alloc.cc)
ADD_EXECUTABLE(TinySTL_setTest ${TinySTL_setTest_SRC})
