#pragma once
#include<iostream>
#include<unordered_map>
#include<map>

using namespace std;

class Storage {
	struct Product {
		string vendor_code;
		string product_name;
		string manufacturer;
		int price;
		Product(string vend = "none", string name = "none", string manuf = "none", int pr = -1) {
			vendor_code = vend;
			product_name = name;
			manufacturer = manuf;
			price = pr;
		}
	};
	
	unordered_map<string, Product> products;  // ключ - артикул
	multimap<string, Product> manufacturers;  // ключ - производитель

public:
	void add_product(string vend, string manuf, string name, int price);
	void remove_product(string vend);
	void get_product(string vend);
	void get_manufacturer_products(string manufacturer);
	void print_info();
};