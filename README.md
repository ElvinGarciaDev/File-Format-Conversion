# 🚗 Automobile Speed/Distance Tracker

This project involves designing and creating a C++ program that will convert a “pipe-delimited” text file to a file in CSV format. (The vertical bar character, “|”, is often called a “pipe” character. For this reason, a text file with vertical bar delimiters is often called a “pipe-delimited” file.)

![Screen Shot 2022-11-24 at 9 56 20 PM](https://user-images.githubusercontent.com/91163017/203891579-7e4b833d-f0cd-4adb-8150-cf7fb0993eb0.png)

Before:
<img width="842" alt="Screen Shot 2022-11-24 at 9 56 42 PM" src="https://user-images.githubusercontent.com/91163017/203891624-f46df8f2-99e6-45ad-93ac-3ccc71cbab0e.png">

After:
<img width="832" alt="Screen Shot 2022-11-24 at 9 58 00 PM" src="https://user-images.githubusercontent.com/91163017/203891637-12ac227a-8234-4e37-9b8a-1633befa07c1.png">




## How It's Made:

**Tech used:** C++11


There are many discussions of “CSV” file format on the internet. It is a mechanism to represent multiple fields per line of text, without using any special, non-standard characters.
The obvious complicating factor with a file format like this is: How do you handle the case where the field delimiter (in this case, a comma) is present in the data? The short answer is to surround those fields with double- quote characters. But what if the original data contains a double-quote character? CSV addresses this issue by “escaping” the double-quote characters: it replaces each original double-quote character with TWO double-quote characters.
A further complication would be: What if the data field itself contains the record separator (new-line) character? Some CSV implementations address this, but for this project we do not consider this case.

## Installation

1. Clone repo
2. (https://www.youtube.com/watch?v=XaFg2vS62Bg&ab_channel=MackenzieRothenberger)

