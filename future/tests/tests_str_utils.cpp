
// https://cpputest.github.io/
// sudo apt install cpputest
// g++ tests_str_utils.cpp ../src/str_utils.cc -o bin_tests_str_utils `pkg-config cpputest glibmm-2.4 --cflags --libs`

#include "../src/str_utils.h"
#include "CppUTest/CommandLineTestRunner.h"


TEST_GROUP(StrUtilsGroup)
{
};


TEST(StrUtilsGroup, replace_in_string)
{
    Glib::ustring test_replaces_str = "one two threetwo";
    CHECK(replace_in_string(test_replaces_str, "two", "four") == "one four threefour");
}

TEST(StrUtilsGroup, trim_string)
{
    Glib::ustring test_trim_str = "\t one two three ";
    CHECK(trim_string(test_trim_str) == "one two three");
}

TEST(StrUtilsGroup, gint64_from_gstring)
{
    CHECK(gint64_from_gstring("") == 0);
    CHECK(gint64_from_gstring("0x7fffffffffffffff") == 0x7fffffffffffffff);
    CHECK(gint64_from_gstring("-0x8000000000000000") == -0x8000000000000000);
    CHECK(gint64_from_gstring("1234") == 1234);
    CHECK(gint64_from_gstring("-1234") == -1234);
    CHECK(gint64_from_gstring("ffff", true) == 0xffff);
}

TEST(StrUtilsGroup, get_uint_from_hex_chars)
{
    CHECK(get_uint_from_hex_chars("aff", 2) == 0xaf);
    CHECK(get_uint_from_hex_chars("aff", 1) == 0xa);
}

TEST(StrUtilsGroup, gstring_split2ustring)
{
    std::list<Glib::ustring> splitted_list = gstring_split2ustring(":a:bc::d:", ":");
    CHECK(splitted_list == std::list<Glib::ustring>({"", "a", "bc", "", "d", ""}));
}

TEST(StrUtilsGroup, gstring_split2int64)
{
    std::list<gint64> splitted_list = gstring_split2int64("-1, 1,0, 1000", ",");
    CHECK(splitted_list == std::list<gint64>({-1, 1, 0, 1000}));
}

TEST(StrUtilsGroup, ustring_join4ustring)
{
    std::list<Glib::ustring> list_to_join({"", "a", "bc", "", "d", ""});
    Glib::ustring rejoined = ustring_join4ustring(list_to_join, ":");
    CHECK(rejoined == ":a:bc::d:");
}

TEST(StrUtilsGroup, ustring_join4int64)
{
    std::list<gint64> list_to_join({-1, 1, 0, 1000});
    Glib::ustring rejoined = ustring_join4int64(list_to_join, ",");
    CHECK(rejoined == "-1,1,0,1000");
}

TEST(StrUtilsGroup, set_rgb24_str_from_rgb24_int)
{
    guint32 int24 = (0xf1 << 16) | (0xab << 8) | 0x57;
    char rgb24_str[8];
    set_rgb24_str_from_rgb24_int(int24, rgb24_str);
    CHECK(g_strcmp0(rgb24_str, "#f1ab57") == 0);
}

TEST(StrUtilsGroup, get_rgb24_int_from_rgb24_str)
{
    guint32 expected_int24 = (0xf1 << 16) | (0xab << 8) | 0x57;
    CHECK(get_rgb24_int_from_rgb24_str("#f1ab57") == expected_int24);
    CHECK(get_rgb24_int_from_rgb24_str("f1ab57") == expected_int24);
}

TEST(StrUtilsGroup, set_rgb24_str_from_str_any)
{
    char rgb24_str[8];
    set_rgb24_str_from_str_any("#f1ab57", rgb24_str);
    CHECK(g_strcmp0(rgb24_str, "#f1ab57") == 0);
    set_rgb24_str_from_str_any("#fab", rgb24_str);
    CHECK(g_strcmp0(rgb24_str, "#ffaabb") == 0);
    set_rgb24_str_from_str_any("#122334455667", rgb24_str);
    CHECK(g_strcmp0(rgb24_str, "#123456") == 0);
    set_rgb24_str_from_str_any("122334455667", rgb24_str);
    CHECK(g_strcmp0(rgb24_str, "#123456") == 0);
}

TEST(StrUtilsGroup, get_rgb24_int_from_str_any)
{
    guint32 expected_int24 = (0xf1 << 16) | (0xab << 8) | 0x57;
    CHECK(get_rgb24_int_from_str_any("#f1ab57") == expected_int24);
    CHECK(get_rgb24_int_from_str_any("f1ab57") == expected_int24);
    CHECK(get_rgb24_int_from_str_any("f122ab335744") == expected_int24);
}


int main(int ac, char** av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}
