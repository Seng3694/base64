#include <base64.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#define streq(lhs, rhs) (strcmp(lhs, rhs) == 0)
#define TEST(description) description##_test(void)
#define RUN(name) name##_test()

TEST(string_to_base64);
TEST(loremipsum_to_base64);
TEST(struct_to_base64);

int main()
{
	RUN(string_to_base64);
	RUN(loremipsum_to_base64);
	RUN(struct_to_base64);

	return 0;
}

TEST(string_to_base64)
{
	const char* string = "hello world";
	const char* expected = "aGVsbG8gd29ybGQ=";
	char* encoded = base64_encode(string, strlen(string));
	char* decoded = base64_decode(encoded, B64_TRUE);

	assert(streq(string, decoded));
	assert(streq(expected, encoded));

	free(encoded);
	free(decoded);
}

TEST(loremipsum_to_base64)
{
	const char* string = "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam";
	const char* expected = "TG9yZW0gaXBzdW0gZG9sb3Igc2l0IGFtZXQsIGNvbnNldGV0dXIgc2FkaXBzY2luZyBlbGl0ciwgc2VkIGRpYW0gbm9udW15IGVpcm1vZCB0ZW1wb3IgaW52aWR1bnQgdXQgbGFib3JlIGV0IGRvbG9yZSBtYWduYSBhbGlxdXlhbSBlcmF0LCBzZWQgZGlhbSB2b2x1cHR1YS4gQXQgdmVybyBlb3MgZXQgYWNjdXNhbSBldCBqdXN0byBkdW8gZG9sb3JlcyBldCBlYSByZWJ1bS4gU3RldCBjbGl0YSBrYXNkIGd1YmVyZ3Jlbiwgbm8gc2VhIHRha2ltYXRhIHNhbmN0dXMgZXN0IExvcmVtIGlwc3VtIGRvbG9yIHNpdCBhbWV0LiBMb3JlbSBpcHN1bSBkb2xvciBzaXQgYW1ldCwgY29uc2V0ZXR1ciBzYWRpcHNjaW5nIGVsaXRyLCBzZWQgZGlhbSBub251bXkgZWlybW9kIHRlbXBvciBpbnZpZHVudCB1dCBsYWJvcmUgZXQgZG9sb3JlIG1hZ25hIGFsaXF1eWFtIGVyYXQsIHNlZCBkaWFtIHZvbHVwdHVhLiBBdCB2ZXJvIGVvcyBldCBhY2N1c2FtIGV0IGp1c3RvIGR1byBkb2xvcmVzIGV0IGVhIHJlYnVtLiBTdGV0IGNsaXRhIGthc2QgZ3ViZXJncmVuLCBubyBzZWEgdGFraW1hdGEgc2FuY3R1cyBlc3QgTG9yZW0gaXBzdW0gZG9sb3Igc2l0IGFtZXQuIExvcmVtIGlwc3VtIGRvbG9yIHNpdCBhbWV0LCBjb25zZXRldHVyIHNhZGlwc2NpbmcgZWxpdHIsIHNlZCBkaWFtIG5vbnVteSBlaXJtb2QgdGVtcG9yIGludmlkdW50IHV0IGxhYm9yZSBldCBkb2xvcmUgbWFnbmEgYWxpcXV5YW0=";
	char* encoded = base64_encode(string, strlen(string));
	char* decoded = base64_decode(encoded, B64_TRUE);

	assert(streq(string, decoded));
	assert(streq(expected, encoded));

	free(encoded);
	free(decoded);
}

TEST(struct_to_base64)
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
	struct TestStruct* decoded = base64_decode(encoded, B64_FALSE);

	assert(decoded->a == test.a);
	assert(decoded->b == test.b);
	assert(decoded->c == test.c);
	assert(decoded->d == test.d);

	free(encoded);
	free(decoded);
}
