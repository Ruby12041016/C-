/*
题目描述
小明正在整理一批历史文献。这些历史文献中出现了很多日期。小明知道这些日期都在1960 年 1 月 1 日至 2059 年 12 月 31日。
令小明头疼的是，这些日期采用的格式非常不统一，有采用年/月/日的，有采用月/日/年的，还有采用日/月/年的。
更加麻烦的是，年份也都省略了前两位，使得文献上的一个日期，存在很多可能的日期与其对应。
比如 02/03/04，可能是 2002 年 03 月 04 日、2004 年 02 月 03 日或 2004 年 03 月02 日。
给出一个文献上的日期，你能帮助小明判断有哪些可能的日期对其对应吗？
输入描述
一个日期，格式是 "AA/BB/CC" (0≤A,B,C≤9)。
输出描述
输出若干个不相同的日期，每个日期一行，格式是 "yyyy−MM−dd"。多个日期按从早到晚排列。
*/

#include <iostream>
using namespace std;

int maxday[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool ru(int year) {
    if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
        return true;
    return false;
}

bool check(int year, int month, int day) {
    if (year >= 1960 && year <= 2059 && month > 0 && month <= 12 && day > 0 &&
        day <= 31) {
        if (month == 2) {
            if (ru(year)) {
                if (day - 1 <= maxday[2])
                    return true;
            } else {
                if (day <= maxday[2])
                    return true;
            }
        } else {
            if (day <= maxday[month])
                return true;
        }
    }
    return false;
}
int main() {
    int a, b, c;
    scanf("%d/%d/%d", &a, &b, &c);
    int year = 0;
    int month = 0;
    int day = 0;
    for (int i = 19600101; i <= 20591231; i++) {
        year = i / 10000;
        month = i % 10000 / 100;
        day = i % 100;
        if ((year % 100 == a && month == b && day == c) ||
            (month == a && day == b && year % 100 == c) ||
            (day == a && month == b && year % 100 == c)) {
            if (check(year, month, day)) {
                printf("%d-%02d-%02d\n", year, month, day);
            }
        }
    }
    return 0;
}

/*  更完善的解法
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

int maxday[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// 判断闰年
bool ru(int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

// 检查日期是否合法
bool check(int year, int month, int day) {
    if (year < 1960 || year > 2059) return false;
    if (month < 1 || month > 12) return false;

    int limit = maxday[month];
    if (month == 2 && ru(year)) {
        limit = 29;  // 闰年2月是29天
    }

    return day >= 1 && day <= limit;
}

int main() {
    int a, b, c;
    scanf("%d/%d/%d", &a, &b, &c);

    set<string> result;  // 使用set自动排序和去重

    // 尝试三种可能的日期格式
    // 1. 年/月/日
    for (int century = 19; century <= 20; century++) {
        int year = century * 100 + a;
        int month = b;
        int day = c;
        if (check(year, month, day)) {
            char date[20];
            sprintf(date, "%04d-%02d-%02d", year, month, day);
            result.insert(date);
        }
    }

    // 2. 月/日/年
    for (int century = 19; century <= 20; century++) {
        int year = century * 100 + c;
        int month = a;
        int day = b;
        if (check(year, month, day)) {
            char date[20];
            sprintf(date, "%04d-%02d-%02d", year, month, day);
            result.insert(date);
        }
    }

    // 3. 日/月/年
    for (int century = 19; century <= 20; century++) {
        int year = century * 100 + c;
        int month = b;
        int day = a;
        if (check(year, month, day)) {
            char date[20];
            sprintf(date, "%04d-%02d-%02d", year, month, day);
            result.insert(date);
        }
    }

    // 输出结果
    for (const string& date : result) {
        cout << date << endl;
    }

    return 0;
}
*/