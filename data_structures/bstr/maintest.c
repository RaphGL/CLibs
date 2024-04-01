#include "bstr.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  {
    bstr str = bstr_new("my first test");
    assert(str.len == 13);

    assert(bstr_equal(str, bstr_new("my first test")));
    assert(bstr_contains(str, bstr_new("y fir")));

    bstring string = bstr_to_bstring(str);
    assert(string.len == 13);
    assert(strcmp(string.cstr, "my first test") == 0);

    bstring new = bstring_new(" append this");
    size_t old_size = string.len;
    bstring_append(&string, new);
    assert(new.len + old_size == string.len);

    bstring_free(&new);
    new = bstring_new("my first test append this");
    assert(bstring_equal(string, new));

    bstring_free(&new);
    bstring_free(&string);
    assert(string.len == 0);
    assert(string.cstr == NULL);
  }

  {
    bstring str = bstring_with_capacity(10);
    assert(str.cap == 10 && str.len == 0);

    bstring_append_bstr(&str, bstr_new("hello"));
    assert(str.cap == 10 && str.len == 5);
    bstring_append_bstr(&str, bstr_new(" world!"));
    assert(str.cap == 12 && str.len == 12);

    bstring_reserve(&str, 20);
    assert(str.cap == 20 && str.len == 12 &&
           bstring_equal_bstr(str, bstr_new("hello world!")));

    bstring_free(&str);
  }

  {
    bstr to_trim = bstr_new("     remove spaces pwease?    ");
    bstring trim_this = bstr_to_bstring(to_trim);
    bstring_trim(&trim_this);
    assert(strcmp(trim_this.cstr, "remove spaces pwease?") == 0);

    bstring_append_bstr(&trim_this, bstr_new(" appended"));
    assert(bstring_equal_bstr(trim_this,
                              bstr_new("remove spaces pwease? appended")));
    bstring_free(&trim_this);

    const bstr expected_str = bstr_new("hello");
    bstring str1 = bstring_new("  \thello");
    bstring_trim_left(&str1);
    assert(bstring_equal_bstr(str1, expected_str));
    bstring_free(&str1);

    bstring str2 = bstring_new("hello\t\t    ");
    bstring_trim_right(&str2);
    assert(bstring_equal_bstr(str2, expected_str));
    bstring_free(&str2);
  }

  {
    bstr str1 = bstr_new("Hello World");
    bstr cmp1 = bstr_new("Hello");

    assert(bstr_startswith(str1, cmp1) == true);
    assert(bstr_startswith(str1, cmp1) == true);
    cmp1 = bstr_new("Hi");
    assert(bstr_startswith(str1, cmp1) == false);
    cmp1 = bstr_new("Hello there!!!!!!");
    assert(bstr_startswith(str1, cmp1) == false);

    bstr str2 = bstr_new("Hello World");
    bstr cmp2 = bstr_new("World");
    assert(bstr_endswith(str2, cmp2) == true);
    assert(bstr_endswith(str2, cmp2) == true);
    cmp2 = bstr_new("Hi");
    assert(bstr_endswith(str2, cmp2) == false);
    cmp2 = bstr_new("Hello there!!!!!!");
    assert(bstr_endswith(str2, cmp2) == false);

    assert(!bstr_equal(bstr_reverse(str2), bstr_new("dlroW olleH")));
    assert(bstr_equal(bstr_reverse(bstr_new("kayak")), bstr_new("kayak")));
  }

  {
    bstring s1 = bstring_new("HELLO");
    bstring s2 = bstring_new("hello");
    assert(bstring_equal(bstring_to_lower(s1), s2));
    assert(bstring_equal_bstr(bstring_to_upper(s2), bstr_new("HELLO")));

    bstring_free(&s1);
    bstring_free(&s2);
  }

  {
    bstr s1 = bstr_new("hello, how are you doing?");
    size_t idx = 0;
    assert(bstr_index(&idx, s1, bstr_new("hello")));
    assert(idx == 0);

    assert(bstr_index(&idx, s1, bstr_new("?")));
    assert(idx == 24);

    assert(bstr_index(&idx, s1, bstr_new("how are you")));
    assert(idx == 7);

    assert(bstr_index(&idx, s1, bstr_new("doing")));
    assert(idx == 19);
  }

  {
    bstr true_kebab = bstr_new("true-kebab-case-style");
    bstr fake_kebab = bstr_new("fake-Kebabcase-style");
    bstr camel = bstr_new("camelCaseStyle");
    bstr pascal = bstr_new("PascalCaseStyle");
    bstr ada = bstr_new("Ada_Case_Style");
    bstr snake = bstr_new("snake_case_style");

    assert(bstr_is_kebabcase(true_kebab));
    assert(!bstr_is_kebabcase(fake_kebab));

    assert(bstr_is_camelcase(camel));
    assert(!bstr_is_camelcase(pascal));
    assert(!bstr_is_camelcase(pascal));
    assert(!bstr_is_camelcase(snake));

    assert(bstr_is_pascalcase(pascal));
    assert(!bstr_is_pascalcase(camel));
    assert(!bstr_is_pascalcase(ada));

    assert(bstr_is_adacase(ada));
    assert(!bstr_is_adacase(snake));
    assert(!bstr_is_adacase(camel));

    assert(bstr_is_snakecase(snake));
    assert(!bstr_is_snakecase(ada));
    assert(!bstr_is_snakecase(pascal));
  }

  {
    bstr t0 = bstr_new("this is great, this has 3 this in it");
    bstr t1 = bstr_new("should have zero dis with an TH in it");
    bstr t2 = bstr_new("has two numbers 3 in it :3");

    assert(bstr_count(t0, bstr_new("this")) == 3);
    assert(bstr_count(t1, bstr_new("this")) == 0);
    assert(bstr_count(t2, bstr_new("3")) == 2);
    assert(bstr_count(t2, bstr_new("")) == 0);
  }

  puts("Passed all tests.");
  return 0;
}
