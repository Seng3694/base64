# base64 C library #

C library which can encode bytes to base64 strings and base64 strings to bytes.
Because the resulting length is precalculated only one `malloc` call is used per function.

## How to use ##

### Strings ###

```c
#include <base64.h>

int main(void)
{
    const char* string = "hello world";
    const char* expected = "aGVsbG8gd29ybGQ=";
    char* encoded = base64_encode(string, strlen(string));
    //true for C string '\0'
    char* decoded = base64_decode(encoded, B64_TRUE);
    
    assert(streq(string, decoded));
    assert(streq(expected, encoded));
    
    free(encoded);
    free(decoded);
    
    return 0;
}
```

### Structs ###

```c
#include <base64.h>

int main(void)
{
    struct TestStruct
    {
    	unsigned int a;
    	int b;
    	float c;
    	double d;
    };
    
    struct TestStruct test;
    test.a = 20;
    test.b = -123;
    test.c = -0.123f;
    test.d = 1234.123456789;
    
    char* encoded = base64_encode(&test, sizeof(struct TestStruct));
    //false because it is no string
    struct TestStruct* decoded = base64_decode(encoded, B64_FALSE);
    
    assert(decoded->a == test.a);
    assert(decoded->b == test.b);
    assert(decoded->c == test.c);
    assert(decoded->d == test.d);
    
    free(encoded);
    free(decoded);
    return 0;
}
```

## Build ##
Project uses [CMake][1].

You can include this project as a submodule:
```
git submodule add "https://github.com/Seng3694/base64"
```

And then add the directory to your CMakeLists:
```CMake
add_subdirectory(base64)
```

And link it with your application:
```CMake
target_link_libraries(YOUR_TARGET base64)
```

Or just embed it manually.

## License ##
This library is licensed under the MIT License. See [LICENSE][2] for more information.

[1]:http://www.cmake.org/
[2]:LICENSE
